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
 * File Name    : r_calib.c
 * Version      : 1.0
 * Description  : Main calibration module
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : 01.04.2013 First release
 *         : 31.12.2019 Revised for new metrology
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_dsadc.h"
#include "r_calib.h"            /* Calibration */
#include "r_calib_sampling.h"   /* Accumulation of calibration */
#include "r_hoco_trimming.h"
/* Standards library */
#include <math.h>               /* Maths */
#include <string.h>             /* Standard String */
#include <limits.h>

#include "em_core.h"            /* EM Core APIs */
#include "em_type.h"
#include "em_operation.h"
#include "wrp_em_adc.h"
#include "wrp_em_pulse.h"
#include "wrp_em_wdt.h"
#include "wrp_em_mcu.h"
#include "wrp_em_timer.h"
#include "config_storage.h"
#include "platform.h"

/* Application */



/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#define R_FLOAT32_IS_SAME_SIGN(x,y)     (((*(((uint8_t *)&(x))+3) & 0x80) ^ (*(((uint8_t *)&(y))+3) & 0x80))? 0 : 1)

/**********************************************************************************************************************
 Local Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
Imported global variables and functions (from other files)
 *********************************************************************************************************************/
extern void EM_ADC_SetGainValue(EM_LINE line, uint8_t gain);

/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/
r_calib_system g_calib_system;

/**********************************************************************************************************************
 Private (static) variables and functions
 *********************************************************************************************************************/
/* Pre-calculated information used for angle calibration, supporting 50Hz and 60Hz only */
static NEAR_PTR const r_calib_angle_data s_calib_angle_data[2][2] =
{
    /* 4K sampling frequency */
    {
        {
            R_CALIB_4K_50Hz_CIRCLE_DELAY_STEP,
            R_CALIB_4K_50Hz_PHASE_SHIFT_STEP,
            R_CALIB_4K_50Hz_MAX_ANGLE_ERR,
            R_CALIB_4K_50Hz_C,
            R_CALIB_4K_50Hz_SIN2C,
            R_CALIB_4K_50Hz_TANC,
        },
        {
            R_CALIB_4K_60Hz_CIRCLE_DELAY_STEP,
            R_CALIB_4K_60Hz_PHASE_SHIFT_STEP,
            R_CALIB_4K_60Hz_MAX_ANGLE_ERR,
            R_CALIB_4K_60Hz_C,
            R_CALIB_4K_60Hz_SIN2C,
            R_CALIB_4K_60Hz_TANC,
        },
    },
    /* 5k sampling frequency */
    {
        {
            R_CALIB_5K_50Hz_CIRCLE_DELAY_STEP,
            R_CALIB_5K_50Hz_PHASE_SHIFT_STEP,
            R_CALIB_5K_50Hz_MAX_ANGLE_ERR,
            R_CALIB_5K_50Hz_C,
            R_CALIB_5K_50Hz_SIN2C,
            R_CALIB_5K_50Hz_TANC,
        },
        {
            R_CALIB_5K_60Hz_CIRCLE_DELAY_STEP,
            R_CALIB_5K_60Hz_PHASE_SHIFT_STEP,
            R_CALIB_5K_60Hz_MAX_ANGLE_ERR,
            R_CALIB_5K_60Hz_C,
            R_CALIB_5K_60Hz_SIN2C,
            R_CALIB_5K_60Hz_TANC,
        },
    },
};

/**********************************************************************************************************************
 * Function Name : r_calib_wait_for_signal_stable
 * Interface     : void r_calib_wait_for_signal_stable(void)
 * Description   : Wait fixed time for signal stable during gain or phase shift changes
 * Arguments     : None
 * Return Value  : None
 *********************************************************************************************************************/
static void r_calib_wait_for_signal_stable(void)
{
    uint8_t i;

    /* Wait nx10ms so that ADC eliminate signal offset */
    for (i = 0; i < g_calib_system.p_args->stable_ndelay; i++)
    {
        EM_MCU_Delay(10000);
        EM_WDT_Restart();
    }
}

