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
* File Name    : r_cg_intp_user.c
* Version      : Code Generator for RL78/I1C V1.01.00.02 [15 May 2017]
* Device(s)    : R5F10NPJ
* Tool-Chain   : CCRL
* Description  : This file implements device driver for INTP module.
* Creation Date: 3/22/2019
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_intp.h"
/* Start user code for include. Do not edit comment generated here */
#include "r_cg_rtc.h"
#include "key.h"
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
volatile uint8_t g_intp_case_open_flag = 0;
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_intc0_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
NEAR_FUNC void r_intc0_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    EI();
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_intc5_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
NEAR_FUNC void r_intc5_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    EI();
    /* End user code. Do not edit comment generated here */
}


/***********************************************************************************************************************
* Function Name: r_rtc_time_capture1
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
NEAR_FUNC void r_intrtcic0_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    EI();
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_rtc_time_capture1
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
NEAR_FUNC void r_intrtcic1_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    EI();
	g_intp_case_open_flag = 1;
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_rtc_time_capture2
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
NEAR_FUNC void r_intrtcic2_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    EI();
    KEY_UpPressed();
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
