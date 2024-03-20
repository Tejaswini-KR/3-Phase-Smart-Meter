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
* File Name    : r_dlms_tcp_wrapper.c
* Version      : 1.00
* Device(s)    : R5F564MLCxDC
* Tool-Chain   : CCRX
* H/W Platform : RX64M RSK+
* Description  : TCP wrapper layer of DLMS
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
#include "wrp_app_ext.h"

#include "wrp_app_uart.h"
#include "r_dlms_config.h"
#include "r_dlms_tcp_wrapper.h"
#include "r_dlms_tcp.h"
#include "r_dlms_com_wrapper_config.h"

#if defined(SUPPORT_TCP_PROFILE) && (SUPPORT_TCP_PROFILE == TRUE) && (TCP_MODE_SELECTION == TCP_MODE_ETHERNET_SERIAL_RX65N)
#include "event.h"
#include "powermgmt.h"

#include <string.h>


/******************************************************************************
Macro definitions
******************************************************************************/
#define ENABLE_DEBUG_COMMUNICATION_SIGNAL                       (FALSE)

/* Frame format */

/* Frame */
// | [Frame format] | IP version   | Protocol  | Port    | Address    |   Code   | Length  | Data      |
// | 5 bytes        | 2 bytes      | 1 byte    | 2 bytes | 4/16 bytes |  1 bytes | 2 bytes | n (bytes) |

/* Example: */
// | "!send"        | 0x0800: IPv4 | 0x06: TCP |         |            |          |         |
// | "!data"        | 0x86DD: IPv6 | 0x11: UDP |         |            |          |         |
// | "!conn"        |              |           |         |            |          |         |
// | "!disc"        |              |           |         |            |          |         |
// | "!abrt"        |              |           |         |            |          |         |

/* Frame configure read/write */
// | [Frame format] |   Code     | Length  | Data      |
// | 5 bytes        |            | 2 bytes | n (bytes) |
// | "!cfgr"        |            |         |           |

/* WRAPPER DEFINE */

#define R_WRP_MODE_SEND             (0)
#define R_WRP_MODE_RECEIVE          (1)

#define R_WRP_CMD_DATA_BUFFER_SIZE              (5 + 2 + 1 + 2 + 16 + 2 + 16)

#define R_WRP_IP_TYPE_IPv4                      (0x0800)
#define R_WRP_IP_TYPE_IPv6                      (0x86DD)

#define R_WRP_PROTOCOL_UDP                      (0x11)
#define R_WRP_PROTOCOL_TCP                      (0x06)

#define R_WRP_RECEIVER_STEP_FRAMETYPE_LENGTH    (5)

/* WRAPPER CONFIGURE */

#define R_WRP_IP_TYPE_USING                     (R_WRP_IP_TYPE_IPv4)
#define R_WRP_PROTCOL_USING                     (R_WRP_PROTOCOL_TCP)

#if R_WRP_IP_TYPE_USING == R_WRP_IP_TYPE_IPv4
#define R_WRP_TCP_IP_ADDR_SIZE					(4)
#elif R_WRP_IP_TYPE_USING == R_WRP_IP_TYPE_IPv6
#define R_WRP_TCP_IP_ADDR_SIZE					(16)
#endif

#define R_WRP_RECEIVER_INTERFRAME_TIMEOUT_DEFAULT           (100)
#define R_WRP_SENDING_TIMEOUT_DEFAULT                       (2000)


#define R_WRP_RECEIVER_RESET(p_receiver)    {                                           \
                            (p_receiver)->step = R_WRP_RECEIVER_STEP_SOF;               \
                            (p_receiver)->step_end_pos = 0;                             \
                            (p_receiver)->byte_count = 0;                               \
                            (p_receiver)->total_byte_count = 0;                         \
}


#define R_WRP_RELOAD_INTERFRAME_TIMEOUT(interframetimeout)  {\
    interframetimeout.count = interframetimeout.initial;    \
}

#define R_WRP_RESET_INTERFRAME_TIMEOUT(interframetimeout)    {     \
    R_WRP_RELOAD_INTERFRAME_TIMEOUT(interframetimeout);    \
    interframetimeout.enable = TRUE;                        \
}

#define R_WRP_STOP_INTERFRAME_TIMEOUT(interframetimeout)  {\
    R_WRP_RELOAD_INTERFRAME_TIMEOUT(interframetimeout);    \
    interframetimeout.enable = FALSE;                        \
}

#define MOVE_UINT8_TO_BUFF(buff, uint8num)		{ *(buff)++ = (uint8_t)(uint8num); }
#define MOVE_UINT16_TO_BUFF(buff, uint16num)	{ *(buff)++ = (uint8_t)(((uint16num) & 0xFF00) >> 8);  *(buff)++ = (uint8_t)(uint16num); }

#define SWAP_UINT16(number)		{ number = (number>> 8) | (number << 8);}

#define R_WRP_TCP_RX65N_STABILIZED_MS           (2000)

/******************************************************************************
Typedef definitions
******************************************************************************/

typedef struct tag_R_Wrapper_Sender
{
	const uint8_t *p_frametype;

	uint8_t configure_code;

	uint16_t ip_type;
	uint16_t protocol;

	TcpPort	port;
	uint8_t	ip[R_WRP_TCP_IP_ADDR_SIZE];

	uint8_t service_code;

	uint16_t length;
	uint8_t *data;

	uint8_t timeout;

} R_WRP_Sender_t;

typedef struct tag_R_Wrapper_Receiver
{
	/* 1 frame */
	uint8_t             *buff;
	uint16_t            buff_length;

	uint8_t             step;
	uint16_t            step_end_pos;

	uint16_t            byte_count;
	uint16_t            total_byte_count;

	struct 
	{
		const uint8_t 	*p_frametype;
		uint16_t 		ip_type;
		uint8_t			protocol;
		uint16_t		port;
		uint8_t			ip[16];
		IpAddress		remote_ip_addr;
		uint8_t			ip_bytes_to_receive;
		uint8_t			service_code;
	} header;

	uint16_t length;
	uint8_t *p_reason_buff;

	uint8_t receiving_done;

} R_WRP_Receiver_t;


typedef struct tagFrameTypeDefinition
{
	const uint8_t     *p_cmd_frametype;
	uint8_t     next_step;
	uint16_t    next_step_length;
} WRP_FrameFormatDefinition_t;

typedef struct
{
	uint16_t	initial;
	uint16_t	count;
	uint16_t	enable;
} R_WRP_DeviceTimeoutChannel_t;

/*
 * ENUM
 */

typedef enum tag_R_Wrp_Frame_Service_t
{
	R_WRP_SERVICE_REQ = 1,
	R_WRP_SERVICE_IND = 2,
	R_WRP_SERVICE_RES = 3,
	R_WRP_SERVICE_CNF = 4
} R_Wrp_Frame_Type_t;

