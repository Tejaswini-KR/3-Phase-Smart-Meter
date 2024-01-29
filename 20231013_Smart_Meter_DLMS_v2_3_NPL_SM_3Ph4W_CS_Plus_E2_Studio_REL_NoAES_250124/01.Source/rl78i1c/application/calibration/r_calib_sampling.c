/**********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2019 Renesas Electronics Corporation. All rights reserved.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * File Name    : r_calib_sampling.c
 * Version      : 1.0
 * Description  : Calib sampling module
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : 01.04.2013 First release
 *         : 31.12.2019 Revised for new metrology
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
/* Driver */
#include "r_cg_macrodriver.h"   /* Macro Driver Definitions */

/* Middleware */
#include "typedef.h"            /* GSCE Standard Typedef */

#include "em_core.h"            /* EM Core APIs */
#include "em_type.h"
#include "em_operation.h"

/* Wrapper */
#include "wrp_em_wdt.h"         /* Wrapper EM WDT */
#include "wrp_em_adc.h"         /* Wrapper EM ADC */
#include "wrp_em_mcu.h"            /* Wrapper MCU */
#include "wrp_em_sw_config.h"   /* SW config info, store ADC channels mapping */
#include "rl78_sw_hpf16.h"

/* Application */
#include <string.h>             /* Standard string lib */
#include <math.h>               /* Standard mathematics lib */
#include <limits.h>
#include "platform.h"           /* Platform definition */
#include "r_calib_sampling.h"   /* Sampling for auto calibration */
#include "r_calib.h"            /* Calculation */


/* Driver layer */

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
/* Function macro definition */
/* Macro function to do phase shift */
#define R_CALIB_DO_PHASESHIFT(in0, in1, out0, out1, phase_shift, step) {                            \
    /* PUSH: Add the signal into the data circle at circlepos position */                           \
    phase_shift.circle0[phase_shift.pos] = in0;                                                     \
    phase_shift.circle1[phase_shift.pos] = in1;                                                     \
    /* POP: Get the signal from data circle from (g_calib_phase_shift_pos + steps) position */      \
    out0 = phase_shift.circle0[(phase_shift.pos + step) % (step+1)];                                \
    out1 = phase_shift.circle1[(phase_shift.pos + step) % (step+1)];                                \
    /* Scroll the circle, scroll left */                                                            \
    phase_shift.pos--;                                                                              \
    if (phase_shift.pos == -1)                                                                      \
    {                                                                                               \
        phase_shift.pos = step;                                                                     \
    }                                                                                               \
    if (phase_shift.ready_count >= (step + 1))                                                      \
    {                                                                                               \
        phase_shift.ready = TRUE;                                                                   \
    }                                                                                               \
    else                                                                                            \
    {                                                                                               \
        phase_shift.ready_count++;                                                                  \
    }                                                                                               \
}

/**********************************************************************************************************************
 Local Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
Imported global variables and functions (from other files)
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/
extern r_calib_system g_calib_system;

/**********************************************************************************************************************
 Private (static) variables and functions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name : r_calib_sampling_for_fs
 * Description   : Count up the number of ADC ISR in 1s
 * Arguments     : None
 * Return Value  : None
 **********************************************************************************************************************/
static void r_calib_sampling_for_fs(void)
{
    EM_MCU_Delay(20);
    if (g_calib_system.p_data->share.fs.start_count_sample == 1)
    {
        g_calib_system.p_data->share.fs.nsample++;
    }
}

/**********************************************************************************************************************
 * Function Name : r_calib_sampling_for_igain
 * Description   : Control sampling process for calculating current gain
 * Arguments     : None
 * Return Value  : None
 **********************************************************************************************************************/
static void r_calib_sampling_for_igain(void)
{
    if (g_calib_system.p_data->share.gain.finished == TRUE)
    {
        return;
    }

    /* Find max value */
    if (g_calib_system.p_data->share.gain.imax < g_calib_system.p_data->samples.i)
    {
        g_calib_system.p_data->share.gain.imax = g_calib_system.p_data->samples.i;
    }

    /* Increase the number of current sample */
    g_calib_system.p_data->share.gain.nsample++;

    if (g_calib_system.p_data->share.gain.nsample >= R_CALIB_NUM_SAMPLE_FOR_CALC_GAIN)
    {
        /* Set flag to confirm finish sampling process */
        g_calib_system.p_data->share.gain.finished = TRUE;
    }
}

/**********************************************************************************************************************
 * Function Name : r_calib_sampling_for_acc_signals
 * Description   : Control sampling process for accumulation
 * Arguments     : None
 * Return Value  : None
 **********************************************************************************************************************/
static void r_calib_sampling_for_acc_signals(void)
{
    EM_ACCMODE_SAMPLES em_accmode_sample;

    if (EM_AccMode_CheckStatus(NULL, NULL) != EM_ACCUMULATING)
    {
        return;
    }

    /* Accumulated voltage signal */
    if (g_calib_system.p_data->share.signals.substep == R_CALIB_SIGNALS_SUBSTEP_V)
    {
        em_accmode_sample.signal0 = g_calib_system.p_data->samples.v;
        em_accmode_sample.signal1 = g_calib_system.p_data->samples.v;

        EM_ADC_AccMode_IntervalProcessing(&em_accmode_sample);
    }

    /* Accumulated phase current signal */
    if (g_calib_system.p_data->share.signals.substep == R_CALIB_SIGNALS_SUBSTEP_I)
    {
        em_accmode_sample.signal0 = g_calib_system.p_data->samples.i;
        em_accmode_sample.signal1 = g_calib_system.p_data->samples.i;

        EM_ADC_AccMode_IntervalProcessing(&em_accmode_sample);
    }
}

