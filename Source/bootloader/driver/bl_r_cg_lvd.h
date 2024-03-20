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
* Copyright (C) 2015, 2016 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : bl_r_cg_lvd.h
* Version      : 
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* Description  : This file implements device driver for LVD module.
* Creation Date: 
***********************************************************************************************************************/
#ifndef LVD_H
#define LVD_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Voltage detection register (LVIM)
*/
/* LVIS register rewrite enable/disable control (LVISEN) */
#define _00_LVD_REWRITE_LVIS_DISABLE    (0x00U) /* disabling rewriting */
#define _80_LVD_REWRITE_LVIS_ENABLE     (0x80U) /* enabling rewriting */
/* LVD output mask status flag (LVIOMSK) */
#define _00_LVD_MASK_INVALIDITY         (0x00U) /* mask is invalid */
#define _02_LVD_MASK_VALIDITY           (0x02U) /* mask is valid */
/* Voltage detection flag (LVIF) */
#define _00_LVD_FLAG_OVER               (0x00U) /* supply voltage (VDD) >= detection voltage (VLVI), or when LVD operation is disabled */
#define _01_LVD_FLAG_LESS               (0x01U) /* supply voltage (VDD) < detection voltage (VLVI) */

/*
    Voltage detection level register (LVIS)
*/
/* Operation mode of voltage detection (LVIMD) */
#define _00_LVD_MODE_INT                (0x00U) /* interrupt mode */
#define _80_LVD_MODE_RESET              (0x80U) /* reset mode */
/* LVD detection level (LVILV) */
#define _00_LVD_LEVEL_HIGH              (0x00U) /* high-voltage detection level (VLVIH) */
#define _01_LVD_LEVEL_LOW               (0x01U) /* low-voltage detection level (VLVIL) */

/*
    Voltage detection control register for VDD pin (LVDVDD) 
*/
/* VDD pin voltage detection enable/disable (LVDVDDEN) */
#define _00_LVD_VDD_DELECT_DISABLE                  (0x00U) /* disables detection */
#define _80_LVD_VDD_DELECT_ENABLE                   (0x80U) /* enables detection */
/* VDD pin voltage detection flag (LVDVDDF) */
#define _00_LVD_VDD_GREATER_LVDVDD                  (0x00U) /* VDD > VLVDVDD, or detection is off */
#define _40_LVD_VDD_NOTGREATER_LVDVDD               (0x40U) /* VDD < VLVDVDD */
/* Detection voltage (VLVDVDD) (LVDVDD2,LVDVDD1,LVDVDD0) */
#define _00_LVD_VDD_VOLTAGE_247                     (0x00U) /* 2.47 V */
#define _01_LVD_VDD_VOLTAGE_268                     (0x01U) /* 2.68 V */
#define _02_LVD_VDD_VOLTAGE_288                     (0x02U) /* 2.88 V */
#define _03_LVD_VDD_VOLTAGE_309                     (0x03U) /* 3.09 V */
#define _04_LVD_VDD_VOLTAGE_340                     (0x04U) /* 3.40 V */
#define _05_LVD_VDD_VOLTAGE_371                     (0x05U) /* 3.71 V */

/*
    Voltage detection control register for VBAT pin (LVDVBAT) 
*/
/* VBAT pin voltage detection enable/disable (LVDVBATEN) */
#define _00_LVD_VBAT_DELECT_DISABLE                 (0x00U) /* disables detection */
#define _80_LVD_VBAT_DELECT_ENABLE                  (0x80U) /* enables detection */
/* VBAT pin voltage detection flag (LVDVBATF) */
#define _00_LVD_VBAT_GREATER_LVDVBAT                (0x00U) /* VBAT > VLVDVBAT, or detection is off */
#define _40_LVD_VBAT_NOTGREATER_LVDVBAT             (0x40U) /* VBAT < VLVDVBAT  */
/* Detection voltage (VLVDVBAT) (LVDVBAT2,LVDVBAT1,LVDVBAT0) */
#define _00_LVD_VBAT_VOLTAGE_206                    (0x00U) /* 2.06 V */
#define _01_LVD_VBAT_VOLTAGE_216                    (0x01U) /* 2.16 V */
#define _02_LVD_VBAT_VOLTAGE_227                    (0x02U) /* 2.27 V */
#define _03_LVD_VBAT_VOLTAGE_237                    (0x03U) /* 2.37 V */
#define _04_LVD_VBAT_VOLTAGE_247                    (0x04U) /* 2.47 V */
#define _05_LVD_VBAT_VOLTAGE_257                    (0x05U) /* 2.57 V */
#define _06_LVD_VBAT_VOLTAGE_268                    (0x06U) /* 2.68 V */

/*
    Voltage detection control register for VRTC pin (LVDVRTC) 
*/
/* VRTC pin voltage detection enable/disable (LVDVRTCEN) */
#define _00_LVD_VRTC_DELECT_DISABLE                 (0x00U) /* disables detection */
#define _80_LVD_VRTC_DELECT_ENABLE                  (0x80U) /* enables detection */
/* VRTC pin voltage detection flag (LVDVRTCF) */
#define _00_LVD_VRTC_GREATER_LVDVRTC                (0x00U) /* VRTC > VLVDVRTC, or detection is off */
#define _40_LVD_VRTC_NOTGREATER_LVDVRTC             (0x40U) /* VRTC < VLVDVRTC */
/* Detection voltage (VLVDVRTC) (LVDVRTC1,LVDVRTC0) */
#define _00_LVD_VRTC_VOLTAGE_216                    (0x00U) /* 2.16 V */
#define _01_LVD_VBAT_VOLTAGE_237                    (0x01U) /* 2.37 V */
#define _02_LVD_VBAT_VOLTAGE_257                    (0x02U) /* 2.57 V */
#define _03_LVD_VBAT_VOLTAGE_278                    (0x03U) /* 2.78 V */

/*
    Voltage detection control register for EXLVD pin (LVDEXLVD) 
*/
/* EXLVD pin voltage detection enable/disable (LVDEXLVDEN) */
#define _00_LVD_EXLVD_DELECT_DISABLE                (0x00U) /* disables detection */
#define _80_LVD_EXLVD_DELECT_ENABLE                 (0x80U) /* enables detection */
/* EXLVD pin voltage detection flag (LVDEXLVDF) */
#define _00_LVD_EXLVD_GREATER_VLVDEXLVD             (0x00U) /* EXLVD > VLVDEXLVD, or detection is off */
#define _40_LVD_EXLVD_NOTGREATER_VLVDEXLVD          (0x40U) /* EXLVD < VLVDEXLVD */


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_LVD_Create(void);
void R_LVD_Start_VDD(void);
void R_LVD_Stop_VDD(void);
void r_lvd_vddinterrupt(void);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
