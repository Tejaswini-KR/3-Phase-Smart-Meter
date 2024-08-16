#include "../fsm.h"
#include "test_setup.h"

void test_process(void)
{
    eFsmState curState = fsm_get_state();

    TestHandler_t *test_data_set = get_test_set();
    
    if( (curState > FSM_START) && (curState < FSM_END) ) {
        if ( test_data_set[curState] != NULL ) {
            test_data_set[curState]();
        }
    }
}