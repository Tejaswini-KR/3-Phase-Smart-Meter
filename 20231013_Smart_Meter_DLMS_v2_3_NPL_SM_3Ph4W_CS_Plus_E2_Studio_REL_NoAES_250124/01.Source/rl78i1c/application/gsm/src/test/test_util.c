#include <string.h>

#include "../fsm.h"
#include "../uart.h"
#include "../utils.h"
#include "../event_log.h"

//void UartRxInt_Mock(const char *mock_response, uint16_t resp_len);
//uint16_t UartTxInt_Mock(char *mock_cmd, uint16_t max_len);

#define TEST_TX_CMD_SIZE    100
char testTxCmd[TEST_TX_CMD_SIZE];

void test_handler_generic(const CommandResponse_t *arrCmdResp, uint16_t arrSize)
{
    uint16_t index = 0;

    //UartTxInt_Mock(testTxCmd, TEST_TX_CMD_SIZE);

    for (index = 0; index < arrSize; index++)
    {
        if (strncmp(testTxCmd, CONST_STR_AND_LEN(arrCmdResp[index].pCommandStr)) == 0)
        {
            //UartRxInt_Mock(CONST_STR_AND_LEN(arrCmdResp[index].pResponseStr));
            break;
        }
    }
}