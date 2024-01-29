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
* File Name    : bl_r_cg_lcd.c
* Version      : 
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* Description  : This file implements device driver for LCD module.
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
#include "bl_r_cg_lcd.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "bl_r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
#ifdef LCD_VOLTAGE_WAITTIME
    #undef  LCD_VOLTAGE_WAITTIME
    #define LCD_VOLTAGE_WAITTIME    100
#endif
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_LCD_Create
* Description  : This function initializes the LCD module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LCD_Create(void)
{
//    volatile uint32_t wt_count;

//    LCDON = 0U;     /* display off (all segment outputs are deselected) */
//    LCDM1 |= _00_LCD_VOLTAGE_HIGH;
//    LCDM0 = _00_LCD_DISPLAY_WAVEFORM_A | _0C_LCD_TIMESLICE_4 | _01_LCD_BIAS_MODE_3;
//    LCDM0 |= _40_LCD_VOLTAGE_MODE_INTERNAL;

//    ///* Set CAPL and CAPH pins --> do this by port driver, reduce code size */
//    //ISCLCD &= (uint8_t)~_01_LCD_CAPLH_BUFFER_VALID;
//    ///* Set VL3 --> do this by port driver, reduce code size */
//    //ISCLCD |= _02_LCD_VL3_BUFFER_VALID;
    
//    /* Set segment pins --> do this by port driver, reduce code size */
//    //PFSEG0 = 0xF0U;
//    //PFSEG1 = 0xFFU;
//    //PFSEG2 = 0xFFU;
//    //PFSEG3 = 0x00U;
//    //PFSEG4 = 0x00U;
//    //PFSEG5 = 0x00U;
    
//    LCDM1 |= _00_LCD_DISPLAY_PATTERN_A;
//    LCDC0 = _05_LCD_CLOCK_FSX_FIL_6;
//    VLCD = _08_LCD_BOOST_VOLTAGE_120V;

//    /* Change the waiting time according to the system */
//    for (wt_count = 0U; wt_count <= LCD_REFVOLTAGE_WAITTIME; wt_count++)
//    {
//        NOP();
//    }
}

/***********************************************************************************************************************
* Function Name: R_LCD_Start
* Description  : This function enables the LCD display.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LCD_Start(void)
{
    LCDON = 1U;
}

/***********************************************************************************************************************
* Function Name: R_LCD_Stop
* Description  : This function disables the LCD display.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LCD_Stop(void)
{
    LCDON = 0U;
}

/***********************************************************************************************************************
* Function Name: R_LCD_Set_VoltageOn
* Description  : This function enables voltage boost circuit or capacitor split circuit.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LCD_Set_VoltageOn(void)
{
    volatile uint32_t wt_count;
    
    VLCON = 1U;

    /* Change the waiting time according to the system */
    for(wt_count = 0U; wt_count <= LCD_VOLTAGE_WAITTIME; wt_count++)
    {
        NOP();
    }
    
    SCOC = 1U;
}

/***********************************************************************************************************************
* Function Name: R_LCD_Set_VoltageOff
* Description  : This function disables voltage boost circuit or capacitor split circuit.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LCD_Set_VoltageOff(void)
{
    SCOC = 0U;
    VLCON = 0U;
    LCDM0 &= (uint8_t)~_C0_LCD_VOLTAGE_MODE_INITIALVALUE;
}

/***********************************************************************************************************************
* Function Name: R_LCD_PowerDown
* Description  : This function power down LCD module
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LCD_PowerOff(void)
{
    R_LCD_Stop();
    R_LCD_Set_VoltageOff();
}

/***********************************************************************************************************************
* Function Name: R_LCD_PowerOn
* Description  : This function power down LCD module
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LCD_PowerOn(void)
{
    R_LCD_Start();
    R_LCD_Set_VoltageOn();
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
