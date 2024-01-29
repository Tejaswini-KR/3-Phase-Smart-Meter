/******************************************************************************
* DISCLAIMER

* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized.

* This software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.

* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES 
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, 
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY 
* DISCLAIMED.

* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES 
* FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS 
* AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

* Renesas reserves the right, without notice, to make changes to this 
* software and to discontinue the availability of this software.  
* By using this software, you agree to the additional terms and 
* conditions found by accessing the following link:
* http://www.renesas.com/disclaimer
******************************************************************************/
/* Copyright (C) 2016 Renesas Electronics Corporation. All rights reserved.  */
/******************************************************************************	
* File Name    : r_dlms_udp_wrapper_nuratech_wisun.c
* Version      : 1.00
* Device(s)    : R5F564MLCxDC
* Tool-Chain   : CCRX
* H/W Platform : RX64M RSK+
* Description  : UDP wrapper layer of DLMS
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 11.05.2016 
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_sau.h"
#include "r_cg_wdt.h"

#include "wrp_app_mcu.h"
#include "typedef.h"
#include "wrp_app_uart.h"
#include "r_dlms_config.h"
#include "r_dlms_udp_wrapper.h"
#include "r_dlms_udp_wrapper_interface.h"
#include "r_dlms_com_wrapper_config.h"
#include <string.h>
#include <stdio.h>              /* Standard IO */
#include <stdarg.h>             /* Variables argument */

#if defined(SUPPORT_UDP_PROFILE) && (SUPPORT_UDP_PROFILE == TRUE) && (UDP_MODE_SELECTION == UDP_MODE_NURATECH_WISUN_MODULE)

/******************************************************************************
Macro definitions
******************************************************************************/
#define		UDP_EUI64_ADDRESS_SIZE			(8)

#define		WISUN_UDP_IP_ADDR_SIZE			(16)
#define		WISUN_CMD_END					"\x0D\x0A"
#define		WISUN_CMD_VAR_ARG_MAX_LENGTH	64
#define		WISUN_CMD_RESPONSE_MIN_LENGTH	64
#define		WISUN_CMD_RESPONSE_MAX_LENGTH	64
#define		WISUN_CMD_RESPONSE_TIMEOUT		200
#define		WISUN_CMD_MODE_SEND				0
#define		WISUN_CMD_MODE_RECEIVE			1
#define		WISUN_DLMS_UDP_PORT				4059
#define		WISUN_DATA_CMD_BUFFER_SIZE		(5 + WISUN_UDP_IP_ADDR_SIZE + 2 + 1)
#define		WISUN_DATA_RECEIVER_INTERFRAME	100
#define		WISUN_UDP_PORT_CONFIG_GET		0
#define		WISUN_UDP_PORT_CONFIG_SET		1
#define		WISUN_UDP_PORT_CONFIG_NOP		0xFF

#define		WISUN_DATA_CMD_STAGE_START		0
#define		WISUN_DATA_CMD_STAGE_NODE_IP6	1
#define		WISUN_DATA_CMD_STAGE_LENGTH		2
#define		WISUN_DATA_CMD_STAGE_DATA		3

#define     WISUN_STATUS_CODE_APP_OPERATE   '1'
#define     WISUN_STATUS_CODE_APP_INIT      '2'
#define     WISUN_STATUS_CODE_APP_CONN      '3'
#define     WISUN_STATUS_CODE_APP_DISC      '4'

#define		WISUN_RESET_DATA_RECEIVER()		{					\
	g_udp_device_data_cmd_stage = WISUN_DATA_CMD_STAGE_START;	\
	g_udp_device_data_cmd_length = 0;							\
	g_udp_device_data_count = 0;								\
	g_udp_device_data_dispatch_count = 0;						\
}

#define		WISUN_RESET_INTERFRAME_TIMEOUT()	{											\
	g_udp_device_interframe_timeout.count = g_udp_device_interframe_timeout.initial;		\
	g_udp_device_interframe_timeout.enable = TRUE;											\
}

