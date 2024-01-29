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
* File Name    : r_cg_dtc.h
* Version      : Code Generator for RL78/I1C V1.01.00.02 [15 May 2017]
* Device(s)    : R5F10NPL
* Tool-Chain   : CCRL
* Description  : This file implements device driver for DTC module.
* Creation Date: 3/22/2019
***********************************************************************************************************************/
#ifndef DTC_H
#define DTC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    DTC activation enable register 4 (DTCEN4) 
*/
/* DTC activation enable 47 (DTCEN47) */
#define _00_DTC_12BIT_ACTIVATION_DISABLE             (0x00U) /* activation disabled (12BIT) */
#define _80_DTC_12BIT_ACTIVATION_ENABLE              (0x80U) /* activation enabled (12BIT) */
/* DTC activation enable 46 (DTCEN46) */
#define _00_DTC_AES_ACTIVATION_DISABLE               (0x00U) /* activation disabled (AES) */
#define _40_DTC_AES_ACTIVATION_ENABLE                (0x40U) /* activation enabled (AES) */
/* DTC activation enable 45 (DTCEN45) */
#define _00_DTC_RTCIC2_ACTIVATION_DISABLE            (0x00U) /* activation disabled (RTCIC2/INTP12) */
#define _20_DTC_RTCIC2_ACTIVATION_ENABLE             (0x20U) /* activation enabled (RTCIC2/INTP12) */
/* DTC activation enable 44 (DTCEN44) */
#define _00_DTC_RTCIC1_ACTIVATION_DISABLE            (0x00U) /* activation disabled (RTCIC1/INTP13) */
#define _10_DTC_RTCIC1_ACTIVATION_ENABLE             (0x10U) /* activation enabled (RTCIC1/INTP13) */
/* DTC activation enable 43 (DTCEN43) */
#define _00_DTC_RTCIC0_ACTIVATION_DISABLE            (0x00U) /* activation disabled (RTCIC0/INTP14) */
#define _08_DTC_RTCIC0_ACTIVATION_ENABLE             (0x08U) /* activation enabled (RTCIC0/INTP14) */
/* DTC activation enable 42 (DTCEN42) */
#define _00_DTC_INTP8_ACTIVATION_DISABLE             (0x00U) /* activation disabled (INTP8) */
#define _04_DTC_INTP8_ACTIVATION_ENABLE              (0x04U) /* activation enabled (INTP8) */
/* DTC activation enable 41 (DTCEN41) */
#define _00_DTC_INTP9_ACTIVATION_DISABLE             (0x00U) /* activation disabled (INTP9) */
#define _02_DTC_INTP9_ACTIVATION_ENABLE              (0x02U) /* activation enabled (INTP9) */
/* DTC activation enable 40 (DTCEN40) */
#define _00_DTC_UART4R_ACTIVATION_DISABLE            (0x00U) /* activation disabled (UART4R) */
#define _01_DTC_UART4R_ACTIVATION_ENABLE             (0x01U) /* activation enabled (UART4R) */