/**********************************************************************************************************************
 * Function Name : em_calib_lookup_derivation
 * Description   : Lookup to get derivation value
 * Arguments     : None
 * Return Value  : None
 *********************************************************************************************************************/
static float32_t em_calib_lookup_derivation(float32_t angle)
{
    float32_t cos_xc;

    /* -sin(2C) / cos^2(x+C), x in Rad */
    angle *= R_CALIB_PI_VALUE;
    angle /= 180.0f;
    cos_xc = cos(angle + g_calib_system.p_angle_table->c);

    return (-g_calib_system.p_angle_table->sin2c / (cos_xc * cos_xc));
}

/**********************************************************************************************************************
* Function Name : em_calib_convert_into_adc_gain
* Description   : Convert the calculated current gain into suitable value to set into ADC module
* Arguments     : Calculated current gain
* Function Calls: None
* Return Value  : The appropriate gain for ADC module
 *********************************************************************************************************************/
static uint8_t em_calib_convert_into_adc_gain(uint8_t calc_gain)
{
    if (calc_gain < 2)
    {
        return 1;
    }
    else if (calc_gain < 4)
    {
        return 2;
    }
    else if (calc_gain < 8)
    {
        return 4;
    }
    else if (calc_gain < 16)
    {
        return 8;
    }
    else if (calc_gain < 32)
    {
        return 16;
    }
    else
    {
        return 32;
    }
}

/**********************************************************************************************************************
* Function Name : r_calib_get_coeff
* Description   : Get coefficient from accumulator, number of sample and reference value
* Arguments     : float32_t * p_acc
*               : uint16_t *p_number_sample
*               : float32_t ref
* Return Value  : float32_t
 *********************************************************************************************************************/
static float32_t r_calib_get_coeff(float32_t * p_acc, uint16_t *p_number_sample, float32_t ref)
{
    float32_t coeff;
    coeff = EM_sqrt(*p_acc / *p_number_sample) / ref;
    return coeff;
}

/**********************************************************************************************************************
* Function Name : r_calib_radian_to_degrees
* Description   : Convert radian to degrees
* Arguments     : float32_t rad
* Return Value  : float32_t
 *********************************************************************************************************************/
static float32_t r_calib_radian_to_degrees(float32_t rad)
{
    return ((rad * 180.0f) / R_CALIB_PI_VALUE);
}

/**********************************************************************************************************************
* Function Name : r_calib_calculate_acc_signals_sub_step
* Description   : Calculate acc signals with substep 
* Arguments     : uint8_t substep:
*               : uint16_t * p_num_of_sample
*               : EM_ACCMODE_ACCUMULATOR *p_em_acc
* Return Value  : None
 *********************************************************************************************************************/
static uint8_t r_calib_calculate_acc_signals_sub_step(uint8_t substep, uint16_t * p_num_of_sample, EM_ACCMODE_ACCUMULATOR *p_em_acc)
{
    uint8_t status;

    /* Clean up and initialize data for calculation */
    memset((uint8_t *)&g_calib_system.p_data->share.signals, 0, sizeof(g_calib_system.p_data->share.signals));

    g_calib_system.p_data->share.signals.substep = substep;

    /* Run accumulation mode */
    if (EM_AccMode_Run(g_calib_system.p_args->cycle) != EM_ACCUMULATING)
    {
        return R_CALIB_PROCESS_ERROR_ACCUMULATION_FAILED;
    }
    /* Wait until finish sampling process */
    g_calib_system.p_data->start_sampling = TRUE;
    while (EM_AccMode_CheckStatus(p_num_of_sample, NULL) == EM_ACCUMULATING)
    {
        EM_WDT_Restart();
    }
    g_calib_system.p_data->start_sampling = FALSE;

    /* Get accumulator value from EM */
    EM_AccMode_GetAccumulator(p_em_acc);

    return R_CALIB_OK;
}

