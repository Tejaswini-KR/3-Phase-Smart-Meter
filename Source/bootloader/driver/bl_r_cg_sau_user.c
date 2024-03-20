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
* File Name    : bl_r_cg_sau_user.c
* Version      : 
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* Description  : This file implements device driver for SAU module.
* Creation Date: 
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "bl_r_cg_macrodriver.h"
#include "bl_r_cg_sau.h"
/* Start user code for include. Do not edit comment generated here */
#include "bl_header.h"
#include "bl_wrp_user_spi.h"
/* End user code. Do not edit comment generated here */
#include "bl_r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint8_t  *gp_Csi30RxAddress;    /* csi00 receive buffer address */
extern volatile uint16_t g_Csi30RxLen;      /* csi00 receive data length */
extern volatile uint16_t g_Csi30RxCnt;      /* csi00 receive data count */
extern volatile uint8_t  *gp_Csi30TxAddress;    /* csi00 send buffer address */
extern volatile uint16_t g_Csi30TxLen;      /* csi00 send data length */
extern volatile uint16_t g_Csi30TxCnt;      /* csi00 send data count */

extern volatile uint8_t * gp_uart2_tx_address;         /* uart2 send buffer address */
extern volatile uint16_t  g_uart2_tx_count;            /* uart2 send data number */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**  This function is INTCSI00 interrupt service routine.
**
**  Parameters:
**  None
**
**  Returns:
**  None
**
**-----------------------------------------------------------------------------
*/
void R_CSI30_Interrupt(void)
{
    uint8_t err_type;

    err_type = (uint8_t)(SSR12 & 0x0007U);
    SIR12 = (uint16_t)err_type;
    if (err_type != 1U)
    {
        if (g_Csi30TxCnt > 0U)
        {
            *gp_Csi30RxAddress = SIO30;
            gp_Csi30RxAddress++;
            SIO30 = *gp_Csi30TxAddress;
            gp_Csi30TxAddress++;
            g_Csi30TxCnt--;     
        }
        else
        {
            if (g_Csi30TxCnt == 0U)
            {
                *gp_Csi30RxAddress = SIO30;
            }
            R_CSI30_Callback_SendEnd(); /* complete send */
            R_CSI30_Callback_ReceiveEnd();  /* complete receive */
        }
    }
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**  This function is a callback function when CSI00 finishes reception.
**
**  Parameters:
**  None
**
**  Returns:
**  None
**
**-----------------------------------------------------------------------------
*/
void R_CSI30_Callback_ReceiveEnd(void)
{
    /* Start user code. Do not edit comment generated here */
    WRP_SPI_SendEndCallback();
    /* End user code. Do not edit comment generated here */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**  This function is a callback function when CSI00 finishes transmission.
**
**  Parameters:
**  None
**
**  Returns:
**  None
**
**-----------------------------------------------------------------------------
*/
void R_CSI30_Callback_SendEnd(void)
{
    /* Start user code. Do not edit comment generated here */
    WRP_SPI_ReceiveEndCallback();
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_uart2_interrupt_send
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_uart2_interrupt_send(void)
{
    EI();
    if (g_uart2_tx_count > 0U)
    {
        TXD2 = *gp_uart2_tx_address;
        gp_uart2_tx_address++;
        g_uart2_tx_count--;
    }
    else
    {
        BL_RECOVERY_UartSendEndCallBack();
    }
}

/***********************************************************************************************************************
* Function Name: r_uart2_interrupt_receive
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_uart2_interrupt_receive(void)
{
    uint8_t err_type;
        
    EI();
    
    err_type = (uint8_t)(SSR11 & 0x0007U);
    SIR11 = (uint16_t)err_type;

    if (err_type != 0U)
    {
        r_uart2_callback_error(err_type);
    }
    
    BL_RECOVERY_UartReceivedEndCallBack(RXD2);
}

/***********************************************************************************************************************
* Function Name: r_uart2_callback_error
* Description  : This function is a callback function when UART2 reception error occurs.
* Arguments    : err_type -
*                    error type value
* Return Value : None
***********************************************************************************************************************/
static void r_uart2_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
