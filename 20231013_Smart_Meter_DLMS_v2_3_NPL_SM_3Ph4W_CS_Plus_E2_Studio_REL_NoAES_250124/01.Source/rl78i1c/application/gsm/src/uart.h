#ifndef __UART_H__
#define __UART_H__

#include "gsm_typedef.h"

void SendData(const uint8_t *data_buffer, uint16_t data_len, bool_t send_crlf);
uint16_t ReceiveResponse(uint8_t *resp_buffer, uint16_t max_len);

#endif
