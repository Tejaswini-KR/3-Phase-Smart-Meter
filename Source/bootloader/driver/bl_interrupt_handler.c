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
* File Name    : bl_interrupt_handler.c
* Version      : 1.00
* Device(s)    : RL78
* Tool-Chain   : 
* Description  : Main interrupt handler, from here the RAM vector will be called accordingly
* Creation Date: 
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "bl_header.h"

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
#ifdef __CCRL__

#pragma section text ISRTx

#pragma interrupt INTWDTI_Interrupt(vect=INTWDTI)
static void INTWDTI_Interrupt(void)
{
    RAM_ISR_Table[INTWDTI]();
}

#pragma interrupt INTLVI_Interrupt(vect=INTLVI)
static void INTLVI_Interrupt(void)
{
    RAM_ISR_Table[INTLVI]();
}

#pragma interrupt INTP0_Interrupt(vect=INTP0)
static void INTP0_Interrupt(void)
{
    RAM_ISR_Table[INTP0]();
}

#pragma interrupt INTP1_Interrupt(vect=INTP1)
static void INTP1_Interrupt(void)
{
    RAM_ISR_Table[INTP1]();
}

#pragma interrupt INTP2_Interrupt(vect=INTP2)
static void INTP2_Interrupt(void)
{
    RAM_ISR_Table[INTP2]();
}

#pragma interrupt INTP3_Interrupt(vect=INTP3)
static void INTP3_Interrupt(void)
{
    RAM_ISR_Table[INTP3]();
}

#pragma interrupt INTP4_Interrupt(vect=INTP4)
static void INTP4_Interrupt(void)
{
    RAM_ISR_Table[INTP4]();
}

#pragma interrupt INTP5_Interrupt(vect=INTP5)
static void INTP5_Interrupt(void)
{
    RAM_ISR_Table[INTP5]();
}

#pragma interrupt INTST2_Interrupt(vect=INTST2)
static void INTST2_Interrupt(void)
{
    RAM_ISR_Table[INTST2]();
}

#pragma interrupt INTSR2_Interrupt(vect=INTSR2)
static void INTSR2_Interrupt(void)
{
    RAM_ISR_Table[INTSR2]();
}

#pragma interrupt INTSRE2_Interrupt(vect=INTSRE2)
static void INTSRE2_Interrupt(void)
{
    RAM_ISR_Table[INTSRE2]();
}

#pragma interrupt INTCR_Interrupt(vect=INTCR)
static void INTCR_Interrupt(void)
{
    RAM_ISR_Table[INTCR]();
}

#pragma interrupt INTCSI00_Interrupt(vect=INTCSI00)
static void INTCSI00_Interrupt(void)
{
    RAM_ISR_Table[INTCSI00]();
}

#pragma interrupt INTIICA0_Interrupt(vect=INTIICA0)
static void INTIICA0_Interrupt(void)
{
    RAM_ISR_Table[INTIICA0]();
}

#pragma interrupt INTSR0_Interrupt(vect=INTSR0)
static void INTSR0_Interrupt(void)
{
    RAM_ISR_Table[INTSR0]();
}

#pragma interrupt INTSRE0_Interrupt(vect=INTSRE0)
static void INTSRE0_Interrupt(void)
{
    RAM_ISR_Table[INTSRE0]();
}

#pragma interrupt INTCSI10_Interrupt(vect=INTCSI10)
static void INTCSI10_Interrupt(void)
{
    RAM_ISR_Table[INTCSI10]();
}

#pragma interrupt INTSR1_Interrupt(vect=INTSR1)
static void INTSR1_Interrupt(void)
{
    RAM_ISR_Table[INTSR1]();
}

#pragma interrupt INTSRE1_Interrupt(vect=INTSRE1)
static void INTSRE1_Interrupt(void)
{
    RAM_ISR_Table[INTSRE1]();
}

#pragma interrupt INTTM00_Interrupt(vect=INTTM00)
static void INTTM00_Interrupt(void)
{
    RAM_ISR_Table[INTTM00]();
}

#pragma interrupt INTRTCALM0_Interrupt(vect=INTRTCALM0)
static void INTRTCALM0_Interrupt(void)
{
    RAM_ISR_Table[INTRTCALM0]();
}

#pragma interrupt INTFM_Interrupt(vect=INTFM)
static void INTFM_Interrupt(void)
{
    RAM_ISR_Table[INTFM]();
}

