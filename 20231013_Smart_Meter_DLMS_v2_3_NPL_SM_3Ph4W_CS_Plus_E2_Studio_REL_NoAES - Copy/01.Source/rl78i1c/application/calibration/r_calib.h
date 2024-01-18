/******************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_calib.h
* Version      : 1.00
* Description  : 
* Note         : 
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 01.04.2013
******************************************************************************/

#ifndef _R_CALIB_H
#define _R_CALIB_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "em_type.h"
#include <math.h>

/******************************************************************************
Macro definitions
******************************************************************************/
/* For calibration */
#define R_CALIB_OK                                              0           /* No error */

/* Init error code */
#define R_CALIB_INIT_ERROR_NULL_PARAM                           1           /* NULL in any params */
#define R_CALIB_INIT_ERROR_UNSUPPORTED_CALIB_TIMER_PERIOD       2           /* Period not 0.5s (500) or 1s (1000) */
#define R_CALIB_INIT_ERROR_NUMBER_OF_GAIN_OUT_OF_RANGE          3           /* Supported gain 1 or 2 */
#define R_CALIB_INIT_ERROR_MAX_GVALUE_OUT_RANGE                 4           /* Expected calculated gain when calib phase, 1 gain */

#define R_CALIB_INIT_ERROR_CALIB_LINE_OUT_OF_RANGE              5           /* Line I > LINE_NEUTRAL */
#define R_CALIB_INIT_ERROR_CALIB_CYCLE_INVALID                  6           /* Either cycle or cycle_angle <= 1 */
#define R_CALIB_INIT_ERROR_INPUT_SIGNAL_TOO_SMALL               7           /* Reference V or I <= 1 */
#define R_CALIB_INIT_ERROR_IMAX_VALUE_INVALID                   8           /* Calib phase, 1 gain, imax < reference I */
#define R_CALIB_INIT_ERROR_LINE_FREQUENCY_OUT_OF_RANGE          9           /* Line frequency 50 or 60 only (Hz) */

#define R_CALIB_PROCESS_ERROR_ACCUMULATION_FAILED               21          /* Accumulation in EM failed */
#define R_CALIB_PROCESS_ERROR_FS_OUT_OF_RANGE                   22          /* Calculated sampling fs out of known value */
#define R_CALIB_PROCESS_ERROR_IGAIN_OUT_RANGE                   23          /* Calculated gain larger than max expected gain */
#define R_CALIB_PROCESS_ERROR_MAX_ANGLE                         24          /* Reference V-I angle exceed adjustable range */
#define R_CALIB_PROCESS_ERROR_OUT_ANGLE                         25          /* Reference V-I could be not UPF */
#define R_CALIB_PROCESS_ERROR_REVERSE                           26          /* Sampled V-I signal reversed */
#define R_CALIB_PROCESS_ERROR_V_LEAD_I                          27          /* Calculated angle positive, V leading I */

/* Redirect metrology math functions to equivalent standard library functions */
#define EM_sqrt     sqrtf
#define EM_absf     fabsf

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef enum tagCalibSteps
{
    R_CALIB_STEP_NOT_INITIATED = 0x00,
    R_CALIB_STEP_FS,
    R_CALIB_STEP_IGAIN,
    R_CALIB_STEP_SIGNALS,
    R_CALIB_STEP_ANGLE,
    R_CALIB_STEP_FINISHED = 0xFF,
} r_calib_steps_t;

typedef uint16_t r_calib_work_t[128];   /* 128x2 bytes even alignment working area for calibration */

typedef struct
{
    float32_t       fs;             /* Sampling frequency */
    float32_t       gain;           /* Current gain */
    float32_t       gain1;          /* Current gain 1 */
    float32_t       vcoeff;         /* Voltage coefficient */
    float32_t       icoeff;         /* Current coefficient */
    float32_t       pcoeff;         /* Power coefficient, for active, reactive and apparent */
    float32_t       angle_error;    /* Angle error between current and volt */
    float32_t       angle_error1;   /* Angle error between current and volt gain 1 */
    EM_LINE         line;           /* Calibration line */
    r_calib_steps_t step;           /* Current step during calibration */
} r_calib_output_t;

typedef void(FAR_FUNC *fp_calib_notify) (r_calib_output_t * p_output);  /* FP registered to receive event notification from calibration to user */

typedef struct tagCalibArgs
{
    uint16_t        timer_period;       /* 1000 or 500 only (corresponding to 1s or 0.5s) */
    uint16_t        max_gvalue;         /* Maximum gain value (before convert to dsasd gain value) (using single gain) */
    uint8_t         num_of_gain_used;   /* 1 or 2 */
    uint8_t         fixed_gain_value;   /* Calib 1 gain, specified if need to bypass Igain calibration, 0 assume set by calibration */
    uint8_t         cpu_clock;          /* CPU clock in MHz (for V90 calibration) */
    uint8_t         is_high_fs;         /* Advance option: Normal fs: 3906 Hz (4k). High fs: 5208 Hz (5.2k) */
    uint8_t         stable_ndelay;      /* Advance option: Internal delay between each phase and gain set, in multiple of 10ms (10 is recommended (100ms)) */

    /* Notification event callback fp */
    fp_calib_notify cb_notify;          /* Call back on step change or in approximation */

    /* Power supply parameters */
    uint8_t         cycle;              /* Number of line cycle used for fs, gain and coefficient calibration */
    uint8_t         cycle_angle;        /* Number of line cycle used for signals angle calibration */
    float32_t       v;                  /* Voltage value on reference power supply */
    float32_t       i;                  /* Current value on reference power supply */
    float32_t       imax;               /* Max measuring current for calibrating meter */
    float32_t       fac;                /* Supply line frequency */

    /* Line selection */
    EM_LINE         line;               /* Line selection */

} r_calib_args_t;

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/
uint8_t R_CALIB_Calibrate(r_calib_args_t * p_args, r_calib_work_t * p_works, r_calib_output_t * p_output);
void R_CALIB_SetDefaultCalibArgs(r_calib_args_t * p_args);
uint8_t R_CALIB_IsInCalibMode(void);
/*
 * Callback function, must be registered to ADC Conversion End Callback of Driver
 */
void R_CALIB_Sampling(EM_SAMPLES * p_samples);

/*
 * Callback function, must be registered to RTC Constant ISR Callback of Driver
 */
void R_CALIB_RTCConstantInterruptCallback(void);

#endif /* _R_CALIB_H */

