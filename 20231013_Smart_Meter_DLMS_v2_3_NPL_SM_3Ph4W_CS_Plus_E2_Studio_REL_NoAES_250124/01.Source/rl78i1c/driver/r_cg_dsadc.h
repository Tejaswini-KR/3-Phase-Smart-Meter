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
* Copyright (C) 2015, 2017 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_dsadc.h
* Version      : Code Generator for RL78/I1C V1.01.00.02 [15 May 2017]
* Device(s)    : R5F10NPJ
* Tool-Chain   : CCRL
* Description  : This file implements device driver for DSADC module.
* Creation Date: 3/22/2019
***********************************************************************************************************************/
#ifndef DSADC_H
#define DSADC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    DSAD converter mode register (DSADMR) 
*/
/* Sampling frequency selection (DSADFR) */
#define _0000_DSAD_SAMPLING_FREQUENCY_0                (0x0000U) /* 3906.25 Hz */
#define _8000_DSAD_SAMPLING_FREQUENCY_1                (0x8000U) /* 1953.125 Hz */
/* Sampling frequency selection (DSADTYP) */
#define _0000_DSAD_RESOLUTION_24BIT                    (0x0000U) /* 24 bits */
#define _4000_DSAD_RESOLUTION_16BIT                    (0x4000U) /* 16 bits */
/* DSAD converter power-on control (analog block) of channel 3 (DSADPON3) */
#define _0000_DSAD_CH3_POWER_DOWN                      (0x0000U) /* power down */
#define _0800_DSAD_CH3_POWER_ON                        (0x0800U) /* power on */
/* DSAD converter power-on control (analog block) of channel 2 (DSADPON2) */
#define _0000_DSAD_CH2_POWER_DOWN                      (0x0000U) /* power down */
#define _0400_DSAD_CH2_POWER_ON                        (0x0400U) /* power on */
/* DSAD converter power-on control (analog block) of channel 1 (DSADPON1) */
#define _0000_DSAD_CH1_POWER_DOWN                      (0x0000U) /* power down */
#define _0200_DSAD_CH1_POWER_ON                        (0x0200U) /* power on */
/* DSAD converter power-on control (analog block) of channel 0 (DSADPON0) */
#define _0000_DSAD_CH0_POWER_DOWN                      (0x0000U) /* power down */
#define _0100_DSAD_CH0_POWER_ON                        (0x0100U) /* power on */
/* DSAD converter operation enable (analog and digital blocks) of channel 3 (DSADCE3) */
#define _0000_DSAD_CH3_RESET                           (0x0000U) /* electric charge reset */
#define _0008_DSAD_CH3_OPERATION                       (0x0008U) /* normal operation */
/* DSAD converter operation enable (analog and digital blocks) of channel 2 (DSADCE2) */
#define _0000_DSAD_CH2_RESET                           (0x0000U) /* electric charge reset */
#define _0004_DSAD_CH2_OPERATION                       (0x0004U) /* normal operation */
/* DSAD converter operation enable (analog and digital blocks) of channel 1 (DSADCE1) */
#define _0000_DSAD_CH1_RESET                           (0x0000U) /* electric charge reset */
#define _0002_DSAD_CH1_OPERATION                       (0x0002U) /* normal operation */
/* DSAD converter operation enable (analog and digital blocks) of channel 0 (DSADCE0) */
#define _0000_DSAD_CH0_RESET                           (0x0000U) /* electric charge reset */
#define _0001_DSAD_CH0_OPERATION                       (0x0001U) /* normal operation */

/*
    DSAD converter gain control register 0 (DSADGCR0) 
*/
/* Channel 1 programmable amplifier gain selection (DSADGAIN12 - DSADGAIN10) */
#define _00_DSAD_CH1_PGAGAIN_1                         (0x00U) /* PGA gain: 1 time */
#define _10_DSAD_CH1_PGAGAIN_2                         (0x10U) /* PGA gain: 2 time */
#define _20_DSAD_CH1_PGAGAIN_4                         (0x20U) /* PGA gain: 4 time */
#define _30_DSAD_CH1_PGAGAIN_8                         (0x30U) /* PGA gain: 8 time */
#define _40_DSAD_CH1_PGAGAIN_16                        (0x40U) /* PGA gain: 16 time */
#define _50_DSAD_CH1_PGAGAIN_32                        (0x50U) /* PGA gain: 32 time */
/* Channel 0 programmable amplifier gain selection (DSADGAIN02 - DSADGAIN00) */
#define _00_DSAD_CH0_PGAGAIN_1                         (0x00U) /* PGA gain: 1 time */
#define _01_DSAD_CH0_PGAGAIN_2                         (0x01U) /* PGA gain: 2 time */
#define _02_DSAD_CH0_PGAGAIN_4                         (0x02U) /* PGA gain: 4 time */
#define _03_DSAD_CH0_PGAGAIN_8                         (0x03U) /* PGA gain: 8 time */
#define _04_DSAD_CH0_PGAGAIN_16                        (0x04U) /* PGA gain: 16 time */
#define _05_DSAD_CH0_PGAGAIN_32                        (0x05U) /* PGA gain: 32 time */

