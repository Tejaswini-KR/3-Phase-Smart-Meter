#include "../fsm.h"
#include "test_functions.h"
#include "test_setup.h"

/// @brief all pass
static TestHandler_t g_TestSet_AllOk[FSM_END] = {
    // GSM_STATE_IDLE
    NULL,

    // GSM_STATE_INIT
    test_init_ok,

    // GSM_STATE_GPRS_INIT
    test_gprs_init_ok,

    // GSM_GPRS_SEND_DATA
    test_gprs_send_data_ok
};

/// @brief init fail at AT+COPS
static TestHandler_t g_TestSet_InitError_1[FSM_END] = {
    // GSM_STATE_IDLE
    NULL,
    // GSM_STATE_INIT
    test_init_error_1,    
    // GSM_STATE_INIT
};

TestHandler_t* get_test_set(void)
{
    return g_TestSet_AllOk;
    // return g_TestSet_InitError_1;
}