/*
    DTC activation enable register 5 (DTCEN5) 
*/
/* DTC activation enable 57 (DTCEN57) */
#define _00_DTC_UART4T_ACTIVATION_DISABLE            (0x00U) /* activation disabled (UART4T) */
#define _80_DTC_UART4T_ACTIVATION_ENABLE             (0x80U) /* activation enabled (UART4T) */
/* DTC activation enable 56 (DTCEN56) */
#define _00_DTC_UARTMG0R_ACTIVATION_DISABLE          (0x00U) /* activation disabled (UARTMG0R) */
#define _40_DTC_UARTMG0R_ACTIVATION_ENABLE           (0x40U) /* activation enabled (UARTMG0R) */
/* DTC activation enable 55 (DTCEN55) */
#define _00_DTC_UARTMG0T_ACTIVATION_DISABLE          (0x00U) /* activation disabled (UARTMG0T) */
#define _20_DTC_UARTMG0T_ACTIVATION_ENABLE           (0x20U) /* activation enabled (UARTMG0T) */
/* DTC activation enable 54 (DTCEN54) */
#define _00_DTC_UARTMG1R_ACTIVATION_DISABLE          (0x00U) /* activation disabled (UARTMG1R) */
#define _10_DTC_UARTMG1R_ACTIVATION_ENABLE           (0x10U) /* activation enabled (UARTMG1R) */
/* DTC activation enable 53 (DTCEN53) */
#define _00_DTC_UARTMG1T_ACTIVATION_DISABLE          (0x00U) /* activation disabled (UARTMG1T) */
#define _08_DTC_UARTMG1T_ACTIVATION_ENABLE           (0x08U) /* activation enabled (UARTMG1T) */
/* DTC activation enable 52 (DTCEN52) */
#define _00_DTC_8BIT20_ACTIVATION_DISABLE            (0x00U) /* activation disabled (8bit20) */
#define _04_DTC_8BIT20_ACTIVATION_ENABLE             (0x04U) /* activation enabled (8bit20) */
/* DTC activation enable 51 (DTCEN51) */
#define _00_DTC_8BIT21_ACTIVATION_DISABLE            (0x00U) /* activation disabled (8bit21) */
#define _02_DTC_8BIT21_ACTIVATION_ENABLE             (0x02U) /* activation enabled (8bit21) */
/* DTC activation enable 50 (DTCEN50) */
#define _00_DTC_8BIT30_ACTIVATION_DISABLE            (0x00U) /* activation disabled (8bit30) */
#define _01_DTC_8BIT30_ACTIVATION_ENABLE             (0x01U) /* activation enabled (8bit30) */

/*
    DTC activation enable register 5 (DTCEN6) 
*/
/* DTC activation enable 67 (DTCEN67) */
#define _00_DTC_8BIT31_ACTIVATION_DISABLE            (0x00U) /* activation disabled (8bit31) */
#define _80_DTC_8BIT31_ACTIVATION_ENABLE             (0x80U) /* activation enabled (8bit31) */
/* DTC activation enable 66 (DTCEN66) */
#define _00_DTC_TRJ0_ACTIVATION_DISABLE              (0x00U) /* activation disabled (TRJ0) */
#define _40_DTC_TRJ0_ACTIVATION_ENABLE               (0x40U) /* activation enabled (TRJ0) */
/* DTC activation enable 65 (DTCEN65) */
#define _00_DTC_TRJ1_ACTIVATION_DISABLE              (0x00U) /* activation disabled (TRJ1) */
#define _20_DTC_TRJ1_ACTIVATION_ENABLE               (0x20U) /* activation enabled (TRJ1) */

/*
    DTC control register n (DTCCRn) 
*/
/* Transfer data size selection (SZ) */
#define _00_DTC_DATA_SIZE_8BITS                      (0x00U) /* 8 bits */
#define _40_DTC_DATA_SIZE_16BITS                     (0x40U) /* 16 bits */
/* Enabling/disabling repeat mode interrupts (RPTINT) */
#define _00_DTC_REPEAT_INT_DISABLE                   (0x00U) /* interrupt generation disabled */
#define _20_DTC_REPEAT_INT_ENABLE                    (0x20U) /* interrupt generation enabled */
/* Enabling/disabling chain transfers (CHNE) */
#define _00_DTC_CHAIN_TRANSFER_DISABLE               (0x00U) /* chain transfers disabled */
#define _10_DTC_CHAIN_TRANSFER_ENABLE                (0x10U) /* chain transfers enabled */
/* Transfer destination address control (DAMOD) */
#define _00_DTC_DEST_ADDR_FIXED                      (0x00U) /* fixed */
#define _08_DTC_DEST_ADDR_INCREMENTED                (0x08U) /* incremented */
/* Transfer source address control (SAMOD) */
#define _00_DTC_SOURCE_ADDR_FIXED                    (0x00U) /* fixed */
#define _04_DTC_SOURCE_ADDR_INCREMENTED              (0x04U) /* incremented */
/* Repeat area selection (RPTSEL) */
#define _00_DTC_REPEAT_AREA_DEST                     (0x00U) /* transfer destination is the repeat area */
#define _02_DTC_REPEAT_AREA_SOURCE                   (0x02U) /* transfer source is the repeat area */
/* Transfer mode selection (MODE) */
#define _00_DTC_TRANSFER_MODE_NORMAL                 (0x00U) /* normal mode */
#define _01_DTC_TRANSFER_MODE_REPEAT                 (0x01U) /* repeat mode */

