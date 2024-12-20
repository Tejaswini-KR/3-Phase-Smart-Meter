/******************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : wrp_app_iic.h
* Version      : 1.00
* Description  : Wrapper User IIC
******************************************************************************
* History : DD.MM.YYYY Version Description
******************************************************************************/

#ifndef _WRAPPER_APP_IIC_H
#define _WRAPPER_APP_IIC_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Macro definitions
******************************************************************************/
#define WRP_IIC_OK      0   /* OK */
#define WRP_IIC_ERROR   1   /* Error */

/* I/Fs mapping */
#define WRP_IIC_DRIVER_Init()                           {;}                                             /* IIC Initialization */
#define WRP_IIC_DRIVER_SendStart(addr, buf, size)       R_IICA0_Master_Send(addr, buf, size, 2)         /* IIC Send */
#define WRP_IIC_DRIVER_ReceiveStart(addr, buf, size)    R_IICA0_Master_Receive(addr, buf, size, 2)      /* IIC Recieve */

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/
/* IIC Wrapper Controller */
void    WRP_IIC_Init(void);                                                             /* Init */
uint8_t WRP_IIC_SendStart(uint8_t device_addr, uint8_t *buffer, uint16_t length);       /* Send Start */
uint8_t WRP_IIC_ReceiveStart(uint8_t device_addr, uint8_t *buffer, uint16_t length);        /* Receive Start */
uint8_t WRP_IIC_PollingWriteCycleStatus(uint8_t device_addr, uint16_t us_poll_interval, uint16_t poll_time);

/* 
 * Callback registration
 * Callback, put 2 below interfaces to the serial user callback
 *      Send End Callback   : WRP_IIC_SendEndCallback
 *      Receive End Callback: WRP_IIC_ReceiveEndCallback
 */
void    WRP_IIC_SendEndCallback(void);
void    WRP_IIC_ReceiveEndCallback(void);

#endif /* _WRAPPER_APP_IIC_H */