/**********************************************************************************************************************
* Function Name : r_calib_notify_event
* Description   : Notify user application on each step of calibration
* Arguments     : None
* Function Calls: None
* Return Value  : None
 *********************************************************************************************************************/
static void r_calib_notify_event(void)
{
    /* Notify user */
    if (g_calib_system.p_args->cb_notify != NULL)
    {
        g_calib_system.p_args->cb_notify(g_calib_system.p_output);
    }
}

/**********************************************************************************************************************
* Function Name : r_calib_calculate_sampling_frequency
* Description   : Trimming the HOCO and calculate actual sampling frequency of DSAD
* Arguments     : None
* Return Value  : uint8_t
 *********************************************************************************************************************/
uint8_t r_calib_calculate_sampling_frequency(void)
{
    float32_t expected_fs;

    /* Clean up and initialize data for calculation */
    g_calib_system.p_output->step = R_CALIB_STEP_FS;

    memset((uint8_t *)&g_calib_system.p_data->share.fs, 0, sizeof(g_calib_system.p_data->share.fs));
    /*  Raise flag for RTC interrupt synchronization */
    g_calib_system.p_data->share.fs.start_1s_count = TRUE;

    /* Wait until finish sampling process */
    g_calib_system.p_data->start_sampling = TRUE;
    while (g_calib_system.p_data->share.fs.start_1s_count == TRUE)
    {
        EM_WDT_Restart();
    }
    g_calib_system.p_data->start_sampling = FALSE;

    /* Process after sampling */
    if (g_calib_system.p_args->is_high_fs)
    {
        expected_fs = 5208.33f;
    }
    else
    {
        expected_fs = 3906.25f;
    }

    if ((g_calib_system.p_data->share.fs.nsample > (expected_fs * 1.02f)) ||
        (g_calib_system.p_data->share.fs.nsample < (expected_fs* 0.98f)))
    {
        return R_CALIB_PROCESS_ERROR_FS_OUT_OF_RANGE;
    }

    /* Asssign calculated parameter */
    g_calib_system.p_output->fs = (float32_t)g_calib_system.p_data->share.fs.nsample;

    r_calib_notify_event();

    return R_CALIB_OK;
}

/**********************************************************************************************************************
* Function Name : r_calib_calculate_and_set_current_gain
* Description   : Calculate and return phase/neutral current gain
*               : Then set the calculated value into ADC module
* Arguments     : None
* Return Value  : uint8_t
 *********************************************************************************************************************/
