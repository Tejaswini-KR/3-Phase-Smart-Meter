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
* File Name    : load_test.c
* Version      : 
* Device(s)    : R5F10NPJ
* Tool-Chain   : CCRL
* Description  : 
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
#include "r_cg_macrodriver.h"
#include "r_cg_tau.h"
/* Start user code for include. Do not edit comment generated here */
#include "load_test.h"
#include "platform.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
#ifdef METER_ENABLE_MEASURE_CPU_LOAD
#define DSAD_MEASUREMENT_TIME   (65535) 
uint16_t g_timer0_dsad_counter = 0;

uint16_t g_timer0_dsad_maxcounter = 0;
uint16_t g_timer0_dsad_mincounter = 0;

uint16_t g_dsad_count = DSAD_MEASUREMENT_TIME;
uint16_t g_dsad_max_count = DSAD_MEASUREMENT_TIME;

uint32_t g_timer0_dsad_sum_counter = 0;

uint16_t g_timer0_diff = 0;
#endif
/* End user code. Do not edit comment generated here */
uint16_t g_loadtest_backup_tps0;
uint16_t g_loadtest_backup_tmr00;
uint16_t g_loadtest_backup_tdr00;

/***********************************************************************************************************************
* Function Name: LOADTEST_TAU0_Channel0_Start
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void LOADTEST_TAU_DRV_Init(void)
{
    /* Backup content of TAU0 related registers */
    g_loadtest_backup_tps0 = TPS0;
    g_loadtest_backup_tmr00 = TMR00;
    g_loadtest_backup_tdr00 = TDR00;

    /* Apply new setting */
    TAU0EN = 1U;    /* supplies input clock */
    TPS0 = _0000_TAU_CKM0_fCLK_0 | _0040_TAU_CKM1_fCLK_4 | _0000_TAU_CKM2_fCLK_1 | _0000_TAU_CKM3_fCLK_8;
    /* Mask channel 0 interrupt */
    TMMK00 = 1U;    /* disable INTTM00 interrupt */
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */  
    
    /* Set INTTM00 low priority */
    TMPR100 = 1U;
    TMPR000 = 1U;
    
    /* Channel 0 used as interval timer */
    TMR00 = _0000_TAU_CLOCK_SELECT_CKM0 | _0000_TAU_CLOCK_MODE_CKS | _0000_TAU_COMBINATION_SLAVE | 
            _0000_TAU_TRIGGER_SOFTWARE | _0000_TAU_MODE_INTERVAL_TIMER | _0000_TAU_START_INT_UNUSED;
    TDR00 = 0xFFFF;
    TO0 &= ~_0001_TAU_CH0_OUTPUT_VALUE_1;
    TOE0 &= ~_0001_TAU_CH0_OUTPUT_ENABLE;
}

/***********************************************************************************************************************
* Function Name: LOADTEST_TAU0_Channel0_Stop
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void LOADTEST_TAU_DRV_DeInit(void)
{
    /* Put here the original initialization of TAU00 */
    TPS0 = g_loadtest_backup_tps0;
    
    /* Mask channel 0 interrupt */
    TMMK00 = 1U;    /* disable INTTM00 interrupt */
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */

    /* Set INTTM00 low priority */
    TMPR100 = 1U;
    TMPR000 = 1U;   
    
    /* Channel 0 used as interval timer */
    TMR00 = g_loadtest_backup_tmr00;
    TDR00 = g_loadtest_backup_tdr00;
    TO0 &= ~_0001_TAU_CH0_OUTPUT_VALUE_1;
    TOE0 &= ~_0001_TAU_CH0_OUTPUT_ENABLE;
}

/******************************************************************************
* Function Name   : LOADTEST_TAU_DRV_SetCKM0Divider
* Interface       : void LOADTEST_TAU_DRV_SetCKM0Divider(uint16_t divider_value)
* Description     : Set TAU CKM0 clock divider value
* Arguments       : uint16_t divider_value: divider value from driver definition
* Function Calls  : None
* Return Value    : None
******************************************************************************/
void LOADTEST_TAU_DRV_SetCKM0Divider(uint16_t divider_value)
{
    TPS0 &= 0xFFF0;
    TPS0 |= divider_value;
}

/******************************************************************************
* Function Name   : LOADTEST_TAU_DRV_GetCKM0Divider
* Interface       : uint16_t LOADTEST_TAU_DRV_GetCKM0Divider(uint8_t is_raw)
* Description     : Get TAU CKM0 clock divider value
* Arguments       : uint8_t is_raw: get raw value or not
*                 :     raw value: value of CKM0 divider (0 -- 15)
*                 :     not raw value: actual divider (2^(CKM0))
* Function Calls  : None
* Return Value    : uint16_t: CKM0 divider
******************************************************************************/
uint16_t LOADTEST_TAU_DRV_GetCKM0Divider(uint8_t is_raw)
{
    if (is_raw == 1)
    {
        return (TPS0 & 0x000F);
    }
    else
    {
        return (1 << (TPS0 & 0x000F));
    }
}

/******************************************************************************
* Function Name   : LOADTEST_CGC_GetClock
* Interface       : uint16_t LOADTEST_CGC_GetClock(void)
* Description     : Get system clock
* Arguments       : uint8_t * arg_str: Arguments string
* Function Calls  : None
* Return Value    : None
******************************************************************************/
uint16_t LOADTEST_CGC_DRV_GetClock(void)
{
    if (HOCODIV == 0x00)
    {
        return 24000;
    }
    else if (HOCODIV == 0x01)
    {
        return 12000;
    }
    else if (HOCODIV == 0x02)
    {
        return 6000;
    }
    else if (HOCODIV == 0x02)
    {
        return 3000;
    }
    else if (HOCODIV == 0x02)
    {
        return 1500;
    }
    else
    {
        return 0xFFFF;
    }
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
