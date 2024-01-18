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
* File Name    : wrp_em_adc.c
* Version      : 1.01
* Device(s)    : RL78/I1C - 512K
* Tool-Chain   : CCRL
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : ADC Wrapper for RL78/I1C - 512K Platform
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Driver */
#include "r_cg_macrodriver.h"
#include "r_cg_dsadc.h"
#include "r_cg_dtc.h"

/* Standard library */
#include <string.h>

/* Other EM wrapper */
#include "wrp_em_sw_config.h"   /* Wrapper Shared Configuration */
#include "wrp_em_adc.h"         /* Wrapper ADC definitions */
#include "em_core.h"
#include "platform.h"
#include "r_calib.h"

/* Filter middleware */
#include "rl78_sw_hpf16.h"
#include "r_dscl_iirbiquad_i32_1.h"
#include "r_dscl_iirbiquad_i32_2.h"

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Macro definitions
******************************************************************************/
/* User definition */
#define EM_FAC_CHANGED_DETECTION_COUNT                              (5)

/* Non user definition */
#define EM_ADC_CHANNEL_RESULT_REG_ADDR_CURRENT_PHASE_R              (&(JOIN(DSADCR, EM_ADC_CURRENT_DRIVER_CHANNEL_OPTIMIZATION_PHASE_R)))
#define EM_ADC_CHANNEL_RESULT_REG_ADDR_CURRENT_PHASE_Y              (&(JOIN(DSADCR, EM_ADC_CURRENT_DRIVER_CHANNEL_OPTIMIZATION_PHASE_Y)))
#define EM_ADC_CHANNEL_RESULT_REG_ADDR_CURRENT_PHASE_B              (&(JOIN(DSADCR, EM_ADC_CURRENT_DRIVER_CHANNEL_OPTIMIZATION_PHASE_B)))
#define EM_ADC_CHANNEL_RESULT_REG_ADDR_CURRENT_NEUTRAL              (&(JOIN(DSADCR, EM_ADC_CURRENT_DRIVER_CHANNEL_OPTIMIZATION_NEUTRAL)))

#define EM_ADC_DRIVER_CURRENT_READ_ONE_CHANNEL(isample, dsad_reg)   {\
                                                                        *((uint16_t *)&isample)         = *((uint16_t *)dsad_reg);\
                                                                        *((uint8_t *)&isample + 0x02)   = *((uint8_t *)dsad_reg + 0x02);\
                                                                        *((int8_t *)&isample + 0x03)    = (*((int8_t *)dsad_reg + 0x02)) >> 7;\
                                                                    }

#define EM_ADC_DRIVER_CURRENT_READ_ALL()                            {\
                                        EM_ADC_DRIVER_CURRENT_READ_ONE_CHANNEL(g_wrp_adc_samples.phase_r.i, EM_ADC_CHANNEL_RESULT_REG_ADDR_CURRENT_PHASE_R);\
                                        EM_ADC_DRIVER_CURRENT_READ_ONE_CHANNEL(g_wrp_adc_samples.phase_y.i, EM_ADC_CHANNEL_RESULT_REG_ADDR_CURRENT_PHASE_Y);\
                                        EM_ADC_DRIVER_CURRENT_READ_ONE_CHANNEL(g_wrp_adc_samples.phase_b.i, EM_ADC_CHANNEL_RESULT_REG_ADDR_CURRENT_PHASE_B);\
                                        EM_ADC_DRIVER_CURRENT_READ_ONE_CHANNEL(g_wrp_adc_samples.neutral.i, EM_ADC_CHANNEL_RESULT_REG_ADDR_CURRENT_NEUTRAL);\
}

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/******************************************************************************
Private global variables and functions
******************************************************************************/

/* Software delay for voltage channel */
#if (EM_ADC_DELAY_STEP_VOLTAGE > 0)

int16_t     g_wrp_adc_voltage_circle_pos; 
uint16_t    g_wrp_adc_voltage_circle_step;

int16_t g_wrp_adc_voltage_circle_phase_r[EM_ADC_DELAY_STEP_VOLTAGE+1];
int16_t g_wrp_adc_voltage_circle_phase_y[EM_ADC_DELAY_STEP_VOLTAGE+1];
int16_t g_wrp_adc_voltage_circle_phase_b[EM_ADC_DELAY_STEP_VOLTAGE+1];

#endif /* EM_ADC_DELAY_STEP_VOLTAGE > 0 */
#ifdef METER_WRAPPER_ADC_COPY_REACTIVE_SAMPLE
#if (EM_ADC_DELAY_VOLTAGE90_MAX_STEP > 0)

int16_t     g_wrp_adc_voltage90_circle_pos; 
uint16_t    g_wrp_adc_voltage90_circle_step;

int16_t g_wrp_adc_voltage90_circle_phase_r[EM_ADC_DELAY_VOLTAGE90_MAX_STEP+1];
int16_t g_wrp_adc_voltage90_circle_phase_y[EM_ADC_DELAY_VOLTAGE90_MAX_STEP+1];
int16_t g_wrp_adc_voltage90_circle_phase_b[EM_ADC_DELAY_VOLTAGE90_MAX_STEP+1];

#endif /* METER_WRAPPER_ADC_COPY_REACTIVE_SAMPLE */
#endif /* EM_ADC_DELAY_VOLTAGE90_MAX_STEP > 0 */

