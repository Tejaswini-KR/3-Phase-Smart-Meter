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
* File Name    : wrp_em_sw_config.h
* Version      : 1.00
* Device(s)    : RL78/I1C - 512K
* Tool-Chain   : CCRL
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : Wrapper Configuration Header file
***********************************************************************************************************************/

#ifndef _WRAPPER_EM_SW_CONFIG_H
#define _WRAPPER_EM_SW_CONFIG_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"

    /**************************************************************************
    *   ADC Driver Header
    ***************************************************************************/
    #include "r_cg_dsadc.h"
    #include "r_cg_12adc.h"
    #include "r_cg_elc.h"
    #include "r_cg_dtc.h"
    
    /**************************************************************************
    *   PULSE Driver Header
    ***************************************************************************/
    #include "r_cg_port.h"
    
    /**************************************************************************
    *   WDT Driver Header
    ***************************************************************************/
    #include "r_cg_wdt.h"
	
    /**************************************************************************
    *   TIMER Driver Header
    ***************************************************************************/
    #include "r_cg_tau.h"
    
    /**************************************************************************
    *   EM Constraint Header
    ***************************************************************************/
    #include "em_constraint.h"

    /**************************************************************************
    *   Platform Property
    ***************************************************************************/
   #include "platform.h"
/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

    /******************************************************************************
    *   Noisy Bit Masking
    *******************************************************************************
    *   The Noisy bit masking is optional, this depend on the signal processing
    *     
    *   In default, the Noisy Bit Masking is ENABLE
    *   To DISABLE, please undefine the macro EM_ENABLE_NOISY_BIT_MASKING
    *   To ENABLE, please define the macro.
    *
    *
    */
    //#define EM_ENABLE_NOISY_BIT_MASKING

    #define EM_MASK_OFF_NOISY_BITS_POSITIVE                 (0xF0)
    #define EM_MASK_OFF_NOISY_BITS_NEGATIVE                 (0x0F)
    
    #if defined(FEATURES_WQFR)   || \
        defined(FEATURES_BQFR)   || \
        defined(FEATURES_ALL)    || \
        (0)
        
    #define METER_WRAPPER_ADC_COPY_FUNDAMENTAL_SAMPLE
    #define METER_WRAPPER_ADC_CURRENT_CHANNEL_LPF_REDUCED_FS    (0)
    
    #endif /* defined(FEATURES_WQFR) ||
              defined(FEATURES_BQFR) || 
              defined(FEATURES_ALL) */
              
    #if defined(FEATURES_BQUR)   || \
        defined(FEATURES_WQUR)   || \
        defined(FEATURES_WQFR)   || \
        defined(FEATURES_BQFR)   || \
        defined(FEATURES_ALL)    || \
        (0)
    #define METER_WRAPPER_ADC_COPY_REACTIVE_SAMPLE
    
    #endif /* defined(FEATURES_BQUR) ||
              defined(FEATURES_WQUR) || 
              defined(FEATURES_WQFR) || 
              defined(FEATURES_BQFR) ||
              defined(FEATURES_ALL) */  

    /* This option below will do integration on input sample in case using the rogowski coil  */
	#define METER_ENABLE_INTEGRATOR_ON_SAMPLE                      (0)                              /* Enable/Disable ADC Integrator  */
    