#pragma interrupt INTTM01_Interrupt(vect=INTTM01)
static void INTTM01_Interrupt(void)
{
    RAM_ISR_Table[INTTM01]();
}

#pragma interrupt INTTM02_Interrupt(vect=INTTM02, bank=RB1)
static void INTTM02_Interrupt(void)
{
    RAM_ISR_Table[INTTM02]();
}

#pragma interrupt INTTM03_Interrupt(vect=INTTM03)
static void INTTM03_Interrupt(void)
{
    RAM_ISR_Table[INTTM03]();
}

#pragma interrupt INTAD_Interrupt(vect=INTAD)
static void INTAD_Interrupt(void)
{
    RAM_ISR_Table[INTAD]();
}

#pragma interrupt INTRTCPRD_Interrupt(vect=INTRTCPRD)
static void INTRTCPRD_Interrupt(void)
{
    RAM_ISR_Table[INTRTCPRD]();
}

#pragma interrupt INTIT_Interrupt(vect=INTIT)
static void INTIT_Interrupt(void)
{
    RAM_ISR_Table[INTIT]();
}

#pragma interrupt INTRTCALM1_Interrupt(vect=INTRTCALM1)
static void INTRTCALM1_Interrupt(void)
{
    RAM_ISR_Table[INTRTCALM1]();
}

#pragma interrupt INTCSI30_Interrupt(vect=INTCSI30)
static void INTCSI30_Interrupt(void)
{
    RAM_ISR_Table[INTCSI30]();
}

#pragma interrupt INTSR3_Interrupt(vect=INTSR3)
static void INTSR3_Interrupt(void)
{
    RAM_ISR_Table[INTSR3]();
}

#pragma interrupt INTDSAD_Interrupt(vect=INTDSAD, bank=RB2)
static void INTDSAD_Interrupt(void)
{
    RAM_ISR_Table[INTDSAD]();
}

#pragma interrupt INTTM04_Interrupt(vect=INTTM04)
static void INTTM04_Interrupt(void)
{
    RAM_ISR_Table[INTTM04]();
}

#pragma interrupt INTTM05_Interrupt(vect=INTTM05)
static void INTTM05_Interrupt(void)
{
    RAM_ISR_Table[INTTM05]();
}

#pragma interrupt INTP6_Interrupt(vect=INTP6)
static void INTP6_Interrupt(void)
{
    RAM_ISR_Table[INTP6]();
}

#pragma interrupt INTP7_Interrupt(vect=INTP7)
static void INTP7_Interrupt(void)
{
    RAM_ISR_Table[INTP7]();
}

#pragma interrupt INTRTCIC0_Interrupt(vect=INTRTCIC0)
static void INTRTCIC0_Interrupt(void)
{
    RAM_ISR_Table[INTRTCIC0]();
}

#pragma interrupt INTRTCIC1_Interrupt(vect=INTRTCIC1)
static void INTRTCIC1_Interrupt(void)
{
    RAM_ISR_Table[INTRTCIC1]();
}

#pragma interrupt INTRTCIC2_Interrupt(vect=INTRTCIC2)
static void INTRTCIC2_Interrupt(void)
{
    RAM_ISR_Table[INTRTCIC2]();
}

#pragma interrupt INTTM06_Interrupt(vect=INTTM06)
static void INTTM06_Interrupt(void)
{
    RAM_ISR_Table[INTTM06]();
}

#pragma interrupt INTTM07_Interrupt(vect=INTTM07)
static void INTTM07_Interrupt(void)
{
    RAM_ISR_Table[INTTM07]();
}

#pragma interrupt INTIT00_Interrupt(vect=INTIT00)
static void INTIT00_Interrupt(void)
{
    RAM_ISR_Table[INTIT00]();
}

#pragma interrupt INTIT01_Interrupt(vect=INTIT01)
static void INTIT01_Interrupt(void)
{
    RAM_ISR_Table[INTIT01]();
}

#pragma interrupt INTSRE3_Interrupt(vect=INTSRE3)
static void INTSRE3_Interrupt(void)
{
    RAM_ISR_Table[INTSRE3]();
}

#pragma interrupt INTMACLOF_Interrupt(vect=INTMACLOF)
static void INTMACLOF_Interrupt(void)
{
    RAM_ISR_Table[INTMACLOF]();
}