/* 16bit of voltage sample, no struct for optimization */
int16_t g_wrp_adc_buffer_phase_r_v;
int16_t g_wrp_adc_buffer_phase_y_v;
int16_t g_wrp_adc_buffer_phase_b_v;

int16_t g_wrp_adc_buffer_phase_r_v90;
int16_t g_wrp_adc_buffer_phase_y_v90;
int16_t g_wrp_adc_buffer_phase_b_v90;

/* Intermediate capture data for checking only */
uint16_t g_wrp_adc_calculated_tdr;

/* Sample storage of wrapper */
EM_SAMPLES g_wrp_adc_samples;

#ifdef __DEBUG
#define EM_ADC_MAX_DEBUG_SAMPLE         (140)
uint16_t g_wrp_sample_count = EM_ADC_MAX_DEBUG_SAMPLE;
int16_t  g_wrp_sample_int16[6][EM_ADC_MAX_DEBUG_SAMPLE];
int32_t  g_wrp_sample_int32[4][EM_ADC_MAX_DEBUG_SAMPLE];

#endif /* __DEBUG */

uint8_t g_EM_ADC_GainPhaseCurrentLevel[EM_VOL_CHANNEL_NUM];        /* The current level of phase gain */

dsad_gain_t g_wrp_adc_channel_gain[EM_VOL_CHANNEL_NUM][EM_GAIN_PHASE_NUM_LEVEL_MAX] = 
{
    {
        EM_ADC_GAIN_LEVEL0_PHASE_R,
        EM_ADC_GAIN_LEVEL1_PHASE_R,
    },
    {
        EM_ADC_GAIN_LEVEL0_PHASE_Y,
        EM_ADC_GAIN_LEVEL1_PHASE_Y,
    },
    {
        EM_ADC_GAIN_LEVEL0_PHASE_B,
        EM_ADC_GAIN_LEVEL1_PHASE_B,
    },
};

/* Reactive timer */
float32_t g_previous_fac;
uint8_t g_fac_update_counter = 0;

/* Linear interpolation for reactive sample at un-settable TDR01 value */
int16_t  g_wrp_adc_v90_lerp_t;
int16_t * gp_previous_v90_r;
int16_t * gp_previous_v90_y;
int16_t * gp_previous_v90_b;

/******************************************************************************
* Function Name    : void EM_ADC_SetGainEnum(EM_LINE line, dsad_gain_t dsad_gain)
* Description      : Set a suitable gain phase level to a port
* Arguments        : None
* Functions Called : None
* Return Value     : None
******************************************************************************/
void EM_ADC_SetGainEnum(EM_LINE line, dsad_gain_t dsad_gain)
{
    switch (line)
    {
        case LINE_PHASE_R:
            R_DSADC_SetChannelGain(EM_ADC_CURRENT_DRIVER_CHANNEL_PHASE_R, dsad_gain);
            break;
        case LINE_PHASE_Y:
            R_DSADC_SetChannelGain(EM_ADC_CURRENT_DRIVER_CHANNEL_PHASE_Y, dsad_gain);
            break;
        case LINE_PHASE_B:
            R_DSADC_SetChannelGain(EM_ADC_CURRENT_DRIVER_CHANNEL_PHASE_B, dsad_gain);
            break;
        case LINE_NEUTRAL:
            R_DSADC_SetChannelGain(EM_ADC_CURRENT_DRIVER_CHANNEL_NEUTRAL, dsad_gain);
            break;
        default:
            break;
    }
}

/******************************************************************************
* Function Name    : void EM_ADC_GainPhaseSet(EM_LINE line, uint8_t gain)
* Description      : Set a suitable gain phase level to a port
* Arguments        : None
* Functions Called : None
* Return Value     : None
******************************************************************************/
void EM_ADC_SetGainValue(EM_LINE line, uint8_t gain)
{
    dsad_gain_t dsad_gain = R_DSADC_GetGainEnumValue(gain);

    EM_ADC_SetGainEnum(line, dsad_gain);
}

