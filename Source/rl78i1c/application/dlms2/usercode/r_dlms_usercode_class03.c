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
* File Name    : r_dlms_usercode_class03.c
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
#include <math.h>
#include "r_dlms_usercode_class03.h"

/* User Code */
#include "r_dlms_app.h"
#include "inst_read.h"
#include "r_dlms_storage.h"
#include "r_tariff.h"
#include "em_measurement.h"
#include "r_dlms_cumulate.h"
#include "r_loadsurvey.h"
#include "r_scheduler.h"
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
* Function Name : GET_ImportApparentEnergyTariff
* Description   : Mark get/set service successfully
* Arguments     : distributor_params_t * p_params - pointer contains all infor of service
*                 uint8_t tariff_index - index tariff in array that need to get
*                 float32_t * p_data_get - output value of energy need to get
* Function Calls:
* Return Value  :
******************************************************************************/
static uint8_t GET_ImportApparentEnergyTariff(distributor_params_t * p_params, uint8_t tariff_index, float32_t * p_data_get)
{
	if(R_TARIFF_GetImportApparentEnergyTariff(tariff_index, p_data_get) == TARIFF_RET_OK)
    {
		return VAL_DATA_ACCESS_RESULT_SUCCESS;
    }
    else
    {
        R_DLMS_GetSetFail(p_params, VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED);
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
    }
}

/******************************************************************************
* Function Name : R_DLMS_GetSetFail
* Interface     : R_DLMS_GetSetFail(uint8_t type_fail)
* Description   : Mark get/set service successfully
* Arguments     : distributor_params_t * p_params - pointer contains all infor of service
*                 uint8_t tariff_index - index tariff in array that need to get
*                 float32_t * p_data_get - output value of energy need to get
* Function Calls:
* Return Value  :
******************************************************************************/
static uint8_t GET_ImportActiveEnergyTariff(distributor_params_t * p_params, uint8_t tariff_index, float32_t * p_data_get)
{
	if(R_TARIFF_GetImportActiveEnergyTariff(tariff_index, p_data_get) == TARIFF_RET_OK)
    {
		return VAL_DATA_ACCESS_RESULT_SUCCESS;
    }
    else
    {
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;			
    }
}
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
* Object name:      System PF for billing period Import
* Object number:    00
* Object obis code: 1.0.13.0.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ00_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ00_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj00_att02_get
* Description   : Object name       : System PF for billing period Import
*                 Object index      : 00
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj00_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 0;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	*(float32_t *)p_attribute_get->buffer = R_LOADSURVEY_GetCurrentAveragePF();

	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ00_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ00_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj00_att02_set
* Description   : Object name       : System PF for billing period Import
*                 Object index      : 00
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj00_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj00_att03_Scaler_Unit
* Object name: System PF for billing period Import
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Billing
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj00_att03_Scaler_Unit  = {0, PHY_UNIT_NONE};




/***********************************************************************************************************
* Object name:      Billing date
* Object number:    01
* Object obis code: 0.0.0.1.2.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ01_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ01_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj01_att02_get
* Description   : Object name       : Billing date
*                 Object index      : 01
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj01_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Octet_String */
	/* Length: 12 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// uint8_t link_data_value[] = NULL;
	// /* Please update link_data_length after assign link_data_value */
	// uint16_t link_data_length = 12;
	// p_attribute_get->choice.size = link_data_length;
	// memcpy(p_attribute_get->buffer, &link_data_value, link_data_length);

	/* Start user code here */
	uint8_t time_schedule[3];
	uint8_t date_schedule[4];
	uint16_t year;
	date_time_t billing_datetime = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		                            0xFF, 0xFF, 0xFF, 0x80, 0x00, 0xFF};
	uint16_t length_array;


    /* Get length of execution time of billing */
	length_array = R_SCHEDULER_ExecutionTimeArrayLengthGet(3);//3 is scheduler id of billing

	/* 
	 * If length of execution time of schedule is 0 or more than SCHEDULE_EXE_TIME_MAX_SUPPORT_3
	 * Return not specific value
	 */
	if((length_array <= 0) || (length_array > SCHEDULE_EXE_TIME_MAX_SUPPORT_3))
	{
		p_attribute_get->choice.size = 12;
		memcpy(p_attribute_get->buffer, &billing_datetime, 12);
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}


	R_SCHEDULER_ExecutionTimeGet(time_schedule, 3, 0);//3 is scheduler id of billing
	R_SCHEDULER_ExecutionDateGet(date_schedule, 3, 0);//3 is scheduler id of billing
	
	/* Convert data date and time of schedule to data_time of passive active calendar */
	if (date_schedule[0] == 0xFF)
	{
		billing_datetime.year_high = 0xFF;
		billing_datetime.year_low = 0xFF;
	}
	else
	{
		year = 2000 + (uint16_t)date_schedule[0];
		billing_datetime.year_high = (uint8_t)(year >> 8);
		billing_datetime.year_low = (uint8_t)year;
	}
     
	billing_datetime.month = date_schedule[1];         
	billing_datetime.day_of_week = date_schedule[2];   
	billing_datetime.day_of_month = date_schedule[3];  
	billing_datetime.hour = time_schedule[0];          
	billing_datetime.minute = time_schedule[1];        
	billing_datetime.second = time_schedule[2];
	/*
	 * According to DLMS bluebook
	 * A definition with "not specified" notation in all fields of the attribute will deactivate this automatism.
	 * Partial "not specified" notation in just some fields of date and time are not allowed.
	 */
	if ((date_schedule[0] & date_schedule[1] & date_schedule[2] & date_schedule[3] &
		 time_schedule[0] & time_schedule[1] & time_schedule[2]) == 0xFF)
	{
		billing_datetime.hundredths = 0xFF;//As mention of bluebook, class22, attirbute 04  
		billing_datetime.deviation_high = 0x80;//Not specified
		billing_datetime.deviation_low = 0x00;//Not specified
		billing_datetime.clock_status = 0xFF;//Not specified
	}
	else
	{
		billing_datetime.hundredths = 0;//As mention of bluebook, class22, attirbute 04  
		billing_datetime.deviation_high = (int8_t)(g_time_zone>>8);
    	billing_datetime.deviation_low = (int8_t)g_time_zone;
		billing_datetime.clock_status = g_clock_status;
	}

	p_attribute_get->choice.size = 12;
	memcpy(p_attribute_get->buffer, &billing_datetime, 12);
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ01_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ01_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj01_att02_set
* Description   : Object name       : Billing date
*                 Object index      : 01
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj01_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj01_att03_Scaler_Unit
* Object name: Billing date
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Billing
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj01_att03_Scaler_Unit  = {0, PHY_UNIT_NONE};




