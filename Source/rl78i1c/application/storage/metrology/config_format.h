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
* File Name    : config_format.h
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : CCRL
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : Storage Format Header file

* Note         : NEED TO CHANGE THIS FILE WHEN
*              :   . EM CORE TYPE DEFINITION IS CHANGED, OR
*              :   . CONFIG START ADDRESS IS CHANGED
* Caution      : DATA ALIGNMENT
*              :    DATA ALIGNMENT ON THIS FORMAT IS 2-BYTES ALIGNMENT, EVEN ADDRESS.
*              :    PLEASE DON'T CHANGE TO OTHER ALIGNMENT SETTING.
*              :    WHEN CHANGE THE DATA ALIGNMENT SETTING, IT WILL DAMAGE THE FORMAT
*              :    ON CONFIG
*              :
*              : BIT FIELD FORMAT
*              :    BIT FIELD FORMAT IS FROM LSB FIRST
*              :    PLEASE DON'T CHANGE THIS SETTING ON THE COMPILE OPTION (IF SUPPORTED)

***********************************************************************************************************************/

#ifndef _CONFIG_STORAGE_FORMAT_H
#define _CONFIG_STORAGE_FORMAT_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "typedef.h"        /* GSCE Standard Typedef */

/* Middleware */
#include "em_type.h"        /* EM Core Type Definitions */
#include "em_constraint.h"

/* Application */
#include "dataflash.h"         /* Dataflash MW */

/******************************************************************************
Macro definitions for Typedef
******************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/* CONFIG Storage Header */
typedef struct tagCfgStorageHeader
{
    /* Total: 6 Bytes */
    uint16_t    usage;                      /* (2 bytes) Usage (number of bytes)                 */
    uint16_t    num_of_calib;               /* (2 bytes) Number of EM Calibration bytes          */
    
} CONFIG_STORAGE_HEADER;

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/* CONFIG Information */
#define CONFIG_STORAGE_START_ADDR                       DATAFLASH_DEVICE_START_ADDR   /* CONFIG Start address */
#define CONFIG_STORAGE_SIZE                             DATAFLASH_DEVICE_SIZE         /* CONFIG Size */
#define CONFIG_STORAGE_PAGESIZE                         DATAFLASH_DEVICE_PAGE_SIZE     /* CONFIG Page Size */

/* CONFIG Storage Type */
#define CONFIG_STORAGE_TYPE_INTEGER8                    0       /* uint8_t            */
#define CONFIG_STORAGE_TYPE_ARRAY_INTEGER8              1       /* array of uint8_t   */
#define CONFIG_STORAGE_TYPE_INTEGER16                   2       /* uint16_t           */
#define CONFIG_STORAGE_TYPE_ARRAY_INTEGER16             3       /* array of uint16_t  */
#define CONFIG_STORAGE_TYPE_INTEGER32                   4       /* uint32_t           */
#define CONFIG_STORAGE_TYPE_ARRAY_INTEGER32             5       /* array of uint32_t  */
#define CONFIG_STORAGE_TYPE_FLOAT32                     6       /* float32_t          */
#define CONFIG_STORAGE_TYPE_ARRAY_FLOAT32               7       /* array of float32_t */
#define CONFIG_STORAGE_TYPE_STRUCT                      8       /* (struct)           */
#define CONFIG_STORAGE_TYPE_ARRAY_STRUCT                9       /* (array of struct)  */

/* CONFIG Group Enable/Disable Macro */
#define CONFIG_STORAGE_HEADER_GROUP                     1
#define CONFIG_STORAGE_CONFIG_GROUP                     1
#define CONFIG_STORAGE_CALIB_GROUP                      1

/* CONFIG Header Structure Location + Size
 * 11 Macro Items */
#if CONFIG_STORAGE_HEADER_GROUP

#define CONFIG_STORAGE_HEADER_ADDR                      (CONFIG_STORAGE_START_ADDR + 0x0000)                                    /* Offset 0x0000 */
#define CONFIG_STORAGE_HEADER_SIZE                      (sizeof(CONFIG_STORAGE_HEADER))                                         /* 24 Bytes */
#define CONFIG_STORAGE_HEADER_TYPE                      CONFIG_STORAGE_TYPE_STRUCT                                              /* Structure */
    
    /* Header Code */
    #define CONFIG_STORAGE_HEADER_HEADER_CODE_ADDR          (CONFIG_STORAGE_HEADER_ADDR                   + 0)                  /* First Element  */
    #define CONFIG_STORAGE_HEADER_HEADER_CODE_SIZE          (sizeof(uint32_t))
    #define CONFIG_STORAGE_HEADER_HEADER_CODE_TYPE          CONFIG_STORAGE_TYPE_INTEGER32

    /* Mask code for data flash*/
    #define CONFIG_STORAGE_HEADER_CODE_MASK                 0x5350454D                                                          /* Mask Code for global data flash header code*/
    
