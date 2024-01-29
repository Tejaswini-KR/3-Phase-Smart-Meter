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
* File Name    : platform.h
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : Platform Property Source File
***********************************************************************************************************************/

#ifndef _EM_PLATFORM_PROPERTY_H
#define _EM_PLATFORM_PROPERTY_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "compiler.h"
#include "em_type.h"

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/* Control operation of application here */
#ifdef __DEBUG
    //#define POWER_MANAGEMENT_ENABLE
#else
    #define POWER_MANAGEMENT_ENABLE
#endif

#ifdef __DEBUG
//#define METER_ENABLE_MEASURE_CPU_LOAD
#endif

#define METER_ENABLE_PROPRIETARY_METER_COMMAND                  (TRUE)

/***********************************************************************************************************************
*   Platform Default Property
***********************************************************************************************************************/
#define EM_PLATFORM_PROPERTY_TARGET_AC_SOURCE_FREQUENCY         50                              /* Target AC Source Frequency */


/***********************************************************************************************************************
*   Platform Default Calibration Informations
***********************************************************************************************************************/
/* Meter Constant */
#define EM_CALIB_DEFAULT_SAMPLING_FREQUENCY                     3900.000000                         /* Actual sampling frequency of the meter    */

/* Co-efficient */
#define EM_CALIB_DEFAULT_COEFF_VRMS_PHASE_R                     (66.063419 )                        /* VRMS Co-efficient  At Gain 1.0f           */
#define EM_CALIB_DEFAULT_COEFF_IRMS_PHASE_R                     (41654.294550 )                     /* IRMS Co-efficient At Gain 1.0f           */
#define EM_CALIB_DEFAULT_COEFF_ACTIVE_POWER_PHASE_R             (EM_CALIB_DEFAULT_COEFF_VRMS_PHASE_R*EM_CALIB_DEFAULT_COEFF_IRMS_PHASE_R)                   /* Active Power Co-efficient At Gain 1.0f    */
#define EM_CALIB_DEFAULT_COEFF_REACTIVE_POWER_PHASE_R           (EM_CALIB_DEFAULT_COEFF_VRMS_PHASE_R*EM_CALIB_DEFAULT_COEFF_IRMS_PHASE_R)                   /* Reactive Power Co-efficient At Gain 1.0f  */
#define EM_CALIB_DEFAULT_COEFF_APPARENT_POWER_PHASE_R           (EM_CALIB_DEFAULT_COEFF_VRMS_PHASE_R*EM_CALIB_DEFAULT_COEFF_IRMS_PHASE_R)                   /* Apparent Power Co-efficient At Gain 1.0f  */

#define EM_CALIB_DEFAULT_COEFF_VRMS_PHASE_Y                     (63.746731 )                        /* VRMS Co-efficient  At Gain 1.0f           */
#define EM_CALIB_DEFAULT_COEFF_IRMS_PHASE_Y                     (41461.07927 )                     /* IRMS Co-efficient At Gain 1.0f           */
#define EM_CALIB_DEFAULT_COEFF_ACTIVE_POWER_PHASE_Y             (EM_CALIB_DEFAULT_COEFF_VRMS_PHASE_Y*EM_CALIB_DEFAULT_COEFF_IRMS_PHASE_Y)                   /* Active Power Co-efficient At Gain 1.0f    */
#define EM_CALIB_DEFAULT_COEFF_REACTIVE_POWER_PHASE_Y           (EM_CALIB_DEFAULT_COEFF_VRMS_PHASE_Y*EM_CALIB_DEFAULT_COEFF_IRMS_PHASE_Y)                   /* Reactive Power Co-efficient At Gain 1.0f  */
#define EM_CALIB_DEFAULT_COEFF_APPARENT_POWER_PHASE_Y           (EM_CALIB_DEFAULT_COEFF_VRMS_PHASE_Y*EM_CALIB_DEFAULT_COEFF_IRMS_PHASE_Y)                   /* Apparent Power Co-efficient At Gain 1.0f  */

#define EM_CALIB_DEFAULT_COEFF_VRMS_PHASE_B                     (43.870165 )                        /* VRMS Co-efficient  At Gain 1.0f           */
#define EM_CALIB_DEFAULT_COEFF_IRMS_PHASE_B                     (41624.333308 )                     /* IRMS Co-efficient At Gain 1.0f           */
#define EM_CALIB_DEFAULT_COEFF_ACTIVE_POWER_PHASE_B             (EM_CALIB_DEFAULT_COEFF_VRMS_PHASE_B*EM_CALIB_DEFAULT_COEFF_IRMS_PHASE_B)                   /* Active Power Co-efficient At Gain 1.0f    */
#define EM_CALIB_DEFAULT_COEFF_REACTIVE_POWER_PHASE_B           (EM_CALIB_DEFAULT_COEFF_VRMS_PHASE_B*EM_CALIB_DEFAULT_COEFF_IRMS_PHASE_B)                   /* Reactive Power Co-efficient At Gain 1.0f  */
#define EM_CALIB_DEFAULT_COEFF_APPARENT_POWER_PHASE_B           (EM_CALIB_DEFAULT_COEFF_VRMS_PHASE_B*EM_CALIB_DEFAULT_COEFF_IRMS_PHASE_B)                   /* Apparent Power Co-efficient At Gain 1.0f  */

