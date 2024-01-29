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
* File Name    : r_cg_12adc.h
* Version      :  
* Device(s)    : R5F11MMD
* Tool-Chain   : CCRL
* Description  : This file implements device driver for ADC module.
* Creation Date: 2/19/2020
***********************************************************************************************************************/
#ifndef ADC_H
#define ADC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    A/D Control Register (ADCSR) 
*/
/* A/D conversion operation control (ADST) */
#define _0000_AD_CONVERSION_DISABLE                     (0x0000U) /* stops A/D conversion process */
#define _8000_AD_CONVERSION_ENABLE                      (0x8000U) /* starts A/D conversion process */
/* Scan mode select bit (ADCS) */
#define _0000_AD_SCAN_MODE_SINGLE                       (0x0000U) /* single scan mode */
#define _4000_AD_SCAN_MODE_CONTINUOUS                   (0x4000U) /* continuous scan mode */
/* Scan end interrupt enable bit (ADIE) */
#define _0000_AD_INTAD_DISABLE                          (0x0000U) /* disables INTAD generation upon scan completion */
#define _1000_AD_INTAD_ENABLE                           (0x1000U) /* enables INTAD  generation upon scan completion */
/* A/D conversion select bit (ADHSC) */
#define _0000_AD_CONVERSION_HIGH_SPEED                  (0x0000U) /* high-speed conversion */
#define _0400_AD_CONVERSION_NORMAL                      (0x0400U) /* normal conversion */
/* Trigger start enable bit (TRGE) */
#define _0000_AD_TRIGGER_CONVERSION_DISABLE             (0x0000U) /* disables A/D conversion to be started by trigger */
#define _0200_AD_TRIGGER_CONVERSION_ENABLE              (0x0200U) /* enables A/D conversion to be started by trigger */
/* Trigger select bit (EXTRG) */
#define _0000_AD_SYNCHRONOUS_TRIGGER                    (0x0000U) /* A/D conversion is started by synchronous trigger */
#define _0100_AD_ASYNCHRONOUS_TRIGGER                   (0x0100U) /* A/D conversion is started by asynchronous trigger */