/******************************************************************************
* Function Name    : static void EM_ADC_DoPhaseDelayAllVoltage(void)
* Description      : Do phase delay for all voltage samples accordingly
* Arguments        : None
* Functions Called : None
* Return Value     : None
******************************************************************************/
static void EM_ADC_DoPhaseDelayAllVoltage(void)
{
    int16_t pop_pos;
    
    /* Phase adjustment for V signal */
    #if (EM_ADC_DELAY_STEP_VOLTAGE > 0)
    if (g_wrp_adc_voltage_circle_pos <= 0)
    {
        pop_pos = g_wrp_adc_voltage_circle_step;
    }
    else
    {
        pop_pos = g_wrp_adc_voltage_circle_pos - 1;
    }

    /* PUSH: Add the signal into the data circle at circlepos position */
    g_wrp_adc_voltage_circle_phase_r[g_wrp_adc_voltage_circle_pos] = g_wrp_adc_buffer_phase_r_v;
    g_wrp_adc_voltage_circle_phase_y[g_wrp_adc_voltage_circle_pos] = g_wrp_adc_buffer_phase_y_v;
    g_wrp_adc_voltage_circle_phase_b[g_wrp_adc_voltage_circle_pos] = g_wrp_adc_buffer_phase_b_v;
    
    /* POP: Get the signal from data circle from (pos + steps) position */
    g_wrp_adc_buffer_phase_r_v = g_wrp_adc_voltage_circle_phase_r[pop_pos];
    g_wrp_adc_buffer_phase_y_v = g_wrp_adc_voltage_circle_phase_y[pop_pos];
    g_wrp_adc_buffer_phase_b_v = g_wrp_adc_voltage_circle_phase_b[pop_pos];
    
    /* Scroll the circle, scroll left */
    g_wrp_adc_voltage_circle_pos--;
    if (g_wrp_adc_voltage_circle_pos == -1)
    {
        g_wrp_adc_voltage_circle_pos = g_wrp_adc_voltage_circle_step;
    }

    #endif /* EM_ADC_DELAY_STEP_VOLTAGE > 0 */

    #ifdef METER_WRAPPER_ADC_COPY_REACTIVE_SAMPLE        
    /* Phase adjustment for V90 signal */
    #if (EM_ADC_DELAY_VOLTAGE90_MAX_STEP > 0)
    if (g_wrp_adc_voltage90_circle_pos <= 0)
    {
        pop_pos = g_wrp_adc_voltage90_circle_step;
    }
    else
    {
        pop_pos = g_wrp_adc_voltage90_circle_pos - 1;
    }

    /* PUSH: Add the signal into the data circle at circlepos position */
    g_wrp_adc_voltage90_circle_phase_r[g_wrp_adc_voltage90_circle_pos] = g_wrp_adc_buffer_phase_r_v90;
    g_wrp_adc_voltage90_circle_phase_y[g_wrp_adc_voltage90_circle_pos] = g_wrp_adc_buffer_phase_y_v90;
    g_wrp_adc_voltage90_circle_phase_b[g_wrp_adc_voltage90_circle_pos] = g_wrp_adc_buffer_phase_b_v90;

    /* Backup pushID for interpolation with next DSAD->SAR sample */
	gp_previous_v90_r = &g_wrp_adc_voltage90_circle_phase_r[g_wrp_adc_voltage90_circle_pos];
	gp_previous_v90_y = &g_wrp_adc_voltage90_circle_phase_y[g_wrp_adc_voltage90_circle_pos];
	gp_previous_v90_b = &g_wrp_adc_voltage90_circle_phase_b[g_wrp_adc_voltage90_circle_pos];
    
    /* POP: Get the signal from data circle from (pos + steps) position */
    g_wrp_adc_buffer_phase_r_v90 = g_wrp_adc_voltage90_circle_phase_r[pop_pos];
    g_wrp_adc_buffer_phase_y_v90 = g_wrp_adc_voltage90_circle_phase_y[pop_pos];
    g_wrp_adc_buffer_phase_b_v90 = g_wrp_adc_voltage90_circle_phase_b[pop_pos];
    
    /* Scroll the circle, scroll left */
    g_wrp_adc_voltage90_circle_pos--;
    if (g_wrp_adc_voltage90_circle_pos == -1)
    {
        g_wrp_adc_voltage90_circle_pos = g_wrp_adc_voltage90_circle_step;
    }
    #endif /* EM_ADC_DELAY_VOLTAGE90_MAX_STEP > 0 */

    #endif /* METER_WRAPPER_ADC_COPY_REACTIVE_SAMPLE */

}
/******************************************************************************
* Function Name    : static void EM_ADC_DoPhaseDelayAllCurrent(void)
* Description      : Do phase delay for all current samples accordingly
* Arguments        : None
* Functions Called : None
* Return Value     : None
******************************************************************************/
static void EM_ADC_DoPhaseDelayAllCurrent(void)
{
    /* Not implement for current channel */
}

/******************************************************************************
* Function Name    : static void EM_ADC_DoNoisyBitMasking(void)
* Description      : Do noisy bit masking for signals
* Functions Called : None
* Return Value     : None
******************************************************************************/
static void EM_ADC_DoNoisyBitMasking(void)
{
    #ifdef EM_ENABLE_NOISY_BIT_MASKING
    
    int16_t i_mask;

    /* Find the mask of I for noisy bit clearing 
     * Note: do not use this on SAR 10bit signal
    */

    /* Phase_R */
    i_mask = ((int16_t)(g_wrp_adc_samples.phase_r.i >> 16));
    
    if (i_mask == 0x0000)
    {
        /* Mask off the noise, 4 low-bits */
        #ifdef EM_MASK_OFF_NOISY_BITS_POSITIVE
        *((uint8_t *)&g_wrp_adc_samples.phase_r.i) &= EM_MASK_OFF_NOISY_BITS_POSITIVE;
        #endif /* EM_MASK_OFF_NOISY_BITS_POSITIVE */
    }
    else if (i_mask == 0xffff)
    {
        /* Mask off the noise, 4 low-bits */
        #ifdef EM_MASK_OFF_NOISY_BITS_NEGATIVE
        *((uint8_t *)&g_wrp_adc_samples.phase_r.i) |= EM_MASK_OFF_NOISY_BITS_NEGATIVE;
        #endif /* EM_MASK_OFF_NOISY_BITS_NEGATIVE */
    }

    /* Phase_Y */
    i_mask = ((int16_t)(g_wrp_adc_samples.phase_y.i >> 16));
    
    if (i_mask == 0x0000)
    {
        /* Mask off the noise, 4 low-bits */
        #ifdef EM_MASK_OFF_NOISY_BITS_POSITIVE
        *((uint8_t *)&g_wrp_adc_samples.phase_y.i) &= EM_MASK_OFF_NOISY_BITS_POSITIVE;
        #endif /* EM_MASK_OFF_NOISY_BITS_POSITIVE */
    }
    else if (i_mask == 0xffff)
    {
        /* Mask off the noise, 4 low-bits */
        #ifdef EM_MASK_OFF_NOISY_BITS_NEGATIVE
        *((uint8_t *)&g_wrp_adc_samples.phase_y.i) |= EM_MASK_OFF_NOISY_BITS_NEGATIVE;
        #endif /* EM_MASK_OFF_NOISY_BITS_NEGATIVE */
    }

    /* Phase_B */
    i_mask = ((int16_t)(g_wrp_adc_samples.phase_b.i >> 16));
    
    if (i_mask == 0x0000)
    {
        /* Mask off the noise, 4 low-bits */
        #ifdef EM_MASK_OFF_NOISY_BITS_POSITIVE
        *((uint8_t *)&g_wrp_adc_samples.phase_b.i) &= EM_MASK_OFF_NOISY_BITS_POSITIVE;
        #endif /* EM_MASK_OFF_NOISY_BITS_POSITIVE */
    }
    else if (i_mask == 0xffff)
    {
        /* Mask off the noise, 4 low-bits */
        #ifdef EM_MASK_OFF_NOISY_BITS_NEGATIVE
        *((uint8_t *)&g_wrp_adc_samples.phase_b.i) |= EM_MASK_OFF_NOISY_BITS_NEGATIVE;
        #endif /* EM_MASK_OFF_NOISY_BITS_NEGATIVE */
    }
    
    #endif /* EM_ENABLE_NOISY_BIT_MASKING */
}