#pragma interrupt INTOSDC_Interrupt(vect=INTOSDC)
static void INTOSDC_Interrupt(void)
{
    RAM_ISR_Table[INTOSDC]();
}

#pragma interrupt INTFL_Interrupt(vect=INTFL)
static void INTFL_Interrupt(void)
{
    RAM_ISR_Table[INTFL]();
}

#pragma interrupt INTP8_Interrupt(vect=INTP8)
static void INTP8_Interrupt(void)
{
    RAM_ISR_Table[INTP8]();
}

#pragma interrupt INTP9_Interrupt(vect=INTP9)
static void INTP9_Interrupt(void)
{
    RAM_ISR_Table[INTP9]();
}

#pragma interrupt INTIT10_Interrupt(vect=INTIT10)
static void INTIT10_Interrupt(void)
{
    RAM_ISR_Table[INTIT10]();
}

#pragma interrupt INTIT11_Interrupt(vect=INTIT11)
static void INTIT11_Interrupt(void)
{
    RAM_ISR_Table[INTIT11]();
}

#pragma interrupt INTLVDVDD_Interrupt(vect=INTLVDVDD)
static void INTLVDVDD_Interrupt(void)
{
    RAM_ISR_Table[INTLVDVDD]();
}

#pragma interrupt INTLVDVBAT_Interrupt(vect=INTLVDVBAT)
static void INTLVDVBAT_Interrupt(void)
{
    RAM_ISR_Table[INTLVDVBAT]();
}

#pragma interrupt INTLVDVRTC_Interrupt(vect=INTLVDVRTC)
static void INTLVDVRTC_Interrupt(void)
{
    RAM_ISR_Table[INTLVDVRTC]();
}

#pragma interrupt INTLVDEXLVD_Interrupt(vect=INTLVDEXLVD)
static void INTLVDEXLVD_Interrupt(void)
{
    RAM_ISR_Table[INTLVDEXLVD]();
}

#pragma interrupt INTST4_Interrupt(vect=INTST4)
static void INTST4_Interrupt(void)
{
    RAM_ISR_Table[INTST4]();
}

#pragma interrupt INTSR4_Interrupt(vect=INTSR4)
static void INTSR4_Interrupt(void)
{
    RAM_ISR_Table[INTSR4]();
}

#pragma interrupt INTSRE4_Interrupt(vect=INTSRE4)
static void INTSRE4_Interrupt(void)
{
    RAM_ISR_Table[INTSRE4]();
}

#pragma interrupt INTDSADDEC_Interrupt(vect=INTDSADDEC)
static void INTDSADDEC_Interrupt(void)
{
    RAM_ISR_Table[INTDSADDEC]();
}

#pragma interrupt INTTRJ1_Interrupt(vect=INTTRJ1)
static void INTTRJ1_Interrupt(void)
{
    RAM_ISR_Table[INTTRJ1]();
}

#endif//__CCRL__

#ifdef __ICCRL78__

#pragma vector = INTWDTI_vect
__interrupt static void INTWDTI_Interrupt(void)
{
    RAM_ISR_Table[INTWDTI_vect]();
}

#pragma vector = INTLVI_vect
__interrupt static void INTLVI_Interrupt(void)
{
    RAM_ISR_Table[INTLVI_vect]();
}

#pragma vector = INTP0_vect
__interrupt static void INTP0_Interrupt(void)
{
    RAM_ISR_Table[INTP0_vect]();
}

#pragma vector = INTP1_vect
__interrupt static void INTP1_Interrupt(void)
{
    RAM_ISR_Table[INTP1_vect]();
}

#pragma vector = INTP2_vect
__interrupt static void INTP2_Interrupt(void)
{
    RAM_ISR_Table[INTP2_vect]();
}

#pragma vector = INTP3_vect
__interrupt static void INTP3_Interrupt(void)
{
    RAM_ISR_Table[INTP3_vect]();
}

#pragma vector = INTP4_vect
__interrupt static void INTP4_Interrupt(void)
{
    RAM_ISR_Table[INTP4_vect]();
}

#pragma vector = INTP5_vect
__interrupt static void INTP5_Interrupt(void)
{
    RAM_ISR_Table[INTP5_vect]();
}

#pragma vector = INTST2_vect
__interrupt static void INTST2_Interrupt(void)
{
    RAM_ISR_Table[INTST2_vect]();
}