/*
    DSAD converter gain control register 1 (DSADGCR1) 
*/
/* Channel 3 programmable amplifier gain selection (DSADGAIN32 - DSADGAIN30) */
#define _00_DSAD_CH3_PGAGAIN_1                         (0x00U) /* PGA gain: 1 time */
#define _10_DSAD_CH3_PGAGAIN_2                         (0x10U) /* PGA gain: 2 time */
#define _20_DSAD_CH3_PGAGAIN_4                         (0x20U) /* PGA gain: 4 time */
#define _30_DSAD_CH3_PGAGAIN_8                         (0x30U) /* PGA gain: 8 time */
#define _40_DSAD_CH3_PGAGAIN_16                        (0x40U) /* PGA gain: 16 time */
#define _50_DSAD_CH3_PGAGAIN_32                        (0x50U) /* PGA gain: 32 time */
/* Channel 2 programmable amplifier gain selection (DSADGAIN22 - DSADGAIN20) */
#define _00_DSAD_CH2_PGAGAIN_1                         (0x00U) /* PGA gain: 1 time */
#define _01_DSAD_CH2_PGAGAIN_2                         (0x01U) /* PGA gain: 2 time */
#define _02_DSAD_CH2_PGAGAIN_4                         (0x02U) /* PGA gain: 4 time */
#define _03_DSAD_CH2_PGAGAIN_8                         (0x03U) /* PGA gain: 8 time */
#define _04_DSAD_CH2_PGAGAIN_16                        (0x04U) /* PGA gain: 16 time */
#define _05_DSAD_CH2_PGAGAIN_32                        (0x05U) /* PGA gain: 32 time */

/*
    DSAD Converter HPF Control Register (DSADHPFCR) 
*/
/* High-pass filter cutoff frequency selection (DSADCOF1,DSADCOF0) */
#define _00_DSAD_CUTOFF_FREQUENCY_0                    (0x00U) /* 0.607 Hz */
#define _40_DSAD_CUTOFF_FREQUENCY_1                    (0x40U) /* 1.214 Hz */
#define _80_DSAD_CUTOFF_FREQUENCY_2                    (0x80U) /* 2.429 Hz */
#define _C0_DSAD_CUTOFF_FREQUENCY_3                    (0xC0U) /* 4.857 Hz */
/* Channel 3 high-pass filter control (DSADTHR3) */
#define _00_DSAD_CH3_HIGHPASS_FILTER_ENABLE            (0x00U) /* enable high-pass filter */
#define _08_DSAD_CH3_HIGHPASS_FILTER_DISABLE           (0x08U) /* disable high-pass filter */
/* Channel 2 high-pass filter control (DSADTHR2) */
#define _00_DSAD_CH2_HIGHPASS_FILTER_ENABLE            (0x00U) /* enable high-pass filter */
#define _04_DSAD_CH2_HIGHPASS_FILTER_DISABLE           (0x04U) /* disable high-pass filter */
/* Channel 1 high-pass filter control (DSADTHR1) */
#define _00_DSAD_CH1_HIGHPASS_FILTER_ENABLE            (0x00U) /* enable high-pass filter */
#define _02_DSAD_CH1_HIGHPASS_FILTER_DISABLE           (0x02U) /* disable high-pass filter */
/* Channel 0 high-pass filter control (DSADTHR0) */
#define _00_DSAD_CH0_HIGHPASS_FILTER_ENABLE            (0x00U) /* enable high-pass filter */
#define _01_DSAD_CH0_HIGHPASS_FILTER_DISABLE           (0x01U) /* disable high-pass filter */


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _0000_DSAD_PHCR0_VALUE                         (0x0000U) /* DSAD Converter channel 0 phase adjustment */
#define _0000_DSAD_PHCR1_VALUE                         (0x0000U) /* DSAD Converter channel 1 phase adjustment */
#define _0000_DSAD_PHCR2_VALUE                         (0x0000U) /* DSAD Converter channel 2 phase adjustment */
#define _0000_DSAD_PHCR3_VALUE                         (0x0000U) /* DSAD Converter channel 3 phase adjustment */
#define _50_DSAD_WAIT_SETUP_TIME                        (0x50U)     /* Waiting time for DSAD stabilization: 80 DSAD conversion */