/******************************************************************************
* Function Name    : void EM_ADC_Init(void)
* Description      : Set a suitable gain neutral level to a port
* Arguments        : None
* Functions Called : EM_ADC_DriverInit()
* Return Value     : None
******************************************************************************/
void EM_ADC_Init(void)
{
    /* Init ADC HW Module */
    
    /* Initialize ADC Data */
    memset((void *)g_adc_data, 0, sizeof(g_adc_data));

    g_wrp_adc_voltage_circle_step = EM_ADC_DELAY_STEP_VOLTAGE;

    #ifdef METER_WRAPPER_ADC_COPY_REACTIVE_SAMPLE    
    g_wrp_adc_voltage90_circle_step = EM_ADC_DELAY_STEP_VOLTAGE90;
    #endif /* METER_WRAPPER_ADC_COPY_REACTIVE_SAMPLE */
    
    /* Init the HPF16 */
    RL78_InitSoftwareHPF16(EM_SW_PROPERTY_ADC_HPF_CUTOFF_FREQUENCY);
}

/******************************************************************************
* Function Name    : void EM_ADC_Start(void)
* Description      : Start ADC sampling
* Arguments        : None
* Functions Called : EM_ADC_DriverStart()
* Return Value     : None
******************************************************************************/
void EM_ADC_Start(void)
{
    /* Reset SW delay and SW filter data */
    g_wrp_adc_voltage_circle_pos = 0;
    #ifdef METER_WRAPPER_ADC_COPY_REACTIVE_SAMPLE
    g_wrp_adc_voltage90_circle_pos = 0;
	/* Reset linear interpolation related variables */
	g_wrp_adc_v90_lerp_t = 0;
	gp_previous_v90_r = &g_wrp_adc_voltage90_circle_phase_r[0];
	gp_previous_v90_y = &g_wrp_adc_voltage90_circle_phase_y[0];
	gp_previous_v90_b = &g_wrp_adc_voltage90_circle_phase_b[0];
    #endif /* METER_WRAPPER_ADC_COPY_REACTIVE_SAMPLE */
	

    /* Clear filer buffer */
    RL78_ResetSoftwareHPF16(0);
    RL78_ResetSoftwareHPF16(1);
    RL78_ResetSoftwareHPF16(2);
    RL78_ResetSoftwareHPF16(3);
    RL78_ResetSoftwareHPF16(4);
    RL78_ResetSoftwareHPF16(5);
    
    /* Clear DSCL Filter */
    R_DSCL_IIRBiquad_i32i32_Reset_1(0);
    R_DSCL_IIRBiquad_i32i32_Reset_1(1);
    R_DSCL_IIRBiquad_i32i32_Reset_1(2);
    R_DSCL_IIRBiquad_i32i32_Reset_2(0);
    R_DSCL_IIRBiquad_i32i32_Reset_2(1);
    R_DSCL_IIRBiquad_i32i32_Reset_2(2);
    
    /* Start ADC HW Module */
    R_DTCD0_Start();
    R_TAU0_Channel1_Start();
    R_12ADC_Start();
    R_DSADC_Start();
}

/******************************************************************************
* Function Name    : void EM_ADC_Stop(void)
* Description      : Stop ADC sampling
* Arguments        : None
* Functions Called : EM_ADC_DriverStop()
* Return Value     : None
******************************************************************************/
void EM_ADC_Stop(void)
{
    /* Stop ADC HW Module */
    R_DSADC_Stop();
    R_TAU0_Channel1_Stop();
    R_12ADC_Stop();
    R_DTCD0_Stop();
}