/***********************************************************************************************************************
*   EM Core Software Block (SW Block)
************************************************************************************************************************/

    /**************************************************************************
    *   SW Wrapper Property Configuration & Settings
    ***************************************************************************/
    #define EM_SW_PROPERTY_ADC_GAIN_NUMBER_LEVEL            		1                   /* (SW Support Only) - Gain switch number of level: 1 or 2  */
    
    #define EM_SW_PROPERTY_ADC_GAIN_UPPER_THRESHOLD_PHASE_R         3000000             /* (SW Support Only) - Gain switch adc upper threshold      */
    #define EM_SW_PROPERTY_ADC_GAIN_LOWER_THRESHOLD_PHASE_R         300000              /* (SW Support Only) - Gain switch adc lower threshold      */
    
    #define EM_SW_PROPERTY_ADC_GAIN_UPPER_THRESHOLD_PHASE_Y         3000000             /* (SW Support Only) - Gain switch adc upper threshold      */
    #define EM_SW_PROPERTY_ADC_GAIN_LOWER_THRESHOLD_PHASE_Y         300000              /* (SW Support Only) - Gain switch adc lower threshold      */

    #define EM_SW_PROPERTY_ADC_GAIN_UPPER_THRESHOLD_PHASE_B         3000000             /* (SW Support Only) - Gain switch adc upper threshold      */
    #define EM_SW_PROPERTY_ADC_GAIN_LOWER_THRESHOLD_PHASE_B         300000              /* (SW Support Only) - Gain switch adc lower threshold      */

    #if ((EM_SW_PROPERTY_ADC_GAIN_NUMBER_LEVEL != 1) && (EM_SW_PROPERTY_ADC_GAIN_NUMBER_LEVEL != 2))
	#error " Please define gain switch number of level 1 or 2 only "
    #endif /* (EM_SW_PROPERTY_ADC_GAIN_NUMBER_LEVEL != 1) && (EM_SW_PROPERTY_ADC_GAIN_NUMBER_LEVEL != 2) */

    #if (EM_SW_PROPERTY_ADC_GAIN_NUMBER_LEVEL == 1)
    #define EM_SW_PROPERTY_ADC_GAIN_NUMBER_LEVEL_PHASE_R            1
    #define EM_SW_PROPERTY_ADC_GAIN_NUMBER_LEVEL_PHASE_Y            1
    #define EM_SW_PROPERTY_ADC_GAIN_NUMBER_LEVEL_PHASE_B            1
    #else
    #define EM_SW_PROPERTY_ADC_GAIN_NUMBER_LEVEL_PHASE_R            2
    #define EM_SW_PROPERTY_ADC_GAIN_NUMBER_LEVEL_PHASE_Y            2
    #define EM_SW_PROPERTY_ADC_GAIN_NUMBER_LEVEL_PHASE_B            2
    #endif /* EM_SW_PROPERTY_ADC_GAIN_NUMBER_LEVEL == 1 */
    
    #define EM_SW_PROPERTY_OPERATION_IRMS_NOLOAD_THRESHOLD      (0.010f)
    #define EM_SW_PROPERTY_OPERATION_POWER_NOLOAD_THRESHOLD     (EM_SW_PROPERTY_OPERATION_IRMS_NOLOAD_THRESHOLD * 180.0f)
    #define EM_SW_PROPERTY_OPERATION_NO_VOLTAGE_THRESHOLD       (10.0f)    /* V */
    #define EM_SW_PROPERTY_OPERATION_FREQUENCY_LOW_THRESHOLD    (40.0f)    /* Hz */
    #define EM_SW_PROPERTY_OPERATION_FREQUENCY_HIGH_THRESHOLD   (70.0f)    /* Hz */
    #define EM_SW_PROPERTY_OPERATION_METER_CONSTANT             (3200)     /* imp/kWh */
    #define EM_SW_PROPERTY_OPERATION_PULSE_ON_TIME              (10.0f)     /* ms */
    #define EM_SW_PROPERTY_OPERATION_ENERY_PULSE_RATIO          (1)        /* Energy resolution equal: (ratio * meter constant) Wh */
    #define EM_SW_PROPERTY_OPERATION_PULSE_EXPORT_DIRECTION     (1)        /* Enable (1) / Disable (0) export direction pulse output */
    #define EM_SW_PROPERTY_OPERATION_PULSE_REACTIVE_ENABLE 	    (1)        /* Enable (1) / Disable (0) reactive pulse output */
    #define EM_SW_PROPERTY_OPERATION_PULSE_APPARENT_ENABLE 	    (0)        /* Enable (1) / Disable (0) apparent pulse output */
    /* Check macro definition */
    #if (EM_SW_PROPERTY_OPERATION_PULSE_REACTIVE_ENABLE) && (EM_SW_PROPERTY_OPERATION_PULSE_APPARENT_ENABLE)
        #error "Only enable Reactive pulse or Apparent pulse "
    #endif


    /* Set rounding for parameter */
    #define EM_SW_PROPERTY_ROUND_DIGIT_POWER                    (4)        /* Number of fraction digit to round up power value */
    #define EM_SW_PROPERTY_ROUND_DIGIT_RMS                      (4)        /* Number of fraction digit to round up rms value */
    #define EM_SW_PROPERTY_ROUND_DIGIT_FREQ                     (1)        /* Number of fraction digit to round up line frequency value */
    #define EM_SW_PROPERTY_ROUND_DIGIT_PF                       (3)        /* Number of fraction digit to round up power factor value */

    #if ((EM_SW_PROPERTY_ROUND_DIGIT_POWER > EM_MAX_ROUNDING_DIGIT) ||  \
        (EM_SW_PROPERTY_ROUND_DIGIT_RMS > EM_MAX_ROUNDING_DIGIT)    ||  \
        (EM_SW_PROPERTY_ROUND_DIGIT_FREQ > EM_MAX_ROUNDING_DIGIT)   ||  \
        (EM_SW_PROPERTY_ROUND_DIGIT_PF > EM_MAX_ROUNDING_DIGIT))        
    #error "Please check the metrology rounding digit settings"
    #endif

    /* Sag and Swell */
    #define EM_SW_PROPERTY_SAG_RMS_RISE_THRESHOLD               (145)       /* V */
    #define EM_SW_PROPERTY_SAG_RMS_FALL_THRESHOLD               (127)       /* V */
    #define EM_SW_PROPERTY_SWELL_RMS_RISE_THRESHOLD             (260)       /* V */
    #define EM_SW_PROPERTY_SWELL_RMS_FALL_THRESHOLD             (242)       /* V */
    #define EM_SW_PROPERTY_SAG_DETECTION_HALF_CYCLE             (3)         /* Number of half cycle for sag detection (rise and fall) */
    #define EM_SW_PROPERTY_SWELL_DETECTION_HALF_CYCLE           (3)         /* Number of half cycle for swell detection (rise and fall) */
          
    /* Define the DSAD High pass cutoff frequency */
    #define EM_SW_PROPERTY_ADC_HPF_CUTOFF_FREQUENCY                 (HPF_2429_HZ)       /* (SW Support Only) DSAD HPF cutoff frequency */ 

    /**************************************************************************
    *   WDT Wrapper Configuration for Settings & I/F mapping
    ***************************************************************************/
    /* I/Fs mapping
     *      Macro Name / I/Fs                                   Setting/Description */
    #define EM_WDT_DriverInit()                                 R_WDT_Create()                  /* WDT Init */
    #define EM_WDT_DriverStart()                                {;}                             /* WDT Start */
    #define EM_WDT_DriverStop()                                 {;}                             /* WDT Stop */
    #define EM_WDT_DriverRestart()                              R_WDT_Restart()                 /* WDT Restart */

    /**************************************************************************
    *   EM TIMER Wrapper Configuration for Settings & I/F mapping
    ***************************************************************************/
    /* I/Fs mapping
     *      Macro Name / I/Fs                                   Setting/Description */
    #define EM_TIMER_DriverInit()                               {;}                             /* Init */
    #define EM_TIMER_DriverStart()                              R_TAU0_Channel2_Start()         /* Start */
    #define EM_TIMER_DriverStop()                               R_TAU0_Channel2_Stop()          /* Stop */

    /**************************************************************************
    *   PULSE Wrapper Configuration for Settings & I/F mapping
    ***************************************************************************/
    /* I/Fs Mapping 
     *      Macro Name / I/Fs                                   Setting/Description */
    #define EM_PULSE_ACTIVE_ON_STATEMENT                              {SET_BIT(P0,2,0);}              /* Pulse 0 LED On */
    #define EM_PULSE_ACTIVE_OFF_STATEMENT                             {SET_BIT(P0,2,1);}              /* Pulse 0 LED Off */
   
   #if (EM_SW_PROPERTY_OPERATION_PULSE_REACTIVE_ENABLE) /* USING REACTIVE PULSE*/
        #define EM_PULSE_REACTIVE_ON_STATEMENT                        {SET_BIT(P4,3,0);}        /* Pulse 1 LED On */
        #define EM_PULSE_REACTIVE_OFF_STATEMENT                       {SET_BIT(P4,3,1);}        /* Pulse 1 LED Off */
        #define EM_PULSE_APPARENT_ON_STATEMENT                        {;}                       /* Pulse 2 LED On */
        #define EM_PULSE_APPARENT_OFF_STATEMENT                       {;}                       /* Pulse 2 LED Off */  
    #else /* USING APPARENT PULSE*/
        #define EM_PULSE_REACTIVE_ON_STATEMENT                        {;}        /* Pulse 1 LED On */
        #define EM_PULSE_REACTIVE_OFF_STATEMENT                       {;}        /* Pulse 1 LED Off */
        #define EM_PULSE_APPARENT_ON_STATEMENT                        {SET_BIT(P4,3,0);}        /* Pulse 2 LED On */
        #define EM_PULSE_APPARENT_OFF_STATEMENT                       {SET_BIT(P4,3,1);}        /* Pulse 2 LED Off */
    #endif /* EM_SW_PROPERTY_OPERATION_PULSE_REACTIVE_ENABLE */

    #define EM_PULSE_DriverInit()                               {;}                             /* Pulse Init */        

    /**************************************************************************
    *   ADC Wrapper Configuration for Settings & I/F mapping
    ***************************************************************************/    
    /* Settings */
    /* Channel Name Specification */
    /* SAR-ADC Channels */

    #define EM_ADC_VOL_DRIVER_START_SCAN_CHANNEL                ADCHANNEL0          /* AD 1st channel in scan chain */

    #define EM_ADC_VOL_DRIVER_CHANNEL_PHASE_R                   ADCHANNEL0          /* AD Driver Voltage Channel ID         */
    #define EM_ADC_VOL_DRIVER_CHANNEL_PHASE_Y                   ADCHANNEL1          /* AD Driver Voltage Channel ID         */
    #define EM_ADC_VOL_DRIVER_CHANNEL_PHASE_B                   ADCHANNEL2          /* AD Driver Voltage Channel ID         */

    #define EM_ADC_CURRENT_DRIVER_CHANNEL_OPTIMIZATION_PHASE_R  0
    #define EM_ADC_CURRENT_DRIVER_CHANNEL_OPTIMIZATION_PHASE_Y  1
    #define EM_ADC_CURRENT_DRIVER_CHANNEL_OPTIMIZATION_PHASE_B  2
    #define EM_ADC_CURRENT_DRIVER_CHANNEL_OPTIMIZATION_NEUTRAL  3

    #define EM_ADC_CURRENT_DRIVER_CHANNEL_PHASE_R               (dsad_channel_t)(DSADCHANNEL0+EM_ADC_CURRENT_DRIVER_CHANNEL_OPTIMIZATION_PHASE_R)        /* AD Driver Voltage Channel ID         */
    #define EM_ADC_CURRENT_DRIVER_CHANNEL_PHASE_Y               (dsad_channel_t)(DSADCHANNEL0+EM_ADC_CURRENT_DRIVER_CHANNEL_OPTIMIZATION_PHASE_Y)        /* AD Driver Voltage Channel ID         */
    #define EM_ADC_CURRENT_DRIVER_CHANNEL_PHASE_B               (dsad_channel_t)(DSADCHANNEL0+EM_ADC_CURRENT_DRIVER_CHANNEL_OPTIMIZATION_PHASE_B)        /* AD Driver Voltage Channel ID         */
    #define EM_ADC_CURRENT_DRIVER_CHANNEL_NEUTRAL               (dsad_channel_t)(DSADCHANNEL0+EM_ADC_CURRENT_DRIVER_CHANNEL_OPTIMIZATION_NEUTRAL)        /* AD Driver Voltage Channel ID         */

    #define EM_ADC_DRIVER_IDEAL_SAMPLING_FREQUENCY              (3906.25)
    
    #define EM_ADC_GAIN_LEVEL0_PHASE_R                          (GAIN_X1)
    #define EM_ADC_GAIN_LEVEL1_PHASE_R                          (GAIN_X4)
    
    #define EM_ADC_GAIN_LEVEL0_PHASE_Y                          (GAIN_X1)
    #define EM_ADC_GAIN_LEVEL1_PHASE_Y                          (GAIN_X4)
    
    #define EM_ADC_GAIN_LEVEL0_PHASE_B                          (GAIN_X1)
    #define EM_ADC_GAIN_LEVEL1_PHASE_B                          (GAIN_X4)        
    /* 
     * Define the settable value for quarter shift timer to protect sampling
     * This setting depends on ADC conversion time
    */
    #define EM_ADC_DRIVER_TAU_256US_SETTING                     (6144)
    #define EM_ADC_DRIVER_TAU_MAX_THRESHOLD                     (5910)
    #define EM_ADC_DRIVER_TAU_MIN_THRESHOLD                     (234)
    
    #if (EM_PLATFORM_PROPERTY_TARGET_AC_SOURCE_FREQUENCY == 50)
    #define EM_ADC_DRIVER_PHASE_SHIFT_STEP                      (0.012f)                        /* AD Driver Phase step */
    #elif (EM_PLATFORM_PROPERTY_TARGET_AC_SOURCE_FREQUENCY == 60)
    #define EM_ADC_DRIVER_PHASE_SHIFT_STEP                      (0.0144f)                       /* AD Driver Phase step */
    #else
    #error "Unsupported line frequency, 50Hz or 60Hz only"
    #endif /* EM_PLATFORM_PROPERTY_TARGET_AC_SOURCE_FREQUENCY */
    
    /*
     * Software Phase Adjustment (by ADC ISR) for 3 channels
     * Set as 0 if not want to delay
     * The maximum step will be auto calculated to adjust the buffer size
     */

    #define EM_ADC_DELAY_STEP_VOLTAGE                           (6)                                         /* Step for phase adjustment of voltage channel */
                                                                
    #define EM_ADC_DELAY_STEP_VOLTAGE90                         (EM_ADC_DELAY_STEP_VOLTAGE + 20)            /* Step for phase adjustment of voltage channel */
    #define EM_ADC_DELAY_VOLTAGE90_MAX_STEP                     (EM_ADC_DELAY_STEP_VOLTAGE90 + 5)

    #define EM_ADC_DELAY_STEP_CURRENT_MAX_STEP                  MAX_OF_4(                               \
                                                                    EM_ADC_DELAY_STEP_CURRENT_PHASE_R,  \
                                                                    EM_ADC_DELAY_STEP_CURRENT_PHASE_Y,  \
                                                                    EM_ADC_DELAY_STEP_CURRENT_PHASE_B,  \
                                                                    EM_ADC_DELAY_STEP_CURRENT_NEUTRAL)

    /* I/Fs mapping
     *      Macro Name / I/Fs                                   Setting/Description */
    #define EM_ADC_Voltage_DriverRead(channel, buffer)          {\
                                                                    buffer = (uint16_t)g_adc_data[\
                                                                            channel - EM_ADC_VOL_DRIVER_START_SCAN_CHANNEL] >> 1;\
                                                                }
    #define EM_ADC_Voltage90_DriverRead(channel, buffer)        {\
                                                                    buffer = (uint16_t)g_adc_data[\
                                                                            channel - EM_ADC_VOL_DRIVER_START_SCAN_CHANNEL + 3] >> 1;\
                                                                }
    #define EM_ADC_DriverSetPhaseStep(channel, step)            R_DSADC_AdjustPhaseDelay(channel, step) /* AD Driver Set Phase Steps   */
/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/

#endif /* _WRAPPER_EM_SW_CONFIG_H */