/***********************************************************************************************************
* Object name:      Cumulative Energy kVAh TZ1
* Object number:    02
* Object obis code: 1.0.9.8.1.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ02_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ02_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj02_att02_get
* Description   : Object name       : Cumulative Energy kVAh TZ1
*                 Object index      : 02
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj02_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 0;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	uint8_t tariff_num = 0;//responding index of tariff tz1
	GET_ImportApparentEnergyTariff(p_params, tariff_num, (float32_t *)p_attribute_get->buffer);
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ02_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ02_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj02_att02_set
* Description   : Object name       : Cumulative Energy kVAh TZ1
*                 Object index      : 02
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj02_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj02_att03_Scaler_Unit
* Object name: Cumulative Energy kVAh TZ1
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Billing
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj02_att03_Scaler_Unit  = {3, PHY_UNIT_VOLT_AMPERE_HOUR};




/***********************************************************************************************************
* Object name:      Cumulative Energy kVAh TZ2
* Object number:    03
* Object obis code: 1.0.9.8.2.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ03_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ03_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj03_att02_get
* Description   : Object name       : Cumulative Energy kVAh TZ2
*                 Object index      : 03
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj03_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 0;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	uint8_t tariff_num = 1;//responding index of tariff tz2
	GET_ImportApparentEnergyTariff(p_params, tariff_num, (float32_t *)p_attribute_get->buffer);
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ03_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ03_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj03_att02_set
* Description   : Object name       : Cumulative Energy kVAh TZ2
*                 Object index      : 03
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj03_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj03_att03_Scaler_Unit
* Object name: Cumulative Energy kVAh TZ2
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Billing
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj03_att03_Scaler_Unit  = {3, PHY_UNIT_VOLT_AMPERE_HOUR};




/***********************************************************************************************************
* Object name:      Cumulative Energy kWh TZ3
* Object number:    04
* Object obis code: 1.0.1.8.3.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ04_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ04_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj04_att02_get
* Description   : Object name       : Cumulative Energy kWh TZ3
*                 Object index      : 04
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj04_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 0;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	uint8_t tariff_num = 2;//responding index of tariff tz3
	GET_ImportActiveEnergyTariff(p_params, tariff_num, (float32_t *)p_attribute_get->buffer);
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ04_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ04_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj04_att02_set
* Description   : Object name       : Cumulative Energy kWh TZ3
*                 Object index      : 04
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj04_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj04_att03_Scaler_Unit
* Object name: Cumulative Energy kWh TZ3
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Billing
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj04_att03_Scaler_Unit  = {3, PHY_UNIT_WATT_HOUR};




/***********************************************************************************************************
* Object name:      Cumulative Energy kVAh TZ3
* Object number:    05
* Object obis code: 1.0.9.8.3.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ05_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ05_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj05_att02_get
* Description   : Object name       : Cumulative Energy kVAh TZ3
*                 Object index      : 05
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj05_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 0;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	uint8_t tariff_num = 2;//responding index of tariff tz3
	GET_ImportApparentEnergyTariff(p_params, tariff_num, (float32_t *)p_attribute_get->buffer);
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ05_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ05_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj05_att02_set
* Description   : Object name       : Cumulative Energy kVAh TZ3
*                 Object index      : 05
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj05_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj05_att03_Scaler_Unit
* Object name: Cumulative Energy kVAh TZ3
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Billing
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj05_att03_Scaler_Unit  = {3, PHY_UNIT_VOLT_AMPERE_HOUR};




/***********************************************************************************************************
* Object name:      Cumulative Energy kVAh TZ4
* Object number:    06
* Object obis code: 1.0.9.8.4.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ06_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ06_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj06_att02_get
* Description   : Object name       : Cumulative Energy kVAh TZ4
*                 Object index      : 06
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj06_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 0;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	uint8_t tariff_num = 3;//responding index of tariff tz4
	GET_ImportApparentEnergyTariff(p_params, tariff_num, (float32_t *)p_attribute_get->buffer);
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ06_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ06_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj06_att02_set
* Description   : Object name       : Cumulative Energy kVAh TZ4
*                 Object index      : 06
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj06_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj06_att03_Scaler_Unit
* Object name: Cumulative Energy kVAh TZ4
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Billing
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj06_att03_Scaler_Unit  = {3, PHY_UNIT_VOLT_AMPERE_HOUR};




/***********************************************************************************************************
* Object name:      Cumulative Energy kWh TZ1 
* Object number:    07
* Object obis code: 1.0.1.8.1.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ07_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ07_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj07_att02_get
* Description   : Object name       : Cumulative Energy kWh TZ1 
*                 Object index      : 07
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj07_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 0;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	uint8_t tariff_num = 0;//responding index of tariff tz0
	GET_ImportActiveEnergyTariff(p_params, tariff_num, (float32_t *)p_attribute_get->buffer);
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ07_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ07_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj07_att02_set
* Description   : Object name       : Cumulative Energy kWh TZ1 
*                 Object index      : 07
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj07_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj07_att03_Scaler_Unit
* Object name: Cumulative Energy kWh TZ1 
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Billing
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj07_att03_Scaler_Unit  = {3, PHY_UNIT_WATT_HOUR};




/***********************************************************************************************************
* Object name:      Cumulative Energy kWh TZ2
* Object number:    08
* Object obis code: 1.0.1.8.2.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ08_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ08_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj08_att02_get
* Description   : Object name       : Cumulative Energy kWh TZ2
*                 Object index      : 08
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj08_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 0;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	uint8_t tariff_num = 1;//responding index of tariff tz2
	GET_ImportActiveEnergyTariff(p_params, tariff_num, (float32_t *)p_attribute_get->buffer);
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ08_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ08_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj08_att02_set
* Description   : Object name       : Cumulative Energy kWh TZ2
*                 Object index      : 08
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj08_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj08_att03_Scaler_Unit
* Object name: Cumulative Energy kWh TZ2
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Billing
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj08_att03_Scaler_Unit  = {3, PHY_UNIT_WATT_HOUR};




/***********************************************************************************************************
* Object name:      Cumulative Energy kWh TZ4
* Object number:    09
* Object obis code: 1.0.1.8.4.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ09_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ09_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj09_att02_get
* Description   : Object name       : Cumulative Energy kWh TZ4
*                 Object index      : 09
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj09_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 0;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	uint8_t tariff_num = 3;//responding index of tariff tz4
	GET_ImportActiveEnergyTariff(p_params, tariff_num, (float32_t *)p_attribute_get->buffer);
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ09_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ09_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj09_att02_set
* Description   : Object name       : Cumulative Energy kWh TZ4
*                 Object index      : 09
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj09_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj09_att03_Scaler_Unit
* Object name: Cumulative Energy kWh TZ4
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Billing
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj09_att03_Scaler_Unit  = {3, PHY_UNIT_WATT_HOUR};




/***********************************************************************************************************
* Object name:      Billing power ON duration
* Object number:    10
* Object obis code: 0.0.94.91.13.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ10_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ10_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj10_att02_get
* Description   : Object name       : Billing power ON duration
*                 Object index      : 10
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj10_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Double_Long_Unsigned */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// uint32_t link_data_value = 0;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	*(uint32_t *)p_attribute_get->buffer = g_meter_power_on_duration;
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ10_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ10_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj10_att02_set
* Description   : Object name       : Billing power ON duration
*                 Object index      : 10
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj10_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj10_att03_Scaler_Unit
* Object name: Billing power ON duration
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Billing
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj10_att03_Scaler_Unit  = {0, PHY_UNIT_MIN};




