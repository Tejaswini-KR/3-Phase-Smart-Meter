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
* File Name    : r_cg_elc.h
* Version      : Code Generator for RL78/I1C V1.01.00.02 [15 May 2017]
* Device(s)    : R5F10NPL
* Tool-Chain   : CCRL
* Description  : This file implements device driver for ELC module.
* Creation Date: 3/22/2019
***********************************************************************************************************************/

#ifndef ELC_H
#define ELC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Event Output Destination Selection Register n (ELSELRn)
*/
/* Event link selection (ELSELn2 - ELSELn0) */
#define _00_ELC_EVENT_LINK_OFF      (0x00U) /* prohibit event link */
#define _01_ELC_EVENT_LINK_AD       (0x01U) /* link destination AD */
#define _02_ELC_EVENT_LINK_TAU00    (0x02U) /* link destination TAU00 */
#define _03_ELC_EVENT_LINK_TAU01    (0x03U) /* link destination TAU01 */
#define _04_ELC_EVENT_LINK_TAU05    (0x04U) /* link destination TAU05 */
#define _05_ELC_EVENT_LINK_TAU07    (0x05U) /* link destination TAU07 */
#define _06_ELC_EVENT_LINK_TRJ0     (0x06U) /* link destination TRJ0 */
#define _07_ELC_EVENT_LINK_TRJ1     (0x07U) /* link destination TRJ1 */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define ELC_TRIGGER_SRC_COUNT       (30U)
#define ELC_TRIGGER_DEST_COUNT      (7U)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum tagElcSrc
{
    ELC_TRIGGER_SRC_INTP0,			/* External interrupt edge detection 0 */
    ELC_TRIGGER_SRC_INTP1,			/* External interrupt edge detection 1 */
    ELC_TRIGGER_SRC_INTP2,			/* External interrupt edge detection 2 */
    ELC_TRIGGER_SRC_INTP3,			/* External interrupt edge detection 3 */
    ELC_TRIGGER_SRC_INTP4,			/* External interrupt edge detection 4 */
    ELC_TRIGGER_SRC_INTP5,			/* External interrupt edge detection 5 */
    ELC_TRIGGER_SRC_INTP6,			/* External interrupt edge detection 6 */
    ELC_TRIGGER_SRC_INTP7,			/* External interrupt edge detection 7 */
    ELC_TRIGGER_SRC_INTKR,			/* Key return signal detection */
    ELC_TRIGGER_SRC_INTIT,			/* 12-bit interval timer count completion */
    ELC_TRIGGER_SRC_INTIT00,		/* 8-bit interval timer channel 00 count completion */
    ELC_TRIGGER_SRC_INTIT10,		/* 8-bit interval timer channel 10 count completion */
    ELC_TRIGGER_SRC_INTRTCPRD,		/* RTC fixed periodic cycle signal */
    ELC_TRIGGER_SRC_INTTM00,		/* TAU0 channel 0 count end / capture end */
    ELC_TRIGGER_SRC_INTTM01,		/* TAU0 channel 1 count end / capture end */
    ELC_TRIGGER_SRC_INTTM02,		/* TAU0 channel 2 count end / capture end */
    ELC_TRIGGER_SRC_INTTM03,		/* TAU0 channel 3 count end / capture end */
    ELC_TRIGGER_SRC_INTTM05,		/* TAU0 channel 5 count end / capture end */
    ELC_TRIGGER_SRC_INTTM07,		/* TAU0 channel 7 count end / capture end */
    ELC_TRIGGER_SRC_INTDSAD_MAIN,	/* Delta-sigma analog to digital translation end (main signal) */
    ELC_TRIGGER_SRC_INTDSAD_SPLIT,	/* Delta-sigma analog to digital translation end (split signal) */
    ELC_TRIGGER_SRC_INTP8,			/* External interrupt edge detection 8 */
    ELC_TRIGGER_SRC_INTP9,			/* External interrupt edge detection 9 */
    ELC_TRIGGER_SRC_INTP12,			/* External interrupt edge detection 12 */
    ELC_TRIGGER_SRC_INTP13,			/* External interrupt edge detection 13 */
    ELC_TRIGGER_SRC_INTP14,			/* External interrupt edge detection 14 */
    ELC_TRIGGER_SRC_INTIT20,		/* 8-bit interval timer channel 20 count completion */
    ELC_TRIGGER_SRC_INTIT30,		/* 8-bit interval timer channel 30 count completion */
    ELC_TRIGGER_SRC_INTTRJ0,		/* Timer RJ0 underflow */
    ELC_TRIGGER_SRC_INTTRJ1,		/* Timer RJ1 underflow */
} elc_src_t;

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_ELC_Create(void);
void R_ELC_Stop(uint32_t src);
void R_ELC_Create_UserInit(void);

/* Start user code for function. Do not edit comment generated here */
#define R_ELC_DIRECT_SET(src, dest)             (*(&ELSELR00 + src) = dest)
#define R_ELC_DIRECT_CLEAR(src)                 (*(&ELSELR00 + src) = _00_ELC_EVENT_LINK_OFF)
/* End user code. Do not edit comment generated here */
#endif
