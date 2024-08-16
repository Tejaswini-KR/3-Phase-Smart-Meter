#include <string.h>
#include <stdlib.h>
#include "gsm_typedef.h"
#include "fsm.h"
#include "relay.h"
#include "utils.h"
#include "uart.h"
#include "event_log.h"
#include "gsm_status.h"

#define INIT_CMD_RESP_LEN 100
static char g_CmdResponse[INIT_CMD_RESP_LEN];

static bool_t g_CmdError = FALSE;

static uint16_t g_CmeErrorNumber = 0;

const char AT_CmdError[] = "ERROR";
const char CME_ErrorStr[] = "+CME ERROR:";
const char SM_RelayStr[] = "+SM:RELAY=";

bool_t is_error(void)
{
    return g_CmdError || g_CmeErrorNumber ? TRUE : FALSE;
}

uint16_t get_cme_error(void)
{
    return g_CmeErrorNumber;
}

void reset_error(void)
{
    g_CmdError = FALSE;
    g_CmeErrorNumber = 0;
}

/// @brief
/// @return
bool_t is_response_received(const char *expResponse)
{
    bool_t ret_value = FALSE;
    const char *pStrRef = NULL;

    if (ReceiveResponse(g_CmdResponse, INIT_CMD_RESP_LEN))
    {
        if (pStrRef = strstr(g_CmdResponse, expResponse))
        {
            g_CmdError = FALSE;
            g_CmeErrorNumber = 0;
            ret_value = TRUE;
        }
        
        if (pStrRef = strstr(g_CmdResponse, CME_ErrorStr))
        {
            pStrRef += (strlen(CME_ErrorStr) + 1);
            g_CmeErrorNumber = atoi(pStrRef);
#ifdef SIMULATION
            log_error("CMR Error: %d", g_CmeErrorNumber);
#endif
            ret_value = TRUE;
        }
        else if (pStrRef = strstr(g_CmdResponse, AT_CmdError))
        {
            g_CmdError = TRUE;
#ifdef SIMULATION
            log_error("AT CMD Error");
#endif
            ret_value = TRUE;
        }
        else if (pStrRef = strstr(g_CmdResponse, SM_RelayStr))
        {
            pStrRef += (strlen(SM_RelayStr));
            set_relay_status(atoi(pStrRef));
#ifdef SIMULATION
            log_info("Relay Status: %d", get_relay_status());
#endif
        }
    }

    return ret_value;
}

bool_t is_ok_received(void)
{
    return is_response_received("OK");
}

uint16_t gsm_state_handler_generic(bool_t isEntry, uint16_t initState, uint16_t endState,
                                   __far uint16_t *pChildState, const CommandResponse_t *arrCmdResp)
{
    static volatile bool_t awaitingResponse = FALSE;
    uint16_t childState = 0;
    const char *pCommandStr = NULL;
	eFsmEvent returnEvent = FSM_EVENT_NO_CHANGE;
	
	childState = *pChildState;
    
    if (isEntry)
    {
        reset_error();
        childState = initState;
        awaitingResponse = FALSE;
    }

	if (childState >= endState)
    {
        awaitingResponse = FALSE;
        return endState;
    }

    if (awaitingResponse == TRUE)
    {
        if (is_response_received(arrCmdResp[childState].pResponseStr))
        {
            if ( is_error() == FALSE ) 
			{
                childState = childState + 1;
            }
            awaitingResponse = FALSE;
        }
    }
    else
    {
        if (arrCmdResp[childState].pAltCommandStr != NULL)
        {
            pCommandStr = arrCmdResp[childState].pAltCommandStr;
        }
        else
        {
            pCommandStr = arrCmdResp[childState].pCommandStr;
        }

        SendData(pCommandStr, strlen(pCommandStr), TRUE);
        awaitingResponse = TRUE;
    }
	
    if ( is_error() )
    {
        returnEvent = FSM_EVENT_ERROR;
    }
    else if (childState >= endState)
    {
		childState = initState;
        returnEvent = FSM_EVENT_ACK;
    }
	
	*pChildState = childState;
	
    return returnEvent;
}