#define EM_CALIB_DEFAULT_COEFF_IRMS_NEUTRAL                     (41624.333308 )                     /* IRMS Co-efficient At Gain 1.0f           */

/* Offset */
#define EM_CALIB_DEFAULT_OFFSET_V                               (16380)                             /* Voltage offset (half of VREF, ADC 12bit flush left >> 1 */

/* DSAD Gain */
#define EM_CALIB_DEFAULT_GAIN_PHASE_R                           (1)
#define EM_CALIB_DEFAULT_GAIN_PHASE_Y                           (1)
#define EM_CALIB_DEFAULT_GAIN_PHASE_B                           (1)
#define EM_CALIB_DEFAULT_GAIN_NEUTRAL                           (1)

/* HOCO Trimming */
#define EM_CALIB_DEFAULT_HOCO_TRIMMING                          (30)                    /* Default value for HIOTRM register */

/* SW Phase Correction */
/* Phase Gain Phase Shift Angle */
#define EM_CALIB_DEFAULT_GAIN_PHASE_LEVEL0_PHASE_SHIFT_PHASE_R  (-2.115543f)            /* Phase Gain Level 0 Phase Shift Angle (in degree) */
#define EM_CALIB_DEFAULT_GAIN_PHASE_LEVEL1_PHASE_SHIFT_PHASE_R  (-2.104473f)            /* Phase Gain Level 2 Phase Shift Angle (in degree) */

/* Phase Gain Phase Shift Angle */
#define EM_CALIB_DEFAULT_GAIN_PHASE_LEVEL0_PHASE_SHIFT_PHASE_Y  (-2.048136f)            /* Phase Gain Level 0 Phase Shift Angle (in degree) */
#define EM_CALIB_DEFAULT_GAIN_PHASE_LEVEL1_PHASE_SHIFT_PHASE_Y  (-2.037581f)            /* Phase Gain Level 2 Phase Shift Angle (in degree) */

/* Phase Gain Phase Shift Angle */
#define EM_CALIB_DEFAULT_GAIN_PHASE_LEVEL0_PHASE_SHIFT_PHASE_B  (-1.919932f)            /* Phase Gain Level 0 Phase Shift Angle (in degree) */
#define EM_CALIB_DEFAULT_GAIN_PHASE_LEVEL1_PHASE_SHIFT_PHASE_B  (-1.915074f)            /* Phase Gain Level 2 Phase Shift Angle (in degree) */

/* Gain Value List */
/* Phase Gain Value List */
#define EM_CALIB_DEFAULT_GAIN_PHASE_LEVEL0_VALUE_PHASE_R        (1.0f)                  /* Phase Gain Level 0 Value (lowest, value is 1.0, fixed)   */
#define EM_CALIB_DEFAULT_GAIN_PHASE_LEVEL1_VALUE_PHASE_R        (4.005f)                /* Phase Gain Level 2 Value     |                           */

/* Phase Gain Value List */
#define EM_CALIB_DEFAULT_GAIN_PHASE_LEVEL0_VALUE_PHASE_Y        (1.0f)                  /* Phase Gain Level 0 Value (lowest, value is 1.0, fixed)   */
#define EM_CALIB_DEFAULT_GAIN_PHASE_LEVEL1_VALUE_PHASE_Y        (3.997f)                /* Phase Gain Level 2 Value     |                           */

/* Phase Gain Value List */
#define EM_CALIB_DEFAULT_GAIN_PHASE_LEVEL0_VALUE_PHASE_B        (1.0f)                  /* Phase Gain Level 0 Value (lowest, value is 1.0, fixed)   */
#define EM_CALIB_DEFAULT_GAIN_PHASE_LEVEL1_VALUE_PHASE_B        (4.003f)                /* Phase Gain Level 2 Value     |                           */


/******************************************************************************
*   Platform Default Nameplate
*******************************************************************************/
#define METER_DEFAULT_IB                                        (5)                         /* Current rating Ib (A) */
#define METER_DEFAULT_IMAX                                      (60)                        /* Current rating Imax (A) */
#define METER_DEFAULT_YEAR_OF_MANUFACTURE                       (21)                        /* Year of manufacture, only end 2 digit */
#define METER_DEFAULT_FLAG_ID                                   "REI"                       /* Meter flag ID, 3 characters */
#define METER_DEFAULT_SERIAL_NUMBER					            "0000000000000045"			/* Last   5 ASCII char */
#define METER_DEFAULT_MANUFACTURE                               "RENESAS ELECTRONICS INDIA PRIVATE LIMITED"
#define METER_DEFAULT_CATEGORY                                  "D2"                        /* Meter category, D1 is Single Phase Smart Meter */
#define METER_DEFAULT_FIRMWARE_VERSION                          "V2.0 Ind"                  /* Firmware version */
#define METER_DEFAULT_TYPE                                      (7)                         /* 1P a.c. static direct connected Wh smart meter */

/******************************************************************************
*   Platform Default Bootloader Firmware Update
*******************************************************************************/

//#define FAST_FOTA      /* Smart Meter with FOTA Bootloader */
#define LEGACY_FOTA    /* Smart Meter with LEGACY Bootloader */

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/
extern FAR_PTR const EM_PLATFORM_PROPERTY   g_EM_DefaultProperty;       /* Default Platform Property */
extern FAR_PTR const EM_CALIBRATION         g_EM_DefaultCalibration;    /* Default Platform Calibration */

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/

#endif /* _EM_PLATFORM_PROPERTY_H */

