/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2013, 2015 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : bl_wrp_user_spi.h
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : 
* Description  : SPI Wrapper Layer Source File
***********************************************************************************************************************/

#ifndef _WRAPPER_USER_SPI_H
#define _WRAPPER_USER_SPI_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "typedef.h"

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define WRP_SPI_OK      0   /* OK */
#define WRP_SPI_ERROR   1   /* Error */

/* I/Fs mapping */
#define WRP_SPI_DRIVER_Init()                           {;}                                     /* SPI Initialization */
#define WRP_SPI_DRIVER_Start()                          R_CSI30_Start()                         /* Start SPI */
#define WRP_SPI_DRIVER_Stop()                           R_CSI30_Stop()                          /* Stop SPI */
#define WRP_SPI_DRIVER_SendReceive(txbuf, num, rxbuf)   R_CSI30_Send_Receive(txbuf, num, rxbuf) /* SPI Send */

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/
/* SPI Wrapper Controller */
void    WRP_SPI_Init(void);                                                     /* Init */
void    WRP_SPI_Start(void);                                                    /* Start */
void    WRP_SPI_Stop(void);                                                     /* Stop */
uint8_t WRP_SPI_SendReceive(uint8_t *txbuf, uint16_t num, uint8_t *rxbuf);      /* Send Receive Start */

/* 
 * Callback registration
 * Callback, put 2 below interfaces to the serial user callback
 *      Send End Callback   : WRP_SPI_SendEndCallback
 *      Receive End Callback: WRP_SPI_ReceiveEndCallback
 */
void    WRP_SPI_SendEndCallback(void);
void    WRP_SPI_ReceiveEndCallback(void);

#endif /* _WRAPPER_USER_SPI_H */
