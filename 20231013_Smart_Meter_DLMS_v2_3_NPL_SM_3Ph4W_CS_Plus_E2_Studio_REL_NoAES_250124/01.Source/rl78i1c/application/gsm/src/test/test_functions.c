#include "test_util.h"

void test_init_ok(void)
{
    static const CommandResponse_t cmd_resp[] = {
        {"AT+CMGF=1", "OK"},
        {"AT+CSQ", "+CSQ:31,99\r\nOK"},
        {"AT+COPS=0", "OK"},
        {"AT", "OK"}
    };

    test_handler_generic(cmd_resp, SIZE_OF_ARRAY(cmd_resp));
}

void test_gprs_init_ok(void)
{
    static const CommandResponse_t cmd_resp[] = {
        {"AT+CGATT=1", "OK"},
        {"AT+CREG?", "OK"},
        {"AT+CGDCONT=1,", "OK"},
        {"AT+CGACT=1,1", "OK"}
    };

    test_handler_generic(cmd_resp, SIZE_OF_ARRAY(cmd_resp));
}

void test_gprs_send_data_ok(void)
{
    static const CommandResponse_t cmd_resp[] = {
        {"AT+QICLOSE=0", "OK"},
        {"AT+QISDE=0", "OK"},
        {"AT+QIOPEN=1,0,", "OK"},
        {"AT+QISEND=0,0", "OK"},
        {"AT+QISEND=0", ">"},
        //{"\r\x1a", "SEND OK\r\n+SM:RELAY=1\r\n<EOM>\r\n"},
    };

    test_handler_generic(cmd_resp, SIZE_OF_ARRAY(cmd_resp));
}

void test_init_error_1(void)
{
    static const CommandResponse_t cmd_resp[] = {
        {"AT+QICLOSE=0", "OK"},
        {"AT+CMGF=1", "OK"},
        {"AT+CSQ", "+CSQ:31,99\r\nOK"},
        {"AT+COPS=0", "+CME ERROR: 100"},
        {"AT", "OK"}
    };

    test_handler_generic(cmd_resp, SIZE_OF_ARRAY(cmd_resp));
}