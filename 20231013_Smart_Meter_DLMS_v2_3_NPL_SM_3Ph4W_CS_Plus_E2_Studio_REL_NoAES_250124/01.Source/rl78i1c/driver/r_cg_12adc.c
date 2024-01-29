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
* Copyright (C) . All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_12adc.c
* Version      : 
* Device(s)    : 
* Tool-Chain   : CCRL
* Description  : This file implements device driver for ADC module.
* Creation Date: 2/19/2020
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_12adc.h"
/* Start user code for include. Do not edit comment generated here */
#include "wrp_app_mcu.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_12ADC_Create
* Description  : This function initializes AD converter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_12ADC_Create(void)
{
    ADCRES = 1U;    /* reset ADC converter */
    ADCRES = 0U;    /* reset release of ADC converter */
    ADCEN = 0U;     /* disable input clock supply */
    ADCEN = 1U;     /* enables input clock supply */
    ADCSR = _0000_AD_CONVERSION_DISABLE | _0000_AD_SCAN_MODE_SINGLE | _0000_AD_INTAD_DISABLE | 
            _0000_AD_CONVERSION_HIGH_SPEED | _0000_AD_TRIGGER_CONVERSION_DISABLE | _0000_AD_SYNCHRONOUS_TRIGGER;
    ADMK = 1U;      /* disable INTAD interrupt */
    ADIF = 0U;      /* clear INTAD interrupt flag */
    /* Set INTAD low priority */
    ADPR1 = 1U;
    ADPR0 = 1U;
    /* Set ANI00, ANI01, ANI02 pin */
    PMC2 = 0xFEU;
    PM2 = 0xFEU;
    /* Configure VREF before converter */
    /* Enable the BGR */
    VREFAMPCNT = _10_VREF_BGR_ENABLE;
    /* Stabilization time: 150us as in chapter43 */
    MCU_Delay(200);
    VREFAMPCNT = _10_VREF_BGR_ENABLE | _08_VREF_OUTPUT_ENABLE | _04_VREF_OUTPUT_VOLTAGE_020V | 
                 _00_VREF_DISABLE_OVC_DETECTION;
    /* Stabilization time: 1500us as in chapter43 */
    MCU_Delay(2000);
    ADCKS = _00_AD_CLK_NOT_DIVIDED;
	ADCSR = _0000_AD_CONVERSION_DISABLE | _0000_AD_SCAN_MODE_SINGLE | _1000_AD_INTAD_ENABLE | 
            _0000_AD_CONVERSION_HIGH_SPEED | _0200_AD_TRIGGER_CONVERSION_ENABLE | _0000_AD_SYNCHRONOUS_TRIGGER;
    ADSTRGR = _3000_AD_TRIGGER_ELCTRG0;
    ADHVREFCNT |= _03_AD_HIGH_REF_DISCHARGE;
    /* UM not explicitly mention how long is discharge time, use back L1A UM notes for VBGR */
    MCU_Delay(2);
    ADHVREFCNT = _00_AD_SLEEP_NORMAL | _00_AD_LOW_REF_AVSS | _01_AD_HIGH_REF_AVREFP_VREFOUT;
    ADADC = _00_AD_MODE_ADDITION | _00_AD_CONVERSION_1TIME;
    ADCER = _8000_AD_DATA_FLUSH_LEFT | _0000_AD_SELF_DIAGNOSIS_DISABLE | _0000_AD_SELF_DIAGNOSIS_ROTATION | 
            _0000_AD_AUTO_CLEAR_DISABLE;
	ADSSTR0 = 0x28;
    ADSSTR1 = 0x28;
    ADSSTR2 = 0x28;
	/* Set sample and hold circuit OFF*/
	ADSHCR =  0x58U;
    
    /* Set AD channel */
    ADANSA0 = _0000_AD_ANI05_NOT_SUBJECT | _0000_AD_ANI04_NOT_SUBJECT | _0000_AD_ANI03_NOT_SUBJECT | 
              _0004_AD_ANI02_SUBJECT | _0002_AD_ANI01_SUBJECT | _0001_AD_ANI00_SUBJECT;
    ADADS0 = _0000_AD_ANI05_NOT_ADD_AVERAGE | _0000_AD_ANI04_NOT_ADD_AVERAGE | _0000_AD_ANI03_NOT_ADD_AVERAGE | 
             _0000_AD_ANI02_NOT_ADD_AVERAGE | _0000_AD_ANI01_NOT_ADD_AVERAGE | _0000_AD_ANI00_NOT_ADD_AVERAGE;
    ADEXICR = _0000_AD_REF_VOLTAGE_DISABLE | _0000_AD_TEMPERATURE_DISABLE | _0000_AD_REF_ADD_AVERAGE_DISABLE | 
              _0000_AD_TEMPERATURE_ADD_AVERAGE_DISABLE;
}
/***********************************************************************************************************************
* Function Name: R_12ADC_Start
* Description  : This function starts AD converter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_12ADC_Start(void)
{
    ADIF = 0U;      /* clear INTAD interrupt flag */
    ADMK = 0U;      /* enable INTAD interrupt */
    ADCSR |= _8000_AD_CONVERSION_ENABLE;
}
/***********************************************************************************************************************
* Function Name: R_12ADC_Stop
* Description  : This function stops AD converter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_12ADC_Stop(void)
{
    ADCSR &= (uint16_t)~_8000_AD_CONVERSION_ENABLE;
    ADMK = 1U;      /* disable INTAD interrupt */
    ADIF = 0U;      /* clear INTAD interrupt flag */
}
/***********************************************************************************************************************
* Function Name: R_12ADC_Get_ValueResult
* Description  : This function gets AD converter result.
* Arguments    : channel -
*                    AD converter channel
*                buffer -
*                    buffer result
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_12ADC_Get_ValueResult(ad_channel_t channel, uint16_t * const buffer)
{
    MD_STATUS status = MD_OK;

    switch (channel)
    {
        case ADCHANNEL0:
            *buffer = (uint16_t)ADDR0;
            break;
        case ADCHANNEL1:
            *buffer = (uint16_t)ADDR1;
            break;
        case ADCHANNEL2:
            *buffer = (uint16_t)ADDR2;
            break;
        case ADCHANNEL3:
            *buffer = (uint16_t)ADDR3;
            break;
        case ADCHANNEL4:
            *buffer = (uint16_t)ADDR4;
            break;
        case ADCHANNEL5:
            *buffer = (uint16_t)ADDR5;
            break;
        case ADINTERREFVOLT:
            *buffer = (uint16_t)ADOCDR;
            break;
        case ADTEMPERSENSOR0:
            *buffer = (uint16_t)ADTSDR;
            break;
        default:
            status = MD_ARGERROR;
            break;
    }

    return status;
}

/* Start user code for adding. Do not edit comment generated here */
/***********************************************************************************************************************
* Function Name: R_ADC_Set_OperationOn
* Description  : This function enables comparator operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ADC_Set_OperationOn(void)
{
	ADCEN = 1U;  /* Supply clock to ADC _1000_AD_INTAD_ENABLE*/
}

/***********************************************************************************************************************
* Function Name: R_ADC_Set_OperationOff
* Description  : This function stops comparator operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ADC_Set_OperationOff(void)
{
	ADCEN = 0U;  /* Stop clock to ADC _0000_AD_INTAD_DISABLE*/
}

/* End user code. Do not edit comment generated here */