#define     WISUN_WAIT_MODULE_STARTUP()         {               \
    for (count = 0; count < 100; count++)                       \
    {                                                           \
        MCU_Delay(10000);                                       \
        R_WDT_Restart();                                        \
    }                                                           \
}
    

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef struct
{
	uint16_t	initial;
	uint16_t	count;
	uint16_t	enable;
} WiSunTimeoutChannel;

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/******************************************************************************
Private global variables and functions
******************************************************************************/
volatile uint8_t	g_udp_device_send_end = TRUE;                   /* Send end */
volatile uint8_t	g_udp_device_mode = WISUN_CMD_MODE_SEND;        /* 0: Sending mode, 1: receiving mode */
uint8_t				*gp_udp_device_cmd_response_buffer = NULL;      /* Buffer to store the UDP module cmd response */
volatile uint16_t	g_udp_device_cmd_response_count = 0;            /* Counter for cmd response buffer */
volatile uint16_t	g_udp_device_cmd_response_length = 0;           /* Counter for cmd response length */
volatile uint8_t	g_udp_device_debug_mode_appear;					/* Indicates that debug mode of wisun module appear during binary data mode */
volatile uint8_t	g_udp_device_hot_plug_appear;					/* Indicates that hot plug happen on Wrapper port */
UdpPortConfig		*g_udp_device_port_config_ptr;					/* UDP port config pointer for auto update event on hot plug */
uint8_t				g_udp_device_port_config_direction;				/* UDP port config direction (GET or SET)*/
const uint8_t		g_udp_device_status_code_preample[] = "CD:0";   /* Code buffer to check if the module restarted (plug in) */
volatile uint8_t	g_udp_device_status_code_count;                 /* Counter to check the code */

/* Vars for WiSun Receive Data */
uint8_t				g_udp_device_data_cmd_buffer[WISUN_DATA_CMD_BUFFER_SIZE];
volatile uint8_t	g_udp_device_data_cmd_stage;
volatile uint16_t	g_udp_device_data_cmd_length;
volatile uint16_t	g_udp_device_data_count;
volatile uint16_t	g_udp_device_data_dispatch_count;

/* IpAddress instance for WiSun module */
volatile uint8_t	g_udp_device_local_ip_addr_buffer[WISUN_UDP_IP_ADDR_SIZE];
volatile IpAddress	g_udp_device_local_ip_addr;
volatile IpAddress	g_udp_device_remote_ip_addr;	/* Use (g_udp_device_data_cmd_buffer + 5) as IpAddress buffer*/

/* WiSun interframe timeout use to reset receiver to initial */
volatile WiSunTimeoutChannel	g_udp_device_interframe_timeout;

/******************************************************************************
* Function Name : R_UDP_DEVICE_Printf
* Interface     : static void R_UDP_DEVICE_Printf(char *format, ...)
* Description   : 
* Arguments     : char * format:
* Function Calls: 
* Return Value  : static void
******************************************************************************/
static void R_UDP_DEVICE_Printf(char *format, ...)
{
    uint8_t     buffer[WISUN_CMD_VAR_ARG_MAX_LENGTH];  /* max bytes */
    va_list     arg = NULL;
    uint16_t    usndone;
    
    #ifdef __CA78K0R__
    /* Parse the argument list, print to buffer string */
    va_starttop(arg, format);
    #endif
    
    #ifdef __CCRL__
    va_start(arg, format);
    #endif
    
    /* Format the string */
    usndone = vsprintf((char *)buffer, (const char *)format, arg);
    buffer[WISUN_CMD_VAR_ARG_MAX_LENGTH-1] = 0;    /* Terminal string to prevent un-expected error */

    g_udp_device_send_end = FALSE;
    WRP_UART0_SendData(buffer, usndone);
    while (g_udp_device_send_end == FALSE);
    
    va_end(arg);
}

/******************************************************************************
* Function Name : R_UDP_DEVICE_SendBuffer
* Interface     : static void R_UDP_DEVICE_SendBuffer(uint8_t *buffer, uint16_t length)
* Description   : 
* Arguments     : uint8_t * buffer:
*               : uint16_t length :
* Function Calls: 
* Return Value  : static void
******************************************************************************/
static void R_UDP_DEVICE_SendBuffer(uint8_t *buffer, uint16_t length)
{
	g_udp_device_send_end = FALSE;
	WRP_UART0_SendData(buffer, length);
	while (g_udp_device_send_end == FALSE);
}

/******************************************************************************
* Function Name : R_UDP_DEVICE_PrepareCmdReply
* Interface     : static void R_UDP_DEVICE_PrepareCmdReply(uint8_t *buffer, uint16_t length)
* Description   : 
* Arguments     : uint8_t * buffer:
*               : uint16_t length :
* Function Calls: 
* Return Value  : static void
******************************************************************************/
static void R_UDP_DEVICE_PrepareCmdReply(uint8_t *buffer, uint16_t length)
{
    memset(buffer, 0, length);
    gp_udp_device_cmd_response_buffer = buffer;
    g_udp_device_cmd_response_length = length;
    g_udp_device_cmd_response_count = 0;
}