/*
    DTC activation enable register 0 (DTCEN0) 
*/
/* DTC activation enable 06 (DTCEN06) */
#define _00_DTC_INTP0_ACTIVATION_DISABLE             (0x00U) /* activation disabled  (INTP0) */
#define _40_DTC_INTP0_ACTIVATION_ENABLE              (0x40U) /* activation enabled  (INTP0) */
/* DTC activation enable 05 (DTCEN05) */
#define _00_DTC_INTP1_ACTIVATION_DISABLE             (0x00U) /* activation disabled  (INTP1) */
#define _20_DTC_INTP1_ACTIVATION_ENABLE              (0x20U) /* activation enabled  (INTP1) */
/* DTC activation enable 04 (DTCEN04) */
#define _00_DTC_INTP2_ACTIVATION_DISABLE             (0x00U) /* activation disabled  (INTP2) */
#define _10_DTC_INTP2_ACTIVATION_ENABLE              (0x10U) /* activation enabled  (INTP2) */
/* DTC activation enable 03 (DTCEN03) */
#define _00_DTC_INTP3_ACTIVATION_DISABLE             (0x00U) /* activation disabled  (INTP3) */
#define _08_DTC_INTP3_ACTIVATION_ENABLE              (0x08U) /* activation enabled  (INTP3) */
/* DTC activation enable 02 (DTCEN02) */
#define _00_DTC_INTP4_ACTIVATION_DISABLE             (0x00U) /* activation disabled  (INTP4) */
#define _04_DTC_INTP4_ACTIVATION_ENABLE              (0x04U) /* activation enabled  (INTP4) */
/* DTC activation enable 01 (DTCEN01) */
#define _00_DTC_INTP5_ACTIVATION_DISABLE             (0x00U) /* activation disabled  (INTP5) */
#define _02_DTC_INTP5_ACTIVATION_ENABLE              (0x02U) /* activation enabled  (INTP5) */
/* DTC activation enable 00 (DTCEN00) */
#define _00_DTC_INTP6_ACTIVATION_DISABLE             (0x00U) /* activation disabled  (INTP6) */
#define _01_DTC_INTP6_ACTIVATION_ENABLE              (0x01U) /* activation enabled  (INTP6) */