uint8_t r_calib_calculate_and_set_current_gain(void)
{
    float32_t   amplified_const;
    float32_t   calculated_gain;

    g_calib_system.p_output->step = R_CALIB_STEP_IGAIN;

    /* Bypass Igain calibration in case dual gain calibration */
    if (g_calib_system.p_args->num_of_gain_used != 1)
    {
        /* Assign to output (first gain always 1), sw second gain calculated in acc signals step */
        g_calib_system.p_output->gain = 1.0f;
        return R_CALIB_OK;
    }
    /* Bypass Igain calibration if fixed gain specified */
    else if (g_calib_system.p_args->fixed_gain_value != 0)
    {
        /* Assign to output */
        g_calib_system.p_output->gain = g_calib_system.p_args->fixed_gain_value;
        return R_CALIB_OK;
    }
    else
    {
        /* Clean up and initialize data for calculation */
        g_calib_system.p_data->share.gain.imax = LONG_MIN;
        g_calib_system.p_data->share.gain.finished = FALSE;

        g_calib_system.p_data->start_sampling = TRUE;
        while (g_calib_system.p_data->share.gain.finished == FALSE)
        {
            EM_WDT_Restart();
        }
        g_calib_system.p_data->start_sampling = FALSE;

        /*
         *          Calculation explanation
         *  Gain is used to make DSAD result reach Max Full Scale at MAX_SUPPORTED_CURRENT
         *                                      *Gain
         *  MAX_SUPPORTED_CURRENT   --> Amax[LSB] -------> 2^24 [LSB] Full scale of DSAD
         *                 2^24
         *  --> Gain = ------------
         *              Amax [LSB]
         *  And:
         *  MAX_SUPPORTED_CURRENT   -->      Amax       [LSB]
         *       calib_current      -->      Imax   [LSB]
         *         MAX_SUPPORTED_CURRENT
         *  Amax = --------------------- * Imax
         *            calib_current
         *                        2^24                          2^24
         *  --> Gain = ----------------------------- = ----------------------
         *             MAX_SUPPORTED_CURRENT            amplified_val * Imax
         *             --------------------- * Imax
         *             calib_current
         */
        /* Calculate current gain */
        amplified_const = g_calib_system.p_args->imax / g_calib_system.p_args->i;
        calculated_gain = ((float32_t)INT24_MAX / (g_calib_system.p_data->share.gain.imax * amplified_const));

        /* Check the usable range of gvalue */
        if (calculated_gain > g_calib_system.p_args->max_gvalue)
        {
            return R_CALIB_PROCESS_ERROR_IGAIN_OUT_RANGE;
        }

        /* Convert to ADC gain and assign to output */
        g_calib_system.p_output->gain = em_calib_convert_into_adc_gain((uint8_t)calculated_gain);

        /* Set to hardware (dependency on wrapper API) */
        EM_ADC_SetGainValue(g_calib_system.p_args->line, (uint8_t)g_calib_system.p_output->gain);
    }

    r_calib_notify_event();

    /* Wait before return to make signal stable for next step */
    r_calib_wait_for_signal_stable();

    return R_CALIB_OK;
}

/**********************************************************************************************************************
* Function Name : r_calib_calculate_acc_signals
* Description   : Calibrate to find coefficient of V, I, Power
*               : Also find coeff of I at 2nd gain for dual gain calibration
* Arguments     : None
* Return Value  : uint8_t
 *********************************************************************************************************************/
uint8_t r_calib_calculate_acc_signals(void)
{
    uint8_t status;
    uint16_t number_of_samples;
    EM_ACCMODE_ACCUMULATOR em_acc;
    float32_t icoeff_gain1;

    g_calib_system.p_output->step = R_CALIB_STEP_SIGNALS;

    if (g_calib_system.p_data->gain_index == 0)
    {
        if (g_calib_system.p_args->line != LINE_NEUTRAL)
        {
            /* First gain calibration, used as coeff for v, i and power */
            /* VRMS Coefficient */
            status = r_calib_calculate_acc_signals_sub_step(R_CALIB_SIGNALS_SUBSTEP_V, &number_of_samples, &em_acc);
            if (status != R_CALIB_OK)
            {
                return status;
            }
            g_calib_system.p_output->vcoeff = r_calib_get_coeff(&em_acc.acc0, &number_of_samples, g_calib_system.p_args->v);

            r_calib_notify_event();
        }
        else
        {
            g_calib_system.p_output->vcoeff = 0;
        }

        /* IRMS Coefficient */
        status = r_calib_calculate_acc_signals_sub_step(R_CALIB_SIGNALS_SUBSTEP_I, &number_of_samples, &em_acc);
        if (status != R_CALIB_OK)
        {
            return status;
        }
        g_calib_system.p_output->icoeff = r_calib_get_coeff(&em_acc.acc0, &number_of_samples, g_calib_system.p_args->i);

        /* Power Coefficient */
        g_calib_system.p_output->pcoeff = g_calib_system.p_output->vcoeff * g_calib_system.p_output->icoeff;

        r_calib_notify_event();
    }
    else
    {
        /* Second gain calibration, used Icoeff for calculating ratio and assign to gain1 */

        /* Calculate for IRMS coefficient to find the ratio */
        status = r_calib_calculate_acc_signals_sub_step(R_CALIB_SIGNALS_SUBSTEP_I, &number_of_samples, &em_acc);
        if (status != R_CALIB_OK)
        {
            return status;
        }
        icoeff_gain1 = r_calib_get_coeff(&em_acc.acc0, &number_of_samples, g_calib_system.p_args->i);

        g_calib_system.p_output->gain1 = icoeff_gain1 / g_calib_system.p_output->icoeff;

        r_calib_notify_event();
    }

    return R_CALIB_OK;
}

