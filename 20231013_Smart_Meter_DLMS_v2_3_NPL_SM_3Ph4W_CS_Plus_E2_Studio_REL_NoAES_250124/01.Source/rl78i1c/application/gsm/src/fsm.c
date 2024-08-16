#include "fsm.h"
#include "utils.h"
#include "event_log.h"

#ifdef SIMULATION
#define FSM_STATE(state) #state
const char fsm_state_names[FSM_END][30] = {
#include "gsm_state.h"
};
#undef FSM_STATE

const char fsm_event_names[FSM_EVENT_END][25] = {
    "FSM_EVENT_NO_CHANGE",
    "FSM_EVENT_ACK",
    "FSM_EVENT_RETRY",
    "FSM_EVENT_TIMEOUT",
    "FSM_EVENT_ERROR",
    "FSM_EVENT_FATAL_ERROR"
};
#endif

#define FSM_STATE(state) STATE_##state

static eFsmState g_FsmCurrState = FSM_START;
static eFsmState g_FsmNextState = FSM_START;
static eFsmEvent g_FsmStateEvent = FSM_EVENT_NO_CHANGE;

void fsm_start(void)
{
    g_FsmNextState = FSM_START + 1;
}

eFsmState fsm_get_state(void)
{
    return g_FsmCurrState;
}

void fsm_set_state(eFsmState newState)
{
    g_FsmCurrState = newState < FSM_END ? newState : g_FsmCurrState;
}
#ifdef SIMULATION
const char *fsm_get_state_name(eFsmState state)
{
    if ((state > FSM_START) && (state < FSM_END))
    {
        return fsm_state_names[state];
    }
    else if (state == FSM_START)
    {
        return "FSM_START";
    }
    else if (state == FSM_ERROR)
    {
        return "FSM_ERROR";
    }
    return "unknown";
}


const char *fsm_get_event_name(eFsmEvent event)
{
    if ((event >= FSM_EVENT_NO_CHANGE) && (event < FSM_END))
    {
        return fsm_event_names[event];
    }
    return "unknown";
}
#endif

bool_t fsm_process(const StateMachine *pStateMachine)
{
    static uint32_t time_tick_snap = 0;
    static uint16_t retry_count = 0;

    eFsmEvent newEvent = FSM_EVENT_NO_CHANGE;
    StateTransition *pTransitHandler = NULL;

    uint16_t index = 0;
    bool_t isTransOk = FALSE;
    bool_t isEntry = FALSE;

    if (pStateMachine == NULL)
    {
        return FALSE;
    }

    if ((g_FsmCurrState != g_FsmNextState) ||
        (g_FsmStateEvent == FSM_EVENT_RETRY) || (g_FsmStateEvent == FSM_EVENT_TIMEOUT))
    {
        if ( (g_FsmStateEvent == FSM_EVENT_RETRY) || (g_FsmStateEvent == FSM_EVENT_TIMEOUT) )
        {
            // if retry due to timeout / retry, increment retry count
            retry_count = retry_count + 1;

            if ( retry_count > STATE_RETRY_MAX ) {
                g_FsmNextState = FSM_START;
                retry_count = 0;
            }   
        }
#ifdef SIMULATION
        log_info("%s -[%s]-> %s", fsm_get_state_name(g_FsmCurrState), fsm_get_event_name(g_FsmStateEvent),
                 fsm_get_state_name(g_FsmNextState));
#endif
        g_FsmCurrState = g_FsmNextState;
        isEntry = TRUE;
        time_tick_snap = get_tick_count();
        g_FsmStateEvent = FSM_EVENT_NO_CHANGE;
    }

    if ((g_FsmCurrState <= FSM_START) || (g_FsmCurrState >= FSM_END))
    {
        return TRUE;
    }

    if (pStateMachine[g_FsmCurrState].pStateHandler != NULL)
    {
        newEvent = pStateMachine[g_FsmCurrState].pStateHandler(isEntry);
    }
    else
    {
#ifdef SIMULATION
        log_error("Invalid state handler for %s", fsm_get_state_name(g_FsmCurrState));
        log_error("FSM in irrecoverable error state");
#endif
        g_FsmCurrState = g_FsmNextState = FSM_ERROR;
        return FALSE;
    }

    if ((newEvent == FSM_EVENT_NO_CHANGE) &&
        (get_elapsed_time_in_s(time_tick_snap) > pStateMachine[g_FsmCurrState].waitTime))
    {
        newEvent = FSM_EVENT_TIMEOUT;
    }

    if (pStateMachine[g_FsmCurrState].pTransitHandler != NULL)
    {
        for (index = 0; index < pStateMachine[g_FsmCurrState].SizeTransition; index++)
        {
            pTransitHandler = &pStateMachine[g_FsmCurrState].pTransitHandler[index];

            if (pTransitHandler->Event == newEvent)
            {
                isTransOk = pTransitHandler->pOnTransition != NULL ? pTransitHandler->pOnTransition() : TRUE;

                g_FsmNextState = isTransOk ? pTransitHandler->NextState : g_FsmCurrState;

                g_FsmStateEvent = newEvent;
            }
        }

        // if time out event is not handled by transition handler, retry
        if ((newEvent == FSM_EVENT_TIMEOUT) && (g_FsmStateEvent != newEvent))
        {
            g_FsmStateEvent = FSM_EVENT_TIMEOUT;
        }
    }
    else
    {
#ifdef SIMUALTION
        log_error("Invalid transition handler for %s", fsm_get_state_name(g_FsmCurrState));
        log_error("FSM in irrecoverable error state");
#endif
        g_FsmCurrState = g_FsmNextState = FSM_ERROR;
        return FALSE;
    }

    return TRUE;
}