/*
    DTC activation enable register 1 (DTCEN1) 
*/
/* DTC activation enable 17 (DTCEN17) */
#define _00_DTC_INTP7_ACTIVATION_DISABLE             (0x00U) /* activation disabled  (INTP7) */
#define _80_DTC_INTP7_ACTIVATION_ENABLE              (0x80U) /* activation enabled  (INTP7) */
/* DTC activation enable 16 (DTCEN16) */
#define _00_DTC_KEY_ACTIVATION_DISABLE               (0x00U) /* activation disabled  (KEY) */
#define _40_DTC_KEY_ACTIVATION_ENABLE                (0x40U) /* activation enabled  (KEY) */
/* DTC activation enable 15 (DTCEN15) */
#define _00_DTC_AD_ACTIVATION_DISABLE                (0x00U) /* activation disabled  (24bitAD) */
#define _20_DTC_AD_ACTIVATION_ENABLE                 (0x20U) /* activation enabled  (24bitAD) */
/* DTC activation enable 14 (DTCEN14) */
#define _00_DTC_SARAD_ACTIVATION_DISABLE             (0x00U) /* activation disabled  (SAR-type A/D) */
#define _10_DTC_SARAD_ACTIVATION_ENABLE              (0x10U) /* activation enabled  (SAR-type A/D) */
/* DTC activation enable 13 (DTCEN13) */
#define _00_DTC_UART0R_ACTIVATION_DISABLE            (0x00U) /* activation disabled  (UART0R) */
#define _08_DTC_UART0R_ACTIVATION_ENABLE             (0x08U) /* activation enabled  (UART0R) */
/* DTC activation enable 12 (DTCEN12) */
#define _00_DTC_UART0T_ACTIVATION_DISABLE            (0x00U) /* activation disabled  (UART0T) */
#define _04_DTC_UART0T_ACTIVATION_ENABLE             (0x04U) /* activation enabled  (UART0T) */
/* DTC activation enable 11 (DTCEN11) */
#define _00_DTC_UART1R_ACTIVATION_DISABLE            (0x00U) /* activation disabled  (UART1R) */
#define _02_DTC_UART1R_ACTIVATION_ENABLE             (0x02U) /* activation enabled  (UART1R) */
/* DTC activation enable 10 (DTCEN10) */
#define _00_DTC_UART1T_ACTIVATION_DISABLE            (0x00U) /* activation disabled  (UART1T) */
#define _01_DTC_UART1T_ACTIVATION_ENABLE             (0x01U) /* activation enabled  (UART1T) */

/*
    DTC activation enable register 2 (DTCEN2) 
*/
/* DTC activation enable 27 (DTCEN27) */
#define _00_DTC_UART2R_ACTIVATION_DISABLE            (0x00U) /* activation disabled  (UART2R) */
#define _80_DTC_UART2R_ACTIVATION_ENABLE             (0x80U) /* activation enabled  (UART2R) */
/* DTC activation enable 26 (DTCEN26) */
#define _00_DTC_UART2T_ACTIVATION_DISABLE            (0x00U) /* activation disabled  (UART2T) */
#define _40_DTC_UART2T_ACTIVATION_ENABLE             (0x40U) /* activation enabled  (UART2T) */
/* DTC activation enable 25 (DTCEN25) */
#define _00_DTC_UART3R_ACTIVATION_DISABLE            (0x00U) /* activation disabled  (UART3R) */
#define _20_DTC_UART3R_ACTIVATION_ENABLE             (0x20U) /* activation enabled  (UART3R) */
/* DTC activation enable 24 (DTCEN24) */
#define _00_DTC_UART3T_ACTIVATION_DISABLE            (0x00U) /* activation disabled  (UART3T) */
#define _10_DTC_UART3T_ACTIVATION_ENABLE             (0x10U) /* activation enabled  (UART3T) */
/* DTC activation enable 23 (DTCEN23) */
#define _00_DTC_TAU00_ACTIVATION_DISABLE             (0x00U) /* activation disabled  (TAU00) */
#define _08_DTC_TAU00_ACTIVATION_ENABLE              (0x08U) /* activation enabled  (TAU00) */
/* DTC activation enable 22 (DTCEN22) */
#define _00_DTC_TAU01_ACTIVATION_DISABLE             (0x00U) /* activation disabled  (TAU01) */
#define _04_DTC_TAU01_ACTIVATION_ENABLE              (0x04U) /* activation enabled  (TAU01) */
/* DTC activation enable 21 (DTCEN21) */
#define _00_DTC_TAU02_ACTIVATION_DISABLE             (0x00U) /* activation disabled  (TAU02) */
#define _02_DTC_TAU02_ACTIVATION_ENABLE              (0x02U) /* activation enabled  (TAU02) */
/* DTC activation enable 20 (DTCEN20) */
#define _00_DTC_TAU03_ACTIVATION_DISABLE             (0x00U) /* activation disabled  (TAU03) */
#define _01_DTC_TAU03_ACTIVATION_ENABLE              (0x01U) /* activation enabled  (TAU03) */

