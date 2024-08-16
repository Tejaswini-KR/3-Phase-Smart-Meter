#ifndef __FSM_DEFINITIONS_H__
#define __FSM_DEFINITIONS_H__

#include "utils.h"
#include "gsm_typedef.h"

#define FSM_STATE(state) STATE_##state

typedef enum {
    FSM_ERROR = -2,
    FSM_START = -1,
    #include "gsm_state.h"
    ,FSM_END
} eFsmState;

#undef FSM_STATE

typedef enum {
    
    FSM_EVENT_NO_CHANGE = 0,
    FSM_EVENT_ACK,
    FSM_EVENT_RETRY,
    FSM_EVENT_TIMEOUT,
    FSM_EVENT_ERROR,
    FSM_EVENT_FATAL_ERROR,
    FSM_EVENT_END
} eFsmEvent;

//typedef of state handler
typedef eFsmEvent (*StateHandler_t)(bool_t isEntry);

//typedef of state handler
typedef bool_t (*OnTransition_t)(void);

//structure of event with event handler
typedef struct
{
    eFsmEvent       Event;
    eFsmState       NextState;
    OnTransition_t  pOnTransition;
} StateTransition;

//structure of state and event with event handler
typedef struct
{
    StateHandler_t      pStateHandler;
    uint32_t            waitTime;
    StateTransition*    pTransitHandler;
    uint16_t            SizeTransition;
} StateMachine;

void fsm_start(void);
bool_t fsm_process(const StateMachine *pStateMachine);

eFsmState fsm_get_state(void);
void fsm_set_state(eFsmState newState);
const char * fsm_get_state_name(eFsmState state);

#define TRANSITION_OBJ_AND_SIZE(TransitionObject) \
        TransitionObject, SIZE_OF_ARRAY(TransitionObject)

#define TRANSITION_OBJ_AND_SIZE_NULL() NULL, 0

#define WAIT_FOREVER        0xFFFFFFFF

#define STATE_RETRY_MAX     1

#endif
