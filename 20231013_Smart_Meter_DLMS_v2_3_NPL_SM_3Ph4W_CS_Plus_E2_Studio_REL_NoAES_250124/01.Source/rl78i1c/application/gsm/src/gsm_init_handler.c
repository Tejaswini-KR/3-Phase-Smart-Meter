#include <string.h>

#include "fsm.h"
#include "uart.h"
#include "utils.h"
#include "event_log.h"
#include "gsm_utils.h"

extern uint8_t g_gsm_gprs_connect_flag;

typedef enum
{
	GSM_GPRS_SEND_ECHO_OFF = 0,
    GSM_INIT_CHECK_CONNECTION,
    GSM_INIT_STATE_END
} GsmInitStates_t;

const CommandResponse_t GsmInitStateCmdResp[GSM_INIT_STATE_END] = 
{
	{"ATE0", "OK", NULL},
    {"AT", "OK", NULL},
};

eFsmEvent gsm_init_state(bool_t isEntry)
{
    static uint16_t currState = GSM_GPRS_SEND_ECHO_OFF;
    eFsmEvent returnEvent = FSM_EVENT_NO_CHANGE;

	g_gsm_gprs_connect_flag = 0;
	
    returnEvent = gsm_state_handler_generic(isEntry, GSM_GPRS_SEND_ECHO_OFF, GSM_INIT_STATE_END,
                                     &currState, GsmInitStateCmdResp);
    return returnEvent;
}
