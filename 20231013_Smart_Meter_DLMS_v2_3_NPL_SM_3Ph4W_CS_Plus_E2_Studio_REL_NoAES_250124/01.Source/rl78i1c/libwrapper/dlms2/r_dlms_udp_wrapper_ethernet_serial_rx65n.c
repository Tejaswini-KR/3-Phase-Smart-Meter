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
* File Name    : r_dlms_udp_wrapper_ethernet_serial_rx65n.c
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

#include "typedef.h"
#include "wrp_app_mcu.h"
#include "wrp_app_uart.h"
#include "r_dlms_config.h"
#include "r_dlms_udp_wrapper.h"
#include "r_dlms_udp_wrapper_interface.h"
#include "r_dlms_com_wrapper_config.h"
#include <string.h>

#if defined(SUPPORT_UDP_PROFILE) && (SUPPORT_UDP_PROFILE == TRUE) && (UDP_MODE_SELECTION == UDP_MODE_ETHERNET_SERIAL_RX65N)

/******************************************************************************
Macro definitions
******************************************************************************/

#define R_WRP_UDP_DEVICE_MODE_SEND				0
#define R_WRP_UDP_DEVICE_MODE_RECEIVE			1

/* Frame format */

/* Frame data */
// | [Frame format] | IP version   | Protocol  | Port    | Address    | Length  | Data      |
// | 5 bytes        | 2 bytes      | 1 byte    | 2 bytes | 4/16 bytes | 2 bytes | n (bytes) |
// | "!send"        | 0x0800: IPv4 | 0x06: TCP |         |            |         |           |
// | "!data"        | 0x86DD: IPv6 | 0x11: UDP |         |            |         |           |

/* Frame status */
// | [Frame format] | Length  | Data      |
// | 5 bytes        | 2 bytes | n (bytes) |
// | "!stat"        |         |           |

/* Frame configure read/write */
// | [Frame format] |   Code     | Length  | Data      |
// | 5 bytes        |            | 2 bytes | n (bytes) |
// | "!cfgr"        |            |         |           |


#define UDP_DEVICE_DATA_CMD_BUFFER_SIZE		(5 + 2 + 1 + 2 + 16 + 2)


#define R_WRP_IP_TYPE_IPv4			(0x0800)
#define R_WRP_IP_TYPE_IPv6		    (0x86DD)

#define UDP_WRP_PROTOCOL_UDP		(0x11)
#define UDP_WRP_PROTOCOL_TCP		(0x06)

#define UDP_WRAPPER_RECEIVER_STEP_FRAMETYPE_LENGTH  (5)

#define R_WRP_IP_TYPE_USING         (R_WRP_IP_TYPE_IPv4)
#define UDP_WRP_PROTCOL_USING       (UDP_WRP_PROTOCOL_UDP)

#if R_WRP_IP_TYPE_USING == R_WRP_IP_TYPE_IPv4
#define R_WRP_UDP_IP_ADDR_SIZE					(4)
#elif R_WRP_IP_TYPE_USING == R_WRP_IP_TYPE_IPv6
#define R_WRP_UDP_IP_ADDR_SIZE					(16)
#endif

#define		UDP_EUI64_ADDRESS_SIZE	8


#define		UDP_DEVICE_DATA_RECEIVER_INTERFRAME			100
#define R_WRP_SENDING_TIMEOUT_DEFAULT                       (2000)


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

#define R_WRP_RECEIVER_RESET(p_receiver)	{							\
					(p_receiver)->step = UDP_WRAPPER_RECEIVER_STEP_SOF;		\
                    (p_receiver)->step_end_pos = 0;                             \
                    (p_receiver)->byte_count = 0;                               \
                    (p_receiver)->total_byte_count = 0;                         \
}

#define PUT_UINT8_TO_BUFF(buff, uint8num)	{ *buff++ = uint8num; }
#define PUT_UINT16_TO_BUFF(buff, uint16num)	{ *buff++ = (uint8_t)((uint16num & 0xFF00) >> 8);  *buff++ = (uint8_t)uint16num; }

