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
* File Name    : r_calib_sampling.h
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : CCRL
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : Internal definition and sampling API for calibration
***********************************************************************************************************************/

#ifndef _R_CALIB_SAMPLING_H
#define _R_CALIB_SAMPLING_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "typedef.h"                /* GSCE Standard Typedef */
#include "r_calib.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/* Constant number of sample for gain calculation */
#define R_CALIB_NUM_SAMPLE_FOR_CALC_GAIN                (100)           /* Must greater than 1 line cycle */

#define R_CALIB_PI_VALUE                                (3.141592654f)  /* PI */

#define INT24_MAX                                       (8388608)       /* 2^23 */

#define R_CALIB_PHCR_REGISTER_MAX_VALUE                 (1151)          /* Max value can be set in DSADPHCRx of I1C */

#define R_CALIB_PHASE_ERROR_STOP_THRESHOLD              (0.0125f)       /* Stop threshold for delta error calculation */
#define R_CALIB_PHASE_ERROR_MIN_THRESHOLD               (-0.59529951f)  /* Min threshold for delta error calculation */
#define R_CALIB_PHASE_ERROR_MAX_THRESHOLD               (1.470963154f)  /* Max threshold for delta error calculation */

/* 3906.25 Hz sampling frequency pre-calculated angle data */
#define R_CALIB_4K_50Hz_CIRCLE_DELAY_STEP               (13)                                                                    /* 13 step * 4.608 ~ 59.904 degree */
#define R_CALIB_4K_50Hz_PHASE_SHIFT_STEP                (0.0120f)                                                               /* Oversampling ratio: 384*fs, 1 step 0.012 degree (on I1C) */
#define R_CALIB_4K_50Hz_MAX_ANGLE_ERR                   (R_CALIB_PHCR_REGISTER_MAX_VALUE * R_CALIB_4K_50Hz_PHASE_SHIFT_STEP)    /* Max abs angle error for setting into Phase Control Register */
#define R_CALIB_4K_50Hz_C                               (1.045522035f)                                                          /* C in Rad of 59.904 degree */
#define R_CALIB_4K_50Hz_SIN2C                           (0.867696054f)                                                          /* Sin(2C) */
#define R_CALIB_4K_50Hz_TANC                            (1.725368131f)                                                          /* Tan(C) */

#define R_CALIB_4K_60Hz_CIRCLE_DELAY_STEP               (10)                                                                    /* 10 step * 5.5296 ~ 55.296 degree */
#define R_CALIB_4K_60Hz_PHASE_SHIFT_STEP                (0.0144f)                                                               /* Oversampling ratio: 384*fs, 1 step 0.0144 degree (on I1C) */
#define R_CALIB_4K_60Hz_MAX_ANGLE_ERR                   (R_CALIB_PHCR_REGISTER_MAX_VALUE * R_CALIB_4K_60Hz_PHASE_SHIFT_STEP)    /* Max abs angle error for setting into Phase Control Register */
#define R_CALIB_4K_60Hz_C                               (0.965097263f)                                                          /* C in Rad of 55.296 degree */
#define R_CALIB_4K_60Hz_SIN2C                           (0.936108653f)                                                          /* Sin(2C) */
#define R_CALIB_4K_60Hz_TANC                            (1.443968007f)                                                          /* Tan(C) */

/* 5208.33 Hz sampling frequency pre-calculated angle data */
#define R_CALIB_5K_50Hz_CIRCLE_DELAY_STEP               (17)                                                                    /* 17 step * 3.456 ~ 58.752 degree */
#define R_CALIB_5K_50Hz_PHASE_SHIFT_STEP                (0.0090f)                                                               /* Oversampling ratio: 384*fs, 1 step 0.009 degree (on I1C) */
#define R_CALIB_5K_50Hz_MAX_ANGLE_ERR                   (R_CALIB_PHCR_REGISTER_MAX_VALUE * R_CALIB_5K_50Hz_PHASE_SHIFT_STEP)    /* Max abs angle error for setting into Phase Control Register */
#define R_CALIB_5K_50Hz_C                               (1.025415842f)                                                          /* C in Rad of 58.752 degree */
#define R_CALIB_5K_50Hz_SIN2C                           (0.886978595f)                                                          /* Sin(2C) */
#define R_CALIB_5K_50Hz_TANC                            (1.648078708f)                                                          /* Tan(C) */