/**********************************************************************************************************************
* Function Name : r_calib_calculate_angle_error
* Description   : Accumulate and scan angle error
* Arguments     : None
* Return Value  : uint8_t
 *********************************************************************************************************************/
uint8_t r_calib_calculate_angle_error(void)
{
    uint8_t status, is_continue;
    float32_t   delta_error, theta = 0.0f;
    uint16_t    number_of_samples;
    EM_ACCMODE_ACCUMULATOR em_acc;

    g_calib_system.p_output->step = R_CALIB_STEP_ANGLE;

    /* Initate angle data
    * Start at 0 degree, Init delta error = 0
    */
    memset((uint8_t *)&g_calib_system.p_data->share.angle, 0, sizeof(g_calib_system.p_data->share.angle));

    /* Wait until finish accumulation */
    is_continue = TRUE;
    while (is_continue)
    {
        /* Reset phase shift controller */
        memset((uint8_t *)&g_calib_system.p_data->share.angle.phase_shift, 0, sizeof(g_calib_system.p_data->share.angle.phase_shift));

        /* Run accumulation mode */
        if (EM_AccMode_Run(g_calib_system.p_args->cycle_angle) != EM_ACCUMULATING)
        {
            return R_CALIB_PROCESS_ERROR_ACCUMULATION_FAILED;
        }

        /* Wait until finish sampling process */
        g_calib_system.p_data->start_sampling = TRUE;
        while (EM_AccMode_CheckStatus(&number_of_samples, NULL) == EM_ACCUMULATING)
        {
            EM_WDT_Restart();
        }
        g_calib_system.p_data->start_sampling = FALSE;

        /* Get accumulator value from EM */
        EM_AccMode_GetAccumulator(&em_acc);

        if (g_calib_system.p_data->gain_index == 1)
        {
            NOP();
        }

        /* delta error (x) = (cos (-phi + theta) / cos (phi + theta) - 1) */
        delta_error = (em_acc.acc1 / em_acc.acc0);
        delta_error -= 1.0f;

        /*
        * Get the initial delta_error, solve for theta,
        * set last_delta_error then start the approximation
        * with the initial theta.
        */
        if (g_calib_system.p_data->share.angle.initial_delta_error == 0.0f)
        {
            /*
                * Solve for theta
                *
                * theta = delta_error / [(delta_error + 2) * tanf(C)]
            */
            theta = (delta_error / ((delta_error + 2) * g_calib_system.p_angle_table->tanc));

            /* Change to degree */
            theta = r_calib_radian_to_degrees(theta);

            g_calib_system.p_data->share.angle.last_theta = theta;

            /* Look up the derivation */
            g_calib_system.p_data->share.angle.derivation = em_calib_lookup_derivation(theta);

            g_calib_system.p_data->share.angle.initial_delta_error = \
                g_calib_system.p_data->share.angle.last_delta_error = delta_error;

            is_continue = TRUE;
        }
        /* have large error & not change sign ?*/
        else if ((100.0f * EM_absf(delta_error)) >= R_CALIB_PHASE_ERROR_STOP_THRESHOLD &&
                 (100.0f * delta_error * g_calib_system.p_data->share.angle.last_delta_error > 0.0f))
        {
            /*
            * Calculate theta, min. grow up is 1step of Phase control register &
            * Update error, derivation for next approximation
            */
            g_calib_system.p_data->share.angle.last_delta_error = delta_error;
            theta -= r_calib_radian_to_degrees(delta_error / g_calib_system.p_data->share.angle.derivation);
            g_calib_system.p_data->share.angle.last_theta = theta;
            g_calib_system.p_data->share.angle.derivation = em_calib_lookup_derivation(theta);

            is_continue = TRUE;
        }
        /* reach small error */
        else
        {
            /*
            * roll back to the last when new error rate larger than the old
            */
            theta = g_calib_system.p_data->share.angle.last_theta;
            status = R_CALIB_OK;
            is_continue = FALSE;
        }

        /* acc0 and acc1 different sign indicate 90 degree detection (assume signal UPF) */
        if (R_FLOAT32_IS_SAME_SIGN(em_acc.acc0, em_acc.acc1) == FALSE)
        {
            status = R_CALIB_PROCESS_ERROR_OUT_ANGLE;
            is_continue = FALSE;
        }

        /* Both acc negative indicate reverse */
        if ((em_acc.acc0 < 0.0f) && (em_acc.acc1 < 0.0f))
        {
            status = R_CALIB_PROCESS_ERROR_REVERSE;
            is_continue = FALSE;
        }

        /* Stop if reach max delay time ? */
        if (EM_absf(theta) > g_calib_system.p_angle_table->max_angle_error)
        {
            status = R_CALIB_PROCESS_ERROR_MAX_ANGLE;
            is_continue = FALSE;
        }

        /* V must leading I */
        if (theta > 0.0f)
        {
            status = R_CALIB_PROCESS_ERROR_V_LEAD_I;
            is_continue = FALSE;
        }

        /* Dual gain output: assign theta even if it failed */
        if (g_calib_system.p_data->gain_index == 0)
        {
            g_calib_system.p_output->angle_error = theta;
        }
        else if (g_calib_system.p_data->gain_index == 1)
        {
            g_calib_system.p_output->angle_error1 = theta;
        }

        /* Set new calculated phase angle error */
        EM_ADC_SetPhaseCorrection(g_calib_system.p_args->line, theta);

        r_calib_notify_event();

        EM_WDT_Restart();
    }

    return status;
}