/*
    DTC activation enable register 3 (DTCEN3) 
*/
/* DTC activation enable 37 (DTCEN37) */
#define _00_DTC_TAU04_ACTIVATION_DISABLE             (0x00U) /* activation disabled  (TAU04) */
#define _80_DTC_TAU04_ACTIVATION_ENABLE              (0x80U) /* activation enabled  (TAU04) */
/* DTC activation enable 36 (DTCEN36) */
#define _00_DTC_TAU05_ACTIVATION_DISABLE             (0x00U) /* activation disabled  (TAU05) */
#define _40_DTC_TAU05_ACTIVATION_ENABLE              (0x40U) /* activation enabled  (TAU05) */
/* DTC activation enable 35 (DTCEN35) */
#define _00_DTC_TAU06_ACTIVATION_DISABLE             (0x00U) /* activation disabled  (TAU06) */
#define _20_DTC_TAU06_ACTIVATION_ENABLE              (0x20U) /* activation enabled  (TAU06) */
/* DTC activation enable 34 (DTCEN34) */
#define _00_DTC_TAU07_ACTIVATION_DISABLE             (0x00U) /* activation disabled  (TAU07) */
#define _10_DTC_TAU07_ACTIVATION_ENABLE              (0x10U) /* activation enabled  (TAU07) */
/* DTC activation enable 33 (DTCEN33) */
#define _00_DTC_8BIT00_ACTIVATION_DISABLE            (0x00U) /* activation disabled  (8bit00) */
#define _08_DTC_8BIT00_ACTIVATION_ENABLE             (0x08U) /* activation enabled  (8bit00) */
/* DTC activation enable 32 (DTCEN32) */
#define _00_DTC_8BIT01_ACTIVATION_DISABLE            (0x00U) /* activation disabled  (8bit01) */
#define _04_DTC_8BIT01_ACTIVATION_ENABLE             (0x04U) /* activation enabled  (8bit01) */
/* DTC activation enable 31 (DTCEN31) */
#define _00_DTC_8BIT10_ACTIVATION_DISABLE            (0x00U) /* activation disabled  (8bit10) */
#define _02_DTC_8BIT10_ACTIVATION_ENABLE             (0x02U) /* activation enabled  (8bit10) */
/* DTC activation enable 30 (DTCEN30) */
#define _00_DTC_8BIT11_ACTIVATION_DISABLE            (0x00U) /* activation disabled  (8bit11) */
#define _01_DTC_8BIT11_ACTIVATION_ENABLE             (0x01U) /* activation enabled  (8bit11) */


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _03_DTCD0_TRANSFER_BLOCKSIZE               (0x03U) /* transfer block size */
#define _02_DTCD0_TRANSFER_BYTE                    (0x02U) /* number of transfers */
#define _0000_DTCD0_SRC_ADDRESS                    (0x0000U) 
#define _0000_DTCD0_DEST_ADDRESS                   (0x0000U) 

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct
{
    uint8_t  dtccr;
    uint8_t  dtbls;
    uint8_t  dtcct;
    uint8_t  dtrld;
    uint16_t dtsar;
    uint16_t dtdar;
}st_dtc_data;

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_DTC_Create(void);
void R_DTCD0_Start(void);
void R_DTCD0_Stop(void);
void R_DTC_Create_UserInit(void);
/* Start user code for function. Do not edit comment generated here */
extern volatile uint16_t __near g_adc_data[6];
extern volatile uint8_t dtc_vectortable[51U];
extern volatile st_dtc_data __near dtc_controldata_0;

#define DTC_USER_ADC_TRANSFER_RELOAD()      {\
                                                dtc_controldata_0.dtcct = _02_DTCD0_TRANSFER_BYTE;  \
                                                dtc_controldata_0.dtdar = (uint16_t)&g_adc_data[0]; \
                                            }
/* End user code. Do not edit comment generated here */
#endif