/***********************************************************************************************************
* Object name:      Cumulative Energy kWh TZ5
* Object number:    11
* Object obis code: 1.0.1.8.5.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ11_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ11_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj11_att02_get
* Description   : Object name       : Cumulative Energy kWh TZ5
*                 Object index      : 11
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj11_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 1.5;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	uint8_t tariff_num = 4;//responding index of tariff tz5
	GET_ImportActiveEnergyTariff(p_params, tariff_num, (float32_t *)p_attribute_get->buffer);
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ11_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ11_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj11_att02_set
* Description   : Object name       : Cumulative Energy kWh TZ5
*                 Object index      : 11
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj11_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj11_att03_Scaler_Unit
* Object name: Cumulative Energy kWh TZ5
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Billing
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj11_att03_Scaler_Unit  = {3, PHY_UNIT_WATT_HOUR};




/***********************************************************************************************************
* Object name:      Cumulative energy kWh TZ6
* Object number:    12
* Object obis code: 1.0.1.8.6.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ12_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ12_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj12_att02_get
* Description   : Object name       : Cumulative energy kWh TZ6
*                 Object index      : 12
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj12_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 1.5;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	uint8_t tariff_num = 5;//responding index of tariff tz6
	GET_ImportActiveEnergyTariff(p_params, tariff_num, (float32_t *)p_attribute_get->buffer);
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ12_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ12_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj12_att02_set
* Description   : Object name       : Cumulative energy kWh TZ6
*                 Object index      : 12
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj12_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj12_att03_Scaler_Unit
* Object name: Cumulative energy kWh TZ6
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Billing
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj12_att03_Scaler_Unit  = {3, PHY_UNIT_WATT_HOUR};




/***********************************************************************************************************
* Object name:      Cumulative energy kVAh TZ5
* Object number:    13
* Object obis code: 1.0.9.8.5.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ13_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ13_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj13_att02_get
* Description   : Object name       : Cumulative energy kVAh TZ5
*                 Object index      : 13
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj13_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 1.5;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	uint8_t tariff_num = 4;//responding index of tariff tz5
	GET_ImportApparentEnergyTariff(p_params, tariff_num, (float32_t *)p_attribute_get->buffer);
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ13_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ13_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj13_att02_set
* Description   : Object name       : Cumulative energy kVAh TZ5
*                 Object index      : 13
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj13_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj13_att03_Scaler_Unit
* Object name: Cumulative energy kVAh TZ5
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Billing
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj13_att03_Scaler_Unit  = {3, PHY_UNIT_VOLT_AMPERE_HOUR};




/***********************************************************************************************************
* Object name:      Cumulative energy kVAh TZ6
* Object number:    14
* Object obis code: 1.0.9.8.6.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ14_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ14_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj14_att02_get
* Description   : Object name       : Cumulative energy kVAh TZ6
*                 Object index      : 14
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj14_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 1.5;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	uint8_t tariff_num = 5;//responding index of tariff tz6
	GET_ImportApparentEnergyTariff(p_params, tariff_num, (float32_t *)p_attribute_get->buffer);
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ14_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ14_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj14_att02_set
* Description   : Object name       : Cumulative energy kVAh TZ6
*                 Object index      : 14
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj14_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//int8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj14_att03_Scaler_Unit
* Object name: Cumulative energy kVAh TZ6
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Billing
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj14_att03_Scaler_Unit  = {3, PHY_UNIT_VOLT_AMPERE_HOUR};




/***********************************************************************************************************
* Object name:      Cumulative energy kWh for TZ7
* Object number:    15
* Object obis code: 1.0.1.8.7.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ15_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ15_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj15_att02_get
* Description   : Object name       : Cumulative energy kWh for TZ7
*                 Object index      : 15
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj15_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 1.5;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	uint8_t tariff_num = 6;//responding index of tariff tz7
	GET_ImportActiveEnergyTariff(p_params, tariff_num, (float32_t *)p_attribute_get->buffer);
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ15_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ15_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj15_att02_set
* Description   : Object name       : Cumulative energy kWh for TZ7
*                 Object index      : 15
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj15_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj15_att03_Scaler_Unit
* Object name: Cumulative energy kWh for TZ7
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Billing
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj15_att03_Scaler_Unit  = {3, PHY_UNIT_WATT_HOUR};




/***********************************************************************************************************
* Object name:      Cumulative energy kWh for TZ8
* Object number:    16
* Object obis code: 1.0.1.8.8.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ16_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ16_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj16_att02_get
* Description   : Object name       : Cumulative energy kWh for TZ8
*                 Object index      : 16
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj16_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 1.5;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	uint8_t tariff_num = 7;//responding index of tariff tz8
	GET_ImportActiveEnergyTariff(p_params, tariff_num, (float32_t *)p_attribute_get->buffer);
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ16_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ16_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj16_att02_set
* Description   : Object name       : Cumulative energy kWh for TZ8
*                 Object index      : 16
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj16_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj16_att03_Scaler_Unit
* Object name: Cumulative energy kWh for TZ8
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Billing
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj16_att03_Scaler_Unit  = {3, PHY_UNIT_WATT_HOUR};




/***********************************************************************************************************
* Object name:      Cumulative energy kVAh for TZ7
* Object number:    17
* Object obis code: 1.0.9.8.7.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ17_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ17_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj17_att02_get
* Description   : Object name       : Cumulative energy kVAh for TZ7
*                 Object index      : 17
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj17_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 1.5;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	uint8_t tariff_num = 6;//responding index of tariff tz7
	GET_ImportApparentEnergyTariff(p_params, tariff_num, (float32_t *)p_attribute_get->buffer);
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ17_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ17_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj17_att02_set
* Description   : Object name       : Cumulative energy kVAh for TZ7
*                 Object index      : 17
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj17_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj17_att03_Scaler_Unit
* Object name: Cumulative energy kVAh for TZ7
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Billing
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj17_att03_Scaler_Unit  = {3, PHY_UNIT_VOLT_AMPERE_HOUR};




/***********************************************************************************************************
* Object name:      Cumulative energy kVAh for TZ8
* Object number:    18
* Object obis code: 1.0.9.8.8.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ18_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ18_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj18_att02_get
* Description   : Object name       : Cumulative energy kVAh for TZ8
*                 Object index      : 18
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj18_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 1.5;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	uint8_t tariff_num = 7;//responding index of tariff tz8
	GET_ImportApparentEnergyTariff(p_params, tariff_num, (float32_t *)p_attribute_get->buffer);
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ18_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ18_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj18_att02_set
* Description   : Object name       : Cumulative energy kVAh for TZ8
*                 Object index      : 18
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj18_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj18_att03_Scaler_Unit
* Object name: Cumulative energy kVAh for TZ8
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Billing
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj18_att03_Scaler_Unit  = {3, PHY_UNIT_VOLT_AMPERE_HOUR};




/***********************************************************************************************************
* Object name:      Block Energy kVAh import BL
* Object number:    19
* Object obis code: 1.0.9.29.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ19_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ19_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj19_att02_get
* Description   : Object name       : Block Energy kVAh import BL
*                 Object index      : 19
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Block load
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj19_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 0;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	float32_t value, value_old;
	DLMS_STORAGE storage_kwh_block = {STORAGE_EEPROM_DLMS_KWH_BLOCK_ADDR, STORAGE_EEPROM_DLMS_KWH_BLOCK_SIZE};

	/* Get the latest value of block load */
	R_DLMS_EEPROM_Read(storage_kwh_block, (uint8_t *)&value_old);
	/* Get current inst energy apparent export */
	value = gp_inst_LastDataPop->value.active_energy_total_import/1000;

	*(float32_t *)p_attribute_get->buffer = value - value_old;
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ19_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ19_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj19_att02_set
* Description   : Object name       : Block Energy kVAh import BL
*                 Object index      : 19
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Block load
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj19_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj19_att03_Scaler_Unit
* Object name: Block Energy kVAh import BL
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Block load
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj19_att03_Scaler_Unit  = {3, PHY_UNIT_VOLT_AMPERE_HOUR};