/**********************************************************************************************************************
* Function Name : r_calib_run
* Description   : Run all calibration steps
* Arguments     : None
* Return Value  : uint8_t
 *********************************************************************************************************************/
uint8_t r_calib_run(void)
{
    uint8_t status;

    /* Each calibration item will:
    * Call to each calibrating function
    * Check calibration result
    * Assign calibrated data to output
    **/

    if (g_calib_system.p_args->line == LINE_NEUTRAL)
    {
        status = r_calib_calculate_and_set_current_gain();

        if (status != R_CALIB_OK)
        {
            return status;
        }

        status = r_calib_calculate_acc_signals();

        if (status != R_CALIB_OK)
        {
            return status;
        }
    }
    else
    {
        status = R_CALIB_HocoTrimming();

        if (status != R_CALIB_OK)
        {
            return status;
        }

        status = r_calib_calculate_sampling_frequency();

        if (status != R_CALIB_OK)
        {
            return status;
        }

        status = r_calib_calculate_and_set_current_gain();

        if (status != R_CALIB_OK)
        {
            return status;
        }

        status = r_calib_calculate_acc_signals();

        if (status != R_CALIB_OK)
        {
            return status;
        }

        status = r_calib_calculate_angle_error();

        if (status != R_CALIB_OK)
        {
            return status;
        }

        /* Calibrating 2nd gain */
        if (g_calib_system.p_args->num_of_gain_used != 1)
        {
            /* Increase gain */
            EM_ADC_GainPhaseIncrease(g_calib_system.p_args->line);
            EM_ADC_SetPhaseCorrection(g_calib_system.p_args->line, 0.0f);
            r_calib_wait_for_signal_stable();
            g_calib_system.p_data->gain_index++;

            status = r_calib_calculate_acc_signals();

            if (status != R_CALIB_OK)
            {
                return status;
            }

            status = r_calib_calculate_angle_error();

            if (status != R_CALIB_OK)
            {
                return status;
            }
        }
    }

    /* Calibration done, reached here, means no error on the above steps, mark step finished */
    g_calib_system.p_output->step = R_CALIB_STEP_FINISHED;

    return R_CALIB_OK;
}