/******************************************************************************
* Function Name    : void EM_ADC_InterruptCallback(void)
* Description      : ADC Interrupt Sample processing and put to following:
*                  :    . EM_Middleware
*                  :    . Calibration App
* Arguments        : None
* Functions Called : TBD
* Return Value     : None
******************************************************************************/
void EM_ADC_InterruptCallback(void)
{
    /* Push MACRx registers */
    uint16_t bkup_macrh = MACRH;
    uint16_t bkup_macrl = MACRL;

    /* DSAD->SAR (for V) samples reading */
    /* Need to do first in DSAD interrupt */
    EM_ADC_Voltage_DriverRead(EM_ADC_VOL_DRIVER_CHANNEL_PHASE_R, g_wrp_adc_buffer_phase_r_v);
    EM_ADC_Voltage_DriverRead(EM_ADC_VOL_DRIVER_CHANNEL_PHASE_Y, g_wrp_adc_buffer_phase_y_v);
    EM_ADC_Voltage_DriverRead(EM_ADC_VOL_DRIVER_CHANNEL_PHASE_B, g_wrp_adc_buffer_phase_b_v);
    
    #ifdef METER_WRAPPER_ADC_COPY_REACTIVE_SAMPLE
    /* TIMER->SAR (for V) samples reading */
    EM_ADC_Voltage90_DriverRead(EM_ADC_VOL_DRIVER_CHANNEL_PHASE_R, g_wrp_adc_buffer_phase_r_v90);
    EM_ADC_Voltage90_DriverRead(EM_ADC_VOL_DRIVER_CHANNEL_PHASE_Y, g_wrp_adc_buffer_phase_y_v90);
    EM_ADC_Voltage90_DriverRead(EM_ADC_VOL_DRIVER_CHANNEL_PHASE_B, g_wrp_adc_buffer_phase_b_v90);
	
	/* Linear interpolation for samples at un-settable TDR value
	 *		y = y0 + [(y1-y0) * (x-x0)/(x1-x0)]
	 *			(x0,y0): TDR step, sample ahead interpolate point
	 *			(x ,y ): TDR step, sample at point to interpolate
	 *			(x1,y1): TDR step, sample behind interpolate point
	 * This routine in DSAD calculate
	 *		y = y0 + (y1-y0)*t
	 * With t precalculated from in timer and scale up 8 bit, within [0-1] range
	 *		t = (x-x0)/(x1-x0)
	 *		(y1-y0)*t then scaled down 8 bit before addition with y0
	 * Computation is inline for 3phase
	*/
    if (g_wrp_adc_v90_lerp_t != 0)
    {
        if (TDR01 == EM_ADC_DRIVER_TAU_MAX_THRESHOLD)
        {
			*gp_previous_v90_r = (int16_t)(*gp_previous_v90_r + (((int32_t)(g_wrp_adc_buffer_phase_r_v - *gp_previous_v90_r) * g_wrp_adc_v90_lerp_t) >> 8));
			*gp_previous_v90_y = (int16_t)(*gp_previous_v90_y + (((int32_t)(g_wrp_adc_buffer_phase_y_v - *gp_previous_v90_y) * g_wrp_adc_v90_lerp_t) >> 8));
			*gp_previous_v90_b = (int16_t)(*gp_previous_v90_b + (((int32_t)(g_wrp_adc_buffer_phase_b_v - *gp_previous_v90_b) * g_wrp_adc_v90_lerp_t) >> 8));
        }
        else // (TDR01 == EM_ADC_DRIVER_TAU_MIN_THRESHOLD)
        {
            /* Interpolate between TIMER->SAR samples and DSAD->SAR samples */
			g_wrp_adc_buffer_phase_r_v90 = (int16_t)(g_wrp_adc_buffer_phase_r_v + (((int32_t)(g_wrp_adc_buffer_phase_r_v90 - g_wrp_adc_buffer_phase_r_v) * g_wrp_adc_v90_lerp_t) >> 8));
            g_wrp_adc_buffer_phase_y_v90 = (int16_t)(g_wrp_adc_buffer_phase_y_v + (((int32_t)(g_wrp_adc_buffer_phase_y_v90 - g_wrp_adc_buffer_phase_y_v) * g_wrp_adc_v90_lerp_t) >> 8));
            g_wrp_adc_buffer_phase_b_v90 = (int16_t)(g_wrp_adc_buffer_phase_b_v + (((int32_t)(g_wrp_adc_buffer_phase_b_v90 - g_wrp_adc_buffer_phase_b_v) * g_wrp_adc_v90_lerp_t) >> 8));
        }
    }
    else
    {
        /* Use TIMER->SAR samples read from register above */
    }
    #endif /* METER_WRAPPER_ADC_COPY_REACTIVE_SAMPLE */
    
    /*  Get current samples */
    EM_ADC_DRIVER_CURRENT_READ_ALL();
        
    EM_ADC_DoNoisyBitMasking();
        
    /* Do phase delay: for all voltage channels */
    EM_ADC_DoPhaseDelayAllVoltage();
    
    /* Do phase delay: for all current channels */
    EM_ADC_DoPhaseDelayAllCurrent();
    
    /* Do HPF to maintain the response with I channel + Copy the voltage signal to output buffer */
    /* Substract with fixed signal offset of bias voltage for faster response */
    g_wrp_adc_samples.phase_r.v = 
    g_wrp_adc_buffer_phase_r_v = RL78_DoSoftwareHPF16(g_wrp_adc_buffer_phase_r_v- EM_CALIB_DEFAULT_OFFSET_V, 0);
        
    g_wrp_adc_samples.phase_y.v = 
    g_wrp_adc_buffer_phase_y_v = RL78_DoSoftwareHPF16(g_wrp_adc_buffer_phase_y_v- EM_CALIB_DEFAULT_OFFSET_V, 1);
        
    g_wrp_adc_samples.phase_b.v = 
    g_wrp_adc_buffer_phase_b_v = RL78_DoSoftwareHPF16(g_wrp_adc_buffer_phase_b_v- EM_CALIB_DEFAULT_OFFSET_V, 2);

    #ifdef METER_WRAPPER_ADC_COPY_REACTIVE_SAMPLE
    g_wrp_adc_samples.phase_r.v90 = 
    g_wrp_adc_buffer_phase_r_v90 = RL78_DoSoftwareHPF16(g_wrp_adc_buffer_phase_r_v90 - EM_CALIB_DEFAULT_OFFSET_V, 3);
        
    g_wrp_adc_samples.phase_y.v90 = 
    g_wrp_adc_buffer_phase_y_v90 = RL78_DoSoftwareHPF16(g_wrp_adc_buffer_phase_y_v90 - EM_CALIB_DEFAULT_OFFSET_V, 4);
        
    g_wrp_adc_samples.phase_b.v90 = 
    g_wrp_adc_buffer_phase_b_v90 = RL78_DoSoftwareHPF16(g_wrp_adc_buffer_phase_b_v90 - EM_CALIB_DEFAULT_OFFSET_V, 5);
    #endif /* METER_WRAPPER_ADC_COPY_REACTIVE_SAMPLE */
    
    #ifdef METER_WRAPPER_ADC_COPY_FUNDAMENTAL_SAMPLE
    /* Do the IIRBiquad to filter the input signals, put filterd signal to buffer and the sequence of fundamental samples*/
    
    /* Run the filter on voltage channel at 3906Hz sampling frequency */
    R_DSCL_IIRBiquad_i32i32_c_nr_1(g_wrp_adc_samples.phase_r.v, &g_wrp_adc_samples.phase_r.v_fund, 0);
    R_DSCL_IIRBiquad_i32i32_c_nr_1(g_wrp_adc_samples.phase_y.v, &g_wrp_adc_samples.phase_y.v_fund, 1);
    R_DSCL_IIRBiquad_i32i32_c_nr_1(g_wrp_adc_samples.phase_b.v, &g_wrp_adc_samples.phase_b.v_fund, 2);
    
    #if (METER_WRAPPER_ADC_CURRENT_CHANNEL_LPF_REDUCED_FS == 0)
    /* Run filter on current channel at 3906Hz sampling frequency, phase response matched */
    R_DSCL_IIRBiquad_i32i32_c_nr_2(g_wrp_adc_samples.phase_r.i, &g_wrp_adc_samples.phase_r.i_fund, 0);
    R_DSCL_IIRBiquad_i32i32_c_nr_2(g_wrp_adc_samples.phase_y.i, &g_wrp_adc_samples.phase_y.i_fund, 1);
    R_DSCL_IIRBiquad_i32i32_c_nr_2(g_wrp_adc_samples.phase_b.i, &g_wrp_adc_samples.phase_b.i_fund, 2);
    g_wrp_adc_samples.status.fund_sequence = EM_SW_FUND_SEQUENCE_PHASE_ALL;
    
    #elif (METER_WRAPPER_ADC_CURRENT_CHANNEL_LPF_REDUCED_FS == 1)
    /* Run the filter on current channel at 1302Hz sampling frequency, need to do phase matching on wrapper */
    switch (g_wrp_adc_samples.status.fund_sequence)
    {
        case EM_SW_FUND_SEQUENCE_PHASE_B:
            R_DSCL_IIRBiquad_i32i32_c_nr_2(g_wrp_adc_samples.phase_r.i, &g_wrp_adc_samples.phase_r.i_fund, 0);
            g_wrp_adc_samples.status.fund_sequence = EM_SW_FUND_SEQUENCE_PHASE_R;
            break;
        case EM_SW_FUND_SEQUENCE_PHASE_R:
            R_DSCL_IIRBiquad_i32i32_c_nr_2(g_wrp_adc_samples.phase_y.i, &g_wrp_adc_samples.phase_y.i_fund, 1);
            g_wrp_adc_samples.status.fund_sequence = EM_SW_FUND_SEQUENCE_PHASE_Y;
            break;
        case EM_SW_FUND_SEQUENCE_PHASE_Y:
            R_DSCL_IIRBiquad_i32i32_c_nr_2(g_wrp_adc_samples.phase_b.i, &g_wrp_adc_samples.phase_b.i_fund, 2);
            g_wrp_adc_samples.status.fund_sequence = EM_SW_FUND_SEQUENCE_PHASE_B;
            break;
        default:
            g_wrp_adc_samples.status.fund_sequence = EM_SW_FUND_SEQUENCE_PHASE_B;
            break;
    }
    #endif /* METER_WRAPPER_ADC_CURRENT_CHANNEL_LPF_REDUCED_FS */
    #endif /* METER_WRAPPER_ADC_COPY_FUNDAMENTAL_SAMPLE */
    
    /* Debug the signal */
    #ifdef __DEBUG
    #ifndef METER_ENABLE_MEASURE_CPU_LOAD
    if (g_wrp_sample_count < EM_ADC_MAX_DEBUG_SAMPLE)
    {
        g_wrp_sample_int16[0][g_wrp_sample_count] = g_wrp_adc_samples.phase_r.v;
        g_wrp_sample_int16[1][g_wrp_sample_count] = g_wrp_adc_samples.phase_y.v;
        g_wrp_sample_int16[2][g_wrp_sample_count] = g_wrp_adc_samples.phase_b.v;
        g_wrp_sample_int16[3][g_wrp_sample_count] = g_wrp_adc_samples.phase_r.v90;
        g_wrp_sample_int16[4][g_wrp_sample_count] = g_wrp_adc_samples.phase_y.v90;
        g_wrp_sample_int16[5][g_wrp_sample_count] = g_wrp_adc_samples.phase_b.v90;
        
        g_wrp_sample_int32[0][g_wrp_sample_count] = g_wrp_adc_samples.phase_r.i;
        g_wrp_sample_int32[1][g_wrp_sample_count] = g_wrp_adc_samples.phase_y.i;
        g_wrp_sample_int32[2][g_wrp_sample_count] = g_wrp_adc_samples.phase_b.i;
        g_wrp_sample_int32[3][g_wrp_sample_count] = g_wrp_adc_samples.neutral.i;
        
        g_wrp_sample_count++;
    }
    #endif /* METER_ENABLE_MEASURE_CPU_LOAD */
    #endif /* __DEBUG */

    /* 
     * METROLOGY AND EXTERNAL APPLICATION PROCESSING:
     * The sample is ready. Put it to each application need
    */
    if (R_CALIB_IsInCalibMode() == 0)
    {
        {
            /* Normal processing */
            EM_ADC_IntervalProcessing(&g_wrp_adc_samples);
        }
    }
    else
    {
        /* Calibration processing */
        R_CALIB_Sampling(&g_wrp_adc_samples);
    }

    /* Pop MACRx registers */
    MACRH = bkup_macrh;
    MACRL = bkup_macrl;
}