/***********************************************************************************************************
* Object name:      Block Energy kVAh Export
* Object number:    20
* Object obis code: 1.0.10.29.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ20_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ20_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj20_att02_get
* Description   : Object name       : Block Energy kVAh Export
*                 Object index      : 20
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Block load
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj20_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 0;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	float32_t value, value_old;
	DLMS_STORAGE storage_kvah_block_export = {STORAGE_EEPROM_DLMS_KVAH_BLOCK_EXPORT_ADDR, STORAGE_EEPROM_DLMS_KVAH_BLOCK_EXPORT_SIZE};

	/* Get the latest value of block load */
	R_DLMS_EEPROM_Read(storage_kvah_block_export, (uint8_t *)&value_old);
	/* Get current inst energy apparent export */
	value = gp_inst_LastDataPop->value.apparent_energy_total_export/1000;

	*(float32_t *)p_attribute_get->buffer = value - value_old;
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ20_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ20_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj20_att02_set
* Description   : Object name       : Block Energy kVAh Export
*                 Object index      : 20
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Block load
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj20_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj20_att03_Scaler_Unit
* Object name: Block Energy kVAh Export
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Block load
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj20_att03_Scaler_Unit  = {3, PHY_UNIT_VOLT_AMPERE_HOUR};




/***********************************************************************************************************
* Object name:      Block Energy kWh Import
* Object number:    21
* Object obis code: 1.0.1.29.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ21_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ21_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj21_att02_get
* Description   : Object name       : Block Energy kWh Import
*                 Object index      : 21
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Block load
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj21_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 0;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	float32_t value, value_old;
	DLMS_STORAGE storage_kwh_block = {STORAGE_EEPROM_DLMS_KWH_BLOCK_ADDR, STORAGE_EEPROM_DLMS_KWH_BLOCK_SIZE};

	/* Get the latest value of block load */
	R_DLMS_EEPROM_Read(storage_kwh_block, (uint8_t *)&value_old);
	/* Get current inst energy apparent export */
	value = gp_inst_LastDataPop->value.active_energy_total_import/1000;

	*(float32_t *)p_attribute_get->buffer = value - value_old;
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ21_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ21_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj21_att02_set
* Description   : Object name       : Block Energy kWh Import
*                 Object index      : 21
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Block load
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj21_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj21_att03_Scaler_Unit
* Object name: Block Energy kWh Import
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Block load
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj21_att03_Scaler_Unit  = {3, PHY_UNIT_WATT_HOUR};




/***********************************************************************************************************
* Object name:      Block Energy kWh Export
* Object number:    22
* Object obis code: 1.0.2.29.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ22_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ22_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj22_att02_get
* Description   : Object name       : Block Energy kWh Export
*                 Object index      : 22
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Block load
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj22_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 0;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	float32_t value, value_old;
	DLMS_STORAGE storage_kwh_block_export = {STORAGE_EEPROM_DLMS_KWH_BLOCK_EXPORT_ADDR, STORAGE_EEPROM_DLMS_KWH_BLOCK_EXPORT_SIZE};

	/* Get the latest value of block load */
	R_DLMS_EEPROM_Read(storage_kwh_block_export, (uint8_t *)&value_old);
	/* Get current inst energy apparent export */
	value = gp_inst_LastDataPop->value.active_energy_total_export/1000;

	*(float32_t *)p_attribute_get->buffer = value - value_old;
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ22_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ22_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj22_att02_set
* Description   : Object name       : Block Energy kWh Export
*                 Object index      : 22
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Block load
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj22_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj22_att03_Scaler_Unit
* Object name: Block Energy kWh Export
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Block load
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj22_att03_Scaler_Unit  = {3, PHY_UNIT_WATT_HOUR};