/******************************************************************************
* Function Name : R_UDP_DEVICE_WaitReply
* Interface     : static uint16_t R_UDP_DEVICE_WaitReply(uint16_t timeout, char *format, ...)
* Description   : 
* Arguments     : uint16_t timeout:
*               : char * format   :
* Function Calls: 
* Return Value  : static uint16_t
******************************************************************************/
static uint16_t R_UDP_DEVICE_WaitReply(uint16_t timeout, char *format, ...)
{
    uint8_t     expected_str[WISUN_CMD_VAR_ARG_MAX_LENGTH];  /* max bytes */
    va_list     arg = NULL;
    uint16_t    usndone;
    
    #ifdef __CA78K0R__
    /* Parse the argument list, print to buffer string */
    va_starttop(arg, format);
    #endif
    
    #ifdef __CCRL__
    va_start(arg, format);
    #endif
    
    /* Format the string */
    usndone = vsprintf((char *)expected_str, (const char *)format, arg);
    expected_str[WISUN_CMD_VAR_ARG_MAX_LENGTH-1] = 0;    /* Terminal string to prevent un-expected error */
    va_end(arg);
    
    /* Wait for cmd reply */
    while (timeout > 0)
    {
        if (g_udp_device_cmd_response_count >= usndone &&
            strstr((const char *)gp_udp_device_cmd_response_buffer, (const char *)expected_str) != NULL)
		{
            break;
        }
        
		if (timeout >= 5) {
			timeout -= 5;
		}
		else {
			timeout = 0;
		}
        MCU_Delay(5000);
    }
    
    return timeout;
}

/******************************************************************************
* Function Name : R_UDP_DEVICE_WaitReply1String
* Interface     : static uint16_t R_UDP_DEVICE_WaitReply1String(
*               :     uint16_t timeout     ,
*               :     uint8_t * str        ,
*               : );
* Description   :
* Arguments     : uint16_t timeout     :
*               : uint8_t * str        :
* Function Calls:
* Return Value  : static uint16_t
******************************************************************************/
static uint16_t R_UDP_DEVICE_WaitReply1String(uint16_t timeout, uint8_t *str)
{
    /* Wait for cmd reply */
    while (timeout > 0)
    {
        if (g_udp_device_cmd_response_count >= strlen((const char *)str) &&
            strstr((const char *)gp_udp_device_cmd_response_buffer, (const char *)str) != NULL)
        {
            break;
        }
        
        if (timeout >= 5) {
            timeout -= 5;
        }
        else {
            timeout = 0;
        }
        MCU_Delay(5000);

        R_WDT_Restart();
    }

    return timeout;
}

/******************************************************************************
* Function Name : R_UDP_DEVICE_WaitReply2String
* Interface     : static uint16_t R_UDP_DEVICE_WaitReply2String(
*               :     uint16_t timeout     ,
*               :     uint8_t * str0       ,
*               :     uint8_t * str1       ,
*               :     uint8_t * found_index,
*               : );
* Description   : 
* Arguments     : uint16_t timeout     :
*               : uint8_t * str0       :
*               : uint8_t * str1       :
*               : uint8_t * found_index:
* Function Calls: 
* Return Value  : static uint16_t
******************************************************************************/
static uint16_t R_UDP_DEVICE_WaitReply2String(
    uint16_t timeout,
    uint8_t *str0,
    uint8_t *str1,
    uint8_t *found_index
)
{
    if (found_index == NULL) {
        return 0;
    }
    
	/* Wait for cmd reply */
	while (timeout > 0)
	{
		if (g_udp_device_cmd_response_count >= strlen((const char *)str0) &&
			strstr((const char *)gp_udp_device_cmd_response_buffer, (const char *)str0) != NULL)
        {
            *found_index = 0;
			break;
		}

        if (g_udp_device_cmd_response_count >= strlen((const char *)str1) &&
			strstr((const char *)gp_udp_device_cmd_response_buffer, (const char *)str1) != NULL)
		{
            *found_index = 1;
			break;
		}
        
		if (timeout >= 5) {
			timeout -= 5;
		}
		else {
			timeout = 0;
		}
		MCU_Delay(5000);
        
        R_WDT_Restart();
	}

	return timeout;
}