/******************************************************************************
* Function Name    : void EM_ADC_GainPhaseReset(EM_LINE line)
* Description      : Reset phase gain to lowest level
* Arguments        : None
* Functions Called : None
* Return Value     : None
******************************************************************************/
void EM_ADC_GainPhaseReset(EM_LINE line)
{
    g_EM_ADC_GainPhaseCurrentLevel[line] = 0;       /* Lowest */
    /* Apply gain */
    EM_ADC_SetGainEnum(line, g_wrp_adc_channel_gain[line][g_EM_ADC_GainPhaseCurrentLevel[line]]);
}

/******************************************************************************
* Function Name    : void EM_ADC_GainPhaseIncrease(void)
* Description      : Increase phase gain 1 level & set the gain level to port
* Arguments        : None
* Functions Called : EM_ADC_GainPhaseSet()
* Return Value     : None
******************************************************************************/
void EM_ADC_GainPhaseIncrease(EM_LINE line)
{
    if (g_EM_ADC_GainPhaseCurrentLevel[line] >= EM_GAIN_PHASE_NUM_LEVEL_MAX-1)  /* Is highest gain? */
    {
        return; /* Do nothing */
    }
    else    /* Still exist higher gain */
    {
        g_EM_ADC_GainPhaseCurrentLevel[line]++; /* Increase level count */
        /* Apply gain */
        EM_ADC_SetGainEnum(line, g_wrp_adc_channel_gain[line][g_EM_ADC_GainPhaseCurrentLevel[line]]);
    }
}

