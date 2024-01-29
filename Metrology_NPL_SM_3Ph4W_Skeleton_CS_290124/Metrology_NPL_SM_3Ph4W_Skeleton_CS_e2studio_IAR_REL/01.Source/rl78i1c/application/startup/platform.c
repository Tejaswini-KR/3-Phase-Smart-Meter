/******************************************************************************
* DISCLAIMER

* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized.

* This software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.

* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES 
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, 
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY 
* DISCLAIMED.

* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES 
* FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS 
* AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

* Renesas reserves the right, without notice, to make changes to this 
* software and to discontinue the availability of this software.  
* By using this software, you agree to the additional terms and 
* conditions found by accessing the following link:
* http://www.renesas.com/disclaimer
******************************************************************************/
/* Copyright (C) 2011 Renesas Electronics Corporation. All rights reserved.  */
/****************************************************************************** 
* File Name    : platform.c
* Version      : 1.00
* Device(s)    : None
* Tool-Chain   : CubeSuite Version 1.5d
* H/W Platform : RL78G13 Energy Meter Platform
* Description  : Platform Property Source File
******************************************************************************
* History : DD.MM.YYYY Version Description
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "platform.h"   /* Platform Property header file */

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/* Default platform property */
const EM_PLATFORM_PROPERTY FAR_PTR g_EM_DefaultProperty = 
{
    EM_PLATFORM_PROPERTY_TARGET_AC_SOURCE_FREQUENCY         ,       /* Target AC Source Frequency */
    0                                                       ,       /* Reserved */
};

/* SW Phase Correction Angle List */
const float32_t FAR_PTR g_EM_DefaultCalibPhaseAngleList_Phase_R[] =
{
    EM_CALIB_DEFAULT_GAIN_PHASE_LEVEL0_PHASE_SHIFT_PHASE_R  ,       /* Phase Gain Level 0 Phase Shift Angle (in degree) */
    EM_CALIB_DEFAULT_GAIN_PHASE_LEVEL1_PHASE_SHIFT_PHASE_R  ,     /* Phase Gain Level 1 Phase Shift Angle (in degree) */
};
const float32_t FAR_PTR g_EM_DefaultCalibPhaseAngleList_Phase_Y[] =
{
    EM_CALIB_DEFAULT_GAIN_PHASE_LEVEL0_PHASE_SHIFT_PHASE_Y,     /* Phase Gain Level 0 Phase Shift Angle (in degree) */
    EM_CALIB_DEFAULT_GAIN_PHASE_LEVEL1_PHASE_SHIFT_PHASE_Y,     /* Phase Gain Level 1 Phase Shift Angle (in degree) */
};
const float32_t FAR_PTR g_EM_DefaultCalibPhaseAngleList_Phase_B[] =
{
    EM_CALIB_DEFAULT_GAIN_PHASE_LEVEL0_PHASE_SHIFT_PHASE_B,     /* Phase Gain Level 0 Phase Shift Angle (in degree) */
    EM_CALIB_DEFAULT_GAIN_PHASE_LEVEL1_PHASE_SHIFT_PHASE_B,     /* Phase Gain Level 1 Phase Shift Angle (in degree) */
};

/* SW Gain Value List (Phase Channel) */
const float32_t FAR_PTR g_EM_DefaultCalibPhaseGainValueList_Phase_R[] =
{
    EM_CALIB_DEFAULT_GAIN_PHASE_LEVEL0_VALUE_PHASE_R,       /* Phase Gain Level 0 Value (lowest, value is 1.0, fixed)   */
    EM_CALIB_DEFAULT_GAIN_PHASE_LEVEL1_VALUE_PHASE_R,       /* Phase Gain Level 1 Value     |                           */
};
const float32_t FAR_PTR g_EM_DefaultCalibPhaseGainValueList_Phase_Y[] =
{
    EM_CALIB_DEFAULT_GAIN_PHASE_LEVEL0_VALUE_PHASE_Y,       /* Phase Gain Level 0 Value (lowest, value is 1.0, fixed)   */
    EM_CALIB_DEFAULT_GAIN_PHASE_LEVEL1_VALUE_PHASE_Y,       /* Phase Gain Level 1 Value     |                           */
};
const float32_t FAR_PTR g_EM_DefaultCalibPhaseGainValueList_Phase_B[] =
{
    EM_CALIB_DEFAULT_GAIN_PHASE_LEVEL0_VALUE_PHASE_B,       /* Phase Gain Level 0 Value (lowest, value is 1.0, fixed)   */
    EM_CALIB_DEFAULT_GAIN_PHASE_LEVEL1_VALUE_PHASE_B,       /* Phase Gain Level 1 Value     |                           */
};