#pragma vector = INTSR2_vect
__interrupt static void INTSR2_Interrupt(void)
{
    RAM_ISR_Table[INTSR2_vect]();
}

#pragma vector = INTSRE2_vect
__interrupt static void INTSRE2_Interrupt(void)
{
    RAM_ISR_Table[INTSRE2_vect]();
}

#pragma vector = INTCR_vect
__interrupt static void INTCR_Interrupt(void)
{
    RAM_ISR_Table[INTCR_vect]();
}

#pragma vector = INTCSI00_vect
__interrupt static void INTCSI00_Interrupt(void)
{
    RAM_ISR_Table[INTCSI00_vect]();
}

#pragma vector = INTIICA0_vect
__interrupt static void INTIICA0_Interrupt(void)
{
    RAM_ISR_Table[INTIICA0_vect]();
}

#pragma vector = INTSR0_vect
__interrupt static void INTSR0_Interrupt(void)
{
    RAM_ISR_Table[INTSR0_vect]();
}

#pragma vector = INTSRE0_vect
__interrupt static void INTSRE0_Interrupt(void)
{
    RAM_ISR_Table[INTSRE0_vect]();
}

#pragma vector = INTCSI10_vect
__interrupt static void INTCSI10_Interrupt(void)
{
    RAM_ISR_Table[INTCSI10_vect]();
}

#pragma vector = INTSR1_vect
__interrupt static void INTSR1_Interrupt(void)
{
    RAM_ISR_Table[INTSR1_vect]();
}

#pragma vector = INTSRE1_vect
__interrupt static void INTSRE1_Interrupt(void)
{
    RAM_ISR_Table[INTSRE1_vect]();
}

#pragma vector = INTTM00_vect
__interrupt static void INTTM00_Interrupt(void)
{
    RAM_ISR_Table[INTTM00_vect]();
}

#pragma vector = INTRTCALM0_vect
__interrupt static void INTRTCALM0_Interrupt(void)
{
    RAM_ISR_Table[INTRTCALM0_vect]();
}

#pragma vector = INTFM_vect
__interrupt static void INTFM_Interrupt(void)
{
    RAM_ISR_Table[INTFM_vect]();
}

#pragma vector =  INTTM01_vect
__interrupt static void INTTM01_Interrupt(void)
{
    RAM_ISR_Table[INTTM01_vect]();
}

#pragma vector = INTTM02_vect
#pragma bank = 1
__interrupt static void INTTM02_Interrupt(void)
{
    RAM_ISR_Table[INTTM02_vect]();
}

#pragma vector = INTTM03_vect
__interrupt static void INTTM03_Interrupt(void)
{
    RAM_ISR_Table[INTTM03_vect]();
}

#pragma vector = INTAD_vect
__interrupt static void INTAD_Interrupt(void)
{
    RAM_ISR_Table[INTAD_vect]();
}

#pragma vector = INTRTCPRD_vect
__interrupt static void INTRTCPRD_Interrupt(void)
{
    RAM_ISR_Table[INTRTCPRD_vect]();
}

#pragma vector = INTIT_vect
__interrupt static void INTIT_Interrupt(void)
{
    RAM_ISR_Table[INTIT_vect]();
}

#pragma vector = INTRTCALM1_vect
__interrupt static void INTRTCALM1_Interrupt(void)
{
    RAM_ISR_Table[INTRTCALM1_vect]();
}

#pragma vector = INTCSI30_vect
__interrupt static void INTCSI30_Interrupt(void)
{
    RAM_ISR_Table[INTCSI30_vect]();
}

#pragma vector = INTSR3_vect
__interrupt static void INTSR3_Interrupt(void)
{
    RAM_ISR_Table[INTSR3_vect]();
}

#pragma vector = INTDSAD_vect
__interrupt static void INTDSAD_Interrupt(void)
{
    RAM_ISR_Table[INTDSAD_vect]();
}

#pragma vector = INTTM04_vect
__interrupt static void INTTM04_Interrupt(void)
{
    RAM_ISR_Table[INTTM04_vect]();
}

#pragma vector = INTTM05_vect
__interrupt static void INTTM05_Interrupt(void)
{
    RAM_ISR_Table[INTTM05_vect]();
}

#pragma vector = INTP6_vect
__interrupt static void INTP6_Interrupt(void)
{
    RAM_ISR_Table[INTP6_vect]();
}