/*
    A/D conversion channel select bit (ADANSA0) 
*/
/* A/D conversion channel select bit 00 (ANSA00) */
#define _0000_AD_ANI00_NOT_SUBJECT                      (0x0000U) /* ANI00 is not subjected to conversion */
#define _0001_AD_ANI00_SUBJECT                          (0x0001U) /* ANI00 is subjected to conversion */
/* A/D conversion channel select bit 01 (ANSA01) */
#define _0000_AD_ANI01_NOT_SUBJECT                      (0x0000U) /* ANI01 is not subjected to conversion */
#define _0002_AD_ANI01_SUBJECT                          (0x0002U) /* ANI01 is subjected to conversion */
/* A/D conversion channel select bit 02 (ANSA02) */
#define _0000_AD_ANI02_NOT_SUBJECT                      (0x0000U) /* ANI02 is not subjected to conversion */
#define _0004_AD_ANI02_SUBJECT                          (0x0004U) /* ANI02 is subjected to conversion */
/* A/D conversion channel select bit 03 (ANSA03) */
#define _0000_AD_ANI03_NOT_SUBJECT                      (0x0000U) /* ANI03 is not subjected to conversion */
#define _0008_AD_ANI03_SUBJECT                          (0x0008U) /* ANI03 is subjected to conversion */
/* A/D conversion channel select bit 04 (ANSA04) */
#define _0000_AD_ANI04_NOT_SUBJECT                      (0x0000U) /* ANI04 is not subjected to conversion */
#define _0010_AD_ANI04_SUBJECT                          (0x0010U) /* ANI04 is subjected to conversion */
/* A/D conversion channel select bit 05 (ANSA05) */
#define _0000_AD_ANI05_NOT_SUBJECT                      (0x0000U) /* ANI05 is not subjected to conversion */
#define _0020_AD_ANI05_SUBJECT                          (0x0020U) /* ANI05 is subjected to conversion */
/*
    A/D-converted value addition/average channel select (ADADS0) 
*/
/* A/D-converted value addition/average channel 00 select (ADS00) */
#define _0000_AD_ANI00_NOT_ADD_AVERAGE                  (0x0000U) /* A/D-converted value addition/average mode for ANI00 is not selected */
#define _0001_AD_ANI00_ADD_AVERAGE                      (0x0001U) /* A/D-converted value addition/average mode for ANI00 is selected */
/* A/D-converted value addition/average channel 01 select (ADS01) */
#define _0000_AD_ANI01_NOT_ADD_AVERAGE                  (0x0000U) /* A/D-converted value addition/average mode for ANI01 is not selected */
#define _0002_AD_ANI01_ADD_AVERAGE                      (0x0002U) /* A/D-converted value addition/average mode for ANI01 is selected */
/* A/D-converted value addition/average channel 02 select (ADS02) */
#define _0000_AD_ANI02_NOT_ADD_AVERAGE                  (0x0000U) /* A/D-converted value addition/average mode for ANI02 is not selected */
#define _0004_AD_ANI02_ADD_AVERAGE                      (0x0004U) /* A/D-converted value addition/average mode for ANI02 is selected */
/* A/D-converted value addition/average channel 03 select (ADS03) */
#define _0000_AD_ANI03_NOT_ADD_AVERAGE                  (0x0000U) /* A/D-converted value addition/average mode for ANI03 is not selected */
#define _0008_AD_ANI03_ADD_AVERAGE                      (0x0008U) /* A/D-converted value addition/average mode for ANI03 is selected */
/* A/D-converted value addition/average channel 04 select (ADS04) */
#define _0000_AD_ANI04_NOT_ADD_AVERAGE                  (0x0000U) /* A/D-converted value addition/average mode for ANI04 is not selected */
#define _0010_AD_ANI04_ADD_AVERAGE                      (0x0010U) /* A/D-converted value addition/average mode for ANI04 is selected */
/* A/D-converted value addition/average channel 05 select (ADS05) */
#define _0000_AD_ANI05_NOT_ADD_AVERAGE                  (0x0000U) /* A/D-converted value addition/average mode for ANI05 is not selected */
#define _0020_AD_ANI05_ADD_AVERAGE                      (0x0020U) /* A/D-converted value addition/average mode for ANI05 is selected */

/*
    A/D-converted Value Addion/Average Count Select Register (ADADC) 
*/
/* Average mode enable bit (AVEE) */
#define _00_AD_MODE_ADDITION                            (0x00U) /* addition mode is selected */
#define _80_AD_MODE_AVERAGE                             (0x80U) /* average mode is selected */
/* Addition count select bit (ADC) */
#define _00_AD_CONVERSION_1TIME                         (0x00U) /* 1-time conversion (no addition; same as normal conversion) */
#define _01_AD_CONVERSION_2TIME                         (0x01U) /* 2-time conversion (addition once) */
#define _02_AD_CONVERSION_3TIME                         (0x02U) /* 3-time conversion (addition twice) */
#define _03_AD_CONVERSION_4TIME                         (0x03U) /* 4-time conversion (addition three times) */
#define _05_AD_CONVERSION_16TIME                        (0x05U) /* 16-time conversion (addition 15 times) */

/*
    A/D Control Extended Register (ADCER) 
*/
/* A/D data register format select bit (ADRFMT) */
#define _0000_AD_DATA_FLUSH_RIGHT                       (0x0000U) /* flush-right is selected for the A/D data register format */
#define _8000_AD_DATA_FLUSH_LEFT                        (0x8000U) /* flush-left is selected for the A/D data register format */
/* Self-diagnosis enable bit (DIAGM) */
#define _0000_AD_SELF_DIAGNOSIS_DISABLE                 (0x0000U) /* disables self-diagnosis of 12-bit A/D converter. */
#define _0800_AD_SELF_DIAGNOSIS_ENABLE                  (0x0800U) /* enables self-diagnosis of 12-bit A/D converter. */
/* Self-diagnosis mode select bit (DIAGLD) */
#define _0000_AD_SELF_DIAGNOSIS_ROTATION                (0x0000U) /* rotation mode for self-diagnosis voltage */
#define _0400_AD_SELF_DIAGNOSIS_FIXED                   (0x0400U) /* fixed mode for self-diagnosis voltage */
/* Self-diagnosis conversion voltage select bit (DIAGVAL) */
#define _0100_AD_SELF_DIAGNOSIS_0_V                     (0x0100U) /* uses the voltage of 0 V for self-diagnosis */
#define _0200_AD_SELF_DIAGNOSIS_1_2_V                   (0x0200U) /* uses the voltage of reference power supply x 1/2 for self-diagnosis */
#define _0300_AD_SELF_DIAGNOSIS_REF_V                   (0x0300U) /* uses the voltage of reference power supply for self-diagnosis. */
/* A/D data register automatic clearing enable bit (ACE) */
#define _0000_AD_AUTO_CLEAR_DISABLE                     (0x0000U) /* disables automatic clearing */
#define _0020_AD_AUTO_CLEAR_ENABLE                      (0x0020U) /* enables automatic clearing */

