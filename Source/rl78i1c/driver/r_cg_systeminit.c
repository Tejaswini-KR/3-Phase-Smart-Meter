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
* Copyright (C) 2015, 2017 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_systeminit.c
* Version      : Code Generator for RL78/I1C V1.01.00.02 [15 May 2017]
* Device(s)    : R5F10NPJ
* Tool-Chain   : CCRL
* Description  : This file implements system initializing function.
* Creation Date: 3/22/2019
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_lvd.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_tau.h"
#include "r_cg_wdt.h"
#include "r_cg_sau.h"
#include "r_cg_iica.h"
#include "r_cg_rtc.h"
#include "r_cg_dsadc.h"
#include "r_cg_mac32bit.h"
#include "r_cg_12adc.h"
#include "r_cg_dtc.h"
#include "r_cg_elc.h"
#include "r_cg_intp.h"
#include "r_cg_lcd.h"
/* Start user code for include. Do not edit comment generated here */
#include "bl_interrupt.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */

#ifdef __CCRL__

#pragma section bss RAMVect
INT_HANDLER RAM_ISR_Table[NUMBER_OF_ISR];

#endif /* __CCRL__ */ 

#ifdef __ICCRL78__

#pragma diag_suppress = Pm011
int __low_level_init(void);
#pragma diag_default = Pm011
void R_Systeminit(void);

extern INT_HANDLER RAM_ISR_Table[NUMBER_OF_ISR];
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

/* Set debug monitor 1 area */
#pragma location = 0x000CE
__root const __far uint8_t debugmon1[10] = 
    {0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU};

#endif /* __ICCRL78__ */

void R_RAM_InterruptVectorInit(void);
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
    R_PORT_Create();
    R_LVD_Create();
    R_CGC_Create();
    R_TAU0_Create();
    R_WDT_Create();
    R_SAU0_Create();
    R_SAU1_Create();
    R_IICA0_Create();
    R_RTC_Create();
    R_DSADC_Create();
    R_MAC32Bit_Create();
    R_12ADC_Create();
    R_DTC_Create();
    R_ELC_Create();
    R_INTC_Create();
    R_LCD_Create();
    IAWCTL = 0x80U;
}

/***********************************************************************************************************************
* Function Name: R_RAM_InterruptVectorInit
* Description  : This function initializes innterrupt RAM vector table
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_RAM_InterruptVectorInit(void)
{
    /* Assign the desired interrupt handler */
    RAM_ISR_Table[VECTOR_INDEX(INTWDTI)] = r_wdt_interrupt;
    RAM_ISR_Table[VECTOR_INDEX(INTIICA0)] = r_iica0_interrupt;
    /* No CSI30 interrupt vector assignation, it's being used by bootloader */
    //RAM_ISR_Table[VECTOR_INDEX(INTCSI30)] = R_CSI30_Interrupt;
    RAM_ISR_Table[VECTOR_INDEX(INTST0)] = r_uart0_interrupt_send;
    RAM_ISR_Table[VECTOR_INDEX(INTSR0)] = r_uart0_interrupt_receive;
    RAM_ISR_Table[VECTOR_INDEX(INTST2)] = r_uart2_interrupt_send;
    RAM_ISR_Table[VECTOR_INDEX(INTSR2)] = r_uart2_interrupt_receive;
    RAM_ISR_Table[VECTOR_INDEX(INTTM00)] = r_tau0_channel0_interrupt;
    RAM_ISR_Table[VECTOR_INDEX(INTRTCPRD)] = r_rtc_periodicinterrupt;
    RAM_ISR_Table[VECTOR_INDEX(INTDSAD)] = r_dsadc_interrupt;
    RAM_ISR_Table[VECTOR_INDEX(INTMACLOF)] = r_mac32bit_interrupt_flow;
    RAM_ISR_Table[VECTOR_INDEX(INTTM02)] = r_tau0_channel2_interrupt;
    RAM_ISR_Table[VECTOR_INDEX(INTP1)] = r_intc0_interrupt;
    RAM_ISR_Table[VECTOR_INDEX(INTP3)] = r_intc5_interrupt;
    RAM_ISR_Table[VECTOR_INDEX(INTRTCIC0)] = r_intrtcic0_interrupt;
    RAM_ISR_Table[VECTOR_INDEX(INTRTCIC1)] = r_intrtcic1_interrupt;
    RAM_ISR_Table[VECTOR_INDEX(INTRTCIC2)] = r_intrtcic2_interrupt;
    RAM_ISR_Table[VECTOR_INDEX(INTLVDEXLVD)] = r_lvd_exlvdinterrupt;
    RAM_ISR_Table[VECTOR_INDEX(INTLVI)] = r_lvd_exlvdinterrupt;
    RAM_ISR_Table[VECTOR_INDEX(INTLVDVDD)] = r_lvd_vddinterrupt;
    RAM_ISR_Table[VECTOR_INDEX(INTLVDVBAT)] = r_lvd_vbatinterrupt;
    RAM_ISR_Table[VECTOR_INDEX(INTLVDVRTC)] = r_lvd_vrtcinterrupt;
	RAM_ISR_Table[VECTOR_INDEX(INTRTCALM0)] = r_rtc_alarm0interrupt;
	RAM_ISR_Table[VECTOR_INDEX(INTRTCALM1)] = r_rtc_alarm1interrupt;
}

/***********************************************************************************************************************
* Function Name: hdwinit
* Description  : This function initializes hardware setting.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#if defined(__CCRL__)
void hdwinit(void)
{
    DI();
    R_Systeminit();
    R_RAM_InterruptVectorInit();
}
#endif /* __CCRL__ */

/***********************************************************************************************************************
* Function Name: __low_level_init
* Description  : This function initializes hardware setting.
* Arguments    : None
* Return Value : 1U -
*                    true
***********************************************************************************************************************/
#ifdef __ICCRL78__
#pragma diag_suppress = Pm011
int __low_level_init(void)
#pragma diag_default = Pm011
{
    DI();
    R_Systeminit();
    R_RAM_InterruptVectorInit();
    return (int)(1U);
}
#endif /* __ICCRL78__ */

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