#pragma vector = INTP7_vect
__interrupt static void INTP7_Interrupt(void)
{
    RAM_ISR_Table[INTP7_vect]();
}

#pragma vector = INTRTCIC0_vect
__interrupt static void INTRTCIC0_Interrupt(void)
{
    RAM_ISR_Table[INTRTCIC0_vect]();
}

#pragma vector = INTRTCIC1_vect
__interrupt static void INTRTCIC1_Interrupt(void)
{
    RAM_ISR_Table[INTRTCIC1_vect]();
}

#pragma vector = INTRTCIC2_vect
__interrupt static void INTRTCIC2_Interrupt(void)
{
    RAM_ISR_Table[INTRTCIC2_vect]();
}

#pragma vector = INTTM06_vect
__interrupt static void INTTM06_Interrupt(void)
{
    RAM_ISR_Table[INTTM06_vect]();
}

#pragma vector = INTTM07_vect
__interrupt static void INTTM07_Interrupt(void)
{
    RAM_ISR_Table[INTTM07_vect]();
}

#pragma vector = INTIT00_vect
__interrupt static void INTIT00_Interrupt(void)
{
    RAM_ISR_Table[INTIT00_vect]();
}

#pragma vector = INTIT01_vect
__interrupt static void INTIT01_Interrupt(void)
{
    RAM_ISR_Table[INTIT01_vect]();
}

#pragma vector = INTSRE3_vect
__interrupt static void INTSRE3_Interrupt(void)
{
    RAM_ISR_Table[INTSRE3_vect]();
}

#pragma vector = INTMACLOF_vect
__interrupt static void INTMACLOF_Interrupt(void)
{
    RAM_ISR_Table[INTMACLOF_vect]();
}

#pragma vector = INTOSDC_vect
__interrupt static void INTOSDC_Interrupt(void)
{
    RAM_ISR_Table[INTOSDC_vect]();
}

#pragma vector = INTFL_vect
__interrupt static void INTFL_Interrupt(void)
{
    RAM_ISR_Table[INTFL_vect]();
}

#pragma vector = INTP8_vect
__interrupt static void INTP8_Interrupt(void)
{
    RAM_ISR_Table[INTP8_vect]();
}

#pragma vector = INTP9_vect
__interrupt static void INTP9_Interrupt(void)
{
    RAM_ISR_Table[INTP9_vect]();
}

#pragma vector = INTIT10_vect
__interrupt static void INTIT10_Interrupt(void)
{
    RAM_ISR_Table[INTIT10_vect]();
}

#pragma vector = INTIT11_vect
__interrupt static void INTIT11_Interrupt(void)
{
    RAM_ISR_Table[INTIT11_vect]();
}

#pragma vector = INTLVDVDD_vect
__interrupt static void INTLVDVDD_Interrupt(void)
{
    RAM_ISR_Table[INTLVDVDD_vect]();
}

#pragma vector = INTLVDVBAT_vect
__interrupt static void INTLVDVBAT_Interrupt(void)
{
    RAM_ISR_Table[INTLVDVBAT_vect]();
}

#pragma vector = INTLVDVRTC_vect
__interrupt static void INTLVDVRTC_Interrupt(void)
{
    RAM_ISR_Table[INTLVDVRTC_vect]();
}

#pragma vector = INTLVDEXLVD_vect
__interrupt static void INTLVDEXLVD_Interrupt(void)
{
    RAM_ISR_Table[INTLVDEXLVD_vect]();
}

#pragma vector = INTST4_vect
__interrupt static void INTST4_Interrupt(void)
{
    RAM_ISR_Table[INTST4_vect]();
}

#pragma vector = INTSR4_vect
__interrupt static void INTSR4_Interrupt(void)
{
    RAM_ISR_Table[INTSR4_vect]();
}

#pragma vector = INTSRE4_vect
__interrupt static void INTSRE4_Interrupt(void)
{
    RAM_ISR_Table[INTSRE4_vect]();
}

#pragma vector = INTDSADDEC_vect
__interrupt static void INTDSADDEC_Interrupt(void)
{
    RAM_ISR_Table[INTDSADDEC_vect]();
}

#pragma vector = INTTRJ1_vect
__interrupt static void INTTRJ1_Interrupt(void)
{
    RAM_ISR_Table[INTTRJ1_vect]();
}

#endif//__ICCRL78__