/*
    A/D Conversion Start Trigger Select Register (ADSTRGR) 
*/
/* A/D conversion start trigger select bit (TRSA5,TRSA4,TRSA3,TRSA2,TRSA1,TRSA0) */
#define _0000_AD_TRIGGER_ADTRG                          (0x0000U) /* external trigger input pin (ADTRG) */
#define _3000_AD_TRIGGER_ELCTRG0                        (0x3000U) /* event output signal from event link controller (ELCTRG0) */
#define _3F00_AD_TRIGGER_SOURCE                         (0x3F00U) /* trigger source deselection */

/*
    A/D Conversion Extended Input Control Register (ADEXICR) 
*/
/* Internal reference voltage A/D conversion select bit (OCSA) */
#define _0000_AD_REF_VOLTAGE_DISABLE                    (0x0000U) /* A/D conversion of internal reference voltage is not performed */
#define _0200_AD_REF_VOLTAGE_ENABLE                     (0x0200U) /* A/D conversion of internal reference voltage is performed */
/* Temperature sensor output A/D conversion select bit (TSSA) */
#define _0000_AD_TEMPERATURE_DISABLE                    (0x0000U) /* A/D conversion of temperature sensor output is not performed */
#define _0100_AD_TEMPERATURE_ENABLE                     (0x0100U) /* A/D conversion of temperature sensor output is performed */
/* Internal reference voltage A/D-converted value addition/average mode select bit (OCSAD) */
#define _0000_AD_REF_ADD_AVERAGE_DISABLE                (0x0000U) /* internal reference voltage A/D-converted value addition/average mode is not selected */
#define _0002_AD_REF_ADD_AVERAGE_ENABLE                 (0x0002U) /* internal reference voltage A/D-converted value addition/average mode is selected */
/* Temperature sensor output A/D-converted value addition/average mode select (TSSAD) */
#define _0000_AD_TEMPERATURE_ADD_AVERAGE_DISABLE        (0x0000U) /* temperature sensor output A/D-converted value addition/average mode is not selected. */
#define _0001_AD_TEMPERATURE_ADD_AVERAGE_ENABLE         (0x0001U) /* temperature sensor output A/D-converted value addition/average mode is selected. */

/*
    A/D sample-and-hold circuit control register (ADSHCR) 
*/

/* ANI0 channel-dedicated sample-and-hold circuit bypass select bit (SHANS[0]) */
#define _0000_AD_BYPASS_SAH_ANI0                        (0x0000U) /* Bypass channel ANI0 dedicated sample-and-hold circuits */
#define _0100_AD_USE_SAH_ANI0                           (0x0100U) /* Use the channel ANI0 dedicated sample-and-hold circuits */
/* ANI1 channel-dedicated sample-and-hold circuit bypass select bit (SHANS[1]) */
#define _0000_AD_BYPASS_SAH_ANI1                        (0x0000U) /* Bypass channel ANI1 dedicated sample-and-hold circuits */
#define _0200_AD_USE_SAH_ANI1                           (0x0200U) /* Use the channel ANI1 dedicated sample-and-hold circuits */
/* ANI2 channel-dedicated sample-and-hold circuit bypass select bit (SHANS[2]) */
#define _0000_AD_BYPASS_SAH_ANI2                        (0x0000U) /* Bypass channel ANI2 dedicated sample-and-hold circuits */
#define _0400_AD_USE_SAH_ANI2                           (0x0400U) /* Use the channel ANI2 dedicated sample-and-hold circuits */

