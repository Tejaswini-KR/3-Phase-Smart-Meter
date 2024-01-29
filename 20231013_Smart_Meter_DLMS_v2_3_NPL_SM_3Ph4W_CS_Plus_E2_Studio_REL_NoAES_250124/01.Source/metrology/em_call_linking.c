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
* Copyright (C) 2015, 2016 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : em_call_linking.c
* Version      : 
* Device(s)    : 
* Tool-Chain   : 
* Description  : 
* Creation Date: 
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#ifdef __CCRL__
#pragma section text    EMTextI
#pragma section const   EMCnst
#endif

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "compiler.h"
#include "em_core.h"

/* EM common */
#include "em_callback.h"
#include "em_measurement.h"


/* 
 * CS+ CCRL reload trigger:
 * This is used to reload changes from middlewware 
 * when there's no change on application layer
 * There's no dummy_reload.h file, this just make
 * a "not found" file in dependency list of main.c
 * Hence, trigger re-compile everytime build project
*/
#ifdef DUMMY_FOR_RELOAD
    #include "dummy_reload.h"
#endif

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
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
volatile static const uint8_t FAR_PTR g_dummy_enabled = 0;

/***********************************************************************************************************************
* Function Name: void EM_ForceLinking(void)
* Description  : Dummy function to force linking whole EM Metrology library
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void EM_ForceLinking(void)
{
    /* Call required functions to force linking whole EM Metrology library, 
     * So it will be linked and available on fsy file 
    */
     if (g_dummy_enabled == 1) 
     {
        /* em_core.h */
        EM_ADC_IntervalProcessing(NULL);
        EM_TIMER_InterruptCallback();
     
        /* em_operation.h */
        EM_Init(NULL, NULL);
        EM_Start();
        EM_Stop();
        EM_GetSystemState();
       
        EM_GetStatus();

        //EM_GetLastSagRMS(LINE_TOTAL);
        //EM_GetLastSwellRMS(LINE_TOTAL);

        // EM_QueryInformation(EM_QUERY_METROLOGY_VERSION);
        
        /* em_calibration.h */
        EM_GetCalibInfo();
        EM_SetCalibInfo(NULL);

        /* em_measurement.h */
        EM_GetPhaseAngleRtoY();
        EM_GetPhaseAngleYtoB();
        EM_GetPhaseAngleBtoR();

        EM_GetActivePower(LINE_TOTAL);
        EM_GetFundamentalActivePower(LINE_TOTAL);
        EM_GetReactivePower(LINE_TOTAL);
        EM_GetApparentPower(LINE_TOTAL);

        //EM_GetEnergyCounter(NULL);
        //EM_AddEnergyCounter(NULL);

        EM_GetVoltageRMS(LINE_TOTAL);
        EM_GetFundamentalVoltageRMS(LINE_TOTAL);

        EM_GetCurrentRMS(LINE_TOTAL);
        EM_GetFundamentalCurrentRMS(LINE_TOTAL);

        EM_GetPowerFactor(LINE_TOTAL);
        EM_GetPowerFactorSign(LINE_TOTAL);

        EM_GetLineFrequency(LINE_TOTAL);

        EM_GetVoltageTHD(LINE_TOTAL);
        EM_GetCurrentTHD(LINE_TOTAL);
        EM_GetActivePowerTHD(LINE_TOTAL);

        EM_GetCurrentPhaseAngle(LINE_TOTAL, LINE_TOTAL);
     }
}

/**************************************************************
 * wrp_em_timer.h
 **************************************************************/
void EM_TIMER_Init(void)
{
    EM_TIMER_Init_Address();
}

void EM_TIMER_Start(void)
{
    EM_TIMER_Start_Address();
}

void EM_TIMER_Stop(void)
{
    EM_TIMER_Stop_Address();
}

/**************************************************************
 * wrp_em_wdt.h
 **************************************************************/
void EM_WDT_Init(void)
{
    EM_WDT_Init_Address();
}

void EM_WDT_Start(void)
{
    EM_WDT_Start_Address();
}

void EM_WDT_Stop(void)
{
    EM_WDT_Stop_Address();
}

void EM_WDT_Restart(void)
{
    EM_WDT_Restart_Address();
}

/**************************************************************
 * wrp_mcu.h
 **************************************************************/
void EM_MCU_Delay(uint16_t us)
{
    EM_MCU_Delay_Address(us);
}

void EM_MCU_MultipleInterruptEnable(uint8_t enable)
{
    EM_MCU_MultipleInterruptEnable_Address(enable);
}

/**************************************************************
 * wrp_em_adc.h
 **************************************************************/
void EM_ADC_Init(void)
{
    EM_ADC_Init_Address();
}

void EM_ADC_Start(void)
{
    EM_ADC_Start_Address();
}

void EM_ADC_Stop(void)
{
    EM_ADC_Stop_Address();
}

void EM_ADC_GainPhaseReset(EM_LINE line)
{
    EM_ADC_GainPhaseReset_Address(line);
}

void EM_ADC_GainPhaseIncrease(EM_LINE line)
{
    EM_ADC_GainPhaseIncrease_Address(line);
}

void EM_ADC_GainPhaseDecrease(EM_LINE line)
{
    EM_ADC_GainPhaseDecrease_Address(line);
}

uint8_t EM_ADC_GainPhaseGetLevel(EM_LINE line)
{
    return EM_ADC_GainPhaseGetLevel_Address(line);
}

void EM_ADC_SetPhaseCorrection(EM_LINE line, float32_t degree)
{
    EM_ADC_SetPhaseCorrection_Address(line, degree);
}

void EM_ADC_SAMP_UpdateStep(float32_t fac)
{
    EM_ADC_SAMP_UpdateStep_Address(fac);
}

/**************************************************************
 * wrp_em_pulse.h
 **************************************************************/
void EM_PULSE_Init(void)
{
    EM_PULSE_Init_Address();
}

void EM_PULSE_ACTIVE_On(void)
{
    EM_PULSE_ACTIVE_On_Address();
}

void EM_PULSE_ACTIVE_Off(void)
{
    EM_PULSE_ACTIVE_Off_Address();
}

void EM_PULSE_REACTIVE_On(void)
{
    EM_PULSE_REACTIVE_On_Address();
}

void EM_PULSE_REACTIVE_Off(void)
{
    EM_PULSE_REACTIVE_Off_Address();
}

void EM_PULSE_APPARENT_On(void)
{
    EM_PULSE_APPARENT_On_Address();
}

void EM_PULSE_APPARENT_Off(void)
{
    EM_PULSE_APPARENT_Off_Address();
}

/**************************************************************
 * wrp_em_sw_property.h
 **************************************************************/
EM_SW_PROPERTY FAR_PTR * EM_SW_GetProperty(void)
{
    return EM_SW_GetProperty_Address();
}