/******************************************************************************
* Function Name    : void EM_ADC_GainPhaseDecrease(void)
* Description      : Decrease phase gain 1 level & set the gain level to port
* Arguments        : None
* Functions Called : EM_ADC_GainPhaseSet()
* Return Value     : None
******************************************************************************/
void EM_ADC_GainPhaseDecrease(EM_LINE line)
{
    if (g_EM_ADC_GainPhaseCurrentLevel[line] == 0)  /* Is lowest gain? */
    {
        return; /* Do nothing */
    }
    else    /* Still exist lower gain */
    {
        g_EM_ADC_GainPhaseCurrentLevel[line]--; /* Decrease level count */
        /* Apply gain */
        EM_ADC_SetGainEnum(line, g_wrp_adc_channel_gain[line][g_EM_ADC_GainPhaseCurrentLevel[line]]);
    }
}
    
/******************************************************************************
* Function Name    : uint8_t EM_ADC_GainPhaseGetLevel(void)
* Description      : Get the current phase gain level
* Arguments        : None
* Functions Called : None
* Return Value     : None
******************************************************************************/
uint8_t EM_ADC_GainPhaseGetLevel(EM_LINE line)
{
    return g_EM_ADC_GainPhaseCurrentLevel[line];
}

/******************************************************************************
* Function Name    : void EM_ADC_SetPhaseCorrection(EM_LINE line, dsad_channel_t channel, float32_t degree)
* Description      : Core function to set phase correction
* Arguments        : EM_LINE line           : phase selection
*                  : dsad_channel_t channel : DSAD channel of selected phase
*                  : float32_t degree       : degree to compensate
* Functions Called : R_DSADC_AdjustPhaseDelay
* Return Value     : None
******************************************************************************/
void EM_ADC_SetPhaseCorrection(EM_LINE line, float32_t degree)
{
    degree = (degree < 0.0f) ? -degree : degree;

    switch (line)
    {
        case LINE_PHASE_R:
            EM_ADC_DriverSetPhaseStep(
                EM_ADC_CURRENT_DRIVER_CHANNEL_PHASE_R,
                (uint16_t)(degree / EM_ADC_DRIVER_PHASE_SHIFT_STEP)
            );
            break;
        case LINE_PHASE_Y:
            EM_ADC_DriverSetPhaseStep(
                EM_ADC_CURRENT_DRIVER_CHANNEL_PHASE_Y,
                (uint16_t)(degree / EM_ADC_DRIVER_PHASE_SHIFT_STEP)
            );
            break;
        case LINE_PHASE_B:
            EM_ADC_DriverSetPhaseStep(
                EM_ADC_CURRENT_DRIVER_CHANNEL_PHASE_B,
                (uint16_t)(degree / EM_ADC_DRIVER_PHASE_SHIFT_STEP)
            );
            break;
        case LINE_NEUTRAL:
            EM_ADC_DriverSetPhaseStep(
                EM_ADC_CURRENT_DRIVER_CHANNEL_NEUTRAL,
                (uint16_t)(degree / EM_ADC_DRIVER_PHASE_SHIFT_STEP)
            );
            break;
        default:
            break;
    }
}