/*
    A/D High-potential/Low-potential Reference Voltage Control Register (ADHVREFCNT) 
*/
/* Sleep bit (ADSLP) */
#define _00_AD_SLEEP_NORMAL                             (0x00U) /* normal operation */
#define _80_AD_SLEEP_STANDBY                            (0x80U) /* standby state */
/* Low-potential reference voltage select bit (LVSEL) */
#define _00_AD_LOW_REF_AVSS                             (0x00U) /* AVSS is selected as the low-potential reference voltage */
#define _10_AD_LOW_REF_AVREFM                           (0x10U) /* AVREFM is selected as the low-potential reference voltage */
/* High-potential reference voltage select bit (HVSEL1,HVSEL0) */
#define _00_AD_HIGH_REF_AVDD                            (0x00U) /* AVDD is selected as the high-potential reference voltage */
#define _01_AD_HIGH_REF_AVREFP_VREFOUT                  (0x01U) /* AVREFP or VREFOUT is selected as the high-potential reference voltage */
#define _03_AD_HIGH_REF_DISCHARGE                       (0x03U) /* discharges the internal reference voltage (the high-potential reference voltage is not selected) */

/*
    A/D Conversion Clock Control Register (ADCKS) 
*/
/* A/D conversion clock select bit (ADCKS1,ADCKS0) */
#define _00_AD_CLK_NOT_DIVIDED                          (0x00U) /* system clock not divided (f1) */
#define _01_AD_CLK_DIVIDED_2                            (0x01U) /* system clock divided by 2 (f2) */
#define _02_AD_CLK_DIVIDED_4                            (0x02U) /* system clock divided by 4 (f4) */
#define _03_AD_CLK_DIVIDED_8                            (0x03U) /* system clock divided by 8 (f8) */

/*
    Voltage reference control register (VREFAMPCNT)
*/
/* Overcurrents detection bit (OLDETEN) */
#define _00_VREF_DISABLE_OVC_DETECTION                  (0x00U) /* Disable detection of overcurrents */
#define _01_VREF_DISABLE_OVC_DETECTION                  (0x01U) /* Enable detection of overcurrents */
/* Output voltage control (VREFADCG[1:0]) */
#define _00_VREF_OUTPUT_VOLTAGE_015V                    (0x00U) /* 1.5V reference voltage */
#define _04_VREF_OUTPUT_VOLTAGE_020V                    (0x04U) /* 2.0V reference voltage */
#define _06_VREF_OUTPUT_VOLTAGE_025V                    (0x06U) /* 2.5V reference voltage */
/* Voltage reference output control bit (VREFADCG) */
#define _00_VREF_OUTPUT_DISABLE                         (0x00U) /* Disable VREF output and use AVREFP as high potential reference voltage */
#define _08_VREF_OUTPUT_ENABLE                          (0x08U) /* Enable VREF output and select VREFOUT as high potential reference voltage */
/* BGR enable control (BGREN) */
#define _00_VREF_BGR_DISABLE                            (0x00U) /* Turn off power supply for BGR block */
#define _10_VREF_BGR_ENABLE                             (0x10U) /* Turn on power supply for BGR block */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum
{
    ADCHANNEL0,
    ADCHANNEL1,
    ADCHANNEL2,
    ADCHANNEL3,
    ADCHANNEL4,
    ADCHANNEL5,
    ADINTERREFVOLT,
    ADTEMPERSENSOR0
} ad_channel_t;

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_12ADC_Create(void);
void R_12ADC_Start(void);
void R_12ADC_Stop(void);
MD_STATUS R_12ADC_Get_ValueResult(ad_channel_t channel, uint16_t * const buffer);
/* Start user code for function. Do not edit comment generated here */
void R_ADC_Set_OperationOn(void);
void R_ADC_Set_OperationOff(void);
NEAR_FUNC void r_12adc_interrupt(void);
/* End user code. Do not edit comment generated here */
#endif
