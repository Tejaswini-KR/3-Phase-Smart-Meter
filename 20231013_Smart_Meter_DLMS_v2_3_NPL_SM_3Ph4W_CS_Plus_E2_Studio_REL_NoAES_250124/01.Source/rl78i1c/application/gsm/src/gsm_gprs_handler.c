#include <string.h>
#include "r_cg_macrodriver.h"
#include "r_cg_sau.h"
#include "em_core.h"        /* EM Core APIs */
#include "fsm.h"
#include "utils.h"
#include "event_log.h"
#include "gsm_utils.h"
#include "gsm_settings.h"
#include "typedef.h"
//#include "energy.h"
//#include "energy_internal.h" 
#include "em_display.h" 
#include "em_type.h"
//#include "wrp_user_ext.h"
#include "em_type.h"

/* Wrapper/User */
//#include "wrp_user_uart.h"          /* UART Wrapper header */

//#define DATA_SEND_INTERVAL   	60
#define GSM_TRANSPARENT_MODE	

extern uint8_t g_received_byte;
extern uint8_t g_received_byte_1st;

uint8_t g_gsm_gprs_connect_flag=0;
uint8_t Gsm_PrepareData(char cmdBuffer[], uint16_t cmd_buffer_len);
uint8_t recv_data_in_transmode(char *cmdBufferptr, uint16_t cmd_buffer_len);

typedef enum
{
    GSM_GPRS_INIT_ATTACH,
    GSM_GPRS_INIT_SET_APN,
    GSM_GPRS_INIT_ENABLE,
    GSM_GPRS_INIT_END
	
} GsmGprsInitStates_t;


CommandResponse_t GsmGprsInitStateCmdResp[GSM_GPRS_INIT_END] = {
    {"AT+CGATT=1", "OK", NULL},
	{"AT+CGDCONT=1,\"IPV4V6\",%s","OK", NULL},
    {"AT+CGACT=1,1", "OK", NULL}
};

eFsmEvent gsm_gprs_init_state(bool_t isEntry)
{
    static uint16_t currState = GSM_GPRS_INIT_ATTACH;
	uint16_t prevState = currState;
    eFsmEvent returnEvent = FSM_EVENT_NO_CHANGE;

	#define CMD_BUFFER_LEN 600
    char cmdBuffer[CMD_BUFFER_LEN];

   	if (currState == GSM_GPRS_INIT_SET_APN) {
		
        sprintf(cmdBuffer,GsmGprsInitStateCmdResp[currState].pCommandStr,
                g_GsmGprsApn);
        GsmGprsInitStateCmdResp[currState].pAltCommandStr = cmdBuffer;
    }

	prevState = currState;
	
    returnEvent = gsm_state_handler_generic(isEntry, (uint16_t)GSM_GPRS_INIT_ATTACH, (uint16_t)GSM_GPRS_INIT_END,
                                            &currState, (const CommandResponse_t*)GsmGprsInitStateCmdResp);
	
    GsmGprsInitStateCmdResp[prevState].pAltCommandStr = NULL;

    return returnEvent;
}

// GPRS_TRANSPARENT_MODE
typedef enum
{
    GSM_GPRS_TRANPARENT_SOCKET_PRE_CLOSE = 0,
	GSM_GPRS_TRANSPARENT_DEACT,
	GMS_GPRS_TRANSPARENT_ACTIVATE,
    GSM_GPRS_TRANPARENT_SOCKET_OPEN,
	GSM_GPRS_TRANSPARENT_SOCKET_STATUS,
	GSM_GPRS_TRANSPARENT_SOCKET_END
} GsmGprstransparentmodeStates_t;

CommandResponse_t GsmGprsTransparentmodeStateCmdResp[GSM_GPRS_TRANSPARENT_SOCKET_END] = {
    {"AT+QICLOSE=1", "OK", NULL},
	{"AT+QIDEACT=1", "OK", NULL},
	{"AT+QIACT=1", "OK", NULL},
	{"AT+QIOPEN=1,1,\"TCP LISTENER\",\"127.0.0.1\",0,2020,2", "OK", NULL},
	{"AT+QISTATE?", "OK", NULL},
};

eFsmEvent gsm_gprs_transparent_mode_state(bool_t isEntry)
{	
    static uint16_t currState = GSM_GPRS_TRANPARENT_SOCKET_PRE_CLOSE;//cmd_mode
	uint16_t prevState = currState;
    eFsmEvent returnEvent = FSM_EVENT_NO_CHANGE;
	
	#define CMD_BUFFER_LEN 600
    char cmdBuffer[CMD_BUFFER_LEN];
	char *ptr;
	uint16_t buflen,i;
	uint16_t transmode_buf[512];

	prevState = currState;
	
    returnEvent = gsm_state_handler_generic(isEntry, GSM_GPRS_TRANPARENT_SOCKET_PRE_CLOSE, GSM_GPRS_TRANSPARENT_SOCKET_END,
                                            &currState, GsmGprsTransparentmodeStateCmdResp);//cmd_mode

    GsmGprsTransparentmodeStateCmdResp[prevState].pAltCommandStr = NULL;
	

    return returnEvent;
}


typedef enum
{
	GSM_GPRS_WAIT_FOR_CONNECT = 0,
	GSM_GPRS_WAIT_FOR_DISCONNECT,
    GSM_GPRS_TRANSPARENT_CONNECT_END
} GsmGprstransparentmodeconnectStates_t;

CommandResponse_t GsmGprsTransparentmodeconnectStateCmdResp[GSM_GPRS_TRANSPARENT_CONNECT_END] = {
	
	{"AT", "CONNECT", NULL},
	{"", "NO CARRIER", NULL},
};

eFsmEvent gsm_gprs_transparent_mode_connect_state(bool_t isEntry)
{	
    static uint16_t currState = GSM_GPRS_WAIT_FOR_CONNECT;//cmd_mode
	uint16_t prevState = currState;
    eFsmEvent returnEvent = FSM_EVENT_NO_CHANGE;

	if (currState == GSM_GPRS_WAIT_FOR_DISCONNECT) 
	{
		g_gsm_gprs_connect_flag = 1;
    }
	else 
	{
		g_gsm_gprs_connect_flag = 0;
	}
	
	prevState = currState;
	
    returnEvent = gsm_state_handler_generic(isEntry, GSM_GPRS_WAIT_FOR_CONNECT, GSM_GPRS_TRANSPARENT_CONNECT_END,
                                            &currState, GsmGprsTransparentmodeconnectStateCmdResp);//cmd_mode

    GsmGprsTransparentmodeconnectStateCmdResp[prevState].pAltCommandStr = NULL;
	
    return returnEvent;
}



eFsmEvent gsm_gprs_wait_for_data_state(bool_t isEntry)
{
    static uint32_t time_tick_snap = 0;

#ifdef SIMULATION
    log_debug(__FUNCTION__);
#endif

    if (isEntry)
    {
        time_tick_snap = get_tick_count();
    }

//    if (get_elapsed_time_in_s(time_tick_snap) >= DATA_SEND_INTERVAL)
//    {
//        return FSM_EVENT_ACK;
//    }

    return FSM_EVENT_NO_CHANGE;
}