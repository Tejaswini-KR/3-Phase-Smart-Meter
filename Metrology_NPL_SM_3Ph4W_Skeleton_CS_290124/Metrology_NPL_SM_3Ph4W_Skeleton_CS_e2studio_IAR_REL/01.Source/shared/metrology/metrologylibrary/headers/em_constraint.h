/******************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : em_constraint.h
* Version      : 1.00
* Description  : EM Core Constraint Middleware Header file
******************************************************************************
* History : DD.MM.YYYY Version Description
******************************************************************************/

#ifndef _EM_CONSTRAINT_H
#define _EM_CONSTRAINT_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/

/******************************************************************************
Macro definitions
******************************************************************************/
/* Platform property constant */
#define EM_GAIN_PHASE_NUM_LEVEL_MIN                 (1U)                    /* Gain phase number level min */
#define EM_GAIN_PHASE_NUM_LEVEL_MAX                 (2U)                    /* Gain phase number level max */
#define EM_SAMPLING_FREQUENCY_MIN                   (1200U)                 /* Sampling Frequency Min (Hz) */
#define EM_SAMPLING_FREQUENCY_MAX                   (4000U)                 /* Sampling Frequency Max (Hz) */
#define EM_TARGET_AC_SOURCE_FREQ_SELECTION0         (50U)                   /* Target AC Source Frequency Selection 0 (Hz) */
#define EM_TARGET_AC_SOURCE_FREQ_SELECTION1         (60U)                   /* Target AC Source Frequency Selection 1 (Hz) */
#define EM_MAX_ROUNDING_DIGIT                       4

/* Configuration Constant */
#define EM_VOL_CHANNEL_NUM                          (3U)       /* Voltage channel number */
#define EM_CURRENT_CHANNEL_NUM                      (4U)        /* Current channel number */
#define EM_CALC_NUM_OF_LINE                         (EM_CURRENT_CHANNEL_NUM + 1)    /* Included Total Calculation*/

/* Configuration Constant */
#define EM_VOL_LOW_MIN                              (10.0f)                   /* Voltage low min */
#define EM_FREQ_LOW_MIN                             (40.0f)                   /* Frequency low min */
#define EM_FREQ_HIGH_MAX                            (70.0f)                   /* Frequency low max */

/* Calibration information */
#define EM_PULSE_ON_TIME_MIN                        (10.0f)          /* Pulse On Time Min */

/* Co-efficient Constant */
#define EM_VRMS_COEFF_MIN                           (0.1f)                  /* VRMS Co-efficient min */
#define EM_IRMS_COEFF_MIN                           (0.1f)                  /* IRMS Co-efficient min */
#define EM_ACT_POWER_COEFF_MIN                      (0.1f)                  /* Active Power Co-efficient min */
#define EM_REA_POWER_COEFF_MIN                      (0.1f)                  /* Reactive Power Co-efficient min */
#define EM_APP_POWER_COEFF_MIN                      (0.1f)                  /* Apparent Power Co-efficient min */

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/

#endif /* _EM_CONSTRAINT_H */