#define SWAP_UINT16(number)		{ number = (number>> 8) | (number << 8);}

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef struct
{
	uint16_t	initial;
	uint16_t	count;
	uint16_t	enable;
} UDPDeviceTimeoutChannel_t;

typedef uint8_t UDPDeviceMode_t;

typedef enum tag_R_Wrp_Frame_Service_t
{
	R_WRP_SERVICE_REQ = 1,
	R_WRP_SERVICE_IND = 2,
	R_WRP_SERVICE_RES = 3,
	R_WRP_SERVICE_CNF = 4
} R_Wrp_Frame_Type_t;

typedef struct tagFrameData
{
	uint8_t	*p_ip_type;
	uint8_t	*p_protocol;
	uint8_t	*p_port;
	union
	{
		uint8_t *p_ipv4;
		uint8_t *p_ipv6;
	};
} WRP_FrameData_t;

typedef struct tagFrameCommand
{
	union{
		struct
		{
			uint8_t code;
		} tcp_cfg_read;

		struct
		{
			uint8_t code;
		} tcp_cfg_write;
	};
} WRP_FrameCommand_t;

typedef struct tagFrameStatus
{
	uint16_t length;
} WRP_FrameStatus_t;

typedef struct tagFrameConfigureRead
{
	uint8_t code;
} WRP_FrameConfigureRead_t;

typedef struct tagFrameConfigureWrite
{
	uint8_t code;
	uint8_t length;
} WRP_FrameConfigureWrite_t;

typedef struct tagWrapperFrameHeader
{
	union
	{
		WRP_FrameData_t                   frame_data;
		WRP_FrameCommand_t                frame_command;
		WRP_FrameStatus_t                 frame_status;
		WRP_FrameConfigureRead_t          frame_configure_read;
		WRP_FrameConfigureWrite_t         frame_configure_write;
	};
} WRP_FrameHeader_t;

typedef struct tagFrameTypeDefinition
{
	uint8_t     arg[5];
	uint8_t     frametype;
	uint8_t     next_step;
	uint16_t    next_step_length;
} WRP_FrameFormatDefinition_t;

typedef struct tagFrame_IP_Type_Definition
{
	uint8_t     arg[2];
	uint8_t     frametype;
	uint8_t     next_step;
	uint16_t    next_step_length;
} WRP_FrameIPTypeDefinition_t;

typedef struct tagUDPWrapperReceiver
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
    
    uint8_t * p_reason_buff;
	uint16_t length;
    
} UDPDeviceReceiver_t;


/*
 * ENUM
 */
typedef enum tagWrpFrameType
{
	WRP_FRAME_DATA = 0,
	WRP_FRAME_SEND,
	WRP_FRAME_STATUS,
	WRP_FRAME_CONFIGURE_READ,
	WRP_FRAME_CONFIGURE_WRITE,
} WrpFrameType_t;


typedef enum Tag_UDP_Wrapper_Receiver_Step_t
{
	UDP_WRAPPER_RECEIVER_STEP_SOF  = 0,
	UDP_WRAPPER_RECEIVER_STEP_FRAMETYPE,
	UDP_WRAPPER_RECEIVER_STEP_IP_TYPE,
	UDP_WRAPPER_RECEIVER_STEP_PROTOCOL,
	UDP_WRAPPER_RECEIVER_STEP_PORT,
	UDP_WRAPPER_RECEIVER_STEP_SERVICE_CODE,
	UDP_WRAPPER_RECEIVER_STEP_IP_ADDRESS,
	UDP_WRAPPER_RECEIVER_STEP_DATA_LENGTH,
	UDP_WRAPPER_RECEIVER_STEP_DATA_BUFFER,
	UDP_WRAPPER_RECEIVER_STEP_CONFIGURE_READ_CODE,
	UDP_WRAPPER_RECEIVER_STEP_CONFIGURE_WRITE_CODE,
	UDP_WRAPPER_RECEIVER_STEP_CONFIGURE_WRITE_LENGTH,
	UDP_WRAPPER_RECEIVER_STEP_CONFIGURE_WRITE_DATA
} UDP_Wrapper_Receiver_Step_t;

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/
//  extern UdpServiceData g_udp_server;
/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/******************************************************************************
Private global variables and functions
******************************************************************************/