/***********************************************************************************************************
* Object name:      Current IR BL
* Object number:    23
* Object obis code: 1.0.31.27.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ23_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ23_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj23_att02_get
* Description   : Object name       : Current IR BL
*                 Object index      : 23
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Block load
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj23_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	//float32_t link_data_value = 1.5;
	/* Set value */
	//memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	*(float32_t *)p_attribute_get->buffer = gp_inst_LastDataPop->value.irms[LINE_PHASE_R];
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ23_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ23_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj23_att02_set
* Description   : Object name       : Current IR BL
*                 Object index      : 23
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Block load
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj23_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj23_att03_Scaler_Unit
* Object name: Current IR BL
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Block load
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj23_att03_Scaler_Unit  = {0, PHY_UNIT_AMPERE};




/***********************************************************************************************************
* Object name:      Voltage VRN BL
* Object number:    24
* Object obis code: 1.0.32.27.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ24_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ24_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj24_att02_get
* Description   : Object name       : Voltage VRN BL
*                 Object index      : 24
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Block load
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj24_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	//float32_t link_data_value = 1.5;
	/* Set value */
	//memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	*(float32_t *)p_attribute_get->buffer = gp_inst_LastDataPop->value.vrms[LINE_PHASE_R];
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ24_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ24_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj24_att02_set
* Description   : Object name       : Voltage VRN BL
*                 Object index      : 24
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Block load
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj24_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj24_att03_Scaler_Unit
* Object name: Voltage VRN BL
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Block load
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj24_att03_Scaler_Unit  = {0, PHY_UNIT_VOLT};




/***********************************************************************************************************
* Object name:      Current IY BL
* Object number:    25
* Object obis code: 1.0.51.27.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ25_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ25_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj25_att02_get
* Description   : Object name       : Current IY BL
*                 Object index      : 25
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Block load
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj25_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	//float32_t link_data_value = 1.5;
	/* Set value */
	//memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	*(float32_t *)p_attribute_get->buffer = gp_inst_LastDataPop->value.irms[LINE_PHASE_Y];
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ25_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ25_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj25_att02_set
* Description   : Object name       : Current IY BL
*                 Object index      : 25
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Block load
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj25_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj25_att03_Scaler_Unit
* Object name: Current IY BL
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Block load
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj25_att03_Scaler_Unit  = {0, PHY_UNIT_AMPERE};




/***********************************************************************************************************
* Object name:      Voltage VYN BL
* Object number:    26
* Object obis code: 1.0.52.27.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ26_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ26_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj26_att02_get
* Description   : Object name       : Voltage VYN BL
*                 Object index      : 26
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Block load
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj26_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	//float32_t link_data_value = 1.5;
	/* Set value */
	//memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	*(float32_t *)p_attribute_get->buffer = gp_inst_LastDataPop->value.vrms[LINE_PHASE_Y];
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ26_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ26_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj26_att02_set
* Description   : Object name       : Voltage VYN BL
*                 Object index      : 26
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Block load
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj26_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj26_att03_Scaler_Unit
* Object name: Voltage VYN BL
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Block load
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj26_att03_Scaler_Unit  = {0, PHY_UNIT_VOLT};




/***********************************************************************************************************
* Object name:      Current IB BL
* Object number:    27
* Object obis code: 1.0.71.27.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ27_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ27_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj27_att02_get
* Description   : Object name       : Current IB BL
*                 Object index      : 27
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Block load
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj27_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	//float32_t link_data_value = 1.5;
	/* Set value */
	//memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	*(float32_t *)p_attribute_get->buffer = gp_inst_LastDataPop->value.irms[LINE_PHASE_B];
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ27_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ27_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj27_att02_set
* Description   : Object name       : Current IB BL
*                 Object index      : 27
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Block load
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj27_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj27_att03_Scaler_Unit
* Object name: Current IB BL
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Block load
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj27_att03_Scaler_Unit  = {0, PHY_UNIT_AMPERE};




/***********************************************************************************************************
* Object name:      Voltage VBN BL
* Object number:    28
* Object obis code: 1.0.72.27.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ28_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ28_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj28_att02_get
* Description   : Object name       : Voltage VBN BL
*                 Object index      : 28
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Block load
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj28_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	//float32_t link_data_value = 1.5;
	/* Set value */
	//memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	*(float32_t *)p_attribute_get->buffer = gp_inst_LastDataPop->value.vrms[LINE_PHASE_B];
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ28_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ28_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj28_att02_set
* Description   : Object name       : Voltage VBN BL
*                 Object index      : 28
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Block load
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj28_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj28_att03_Scaler_Unit
* Object name: Voltage VBN BL
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Block load
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj28_att03_Scaler_Unit  = {0, PHY_UNIT_VOLT};




/***********************************************************************************************************
* Object name:      Cumulative power OFF
* Object number:    29
* Object obis code: 0.0.94.91.8.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ29_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ29_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj29_att02_get
* Description   : Object name       : Cumulative power OFF
*                 Object index      : 29
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj29_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Double_Long_Unsigned */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	//uint32_t link_data_value = 0;
	/* Set value */
	//memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	*(uint32_t *)p_attribute_get->buffer = g_meter_power_off_duration;
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ29_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ29_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj29_att02_set
* Description   : Object name       : Cumulative power OFF
*                 Object index      : 29
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Instantaneous
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj29_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj29_att03_Scaler_Unit
* Object name: Cumulative power OFF
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj29_att03_Scaler_Unit  = {0, PHY_UNIT_MIN};




/***********************************************************************************************************
* Object name:      Current IR
* Object number:    30
* Object obis code: 1.0.31.7.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ30_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ30_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj30_att02_get
* Description   : Object name       : Current IR
*                 Object index      : 30
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj30_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	//float32_t link_data_value = 0;
	/* Set value */
	//memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	*(float32_t *)p_attribute_get->buffer = gp_inst_LastDataPop->value.irms[LINE_PHASE_R];
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ30_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ30_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj30_att02_set
* Description   : Object name       : Current IR
*                 Object index      : 30
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Instantaneous
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj30_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj30_att03_Scaler_Unit
* Object name: Current IR
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj30_att03_Scaler_Unit  = {0, PHY_UNIT_AMPERE};