#endif /* CONFIG_STORAGE_HEADER_GROUP */

/* EM Calibration Structure location + size */
#if CONFIG_STORAGE_CALIB_GROUP
#define CONFIG_STORAGE_CALIB_ADDR                       (CONFIG_STORAGE_START_ADDR + 0x00F8)                                        /* Offset */
/* Size of calibration data for driver */
#define CONFIG_STORAGE_CALIB_DRIVER                     (\
                                                            sizeof(uint8_t)*2                                                           /* DSAD gain register */        \
                                                        )
/* Size of EM_CALIBRATION without pointer */                                                        
#define CONFIG_STORAGE_CALIB_NO_ARRAY_SIZE              (\
                                                            (sizeof(EM_CALIBRATION))                                                -                                   \
                                                            (sizeof(((EM_CALIBRATION *)0)->sw_gain))                                -   /* Gain array */                \
                                                            (sizeof(((EM_CALIBRATION *)0)->sw_phase_correction))                        /* Phase array */               \
                                                        )
/* Size of whole calibration page */
#define CONFIG_STORAGE_CALIB_SIZE                       (\
                                                            (CONFIG_STORAGE_CALIB_NO_ARRAY_SIZE)                                    +                                   \
                                                            (sizeof(float32_t) * EM_VOL_CHANNEL_NUM * EM_GAIN_PHASE_NUM_LEVEL_MAX)     +   /* Gain array */                \
                                                            (sizeof(float32_t) * EM_VOL_CHANNEL_NUM * EM_GAIN_PHASE_NUM_LEVEL_MAX)    +   /* Phase array */               \
                                                            (CONFIG_STORAGE_CALIB_DRIVER)                                                                               \
                                                        )
