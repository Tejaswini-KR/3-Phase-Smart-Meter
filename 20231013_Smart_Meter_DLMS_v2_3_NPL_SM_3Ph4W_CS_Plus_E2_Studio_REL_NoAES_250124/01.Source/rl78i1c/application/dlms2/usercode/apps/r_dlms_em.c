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
 * Copyright (C) 2013, 2016 Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * File Name    : r_dlms_em.c
 * Version      : 1.00
 * Device(s)    : RL78/I1C
 * Tool-Chain   : CCRL
 * H/W Platform : RL78/I1C Energy Meter Platform
 * Description  : 
 ************************************************************************************************************************
 * History      : DD.MM.YYYY Version Description
 ***********************************************************************************************************************/
// 21.12.2020 New create
/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
#include "r_dlms_em.h"
/***********************************************************************************************************************
 Macro definitions
 ***********************************************************************************************************************/


/***********************************************************************************************************************
 Typedef definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Imported global variables and functions (from other files)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global variables and functions (to be accessed by other files)
 ***********************************************************************************************************************/
/*
* DLMS OBIS data linkage
*/

uint16_t g_EM_MaxDemandIntegrationPeriod;

/**********************************************************************************************************************
 * Function Name: R_EM_MaxDemandIntegrationPeriodSet      
 * Description  : Function to set max demand integration period
 * Arguments    : period value from client to set.
 * Return Value : result of set, RLT_SUCCESS - successful(= 0), else unsuccessfull.                   
 **********************************************************************************************************************/ 
uint8_t R_EM_MaxDemandIntegrationPeriodSet(uint16_t period)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}


/***********************************************************************************************************************
 Private global variables and functions
 ***********************************************************************************************************************/