#define R_CALIB_5K_60Hz_CIRCLE_DELAY_STEP               (14)                                                                    /* 14 step * 4.1472 ~ 58.0608 degree */
#define R_CALIB_5K_60Hz_PHASE_SHIFT_STEP                (0.0108f)                                                               /* Oversampling ratio: 384*fs, 1 step 0.0108 degree (on I1C) */
#define R_CALIB_5K_60Hz_MAX_ANGLE_ERR                   (R_CALIB_PHCR_REGISTER_MAX_VALUE * R_CALIB_5K_60Hz_PHASE_SHIFT_STEP)    /* Max abs angle error for setting into Phase Control Register */
#define R_CALIB_5K_60Hz_C                               (1.013352126f)                                                          /* C in Rad of 58.0608 degree */
#define R_CALIB_5K_60Hz_SIN2C                           (0.897861659f)                                                          /* Sin(2C) */
#define R_CALIB_5K_60Hz_TANC                            (1.604119824f)                                                          /* Tan(C) */

/* Buffer length for angle calibration */
#define R_CALIB_MAX_CIRCLE_LENGTH                       (17 + 1)    /* Worst case at 50Hz, 5k fs */

#define R_CALIB_SIGNALS_SUBSTEP_V                       (0)
#define R_CALIB_SIGNALS_SUBSTEP_I                       (1)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct tagCalibSample
{
    EM_SW_SAMP_TYPE v;
    EM_SW_SAMP_TYPE i;
} r_calib_samples;

typedef struct tagRCalibData
{
    r_calib_samples samples;
    
    uint8_t start_sampling;
    uint8_t gain_index;

    union tagEMCalibationShared
    {
        struct tagEMCalibrationDataShareFs
        {
            uint8_t start_1s_count;
            uint8_t start_count_sample;
            uint8_t rtc_start_count;
            uint8_t rtc_int_count;
            uint16_t nsample;
        } fs;

        struct tagEMCalibrationDataShareGain
        {
            uint8_t finished;
            uint16_t nsample;
            EM_SW_SAMP_TYPE imax;
        } gain;

        struct tagEMCalibrationDataShareSignals
        {
            uint8_t substep;
        } signals;

        struct tagEMCalibrationAngle
        {
            float32_t   last_theta;                     /* Last theta angle */
            float32_t   derivation;                     /* Derivation value */
            float32_t   initial_delta_error;            /* Initial delta error rate */
            float32_t   last_delta_error;               /* Last delta error */

            struct
            {
                int8_t          pos;
                uint8_t         ready;
                uint16_t        ready_count;
                EM_SW_SAMP_TYPE circle0[R_CALIB_MAX_CIRCLE_LENGTH];
                EM_SW_SAMP_TYPE circle1[R_CALIB_MAX_CIRCLE_LENGTH];
            } phase_shift;

        } angle;

    } share;
} r_calib_data_t;

typedef struct tagEMCalibAngleDataAngleFixed
{
    uint16_t circle_delay_step;
    float32_t dsad_phase_shift_step;
    float32_t max_angle_error;
    float32_t c;
    float32_t sin2c;
    float32_t tanc;

} r_calib_angle_data;

typedef struct tagCalibSystem
{
    uint8_t             enabled;
    r_calib_args_t      * p_args;
    r_calib_output_t    * p_output;
    r_calib_data_t      * p_data;
    r_calib_angle_data  * p_angle_table;
} r_calib_system;

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/

#endif /* _R_CALIB_SAMPLING_H */

