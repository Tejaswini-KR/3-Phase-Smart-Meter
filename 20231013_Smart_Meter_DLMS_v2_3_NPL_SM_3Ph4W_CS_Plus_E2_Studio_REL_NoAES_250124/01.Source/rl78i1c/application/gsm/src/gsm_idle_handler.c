#include <string.h>

#include "fsm.h"
#include "event_log.h"

eFsmEvent gsm_idle_state(bool_t isEntry)
{
#ifdef SIMULATION
    log_debug(__FUNCTION__);
#endif
    return FSM_EVENT_ACK;
}
