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
* File Name    : r_dscl_iirbiquad_config.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : CCRL
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : ADC Wrapper for RL78/I1C Platform
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "platform.h"
#include "wrp_em_sw_config.h"

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
#if (EM_PLATFORM_PROPERTY_TARGET_AC_SOURCE_FREQUENCY == 50)
int32_t iir32_coeff_1[] = {
    /* Fs: 3906Hz coefficients */
    138502279   ,  -228022888   , 138502279 ,  -(-1728206983)   ,  -(703446828) ,
    666965132   ,  -1315481260  , 666965132 ,  -(-2085576663)   ,  -(1032295489),
    617738210   ,  -1203780843  , 617738210 ,  -(-1960740305)   ,  -(915577819) ,
};

int32_t iir32_coeff_2[] = {
    #if (METER_WRAPPER_ADC_CURRENT_CHANNEL_LPF_REDUCED_FS == 0)
    /* Fs: 3906Hz coefficients */
    138502279   ,  -228022888   , 138502279 ,  -(-1728206983)   ,  -(703446828) ,
    666965132   ,  -1315481260  , 666965132 ,  -(-2085576663)   ,  -(1032295489),
    617738210   ,  -1203780843  , 617738210 ,  -(-1960740305)   ,  -(915577819) ,
    #elif (METER_WRAPPER_ADC_CURRENT_CHANNEL_LPF_REDUCED_FS == 1)
    /* Fs: 1302Hz coefficients */
    165915417   ,  -16728554    , 165915417 ,  -(-1052124266)   ,  -(293484723) ,
    653536733   ,  -1147743046  , 653536733 ,  -(-1853535721)   ,  -(956498763) ,
    566626673   ,  -888401075   , 566626673 ,  -(-1526502108)   ,  -(673537538) ,
    #endif
};
#elif (EM_PLATFORM_PROPERTY_TARGET_AC_SOURCE_FREQUENCY == 60)
int32_t iir32_coeff_1[] = {
    /* Fs: 3906Hz coefficients */
    138423908   ,  -208880289   , 138423908 ,  -(-1651735688)   ,  -(645961391) ,
    665018747   ,  -1303578967  , 665018747 ,  -(-2068653446)   ,  -(1024255322),
    610409181   ,  -1175887430  , 610409181 ,  -(-1920308056)   ,  -(887079402) ,
};

int32_t iir32_coeff_2[] = {
    #if (METER_WRAPPER_ADC_CURRENT_CHANNEL_LPF_REDUCED_FS == 0)
    /* Fs: 3906Hz coefficients */
    138423908   ,  -208880289   , 138423908 ,  -(-1651735688)   ,  -(645961391) ,
    665018747   ,  -1303578967  , 665018747 ,  -(-2068653446)   ,  -(1024255322),
    610409181   ,  -1175887430  , 610409181 ,  -(-1920308056)   ,  -(887079402) ,
    #elif (METER_WRAPPER_ADC_CURRENT_CHANNEL_LPF_REDUCED_FS == 1)
    /* Fs: 1302Hz coefficients */
    182406032   ,  50991864     , 182406032 ,  -(-881211080)    ,  -(223273183) ,
    652092432   ,  -1077607511  , 652092432 ,  -(-1758481199)   ,  -(936024423) ,
    559759171   ,  -781978028   , 559759171 ,  -(-1387424332)   ,  -(618034045) ,
    #endif
};
#else
    #error "Unsupported line frequency, 50Hz or 60Hz only"
#endif

/******************************************************************************
Private global variables and functions
******************************************************************************/