/**********************************************************************************************************************
* Function Name : r_calib_check_parameter
* Description   : Check parameter when calling calibrate function
* Arguments     : r_calib_args_t * p_args
*               : r_calib_work_t * p_works
*               : r_calib_output_t * p_output
* Return Value  : uint8_t
 *********************************************************************************************************************/
static uint8_t r_calib_check_parameter(r_calib_args_t * p_args, r_calib_work_t * p_works, r_calib_output_t * p_output)
{
    if (p_args == NULL || p_works == NULL || p_output == NULL)
    {
        return R_CALIB_INIT_ERROR_NULL_PARAM;
    }

    if ((p_args->timer_period != 500) && (p_args->timer_period != 1000))
    {
        return R_CALIB_INIT_ERROR_UNSUPPORTED_CALIB_TIMER_PERIOD;
    }

    if ((p_args->num_of_gain_used != 1) && (p_args->num_of_gain_used != 2))
    {
        return R_CALIB_INIT_ERROR_NUMBER_OF_GAIN_OUT_OF_RANGE;
    }

    /* Check max gain value setting */
    if ((p_args->line <= LINE_PHASE_B) &&
        (p_args->num_of_gain_used == 1) &&
        (p_args->max_gvalue == 0))
    {
        return R_CALIB_INIT_ERROR_MAX_GVALUE_OUT_RANGE;
    }

    if (p_args->line > LINE_NEUTRAL)
    {
        return R_CALIB_INIT_ERROR_CALIB_LINE_OUT_OF_RANGE;
    }

    /* Check input calibration settings */
    if (p_args->cycle <= 1.0f || p_args->cycle_angle <= 1.0f)
    {
        return R_CALIB_INIT_ERROR_CALIB_CYCLE_INVALID;
    }

    /* Minimum input value of V, I, Imax */
    if (p_args->v <= 1.0f || p_args->i <= 1.0f)
    {
        return R_CALIB_INIT_ERROR_INPUT_SIGNAL_TOO_SMALL;
    }

    /* Require imax > 0 when there's only single gain */
    if ((p_args->line <= LINE_PHASE_B) &&
        (p_args->num_of_gain_used == 1) &&
        (p_args->imax <= p_args->i))
    {
        return R_CALIB_INIT_ERROR_IMAX_VALUE_INVALID;
    }

    /* Only support 50 and 60Hz calibration */
    if (p_args->fac == 50)
    {
        g_calib_system.p_angle_table = (r_calib_angle_data *)&s_calib_angle_data[p_args->is_high_fs][0];
    }
    else if (p_args->fac == 60)
    {
        g_calib_system.p_angle_table = (r_calib_angle_data *)&s_calib_angle_data[p_args->is_high_fs][1];
    }
    else
    {
        return R_CALIB_INIT_ERROR_LINE_FREQUENCY_OUT_OF_RANGE;
    }

    return R_CALIB_OK;
}

/**********************************************************************************************************************
* Function Name : r_calib_limit_args_range
* Description   : Limit the value range of arguments for correct opertaion internally
* Arguments     : r_calib_args_t * p_args
* Return Value  : uint8_t
 *********************************************************************************************************************/
static void r_calib_limit_args_range(r_calib_args_t * p_args)
{
    if (p_args->line == LINE_NEUTRAL)
    {
        p_args->num_of_gain_used = 1;
    }

    /* Limit range of input high fs value to 0 or 1 only for array indexing */
    if ((p_args->is_high_fs >= 1))
    {
        p_args->is_high_fs = 1;
    }
}