typedef enum Tag_R_Wrapper_Receiver_Step_t
{
	R_WRP_RECEIVER_STEP_SOF  = 0,
	R_WRP_RECEIVER_STEP_FRAMETYPE,
	R_WRP_RECEIVER_STEP_IP_TYPE,
	R_WRP_RECEIVER_STEP_PROTOCOL,
	R_WRP_RECEIVER_STEP_PORT,
	R_WRP_RECEIVER_STEP_IP_ADDRESS,
	R_WRP_RECEIVER_STEP_SERVICE_CODE,
	R_WRP_RECEIVER_STEP_DATA_LENGTH,
	R_WRP_RECEIVER_STEP_DATA_BUFFER,
	R_WRP_RECEIVER_STEP_STATUS,
	R_WRP_RECEIVER_STEP_STATUS_LENGTH,
	R_WRP_RECEIVER_STEP_STATUS_DATA,
	R_WRP_RECEIVER_STEP_CONFIGURE_CODE,
	R_WRP_RECEIVER_STEP_CONFIGURE_WRITE_LENGTH,
	R_WRP_RECEIVER_STEP_CONFIGURE_WRITE_DATA
} R_Wrp_Receiver_Step_t;
/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/******************************************************************************
Private global variables and functions
******************************************************************************/

volatile uint8_t   g_wrp_tcp_local_ip_addr_buffer[R_WRP_TCP_IP_ADDR_SIZE];
volatile IpAddress g_wrp_tcp_local_ip_addr = { (uint8_t *)g_wrp_tcp_local_ip_addr_buffer, R_WRP_TCP_IP_ADDR_SIZE };
/*
 * Remote ip address stored in g_wrp_tcp_receiver0 in below.
 */

volatile uint8_t g_wrp_send_end = TRUE;       /* Send end */

uint8_t g_wrp_receiver_buffer[R_WRP_CMD_DATA_BUFFER_SIZE];

uint8_t g_wrp_receiver_status_buffer[8];

R_WRP_Receiver_t                        g_wrp_tcp_receiver0;
volatile R_WRP_DeviceTimeoutChannel_t   g_interframe_timeout;

static volatile uint8_t g_sending_confirm_received = FALSE;
static volatile uint8_t g_config_read_confirm_received = FALSE;
static volatile uint8_t g_config_write_confirm_received = FALSE;
static volatile uint16_t g_wrp_tcp_rx65n_stabilized_count;
static volatile uint8_t * g_wrp_tcp_rx65n_p_condition;

const uint8_t R_WRP_CMD_ARG_DATA[5] = "!data";
const uint8_t R_WRP_CMD_ARG_SEND[5] = "!send";
const uint8_t R_WRP_CMD_ARG_CONN[5] = "!conn";
const uint8_t R_WRP_CMD_ARG_DISC[5] = "!disc";
const uint8_t R_WRP_CMD_ARG_ABRT[5] = "!abrt";
const uint8_t R_WRP_CMD_ARG_STAT[5] = "!stat";
const uint8_t R_WRP_CMD_ARG_CFGR[5] = "!cfgr";
const uint8_t R_WRP_CMD_ARG_CFGW[5] = "!cfgw";

const WRP_FrameFormatDefinition_t G_WRP_TCP_FRAME_TYPE_LIST[] = 
{
	{ R_WRP_CMD_ARG_DATA,  R_WRP_RECEIVER_STEP_IP_TYPE             , 2 },
	{ R_WRP_CMD_ARG_SEND,  R_WRP_RECEIVER_STEP_IP_TYPE             , 2 },
	{ R_WRP_CMD_ARG_CONN,  R_WRP_RECEIVER_STEP_IP_TYPE             , 2 },
	{ R_WRP_CMD_ARG_DISC,  R_WRP_RECEIVER_STEP_IP_TYPE             , 2 },
	{ R_WRP_CMD_ARG_ABRT,  R_WRP_RECEIVER_STEP_IP_TYPE             , 2 },
	{ R_WRP_CMD_ARG_CFGR,  R_WRP_RECEIVER_STEP_CONFIGURE_CODE      , 1 },
	{ R_WRP_CMD_ARG_CFGW,  R_WRP_RECEIVER_STEP_CONFIGURE_CODE      , 1 },
};
const uint16_t G_WRP_TCP_FRAME_TYPE_LIST_SIZE = sizeof(G_WRP_TCP_FRAME_TYPE_LIST)/sizeof(WRP_FrameFormatDefinition_t);

volatile uint8_t g_tcp_connect_active_connected = FALSE;
volatile uint8_t g_tcp_connect_active_disconnected = FALSE;

void R_TCP_WRP_UartPhySendFrame (TcpChannel channel, R_WRP_Sender_t *p_sender);
void R_TCP_WRP_UartPhyReceiveData(TcpChannel channel, uint8_t received_byte);

#if (ENABLE_DEBUG_COMMUNICATION_SIGNAL == TRUE)
#define DEBUG_RX65N_FRAME_SEQUENCE_LENGTH   32

/* 4 MSB-nibble is rx65n frame type (according to G_WRP_TCP_FRAME_TYPE_LIST table order 
 * 4 LSB-nibble is rx65n frame service type
*/
typedef enum {
    DATA_IND = (0 << 4) | R_WRP_SERVICE_IND,
    
    SEND_REQ = (1 << 4) | R_WRP_SERVICE_REQ,
    SEND_CNF = (1 << 4) | R_WRP_SERVICE_CNF,
    
    CONN_REQ = (2 << 4) | R_WRP_SERVICE_REQ,
    CONN_IND = (2 << 4) | R_WRP_SERVICE_IND,
    CONN_CNF = (2 << 4) | R_WRP_SERVICE_CNF,
    
    DISC_REQ = (3 << 4) | R_WRP_SERVICE_REQ,
    DISC_IND = (3 << 4) | R_WRP_SERVICE_IND,
    DISC_CNF = (3 << 4) | R_WRP_SERVICE_CNF,
    
    ABRT_IND = (4 << 4) | R_WRP_SERVICE_IND,
    
    CFGR_REQ = (5 << 4) | R_WRP_SERVICE_REQ,
    CFGR_CNF = (5 << 4) | R_WRP_SERVICE_CNF,
    
    CFGW_REQ = (6 << 4) | R_WRP_SERVICE_REQ,
    CFGW_CNF = (6 << 4) | R_WRP_SERVICE_CNF,
    
} rx65n_frame_type;

uint32_t g_debug_frame_data_received = 0;
uint32_t g_debug_frame_send_confirm_received = 0;
uint32_t g_debug_frame_send_confirmed = 0;
uint32_t g_debug_frame_send_unconfirmed = 0;

/* Sequence of RX65N frame */
rx65n_frame_type  g_debug_frame_sequence[DEBUG_RX65N_FRAME_SEQUENCE_LENGTH];
uint16_t g_debug_frame_count = 0;

#endif /* ENABLE_DEBUG_COMMUNICATION_SIGNAL == TRUE */

