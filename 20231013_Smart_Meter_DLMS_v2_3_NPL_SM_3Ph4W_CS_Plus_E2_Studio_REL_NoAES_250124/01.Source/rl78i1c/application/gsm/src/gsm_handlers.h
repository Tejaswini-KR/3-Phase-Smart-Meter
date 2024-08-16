#ifndef  __GSM_STATE_HANDLER_H__
#define  __GSM_STATE_HANDLER_H__

#include "fsm.h"

eFsmEvent gsm_idle_state(bool_t isEntry);
eFsmEvent gsm_init_state(bool_t isEntry);
eFsmEvent gsm_gprs_init_state(bool_t isEntry);
eFsmEvent gsm_gprs_transparent_mode_state(bool_t isEntry); //transparent_mode
eFsmEvent gsm_gprs_transparent_mode_connect_state(bool_t isEntry);
eFsmEvent gsm_gprs_wait_for_data_state(bool_t isEntry);

#endif