/**********************************************************************************************************************
* Function Name : R_CALIB_Calibrate
* Description   : Start auto calibration
* Arguments     : r_calib_args_t * p_args       : Max supported measured current of MCU
*               : r_calib_work_t * p_works      : Working area for calibration
*               : r_calib_output_t * p_output   : Calibrated current
* Return Value  : uint8_t: initiate result. Check header for details
***********************************************************************************************************************/
uint8_t R_CALIB_Calibrate(r_calib_args_t * p_args, r_calib_work_t * p_works, r_calib_output_t * p_output)
{
    uint8_t i;
    uint8_t status;
    
    memset(&g_calib_system, 0, sizeof(g_calib_system));

    g_calib_system.enabled = FALSE;

    if (status = r_calib_check_parameter(p_args, p_works, p_output) != R_CALIB_OK)
    {
        return status;
    }

    r_calib_limit_args_range(p_args);

    /* Assign allocated memory to working pointer data */
    g_calib_system.p_args = p_args;
    g_calib_system.p_data = (r_calib_data_t *)p_works;
    g_calib_system.p_output = p_output;

    memset((uint8_t *)g_calib_system.p_data, 0, sizeof(r_calib_data_t));
    memset((uint8_t *)g_calib_system.p_output, 0, sizeof(r_calib_output_t));

    g_calib_system.enabled = TRUE;

    /* Initialize the phase */
    EM_ADC_SetPhaseCorrection(g_calib_system.p_args->line, 0.0f);

    /* Initialize the gain of current */
    if (p_args->num_of_gain_used == 1)
    {
        if (p_args->fixed_gain_value != 0)
        {
            /* Fixed gain specified */
            p_args->fixed_gain_value = em_calib_convert_into_adc_gain(p_args->fixed_gain_value);
            EM_ADC_SetGainValue(p_args->line, p_args->fixed_gain_value);
        }
        else
        {
            /* Auto gain calculation, start from gain 1 */
            EM_ADC_SetGainValue(p_args->line, 1);
        }
    }
    else
    {
        /* Assume 2 gain, reset to first gain */
        EM_ADC_GainPhaseReset(p_args->line);
    }

    /* Synchronize to p_output line */
    g_calib_system.p_output->line = g_calib_system.p_args->line;

    EM_TIMER_Stop();
    r_calib_wait_for_signal_stable();

    /* Initial callback */
    r_calib_notify_event();

    /* Internal calibration run */
    status = r_calib_run();

    /* Final callback */
    r_calib_notify_event();

    /* Calibration done, reset all state */
    g_calib_system.enabled = FALSE;

    EM_TIMER_Start();

    return status;
}

/**********************************************************************************************************************
* Function Name : R_CALIB_SetDefaultCalibArgs
* Description   : Initialize the calibration argument with default value
* Arguments     : r_calib_args_t * p_args
* Return Value  : None
***********************************************************************************************************************/
void R_CALIB_SetDefaultCalibArgs(r_calib_args_t * p_args)
{
    p_args->timer_period = 500;
    p_args->max_gvalue = 64;
    p_args->num_of_gain_used = 1;
    p_args->fixed_gain_value = 0;
    p_args->cpu_clock = 24;
    p_args->is_high_fs = 0;
    p_args->stable_ndelay = 20;
    p_args->cb_notify = NULL;

    p_args->cycle = 150;
    p_args->cycle_angle = 150;
    p_args->v = 220.0f;
    p_args->i = 5.0f;
    p_args->imax = 60.0f;
    p_args->fac = 50.0f;

    p_args->line = LINE_PHASE_R;
}

/**********************************************************************************************************************
* Function Name : R_CALIB_IsInCalibMode
* Description   : Used for background operation to know calibration status
* Arguments     : None
* Return Value  : uint8_t: 1 in calib, 0 normal operation
***********************************************************************************************************************/
uint8_t R_CALIB_IsInCalibMode(void)
{
    return g_calib_system.enabled;
}