/***********************************************************************************************************
* Object name:      Current IY
* Object number:    31
* Object obis code: 1.0.51.7.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ31_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ31_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj31_att02_get
* Description   : Object name       : Current IY
*                 Object index      : 31
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj31_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	//float32_t link_data_value = 1.5;
	/* Set value */
	//memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	*(float32_t *)p_attribute_get->buffer = gp_inst_LastDataPop->value.irms[LINE_PHASE_Y];
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ31_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ31_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj31_att02_set
* Description   : Object name       : Current IY
*                 Object index      : 31
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Instantaneous
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj31_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj31_att03_Scaler_Unit
* Object name: Current IY
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj31_att03_Scaler_Unit  = {0, PHY_UNIT_AMPERE};




/***********************************************************************************************************
* Object name:      Signed power factor B phase
* Object number:    32
* Object obis code: 1.0.73.7.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ32_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ32_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj32_att02_get
* Description   : Object name       : Signed power factor B phase
*                 Object index      : 32
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj32_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	//float32_t link_data_value = 1.5;
	/* Set value */
	//memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	/* Indian standard representation sign of PF */
	float32_t pf;
	pf = fabsf(gp_inst_LastDataPop->value.power_factor[LINE_PHASE_B]);
	if (gp_inst_LastDataPop->value.power_factor_sign[LINE_PHASE_B] == PF_SIGN_LEAD_C)
    {
        	pf = -pf;
    }

	*(float32_t *)p_attribute_get->buffer = pf;
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ32_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ32_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj32_att02_set
* Description   : Object name       : Signed power factor B phase
*                 Object index      : 32
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Instantaneous
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj32_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj32_att03_Scaler_Unit
* Object name: Signed power factor B phase
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj32_att03_Scaler_Unit  = {0, PHY_UNIT_NONE};




/***********************************************************************************************************
* Object name:      Signed power factor R phase
* Object number:    33
* Object obis code: 1.0.33.7.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ33_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ33_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj33_att02_get
* Description   : Object name       : Signed power factor R phase
*                 Object index      : 33
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj33_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	//float32_t link_data_value = 0.5;
	/* Set value */
	//memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	/* Indian standard representation sign of PF */
	float32_t pf;
	pf = fabsf(gp_inst_LastDataPop->value.power_factor[LINE_PHASE_R]);
	if (gp_inst_LastDataPop->value.power_factor_sign[LINE_PHASE_R] == PF_SIGN_LEAD_C)
    {
        	pf = -pf;
    }

	*(float32_t *)p_attribute_get->buffer = pf;
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ33_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ33_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj33_att02_set
* Description   : Object name       : Signed power factor R phase
*                 Object index      : 33
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Instantaneous
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj33_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj33_att03_Scaler_Unit
* Object name: Signed power factor R phase
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj33_att03_Scaler_Unit  = {0, PHY_UNIT_NONE};




/***********************************************************************************************************
* Object name:      Signed power factor Y phase
* Object number:    34
* Object obis code: 1.0.53.7.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ34_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ34_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj34_att02_get
* Description   : Object name       : Signed power factor Y phase
*                 Object index      : 34
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj34_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	//float32_t link_data_value = 0.5;
	/* Set value */
	//memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	float32_t pf;
	pf = fabsf(gp_inst_LastDataPop->value.power_factor[LINE_PHASE_Y]);
	if (gp_inst_LastDataPop->value.power_factor_sign[LINE_PHASE_Y] == PF_SIGN_LEAD_C)
    {
        	pf = -pf;
    }

	*(float32_t *)p_attribute_get->buffer = pf;
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ34_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ34_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj34_att02_set
* Description   : Object name       : Signed power factor Y phase
*                 Object index      : 34
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Instantaneous
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj34_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj34_att03_Scaler_Unit
* Object name: Signed power factor Y phase
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj34_att03_Scaler_Unit  = {0, PHY_UNIT_NONE};




/***********************************************************************************************************
* Object name:      Three phase power factor PF
* Object number:    35
* Object obis code: 1.0.13.7.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ35_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ35_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj35_att02_get
* Description   : Object name       : Three phase power factor PF
*                 Object index      : 35
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj35_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	//float32_t link_data_value = 0.5;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	*(float32_t *)p_attribute_get->buffer = gp_inst_LastDataPop->value.power_factor[LINE_TOTAL];
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ35_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ35_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj35_att02_set
* Description   : Object name       : Three phase power factor PF
*                 Object index      : 35
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Instantaneous
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj35_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj35_att03_Scaler_Unit
* Object name: Three phase power factor PF
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj35_att03_Scaler_Unit  = {0, PHY_UNIT_NONE};




/***********************************************************************************************************
* Object name:      Signed reactive power
* Object number:    36
* Object obis code: 1.0.3.7.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ36_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ36_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj36_att02_get
* Description   : Object name       : Signed reactive power
*                 Object index      : 36
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj36_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	//float32_t link_data_value = 1.5;
	/* Set value */
	//memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	float32_t reactive_power;
	reactive_power = gp_inst_LastDataPop->value.reactive_power[LINE_TOTAL];
	if (gp_inst_LastDataPop->value.power_factor_sign[LINE_TOTAL] == PF_SIGN_LEAD_C)
    {
        reactive_power = -reactive_power;
    }

	*(float32_t *)p_attribute_get->buffer = reactive_power;
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ36_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ36_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj36_att02_set
* Description   : Object name       : Signed reactive power
*                 Object index      : 36
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Instantaneous
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj36_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj36_att03_Scaler_Unit
* Object name: Signed reactive power
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj36_att03_Scaler_Unit  = {3, PHY_UNIT_VAR};




/***********************************************************************************************************
* Object name:      Cumulative energy Q1
* Object number:    37
* Object obis code: 1.0.5.8.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ37_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ37_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj37_att02_get
* Description   : Object name       : Cumulative energy Q1
*                 Object index      : 37
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous, Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj37_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	//float32_t link_data_value = 1.5;
	/* Set value */
	//memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	*(float32_t *)p_attribute_get->buffer = R_TARIFF_GetImportInductiveReactiveEnergyTotal();
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ37_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ37_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj37_att02_set
* Description   : Object name       : Cumulative energy Q1
*                 Object index      : 37
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Instantaneous, Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj37_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj37_att03_Scaler_Unit
* Object name: Cumulative energy Q1
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous, Billing
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj37_att03_Scaler_Unit  = {3, PHY_UNIT_VAR_HOUR};




