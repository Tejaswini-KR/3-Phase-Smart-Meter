/******************************************************************************
* DISCLAIMER

* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized.

* This software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.

* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES 
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, 
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY 
* DISCLAIMED.

* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES 
* FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS 
* AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

* Renesas reserves the right, without notice, to make changes to this 
* software and to discontinue the availability of this software.  
* By using this software, you agree to the additional terms and 
* conditions found by accessing the following link:
* http://www.renesas.com/disclaimer
******************************************************************************/
/* Copyright (C) 2018 Renesas Electronics Corporation. All rights reserved.  */
/******************************************************************************	
* File Name    : r_dlms_usercode_class45.c
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023 
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/

#include <string.h>
#include <stddef.h>
#include "r_dlms_usercode_class45.h"


/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/* User code variable */


/* User code function */

/******************************************************************************
Private global variables and functions
******************************************************************************/
/**********************************************************************
***********************************************************************
*******************     PRIVATE GLOBAL VARIABLES       ****************
***********************************************************************
***********************************************************************
* Declare detail value to assign to Exported global variables if      *
* that is complex data type (struct or array)                         *
**********************************************************************/



/***********************************************************************************************************
* Object name:      GPRS modem setup
* Object number:    00
* Object obis code: 0.0.25.4.0.255
***********************************************************************************************************/

/* Please update your array size following your setting change by asigning under variable */
/* For APN */
const uint16_t r_dlms_ic45_obj00_att02_APN_string_length = 8;
/******************************************************************************
* Function Name : R_DLMS_USER_ic45_obj00_att02_get
* Description   : Object name       : GPRS modem setup
*                 Object index      : 00
*                 Class             : 45
*                 Attribute order   : 02
*                 Attribute name    : APN
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 OctetString * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic45_obj00_att02_get(distributor_params_t * p_params, OctetString * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	OctetString
	{
	    uint8_t   *p_content;
	    uint16_t   length;
	    uint16_t   alloc_size;
	}
	*********************************************/

	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign data link here */
	uint8_t link_data_string[] =  "m3-world";
	/* Set length for string */
	/* !!! If change content of link_data_string, please update r_dlms_ic45_obj00_att02_APN_string_length */
	p_attribute_get->length = r_dlms_ic45_obj00_att02_APN_string_length;
	/* Set value for string */
	memcpy(p_attribute_get->p_content, &link_data_string, r_dlms_ic45_obj00_att02_APN_string_length);

	/* Start user code here */
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic45_obj00_att03_get
* Description   : Object name       : GPRS modem setup
*                 Object index      : 00
*                 Class             : 45
*                 Attribute order   : 03
*                 Attribute name    : PIN_code
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint16_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic45_obj00_att03_get(distributor_params_t * p_params, uint16_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint16_t(long-unsigned)
	*********************************************/

	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	uint16_t link_data = 0;
	/* Set value */
	*((uint16_t *)p_attribute_get) = link_data;

	/* Start user code here */
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic45_obj00_att04_get
* Description   : Object name       : GPRS modem setup
*                 Object index      : 00
*                 Class             : 45
*                 Attribute order   : 04
*                 Attribute name    : quality_of_service
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 quality_of_service_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic45_obj00_att04_get(distributor_params_t * p_params, quality_of_service_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	 This is structure of quality of service, please set following  this.
	 quality_of_service_t
	 {
	       qos_element_t * p_default;
	       qos_element_t * p_requested;
	 };
	 This is structure of qos element, please set following  this.
	 qos_element_t
	 {
	       uint8_t precedence;
	       uint8_t delay;
	       uint8_t reliability;
	       uint8_t peak_throughput;
	       uint8_t mean_throughput;
	 };
	*********************************************/

	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Link data here */
	/* Default */
	uint8_t precedence_of_default_link = 0;
	uint8_t delay_of_default_link = 0;
	uint8_t reliability_of_default_link = 0;
	uint8_t peak_throughput_of_default_link = 0;
	uint8_t mean_throughput_of_default_link = 0;

	/* Requested */
	uint8_t precedence_of_requested_link = 0;
	uint8_t delay_of_requested_link = 0;
	uint8_t reliability_of_requested_link = 0;
	uint8_t peak_throughput_of_requested_link = 0;
	uint8_t mean_throughput_of_requested_link = 0;

	/* Set data link to p_get_attribute */
	/* Default */
	p_attribute_get->p_default->precedence = precedence_of_default_link;
	p_attribute_get->p_default->delay = delay_of_default_link;
	p_attribute_get->p_default->reliability = reliability_of_default_link;
	p_attribute_get->p_default->peak_throughput = peak_throughput_of_default_link;
	p_attribute_get->p_default->mean_throughput = mean_throughput_of_default_link;
	/* Requested */
	p_attribute_get->p_requested->precedence = precedence_of_requested_link;
	p_attribute_get->p_requested->delay = delay_of_requested_link;
	p_attribute_get->p_requested->reliability = reliability_of_requested_link;
	p_attribute_get->p_requested->peak_throughput = peak_throughput_of_requested_link;
	p_attribute_get->p_requested->mean_throughput = mean_throughput_of_requested_link;
	/* Start user code here */
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}