/******************************************************************************
* Function Name : R_WRP_SendBuffer
* Interface     : static void R_WRP_SendBuffer(uint8_t *buffer, uint16_t length)
* Description   : 
* Arguments     : uint8_t * buffer:
*               : uint16_t length :
* Function Calls: 
* Return Value  : static void
******************************************************************************/
static void R_WRP_SendBuffer(uint8_t *buffer, uint16_t length)
{
	g_wrp_send_end = FALSE;
	WRP_UART0_SendData(buffer, length);
	
	// R_WRP_RESET_INTERFRAME_TIMEOUT(g_interframe_timeout);
	while (g_wrp_send_end == FALSE);
}

/******************************************************************************
* Function Name : r_wrp_tcp_rx65n_waiting_predicate
* Interface     : static uint8_t r_wrp_tcp_rx65n_waiting_predicate(void)
* Description   : 
* Arguments     : uint8_t * buffer:
*               : uint16_t length :
* Function Calls:
* Return Value  : static void
******************************************************************************/
static uint8_t r_wrp_tcp_rx65n_waiting_predicate(void)
{
    /* Condition 1: requested variables set */
    if (g_wrp_tcp_rx65n_p_condition != NULL) {
        if (*g_wrp_tcp_rx65n_p_condition == TRUE) {
            return TRUE;
        }
    }

    /* Condition 2: meter is not in last gasp operation */
    if ((EVENT_IsLastGasp() == 1) || (POWERMGMT_IsVDDLow() == 1))
    {
        return TRUE;
    }

    return FALSE;
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_Init
* Interface     : void R_TCP_DEVICE_Init(void)
* Description   : Initial TCP device
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_TCP_DEVICE_Init(TcpChannel tcp_channel)
{
    if (tcp_channel == 0)
    {
		WRP_UART0_Init();
		WRP_UART0_SetBaudRate(WRP_UART_BAUD_RATE_19200);
		WRP_UART0_ConfigHDLCProtocol();
		WRP_UART0_Start();

        g_wrp_send_end  = TRUE;

		g_wrp_tcp_local_ip_addr.p_addr = (uint8_t *)g_wrp_tcp_local_ip_addr_buffer;
		g_wrp_tcp_local_ip_addr.size = R_WRP_TCP_IP_ADDR_SIZE;
		g_wrp_tcp_receiver0.header.remote_ip_addr.p_addr = g_wrp_tcp_receiver0.header.ip;
		g_wrp_tcp_receiver0.header.remote_ip_addr.size   = R_WRP_TCP_IP_ADDR_SIZE;
        g_wrp_tcp_receiver0.buff        = g_wrp_receiver_buffer;
        g_wrp_tcp_receiver0.buff_length = R_WRP_CMD_DATA_BUFFER_SIZE;

        R_WRP_RECEIVER_RESET(&g_wrp_tcp_receiver0);

        /* Init interframe timeout */
        g_interframe_timeout.enable = FALSE;
        g_interframe_timeout.count = 0;
        g_interframe_timeout.initial = R_WRP_RECEIVER_INTERFRAME_TIMEOUT_DEFAULT;
    }
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_Start
* Interface     : void R_TCP_DEVICE_Start(void)
* Description   : Start TCP device
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_TCP_DEVICE_Start(TcpChannel tcp_channel)
{
	if (tcp_channel == 0)
	{
		// WRP_UART0_Start();

        g_wrp_tcp_rx65n_stabilized_count = R_WRP_TCP_RX65N_STABILIZED_MS;
	}
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_Stop
* Interface     : void R_TCP_DEVICE_Stop(void)
* Description   : Stop TCP device
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_TCP_DEVICE_Stop(TcpChannel tcp_channel)
{
	if (tcp_channel == 0) {
		//  WRP_UART0_Stop();
	}
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_PollingProcess
* Interface     : void R_TCP_DEVICE_PollingProcess(void)
* Description   : Polling process of TCP device
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_TCP_DEVICE_PollingProcess(TcpChannel tcp_channel)
{
	R_WRP_Receiver_t * p_receiver = NULL;

    if (tcp_channel == 0) {
       
	   	/* Do nothing */
		p_receiver = &g_wrp_tcp_receiver0;
		if ((p_receiver->buff == NULL) || (p_receiver->buff_length == 0))
		{
			return;
		}
    }
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_GetConfig
* Interface     : uint8_t R_TCP_DEVICE_GetConfig(
*               :     TcpChannel tcp_channel ,
*               :     TcpPortConfig* p_config,
*               : );
* Description   : Get config of TCP device (Port number, IP address), put to p_config
* Arguments     : TcpChannel tcp_channel :
*               : TcpPortConfig* p_config:
* Function Calls:
* Return Value  : uint8_t, Success (TRUE) or fail (FALSE)
******************************************************************************/
uint8_t R_TCP_DEVICE_GetConfig(TcpChannel tcp_channel, TcpPortConfig* p_config)
{
    uint32_t count;
	R_WRP_Sender_t sender;
    uint8_t config_code;
    uint8_t link_status;
    uint8_t result;
    if (tcp_channel != 0)
    {
        return FALSE;
    }
    
	if (p_config->local_ip_address->size != R_WRP_TCP_IP_ADDR_SIZE) {
		return FALSE;
	}

	sender.p_frametype	= R_WRP_CMD_ARG_CFGR;
    
	sender.ip_type		= R_WRP_IP_TYPE_USING;
	sender.protocol		= R_WRP_PROTCOL_USING;
	sender.service_code = (uint8_t)R_WRP_SERVICE_REQ;

	sender.port			= p_config->local_tcp_port;
	memcpy(sender.ip, p_config->local_ip_address->p_addr, R_WRP_TCP_IP_ADDR_SIZE);
    
    /* Configure code: port + IP */
    sender.length = 1;
    sender.data = &config_code;
    
    config_code = 0x02;
    
    g_config_read_confirm_received = FALSE;
	R_TCP_WRP_UartPhySendFrame(tcp_channel, &sender);
    /* Wait until receive cfgr confirm from module */
    g_wrp_tcp_rx65n_p_condition = &g_config_read_confirm_received;
    result = WRP_EXT_HwDelay(1000, r_wrp_tcp_rx65n_waiting_predicate);
    if (result != WRP_EXT_HW_DELAY_PRED_TRUE) {
        return FALSE;
    }
    else
    {
        if (g_wrp_tcp_receiver0.p_reason_buff != NULL)
        {
            link_status = g_wrp_tcp_receiver0.p_reason_buff[2];
        }
    }
    
    /* Link on */
    if (link_status >= 1)
    {
        /* Skip ethernet link checking */
        NOP();
    }
    
    /* Configure code: port + IP */
    config_code = 0x01;
    
    g_config_read_confirm_received = FALSE;
	R_TCP_WRP_UartPhySendFrame(tcp_channel, &sender);
    /* Wait until receive cfgr confirm from module */
    g_wrp_tcp_rx65n_p_condition = &g_config_read_confirm_received;
    result = WRP_EXT_HwDelay(1000, r_wrp_tcp_rx65n_waiting_predicate);
    if (result != WRP_EXT_HW_DELAY_PRED_TRUE) {
        return FALSE;
    }
    else
    {
		memcpy((void *)g_wrp_tcp_local_ip_addr_buffer, g_wrp_tcp_receiver0.header.ip, R_WRP_TCP_IP_ADDR_SIZE);
		g_wrp_tcp_local_ip_addr.p_addr = (uint8_t *)g_wrp_tcp_local_ip_addr_buffer;
		g_wrp_tcp_local_ip_addr.size = R_WRP_TCP_IP_ADDR_SIZE;
		p_config->local_ip_address = (IpAddressPtr)&g_wrp_tcp_local_ip_addr;
        p_config->local_tcp_port = g_wrp_tcp_receiver0.header.port;
    }
    
	return TRUE;
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_SetConfig
* Interface     : uint8_t R_TCP_DEVICE_SetConfig(
*               :     TcpChannel tcp_channel ,
*               :     TcpPortConfig* p_config,
*               : );
* Description   : Set config of TCP device (Port number, IP address), read from p_config
* Arguments     : TcpChannel tcp_channel :
*               : TcpPortConfig* p_config:
* Function Calls:
* Return Value  : uint8_t, Success (TRUE) or fail (FALSE)
******************************************************************************/
uint8_t R_TCP_DEVICE_SetConfig(TcpChannel tcp_channel, TcpPortConfig* p_config)
{
    uint32_t count;
    uint8_t result;
	R_WRP_Sender_t sender;
    uint8_t config_code;
    
    if (tcp_channel != 0)
    {
        return FALSE;
    }
	
	if (p_config->local_ip_address->size != R_WRP_TCP_IP_ADDR_SIZE) {
		return FALSE;
	}

	sender.p_frametype	= R_WRP_CMD_ARG_CFGW;

	sender.ip_type		= R_WRP_IP_TYPE_USING;
	sender.protocol		= R_WRP_PROTCOL_USING;
	sender.service_code = (uint8_t)R_WRP_SERVICE_REQ;

	sender.port			= p_config->local_tcp_port;
	memcpy(sender.ip, p_config->local_ip_address->p_addr, R_WRP_TCP_IP_ADDR_SIZE);
    
    /* Configure port + IP */
    config_code = 0x01;
    
    sender.length = 1;
    sender.data = &config_code;
    
    g_config_write_confirm_received = FALSE;
    
	R_TCP_WRP_UartPhySendFrame(tcp_channel, &sender);

    /* Wait until receive cfgw confirm from module */
    g_wrp_tcp_rx65n_p_condition = &g_config_write_confirm_received;
    result = WRP_EXT_HwDelay(1000, r_wrp_tcp_rx65n_waiting_predicate);
    if (result != WRP_EXT_HW_DELAY_PRED_TRUE) {
        return FALSE;
    }
    
	return TRUE;
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_ConnectRequest
* Interface     : uint8_t R_TCP_DEVICE_ConnectRequest(
*               :     TcpChannel tcp_channel        ,
*               :     TcpPort remote_tcp_port       ,
*               :     IpAddressPtr remote_ip_address,
*               : );
* Description   : Request a TCP connection to a remote station (remote_tcp_port, remote_ip_address)
* Arguments     : TcpChannel tcp_channel        : Channel ID associated with TCP device
*               : TcpPort remote_tcp_port       : Remote station TCP port
*               : IpAddressPtr remote_ip_address: Remote station IP address
* Return Value  : uint8_t, Success (TRUE) or fail (FALSE)
******************************************************************************/
uint8_t R_TCP_DEVICE_ConnectRequest(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address)
{
	R_WRP_Sender_t sender;

	if (remote_ip_address->size != R_WRP_TCP_IP_ADDR_SIZE) {
		return FALSE;
	}

	sender.p_frametype	= R_WRP_CMD_ARG_CONN;

	sender.ip_type		= R_WRP_IP_TYPE_USING;
	sender.protocol		= R_WRP_PROTCOL_USING;

	sender.port			= remote_tcp_port;
	memcpy(sender.ip, remote_ip_address->p_addr, R_WRP_TCP_IP_ADDR_SIZE);

	sender.data		= NULL;
	sender.length	= 0;

	sender.service_code = (uint8_t)R_WRP_SERVICE_REQ;

	R_TCP_WRP_UartPhySendFrame(tcp_channel, &sender);

	return TRUE;
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_ConnectResponse
* Interface     : uint8_t R_TCP_DEVICE_ConnectResponse(
*               :     TcpChannel tcp_channel        ,
*               :     TcpPort remote_tcp_port       ,
*               :     IpAddressPtr remote_ip_address,
*               :     uint8_t result                ,
*               : );
* Description   : Response to a TCP connection from a remote station (remote_tcp_port, remote_ip_address)
* Arguments     : TcpChannel tcp_channel        : Channel ID associated with TCP device
*               : TcpPort remote_tcp_port       : Remote station TCP port
*               : IpAddressPtr remote_ip_address: Remote station IP address
*               : uint8_t result                : Connection req from remote station is accepted (TRUE) or reject (FALSE)
* Return Value  : uint8_t, Success (TRUE) or fail (FALSE)
******************************************************************************/
uint8_t R_TCP_DEVICE_ConnectResponse(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address, uint8_t result)
{
	return TRUE;
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_DisconnectRequest
* Interface     : uint8_t R_TCP_DEVICE_DisconnectRequest(
*               :     TcpChannel tcp_channel        ,
*               :     TcpPort remote_tcp_port       ,
*               :     IpAddressPtr remote_ip_address,
*               : );
* Description   : Request a TCP disconnect signal to remote station (remote_tcp_port, remote_ip_address)
* Arguments     : TcpChannel tcp_channel        : Channel ID associated with TCP device
*               : TcpPort remote_tcp_port       : Remote station TCP port
*               : IpAddressPtr remote_ip_address: Remote station IP address
* Function Calls: 
* Return Value  : uint8_t, Success (TRUE) or fail (FALSE)
******************************************************************************/
uint8_t R_TCP_DEVICE_DisconnectRequest(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address)
{
	R_WRP_Sender_t sender;

	if (remote_ip_address->size != R_WRP_TCP_IP_ADDR_SIZE) {
		return FALSE;
	}

	sender.p_frametype	= R_WRP_CMD_ARG_DISC;

	sender.ip_type		= R_WRP_IP_TYPE_IPv4;
	sender.protocol		= R_WRP_PROTOCOL_TCP;

	sender.port			= remote_tcp_port;
	memcpy(sender.ip, remote_ip_address->p_addr, R_WRP_TCP_IP_ADDR_SIZE);

	sender.data		= NULL;
	sender.length	= 0;

	sender.service_code = (uint8_t)R_WRP_SERVICE_REQ;

	R_TCP_WRP_UartPhySendFrame(tcp_channel, &sender);

	return TRUE;
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_DisconnectResponse
* Interface     : uint8_t R_TCP_DEVICE_DisconnectResponse(
*               :     TcpChannel tcp_channel        ,
*               :     TcpPort remote_tcp_port       ,
*               :     IpAddressPtr remote_ip_address,
*               :     uint8_t result                ,
*               : );
* Description   : Response to a TCP disconnection from a remote station (remote_tcp_port, remote_ip_address)
* Arguments     : TcpChannel tcp_channel        : Channel ID associated with TCP device
*               : TcpPort remote_tcp_port       : Remote station TCP port
*               : IpAddressPtr remote_ip_address: Remote station IP address
*               : uint8_t result                : Disconnection req from remote station is accepted (TRUE) or reject (FALSE)
* Function Calls: 
* Return Value  : uint8_t, Success (TRUE) or fail (FALSE)
******************************************************************************/
uint8_t R_TCP_DEVICE_DisconnectResponse(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address, uint8_t result)
{
	return TRUE;
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_DataRequest
* Interface     : uint8_t R_TCP_DEVICE_DataRequest(
*               :     TcpChannel tcp_channel        ,
*               :     TcpPort remote_tcp_port       ,
*               :     IpAddressPtr remote_ip_address,
*               :     uint8_t * data                ,
*               :     uint16_t length               ,
*               : );
* Description   : Request to send data to a remote station (remote_tcp_port, remote_ip_address)
* Arguments     : TcpChannel tcp_channel        : Channel ID associated with TCP device
*               : TcpPort remote_tcp_port       : Remote station TCP port
*               : IpAddressPtr remote_ip_address: Remote station IP address
*               : uint8_t * data                : Input data buffer pointer
*               : uint16_t length               : Input data length
* Function Calls: 
* Return Value  : uint8_t, Success (TRUE) or fail (FALSE)
******************************************************************************/
uint8_t R_TCP_DEVICE_DataRequest(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address, uint8_t *data, uint16_t length)
{
	R_WRP_Sender_t sender;

	if (remote_ip_address->size != R_WRP_TCP_IP_ADDR_SIZE) {
		return FALSE;
	}

	sender.p_frametype	= R_WRP_CMD_ARG_SEND;

	sender.ip_type		= R_WRP_IP_TYPE_USING;
	sender.protocol		= R_WRP_PROTCOL_USING;

	sender.port			= remote_tcp_port;
	memcpy(sender.ip, remote_ip_address->p_addr, R_WRP_TCP_IP_ADDR_SIZE);

	sender.data		= data;
	sender.length	= length;

	sender.service_code = (uint8_t)R_WRP_SERVICE_REQ;

#if (ENABLE_DEBUG_COMMUNICATION_SIGNAL == TRUE)    
    g_debug_frame_sequence[g_debug_frame_count++] = SEND_REQ;
    g_debug_frame_count %= DEBUG_RX65N_FRAME_SEQUENCE_LENGTH;
#endif

    g_sending_confirm_received = FALSE;
    
	R_TCP_WRP_UartPhySendFrame(tcp_channel, &sender);

	return TRUE;
}

/*
 * Usage of TCP device service callbacks
 */

 /*
  * R_TCP_DEVICE_ConnectConfirm(TcpChannel tcp_channel, uint8_t result, uint8_t *reason, uint16_t reason_length);
  * ---
  * R_TCP_DEVICE_ConnectConfirm() is used to confirm about the last R_TCP_DEVICE_ConnectRequest() call,
  * Normally it is called once remote station has response for the R_TCP_DEVICE_ConnectRequest()
  */
 
 /*
  * R_TCP_DEVICE_ConnectIndication(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address);
  * ---
  * R_TCP_DEVICE_ConnectIndication() is used to indicate that there is a connection request event raised from remote station,
  * This function shall be called once remote station sent connection request to this device
  */

 /*
  * R_TCP_DEVICE_DisconnectConfirm(TcpChannel tcp_channel, uint8_t result, uint8_t *reason, uint16_t reason_length);
  * ---
  * R_TCP_DEVICE_DisconnectConfirm() is used to confirm about the last R_TCP_DEVICE_DisconnectRequest() call,
  * Normally it is called once remote station has response for the R_TCP_DEVICE_DisconnectRequest()
  */

 /*
  * R_TCP_DEVICE_DisconnectIndication(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address, TcpDisconnectReason reason);
  * ---
  * R_TCP_DEVICE_DisconnectIndication() is used to indicate that there is a disconnection request event raised from remote station,
  * This function shall be called once remote station sent disconnection request to this device
  */

 /*
  * R_TCP_DEVICE_AbortIndication(TcpChannel tcp_channel, uint8_t *reason, uint16_t reason_length);
  * ---
  * R_TCP_DEVICE_AbortIndication() is used to indicate that there is an interruption event raised from local or from remote station,
  * This function shall be called once there is an  interruption happen between this device and remote station
  */

 /*
  * R_TCP_DEVICE_DataConfirm(TcpChannel tcp_channel, uint8_t result);
  * ---
  * R_TCP_DEVICE_DataConfirm() is used to confirm about the last R_TCP_DEVICE_DataRequest() call,
  * Normally it is called once to confirm about the data transmition end on the R_TCP_DEVICE_DataRequest()
  */

 /*
  * R_TCP_DEVICE_DataIndication(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address, uint8_t *rx_buffer, uint16_t rx_buffer_length);
  * ---
  * R_TCP_DEVICE_DataIndication() is used to indicate that there is data received from remote station,
  * It is able to put fragmented data to R_TCP_DEVICE_DataIndication() and call multiple time. WPDU is concat & process normally.
  */

 /*
  * R_TCP_DEVICE_DataErrorIndication(TcpChannel tcp_channel);
  * ---
  * R_TCP_DEVICE_DataErrorIndication() is used to indicate that there is data received error happen on this device
  */

/******************************************************************************
* Function Name : R_TCP_WRP_UartPhySendFrame
* Interface     : void R_TCP_WRP_UartPhySendFrame(
*               :     TcpChannel channel, 
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
void R_TCP_WRP_UartPhySendFrame ( TcpChannel channel, R_WRP_Sender_t *p_sender )
{
	uint8_t	 cmd_buffer[5 + 2 + 1 + 2 + R_WRP_TCP_IP_ADDR_SIZE + 4];
	uint8_t  *p_cmd = cmd_buffer;
	uint16_t cmd_length;
    uint8_t result;

	void (*wrp_send_function)(uint8_t *buffer, uint16_t length);

	int8_t i;

	if (channel == 0)
	{
		wrp_send_function = R_WRP_SendBuffer;
	}
	else
	{
		return;
	}


	/* 
	 * 	Frame format
	 * 			
	 * 		[Frame type]	[IP version]	[Protocol]	[Port]	[Address]	[Code]	[Length]	[Data]
	 * 
	 */

	/* Frame type */
	memcpy(p_cmd, p_sender->p_frametype, 5 );
	p_cmd += 5;
    
	/* !ip_type */
	MOVE_UINT16_TO_BUFF(p_cmd, p_sender->ip_type);

	/* Protocol */
	MOVE_UINT8_TO_BUFF(p_cmd, p_sender->protocol);

	/* Port */
	MOVE_UINT16_TO_BUFF(p_cmd, p_sender->port);

	/* IP address */
	#if (defined( R_WRP_IP_TYPE_USING))
		memcpy(p_cmd, p_sender->ip, R_WRP_TCP_IP_ADDR_SIZE);
		p_cmd += R_WRP_TCP_IP_ADDR_SIZE;
	#endif

	/* [Service code] */
	MOVE_UINT8_TO_BUFF(p_cmd, p_sender->service_code);

	/* [length] */
	MOVE_UINT16_TO_BUFF(p_cmd, p_sender->length);

	cmd_length = (uint16_t)(p_cmd - cmd_buffer);
	wrp_send_function(cmd_buffer, cmd_length);

	if (p_sender->length > 0)
	{
		/* Send data */
		wrp_send_function(p_sender->data, p_sender->length);
	}

    if (p_sender->p_frametype == R_WRP_CMD_ARG_SEND)
    {
        g_wrp_tcp_rx65n_p_condition = &g_sending_confirm_received;
        result = WRP_EXT_HwDelay(R_WRP_SENDING_TIMEOUT_DEFAULT, r_wrp_tcp_rx65n_waiting_predicate);
        if (result != WRP_EXT_HW_DELAY_PRED_TRUE) {
            R_TCP_DEVICE_DataConfirm(channel, FALSE);
#if (ENABLE_DEBUG_COMMUNICATION_SIGNAL == TRUE)
            g_debug_frame_send_unconfirmed++;
#endif
            }
        else {
			R_TCP_DEVICE_DataConfirm(channel, TRUE);
#if (ENABLE_DEBUG_COMMUNICATION_SIGNAL == TRUE)
            g_debug_frame_send_confirmed++;
#endif
        }
    }
}

/******************************************************************************
* Function Name : R_TCP_WRP_UartPhyReceiveData
* Interface     : void R_TCP_WRP_UartPhyReceiveData(TcChannel channel, uint8_t received_byte)
* Description   : 
* Arguments     : TcpChannel channel   :
*               : uint8_t received_byte:
* Function Calls: 
* Return Value  : void
******************************************************************************/
void R_TCP_WRP_UartPhyReceiveData(TcpChannel channel, uint8_t received_byte)
{
	uint8_t i;
	R_WRP_Receiver_t * p_receiver = NULL;

	uint8_t frame_OK = FALSE;
    uint8_t service_result;
	uint16_t ip_type;
    
	// Check validity
	{
		if (channel == 0) 
		{
			p_receiver = &g_wrp_tcp_receiver0;
		}
		else
		{
			return;
		}

		if ((p_receiver->buff == NULL) || (p_receiver->buff_length == 0))
		{
			return;
		}
	}
    
	/*
	 * Receive & decode the !data node_ip4 length data_bytes
	 * Bring data to upper layer on receiving mode
	 */
    R_WRP_RESET_INTERFRAME_TIMEOUT(g_interframe_timeout);
    p_receiver->total_byte_count++;
	if (p_receiver->byte_count < p_receiver->buff_length)
	{
		p_receiver->buff[p_receiver->byte_count++] = (uint8_t)received_byte;
	}

	switch ( p_receiver->step )
	{
		/*******************************************************************************
		 *  FRAME TYPE
		 *******************************************************************************/
		case R_WRP_RECEIVER_STEP_SOF:
			if (received_byte == '!' && p_receiver->step_end_pos == 0)
			{
				p_receiver->step = R_WRP_RECEIVER_STEP_FRAMETYPE;
				p_receiver->step_end_pos = 5;
			}
			else
			{
				R_WRP_RECEIVER_RESET(p_receiver);
			}
			break;
		case R_WRP_RECEIVER_STEP_FRAMETYPE:
			if (p_receiver->total_byte_count >= p_receiver->step_end_pos)
			{
				frame_OK = FALSE;
				for(i = 0; i < G_WRP_TCP_FRAME_TYPE_LIST_SIZE; i++)
				{
					if (memcmp(p_receiver->buff, G_WRP_TCP_FRAME_TYPE_LIST[i].p_cmd_frametype , 5) == 0)
					{
						p_receiver->header.p_frametype = G_WRP_TCP_FRAME_TYPE_LIST[i].p_cmd_frametype;
						p_receiver->step          = R_WRP_RECEIVER_STEP_IP_TYPE;
						p_receiver->step_end_pos += 2;
						
						frame_OK = TRUE;

						break;
					}
				}

				if (frame_OK == FALSE)
				{
					R_WRP_RECEIVER_RESET(p_receiver);
				}
			}

			break;

		/*******************************************************************************
		 *  FRAME TYPE == DATA
		 *******************************************************************************/
		case R_WRP_RECEIVER_STEP_IP_TYPE:
			if (p_receiver->total_byte_count >= p_receiver->step_end_pos)
			{
				memcpy( 
                    &p_receiver->header.ip_type, 
                    &p_receiver->buff[p_receiver->step_end_pos - 2] , 
                    2
                );
				SWAP_UINT16(p_receiver->header.ip_type);

				if ((p_receiver->header.ip_type == (uint16_t)R_WRP_IP_TYPE_IPv4) || 
					(p_receiver->header.ip_type == (uint16_t)R_WRP_IP_TYPE_IPv6))
				{
					p_receiver->step          = R_WRP_RECEIVER_STEP_PROTOCOL;
					p_receiver->step_end_pos += 1;
				}
				else
				{
					R_WRP_RECEIVER_RESET(p_receiver);
				}
			}
			break;
		case R_WRP_RECEIVER_STEP_PROTOCOL:
			if (p_receiver->total_byte_count >= p_receiver->step_end_pos)
			{
				p_receiver->header.protocol = received_byte;

				/* Next step */
				p_receiver->step          = R_WRP_RECEIVER_STEP_PORT;
				p_receiver->step_end_pos += 2;
			}
			break;

		case R_WRP_RECEIVER_STEP_PORT:
			if (p_receiver->total_byte_count >= p_receiver->step_end_pos)
			{
				memcpy(&p_receiver->header.port, &p_receiver->buff[p_receiver->step_end_pos - 2] , 2);
				SWAP_UINT16(p_receiver->header.port);

				/* Next step */
				p_receiver->step          = R_WRP_RECEIVER_STEP_IP_ADDRESS;

				if (p_receiver->header.ip_type == R_WRP_IP_TYPE_IPv4)
				{
					p_receiver->header.ip_bytes_to_receive = 4;
				}
				else 
				{
					p_receiver->header.ip_bytes_to_receive = 16;
				}
                
                p_receiver->step_end_pos += p_receiver->header.ip_bytes_to_receive;
			}
            break;

		case R_WRP_RECEIVER_STEP_IP_ADDRESS:
			if (p_receiver->total_byte_count >= p_receiver->step_end_pos)
			{
                memcpy(
                    p_receiver->header.ip, 
                    &p_receiver->buff[p_receiver->step_end_pos - p_receiver->header.ip_bytes_to_receive], 
                    p_receiver->header.ip_bytes_to_receive
                    );

				p_receiver->header.remote_ip_addr.p_addr = p_receiver->header.ip;
				p_receiver->header.remote_ip_addr.size = R_WRP_TCP_IP_ADDR_SIZE;

				p_receiver->step = R_WRP_RECEIVER_STEP_SERVICE_CODE;
				p_receiver->step_end_pos += 1;
			}
			break;
		case R_WRP_RECEIVER_STEP_SERVICE_CODE:
			if (p_receiver->total_byte_count >= p_receiver->step_end_pos)
			{
				p_receiver->header.service_code = received_byte;

				p_receiver->step = R_WRP_RECEIVER_STEP_DATA_LENGTH;
				p_receiver->step_end_pos += 2;
			}
			break;

		case R_WRP_RECEIVER_STEP_DATA_LENGTH:
			if (p_receiver->total_byte_count >= p_receiver->step_end_pos)
			{
				memcpy(
                    (uint8_t *)&p_receiver->length, 
                    &p_receiver->buff[p_receiver->step_end_pos - 2], 
                    2
                );
				SWAP_UINT16(p_receiver->length);
				
				if (p_receiver->header.p_frametype != R_WRP_CMD_ARG_DATA &&
					p_receiver->length > 16)
				{
					R_WRP_RECEIVER_RESET(p_receiver);
					break;
				}
                
				p_receiver->step = R_WRP_RECEIVER_STEP_DATA_BUFFER;
				p_receiver->step_end_pos += p_receiver->length;
                
                /* If there's no data, then fall to R_WRP_RECEIVER_STEP_DATA_BUFFER step */
                if (p_receiver->length > 0)
                {
    			    break;
                }
			}
            else
            {
                break;
            }
            
		case R_WRP_RECEIVER_STEP_DATA_BUFFER:
            
			if (p_receiver->header.p_frametype == R_WRP_CMD_ARG_DATA)
			{
				R_TCP_DEVICE_DataIndication(
					(TcpChannel)		channel,
					(TcpPort)			p_receiver->header.port,
					(IpAddressPtr)		&p_receiver->header.remote_ip_addr,
					(uint8_t *)			&received_byte,
					(uint16_t)			1
				);
			}
            
            if ((p_receiver->total_byte_count >= p_receiver->step_end_pos))
			{
                if ((p_receiver->header.p_frametype != R_WRP_CMD_ARG_DATA))
                {
                    if (p_receiver->length >= 1 && p_receiver->length < 16)
                    {
                        p_receiver->p_reason_buff = &p_receiver->buff[p_receiver->step_end_pos - p_receiver->length];
                        service_result = p_receiver->p_reason_buff[0];
                    }
                    else
                    {
                        p_receiver->p_reason_buff = NULL;
                        service_result = TRUE;
                    }
                    
                    if (p_receiver->header.p_frametype == R_WRP_CMD_ARG_CONN)
                    {
                        if (p_receiver->header.service_code == R_WRP_SERVICE_CNF) 
                        {
                            R_TCP_DEVICE_ConnectConfirm(
                                channel, 
                                service_result, 
                                p_receiver->p_reason_buff, 
                                p_receiver->length
                            );
                            g_tcp_connect_active_connected = service_result;
#if (ENABLE_DEBUG_COMMUNICATION_SIGNAL == TRUE)
                            g_debug_frame_sequence[g_debug_frame_count++] = CONN_CNF;
                            g_debug_frame_count %= DEBUG_RX65N_FRAME_SEQUENCE_LENGTH;
#endif
                        }
                        else if (p_receiver->header.service_code == R_WRP_SERVICE_IND)
                        {
                            R_TCP_DEVICE_ConnectIndication(
                                channel, 
                                p_receiver->header.port, 
								(IpAddressPtr)&p_receiver->header.remote_ip_addr
                            );
#if (ENABLE_DEBUG_COMMUNICATION_SIGNAL == TRUE)
                            g_debug_frame_sequence[g_debug_frame_count++] = CONN_IND;
                            g_debug_frame_count %= DEBUG_RX65N_FRAME_SEQUENCE_LENGTH;
#endif
                        }
                    }
                    else if (p_receiver->header.p_frametype == R_WRP_CMD_ARG_DISC)
                    {
                        if (p_receiver->header.service_code == R_WRP_SERVICE_CNF)
                        {
                            R_TCP_DEVICE_DisconnectConfirm(
                                channel, 
                                service_result, 
                                p_receiver->p_reason_buff, 
                                p_receiver->length
                            );
                            g_tcp_connect_active_disconnected = service_result;
#if (ENABLE_DEBUG_COMMUNICATION_SIGNAL == TRUE)
                            g_debug_frame_sequence[g_debug_frame_count++] = DISC_CNF;
                            g_debug_frame_count %= DEBUG_RX65N_FRAME_SEQUENCE_LENGTH;
#endif
                        }
                        else if (p_receiver->header.service_code == R_WRP_SERVICE_IND)
                        {
					        R_TCP_DEVICE_DisconnectIndication(
                                channel, 
                                p_receiver->header.port, 
								(IpAddressPtr)&p_receiver->header.remote_ip_addr,
                                (TcpDisconnectReason)service_result
                            );
#if (ENABLE_DEBUG_COMMUNICATION_SIGNAL == TRUE)
                            g_debug_frame_sequence[g_debug_frame_count++] = DISC_IND;
                            g_debug_frame_count %= DEBUG_RX65N_FRAME_SEQUENCE_LENGTH;
#endif
                        }
                    }
                    else if (p_receiver->header.p_frametype == R_WRP_CMD_ARG_ABRT)
                    {
                        if (p_receiver->header.service_code == R_WRP_SERVICE_IND)
                        {
                            R_TCP_DEVICE_AbortIndication(
                                channel, 
                                p_receiver->header.port, 
								(IpAddressPtr)&p_receiver->header.remote_ip_addr,
                                p_receiver->p_reason_buff, 
                                p_receiver->length
                            );
#if (ENABLE_DEBUG_COMMUNICATION_SIGNAL == TRUE)
                            g_debug_frame_sequence[g_debug_frame_count++] = ABRT_IND;
                            g_debug_frame_count %= DEBUG_RX65N_FRAME_SEQUENCE_LENGTH;
#endif
                        }
                    }
                    else if (p_receiver->header.p_frametype == R_WRP_CMD_ARG_SEND && p_receiver->header.service_code == R_WRP_SERVICE_CNF)
                    {
                        g_sending_confirm_received = TRUE;
    	                R_TCP_DEVICE_DataConfirm(channel, service_result);
#if (ENABLE_DEBUG_COMMUNICATION_SIGNAL == TRUE)
                        g_debug_frame_send_confirm_received++;
                        g_debug_frame_sequence[g_debug_frame_count++] = SEND_CNF;
                        g_debug_frame_count %= DEBUG_RX65N_FRAME_SEQUENCE_LENGTH;
#endif
                    }
                    else if (p_receiver->header.p_frametype == R_WRP_CMD_ARG_CFGR)
                    {
                        g_sending_confirm_received = TRUE;
                        if (p_receiver->header.service_code == R_WRP_SERVICE_CNF)
                        {
                            g_config_read_confirm_received = TRUE;
                        }
                    }
                    else if (p_receiver->header.p_frametype == R_WRP_CMD_ARG_CFGW)
                    {
                        g_sending_confirm_received = TRUE;
                        if (p_receiver->header.service_code == R_WRP_SERVICE_CNF)
                        {
                            g_config_write_confirm_received = TRUE;
                        }
                    }
                }
                else {
#if (ENABLE_DEBUG_COMMUNICATION_SIGNAL == TRUE)
                    g_debug_frame_data_received++;
                    g_debug_frame_sequence[g_debug_frame_count++] = DATA_IND;
                    g_debug_frame_count %= DEBUG_RX65N_FRAME_SEQUENCE_LENGTH;
#endif
                }
                
                R_WRP_STOP_INTERFRAME_TIMEOUT(g_interframe_timeout);
				R_WRP_RECEIVER_RESET(p_receiver);
			}
			break;

		default:
			R_WRP_RECEIVER_RESET(p_receiver);
			break;
	}

	return;
}


/******************************************************************************
* Function Name : R_TCP_WRP_UartPhySendEnd
* Interface     : void R_TCP_WRP_UartPhySendEnd(TcpChannel channel)
* Description   : 
* Arguments     : TcpChannel channel:
* Function Calls: 
* Return Value  : void
******************************************************************************/
void R_TCP_WRP_UartPhySendEnd(TcpChannel channel)
{
	if (channel == 0) {
		g_wrp_send_end = TRUE;
	}
}

 /******************************************************************************
* Function Name : R_TCP_WRP_ReceiverInterframeTimeoutCallback
* Interface     : void R_TCP_WRP_ReceiverInterframeTimeoutCallback(void)
* Description   : 
* Arguments     : None:
* Function Calls: 
* Return Value  : None
******************************************************************************/
void R_TCP_WRP_ReceiverInterframeTimeout_Callback(void)
{
    R_WRP_STOP_INTERFRAME_TIMEOUT(g_interframe_timeout);
	R_WRP_RECEIVER_RESET(&g_wrp_tcp_receiver0);
}

 /******************************************************************************
* Function Name : R_TCP_WRP_ReceiverTimeoutMilisecond
* Interface     : void R_TCP_WRP_ReceiverTimeoutMilisecond(void)
* Description   : 
* Arguments     : None:
* Function Calls: 
* Return Value  : void
******************************************************************************/
void R_TCP_WRP_ReceiverTimeoutMilisecond(void)
{
	/* Check for interframe timeout */
	if (g_interframe_timeout.enable == TRUE) {
		if (g_interframe_timeout.count > 0) {
			g_interframe_timeout.count--;
		}
		else {
			R_TCP_WRP_ReceiverInterframeTimeout_Callback();
		}
	}
    
    if (g_wrp_tcp_rx65n_stabilized_count > 0)
    {
        g_wrp_tcp_rx65n_stabilized_count--;
		}
    }

/******************************************************************************
* Function Name : R_TCP_WRP_IsConnected
* Interface     : uint8_t R_TCP_WRP_IsConnected(void)
* Description   :
* Arguments     : None:
* Function Calls:
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_TCP_WRP_IsConnected(void)
{
    /* TODO: Add implementation to check if meter connected to network */
    return (g_wrp_tcp_rx65n_stabilized_count == 0 ? TRUE : FALSE);
}

/******************************************************************************
* Function Name : R_TCP_WRP_TryOpenConnection
* Interface     : uint8_t R_TCP_WRP_TryOpenConnection(TcpPort remote_port, IpAddressPtr remote_ip_address)
* Description   : 
* Arguments     : TcpPort remote_port: remote port to connect
*               : IpAddressPtr remote_ip_address: remote IP address to connect
* Return Value  : uint8_t: TRUE or FALSE
*               : TRUE: already connected or connect successfully
*               : FALSE: connection failed (timeout)
******************************************************************************/
uint8_t R_TCP_WRP_TryOpenConnection(TcpPort remote_port, IpAddressPtr remote_ip_address)
{
    volatile uint8_t result = FALSE;
	/* Waiting if there's any disconnect signal coming */
    WRP_EXT_HwDelay(500, EVENT_IsLastGasp);

	if (R_TCP_GetConnectionState(0) == TCP_DISCONNECTED)
	{
		g_tcp_connect_active_connected = FALSE;
		
		R_TCP_Connect(
			0,
			remote_port,
			remote_ip_address
		);
		
		/* Wait until connection establish with timeout */
        g_wrp_tcp_rx65n_p_condition = &g_tcp_connect_active_connected;
        WRP_EXT_HwDelay(3000, r_wrp_tcp_rx65n_waiting_predicate);
		result = (g_tcp_connect_active_connected == 1) ? TRUE : FALSE;
	}

	return result;
}

/******************************************************************************
* Function Name : R_TCP_WRP_TryCloseConnection
* Interface     : uint8_t R_TCP_WRP_TryCloseConnection(TcpPort remote_port, IpAddressPtr remote_ip_address)
* Description   : 
* Arguments     : TcpPort remote_port: remote port to disconnect
*               : IpAddressPtr remote_ip_address: remote IP address to disconnect
* Return Value  : uint8_t: TRUE or FALSE
*               : TRUE: already disconnected or disconnect successfully
*               : FALSE: disconnection failed
******************************************************************************/
uint8_t R_TCP_WRP_TryCloseConnection(TcpPort remote_port, IpAddressPtr remote_ip_address)
{
    volatile uint32_t count;
	volatile uint8_t result = FALSE;
    
    if (R_TCP_GetConnectionState(0) == TCP_CONNECTED)
    {
        g_tcp_connect_active_disconnected = FALSE;
        
        R_TCP_Disconnect(
            0,
            remote_port,
            remote_ip_address
        );
        
        /* Wait until connection establish with timeout */
        g_wrp_tcp_rx65n_p_condition = &g_tcp_connect_active_disconnected;
        WRP_EXT_HwDelay(3000, r_wrp_tcp_rx65n_waiting_predicate);
		result = (g_tcp_connect_active_disconnected == 1) ? TRUE : FALSE;
    }
    
	return result;
}

#endif /* #if defined(SUPPORT_TCP_PROFILE) && (SUPPORT_TCP_PROFILE == TRUE) && (TCP_MODE_SELECTION == TCP_MODE_ETHERNET_SERIAL_RX65N) */