/***********************************************************************************************************
* Object name:      Cumulative energy Q2
* Object number:    38
* Object obis code: 1.0.6.8.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ38_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ38_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj38_att02_get
* Description   : Object name       : Cumulative energy Q2
*                 Object index      : 38
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous, Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj38_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	//float32_t link_data_value = 1.5;
	/* Set value */
	//memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	*(float32_t *)p_attribute_get->buffer = R_TARIFF_GetExportCapacitiveReactiveEnergyTotal();
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ38_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ38_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj38_att02_set
* Description   : Object name       : Cumulative energy Q2
*                 Object index      : 38
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Instantaneous, Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj38_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj38_att03_Scaler_Unit
* Object name: Cumulative energy Q2
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous, Billing
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj38_att03_Scaler_Unit  = {3, PHY_UNIT_VAR_HOUR};




/***********************************************************************************************************
* Object name:      Cumulative energy Q3
* Object number:    39
* Object obis code: 1.0.7.8.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ39_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ39_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj39_att02_get
* Description   : Object name       : Cumulative energy Q3
*                 Object index      : 39
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous, Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj39_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	//float32_t link_data_value = 1.5;
	/* Set value */
	//memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	*(float32_t *)p_attribute_get->buffer = R_TARIFF_GetExportInductiveReactiveEnergyTotal();
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ39_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ39_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj39_att02_set
* Description   : Object name       : Cumulative energy Q3
*                 Object index      : 39
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Instantaneous, Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj39_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj39_att03_Scaler_Unit
* Object name: Cumulative energy Q3
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous, Billing
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj39_att03_Scaler_Unit  = {3, PHY_UNIT_VAR_HOUR};




/***********************************************************************************************************
* Object name:      Cumulative energy Q4
* Object number:    40
* Object obis code: 1.0.8.8.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ40_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ40_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj40_att02_get
* Description   : Object name       : Cumulative energy Q4
*                 Object index      : 40
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous, Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj40_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	//float32_t link_data_value = 1.5;
	/* Set value */
	//memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	*(float32_t *)p_attribute_get->buffer = R_TARIFF_GetImportCapacitiveReactiveEnergyTotal();
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ40_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ40_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj40_att02_set
* Description   : Object name       : Cumulative energy Q4
*                 Object index      : 40
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Instantaneous, Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj40_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj40_att03_Scaler_Unit
* Object name: Cumulative energy Q4
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous, Billing
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj40_att03_Scaler_Unit  = {3, PHY_UNIT_VAR_HOUR};




/***********************************************************************************************************
* Object name:      Cumulative Energy kWh Export
* Object number:    41
* Object obis code: 1.0.2.8.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ41_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ41_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj41_att02_get
* Description   : Object name       : Cumulative Energy kWh Export
*                 Object index      : 41
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous, Daily load, Billing, Event
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj41_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 0;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	*(float32_t *)p_attribute_get->buffer = R_TARIFF_GetExportActiveEnergyTotal();
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ41_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ41_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj41_att02_set
* Description   : Object name       : Cumulative Energy kWh Export
*                 Object index      : 41
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Instantaneous, Daily load, Billing, Event
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj41_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj41_att03_Scaler_Unit
* Object name: Cumulative Energy kWh Export
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous, Daily load, Billing, Event
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj41_att03_Scaler_Unit  = {3, PHY_UNIT_WATT_HOUR};




/***********************************************************************************************************
* Object name:      Cumulative Energy kVAh Export
* Object number:    42
* Object obis code: 1.0.10.8.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ42_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ42_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj42_att02_get
* Description   : Object name       : Cumulative Energy kVAh Export
*                 Object index      : 42
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous, Daily load, Blling
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj42_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 0;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	*(float32_t *)p_attribute_get->buffer = R_TARIFF_GetExportApparentEnergyTotal();
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ42_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ42_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj42_att02_set
* Description   : Object name       : Cumulative Energy kVAh Export
*                 Object index      : 42
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Instantaneous, Daily load, Blling
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj42_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj42_att03_Scaler_Unit
* Object name: Cumulative Energy kVAh Export
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous, Daily load, Blling
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj42_att03_Scaler_Unit  = {3, PHY_UNIT_VOLT_AMPERE_HOUR};




/***********************************************************************************************************
* Object name:      Current IB
* Object number:    43
* Object obis code: 1.0.71.7.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ43_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ43_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj43_att02_get
* Description   : Object name       : Current IB
*                 Object index      : 43
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous, Event
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj43_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	//float32_t link_data_value = 1.5;
	/* Set value */
	//memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	*(float32_t *)p_attribute_get->buffer = gp_inst_LastDataPop->value.irms[LINE_PHASE_B];
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ43_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ43_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj43_att02_set
* Description   : Object name       : Current IB
*                 Object index      : 43
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Instantaneous, Event
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj43_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj43_att03_Scaler_Unit
* Object name: Current IB
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous, Event
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj43_att03_Scaler_Unit  = {0, PHY_UNIT_AMPERE};




/***********************************************************************************************************
* Object name:      Voltage VBN
* Object number:    44
* Object obis code: 1.0.72.7.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ44_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ44_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj44_att02_get
* Description   : Object name       : Voltage VBN
*                 Object index      : 44
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous, Event
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj44_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	//float32_t link_data_value = 1.5;
	/* Set value */
	//memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	*(float32_t *)p_attribute_get->buffer = gp_inst_LastDataPop->value.vrms[LINE_PHASE_B];
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ44_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ44_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj44_att02_set
* Description   : Object name       : Voltage VBN
*                 Object index      : 44
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Instantaneous, Event
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj44_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj44_att03_Scaler_Unit
* Object name: Voltage VBN
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous, Event
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj44_att03_Scaler_Unit  = {0, PHY_UNIT_VOLT};




/***********************************************************************************************************
* Object name:      Voltage VRN
* Object number:    45
* Object obis code: 1.0.32.7.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ45_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ45_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj45_att02_get
* Description   : Object name       : Voltage VRN
*                 Object index      : 45
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous, Event
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj45_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	//float32_t link_data_value = 1.5;
	/* Set value */
	//memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	*(float32_t *)p_attribute_get->buffer = gp_inst_LastDataPop->value.vrms[LINE_PHASE_R];
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ45_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ45_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj45_att02_set
* Description   : Object name       : Voltage VRN
*                 Object index      : 45
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Instantaneous, Event
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj45_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj45_att03_Scaler_Unit
* Object name: Voltage VRN
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous, Event
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj45_att03_Scaler_Unit  = {0, PHY_UNIT_VOLT};




