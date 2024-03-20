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
 * File Name    : r_dlms_ctrl_limiter.c
 * Version      : 1.00
 * Device(s)    : RL78/I1C
 * Tool-Chain   : CCRL
 * H/W Platform : RL78/I1C Energy Meter Platform
 * Description  : 
 ************************************************************************************************************************
 * History      : DD.MM.YYYY Version Description
 ***********************************************************************************************************************/
// 16.12.2020 New create
/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
#include "r_dlms_ctrl_limiter.h"
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

/*
* LIMITER
*/

/* Class 71 attribute 03 */
/**********************************************************************************************************************
 * Function Name: R_LIMITER_ThresholdActiveGet      
 * Description  : Function to get limiter threshold active
 * Arguments    : p_data_out -  pointer of threshold active to get.
 * Return Value : TRUE - get successfully, FALSE - get unsuccessfully.                   
 **********************************************************************************************************************/ 
uint8_t R_LIMITER_ThresholdActiveGet(float32_t * p_out_data)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}

/* Class 71 attribute 04 */
float32_t g_limiter_ThresholdNormal;

/**********************************************************************************************************************
 * Function Name: R_LIMITER_ThresholdNormalSet      
 * Description  : Function to set limiter threshold normal 
 * Arguments    : p_data_in -  pointer of normal threshold from client to set.
 * Return Value : TRUE - get successfully, FALSE - get unsuccessfully.                  
 **********************************************************************************************************************/ 
uint8_t R_LIMITER_ThresholdNormalSet(float32_t * p_data_in)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}

/* Class 71 attribute 05 */
float32_t g_limiter_ThresholdEmergency;

/**********************************************************************************************************************
 * Function Name: R_LIMITER_ThresholdEmergencySet      
 * Description  : Function to set limiter threshold emergency 
 * Arguments    : p_data_in -  pointer of emergency threshold from client to set.
 * Return Value : TRUE - get successfully, FALSE - get unsuccessfully.                 
 **********************************************************************************************************************/ 
uint8_t R_LIMITER_ThresholdEmergencySet(float32_t * p_data_in)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}

/* Class 71 attribute 06 */
uint32_t g_limiter_MinOverThresholdDuration;

/**********************************************************************************************************************
 * Function Name: R_LIMITER_MinOverThresholdDurationSet      
 * Description  : Function to set min over threshold duration
 * Arguments    : p_data_in -  pointer of minimal over threshold duration in seconds required to 
 *                             execute the over threshold action from client to set.
 * Return Value : TRUE - set successfully, FALSE - set unsuccessfully.                 
 **********************************************************************************************************************/ 
uint8_t R_LIMITER_MinOverThresholdDurationSet(uint32_t * p_data_in)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}

/* Class 71 attribute 07 */
uint32_t g_limiter_MinUnderThresholdDuration;

/**********************************************************************************************************************
 * Function Name: R_LIMITER_MinUnderThresholdDurationSet      
 * Description  : Function to set min under threshold duration
 * Arguments    : p_data_in -  pointer of minimal under threshold duration in seconds required to
 *                             execute the over threshold action from client to set.
 * Return Value : TRUE - set successfully, FALSE - set unsuccessfully.                 
 **********************************************************************************************************************/ 
uint8_t R_LIMITER_MinUnderThresholdDurationSet(uint32_t * p_data_in)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}

/* Class 71 attribute 10 */
/**********************************************************************************************************************
 * Function Name: R_LIMITER_ActiveGet      
 * Description  : Function to get limiter active value
 * Arguments    : p_data_in -  boolean, pointer of active value to get.
 * Return Value : TRUE - get successfully, FALSE - get unsuccessfully.                 
 **********************************************************************************************************************/ 
uint8_t R_LIMITER_ActiveGet(uint8_t * p_data_in)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}

/*
 * Disconnect control
 */

/* Class 70 attribute 03 */
uint8_t g_ctrl_ControlState;

/* Class 70 attribute 04 */
uint8_t g_ctrl_ControlMode;
/**********************************************************************************************************************
 * Function Name: R_CTRL_ControlModeSet      
 * Description  : Function to set control mode
 * Arguments    : p_data_in(enum) -  pointer of control mode from client to set.
 * Return Value : TRUE - get successfully, FALSE - get unsuccessfully.                
 **********************************************************************************************************************/ 
uint8_t R_CTRL_ControlModeSet(uint8_t * p_data_in)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}

/**********************************************************************************************************************
 * Function Name: R_CTRL_DisconnectAction      
 * Description  : Function to execute disconnect action
 * Arguments    : p_data_in(enum) -  pointer of control mode from client to set.
 * Return Value : TRUE - get successfully, FALSE - get unsuccessfully.                
 **********************************************************************************************************************/ 
uint8_t R_CTRL_DisconnectAction(void)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}

/**********************************************************************************************************************
 * Function Name: R_CTRL_ConnectAction      
 * Description  : Function to disconnect action
 * Arguments    : p_data_in(enum) -  pointer of control mode from client to set.
 * Return Value : TRUE - get successfully, FALSE - get unsuccessfully.                
 **********************************************************************************************************************/ 
uint8_t R_CTRL_ConnectAction(void)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}
/***********************************************************************************************************************
 Private global variables and functions
 ***********************************************************************************************************************/