/******************************************************************************
* Function Name : R_UDP_DEVICE_Init
* Interface     : void R_UDP_DEVICE_Init(void)
* Description   : Initial PHY Driver
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_UDP_DEVICE_Init(UdpChannel udp_channel)
{
    if (udp_channel == 0)
	{
        /* NOTE: the process below alter the UART line and break the auto start of RF module */
        WRP_UART0_Init();
        WRP_UART0_SetBaudRate(WRP_UART_BAUD_RATE_9600);
        WRP_UART0_ConfigHDLCProtocol();
		WRP_UART0_Start();

        g_udp_device_send_end = TRUE;
		g_udp_device_mode = WISUN_CMD_MODE_SEND;

        gp_udp_device_cmd_response_buffer = NULL;
        g_udp_device_cmd_response_length = 0;
        g_udp_device_cmd_response_count = 0;
		g_udp_device_debug_mode_appear = FALSE;
		g_udp_device_hot_plug_appear = FALSE;
		g_udp_device_port_config_ptr = NULL;
		g_udp_device_port_config_direction = WISUN_UDP_PORT_CONFIG_NOP;
        g_udp_device_status_code_count = 0;

		memset(g_udp_device_data_cmd_buffer, 0, WISUN_DATA_CMD_BUFFER_SIZE);
		WISUN_RESET_DATA_RECEIVER();

		/* Initial local ip address of WiSun module & set null for remote address */
		memset((void *)g_udp_device_local_ip_addr_buffer, 0, WISUN_UDP_IP_ADDR_SIZE);
		g_udp_device_local_ip_addr.p_addr = (uint8_t *)g_udp_device_local_ip_addr_buffer;
		g_udp_device_local_ip_addr.size = WISUN_UDP_IP_ADDR_SIZE;
		g_udp_device_remote_ip_addr.p_addr = NULL;
		g_udp_device_remote_ip_addr.size = 0;

		g_udp_device_interframe_timeout.enable = FALSE;
		g_udp_device_interframe_timeout.count = 0;
		g_udp_device_interframe_timeout.initial = WISUN_DATA_RECEIVER_INTERFRAME;

        /* 200ms delay for init of RF device */
        MCU_Delay(50000);
        MCU_Delay(50000);
        MCU_Delay(50000);
        MCU_Delay(50000);
    }
}

/******************************************************************************
* Function Name : R_UDP_DEVICE_Start
* Interface     : void R_UDP_DEVICE_Start(void)
* Description   : Start PHY Driver
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_UDP_DEVICE_Start(UdpChannel udp_channel)
{
	uint8_t reply_buffer[WISUN_CMD_RESPONSE_MIN_LENGTH];
    uint16_t timeout_remain;
    uint8_t  count;
    
    if (udp_channel == 0) {

        /* Cmd Sending mode */
		g_udp_device_mode = WISUN_CMD_MODE_SEND;

		/* Enter to discard all input chars */
		R_UDP_DEVICE_PrepareCmdReply(reply_buffer, WISUN_CMD_RESPONSE_MIN_LENGTH);
        R_UDP_DEVICE_SendBuffer((uint8_t *)WISUN_CMD_END, strlen(WISUN_CMD_END));
		timeout_remain = R_UDP_DEVICE_WaitReply1String(WISUN_CMD_RESPONSE_TIMEOUT, (uint8_t *)"\n");
		if (timeout_remain == 0) {
			/* No reply from module */
		}

        /* Cmd Receiving mode */
		g_udp_device_mode = WISUN_CMD_MODE_RECEIVE;

		/* Reset vars of receive mode */
		WISUN_RESET_DATA_RECEIVER();
    }
}

/******************************************************************************
* Function Name : R_UDP_DEVICE_Stop
* Interface     : void R_UDP_DEVICE_Stop(void)
* Description   : Stop PHY Driver
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_UDP_DEVICE_Stop(UdpChannel udp_channel)
{
    if (udp_channel == 0) {
		/* Do nothing */
    }
}

/******************************************************************************
* Function Name : R_UDP_DEVICE_PollingProcess
* Interface     : void R_UDP_DEVICE_PollingProcess(void)
* Description   : Polling process of UDP device
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_UDP_DEVICE_PollingProcess(UdpChannel udp_channel)
{
	if (udp_channel == 0) {
		
		if (g_udp_device_hot_plug_appear == TRUE) {
			g_udp_device_hot_plug_appear = FALSE;
			if (g_udp_device_port_config_ptr != NULL) {
				if (g_udp_device_port_config_direction == WISUN_UDP_PORT_CONFIG_GET) {
					R_UDP_DEVICE_GetConfig(udp_channel, g_udp_device_port_config_ptr);
				}
				else if (g_udp_device_port_config_direction == WISUN_UDP_PORT_CONFIG_SET) {
					R_UDP_DEVICE_SetConfig(udp_channel, g_udp_device_port_config_ptr);
				}
				else {
					/* Do nothing */
				}
			}
		}
	}
}

/******************************************************************************
* Function Name : R_UDP_DEVICE_TwoHexCharsToByte
* Interface     : static uint8_t R_UDP_DEVICE_TwoHexCharsToByte(uint8_t *two_hex_chars)
* Description   : 
* Arguments     : uint8_t * two_hex_chars:
* Function Calls: 
* Return Value  : static uint8_t
******************************************************************************/
static uint8_t R_UDP_DEVICE_TwoHexCharsToByte(uint8_t *two_hex_chars)
{
	uint8_t result = 0;

	uint8_t count = 0;
	uint8_t u8;

	if (two_hex_chars == NULL) {
		return 0;
	}

	while (count < 2)
	{
		u8 = *two_hex_chars++;
		result <<= 4;

		if (u8 >= 'a') {
			result += 10 + (u8 - 'a');
		}
		else if (u8 >= 'A') {
			result += 10 + (u8 - 'A');
		}
		else {
			result += u8 - '0';
		}

		count++;
	}

	return result;
}