/***********************************************************************************************************
* Object name:      Voltage VYN
* Object number:    46
* Object obis code: 1.0.52.7.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ46_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ46_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj46_att02_get
* Description   : Object name       : Voltage VYN
*                 Object index      : 46
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous, Event
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj46_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	//float32_t link_data_value = 1.5;
	/* Set value */
	//memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	*(float32_t *)p_attribute_get->buffer = gp_inst_LastDataPop->value.vrms[LINE_PHASE_Y];
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ46_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ46_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj46_att02_set
* Description   : Object name       : Voltage VYN
*                 Object index      : 46
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Instantaneous, Event
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj46_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj46_att03_Scaler_Unit
* Object name: Voltage VYN
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous, Event
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj46_att03_Scaler_Unit  = {0, PHY_UNIT_VOLT};




/***********************************************************************************************************
* Object name:      Signed Active Power  
* Object number:    47
* Object obis code: 1.0.1.7.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ47_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ47_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj47_att02_get
* Description   : Object name       : Signed Active Power  
*                 Object index      : 47
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous, Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj47_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 0;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	*(float32_t *)p_attribute_get->buffer = gp_inst_LastDataPop->value.active_power[LINE_TOTAL];
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ47_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ47_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj47_att02_set
* Description   : Object name       : Signed Active Power  
*                 Object index      : 47
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Instantaneous, Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj47_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj47_att03_Scaler_Unit
* Object name: Signed Active Power  
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous, Push
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj47_att03_Scaler_Unit  = {3, PHY_UNIT_WATT};




/***********************************************************************************************************
* Object name:      Apparent Power
* Object number:    48
* Object obis code: 1.0.9.7.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ48_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ48_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj48_att02_get
* Description   : Object name       : Apparent Power
*                 Object index      : 48
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous, Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj48_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 0;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	*(float32_t *)p_attribute_get->buffer = gp_inst_LastDataPop->value.apparent_power[LINE_TOTAL];
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ48_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ48_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj48_att02_set
* Description   : Object name       : Apparent Power
*                 Object index      : 48
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Instantaneous, Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj48_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj48_att03_Scaler_Unit
* Object name: Apparent Power
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous, Push
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj48_att03_Scaler_Unit  = {3, PHY_UNIT_VOLT_AMPERE};




/***********************************************************************************************************
* Object name:      Frequency
* Object number:    49
* Object obis code: 1.0.14.7.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ49_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ49_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj49_att02_get
* Description   : Object name       : Frequency
*                 Object index      : 49
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous, Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj49_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 0;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	*(float32_t *)p_attribute_get->buffer = gp_inst_LastDataPop->value.freq[LINE_TOTAL];

	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ49_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ49_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj49_att02_set
* Description   : Object name       : Frequency
*                 Object index      : 49
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Instantaneous, Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj49_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj49_att03_Scaler_Unit
* Object name: Frequency
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous, Push
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj49_att03_Scaler_Unit  = {0, PHY_UNIT_HERTZ};




/***********************************************************************************************************
* Object name:      Cumulative Energy kVAh Import
* Object number:    50
* Object obis code: 1.0.9.8.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ50_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ50_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj50_att02_get
* Description   : Object name       : Cumulative Energy kVAh Import
*                 Object index      : 50
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous, Push, Daily load, Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj50_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 0;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	*(float32_t *)p_attribute_get->buffer = R_TARIFF_GetImportApparentEnergyTotal();
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ50_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ50_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj50_att02_set
* Description   : Object name       : Cumulative Energy kVAh Import
*                 Object index      : 50
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Instantaneous, Push, Daily load, Billing
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj50_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj50_att03_Scaler_Unit
* Object name: Cumulative Energy kVAh Import
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous, Push, Daily load, Billing
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj50_att03_Scaler_Unit  = {3, PHY_UNIT_VOLT_AMPERE_HOUR};




/***********************************************************************************************************
* Object name:      Cumulative Energy kWh import
* Object number:    51
* Object obis code: 1.0.1.8.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ51_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ51_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj51_att02_get
* Description   : Object name       : Cumulative Energy kWh import
*                 Object index      : 51
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous, Push, Daily load, Billing, Event
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj51_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 0;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	*(float32_t *)p_attribute_get->buffer = R_TARIFF_GetImportActiveEnergyTotal();
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ51_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ51_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj51_att02_set
* Description   : Object name       : Cumulative Energy kWh import
*                 Object index      : 51
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Instantaneous, Push, Daily load, Billing, Event
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj51_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj51_att03_Scaler_Unit
* Object name: Cumulative Energy kWh import
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous, Push, Daily load, Billing, Event
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj51_att03_Scaler_Unit  = {3, PHY_UNIT_WATT_HOUR};




/***********************************************************************************************************
* Object name:      Cumulative Energy kWh 
* Object number:    52
* Object obis code: 1.0.1.9.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS03_OBJ52_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ52_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj52_att02_get
* Description   : Object name       : Cumulative Energy kWh 
*                 Object index      : 52
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj52_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	// float32_t link_data_value = 0;
	// /* Set value */
	// memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	/* Get cumulative energy from begining of current billing period(IS15959) */
	float32_t the_last_import_active_energy_billing;
	if(R_BILLING_GetLastActiveEnergyImport(&the_last_import_active_energy_billing))
	{
		*(float32_t *)p_attribute_get->buffer = (g_inst_read_params.active_energy_total_import/1000) - the_last_import_active_energy_billing;
		/* Return result of this, please check again result value */
		return VAL_DATA_ACCESS_RESULT_SUCCESS;	
	}
	else
	{
		/* Return result of this, please check again result value */
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;	
	}
	/* End user code here */
	
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS03_OBJ52_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ52_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic03_obj52_att02_set
* Description   : Object name       : Cumulative Energy kWh 
*                 Object index      : 52
*                 Class             : 03
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj52_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 03
* Variable name: g_dlms_ic03_obj52_att03_Scaler_Unit
* Object name: Cumulative Energy kWh 
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 03, atrribute - 03)*/
const scaler_unit_t g_dlms_ic03_obj52_att03_Scaler_Unit  = {3, PHY_UNIT_WATT_HOUR};




