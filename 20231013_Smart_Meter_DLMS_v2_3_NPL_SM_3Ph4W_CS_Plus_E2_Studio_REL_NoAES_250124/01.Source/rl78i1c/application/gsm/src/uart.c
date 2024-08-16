#ifndef SIMULATION
#include "r_cg_macrodriver.h"
#include "r_cg_sau.h"
#endif

#include <stdio.h>
#include <string.h>

#include "gsm_typedef.h"
#include "event_log.h"

#define RX_BUFFER_LEN   200
#define TX_BUFFER_LEN   200

#ifndef SIMULATION
//void Wait_ms(unsigned int Required_Delay);
#endif

extern uint8_t g_gsm_gprs_connect_flag;
extern volatile uint16_t  g_uart0_rx_count;
static char g_RxBuffer[RX_BUFFER_LEN];
static uint16_t g_RxDataLen = 0;

static char g_TxBuffer[TX_BUFFER_LEN + 5];
static uint16_t g_TxDataLen = 0;
static bool_t g_TxComplete = TRUE;

void SendData(const uint8_t *data_buffer, uint16_t data_len, bool_t send_crlf)
{
    if (data_len > TX_BUFFER_LEN) {
        data_len = TX_BUFFER_LEN;
    }
	
    if (data_len) {
#ifndef SIMULATION
		// wait for previous transmission to complete
		while ( g_TxComplete == FALSE ) {
			//Wait_ms(100);
		}
#else
        log_print("=>[%03d] %s", data_len, data_buffer);
#endif
	    memset(g_TxBuffer, 0, TX_BUFFER_LEN);
        memcpy(g_TxBuffer, data_buffer, data_len);

		g_TxDataLen = data_len;
        if (send_crlf == TRUE) {
            memcpy(g_TxBuffer + data_len, "\r", 1);
	        g_TxDataLen += 1;
        }
        
        g_TxBuffer[g_TxDataLen] = 0;
#ifndef SIMULATION
		g_TxComplete = FALSE;
		R_UART0_Send((uint8_t *)g_TxBuffer, g_TxDataLen);
#endif
    }
	
	// clear rx buffer
    memset(g_RxBuffer, 0, RX_BUFFER_LEN);
    g_RxDataLen = 0;      
	
#ifndef SIMULATION
	//R_UART0_Receive((uint8_t *)g_RxBuffer, RX_BUFFER_LEN);
#endif
}

bool_t is_trasmit_complete(void)
{
	return g_TxComplete;
}

void GPRS_SendCompleteCallBack(void)
{
	g_TxComplete = TRUE;
}

uint16_t ReceiveResponse(uint8_t *resp_buffer, uint16_t max_len)
{
    uint16_t data_len = g_RxDataLen > max_len ? max_len : g_RxDataLen;

    if (data_len > 0) 
	{
        memcpy(resp_buffer, g_RxBuffer, data_len);
        resp_buffer[data_len] = 0;
#ifdef SIMULATION
        log_print("<=[%03d] %s", g_RxDataLen, g_RxBuffer);
#endif
    }
    return data_len;
}

void GPRS_ReceiveEndCallback(char rx_data)
{
	if (g_RxDataLen >= RX_BUFFER_LEN) {
		g_RxDataLen = 0;
	}
	if (rx_data > 0 && rx_data < 0x7f) {
		g_RxBuffer[g_RxDataLen++] = rx_data;
	}
}

uint8_t GPRS_IsConnected(void)
{
	return g_gsm_gprs_connect_flag;
}

void uart_init(void)
{
    memset(g_RxBuffer, 0, RX_BUFFER_LEN);
    g_RxDataLen = 0;
    
    memset(g_TxBuffer, 0, TX_BUFFER_LEN);
    g_TxDataLen = 0;
}

#ifdef SIMULATION

void UartRxInt_Mock(const char *mock_response, uint16_t resp_len)
{
    memcpy(g_RxBuffer, mock_response, resp_len);
    memcpy(g_RxBuffer + resp_len, "\r", 1);
    g_RxDataLen = resp_len + 1;
}

uint16_t UartTxInt_Mock(char *mock_cmd, uint16_t max_len)
{
    memcpy(mock_cmd, g_TxBuffer, g_TxDataLen > max_len ? max_len : g_TxDataLen);
    return g_TxDataLen;
}
#endif