/******************************************************************************
* Function Name : R_UDP_DEVICE_ByteToHexStr
* Interface     : static void R_UDP_DEVICE_ByteToHexStr(uint8_t *buffer, uint8_t byte)
* Description   : 
* Arguments     : uint8_t * buffer:
*               : uint8_t byte    :
* Function Calls: 
* Return Value  : static void
******************************************************************************/
static void R_UDP_DEVICE_ByteToHexStr(uint8_t *buffer, uint8_t byte)
{
	uint8_t count = 0;
	uint8_t u8;

	if (buffer == NULL) {
		return;
	}

	while (count < 2)
	{
		u8 = byte >> ((1 - count) * 4);
		u8 &= 0x0F;

		if (u8 >= 10) {
			*buffer++ = (u8 - 10 + 'A');
		}
		else {
			*buffer++ = u8 + '0';
		}

		count++;
	}
}

/******************************************************************************
* Function Name : R_UDP_DEVICE_GetConfig
* Interface     : uint8_t R_UDP_DEVICE_GetConfig(
*               :     UdpChannel udp_channel ,
*               :     UdpPortConfig* p_config,
*               : );
* Description   :
* Arguments     : UdpChannel udp_channel :
*               : UdpPortConfig* p_config:
* Function Calls:
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_UDP_DEVICE_GetConfig(UdpChannel udp_channel, UdpPortConfig* p_config)
{
	uint8_t reply_buffer[WISUN_CMD_RESPONSE_MAX_LENGTH];
	uint16_t timeout_remain;
	uint8_t  *p_u8;
	uint8_t  *p_ip6;
	uint16_t count;

	uint8_t  result = TRUE;

	if (p_config == NULL) {
		return 1;
	}

	/* Get config of UDP module, port and ip */
	if (udp_channel == 0) {

        WISUN_WAIT_MODULE_STARTUP();

		/* Store the pointer for hotplug if happen */
		g_udp_device_port_config_ptr = p_config;
		g_udp_device_port_config_direction = WISUN_UDP_PORT_CONFIG_GET;

		/* DLMS UDP Port (Blue book 12.1, page 218) */
		p_config->local_udp_port = 4059;

		/* Cmd Sending mode */
		g_udp_device_mode = WISUN_CMD_MODE_SEND;

		/* Enter to discard all input chars */
		if (result == TRUE) {
			R_UDP_DEVICE_PrepareCmdReply(reply_buffer, WISUN_CMD_RESPONSE_MAX_LENGTH);
			R_UDP_DEVICE_SendBuffer((uint8_t *)WISUN_CMD_END, strlen(WISUN_CMD_END));
			timeout_remain = R_UDP_DEVICE_WaitReply1String(WISUN_CMD_RESPONSE_TIMEOUT, (uint8_t *)"\n");
			if (timeout_remain == 0) {
				result = FALSE;
			}
		}

		/* Get environments */
		if (result == TRUE) {

			R_UDP_DEVICE_PrepareCmdReply(reply_buffer, WISUN_CMD_RESPONSE_MAX_LENGTH);
			R_UDP_DEVICE_SendBuffer((uint8_t *)("app euid" WISUN_CMD_END), strlen("app euid" WISUN_CMD_END));
			timeout_remain = R_UDP_DEVICE_WaitReply1String(WISUN_CMD_RESPONSE_TIMEOUT, (uint8_t *)"OK\n");
			if (timeout_remain == 0) {
				result = FALSE;
			}
			else {
				/*
				 * First 8 bytes of WiSun local ip address is copied from the config (prefix)
				 * Last 8 bytes is the EUID setup on WiSun module
				 */
				memcpy((void *)g_udp_device_local_ip_addr_buffer, p_config->local_ip_address->p_addr, 8);
				p_ip6 = ((uint8_t *)g_udp_device_local_ip_addr_buffer + 8);
                /* Skip the first 0x0a in buffer */
                p_u8 = (reply_buffer + 1);
                if (strlen((const char *)p_u8) >= 16)
                {
					for (count = 0; count < (WISUN_UDP_IP_ADDR_SIZE / 2); count++) {
                        *p_ip6++ = R_UDP_DEVICE_TwoHexCharsToByte(p_u8);
                        p_u8 += 2;
                    }
                }
				/* Point the local ip address into IpAddress instance on this WiSun module */
				g_udp_device_local_ip_addr.p_addr = (uint8_t *)g_udp_device_local_ip_addr_buffer;
				g_udp_device_local_ip_addr.size = WISUN_UDP_IP_ADDR_SIZE;
				p_config->local_ip_address = (IpAddressPtr)&g_udp_device_local_ip_addr;
			}
		}

		/* Cmd Receiving mode */
		g_udp_device_mode = WISUN_CMD_MODE_RECEIVE;
	}

	if (result == FALSE) {
		return 2;
	}

	return 0;
}