/**********************************************************************************************************************
 * Function Name : r_calib_sampling_for_angle_error
 * Description   : Sampling for calculate angle error
 * Arguments     : None
 * Return Value  : None
 **********************************************************************************************************************/
static void r_calib_sampling_for_angle_error(void)
{
    EM_ACCMODE_SAMPLES em_accmode_sample;
    EM_SW_SAMP_TYPE    v_shifted, i_shifted;

    if (EM_AccMode_CheckStatus(NULL, NULL) != EM_ACCUMULATING)
    {
        return;
    }

    /* Shift voltage and current to create power0 and power1 */
    R_CALIB_DO_PHASESHIFT(
        g_calib_system.p_data->samples.v,
        g_calib_system.p_data->samples.i,
        v_shifted,
        i_shifted,
        g_calib_system.p_data->share.angle.phase_shift,
        g_calib_system.p_angle_table->circle_delay_step
    );
    
    em_accmode_sample.signal0 = g_calib_system.p_data->samples.v;
    em_accmode_sample.signal1 = i_shifted;

    em_accmode_sample.signal2 = v_shifted;
    em_accmode_sample.signal3 = g_calib_system.p_data->samples.i;

    EM_ADC_AccMode_IntervalProcessing(&em_accmode_sample);
}

/**********************************************************************************************************************
 * Function Name : R_CALIB_Sampling
 * Description   : Do sampling for calibration module
 *               : Callback function which is used to register into ADC ISR
 * Arguments     : EM_SAMPLES * p_samples
 * Return Value  : None
 **********************************************************************************************************************/
void R_CALIB_Sampling(EM_SAMPLES * p_samples)
{
    if (g_calib_system.enabled != 1)
    {
        return;
    }

    if (g_calib_system.p_args->line == LINE_PHASE_R)
    {
        g_calib_system.p_data->samples.v = p_samples->phase_r.v;
        g_calib_system.p_data->samples.i = p_samples->phase_r.i;
    }
    else if (g_calib_system.p_args->line == LINE_PHASE_Y)
    {
        g_calib_system.p_data->samples.v = p_samples->phase_y.v;
        g_calib_system.p_data->samples.i = p_samples->phase_y.i;
    }
    else if (g_calib_system.p_args->line == LINE_PHASE_B)
    {
        g_calib_system.p_data->samples.v = p_samples->phase_b.v;
        g_calib_system.p_data->samples.i = p_samples->phase_b.i;
    }
    else if (g_calib_system.p_args->line == LINE_NEUTRAL)
    {
        g_calib_system.p_data->samples.i = p_samples->neutral.i;
    }
    else
    {
        return;
    }

    if (g_calib_system.p_data->start_sampling == FALSE)
    {
        return;
    }

    switch (g_calib_system.p_output->step)
    {
        case R_CALIB_STEP_FS:
            r_calib_sampling_for_fs();
            break;
        case R_CALIB_STEP_IGAIN:
            r_calib_sampling_for_igain();
            break;
        case R_CALIB_STEP_SIGNALS:
            r_calib_sampling_for_acc_signals();
            break;
        case R_CALIB_STEP_ANGLE:
            r_calib_sampling_for_angle_error();
            break;
        default:
            break;
    }
}

/**********************************************************************************************************************
 * Function Name : R_CALIB_RTCConstantInterruptCallback
 * Description   : Callback function, which is used to registered into driver layer
 * Arguments     : None
 * Return Value  : None
 **********************************************************************************************************************/
void R_CALIB_RTCConstantInterruptCallback(void)
{
    if (g_calib_system.enabled != 1 ||
        g_calib_system.p_output->step != R_CALIB_STEP_FS ||
        g_calib_system.p_data->share.fs.start_1s_count == 0)
    {
        return;
    }

    /* Wait until first interrupt of RTC for synchronization */
    if (g_calib_system.p_data->share.fs.rtc_start_count == FALSE)
    {
        /* Raise signal to start counting number of sample in DSAD interrupt */
        g_calib_system.p_data->share.fs.start_count_sample = TRUE;
        g_calib_system.p_data->share.fs.rtc_start_count = TRUE;

        /* Set RTC counter value */
        if (g_calib_system.p_args->timer_period == 1000) 
        {
            g_calib_system.p_data->share.fs.rtc_int_count = 1;
        }
        else 
        {
            g_calib_system.p_data->share.fs.rtc_int_count = 2;
        }
    }
    else
    {
        /* Check sample counting time */
        g_calib_system.p_data->share.fs.rtc_int_count--;
        if (g_calib_system.p_data->share.fs.rtc_int_count == 0)
        {
            /* Confirm finish counting fs */
            g_calib_system.p_data->share.fs.start_count_sample = FALSE;
            g_calib_system.p_data->share.fs.rtc_start_count = FALSE;
            g_calib_system.p_data->share.fs.start_1s_count = FALSE;
        }
    }
}