#define CONFIG_STORAGE_CALIB_TYPE                       CONFIG_STORAGE_TYPE_STRUCT                                                  /* Structure */

    /* Sampling frequency */
    #define CONFIG_STORAGE_CALIB_SAMPLING_FREQUENCY_ADDR                    (CONFIG_STORAGE_CALIB_ADDR                              + 0)                  /* First Element */
    #define CONFIG_STORAGE_CALIB_SAMPLING_FREQUENCY_SIZE                    (sizeof(float32_t))
    #define CONFIG_STORAGE_CALIB_SAMPLING_FREQUENCY_TYPE                    CONFIG_STORAGE_TYPE_FLOAT32                 
                    
    /* Coefficient */
    /* Phase_R */
        /* VRMS Coefficient */
        #define CONFIG_STORAGE_CALIB_COEFF_VRMS_PHASE_R_ADDR                (CONFIG_STORAGE_CALIB_SAMPLING_FREQUENCY_ADDR                + CONFIG_STORAGE_CALIB_SAMPLING_FREQUENCY_SIZE)
        #define CONFIG_STORAGE_CALIB_COEFF_VRMS_PHASE_R_SIZE                (sizeof(float32_t))
        #define CONFIG_STORAGE_CALIB_COEFF_VRMS_PHASE_R_TYPE                CONFIG_STORAGE_TYPE_FLOAT32
    
        /* IRMS Coefficient */  
        #define CONFIG_STORAGE_CALIB_COEFF_IRMS_PHASE_R_ADDR                (CONFIG_STORAGE_CALIB_COEFF_VRMS_PHASE_R_ADDR           + CONFIG_STORAGE_CALIB_COEFF_VRMS_PHASE_R_SIZE)
        #define CONFIG_STORAGE_CALIB_COEFF_IRMS_PHASE_R_SIZE                (sizeof(float32_t))
        #define CONFIG_STORAGE_CALIB_COEFF_IRMS_PHASE_R_TYPE                CONFIG_STORAGE_TYPE_FLOAT32
    
        /* Active Power Coefficient */  
        #define CONFIG_STORAGE_CALIB_COEFF_ACTIVE_POWER_PHASE_R_ADDR        (CONFIG_STORAGE_CALIB_COEFF_IRMS_PHASE_R_ADDR           + CONFIG_STORAGE_CALIB_COEFF_IRMS_PHASE_R_SIZE)
        #define CONFIG_STORAGE_CALIB_COEFF_ACTIVE_POWER_PHASE_R_SIZE        (sizeof(float32_t))
        #define CONFIG_STORAGE_CALIB_COEFF_ACTIVE_POWER_PHASE_R_TYPE        CONFIG_STORAGE_TYPE_FLOAT32
    
        /* Reactive Power Coefficient */    
        #define CONFIG_STORAGE_CALIB_COEFF_REACTIVE_POWER_PHASE_R_ADDR      (CONFIG_STORAGE_CALIB_COEFF_ACTIVE_POWER_PHASE_R_ADDR   + CONFIG_STORAGE_CALIB_COEFF_ACTIVE_POWER_PHASE_R_SIZE)
        #define CONFIG_STORAGE_CALIB_COEFF_REACTIVE_POWER_PHASE_R_SIZE      (sizeof(float32_t))
        #define CONFIG_STORAGE_CALIB_COEFF_REACTIVE_POWER_PHASE_R_TYPE      CONFIG_STORAGE_TYPE_FLOAT32

        /* Apparent Power Coefficient */
        #define CONFIG_STORAGE_CALIB_COEFF_APPARENT_POWER_PHASE_R_ADDR      (CONFIG_STORAGE_CALIB_COEFF_REACTIVE_POWER_PHASE_R_ADDR + CONFIG_STORAGE_CALIB_COEFF_REACTIVE_POWER_PHASE_R_SIZE)
        #define CONFIG_STORAGE_CALIB_COEFF_APPARENT_POWER_PHASE_R_SIZE      (sizeof(float32_t))
        #define CONFIG_STORAGE_CALIB_COEFF_APPARENT_POWER_PHASE_R_TYPE      CONFIG_STORAGE_TYPE_FLOAT32

    /* Phase_Y */
        /* VRMS Coefficient */
        #define CONFIG_STORAGE_CALIB_COEFF_VRMS_PHASE_Y_ADDR                (CONFIG_STORAGE_CALIB_COEFF_APPARENT_POWER_PHASE_R_ADDR + CONFIG_STORAGE_CALIB_COEFF_APPARENT_POWER_PHASE_R_SIZE)
        #define CONFIG_STORAGE_CALIB_COEFF_VRMS_PHASE_Y_SIZE                (sizeof(float32_t))
        #define CONFIG_STORAGE_CALIB_COEFF_VRMS_PHASE_Y_TYPE                CONFIG_STORAGE_TYPE_FLOAT32
    
        /* IRMS Coefficient */  
        #define CONFIG_STORAGE_CALIB_COEFF_IRMS_PHASE_Y_ADDR                (CONFIG_STORAGE_CALIB_COEFF_VRMS_PHASE_Y_ADDR           + CONFIG_STORAGE_CALIB_COEFF_VRMS_PHASE_Y_SIZE)
        #define CONFIG_STORAGE_CALIB_COEFF_IRMS_PHASE_Y_SIZE                (sizeof(float32_t))
        #define CONFIG_STORAGE_CALIB_COEFF_IRMS_PHASE_Y_TYPE                CONFIG_STORAGE_TYPE_FLOAT32
    
        /* Active Power Coefficient */  
        #define CONFIG_STORAGE_CALIB_COEFF_ACTIVE_POWER_PHASE_Y_ADDR        (CONFIG_STORAGE_CALIB_COEFF_IRMS_PHASE_Y_ADDR           + CONFIG_STORAGE_CALIB_COEFF_IRMS_PHASE_Y_SIZE)
        #define CONFIG_STORAGE_CALIB_COEFF_ACTIVE_POWER_PHASE_Y_SIZE        (sizeof(float32_t))
        #define CONFIG_STORAGE_CALIB_COEFF_ACTIVE_POWER_PHASE_Y_TYPE        CONFIG_STORAGE_TYPE_FLOAT32
    
        /* Reactive Power Coefficient */    
        #define CONFIG_STORAGE_CALIB_COEFF_REACTIVE_POWER_PHASE_Y_ADDR      (CONFIG_STORAGE_CALIB_COEFF_ACTIVE_POWER_PHASE_Y_ADDR   + CONFIG_STORAGE_CALIB_COEFF_ACTIVE_POWER_PHASE_Y_SIZE)
        #define CONFIG_STORAGE_CALIB_COEFF_REACTIVE_POWER_PHASE_Y_SIZE      (sizeof(float32_t))
        #define CONFIG_STORAGE_CALIB_COEFF_REACTIVE_POWER_PHASE_Y_TYPE      CONFIG_STORAGE_TYPE_FLOAT32

        /* Apparent Power Coefficient */
        #define CONFIG_STORAGE_CALIB_COEFF_APPARENT_POWER_PHASE_Y_ADDR      (CONFIG_STORAGE_CALIB_COEFF_REACTIVE_POWER_PHASE_Y_ADDR + CONFIG_STORAGE_CALIB_COEFF_REACTIVE_POWER_PHASE_Y_SIZE)
        #define CONFIG_STORAGE_CALIB_COEFF_APPARENT_POWER_PHASE_Y_SIZE      (sizeof(float32_t))
        #define CONFIG_STORAGE_CALIB_COEFF_APPARENT_POWER_PHASE_Y_TYPE      CONFIG_STORAGE_TYPE_FLOAT32

    /* Phase_B */
        /* VRMS Coefficient */
        #define CONFIG_STORAGE_CALIB_COEFF_VRMS_PHASE_B_ADDR                (CONFIG_STORAGE_CALIB_COEFF_APPARENT_POWER_PHASE_Y_ADDR + CONFIG_STORAGE_CALIB_COEFF_APPARENT_POWER_PHASE_Y_SIZE)
        #define CONFIG_STORAGE_CALIB_COEFF_VRMS_PHASE_B_SIZE                (sizeof(float32_t))
        #define CONFIG_STORAGE_CALIB_COEFF_VRMS_PHASE_B_TYPE                CONFIG_STORAGE_TYPE_FLOAT32
    
        /* IRMS Coefficient */  
        #define CONFIG_STORAGE_CALIB_COEFF_IRMS_PHASE_B_ADDR                (CONFIG_STORAGE_CALIB_COEFF_VRMS_PHASE_B_ADDR           + CONFIG_STORAGE_CALIB_COEFF_VRMS_PHASE_B_SIZE)
        #define CONFIG_STORAGE_CALIB_COEFF_IRMS_PHASE_B_SIZE                (sizeof(float32_t))
        #define CONFIG_STORAGE_CALIB_COEFF_IRMS_PHASE_B_TYPE                CONFIG_STORAGE_TYPE_FLOAT32
    
        /* Active Power Coefficient */  
        #define CONFIG_STORAGE_CALIB_COEFF_ACTIVE_POWER_PHASE_B_ADDR        (CONFIG_STORAGE_CALIB_COEFF_IRMS_PHASE_B_ADDR           + CONFIG_STORAGE_CALIB_COEFF_IRMS_PHASE_B_SIZE)
        #define CONFIG_STORAGE_CALIB_COEFF_ACTIVE_POWER_PHASE_B_SIZE        (sizeof(float32_t))
        #define CONFIG_STORAGE_CALIB_COEFF_ACTIVE_POWER_PHASE_B_TYPE        CONFIG_STORAGE_TYPE_FLOAT32
    
        /* Reactive Power Coefficient */    
        #define CONFIG_STORAGE_CALIB_COEFF_REACTIVE_POWER_PHASE_B_ADDR      (CONFIG_STORAGE_CALIB_COEFF_ACTIVE_POWER_PHASE_B_ADDR   + CONFIG_STORAGE_CALIB_COEFF_ACTIVE_POWER_PHASE_B_SIZE)
        #define CONFIG_STORAGE_CALIB_COEFF_REACTIVE_POWER_PHASE_B_SIZE      (sizeof(float32_t))
        #define CONFIG_STORAGE_CALIB_COEFF_REACTIVE_POWER_PHASE_B_TYPE      CONFIG_STORAGE_TYPE_FLOAT32

        /* Apparent Power Coefficient */
        #define CONFIG_STORAGE_CALIB_COEFF_APPARENT_POWER_PHASE_B_ADDR      (CONFIG_STORAGE_CALIB_COEFF_REACTIVE_POWER_PHASE_B_ADDR + CONFIG_STORAGE_CALIB_COEFF_REACTIVE_POWER_PHASE_B_SIZE)
        #define CONFIG_STORAGE_CALIB_COEFF_APPARENT_POWER_PHASE_B_SIZE      (sizeof(float32_t))
        #define CONFIG_STORAGE_CALIB_COEFF_APPARENT_POWER_PHASE_B_TYPE      CONFIG_STORAGE_TYPE_FLOAT32
    
    /* IRMS Coefficient */  
        #define CONFIG_STORAGE_CALIB_COEFF_IRMS_NEUTRAL_ADDR                (CONFIG_STORAGE_CALIB_COEFF_APPARENT_POWER_PHASE_B_ADDR + CONFIG_STORAGE_CALIB_COEFF_APPARENT_POWER_PHASE_B_SIZE)
        #define CONFIG_STORAGE_CALIB_COEFF_IRMS_NEUTRAL_SIZE                (sizeof(float32_t))
        #define CONFIG_STORAGE_CALIB_COEFF_IRMS_NEUTRAL_TYPE                CONFIG_STORAGE_TYPE_FLOAT32
        
    /* SW Phase Correction */
    /* Phase_R */
        /* SW Phase Correction Degree Array, 2 elements
         * 1 element is a float32_t type */
        #define CONFIG_STORAGE_CALIB_SW_DEGREE_ARRAY_PHASE_R_ADDR           (CONFIG_STORAGE_CALIB_COEFF_IRMS_NEUTRAL_ADDR           + CONFIG_STORAGE_CALIB_COEFF_IRMS_NEUTRAL_SIZE)
        #define CONFIG_STORAGE_CALIB_SW_DEGREE_ARRAY_PHASE_R_SIZE           (sizeof(float32_t) * EM_GAIN_PHASE_NUM_LEVEL_MAX)
        #define CONFIG_STORAGE_CALIB_SW_DEGREE_ARRAY_PHASE_R_TYPE           CONFIG_STORAGE_TYPE_ARRAY_FLOAT32
    /* Phase_Y */
        /* SW Phase Correction Degree Array, 2 elements
         * 1 element is a float32_t type */
        #define CONFIG_STORAGE_CALIB_SW_DEGREE_ARRAY_PHASE_Y_ADDR           (CONFIG_STORAGE_CALIB_SW_DEGREE_ARRAY_PHASE_R_ADDR      + CONFIG_STORAGE_CALIB_SW_DEGREE_ARRAY_PHASE_R_SIZE)
        #define CONFIG_STORAGE_CALIB_SW_DEGREE_ARRAY_PHASE_Y_SIZE           (sizeof(float32_t) * EM_GAIN_PHASE_NUM_LEVEL_MAX)
        #define CONFIG_STORAGE_CALIB_SW_DEGREE_ARRAY_PHASE_Y_TYPE           CONFIG_STORAGE_TYPE_ARRAY_FLOAT32
    /* Phase_B */
        /* SW Phase Correction Degree Array, 2 elements
         * 1 element is a float32_t type */
        #define CONFIG_STORAGE_CALIB_SW_DEGREE_ARRAY_PHASE_B_ADDR           (CONFIG_STORAGE_CALIB_SW_DEGREE_ARRAY_PHASE_Y_ADDR      + CONFIG_STORAGE_CALIB_SW_DEGREE_ARRAY_PHASE_Y_SIZE)
        #define CONFIG_STORAGE_CALIB_SW_DEGREE_ARRAY_PHASE_B_SIZE           (sizeof(float32_t) * EM_GAIN_PHASE_NUM_LEVEL_MAX)
        #define CONFIG_STORAGE_CALIB_SW_DEGREE_ARRAY_PHASE_B_TYPE           CONFIG_STORAGE_TYPE_ARRAY_FLOAT32

    /* SW Gain */
    /* Phase_R */
        /* SW Phase Channel Gain Array, 2 elements
         * 1 element is a float32_t type */
        #define CONFIG_STORAGE_CALIB_SW_GAIN_ARRAY_PHASE_R_ADDR             (CONFIG_STORAGE_CALIB_SW_DEGREE_ARRAY_PHASE_B_ADDR      + CONFIG_STORAGE_CALIB_SW_DEGREE_ARRAY_PHASE_B_SIZE)
        #define CONFIG_STORAGE_CALIB_SW_GAIN_ARRAY_PHASE_R_SIZE             (sizeof(float32_t) * EM_GAIN_PHASE_NUM_LEVEL_MAX)
        #define CONFIG_STORAGE_CALIB_SW_GAIN_ARRAY_PHASE_R_TYPE             CONFIG_STORAGE_TYPE_ARRAY_FLOAT32
        
    /* Phase_Y */
        /* SW Phase Channel Gain Array, 2 elements
         * 1 element is a float32_t type */
        #define CONFIG_STORAGE_CALIB_SW_GAIN_ARRAY_PHASE_Y_ADDR             (CONFIG_STORAGE_CALIB_SW_GAIN_ARRAY_PHASE_R_ADDR        + CONFIG_STORAGE_CALIB_SW_GAIN_ARRAY_PHASE_R_SIZE)
        #define CONFIG_STORAGE_CALIB_SW_GAIN_ARRAY_PHASE_Y_SIZE             (sizeof(float32_t) * EM_GAIN_PHASE_NUM_LEVEL_MAX)
        #define CONFIG_STORAGE_CALIB_SW_GAIN_ARRAY_PHASE_Y_TYPE             CONFIG_STORAGE_TYPE_ARRAY_FLOAT32
        
    /* Phase_B */
        /* SW Phase Channel Gain Array, 2 elements
         * 1 element is a float32_t type */
        #define CONFIG_STORAGE_CALIB_SW_GAIN_ARRAY_PHASE_B_ADDR             (CONFIG_STORAGE_CALIB_SW_GAIN_ARRAY_PHASE_Y_ADDR        + CONFIG_STORAGE_CALIB_SW_GAIN_ARRAY_PHASE_Y_SIZE)
        #define CONFIG_STORAGE_CALIB_SW_GAIN_ARRAY_PHASE_B_SIZE             (sizeof(float32_t) * EM_GAIN_PHASE_NUM_LEVEL_MAX)
        #define CONFIG_STORAGE_CALIB_SW_GAIN_ARRAY_PHASE_B_TYPE             CONFIG_STORAGE_TYPE_ARRAY_FLOAT32
        
    /* ADC Gain0 Value
     * 1 element is a uint8_t type */
    #define CONFIG_STORAGE_CALIB_DRIVER_ADC_GAIN0_ADDR                      (CONFIG_STORAGE_CALIB_SW_GAIN_ARRAY_PHASE_B_ADDR        + CONFIG_STORAGE_CALIB_SW_GAIN_ARRAY_PHASE_B_SIZE)
    #define CONFIG_STORAGE_CALIB_DRIVER_ADC_GAIN0_SIZE                      (sizeof(uint8_t))
    #define CONFIG_STORAGE_CALIB_DRIVER_ADC_GAIN0_TYPE                      CONFIG_STORAGE_TYPE_INTEGER8

    /* ADC Gain1 Value
     * 1 element is a uint8_t type */
    #define CONFIG_STORAGE_CALIB_DRIVER_ADC_GAIN1_ADDR                      (CONFIG_STORAGE_CALIB_DRIVER_ADC_GAIN0_ADDR             + CONFIG_STORAGE_CALIB_DRIVER_ADC_GAIN0_SIZE)
    #define CONFIG_STORAGE_CALIB_DRIVER_ADC_GAIN1_SIZE                      (sizeof(uint8_t))
    #define CONFIG_STORAGE_CALIB_DRIVER_ADC_GAIN1_TYPE                      CONFIG_STORAGE_TYPE_INTEGER8

    /* HIOTRM Value
     * 1 element is a uint8_t type */
    #define CONFIG_STORAGE_CALIB_DRIVER_HOCO_TRIM_ADDR                      (CONFIG_STORAGE_CALIB_DRIVER_ADC_GAIN1_ADDR             + CONFIG_STORAGE_CALIB_DRIVER_ADC_GAIN1_SIZE)
    #define CONFIG_STORAGE_CALIB_DRIVER_HOCO_TRIM_SIZE                      (sizeof(uint8_t))
    #define CONFIG_STORAGE_CALIB_DRIVER_HOCO_TRIM_TYPE                      CONFIG_STORAGE_TYPE_INTEGER8

    
#endif /* CONFIG_STORAGE_CALIB_GROUP */


/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/

#endif /* _CONFIG_STORAGE_FORMAT_H */