/******************************************************************************
* Function Name : R_UDP_DEVICE_SetConfig
* Interface     : uint8_t R_UDP_DEVICE_SetConfig(
*               :     UdpChannel udp_channel ,
*               :     UdpPortConfig* p_config,
*               : );
* Description   :
* Arguments     : UdpChannel udp_channel :
*               : UdpPortConfig* p_config:
* Function Calls:
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_UDP_DEVICE_SetConfig(UdpChannel udp_channel, UdpPortConfig* p_config)
{
	uint8_t reply_buffer[WISUN_CMD_RESPONSE_MAX_LENGTH];
	uint8_t env_buffer[128];
	uint8_t  *p_u8 = env_buffer;
	uint16_t timeout_remain;
	uint16_t count;

	uint8_t  result = TRUE;

	if (p_config == NULL) {
		return 1;
	}

	/* Set config of UDP module, port and ip */
	if (udp_channel == 0) {

		/* Store the pointer for hotplug if happen */
		g_udp_device_port_config_ptr = p_config;
		g_udp_device_port_config_direction = WISUN_UDP_PORT_CONFIG_SET;

		/* Cmd Sending mode */
		g_udp_device_mode = WISUN_CMD_MODE_SEND;

		/* Enter to discard all input chars */
		if (result == TRUE) {
			R_UDP_DEVICE_PrepareCmdReply(reply_buffer, WISUN_CMD_RESPONSE_MAX_LENGTH);
			R_UDP_DEVICE_SendBuffer((uint8_t *)WISUN_CMD_END, strlen(WISUN_CMD_END));
			timeout_remain = R_UDP_DEVICE_WaitReply1String(WISUN_CMD_RESPONSE_TIMEOUT, (uint8_t *)"\n");
			if (timeout_remain == 0) {
				result = FALSE;
			}
		}

		/* Set environments */
		if (result == TRUE) {
            
            WISUN_WAIT_MODULE_STARTUP();
            
			/* Set env cmd */
			memcpy(p_u8, "set addr ", 9);
			p_u8 += 9;

			/* Prefix & EUI64 */
			for (count = 0; count < UDP_EUI64_ADDRESS_SIZE; count++) {
				R_UDP_DEVICE_ByteToHexStr(p_u8, *( p_config->local_ip_address->p_addr + 8 + count ));
				p_u8 += 2;
			}

			/* Backup ip address to local buffer */
			memcpy((void *)g_udp_device_local_ip_addr_buffer, p_config->local_ip_address->p_addr, 16);

			/* \n */
			memcpy(p_u8, WISUN_CMD_END, 2);
			p_u8 += 2;

			/* Terminate string */
			*p_u8++ = 0;

			R_UDP_DEVICE_PrepareCmdReply(reply_buffer, WISUN_CMD_RESPONSE_MAX_LENGTH);
			R_UDP_DEVICE_SendBuffer((uint8_t *)env_buffer, (uint16_t)(p_u8 - env_buffer));
			timeout_remain = R_UDP_DEVICE_WaitReply1String(WISUN_CMD_RESPONSE_TIMEOUT, (uint8_t *)"OK\n");
			if (timeout_remain == 0) {
				result = FALSE;
			}
            
    		R_UDP_DEVICE_PrepareCmdReply(reply_buffer, WISUN_CMD_RESPONSE_MIN_LENGTH);
    		R_UDP_DEVICE_SendBuffer((uint8_t *)WISUN_CMD_END, 2);
            R_UDP_DEVICE_WaitReply1String(WISUN_CMD_RESPONSE_TIMEOUT, (uint8_t *)"\n");

            R_UDP_DEVICE_PrepareCmdReply(reply_buffer, WISUN_CMD_RESPONSE_MIN_LENGTH);
            R_UDP_DEVICE_SendBuffer((uint8_t *)("save" WISUN_CMD_END), strlen("save" WISUN_CMD_END));
            timeout_remain = R_UDP_DEVICE_WaitReply1String(WISUN_CMD_RESPONSE_TIMEOUT, (uint8_t *)"OK\n");
            if (timeout_remain == 0) {
                result = FALSE;
            }

		}

		/* Cmd Receiving mode */
		g_udp_device_mode = WISUN_CMD_MODE_RECEIVE;
	}

	if (result == FALSE) {
		return 2;
	}

	return 0;
}