/* Private variable */

volatile uint8_t   g_wrp_udp_local_ip_addr_buffer[R_WRP_UDP_IP_ADDR_SIZE];
volatile IpAddress g_wrp_udp_local_ip_addr = { (uint8_t *)g_wrp_udp_local_ip_addr_buffer, R_WRP_UDP_IP_ADDR_SIZE };

/*
 * Remote ip address stored in g_wrp_udp_receiver0 in below.
 */

volatile uint8_t			g_udp_device_send_end				= TRUE;							/* Send end */
UDPDeviceMode_t				g_udp_device_mode					= R_WRP_UDP_DEVICE_MODE_SEND;	/* 0: Sending mode, 1: receiving mode */
UDPDeviceReceiver_t			g_wrp_udp_receiver0;

uint8_t								g_udp_device_data_cmd_buffer[UDP_DEVICE_DATA_CMD_BUFFER_SIZE];
volatile UDPDeviceTimeoutChannel_t	g_udp_device_interframe_timeout;

static volatile UDPDeviceTimeoutChannel_t	g_sending_timeout;
static volatile uint8_t g_sending_timeout_indication = FALSE;
static volatile uint8_t g_sending_confirm_received = FALSE;

static volatile uint8_t g_config_read_confirm_received = FALSE;
static volatile uint8_t g_config_write_confirm_received = FALSE;

uint16_t					g_udp_device_ip_type;

uint16_t					g_udp_device_remoteport;
uint8_t						g_udp_device_remoteip[4];

uint16_t					g_udp_device_frame_length;

const WRP_FrameFormatDefinition_t FRAMETYPE_LIST[] = 
{
	{ "!data",  WRP_FRAME_DATA,                 UDP_WRAPPER_RECEIVER_STEP_IP_TYPE                   , 2 },
	{ "!send",  WRP_FRAME_SEND,                 UDP_WRAPPER_RECEIVER_STEP_IP_TYPE                   , 2 },
	{ "!cfgr",  WRP_FRAME_CONFIGURE_READ,       UDP_WRAPPER_RECEIVER_STEP_CONFIGURE_READ_CODE       , 1 },
	{ "!cfgw",  WRP_FRAME_CONFIGURE_WRITE,      UDP_WRAPPER_RECEIVER_STEP_CONFIGURE_WRITE_CODE      , 1 },
};
const uint16_t FRAMETYPE_LIST_SIZE = sizeof(FRAMETYPE_LIST)/sizeof(WRP_FrameFormatDefinition_t);


