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
* File Name    : bl_wrp_user_spi.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : 
* Description  : SPI Wrapper Layer Source File
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Driver */
#include "bl_r_cg_macrodriver.h"    /* Macro Driver Definitions */
#include "bl_r_cg_sau.h"            /* Serial Device Driver */

/* Wrapper/User */
#include "bl_wrp_user_spi.h"        /* Wrapper SPI header */

/* Application */
#include "bl_header.h"
#include "bl_serialflash.h"

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro Definitions Checking
***********************************************************************************************************************/

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name    : void WRP_SPI_Init(void)
* Description      : SPI Initialization
* Arguments        : None
* Functions Called : WRP_SPI_DRIVER_Init()
* Return Value     : None
***********************************************************************************************************************/
void WRP_SPI_Init(void)
{
    WRP_SPI_DRIVER_Init();
}

/***********************************************************************************************************************
* Function Name    : void WRP_SPI_Start(void)
* Description      : SPI driver start
* Arguments        : None
* Functions Called : WRP_SPI_DRIVER_Start()
* Return Value     : None
***********************************************************************************************************************/
void WRP_SPI_Start(void)
{
    WRP_SPI_DRIVER_Start();
}

/***********************************************************************************************************************
* Function Name    : void WRP_SPI_Init(void)
* Description      : SPI driver stop
* Arguments        : None
* Functions Called : WRP_SPI_DRIVER_Stop()
* Return Value     : None
***********************************************************************************************************************/
void WRP_SPI_Stop(void)
{
    WRP_SPI_DRIVER_Stop();
}

/***********************************************************************************************************************
* Function Name : WRP_SPI_SendReceive
* Interface     : uint8_t WRP_SPI_SendReceive(uint8_t *txbuf, uint16_t num, uint8_t *rxbuf)
* Description   : SPI Send Receive Start
* Arguments     : uint8_t * txbuf: Pointer to tx buf
*               : uint16_t num   : Number of byte transmit receive
*               : uint8_t * rxbuf: Pointer to rx buf
* Function Calls: WRP_SPI_DRIVER_SendReceive
* Return Value  : uint8_t, return code
***********************************************************************************************************************/
uint8_t WRP_SPI_SendReceive(uint8_t *txbuf, uint16_t num, uint8_t *rxbuf)
{
    if (WRP_SPI_DRIVER_SendReceive(txbuf, num, rxbuf) != MD_OK)
    {
        return WRP_SPI_ERROR;
    }
    else
    {
        return WRP_SPI_OK;
    }
}

/***********************************************************************************************************************
* Function Name    : void WRP_SPI_SendEndCallback(void)
* Description      : SPI Wrapper Send End Callback
* Arguments        : None
* Functions Called : None
* Return Value     : None
***********************************************************************************************************************/
void WRP_SPI_SendEndCallback(void)
{
    /* Put application callback here */
    SFL_SendEndCallback();
}

/***********************************************************************************************************************
* Function Name    : void WRP_SPI_ReceiveEndCallback(void)
* Description      : SPI Wraper Receive End Callback
* Arguments        : None
* Functions Called : None
* Return Value     : None
***********************************************************************************************************************/
void WRP_SPI_ReceiveEndCallback(void)
{
    /* Put application callback here */
    SFL_ReceiveEndCallback();
}