/******************************************************************************
* Function Name : R_UDP_DEVICE_SendData
* Interface     : uint8_t R_UDP_DEVICE_SendData(uint8_t *data, uint16_t length)
* Description   : PHY send data
* Arguments     : uint8_t * data : Data buffer to be sent
*               : uint16_t length: Length of buffer
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_UDP_DEVICE_SendData(UdpChannel udp_channel, UdpPort remote_udp_port, IpAddressPtr remote_ip_address, uint8_t *data, uint16_t length)
{
	/* WiSun buffer to store reply cmd */
	uint8_t  reply_buffer[WISUN_CMD_RESPONSE_MIN_LENGTH];

	/* WiSun buffer to store !send length node_id/node_ip data_bytes */
	uint8_t	 cmd_buffer[5 + 2 + WISUN_UDP_IP_ADDR_SIZE];
	uint8_t  *p_cmd = cmd_buffer;
	uint16_t cmd_length;

	/* Bluebook 12.1 page 218 */
	if (remote_udp_port != WISUN_DLMS_UDP_PORT || data == NULL || length == 0) {
		return 1;	/* Params incorrect */
	}

    if (udp_channel == 0) {
        
		/*
		 * Prepare the WiSun !send cmd
		 */

		/* !send */
		memcpy(p_cmd, "!send", 5);
		p_cmd += 5;

		/* length */
		*p_cmd++ = (uint8_t)length;
		*p_cmd++ = (uint8_t)((length & 0x7F00) >> 8);

		/* node_ip6 */
		if (remote_ip_address->size != WISUN_UDP_IP_ADDR_SIZE) {
			return 2;	/* remote ip address not suitable */
		}
		memcpy(p_cmd, remote_ip_address->p_addr, remote_ip_address->size);
		p_cmd += remote_ip_address->size;

		/* data_bytes */
		//memcpy(p_cmd, data, length);
		//p_cmd += length;

		cmd_length = (uint16_t)(p_cmd - cmd_buffer);

        /* Sending mode */
		g_udp_device_mode = WISUN_CMD_MODE_SEND;
        
		/* Enter to discard all input chars */
		R_UDP_DEVICE_PrepareCmdReply(reply_buffer, WISUN_CMD_RESPONSE_MIN_LENGTH);
		R_UDP_DEVICE_SendBuffer((uint8_t *)WISUN_CMD_END, 2);
        R_UDP_DEVICE_WaitReply1String(WISUN_CMD_RESPONSE_TIMEOUT, (uint8_t *)"\n");
		
		R_UDP_DEVICE_SendBuffer((uint8_t *)cmd_buffer, cmd_length);
        R_UDP_DEVICE_SendBuffer((uint8_t *)data, length);
		
        /* Receiving mode */
		WISUN_RESET_DATA_RECEIVER();
		g_udp_device_mode = WISUN_CMD_MODE_RECEIVE;

        R_UDP_DeviceSendEnd(0);

    }

	return 0;
}