/* Private fucntion */
EXTERN_C uint8_t R_WRP_UDP_DEVICE_Send_FrameData(UdpChannel udp_channel, uint8_t * p_frame_name, UdpPort remote_udp_port, IpAddressPtr remote_ip_address, uint8_t *data, uint16_t length);
EXTERN_C uint8_t R_WRP_UDP_DEVICE_ReceiveData(UdpChannel udp_channel, uint8_t data);

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
		WRP_UART0_Init();
		WRP_UART0_SetBaudRate(WRP_UART_BAUD_RATE_19200);
		WRP_UART0_ConfigHDLCProtocol();
		WRP_UART0_Start();

		g_udp_device_send_end   = TRUE;
		g_udp_device_mode       = R_WRP_UDP_DEVICE_MODE_SEND;

		g_udp_device_interframe_timeout.enable = FALSE;
		g_udp_device_interframe_timeout.count = 0;

		memset(g_udp_device_data_cmd_buffer, 0, UDP_DEVICE_DATA_CMD_BUFFER_SIZE);

		g_wrp_udp_local_ip_addr.p_addr = (uint8_t *)g_wrp_udp_local_ip_addr_buffer;
		g_wrp_udp_local_ip_addr.size = R_WRP_UDP_IP_ADDR_SIZE;
		g_wrp_udp_receiver0.header.remote_ip_addr.p_addr = g_wrp_udp_receiver0.header.ip;
		g_wrp_udp_receiver0.header.remote_ip_addr.size = R_WRP_UDP_IP_ADDR_SIZE;
		g_wrp_udp_receiver0.buff 		= g_udp_device_data_cmd_buffer;
		g_wrp_udp_receiver0.buff_length = UDP_DEVICE_DATA_CMD_BUFFER_SIZE;
		R_WRP_RECEIVER_RESET(&g_wrp_udp_receiver0);

		g_udp_device_interframe_timeout.enable = FALSE;
		g_udp_device_interframe_timeout.count = 0;
		g_udp_device_interframe_timeout.initial = UDP_DEVICE_DATA_RECEIVER_INTERFRAME;

        /* Sending timeout */
        g_sending_timeout.enable = FALSE;
        g_sending_timeout.count = 0;
        g_sending_timeout.initial = R_WRP_SENDING_TIMEOUT_DEFAULT;
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
	if (udp_channel == 0) {

		/* Cmd Receiving mode */
		g_udp_device_mode = R_WRP_UDP_DEVICE_MODE_RECEIVE;
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
		/* Do nothing */
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
    uint32_t count;
    uint8_t config_code;
    uint8_t link_status;
    
    if (udp_channel != 0)
    {
        return FALSE;
    }
    
    /* Configure code: port + IP */
    config_code = 0x02;
    g_config_read_confirm_received = FALSE;
	R_WRP_UDP_DEVICE_Send_FrameData(udp_channel, (uint8_t *)FRAMETYPE_LIST[2].arg, p_config->local_udp_port, p_config->local_ip_address, &config_code, 1);
	
    /* Wait until receive cfgr confirm from module */
    count = 100;
    while (g_config_read_confirm_received == FALSE)
    {
        MCU_Delay(10000);
        R_WDT_Restart();
        
        count--;
        if (count == 0)
        {
            break;
        }
    }
    
    if (count == 0)
    {
        return FALSE;
    }
    else
    {
        if (g_wrp_udp_receiver0.p_reason_buff != NULL)
        {
            link_status = g_wrp_udp_receiver0.p_reason_buff[2];
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
	R_WRP_UDP_DEVICE_Send_FrameData(udp_channel, (uint8_t *)FRAMETYPE_LIST[2].arg, p_config->local_udp_port, p_config->local_ip_address, &config_code, 1);
    
    /* Wait until receive cfgr confirm from module */
    count = 100;
    while (g_config_read_confirm_received == FALSE)
    {
        MCU_Delay(10000);
        R_WDT_Restart();
        
        count--;
        if (count == 0)
        {
            break;
        }
    }
    
    if (count == 0)
    {
        return FALSE;
    }
    else
    {
		memcpy((void *)g_wrp_udp_local_ip_addr_buffer, g_wrp_udp_receiver0.header.ip, R_WRP_UDP_IP_ADDR_SIZE);
		g_wrp_udp_local_ip_addr.p_addr = (uint8_t *)g_wrp_udp_local_ip_addr_buffer;
		g_wrp_udp_local_ip_addr.size = R_WRP_UDP_IP_ADDR_SIZE;
		p_config->local_ip_address = (IpAddressPtr)&g_wrp_udp_local_ip_addr;
        p_config->local_udp_port = g_wrp_udp_receiver0.header.port;
    }
    
	return TRUE;
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
    uint32_t count;
    uint8_t config_code;
    
    if (udp_channel != 0)
    {
        return FALSE;
    }
    
    /* Configure port + IP */
    config_code = 0x01;
    
    g_config_write_confirm_received = FALSE;
    
    R_WRP_UDP_DEVICE_Send_FrameData(udp_channel, (uint8_t *)FRAMETYPE_LIST[3].arg, p_config->local_udp_port, p_config->local_ip_address, &config_code, 1);

    /* Wait until receive cfgw confirm from module */
    count = 100;
    while (g_config_write_confirm_received == FALSE)
    {
        MCU_Delay(10000);
        R_WDT_Restart();
        
        count--;
        if (count == 0)
        {
            break;
        }
    }
    
    if (count == 0)
    {
        return FALSE;
    }
    
	return TRUE;
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
	// if (udp_channel == 0) 
	// {
	//     WRP_UART0_SendData(data, length);
	// }

	R_WRP_UDP_DEVICE_Send_FrameData(udp_channel, (uint8_t *)FRAMETYPE_LIST[1].arg, remote_udp_port, remote_ip_address, data, length);
	
	return 0;
}

/******************************************************************************
* Function Name : R_WRP_UDP_DEVICE_Send_FrameData
* Interface     : uint8_t R_WRP_UDP_DEVICE_Send_FrameData(
*               :     UdpChannel udp_channel,
*               :     UdpPort remote_udp_port,
*               :     IpAddress remote_ip_address,
*               :     uint8_t *data,
*               :     uint16_t length
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_WRP_UDP_DEVICE_Send_FrameData(UdpChannel udp_channel, uint8_t * p_frame_name, UdpPort remote_udp_port, IpAddressPtr remote_ip_address, uint8_t *data, uint16_t length)
{
	uint8_t	 cmd_buffer[5 + 2 + 1 + 2 + R_WRP_UDP_IP_ADDR_SIZE + 4];
	uint8_t  *p_cmd = cmd_buffer;
	uint16_t cmd_length;

	void (*wrp_send_function)(uint8_t *buffer, uint16_t length);

	uint8_t i;

	uint16_t ip_type;
	uint16_t protocol;
	uint16_t port;

	if (udp_channel == 0)
	{
		wrp_send_function = R_UDP_DEVICE_SendBuffer;
	}
	
	/* Cmd Sending mode */
	g_udp_device_mode = R_WRP_UDP_DEVICE_MODE_SEND;
	
	/* Create header */
	ip_type    = R_WRP_IP_TYPE_USING;
	protocol   = UDP_WRP_PROTCOL_USING;
	port       = remote_udp_port;

	/* !data */
	memcpy(p_cmd, p_frame_name, 5 );
	p_cmd += 5;

	/* !ip_type */
	PUT_UINT16_TO_BUFF(p_cmd, ip_type);

	/* Protocol */
	PUT_UINT8_TO_BUFF(p_cmd, protocol);

	/* Port */
	PUT_UINT16_TO_BUFF(p_cmd, port);

	/* IP address */
	if (remote_ip_address->size != R_WRP_UDP_IP_ADDR_SIZE) {
		return 1;	/* Ip address size note suitable */
	}
	#if (defined(R_WRP_IP_TYPE_USING))
		memcpy(p_cmd, remote_ip_address->p_addr, R_WRP_UDP_IP_ADDR_SIZE);
		p_cmd += R_WRP_UDP_IP_ADDR_SIZE;
	#endif /* R_WRP_IP_TYPE_USING */
    
	/* [Service code] */
	PUT_UINT8_TO_BUFF(p_cmd, R_WRP_SERVICE_REQ);

	/* length */
	PUT_UINT16_TO_BUFF(p_cmd, length);

	cmd_length = (uint16_t)(p_cmd - cmd_buffer);
	wrp_send_function(cmd_buffer, cmd_length);

	/* Send data */
	wrp_send_function(data, length);

	/* Cmd Sending mode */
	g_udp_device_mode = R_WRP_UDP_DEVICE_MODE_RECEIVE;
    
    R_WRP_RESET_INTERFRAME_TIMEOUT(g_sending_timeout);
    g_sending_confirm_received = FALSE;
    g_sending_timeout_indication = FALSE;
    while (g_sending_confirm_received == FALSE)
    {
        if (g_sending_timeout_indication == TRUE)
        {
            break;
        }
        R_WDT_Restart();
    }
    
    /* No confirm received, inform DLMS library send end also */
    if (g_sending_timeout_indication == TRUE)
    {
        R_UDP_DeviceSendEnd(udp_channel);
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
	uint8_t i;
	UDPDeviceReceiver_t * p_receiver = NULL;

	uint8_t frame_OK = FALSE;

	uint16_t ip_type;
	

	// Check validity
	{
		if (channel == 0) 
		{
			p_receiver = &g_wrp_udp_receiver0;
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

	// uint8_t		*gp_udp_device_cmd_response_buffer = NULL;      /* Buffer to store the UDP module cmd response */
	// uint16_t		g_udp_device_cmd_response_count = 0;            /* Counter for cmd response buffer */
	// uint16_t		g_udp_device_cmd_response_length = 0;           /* Counter for cmd response length */

	// /* Wait command reply from UDP module */
	// if (g_udp_device_mode == R_WRP_UDP_DEVICE_MODE_SEND)
	// {
	// 	if (gp_udp_device_cmd_response_buffer != NULL &&
	// 		g_udp_device_cmd_response_count < g_udp_device_cmd_response_length) {
	// 		gp_udp_device_cmd_response_buffer[g_udp_device_cmd_response_count++] = received_byte;
	// 	}
	// 	return;
	// }

	/*
	 * Receive & decode the !data node_ip4 length data_bytes
	 * Bring data to upper layer on receiving mode
	 */
    R_WRP_RESET_INTERFRAME_TIMEOUT(g_udp_device_interframe_timeout);
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
		case UDP_WRAPPER_RECEIVER_STEP_SOF:
			if (received_byte == '!' && p_receiver->step_end_pos == 0)
			{
				p_receiver->step = UDP_WRAPPER_RECEIVER_STEP_FRAMETYPE;
				p_receiver->step_end_pos = 5;
			}
			else
			{
				R_WRP_RECEIVER_RESET(p_receiver);
			}
			break;
		case UDP_WRAPPER_RECEIVER_STEP_FRAMETYPE:
			if (p_receiver->total_byte_count >= p_receiver->step_end_pos)
			{
				frame_OK = FALSE;
				for(i = 0; i < FRAMETYPE_LIST_SIZE; i++)
				{
					if (memcmp(p_receiver->buff, FRAMETYPE_LIST[i].arg , 5) == 0)
					{
						p_receiver->step          = UDP_WRAPPER_RECEIVER_STEP_IP_TYPE;
						p_receiver->step_end_pos += 2;
						p_receiver->header.p_frametype = FRAMETYPE_LIST[i].arg;
                        
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

		case UDP_WRAPPER_RECEIVER_STEP_IP_TYPE:
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
					p_receiver->step          = UDP_WRAPPER_RECEIVER_STEP_PROTOCOL;
					p_receiver->step_end_pos += 1;
				}
				else
				{
					R_WRP_RECEIVER_RESET(p_receiver);
				}
			}
			break;
		case UDP_WRAPPER_RECEIVER_STEP_PROTOCOL:
			if (p_receiver->total_byte_count >= p_receiver->step_end_pos)
			{
				p_receiver->header.protocol = received_byte;

				/* Next step */
				p_receiver->step          = UDP_WRAPPER_RECEIVER_STEP_PORT;
				p_receiver->step_end_pos += 2;
			}
			break;

		case UDP_WRAPPER_RECEIVER_STEP_PORT:
			if (p_receiver->total_byte_count >= p_receiver->step_end_pos)
			{
				memcpy(&p_receiver->header.port, &p_receiver->buff[p_receiver->step_end_pos - 2] , 2);
				SWAP_UINT16(p_receiver->header.port);

				/* Next step */
				p_receiver->step          = UDP_WRAPPER_RECEIVER_STEP_IP_ADDRESS;

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

		case UDP_WRAPPER_RECEIVER_STEP_IP_ADDRESS:
			if (p_receiver->total_byte_count >= p_receiver->step_end_pos)
			{
                memcpy(
                    p_receiver->header.ip, 
                    &p_receiver->buff[p_receiver->step_end_pos - p_receiver->header.ip_bytes_to_receive], 
                    p_receiver->header.ip_bytes_to_receive
                    );

				p_receiver->header.remote_ip_addr.p_addr = p_receiver->header.ip;
				p_receiver->header.remote_ip_addr.size = R_WRP_UDP_IP_ADDR_SIZE;

				p_receiver->step = UDP_WRAPPER_RECEIVER_STEP_SERVICE_CODE;
				p_receiver->step_end_pos += 1;
			}
			break;

		case UDP_WRAPPER_RECEIVER_STEP_SERVICE_CODE:
			if (p_receiver->total_byte_count >= p_receiver->step_end_pos)
			{
				p_receiver->header.service_code = received_byte;

				p_receiver->step = UDP_WRAPPER_RECEIVER_STEP_DATA_LENGTH;
				p_receiver->step_end_pos += 2;
			}
			break;

		case UDP_WRAPPER_RECEIVER_STEP_DATA_LENGTH:
			if (p_receiver->total_byte_count >= p_receiver->step_end_pos)
			{
				memcpy(
                    (uint8_t *)&p_receiver->length, 
                    &p_receiver->buff[p_receiver->step_end_pos - 2], 
                    2
                );
				SWAP_UINT16(p_receiver->length);
                
				p_receiver->step = UDP_WRAPPER_RECEIVER_STEP_DATA_BUFFER;
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

		case UDP_WRAPPER_RECEIVER_STEP_DATA_BUFFER:
            if (p_receiver->header.service_code == R_WRP_SERVICE_IND)
            {
    			R_UDP_DeviceReceiveEnd(
    				(UdpChannel)	channel,
    				(UdpPort)		4059,
    				(IpAddressPtr)	&p_receiver->header.remote_ip_addr,
    				(uint8_t *)		&received_byte,
    				(uint16_t)		1
    			);
            }
            
            if ((p_receiver->total_byte_count >= p_receiver->step_end_pos))
			{
                if (p_receiver->header.p_frametype != FRAMETYPE_LIST[0].arg)
                {
                    if (p_receiver->length >= 1 && p_receiver->length < 16)
                    {
                        p_receiver->p_reason_buff = &p_receiver->buff[p_receiver->step_end_pos - p_receiver->length];
                    }
                    else
                    {
                        p_receiver->p_reason_buff = NULL;
                    }
                    
                }
                
                if (p_receiver->header.p_frametype == FRAMETYPE_LIST[1].arg && p_receiver->header.service_code == R_WRP_SERVICE_CNF)
                {
                    g_sending_confirm_received = TRUE;
                	/* ACK to upper layer */
                	R_UDP_DeviceSendEnd(channel);
                }
                else if (p_receiver->header.p_frametype == FRAMETYPE_LIST[2].arg)
                {
                    g_sending_confirm_received = TRUE;
                    if (p_receiver->header.service_code == R_WRP_SERVICE_CNF)
                    {
                        g_config_read_confirm_received = TRUE;
                    }
                }
                else if (p_receiver->header.p_frametype == FRAMETYPE_LIST[3].arg)
                {
                    g_sending_confirm_received = TRUE;
                    if (p_receiver->header.service_code == R_WRP_SERVICE_CNF)
                    {
                        g_config_write_confirm_received = TRUE;
                    }
                }
                
                R_WRP_STOP_INTERFRAME_TIMEOUT(g_udp_device_interframe_timeout);
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
void R_UDP_WRP_ReceiverInterframeTimeout_Callback(void)
{
    R_WRP_STOP_INTERFRAME_TIMEOUT(g_udp_device_interframe_timeout);
	R_WRP_RECEIVER_RESET(&g_wrp_udp_receiver0);
}

/******************************************************************************
* Function Name : R_UDP_WRP_SendingTimeout_Callback
* Interface     : void R_UDP_WRP_SendingTimeout_Callback(void)
* Description   : 
* Arguments     : None:
* Function Calls: 
* Return Value  : None
******************************************************************************/
void R_UDP_WRP_SendingTimeout_Callback(void)
{
    R_WRP_STOP_INTERFRAME_TIMEOUT(g_sending_timeout);
    g_sending_timeout_indication = TRUE;
}

/******************************************************************************
* Function Name : R_UDP_WRP_ReceiverTimeoutMilisecond
* Interface     : void R_UDP_WRP_ReceiverTimeoutMilisecond(void)
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
			R_UDP_WRP_ReceiverInterframeTimeout_Callback();
		}
	}
    
    if (g_sending_timeout.enable == TRUE) {
		if (g_sending_timeout.count > 0) {
			g_sending_timeout.count--;
		}
		else {
			R_UDP_WRP_SendingTimeout_Callback();
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
#endif /* #if defined(SUPPORT_UDP_PROFILE) && (SUPPORT_UDP_PROFILE == TRUE) && (UDP_MODE_SELECTION == UDP_MODE_ETHERNET_SERIAL_RX65N) */