#define _0101_DSAD_ENABLE_CH0                           (0x0101U)
#define _0202_DSAD_ENABLE_CH1                           (0x0202U)
#define _0404_DSAD_ENABLE_CH2                           (0x0404U)
#define _0808_DSAD_ENABLE_CH3                           (0x0808U)

#define _0F0F_DSAD_ENABLE_ALLCH                         (0x0F0FU)
#define _0707_DSAD_ENABLE_3CH                           (0x0707U)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

typedef enum
{
    DSADCHANNEL0,
    DSADCHANNEL1,
    DSADCHANNEL2,
    DSADCHANNEL3
} dsad_channel_t;

typedef enum
{
    DSAD_3906HZ = 0U,
    DSAD_1953HZ
} dsad_rate_t;

typedef enum
{
    GAIN_X1 = 0U,
    GAIN_X2,
    GAIN_X4,
    GAIN_X8,
    GAIN_X16,
    GAIN_X32,
    GAIN_NONE,    
} dsad_gain_t;

typedef enum
{
    HPF_0067HZ = 0U,    /* Selection of cut off HPF 0.067 Hz */
    HPF_1214_HZ,        /* Selection of cut off HPF 1.214 Hz */
    HPF_2429_HZ,        /* Selection of cut off HPF 2.429 Hz */
    HPF_4857_HZ         /* Selection of cut off HPF 4.857 Hz */
} dsad_cutoff_t;

typedef struct
{   
    uint8_t  gain0;
    uint8_t  gain1;
    uint16_t phase0;
    uint16_t phase1;
    uint16_t phase2;
    uint16_t phase3;    
} dsad_reg_setting_t;

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_DSADC_Create(void);
void R_DSADC_Start(void);
void R_DSADC_Stop(void);
void R_DSADC_Set_OperationOn(void);
void R_DSADC_Set_OperationOff(void);
void R_DSADC_Channel0_Get_Result(uint32_t * const buffer);
void R_DSADC_Channel1_Get_Result(uint32_t * const buffer);
void R_DSADC_Channel2_Get_Result(uint32_t * const buffer);
/* Start user code for function. Do not edit comment generated here */
void R_DSADC_StartChannel0Only(void);
void R_DSADC_StartChannel1Only(void);
void R_DSADC_StartChannel2Only(void);
void R_DSADC_StartChannel3Only(void);
void R_DSADC_StopChannel(uint8_t channel_number);
void R_DSADC_StartCurrentChannels(void);
void R_DSADC_StartAllChannels(void);
void R_DSADC_BackupPhaseRegSetting(void);
void R_DSADC_RestorePhaseRegSetting(void);
void R_DSADC_Get_Result(dsad_channel_t channel, int32_t * const buffer);
MD_STATUS R_DSADC_SetHighPassFilterOn(dsad_channel_t channel);
MD_STATUS R_DSADC_SetHighPassFilterOff(dsad_channel_t channel);
MD_STATUS R_DSADC_Set_CutOffFrequency(dsad_cutoff_t frequency);
MD_STATUS R_DSADC_SetChannelGain(dsad_channel_t channel, dsad_gain_t gain);
MD_STATUS R_DSADC_AdjustPhaseDelay(dsad_channel_t channel, uint16_t step);
void R_DSADC_GetGainAndPhase(dsad_reg_setting_t *adc_gain_phase);
void R_DSADC_SetGainAndPhase(dsad_reg_setting_t adc_gain_phase);
void R_DSADC_SetGain(dsad_reg_setting_t adc_gain_phase);
void R_DSADC_StartWithoutGainAndPhase(uint16_t channel_control);
dsad_gain_t R_DSADC_GetGainEnumValue(uint8_t gain);
uint8_t R_DSADC_GetChannelGain(dsad_channel_t channel);
uint16_t R_DSADC_GetChannelPhase(dsad_channel_t channel);
void R_DSADC_ClearGainSetting(dsad_reg_setting_t * p_setting, dsad_channel_t channel);
NEAR_FUNC void r_dsadc_interrupt(void);
/* End user code. Do not edit comment generated here */
#endif
