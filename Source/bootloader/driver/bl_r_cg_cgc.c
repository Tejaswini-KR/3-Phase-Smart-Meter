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
* File Name    : bl_r_cg_cgc.c
* Version      : 
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* Description  : This file implements device driver for CGC module.
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
/* Start user code for include. Do not edit comment generated here */
#include "bl_r_cg_sau.h"
#include "bl_r_cg_tau.h"
/* End user code. Do not edit comment generated here */
#include "bl_r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_CGC_Create
* Description  : This function initializes the clock generator.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CGC_Create(void)
{
    volatile uint16_t w_count;
    /* Can only set once */
    CMC = _40_CGC_HISYS_OSC | _10_CGC_SYSOSC_PERMITTED | _01_CGC_SYSOSC_OVER10M ;     
    
    /* Supply clock to access RTC domain register */
    VRTCEN = 1U;
    SCMC = _10_CGC_SUB_OSC | _02_CGC_NORMAL_OSCILLATION;
    
    XTSTOP = 0U;
    XT1SELDIS = 0U;
    
    /* Waiting time for sub clock stabilization */
    /* XT1 */
    for (w_count = 0U; w_count <= CGC_SUBWAITTIME; w_count++)
    {
        NOP();
    }
    
    /* Turn on fIH */
    HIOSTOP = 0;
    
    /* Select fMAIN as fCLK */
    CSS = 0U;
    
    /* Select fOCO as fMAIN */
    MCM0 = 0;
    
    /* Select fIH as fOCO */
    MCM1 = 0;
}

/* Start user code for adding. Do not edit comment generated here */
/******************************************************************************
* Function Name : BL_R_CGC_OperateAt24MHz
* Interface     : void BL_R_CGC_OperateAt24MHz(void)
* Description   : 
* Arguments     : None:
* Function Calls: 
* Return Value  : None
******************************************************************************/
void BL_R_CGC_OperateAtClock24M(void)
{
    HOCODIV = 0x00U;        /*  MCU operate at 24Mhz */
    BL_R_CGC_UpdateCPUClock();
}

/******************************************************************************
* Function Name : R_CGC_OperateAt12MHz
* Interface     : void R_CGC_OperateAt12MHz(void)
* Description   : 
* Arguments     : None:
* Function Calls: 
* Return Value  : None
******************************************************************************/
void BL_R_CGC_OperateAtClock12M(void)
{
    HOCODIV = 0x01U;        /*  MCU operate at 12Mhz */
    BL_R_CGC_UpdateCPUClock();
}

/******************************************************************************
* Function Name : R_CRC_OperateAt6MHz
* Interface     : void R_CRC_OperateAt6MHz(void)
* Description   : 
* Arguments     : None:
* Function Calls: 
* Return Value  : None
******************************************************************************/
void BL_R_CGC_OperateAtClock6M(void)
{
    HOCODIV = 0x02U;        /*  MCU operate at 6Mhz */
    BL_R_CGC_UpdateCPUClock();
}

void BL_R_CGC_UpdateCPUClock(void)
{
    /* Support HOCO clock only */
    if ((HIOSTOP + CSS + MCM0 + MCM1) == 0)
    {
        /* Currently not implemented, no driver need to change 
         * Serial flash is synchrnous
        */
    }
}
/* End user code. Do not edit comment generated here */