/* Platform default calibration */
const EM_CALIBRATION FAR_PTR g_EM_DefaultCalibration =
{
    EM_CALIB_DEFAULT_SAMPLING_FREQUENCY         			,                   /* Actual sampling frequency of the meter     */
    /* Coeff */
    {
        {
            EM_CALIB_DEFAULT_COEFF_VRMS_PHASE_R                         ,                   /* VRMS Co-efficient  At Gain 1.0f            */
            EM_CALIB_DEFAULT_COEFF_IRMS_PHASE_R                         ,                   /* I1RMS Co-efficient At Gain 1.0f            */
            EM_CALIB_DEFAULT_COEFF_ACTIVE_POWER_PHASE_R                 ,                   /* Active Power Co-efficient At Gain 1.0f     */
            EM_CALIB_DEFAULT_COEFF_REACTIVE_POWER_PHASE_R               ,                   /* Reactive Power Co-efficient At Gain 1.0f   */
            EM_CALIB_DEFAULT_COEFF_APPARENT_POWER_PHASE_R               ,                   /* Apparent Power Co-efficient At Gain 1.0f   */
        },
        {
            EM_CALIB_DEFAULT_COEFF_VRMS_PHASE_Y                         ,                   /* VRMS Co-efficient  At Gain 1.0f            */
            EM_CALIB_DEFAULT_COEFF_IRMS_PHASE_Y                         ,                   /* I1RMS Co-efficient At Gain 1.0f            */
            EM_CALIB_DEFAULT_COEFF_ACTIVE_POWER_PHASE_Y                 ,                   /* Active Power Co-efficient At Gain 1.0f     */
            EM_CALIB_DEFAULT_COEFF_REACTIVE_POWER_PHASE_Y               ,                   /* Reactive Power Co-efficient At Gain 1.0f   */
            EM_CALIB_DEFAULT_COEFF_APPARENT_POWER_PHASE_Y               ,                   /* Apparent Power Co-efficient At Gain 1.0f   */
        },
        {
            EM_CALIB_DEFAULT_COEFF_VRMS_PHASE_B                         ,                   /* VRMS Co-efficient  At Gain 1.0f            */
            EM_CALIB_DEFAULT_COEFF_IRMS_PHASE_B                         ,                   /* I1RMS Co-efficient At Gain 1.0f            */
            EM_CALIB_DEFAULT_COEFF_ACTIVE_POWER_PHASE_B                 ,                   /* Active Power Co-efficient At Gain 1.0f     */
            EM_CALIB_DEFAULT_COEFF_REACTIVE_POWER_PHASE_B               ,                   /* Reactive Power Co-efficient At Gain 1.0f   */
            EM_CALIB_DEFAULT_COEFF_APPARENT_POWER_PHASE_B               ,                   /* Apparent Power Co-efficient At Gain 1.0f   */
        },
        {
            EM_CALIB_DEFAULT_COEFF_IRMS_NEUTRAL                         ,
        },
    },
    
    /* Angle */
    {
        {
            (float32_t FAR_PTR *)g_EM_DefaultCalibPhaseAngleList_Phase_R        ,                       /* Point to phase angle list */
        },
        {
            (float32_t FAR_PTR *)g_EM_DefaultCalibPhaseAngleList_Phase_Y        ,                       /* Point to phase angle list */
        },
        {
            (float32_t FAR_PTR *)g_EM_DefaultCalibPhaseAngleList_Phase_B        ,                       /* Point to phase angle list */
        },
    },
    
    /* SW Gain */
    {
        {
            (float32_t FAR_PTR *)g_EM_DefaultCalibPhaseGainValueList_Phase_R    ,                       /* Point to gain value list (phase line) */
        },
        
        {
            (float32_t FAR_PTR *)g_EM_DefaultCalibPhaseGainValueList_Phase_Y    ,                       /* Point to gain value list (phase line) */
        },
        
        {
            (float32_t FAR_PTR *)g_EM_DefaultCalibPhaseGainValueList_Phase_B    ,                       /* Point to gain value list (phase line) */
        },
    },

};


/******************************************************************************
Private global variables and functions
******************************************************************************/