/******************************************************************************
* Function Name : R_UDP_WRP_UartPhyReceiveData
* Interface     : void R_UDP_WRP_UartPhyReceiveData(UdpChannel channel, uint8_t received_byte)
* Description   : 
* Arguments     : UdpChannel channel   :
*               : uint8_t received_byte:
* Function Calls: 
* Return Value  : void
******************************************************************************/
void R_UDP_WRP_UartPhyReceiveData(UdpChannel channel, uint8_t received_byte)
{
    /* Wait command reply from RF module */
	if (g_udp_device_mode == WISUN_CMD_MODE_SEND)
	{
        if (gp_udp_device_cmd_response_buffer != NULL &&
            g_udp_device_cmd_response_count < g_udp_device_cmd_response_length) {
            gp_udp_device_cmd_response_buffer[g_udp_device_cmd_response_count++] = received_byte;
        }
    }
    /*
	 * Receive & decode the !data node_ip6 length data_bytes
	 * Bring data to upper layer on receiving mode
	 */
	else if (g_udp_device_mode == WISUN_CMD_MODE_RECEIVE) {

		WISUN_RESET_INTERFRAME_TIMEOUT();

		if (g_udp_device_data_count < WISUN_DATA_CMD_BUFFER_SIZE) {
			g_udp_device_data_cmd_buffer[g_udp_device_data_count++] = received_byte;
		}

        if (g_udp_device_status_code_count < (sizeof(g_udp_device_status_code_preample) - 1))
        {
            if (received_byte == g_udp_device_status_code_preample[g_udp_device_status_code_count])
            {
                g_udp_device_status_code_count++;
            }
            else if (g_udp_device_status_code_count != 0)
            {
                g_udp_device_status_code_count = 0;
            }
        }
        else
        {
            if (received_byte == WISUN_STATUS_CODE_APP_INIT)
            {
                g_udp_device_hot_plug_appear = TRUE;
            }
            else if (received_byte == WISUN_STATUS_CODE_APP_CONN)
            {

            }
            else if (received_byte == WISUN_STATUS_CODE_APP_DISC)
            {

            }
            g_udp_device_status_code_count = 0;
        }

		if (g_udp_device_data_cmd_stage == WISUN_DATA_CMD_STAGE_START) {
			if (g_udp_device_data_count >= 5) {
				if (memcmp(g_udp_device_data_cmd_buffer, "!data", 5) == 0) {
					g_udp_device_data_cmd_stage = WISUN_DATA_CMD_STAGE_NODE_IP6;
				}
				else
				{
					WISUN_RESET_DATA_RECEIVER();
				}
			}
		}
		else if (g_udp_device_data_cmd_stage == WISUN_DATA_CMD_STAGE_NODE_IP6) {
			if (g_udp_device_data_count >= (5 + WISUN_UDP_IP_ADDR_SIZE)) {
				g_udp_device_data_cmd_stage = WISUN_DATA_CMD_STAGE_LENGTH;
			}
		}
		else if (g_udp_device_data_cmd_stage == WISUN_DATA_CMD_STAGE_LENGTH) {
			if (g_udp_device_data_count >= (5 + WISUN_UDP_IP_ADDR_SIZE + 2)) {
				g_udp_device_data_cmd_length = g_udp_device_data_cmd_buffer[g_udp_device_data_count - 2];
				g_udp_device_data_cmd_length |= ((uint16_t)g_udp_device_data_cmd_buffer[g_udp_device_data_count - 1] << 8);
				g_udp_device_data_dispatch_count = 0;
				g_udp_device_data_cmd_stage = WISUN_DATA_CMD_STAGE_DATA;
			}
		}
		else if (g_udp_device_data_cmd_stage == WISUN_DATA_CMD_STAGE_DATA) {
			if (g_udp_device_data_dispatch_count < g_udp_device_data_cmd_length) {
				g_udp_device_remote_ip_addr.p_addr = g_udp_device_data_cmd_buffer + 5;
				g_udp_device_remote_ip_addr.size = WISUN_UDP_IP_ADDR_SIZE;
				R_UDP_DeviceReceiveEnd(0, WISUN_DLMS_UDP_PORT, (IpAddressPtr)&g_udp_device_remote_ip_addr, &received_byte, 1);
				g_udp_device_data_dispatch_count++;
			}
			else {
				WISUN_RESET_DATA_RECEIVER();
			}
		}
		else {
			WISUN_RESET_DATA_RECEIVER();
		}
    }
}

/******************************************************************************
* Function Name : R_UDP_WRP_UartPhySendEnd
* Interface     : void R_UDP_WRP_UartPhySendEnd(UdpChannel channel)
* Description   : 
* Arguments     : UdpChannel channel:
* Function Calls: 
* Return Value  : void
******************************************************************************/
void R_UDP_WRP_UartPhySendEnd(UdpChannel channel)
{
    if (channel == 0) {
        g_udp_device_send_end = TRUE;
    }
}

/******************************************************************************
* Function Name : R_UDP_DEVICE_WiSunReceiverInterframeTimeoutCallback
* Interface     : void R_UDP_DEVICE_WiSunReceiverInterframeTimeoutCallback(void)
* Description   : 
* Arguments     : None:
* Function Calls: 
* Return Value  : None
******************************************************************************/
void R_UDP_DEVICE_WiSunReceiverInterframeTimeoutCallback(void)
{
	WISUN_RESET_DATA_RECEIVER();
}

/******************************************************************************
* Function Name : R_UDP_DEVICE_WiSunReceiverTimeoutMilisecond
* Interface     : void R_UDP_DEVICE_WiSunReceiverTimeoutMilisecond(void)
* Description   : 
* Arguments     : None:
* Function Calls: 
* Return Value  : void
******************************************************************************/
void R_UDP_WRP_ReceiverTimeoutMilisecond(void)
{
	/* Check for interframe timeout */
	if (g_udp_device_interframe_timeout.enable == TRUE) {
		if (g_udp_device_interframe_timeout.count > 0) {
			g_udp_device_interframe_timeout.count--;
		}
		else {
			g_udp_device_interframe_timeout.enable = FALSE;
			R_UDP_DEVICE_WiSunReceiverInterframeTimeoutCallback();
		}
	}
}
/******************************************************************************
* Function Name : R_UDP_WRP_IsConnected
* Interface     : uint8_t R_UDP_WRP_IsConnected(void)
* Description   :
* Arguments     : None:
* Function Calls:
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_UDP_WRP_IsConnected(void)
{
	/* TODO: Add implementation to check if meter connected to network */
	return TRUE;
}
#endif /* #if defined(SUPPORT_UDP_PROFILE) && (SUPPORT_UDP_PROFILE == TRUE) && (UDP_MODE_SELECTION == UDP_MODE_NURATECH_WISUN_MODULE) */
