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
* File Name    : bl_r_systeminit.c
* Version      : 
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* Description  : This file implements system initializing function.
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
#include "bl_r_cg_cgc.h"
#include "bl_r_cg_port.h"
#include "bl_r_cg_sau.h"
#include "bl_r_cg_tau.h"
#include "bl_r_cg_lcd.h"
#include "bl_r_cg_lvd.h"
/* Start user code for include. Do not edit comment generated here */
#include "bl_header.h"
#include "bl_wrp_mcu.h"
#include "bl_interrupt.h"
/* End user code. Do not edit comment generated here */
#include "bl_r_cg_userdefine.h"


/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
#ifdef __ICCRL78__

/* Set option bytes */
#pragma location = "OPTBYTE"
__root const uint8_t opbyte0 = 0x7EU;
#pragma location = "OPTBYTE"
__root const uint8_t opbyte1 = 0x7FU;
#pragma location = "OPTBYTE"
__root const uint8_t opbyte2 = 0xE0U;
#pragma location = "OPTBYTE"
__root const uint8_t opbyte3 = 0x84U;

/* Set security ID */
#pragma location = "SECUID"
__root const uint8_t secuid[10] = 
    {0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U};

#endif
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Systeminit
* Description  : This function initializes every macro.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Systeminit(void)
{
    PIOR0 = 0x00U;
   // MCU_Delay(50000);   /* Delay 50ms */

    R_CGC_Create();
    R_PORT_StopCreate();
    R_SAU1_Create();
    R_TAU0_Create();
    //R_LCD_Create();
    
    /* Enable the VBAT */

    /* Enable Illegal access reset */
    IAWCTL = 0x80U;
}

/***********************************************************************************************************************
* Function Name: R_DefaultInterrupHandler
* Description  : This function used as default handler for interrupt vector.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DefaultInterrupHandler(void)
{
    /* Empty function */
}

/***********************************************************************************************************************
* Function Name: R_RAM_InterruptVectorInit
* Description  : This function initialize the RAM vector table for interrupt vector
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_RAM_InterruptVectorInit(void)
{
    uint8_t i;
    
    /* Set default handler for interrupt */
    for (i = 0; i < NUMBER_OF_ISR; i++)
    {
        RAM_ISR_Table[i] = R_DefaultInterrupHandler;
    }
    
    /* Assign the desired interrupt handler */
    RAM_ISR_Table[VECTOR_INDEX(INTCSI30)] = R_CSI30_Interrupt;
    RAM_ISR_Table[VECTOR_INDEX(INTST2)] = r_uart2_interrupt_send;
    RAM_ISR_Table[VECTOR_INDEX(INTSR2)] = r_uart2_interrupt_receive;
    RAM_ISR_Table[VECTOR_INDEX(INTTM00)] = r_tau0_channel0_interrupt;
    RAM_ISR_Table[VECTOR_INDEX(INTLVDVDD)] = r_lvd_vddinterrupt;

	
}

/***********************************************************************************************************************
* Function Name: bl_hdwinit
* Description  : This function initializes hardware setting for bootloader
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void bl_hdwinit(void)
{
    DI();
    R_Systeminit();
    R_RAM_InterruptVectorInit();
    EI();
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