/******************************************************************************
* Function Name    : void EM_ADC_SAMP_UpdateStep(float32_t fac)
* Description      : Update the step delay into sw delay circle and hw timer delay
* Arguments        : float32_t fac: measured line frequency
* Functions Called : EM_ADC_QuarterShiftTimer_LookupValue(): lookup timer value
*                  : R_TAU0_Channel1_SetValue(): set TDR value
* Return Value     : None
******************************************************************************/
void EM_ADC_SAMP_UpdateStep(float32_t fac)
{
    #ifdef METER_WRAPPER_ADC_COPY_REACTIVE_SAMPLE
    /* Update software integer  */  
    uint8_t     sw_delay_steps;
    float32_t   fsteps, total_steps;
    int16_t     tdr_value, lerp_t;
    
    /* Delay frequency updating */
    if (fac == g_previous_fac)
    {
        g_fac_update_counter = 0;
        return;
    }
    else
    {
        g_fac_update_counter++;
        if (g_fac_update_counter < EM_FAC_CHANGED_DETECTION_COUNT)
        {
            return;
        }
        else
        {
            g_previous_fac = fac;
            g_fac_update_counter = 0;
            /* Update by below routine */
        }
    }
    
    /*
     *                                  90.0f * fs
     * Calculate ideal total step: = -----------------
     *                                 fac * 360.0f
    */
    
    total_steps = ((90.0f/360.0f) * EM_GetCalibInfo().sampling_frequency)/ (fac);
                        
    sw_delay_steps = (uint8_t)total_steps;
    
    /* Reverse the fsteps as required */
    fsteps = 1.0f - (total_steps - sw_delay_steps); 
    
    /* Increase 1 step software delay for subtraction of TDR sample + DSAD->SAR voltage sample delay steps  */
    sw_delay_steps += 1 + EM_ADC_DELAY_STEP_VOLTAGE;
    
    tdr_value = (int16_t)(fsteps * (float32_t)EM_ADC_DRIVER_TAU_256US_SETTING);

	/* Record intermediate data (for checking only) */
	g_wrp_adc_calculated_tdr = tdr_value;
		
	/* Precalculate linear interpolation t constant and limit TDR setting to max or min
	 * 	t = (x-x0)/(x1-x0)
	 * 		Both range:
     *  		EM_ADC_DRIVER_TAU_MIN_THRESHOLD to 0
     *  		EM_ADC_DRIVER_TAU_256US_SETTING to EM_ADC_DRIVER_TAU_MAX_THRESHOLD
     * 		Currently the same on 512k, but it considered more meaningful to use separate calculation
	 * 	Limit TDR setting to max or min and used TIMER->SAR sample as one point in linear interpolation
    */
    if (tdr_value > EM_ADC_DRIVER_TAU_MAX_THRESHOLD)
    {
        lerp_t = (int16_t)(((int32_t)(tdr_value - EM_ADC_DRIVER_TAU_MAX_THRESHOLD) << 8) / (EM_ADC_DRIVER_TAU_256US_SETTING - EM_ADC_DRIVER_TAU_MAX_THRESHOLD));
        tdr_value = EM_ADC_DRIVER_TAU_MAX_THRESHOLD;
    }
    else if (tdr_value < EM_ADC_DRIVER_TAU_MIN_THRESHOLD)
    {
        lerp_t = (int16_t)(((int32_t)(tdr_value - 0) << 8) / (EM_ADC_DRIVER_TAU_MIN_THRESHOLD - 0));
        tdr_value = EM_ADC_DRIVER_TAU_MIN_THRESHOLD;
    }
    else
    {
        /* Within settable TDR range, use V90 sample with calculated tdr value */
		lerp_t = 0;
    }
    
    /* Make sure steps still within maximum buffer length */
    if (sw_delay_steps > EM_ADC_DELAY_VOLTAGE90_MAX_STEP)
    {
        /* Abnormal: out of buffer range, limit the buffer length */
        sw_delay_steps = EM_ADC_DELAY_VOLTAGE90_MAX_STEP;
    }
    else
    {
        /* SW delay steps within buffer size, no need to change */
    }

    /* Control timer delay, convert to us */
    R_TAU0_Channel1_SetValue(tdr_value);

    /* Apply new circle delay step and interpolation t constant */
    g_wrp_adc_voltage90_circle_step = sw_delay_steps;
    g_wrp_adc_v90_lerp_t = lerp_t;
        
    #endif /* METER_WRAPPER_ADC_COPY_REACTIVE_SAMPLE */
}
