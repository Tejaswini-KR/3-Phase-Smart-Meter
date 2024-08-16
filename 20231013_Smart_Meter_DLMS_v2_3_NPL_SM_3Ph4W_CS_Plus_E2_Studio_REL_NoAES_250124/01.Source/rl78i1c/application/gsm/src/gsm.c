#include <stdio.h>

#include "fsm.h"
#include "event_log.h"
#include "gsm_handlers.h"

#define FSM_STATE(state) STATE_##state

// GSM_IDLE
static StateTransition g_GsmIdleTransition[] = 
{
    {FSM_EVENT_ACK, FSM_STATE(GSM_INIT), NULL}
};

// GSM_INIT
static StateTransition g_GsmInitTransition[] = 
{
    {FSM_EVENT_ACK, FSM_STATE(GSM_GPRS_INIT), NULL},
    {FSM_EVENT_ERROR, FSM_STATE(GSM_IDLE), NULL}
};

// GSM_GPRS_INIT
static StateTransition g_Gsm_Gprs_InitTransition[] = 
{
    {FSM_EVENT_ACK, FSM_STATE(GSM_GPRS_TRANSPARENT_MODE), NULL},
    {FSM_EVENT_ERROR, FSM_STATE(GSM_IDLE), NULL}
};

//GSM_GPRS_TRASPARENT_MODE //transparent_mode
static StateTransition g_GsmGprstransparentmode[] = 
{
    {FSM_EVENT_ACK,   FSM_STATE(GSM_GPRS_WAIT_FOR_CONNECT), NULL},
    {FSM_EVENT_ERROR, FSM_STATE(GSM_INIT), NULL}
};

// GSM_GPRS_WAIT_FOR_CONNECT
static StateTransition g_GsmGprsTransparentModeConnect[] = 
{
    {FSM_EVENT_ACK,   FSM_STATE(GSM_GPRS_WAIT_FOR_CONNECT), NULL},
    {FSM_EVENT_ERROR, FSM_STATE(GSM_GPRS_INIT), NULL}
};


static StateMachine g_GsmStateMachine[FSM_END] = 
{
    // GSM_STATE_IDLE
    {gsm_idle_state, 2, TRANSITION_OBJ_AND_SIZE(g_GsmIdleTransition)},
    
    // GSM_STATE_INIT
    {gsm_init_state, 30, TRANSITION_OBJ_AND_SIZE(g_GsmInitTransition)},
	
	// GSM_GPRS_GPRS_TRANSPARENT_MODE
    {gsm_gprs_init_state, 2, TRANSITION_OBJ_AND_SIZE(g_Gsm_Gprs_InitTransition)},
	
	// GSM_GPRS_GPRS_TRANSPARENT_MODE
    {gsm_gprs_transparent_mode_state, 2, TRANSITION_OBJ_AND_SIZE(g_GsmGprstransparentmode)},

    // GSM_GPRS_WAIT_FOR_CONNECT
    {gsm_gprs_transparent_mode_connect_state, WAIT_FOREVER, TRANSITION_OBJ_AND_SIZE(g_GsmGprsTransparentModeConnect)},
};

void gsm_fsm_entry(void)
{
#ifdef SIMULATION
    log_print(__FUNCTION__);
#endif
    fsm_start();
}

void GSM_PollingProcess(void)
{
    eFsmState curState = fsm_get_state();
   
    if ( curState == FSM_START ) {
        gsm_fsm_entry();
    }
    
    fsm_process(g_GsmStateMachine);
}
