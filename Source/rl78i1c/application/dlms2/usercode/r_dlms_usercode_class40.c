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
* File Name    : r_dlms_usercode_class40.c
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
#include "r_dlms_usercode_class40.h"
#include "compiler.h"

/* User application */
#include "r_dlms_push.h"
#include "r_dlms_app.h"
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
push_config_t* R_DLMS_USER_GetPushConfig(distributor_params_t * p_params, uint8_t *p_push_channel)
{
	class40_child_record_t	*p_class40_obj = (class40_child_record_t *)p_params->p_child_record;
	push_config_t	*p_cnfg;

	*p_push_channel = p_class40_obj->logical_name[1];
	p_cnfg = R_DLMS_Push_GetConfig(*p_push_channel);
	if (p_cnfg == NULL)
	{
		return NULL;
	}
	return p_cnfg;
}


static uint8_t R_DLMS_USER_class40_send_destination_and_method_t_get(distributor_params_t * p_params, class40_send_destination_and_method_t * p_attribute_get)
{
	uint8_t			*p_alloc;
	uint8_t 		*p_head;
	push_config_t	*p_cnfg;
	uint8_t			push_channel;

	/* Get push setup from application */
	p_cnfg = R_DLMS_USER_GetPushConfig(p_params, &push_channel);
	if (p_cnfg == NULL){ 
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}


	/* Linkage value */
	p_attribute_get->transport_service = p_cnfg->destination.service;
	p_attribute_get->message = (class40_message_type_t)p_cnfg->destination.message;
	R_DLMS_Push_Convert_DestConfigToString
	(
		(push_transport_service_t)p_attribute_get->transport_service,
		&p_cnfg->destination.config,
		p_attribute_get->destination.p_content,
		&p_attribute_get->destination.length
	);
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

static uint8_t R_DLMS_USER_class40_send_destination_and_method_t_set(distributor_params_t * p_params, class40_send_destination_and_method_t * p_attribute_set)
{
	push_destination_t		dest_cfg;
	uint8_t					action_result;

	uint8_t 				push_channel;
	push_config_t 			*p_cnfg;

	/* Get push setup from application */
	p_cnfg = R_DLMS_USER_GetPushConfig(p_params, &push_channel);
	if (p_cnfg == NULL){ 
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}

	p_attribute_set = (void *)p_params->service_params.malloc.p_content;

	if (p_attribute_set != NULL)
	{
		dest_cfg.service = (push_transport_service_t)p_attribute_set->transport_service;
		R_DLMS_Push_Convert_StringToDestAddr(
			(push_transport_service_t)p_attribute_set->transport_service,
			p_attribute_set->destination.p_content,
			p_attribute_set->destination.length,
			&dest_cfg.config
		);
		dest_cfg.message = (push_message_type_t)p_attribute_set->message;

		action_result = R_DLMS_Push_Backup_DestinationSetup(
			push_channel,
			&dest_cfg
		);

		if (action_result == PUSH_RESULT_SUCCESS)
		{
			memcpy((uint8_t *)&p_cnfg->destination, &dest_cfg, sizeof(push_destination_t));
		}
		else if (action_result == PUSH_RESULT_FAILED)
		{
			return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
		}
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

static uint8_t R_DLMS_USER_class40_comm_window_array_t_get(distributor_params_t * p_params, class40_comm_window_array_t * p_attribute_get)
{
	push_config_t 	*p_cnfg;
	uint8_t 		push_channel;

	uint16_t		number_of_window;
	uint8_t			u8;

	/* Get push setup from application */
	p_cnfg = R_DLMS_USER_GetPushConfig(p_params, &push_channel);
	if (p_cnfg == NULL){ 
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* Allocate for pointer of attribute */
	p_attribute_get->length = 0;
	if (p_cnfg->num_of_window == 0)
	{
		
	}
	else
	{
		for (u8 = 0; u8 < p_cnfg->num_of_window; u8++)
		{
			R_DLMS_RTC_Convert_RTC2DateTime(&p_attribute_get->p_content->start_time, &p_cnfg->p_window->start);
			R_DLMS_RTC_Convert_RTC2DateTime(&p_attribute_get->p_content->end_time, &p_cnfg->p_window->end);
			
			p_attribute_get->p_content->start_time.clock_status = g_clock_status;
			p_attribute_get->p_content->start_time.deviation_high = (uint8_t)(g_time_zone>>8);
			p_attribute_get->p_content->start_time.deviation_low = (uint8_t)g_time_zone;
			
			p_attribute_get->p_content->end_time.clock_status = g_clock_status;
			p_attribute_get->p_content->end_time.deviation_high = (uint8_t)(g_time_zone>>8);
			p_attribute_get->p_content->end_time.deviation_low = (uint8_t)g_time_zone;

			p_attribute_get->length++;
		}
	}
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

static uint8_t R_DLMS_USER_class40_comm_window_array_t_set(distributor_params_t * p_params, class40_comm_window_array_t * p_attribute_set)
{
	push_window_t   		push_window[PUSH_MAX_WINDOW_SUPPORT];

	uint8_t 				push_channel;
	push_config_t 			*p_cnfg;

	uint8_t					i;

	/* Get push setup from application */
	p_cnfg = R_DLMS_USER_GetPushConfig(p_params, &push_channel);
	if (p_cnfg == NULL){ 
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}

	if (p_attribute_set->length <= PUSH_MAX_WINDOW_SUPPORT)
	{
		p_cnfg->num_of_window = p_attribute_set->length;
		if (p_attribute_set > 0)
		{
			for (i = 0; i < p_attribute_set->length; i++)
			{
				R_DLMS_RTC_Convert_DateTime2RTC(&push_window[i].start,    &p_attribute_set->p_content[i].start_time);
				R_DLMS_RTC_Convert_DateTime2RTC(&push_window[i].end,      &p_attribute_set->p_content[i].end_time);
			}
		}
		R_DLMS_Push_Backup_CommWin(
			push_channel,
			push_window,
			p_attribute_set->length
		);
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

static uint8_t R_DLMS_USER_class40_delay_start_max_uint16_t_get(distributor_params_t * p_params, uint16_t * p_attribute_get)
{
	uint8_t			*p_alloc;
	uint8_t 		*p_head;
	push_config_t 	*p_cnfg;
	uint8_t 		push_channel;

	uint16_t		number_of_window;
	uint8_t			u8;

	/* Get push setup from application */
	p_cnfg = R_DLMS_USER_GetPushConfig(p_params, &push_channel);
	if (p_cnfg == NULL){ 
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}

	/* linkage */
	*p_attribute_get = p_cnfg->delay_start_max;
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

static uint8_t R_DLMS_USER_class40_delay_start_max_uint16_t_set(distributor_params_t * p_params, uint16_t * p_attribute_set)
{
	uint8_t 				action_result;
	uint8_t 				push_channel;
	push_config_t 			*p_cnfg;

	uint8_t					i;

	/* Get push setup from application */
	p_cnfg = R_DLMS_USER_GetPushConfig(p_params, &push_channel);
	if (p_cnfg == NULL){ 
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}

	p_cnfg->delay_start = *p_attribute_set;

	action_result = R_DLMS_Push_Backup_RandomisationStartInterval(
		push_channel,
		p_cnfg->delay_start
	);
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

static uint8_t R_DLMS_USER_class40_retried_num_max_uint8_t_get(distributor_params_t * p_params, uint8_t * p_attribute_get)
{
	uint8_t			*p_alloc;
	uint8_t 		*p_head;
	push_config_t 	*p_cnfg;
	uint8_t 		push_channel;

	uint16_t		number_of_window;
	uint8_t			u8;

	/* Get push setup from application */
	p_cnfg = R_DLMS_USER_GetPushConfig(p_params, &push_channel);
	if (p_cnfg == NULL){ 
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}

	/* linkage */
	*p_attribute_get = p_cnfg->retried_num_max;
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

static uint8_t R_DLMS_USER_class40_retried_num_max_uint8_t_set(distributor_params_t * p_params, uint8_t * p_attribute_set)
{
	uint8_t 				action_result;
	uint8_t 				push_channel;
	push_config_t 			*p_cnfg;

	uint8_t					i;

	/* Get push setup from application */
	p_cnfg = R_DLMS_USER_GetPushConfig(p_params, &push_channel);
	if (p_cnfg == NULL){ 
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}

	p_cnfg->retried_num = *(uint8_t *)p_attribute_set;

	action_result = R_DLMS_Push_Backup_NumberOfRetry(
		push_channel,
		p_cnfg->retried_num
	);
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

static uint8_t R_DLMS_USER_class40_delay_retry_max_uint16_t_get(distributor_params_t * p_params, uint16_t * p_attribute_get)
{
	uint8_t			*p_alloc;
	uint8_t 		*p_head;
	push_config_t 	*p_cnfg;
	uint8_t 		push_channel;

	uint16_t		number_of_window;
	uint8_t			u8;

	/* Get push setup from application */
	p_cnfg = R_DLMS_USER_GetPushConfig(p_params, &push_channel);
	if (p_cnfg == NULL){ 
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}

	/* linkage */
	*p_attribute_get = p_cnfg->delay_retry_max;
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

static uint8_t R_DLMS_USER_class40_delay_retry_max_uint16_t_set(distributor_params_t * p_params, uint16_t * p_attribute_set)
{
	uint8_t 				action_result;
	uint8_t 				push_channel;
	push_config_t 			*p_cnfg;

	uint8_t					i;

	/* Get push setup from application */
	p_cnfg = R_DLMS_USER_GetPushConfig(p_params, &push_channel);
	if (p_cnfg == NULL){ 
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}

	p_cnfg->delay_retry = *(uint16_t *)p_attribute_set;

	action_result = R_DLMS_Push_Backup_RepetitionDelay(
		push_channel,
		p_cnfg->delay_retry
	);
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

static uint8_t R_DLMS_USER_class40_meth01_int8_t_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	uint8_t 				push_channel;
    push_config_t 			*p_cnfg;
    
	/* Get push setup from application */
	p_cnfg = R_DLMS_USER_GetPushConfig(p_params, &push_channel);
	if (p_cnfg == NULL){ 
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}

	R_DLMS_Push_SetFlag(push_channel);
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/* User code function */
/**********************************************************************************************************************
 * Function Name: send_destination_and_method_attribute03_get      
 * Description  : this is common function to get send_destination_and_method
 * Arguments    : p_params - service parameters
 *                p_attribute_get - attribute get data
 *                channel - number channel need to get     
 * Return Value : void                    
 **********************************************************************************************************************/
static uint8_t send_destination_and_method_attribute03_get(distributor_params_t * p_params,
 														class40_send_destination_and_method_t * p_attribute_get, 
														uint8_t channel)
{
	push_config_t *p_cnfg;

	/* Get push config at channel */
	p_cnfg = R_DLMS_Push_GetConfig(channel);
	if (p_cnfg == NULL)
    {
        return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
    }
	else
	{	
		/* Get transport service */
		p_attribute_get->transport_service = p_cnfg->destination.service;
		/* Get message type */
		p_attribute_get->message = (class40_message_type_t)p_cnfg->destination.message;
		/* Get destination */
		R_DLMS_Push_Convert_DestConfigToString(
			(push_transport_service_t)p_attribute_get->transport_service,
			&p_cnfg->destination.config,
			p_attribute_get->destination.p_content,
			&p_attribute_get->destination.length);
		return VAL_DATA_ACCESS_RESULT_SUCCESS;

	}
	
}
/**********************************************************************************************************************
 * Function Name: send_destination_and_method_attribute03_set      
 * Description  : this is common function to get send_destination_and_method
 * Arguments    : p_params - service parameters
 *                p_attribute_set - attribute set data
 *                channel - number channel need to get     
 * Return Value : void                     
 **********************************************************************************************************************/
 static uint8_t send_destination_and_method_attribute03_set(distributor_params_t * p_params,
 														 class40_send_destination_and_method_t * p_attribute_set,
														 uint8_t channel)
 {
	push_destination_t * p_dest_cfg = &g_push_setup[channel].destination;
	if(p_attribute_set != NULL)
	{
		/* Set transport service */
		p_dest_cfg->service = (push_transport_service_t)p_attribute_set->transport_service;
		/* Set destination */
		R_DLMS_Push_Convert_StringToDestAddr(
			(push_transport_service_t)p_attribute_set->transport_service,
			p_attribute_set->destination.p_content,
			p_attribute_set->destination.length,
			&p_dest_cfg->config);
		/* Set message type */
		p_dest_cfg->message = (push_message_type_t)p_attribute_set->message;
		/* Write new data to storage */
		R_DLMS_Push_Backup_DestinationSetup(channel, p_dest_cfg);
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/**********************************************************************************************************************
 * Function Name: communication_window_attribute04_get      
 * Description  : this is common function to get communication_window
 * Arguments    : p_params - service parameters
 *                p_attribute_get - attribute get data
 *                channel - number channel need to get     
 * Return Value : void                     
 **********************************************************************************************************************/
 static uint8_t communication_window_attribute04_get(distributor_params_t * p_params,
 												  class40_comm_window_array_t * p_attribute_get,
												  uint8_t channel)
 {
	 push_config_t *p_cnfg;
	 uint16_t i;
	 if(p_attribute_get != NULL)
	 {
		/* Get push config at channel */
		p_cnfg = R_DLMS_Push_GetConfig(channel);
		if (p_cnfg->num_of_window == 0)
		{
			p_attribute_get->length = 0;
		}
		else
		{
			/* Pass length of comm window */
			p_attribute_get->length = p_cnfg->num_of_window;
			for (i = 0; i < p_attribute_get->length; i++)
			{
				R_DLMS_RTC_Convert_RTC2DateTime(&p_attribute_get->p_content[i].start_time, &p_cnfg->p_window[i].start);
				R_DLMS_RTC_Convert_RTC2DateTime(&p_attribute_get->p_content[i].end_time, &p_cnfg->p_window[i].end);
			}
		}
	 }
	 else
	 {
		 return VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED;
	 }
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
 }
 /**********************************************************************************************************************
 * Function Name: communication_window_attribute04_set      
 * Description  : this is common function to set communication_window
 * Arguments    : p_params - service parameters
 *                p_attribute_set - attribute set data
 *                channel - number channel need to set    
 * Return Value : void                     
 **********************************************************************************************************************/
 static uint8_t communication_window_attribute04_set(distributor_params_t * p_params,
 												  class40_comm_window_array_t * p_attribute_set,
												  uint8_t channel)
 {
	 push_config_t * p_cnfg;
	 uint16_t i;

	 if(p_attribute_set->length <= PUSH_MAX_WINDOW_SUPPORT)
	 {
		 /* Get push config at channel */
		p_cnfg = R_DLMS_Push_GetConfig(channel);
		p_cnfg->num_of_window = (uint8_t)p_attribute_set->length;
		if (p_attribute_set > 0)
		{
			for (i = 0; i < p_attribute_set->length; i++)
			{
				R_DLMS_RTC_Convert_DateTime2RTC(&p_cnfg->p_window[i].start, &p_attribute_set->p_content[i].start_time);
				R_DLMS_RTC_Convert_DateTime2RTC(&p_cnfg->p_window[i].end, &p_attribute_set->p_content[i].end_time);
			}
		}
		/* Write new data to storage */
		R_DLMS_Push_Backup_CommWin(channel, p_cnfg->p_window, p_cnfg->num_of_window);
	 }
	 else
	 {
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	 }
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
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
* Object name:      Push setup 0
* Object number:    00
* Object obis code: 0.0.25.9.0.255
***********************************************************************************************************/

/*******************************************************************************
* Class ID: 40
* Variable name: g_dlms_ic40_obj00_att02_push_object_list
* Object name: Push setup 0
* Attribute order: 02
* Attribute name: push_object_list
* Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ;
* Group object		: Push
*******************************************************************************/
/*********************************************
 This is array of object definition
 class40_push_object_t
 { 
       uint16_t      class_id;
       FixedString   logical_name;
       int8_t        attribute_index;
       uint16_t      data_index;
 }
* FixedString
* {
*     uint8_t* p_content; 
*     uint16_t length;
* }

 class40_push_object_array_t
 {
       uint8_t* p_content;
       uint16_t length;
 }
 p_content: this is pointer of variable class40_push_object_t[]
*********************************************/

/* Component value of each element array */

/* Element 00 */
const uint8_t g_obj00_att02_logical_name_element00[] = {0, 0, 96, 1, 2, 255};


/* Element 01 */
const uint8_t g_obj00_att02_logical_name_element01[] = {0, 0, 25, 9, 0, 255};


/* Element 02 */
const uint8_t g_obj00_att02_logical_name_element02[] = {0, 0, 1, 0, 0, 255};


/* Element 03 */
const uint8_t g_obj00_att02_logical_name_element03[] = {1, 0, 12, 7, 0, 255};


/* Element 04 */
const uint8_t g_obj00_att02_logical_name_element04[] = {1, 0, 11, 7, 0, 255};


/* Element 05 */
const uint8_t g_obj00_att02_logical_name_element05[] = {1, 0, 91, 7, 0, 255};


/* Element 06 */
const uint8_t g_obj00_att02_logical_name_element06[] = {1, 0, 13, 7, 0, 255};


/* Element 07 */
const uint8_t g_obj00_att02_logical_name_element07[] = {1, 0, 14, 7, 0, 255};


/* Element 08 */
const uint8_t g_obj00_att02_logical_name_element08[] = {1, 0, 9, 7, 0, 255};


/* Element 09 */
const uint8_t g_obj00_att02_logical_name_element09[] = {1, 0, 1, 7, 0, 255};


/* Element 10 */
const uint8_t g_obj00_att02_logical_name_element10[] = {1, 0, 1, 8, 0, 255};


/* Element 11 */
const uint8_t g_obj00_att02_logical_name_element11[] = {1, 0, 9, 8, 0, 255};


/* Element 12 */
const uint8_t g_obj00_att02_logical_name_element12[] = {1, 0, 1, 6, 0, 255};


/* Element array value */
const class40_push_object_t g_dlms_ic40_obj00_push_object_list_array_content[] = 
{
   { 1, { (uint8_t *)&g_obj00_att02_logical_name_element00, 6 }, 2, 0 }, 
   { 40, { (uint8_t *)&g_obj00_att02_logical_name_element01, 6 }, 1, 0 }, 
   { 8, { (uint8_t *)&g_obj00_att02_logical_name_element02, 6 }, 2, 0 }, 
   { 3, { (uint8_t *)&g_obj00_att02_logical_name_element03, 6 }, 2, 0 }, 
   { 3, { (uint8_t *)&g_obj00_att02_logical_name_element04, 6 }, 2, 0 }, 
   { 3, { (uint8_t *)&g_obj00_att02_logical_name_element05, 6 }, 2, 0 }, 
   { 3, { (uint8_t *)&g_obj00_att02_logical_name_element06, 6 }, 2, 0 }, 
   { 3, { (uint8_t *)&g_obj00_att02_logical_name_element07, 6 }, 2, 0 }, 
   { 3, { (uint8_t *)&g_obj00_att02_logical_name_element08, 6 }, 2, 0 }, 
   { 3, { (uint8_t *)&g_obj00_att02_logical_name_element09, 6 }, 2, 0 }, 
   { 3, { (uint8_t *)&g_obj00_att02_logical_name_element10, 6 }, 2, 0 }, 
   { 3, { (uint8_t *)&g_obj00_att02_logical_name_element11, 6 }, 2, 0 }, 
   { 4, { (uint8_t *)&g_obj00_att02_logical_name_element12, 6 }, 2, 0 }
};
/* Declare for variable of push_object_list (class - 40, atrribute - 02)*/
const class40_push_object_array_t g_dlms_ic40_obj00_att02_push_object_list  = { (class40_push_object_t *)&g_dlms_ic40_obj00_push_object_list_array_content, 13 };


/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj00_att03_get
* Description   : Object name       : Push setup 0
*                 Object index      : 00
*                 Class             : 40
*                 Attribute order   : 03
*                 Attribute name    : send_destination_and_method
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class40_send_destination_and_method_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj00_att03_get(distributor_params_t * p_params, class40_send_destination_and_method_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	 This is structure of send destinationa and methods, please set following  this.
	 class40_send_destination_and_method_t
	 {
	         class40_transport_service_t    transport_service;
	         OctetString                    destination;
	         class40_message_type_t         message;
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
	//class40_transport_service_t transport_service_link = CLASS_40_TRANSPORT_SERVICE_HDLC;[generated template code]
	//uint8_t destination_content_link[] = { 0x00 };[generated template code]
	//class40_message_type_t message_link = CLASS_40_MESSAGE_TYPE_A_XDR_ENC_xDLMS_APDU;[generated template code]

	/* Set data link to p_get_attribute */
	//p_attribute_get->transport_service = transport_service_link;[generated template code]
	//memcpy(p_attribute_get->destination.p_content, &destination_content_link, 1);[generated template code]
	//p_attribute_get->destination.length = 1;[generated template code]
	//p_attribute_get->message = message_link;[generated template code]

	/* Start user code here */
	return send_destination_and_method_attribute03_get(p_params, p_attribute_get, 0);//channel = 0;
	/* End user code here */

	/* Return result of this, please check again result value */
	//return result;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj00_att03_set
* Description   : Object name       : Push setup 0
*                 Object index      : 00
*                 Class             : 40
*                 Attribute order   : 03
*                 Attribute name    : send_destination_and_method
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class40_send_destination_and_method_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj00_att03_set(distributor_params_t * p_params, class40_send_destination_and_method_t * p_attribute_set)
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
	 This is structure of send destinationa and methods, please set following  this.
	 class40_send_destination_and_method_t
	 {
	         class40_transport_service_t    transport_service;
	         OctetString                    destination;
	         class40_message_type_t         message;
	 };
	*********************************************/


	
	/* Start user code here */
	return send_destination_and_method_attribute03_set(p_params, p_attribute_set, 0);//channel = 0
	/* End user code here */
	/* Return result of this, please check again result value */
	//return result;
}

/* Please update your array size following your setting change by asigning under variable */
/* For communication_window */
const uint16_t r_dlms_ic40_obj00_att04_array_length = PUSH_MAX_WINDOW_SUPPORT;
/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj00_att04_get
* Description   : Object name       : Push setup 0
*                 Object index      : 00
*                 Class             : 40
*                 Attribute order   : 04
*                 Attribute name    : communication_window
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class40_comm_window_array_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj00_att04_get(distributor_params_t * p_params, class40_comm_window_array_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
	/*
	 * Not implemented(default), r_dlms_ic40_obj00_att04_array_length is assigned 0, response is array - 0 element(0100)
	 * Implemented, but r_dlms_ic40_obj00_att04_array_length is assigned 0, response is array - 0 element(0100)
	 */


	/*********************************************
	 This is element definition
	 class40_comm_window_t
	 {
	     date_time_t start_time;
	     date_time_t end_time;
	}

	 This is array definition
	 class40_comm_window_array_t
	 {
	       uint8_t* p_content;
	       uint16_t length;
	 }
	 p_content: this is pointer of variable class40_comm_window_t[]
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


	/* Element 00 */
	//date_time_t start_time_link_element00 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};[generated template code]
	//date_time_t end_time_link_element00 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};[generated template code]


	/* Set length for this array */
	//p_attribute_get->length = r_dlms_ic40_obj04_att04_array_length;[generated template code]

	/* Set value for element at 0 */
	//p_attribute_get->p_content[0].start_time = start_time_link_element00;[generated template code]
	//p_attribute_get->p_content[0].end_time = end_time_link_element00;[generated template code]



	/* Start user code here */
	return communication_window_attribute04_get(p_params, p_attribute_get, 0);//channel = 0
	/* End user code here */

	/* Return result of this, please check again result value */
	//return result;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj00_att04_set
* Description   : Object name       : Push setup 0
*                 Object index      : 00
*                 Class             : 40
*                 Attribute order   : 04
*                 Attribute name    : communication_window
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class40_comm_window_array_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj00_att04_set(distributor_params_t * p_params, class40_comm_window_array_t * p_attribute_set)
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
	 This is element definition
	 class40_comm_window_t
	 {
	     date_time_t start_time;
	     date_time_t end_time;
	}

	 This is array definition
	 class40_comm_window_array_t
	 {
	       uint8_t* p_content;
	       uint16_t length;
	 }
	 p_content: this is pointer of variable class40_comm_window_t[]
	*********************************************/


	
	/* Start user code here */
	return communication_window_attribute04_set(p_params, p_attribute_set, 0);//channel = 0
	/* End user code here */
	/* Return result of this, please check again result value */
	//return result;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj00_att05_get
* Description   : Object name       : Push setup 0
*                 Object index      : 00
*                 Class             : 40
*                 Attribute order   : 05
*                 Attribute name    : randomisation_start_interval
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint16_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj00_att05_get(distributor_params_t * p_params, uint16_t * p_attribute_get)
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
	//uint16_t link_data = 0;[generated template code]
	/* Set value */
	//*((uint16_t *)p_attribute_get) = link_data;[generated template code]

	/* Start user code here */
	*p_attribute_get = g_push_setup[0].delay_start_max;//channel = 0;
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj00_att05_set
* Description   : Object name       : Push setup 0
*                 Object index      : 00
*                 Class             : 40
*                 Attribute order   : 05
*                 Attribute name    : randomisation_start_interval
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint16_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj00_att05_set(distributor_params_t * p_params, uint16_t * p_attribute_set)
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
	Data type:uint16_t(long-unsigned)
	*********************************************/


	
	/* Start user code here */
	if(R_DLMS_Push_Set_RandomisationStartInterval(0, *p_attribute_set) != RLT_SUCCESS)//channel = 0
	{	
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_SUCCESS;
	}
	/* End user code here */
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj00_att06_get
* Description   : Object name       : Push setup 0
*                 Object index      : 00
*                 Class             : 40
*                 Attribute order   : 06
*                 Attribute name    : number_of_retries
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint8_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj00_att06_get(distributor_params_t * p_params, uint8_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint8_t(unsigned)
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
	//uint8_t link_data = 0;[generated template code]
	/* Set value */
	//*((uint8_t *)p_attribute_get) = link_data;[generated template code]

	/* Start user code here */
	*p_attribute_get = g_push_setup[0].retried_num_max;//channel = 0
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj00_att06_set
* Description   : Object name       : Push setup 0
*                 Object index      : 00
*                 Class             : 40
*                 Attribute order   : 06
*                 Attribute name    : number_of_retries
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint8_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj00_att06_set(distributor_params_t * p_params, uint8_t * p_attribute_set)
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
	Data type:uint8_t(unsigned)
	*********************************************/


	
	/* Start user code here */
	if(R_DLMS_Push_Set_NumberOfRetry(0, *p_attribute_set) != RLT_SUCCESS)//channel = 0
	{	
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_SUCCESS;
	}
	/* End user code here */
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj00_att07_get
* Description   : Object name       : Push setup 0
*                 Object index      : 00
*                 Class             : 40
*                 Attribute order   : 07
*                 Attribute name    : repetition_delay
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint16_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj00_att07_get(distributor_params_t * p_params, uint16_t * p_attribute_get)
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
	//uint16_t link_data = 0;[generated template code]
	/* Set value */
	//*((uint16_t *)p_attribute_get) = link_data;[generated template code]

	/* Start user code here */
	*p_attribute_get = g_push_setup[0].delay_retry_max;//Channel = 0
	/* End user code here */

	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj00_att07_set
* Description   : Object name       : Push setup 0
*                 Object index      : 00
*                 Class             : 40
*                 Attribute order   : 07
*                 Attribute name    : repetition_delay
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint16_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj00_att07_set(distributor_params_t * p_params, uint16_t * p_attribute_set)
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
	Data type:uint16_t(long-unsigned)
	*********************************************/


	
	/* Start user code here */
	if(R_DLMS_Push_Set_RepetitionDelay(0, *p_attribute_set) != RLT_SUCCESS)//channel = 0
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_SUCCESS;
	}
	/* End user code here */
}


/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj00_meth01_action
* Description   : Object name       : Push setup 0
*                 Object index      : 00
*                 Class             : 40
*                 Method order      : 01
*                 Method name       : push
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj00_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Activates the push process leading to the elaboration and the sending of
	*  the push data taking into account the values of the attributes defined 
	*  in the given instance of this IC.
	* p_data_from_client ::= integer(0)->NOT REQUIREMENT.
	*************************************************************************/


	/**************************************************************
	This is enum of return result value. 
	Default is VAL_ACTION_RESULT_OTHER_REASON
	* typedef enum																															 *
	* {																																		 *
	* 	VAL_ACTION_RESULT_SUCCESS 						= 0   ,																				 *
	* 	VAL_ACTION_RESULT_HARDWARE_FAULT 				= 1   ,																				 *
	* 	VAL_ACTION_RESULT_TEMPORARY_FAILURE 			= 2   ,																				 *
	* 	VAL_ACTION_RESULT_READ_WRITE_DENIED 			= 3   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNDEFINED 				= 4   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNAVAILABLE 			= 11  ,																				 *
	* 	VAL_ACTION_RESULT_TYPE_UNMATCHED 				= 12  ,																				 *
	* 	VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED 		= 13  ,																				 *
	* 	VAL_ACTION_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14  ,																				 *
	* 	VAL_ACTION_RESULT_LONG_ACTION_ABORTED 			= 15  ,																				 *
	* 	VAL_ACTION_RESULT_NO_LONG_ACTION_IN_PROGRESS 	= 16  ,																				 *
	* 	VAL_ACTION_RESULT_OTHER_REASON 					= 250 ,																				 *
	* } ActionResult_Value;																													 *
	
	*****************************************************************/
	/* Start user code here */
	R_DLMS_Push_SetFlag(0);//Channel = 0
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
	/* End user code here */
}


/***********************************************************************************************************
* Object name:      Push setup 1
* Object number:    01
* Object obis code: 0.1.25.9.0.255
***********************************************************************************************************/

/*******************************************************************************
* Class ID: 40
* Variable name: g_dlms_ic40_obj01_att02_push_object_list
* Object name: Push setup 1
* Attribute order: 02
* Attribute name: push_object_list
* Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ;
* Group object		: Push
*******************************************************************************/
/*********************************************
 This is array of object definition
 class40_push_object_t
 { 
       uint16_t      class_id;
       FixedString   logical_name;
       int8_t        attribute_index;
       uint16_t      data_index;
 }
* FixedString
* {
*     uint8_t* p_content; 
*     uint16_t length;
* }

 class40_push_object_array_t
 {
       uint8_t* p_content;
       uint16_t length;
 }
 p_content: this is pointer of variable class40_push_object_t[]
*********************************************/

/* Component value of each element array */

/* Element 00 */
const uint8_t g_obj01_att02_logical_name_element00[] = {0, 0, 1, 0, 0, 255};


/* Element 01 */
const uint8_t g_obj01_att02_logical_name_element01[] = {0, 1, 25, 9, 0, 255};


/* Element 02 */
const uint8_t g_obj01_att02_logical_name_element02[] = {0, 0, 96, 13, 1, 255};


/* Element array value */
const class40_push_object_t g_dlms_ic40_obj01_push_object_list_array_content[] = 
{
   { 8, { (uint8_t *)&g_obj01_att02_logical_name_element00, 6 }, 2, 0 }, 
   { 40, { (uint8_t *)&g_obj01_att02_logical_name_element01, 6 }, 1, 0 }, 
   { 1, { (uint8_t *)&g_obj01_att02_logical_name_element02, 6 }, 2, 0 }
};
/* Declare for variable of push_object_list (class - 40, atrribute - 02)*/
const class40_push_object_array_t g_dlms_ic40_obj01_att02_push_object_list  = { (class40_push_object_t *)&g_dlms_ic40_obj01_push_object_list_array_content, 3 };


/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj01_att03_get
* Description   : Object name       : Push setup 1
*                 Object index      : 01
*                 Class             : 40
*                 Attribute order   : 03
*                 Attribute name    : send_destination_and_method
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class40_send_destination_and_method_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj01_att03_get(distributor_params_t * p_params, class40_send_destination_and_method_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	 This is structure of send destinationa and methods, please set following  this.
	 class40_send_destination_and_method_t
	 {
	         class40_transport_service_t    transport_service;
	         OctetString                    destination;
	         class40_message_type_t         message;
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
	//class40_transport_service_t transport_service_link = CLASS_40_TRANSPORT_SERVICE_HDLC;[generated template code]
	//uint8_t destination_content_link[] = { 0x00 };[generated template code]
	//class40_message_type_t message_link = CLASS_40_MESSAGE_TYPE_A_XDR_ENC_xDLMS_APDU;[generated template code]

	/* Set data link to p_get_attribute */
	//p_attribute_get->transport_service = transport_service_link;[generated template code]
	//memcpy(p_attribute_get->destination.p_content, &destination_content_link, 1);[generated template code]
	//p_attribute_get->destination.length = 1;[generated template code]
	//p_attribute_get->message = message_link;[generated template code]

	/* Start user code here */
	return send_destination_and_method_attribute03_get(p_params, p_attribute_get, 1);//channel = 1;
	/* End user code here */

	/* Return result of this, please check again result value */
	//return result;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj01_att03_set
* Description   : Object name       : Push setup 1
*                 Object index      : 01
*                 Class             : 40
*                 Attribute order   : 03
*                 Attribute name    : send_destination_and_method
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class40_send_destination_and_method_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj01_att03_set(distributor_params_t * p_params, class40_send_destination_and_method_t * p_attribute_set)
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
	 This is structure of send destinationa and methods, please set following  this.
	 class40_send_destination_and_method_t
	 {
	         class40_transport_service_t    transport_service;
	         OctetString                    destination;
	         class40_message_type_t         message;
	 };
	*********************************************/


	
	/* Start user code here */
	return send_destination_and_method_attribute03_set(p_params, p_attribute_set, 1);//Channel = 1
	/* End user code here */
	/* Return result of this, please check again result value */
	//return result;
}

/* Please update your array size following your setting change by asigning under variable */
/* For communication_window */
const uint16_t r_dlms_ic40_obj01_att04_array_length = PUSH_MAX_WINDOW_SUPPORT;
/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj01_att04_get
* Description   : Object name       : Push setup 1
*                 Object index      : 01
*                 Class             : 40
*                 Attribute order   : 04
*                 Attribute name    : communication_window
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class40_comm_window_array_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj01_att04_get(distributor_params_t * p_params, class40_comm_window_array_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
	/*
	 * Not implemented(default), r_dlms_ic40_obj01_att04_array_length is assigned 0, response is array - 0 element(0100)
	 * Implemented, but r_dlms_ic40_obj01_att04_array_length is assigned 0, response is array - 0 element(0100)
	 */


	/*********************************************
	 This is element definition
	 class40_comm_window_t
	 {
	     date_time_t start_time;
	     date_time_t end_time;
	}

	 This is array definition
	 class40_comm_window_array_t
	 {
	       uint8_t* p_content;
	       uint16_t length;
	 }
	 p_content: this is pointer of variable class40_comm_window_t[]
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


	/* Element 00 */
	//date_time_t start_time_link_element00 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};[generated template code]
	//date_time_t end_time_link_element00 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};[generated template code]


	/* Set length for this array */
	//p_attribute_get->length = r_dlms_ic40_obj04_att04_array_length;[generated template code]

	/* Set value for element at 0 */
	//p_attribute_get->p_content[0].start_time = start_time_link_element00;[generated template code]
	//p_attribute_get->p_content[0].end_time = end_time_link_element00;[generated template code]

	/* Start user code here */
	return communication_window_attribute04_get(p_params, p_attribute_get, 1);//channel = 1
	/* End user code here */

	/* Return result of this, please check again result value */
	//return result;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj01_att04_set
* Description   : Object name       : Push setup 1
*                 Object index      : 01
*                 Class             : 40
*                 Attribute order   : 04
*                 Attribute name    : communication_window
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class40_comm_window_array_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj01_att04_set(distributor_params_t * p_params, class40_comm_window_array_t * p_attribute_set)
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
	 This is element definition
	 class40_comm_window_t
	 {
	     date_time_t start_time;
	     date_time_t end_time;
	}

	 This is array definition
	 class40_comm_window_array_t
	 {
	       uint8_t* p_content;
	       uint16_t length;
	 }
	 p_content: this is pointer of variable class40_comm_window_t[]
	*********************************************/


	
	/* Start user code here */
	return communication_window_attribute04_set(p_params, p_attribute_set, 1);//channel = 1
	/* End user code here */
	/* Return result of this, please check again result value */
	//return result;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj01_att05_get
* Description   : Object name       : Push setup 1
*                 Object index      : 01
*                 Class             : 40
*                 Attribute order   : 05
*                 Attribute name    : randomisation_start_interval
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint16_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj01_att05_get(distributor_params_t * p_params, uint16_t * p_attribute_get)
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
	//uint16_t link_data = 0;[generated template code]
	/* Set value */
	//*((uint16_t *)p_attribute_get) = link_data;[generated template code]

	/* Start user code here */
	*p_attribute_get = g_push_setup[1].delay_start_max;//channel = 1;
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj01_att05_set
* Description   : Object name       : Push setup 1
*                 Object index      : 01
*                 Class             : 40
*                 Attribute order   : 05
*                 Attribute name    : randomisation_start_interval
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint16_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj01_att05_set(distributor_params_t * p_params, uint16_t * p_attribute_set)
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
	Data type:uint16_t(long-unsigned)
	*********************************************/


	
	/* Start user code here */
	if(R_DLMS_Push_Set_RandomisationStartInterval(1, *p_attribute_set) != RLT_SUCCESS)//channel = 1
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_SUCCESS;
	}
	/* End user code here */
	/* Return result of this, please check again result value */
	//return result;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj01_att06_get
* Description   : Object name       : Push setup 1
*                 Object index      : 01
*                 Class             : 40
*                 Attribute order   : 06
*                 Attribute name    : number_of_retries
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint8_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj01_att06_get(distributor_params_t * p_params, uint8_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint8_t(unsigned)
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
	//uint8_t link_data = 0;[generated template code]
	/* Set value */
	//*((uint8_t *)p_attribute_get) = link_data;[generated template code]

	/* Start user code here */
	*p_attribute_get = g_push_setup[1].retried_num_max;//channel = 1
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj01_att06_set
* Description   : Object name       : Push setup 1
*                 Object index      : 01
*                 Class             : 40
*                 Attribute order   : 06
*                 Attribute name    : number_of_retries
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint8_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj01_att06_set(distributor_params_t * p_params, uint8_t * p_attribute_set)
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
	Data type:uint8_t(unsigned)
	*********************************************/


	
	/* Start user code here */
	if(R_DLMS_Push_Set_NumberOfRetry(1, *p_attribute_set) != RLT_SUCCESS)//channel = 1
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_SUCCESS;
	}
	/* End user code here */
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj01_att07_get
* Description   : Object name       : Push setup 1
*                 Object index      : 01
*                 Class             : 40
*                 Attribute order   : 07
*                 Attribute name    : repetition_delay
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint16_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj01_att07_get(distributor_params_t * p_params, uint16_t * p_attribute_get)
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
	//uint16_t link_data = 0;[generated template code]
	/* Set value */
	//*((uint16_t *)p_attribute_get) = link_data;[generated template code]

	/* Start user code here */
	*p_attribute_get = g_push_setup[1].delay_retry_max;//Channel = 1
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj01_att07_set
* Description   : Object name       : Push setup 1
*                 Object index      : 01
*                 Class             : 40
*                 Attribute order   : 07
*                 Attribute name    : repetition_delay
*                 Association access: {2, Utility Setting}; {3, Push}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint16_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj01_att07_set(distributor_params_t * p_params, uint16_t * p_attribute_set)
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
	Data type:uint16_t(long-unsigned)
	*********************************************/


	
	/* Start user code here */
	if(R_DLMS_Push_Set_RepetitionDelay(1, *p_attribute_set) != RLT_SUCCESS)//channel = 1
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_SUCCESS;
	}
	/* End user code here */
}


/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj01_meth01_action
* Description   : Object name       : Push setup 1
*                 Object index      : 01
*                 Class             : 40
*                 Method order      : 01
*                 Method name       : push
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj01_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Activates the push process leading to the elaboration and the sending of
	*  the push data taking into account the values of the attributes defined 
	*  in the given instance of this IC.
	* p_data_from_client ::= integer(0)->NOT REQUIREMENT.
	*************************************************************************/


	/**************************************************************
	This is enum of return result value. 
	Default is VAL_ACTION_RESULT_OTHER_REASON
	* typedef enum																															 *
	* {																																		 *
	* 	VAL_ACTION_RESULT_SUCCESS 						= 0   ,																				 *
	* 	VAL_ACTION_RESULT_HARDWARE_FAULT 				= 1   ,																				 *
	* 	VAL_ACTION_RESULT_TEMPORARY_FAILURE 			= 2   ,																				 *
	* 	VAL_ACTION_RESULT_READ_WRITE_DENIED 			= 3   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNDEFINED 				= 4   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNAVAILABLE 			= 11  ,																				 *
	* 	VAL_ACTION_RESULT_TYPE_UNMATCHED 				= 12  ,																				 *
	* 	VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED 		= 13  ,																				 *
	* 	VAL_ACTION_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14  ,																				 *
	* 	VAL_ACTION_RESULT_LONG_ACTION_ABORTED 			= 15  ,																				 *
	* 	VAL_ACTION_RESULT_NO_LONG_ACTION_IN_PROGRESS 	= 16  ,																				 *
	* 	VAL_ACTION_RESULT_OTHER_REASON 					= 250 ,																				 *
	* } ActionResult_Value;																													 *
	
	*****************************************************************/
	/* Start user code here */
	R_DLMS_Push_SetFlag(1);//Channel = 1

	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}


/***********************************************************************************************************
* Object name:      Push setup 2
* Object number:    02
* Object obis code: 0.2.25.9.0.255
***********************************************************************************************************/

/*******************************************************************************
* Class ID: 40
* Variable name: g_dlms_ic40_obj02_att02_push_object_list
* Object name: Push setup 2
* Attribute order: 02
* Attribute name: push_object_list
* Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ;
* Group object		: Push
*******************************************************************************/
/*********************************************
 This is array of object definition
 class40_push_object_t
 { 
       uint16_t      class_id;
       FixedString   logical_name;
       int8_t        attribute_index;
       uint16_t      data_index;
 }
* FixedString
* {
*     uint8_t* p_content; 
*     uint16_t length;
* }

 class40_push_object_array_t
 {
       uint8_t* p_content;
       uint16_t length;
 }
 p_content: this is pointer of variable class40_push_object_t[]
*********************************************/

/* Component value of each element array */

/* Element 00 */
const uint8_t g_obj02_att02_logical_name_element00[] = {0, 0, 96, 1, 2, 255};


/* Element 01 */
const uint8_t g_obj02_att02_logical_name_element01[] = {0, 2, 25, 9, 0, 255};


/* Element 02 */
const uint8_t g_obj02_att02_logical_name_element02[] = {0, 0, 1, 0, 0, 255};


/* Element 03 */
const uint8_t g_obj02_att02_logical_name_element03[] = {0, 0, 96, 13, 2, 255};


/* Element array value */
const class40_push_object_t g_dlms_ic40_obj02_push_object_list_array_content[] = 
{
   { 1, { (uint8_t *)&g_obj02_att02_logical_name_element00, 6 }, 2, 0 }, 
   { 40, { (uint8_t *)&g_obj02_att02_logical_name_element01, 6 }, 1, 0 }, 
   { 8, { (uint8_t *)&g_obj02_att02_logical_name_element02, 6 }, 2, 0 }, 
   { 1, { (uint8_t *)&g_obj02_att02_logical_name_element03, 6 }, 2, 0 }
};
/* Declare for variable of push_object_list (class - 40, atrribute - 02)*/
const class40_push_object_array_t g_dlms_ic40_obj02_att02_push_object_list  = { (class40_push_object_t *)&g_dlms_ic40_obj02_push_object_list_array_content, 4 };


/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj02_att03_get
* Description   : Object name       : Push setup 2
*                 Object index      : 02
*                 Class             : 40
*                 Attribute order   : 03
*                 Attribute name    : send_destination_and_method
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class40_send_destination_and_method_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj02_att03_get(distributor_params_t * p_params, class40_send_destination_and_method_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	 This is structure of send destinationa and methods, please set following  this.
	 class40_send_destination_and_method_t
	 {
	         class40_transport_service_t    transport_service;
	         OctetString                    destination;
	         class40_message_type_t         message;
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
	//class40_transport_service_t transport_service_link = CLASS_40_TRANSPORT_SERVICE_HDLC;[generated template code]
	//uint8_t destination_content_link[] = { 0x00 };[generated template code]
	//class40_message_type_t message_link = CLASS_40_MESSAGE_TYPE_A_XDR_ENC_xDLMS_APDU;[generated template code]

	/* Set data link to p_get_attribute */
	//p_attribute_get->transport_service = transport_service_link;[generated template code]
	//memcpy(p_attribute_get->destination.p_content, &destination_content_link, 1);[generated template code]
	//p_attribute_get->destination.length = 1;[generated template code]
	//p_attribute_get->message = message_link;[generated template code]

	/* Start user code here */
	return send_destination_and_method_attribute03_get(p_params, p_attribute_get, 2);//channel = 2;
	/* End user code here */

	/* Return result of this, please check again result value */
	//return result;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj02_att03_set
* Description   : Object name       : Push setup 2
*                 Object index      : 02
*                 Class             : 40
*                 Attribute order   : 03
*                 Attribute name    : send_destination_and_method
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class40_send_destination_and_method_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj02_att03_set(distributor_params_t * p_params, class40_send_destination_and_method_t * p_attribute_set)
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
	 This is structure of send destinationa and methods, please set following  this.
	 class40_send_destination_and_method_t
	 {
	         class40_transport_service_t    transport_service;
	         OctetString                    destination;
	         class40_message_type_t         message;
	 };
	*********************************************/


	
	/* Start user code here */
	return send_destination_and_method_attribute03_set(p_params, p_attribute_set, 2);//Channel = 2
	/* End user code here */
	/* Return result of this, please check again result value */
	//return result;
}

/* Please update your array size following your setting change by asigning under variable */
/* For communication_window */
const uint16_t r_dlms_ic40_obj02_att04_array_length = PUSH_MAX_WINDOW_SUPPORT;
/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj02_att04_get
* Description   : Object name       : Push setup 2
*                 Object index      : 02
*                 Class             : 40
*                 Attribute order   : 04
*                 Attribute name    : communication_window
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class40_comm_window_array_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj02_att04_get(distributor_params_t * p_params, class40_comm_window_array_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
	/*
	 * Not implemented(default), r_dlms_ic40_obj02_att04_array_length is assigned 0, response is array - 0 element(0100)
	 * Implemented, but r_dlms_ic40_obj02_att04_array_length is assigned 0, response is array - 0 element(0100)
	 */


	/*********************************************
	 This is element definition
	 class40_comm_window_t
	 {
	     date_time_t start_time;
	     date_time_t end_time;
	}

	 This is array definition
	 class40_comm_window_array_t
	 {
	       uint8_t* p_content;
	       uint16_t length;
	 }
	 p_content: this is pointer of variable class40_comm_window_t[]
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


	/* Element 00 */
	//date_time_t start_time_link_element00 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};[generated template code]
	//date_time_t end_time_link_element00 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};[generated template code]


	/* Set length for this array */
	//p_attribute_get->length = r_dlms_ic40_obj04_att04_array_length;[generated template code]

	/* Set value for element at 0 */
	//p_attribute_get->p_content[0].start_time = start_time_link_element00;[generated template code]
	//p_attribute_get->p_content[0].end_time = end_time_link_element00;[generated template code]

	/* Start user code here */
	return communication_window_attribute04_get(p_params, p_attribute_get, 2);//channel = 2
	/* End user code here */

	/* Return result of this, please check again result value */
	//return result;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj02_att04_set
* Description   : Object name       : Push setup 2
*                 Object index      : 02
*                 Class             : 40
*                 Attribute order   : 04
*                 Attribute name    : communication_window
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class40_comm_window_array_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj02_att04_set(distributor_params_t * p_params, class40_comm_window_array_t * p_attribute_set)
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
	 This is element definition
	 class40_comm_window_t
	 {
	     date_time_t start_time;
	     date_time_t end_time;
	}

	 This is array definition
	 class40_comm_window_array_t
	 {
	       uint8_t* p_content;
	       uint16_t length;
	 }
	 p_content: this is pointer of variable class40_comm_window_t[]
	*********************************************/


	
	/* Start user code here */
	return communication_window_attribute04_set(p_params, p_attribute_set, 2);//channel = 2
	/* End user code here */
	/* Return result of this, please check again result value */
	//return result;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj02_att05_get
* Description   : Object name       : Push setup 2
*                 Object index      : 02
*                 Class             : 40
*                 Attribute order   : 05
*                 Attribute name    : randomisation_start_interval
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint16_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj02_att05_get(distributor_params_t * p_params, uint16_t * p_attribute_get)
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
	//uint16_t link_data = 0;[generated template code]
	/* Set value */
	//*((uint16_t *)p_attribute_get) = link_data;[generated template code]

	/* Start user code here */
	*p_attribute_get = g_push_setup[2].delay_start_max;//channel = 2;
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj02_att05_set
* Description   : Object name       : Push setup 2
*                 Object index      : 02
*                 Class             : 40
*                 Attribute order   : 05
*                 Attribute name    : randomisation_start_interval
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint16_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj02_att05_set(distributor_params_t * p_params, uint16_t * p_attribute_set)
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
	Data type:uint16_t(long-unsigned)
	*********************************************/


	
	/* Start user code here */
	if(R_DLMS_Push_Set_RandomisationStartInterval(2, *p_attribute_set) != RLT_SUCCESS)//channel = 2
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_SUCCESS;
	}
	/* End user code here */
	/* Return result of this, please check again result value */
	//return result;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj02_att06_get
* Description   : Object name       : Push setup 2
*                 Object index      : 02
*                 Class             : 40
*                 Attribute order   : 06
*                 Attribute name    : number_of_retries
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint8_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj02_att06_get(distributor_params_t * p_params, uint8_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint8_t(unsigned)
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
	//uint8_t link_data = 0;[generated template code]
	/* Set value */
	//*((uint8_t *)p_attribute_get) = link_data;[generated template code]

	/* Start user code here */
	*p_attribute_get = g_push_setup[2].retried_num_max;//channel = 2
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj02_att06_set
* Description   : Object name       : Push setup 2
*                 Object index      : 02
*                 Class             : 40
*                 Attribute order   : 06
*                 Attribute name    : number_of_retries
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint8_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj02_att06_set(distributor_params_t * p_params, uint8_t * p_attribute_set)
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
	Data type:uint8_t(unsigned)
	*********************************************/


	
	/* Start user code here */
	if(R_DLMS_Push_Set_NumberOfRetry(2, *p_attribute_set) != RLT_SUCCESS)//channel = 2
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_SUCCESS;
	}
	/* End user code here */
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj02_att07_get
* Description   : Object name       : Push setup 2
*                 Object index      : 02
*                 Class             : 40
*                 Attribute order   : 07
*                 Attribute name    : repetition_delay
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint16_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj02_att07_get(distributor_params_t * p_params, uint16_t * p_attribute_get)
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
	//uint16_t link_data = 0;[generated template code]
	/* Set value */
	//*((uint16_t *)p_attribute_get) = link_data;[generated template code]

	/* Start user code here */
	*p_attribute_get = g_push_setup[2].delay_retry_max;//Channel = 2
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj02_att07_set
* Description   : Object name       : Push setup 2
*                 Object index      : 02
*                 Class             : 40
*                 Attribute order   : 07
*                 Attribute name    : repetition_delay
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint16_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj02_att07_set(distributor_params_t * p_params, uint16_t * p_attribute_set)
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
	Data type:uint16_t(long-unsigned)
	*********************************************/


	
	/* Start user code here */
	if(R_DLMS_Push_Set_RepetitionDelay(2, *p_attribute_set))//channel = 2
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_SUCCESS;
	}
	/* End user code here */
}


/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj02_meth01_action
* Description   : Object name       : Push setup 2
*                 Object index      : 02
*                 Class             : 40
*                 Method order      : 01
*                 Method name       : push
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj02_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Activates the push process leading to the elaboration and the sending of
	*  the push data taking into account the values of the attributes defined 
	*  in the given instance of this IC.
	* p_data_from_client ::= integer(0)->NOT REQUIREMENT.
	*************************************************************************/


	/**************************************************************
	This is enum of return result value. 
	Default is VAL_ACTION_RESULT_OTHER_REASON
	* typedef enum																															 *
	* {																																		 *
	* 	VAL_ACTION_RESULT_SUCCESS 						= 0   ,																				 *
	* 	VAL_ACTION_RESULT_HARDWARE_FAULT 				= 1   ,																				 *
	* 	VAL_ACTION_RESULT_TEMPORARY_FAILURE 			= 2   ,																				 *
	* 	VAL_ACTION_RESULT_READ_WRITE_DENIED 			= 3   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNDEFINED 				= 4   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNAVAILABLE 			= 11  ,																				 *
	* 	VAL_ACTION_RESULT_TYPE_UNMATCHED 				= 12  ,																				 *
	* 	VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED 		= 13  ,																				 *
	* 	VAL_ACTION_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14  ,																				 *
	* 	VAL_ACTION_RESULT_LONG_ACTION_ABORTED 			= 15  ,																				 *
	* 	VAL_ACTION_RESULT_NO_LONG_ACTION_IN_PROGRESS 	= 16  ,																				 *
	* 	VAL_ACTION_RESULT_OTHER_REASON 					= 250 ,																				 *
	* } ActionResult_Value;																													 *
	
	*****************************************************************/
	/* Start user code here */
	R_DLMS_Push_SetFlag(2);//Channel = 2
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}


/***********************************************************************************************************
* Object name:      Push setup 3
* Object number:    03
* Object obis code: 0.3.25.9.0.255
***********************************************************************************************************/

/*******************************************************************************
* Class ID: 40
* Variable name: g_dlms_ic40_obj03_att02_push_object_list
* Object name: Push setup 3
* Attribute order: 02
* Attribute name: push_object_list
* Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ;
* Group object		: Push
*******************************************************************************/
/*********************************************
 This is array of object definition
 class40_push_object_t
 { 
       uint16_t      class_id;
       FixedString   logical_name;
       int8_t        attribute_index;
       uint16_t      data_index;
 }
* FixedString
* {
*     uint8_t* p_content; 
*     uint16_t length;
* }

 class40_push_object_array_t
 {
       uint8_t* p_content;
       uint16_t length;
 }
 p_content: this is pointer of variable class40_push_object_t[]
*********************************************/

/* Component value of each element array */

/* Element 00 */
const uint8_t g_obj03_att02_logical_name_element00[] = {0, 0, 1, 0, 0, 255};


/* Element 01 */
const uint8_t g_obj03_att02_logical_name_element01[] = {0, 3, 25, 9, 0, 255};


/* Element 02 */
const uint8_t g_obj03_att02_logical_name_element02[] = {1, 0, 1, 9, 0, 255};


/* Element 03 */
const uint8_t g_obj03_att02_logical_name_element03[] = {1, 0, 31, 7, 0, 255};


/* Element 04 */
const uint8_t g_obj03_att02_logical_name_element04[] = {1, 0, 32, 7, 0, 255};


/* Element 05 */
const uint8_t g_obj03_att02_logical_name_element05[] = {1, 0, 33, 7, 0, 255};


/* Element 06 */
const uint8_t g_obj03_att02_logical_name_element06[] = {1, 0, 9, 7, 0, 255};


/* Element 07 */
const uint8_t g_obj03_att02_logical_name_element07[] = {1, 0, 1, 7, 0, 255};


/* Element array value */
const class40_push_object_t g_dlms_ic40_obj03_push_object_list_array_content[] = 
{
   { 8, { (uint8_t *)&g_obj03_att02_logical_name_element00, 6 }, 2, 0 }, 
   { 40, { (uint8_t *)&g_obj03_att02_logical_name_element01, 6 }, 1, 0 }, 
   { 3, { (uint8_t *)&g_obj03_att02_logical_name_element02, 6 }, 2, 0 }, 
   { 3, { (uint8_t *)&g_obj03_att02_logical_name_element03, 6 }, 2, 0 }, 
   { 3, { (uint8_t *)&g_obj03_att02_logical_name_element04, 6 }, 2, 0 }, 
   { 3, { (uint8_t *)&g_obj03_att02_logical_name_element05, 6 }, 2, 0 }, 
   { 3, { (uint8_t *)&g_obj03_att02_logical_name_element06, 6 }, 2, 0 }, 
   { 3, { (uint8_t *)&g_obj03_att02_logical_name_element07, 6 }, 2, 0 }
};
/* Declare for variable of push_object_list (class - 40, atrribute - 02)*/
const class40_push_object_array_t g_dlms_ic40_obj03_att02_push_object_list  = { (class40_push_object_t *)&g_dlms_ic40_obj03_push_object_list_array_content, 8 };


/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj03_att03_get
* Description   : Object name       : Push setup 3
*                 Object index      : 03
*                 Class             : 40
*                 Attribute order   : 03
*                 Attribute name    : send_destination_and_method
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class40_send_destination_and_method_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj03_att03_get(distributor_params_t * p_params, class40_send_destination_and_method_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	 This is structure of send destinationa and methods, please set following  this.
	 class40_send_destination_and_method_t
	 {
	         class40_transport_service_t    transport_service;
	         OctetString                    destination;
	         class40_message_type_t         message;
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
	//class40_transport_service_t transport_service_link = CLASS_40_TRANSPORT_SERVICE_HDLC;[generated template code]
	//uint8_t destination_content_link[] = { 0x00 };[generated template code]
	//class40_message_type_t message_link = CLASS_40_MESSAGE_TYPE_A_XDR_ENC_xDLMS_APDU;[generated template code]

	/* Set data link to p_get_attribute */
	//p_attribute_get->transport_service = transport_service_link;[generated template code]
	//memcpy(p_attribute_get->destination.p_content, &destination_content_link, 1);[generated template code]
	//p_attribute_get->destination.length = 1;[generated template code]
	//p_attribute_get->message = message_link;[generated template code]

	/* Start user code here */
	return send_destination_and_method_attribute03_get(p_params, p_attribute_get, 3);//channel = 3;
	/* End user code here */

	/* Return result of this, please check again result value */
	//return result;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj03_att03_set
* Description   : Object name       : Push setup 3
*                 Object index      : 03
*                 Class             : 40
*                 Attribute order   : 03
*                 Attribute name    : send_destination_and_method
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class40_send_destination_and_method_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj03_att03_set(distributor_params_t * p_params, class40_send_destination_and_method_t * p_attribute_set)
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
	 This is structure of send destinationa and methods, please set following  this.
	 class40_send_destination_and_method_t
	 {
	         class40_transport_service_t    transport_service;
	         OctetString                    destination;
	         class40_message_type_t         message;
	 };
	*********************************************/


	
	/* Start user code here */
	return send_destination_and_method_attribute03_set(p_params, p_attribute_set, 3);//Channel = 3
	/* End user code here */
	/* Return result of this, please check again result value */
	//return result;
}

/* Please update your array size following your setting change by asigning under variable */
/* For communication_window */
const uint16_t r_dlms_ic40_obj03_att04_array_length = PUSH_MAX_WINDOW_SUPPORT;
/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj03_att04_get
* Description   : Object name       : Push setup 3
*                 Object index      : 03
*                 Class             : 40
*                 Attribute order   : 04
*                 Attribute name    : communication_window
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class40_comm_window_array_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj03_att04_get(distributor_params_t * p_params, class40_comm_window_array_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
	/*
	 * Not implemented(default), r_dlms_ic40_obj03_att04_array_length is assigned 0, response is array - 0 element(0100)
	 * Implemented, but r_dlms_ic40_obj03_att04_array_length is assigned 0, response is array - 0 element(0100)
	 */


	/*********************************************
	 This is element definition
	 class40_comm_window_t
	 {
	     date_time_t start_time;
	     date_time_t end_time;
	}

	 This is array definition
	 class40_comm_window_array_t
	 {
	       uint8_t* p_content;
	       uint16_t length;
	 }
	 p_content: this is pointer of variable class40_comm_window_t[]
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


	/* Element 00 */
	//date_time_t start_time_link_element00 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};[generated template code]
	//date_time_t end_time_link_element00 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};[generated template code]


	/* Set length for this array */
	//p_attribute_get->length = r_dlms_ic40_obj04_att04_array_length;[generated template code]

	/* Set value for element at 0 */
	//p_attribute_get->p_content[0].start_time = start_time_link_element00;[generated template code]
	//p_attribute_get->p_content[0].end_time = end_time_link_element00;[generated template code]

	/* Start user code here */
	return communication_window_attribute04_get(p_params, p_attribute_get, 3);//channel = 3
	/* End user code here */

	/* Return result of this, please check again result value */
	//return result;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj03_att04_set
* Description   : Object name       : Push setup 3
*                 Object index      : 03
*                 Class             : 40
*                 Attribute order   : 04
*                 Attribute name    : communication_window
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class40_comm_window_array_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj03_att04_set(distributor_params_t * p_params, class40_comm_window_array_t * p_attribute_set)
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
	 This is element definition
	 class40_comm_window_t
	 {
	     date_time_t start_time;
	     date_time_t end_time;
	}

	 This is array definition
	 class40_comm_window_array_t
	 {
	       uint8_t* p_content;
	       uint16_t length;
	 }
	 p_content: this is pointer of variable class40_comm_window_t[]
	*********************************************/


	
	/* Start user code here */
	return communication_window_attribute04_set(p_params, p_attribute_set, 3);//channel = 3
	/* End user code here */
	/* Return result of this, please check again result value */
	//return result;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj03_att05_get
* Description   : Object name       : Push setup 3
*                 Object index      : 03
*                 Class             : 40
*                 Attribute order   : 05
*                 Attribute name    : randomisation_start_interval
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint16_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj03_att05_get(distributor_params_t * p_params, uint16_t * p_attribute_get)
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
	//uint16_t link_data = 0;[generated template code]
	/* Set value */
	//*((uint16_t *)p_attribute_get) = link_data;[generated template code]

	/* Start user code here */
	*p_attribute_get = g_push_setup[3].delay_start_max;//channel = 3;
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj03_att05_set
* Description   : Object name       : Push setup 3
*                 Object index      : 03
*                 Class             : 40
*                 Attribute order   : 05
*                 Attribute name    : randomisation_start_interval
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint16_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj03_att05_set(distributor_params_t * p_params, uint16_t * p_attribute_set)
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
	Data type:uint16_t(long-unsigned)
	*********************************************/


	
	/* Start user code here */
	if(R_DLMS_Push_Set_RandomisationStartInterval(3, *p_attribute_set) != RLT_SUCCESS)//channel = 3
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_SUCCESS;
	}
	/* End user code here */
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj03_att06_get
* Description   : Object name       : Push setup 3
*                 Object index      : 03
*                 Class             : 40
*                 Attribute order   : 06
*                 Attribute name    : number_of_retries
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint8_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj03_att06_get(distributor_params_t * p_params, uint8_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint8_t(unsigned)
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
	//uint8_t link_data = 0;[generated template code]
	/* Set value */
	//*((uint8_t *)p_attribute_get) = link_data;[generated template code]

	/* Start user code here */
	*p_attribute_get = g_push_setup[3].retried_num_max;//channel = 3
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj03_att06_set
* Description   : Object name       : Push setup 3
*                 Object index      : 03
*                 Class             : 40
*                 Attribute order   : 06
*                 Attribute name    : number_of_retries
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint8_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj03_att06_set(distributor_params_t * p_params, uint8_t * p_attribute_set)
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
	Data type:uint8_t(unsigned)
	*********************************************/


	
	/* Start user code here */
	if(R_DLMS_Push_Set_NumberOfRetry(3, *p_attribute_set) != RLT_SUCCESS)//channel = 3
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_SUCCESS;
	}
	/* End user code here */
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj03_att07_get
* Description   : Object name       : Push setup 3
*                 Object index      : 03
*                 Class             : 40
*                 Attribute order   : 07
*                 Attribute name    : repetition_delay
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint16_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj03_att07_get(distributor_params_t * p_params, uint16_t * p_attribute_get)
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
	//uint16_t link_data = 0;[generated template code]
	/* Set value */
	//*((uint16_t *)p_attribute_get) = link_data;[generated template code]

	/* Start user code here */
	*p_attribute_get = g_push_setup[3].delay_retry_max;//Channel = 3
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj03_att07_set
* Description   : Object name       : Push setup 3
*                 Object index      : 03
*                 Class             : 40
*                 Attribute order   : 07
*                 Attribute name    : repetition_delay
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint16_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj03_att07_set(distributor_params_t * p_params, uint16_t * p_attribute_set)
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
	Data type:uint16_t(long-unsigned)
	*********************************************/


	
	/* Start user code here */
	if(R_DLMS_Push_Set_RepetitionDelay(3, *p_attribute_set) != RLT_SUCCESS)//channel = 3
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_SUCCESS;
	}
	/* End user code here */
}


/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj03_meth01_action
* Description   : Object name       : Push setup 3
*                 Object index      : 03
*                 Class             : 40
*                 Method order      : 01
*                 Method name       : push
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj03_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Activates the push process leading to the elaboration and the sending of
	*  the push data taking into account the values of the attributes defined 
	*  in the given instance of this IC.
	* p_data_from_client ::= integer(0)->NOT REQUIREMENT.
	*************************************************************************/


	/**************************************************************
	This is enum of return result value. 
	Default is VAL_ACTION_RESULT_OTHER_REASON
	* typedef enum																															 *
	* {																																		 *
	* 	VAL_ACTION_RESULT_SUCCESS 						= 0   ,																				 *
	* 	VAL_ACTION_RESULT_HARDWARE_FAULT 				= 1   ,																				 *
	* 	VAL_ACTION_RESULT_TEMPORARY_FAILURE 			= 2   ,																				 *
	* 	VAL_ACTION_RESULT_READ_WRITE_DENIED 			= 3   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNDEFINED 				= 4   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNAVAILABLE 			= 11  ,																				 *
	* 	VAL_ACTION_RESULT_TYPE_UNMATCHED 				= 12  ,																				 *
	* 	VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED 		= 13  ,																				 *
	* 	VAL_ACTION_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14  ,																				 *
	* 	VAL_ACTION_RESULT_LONG_ACTION_ABORTED 			= 15  ,																				 *
	* 	VAL_ACTION_RESULT_NO_LONG_ACTION_IN_PROGRESS 	= 16  ,																				 *
	* 	VAL_ACTION_RESULT_OTHER_REASON 					= 250 ,																				 *
	* } ActionResult_Value;																													 *
	
	*****************************************************************/
	/* Start user code here */
	R_DLMS_Push_SetFlag(3);//Channel = 3
		
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}


/***********************************************************************************************************
* Object name:      Push setup 4
* Object number:    04
* Object obis code: 0.4.25.9.0.255
***********************************************************************************************************/

/*******************************************************************************
* Class ID: 40
* Variable name: g_dlms_ic40_obj04_att02_push_object_list
* Object name: Push setup 4
* Attribute order: 02
* Attribute name: push_object_list
* Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ;
* Group object		: Push
*******************************************************************************/
/*********************************************
 This is array of object definition
 class40_push_object_t
 { 
       uint16_t      class_id;
       FixedString   logical_name;
       int8_t        attribute_index;
       uint16_t      data_index;
 }
* FixedString
* {
*     uint8_t* p_content; 
*     uint16_t length;
* }

 class40_push_object_array_t
 {
       uint8_t* p_content;
       uint16_t length;
 }
 p_content: this is pointer of variable class40_push_object_t[]
*********************************************/

/* Component value of each element array */

/* Element 00 */
const uint8_t g_obj04_att02_logical_name_element00[] = {0, 0, 96, 1, 2, 255};


/* Element 01 */
const uint8_t g_obj04_att02_logical_name_element01[] = {0, 4, 25, 9, 0, 255};


/* Element 02 */
const uint8_t g_obj04_att02_logical_name_element02[] = {0, 0, 1, 0, 0, 255};


/* Element 03 */
const uint8_t g_obj04_att02_logical_name_element03[] = {0, 0, 94, 91, 18, 255};


/* Element array value */
const class40_push_object_t g_dlms_ic40_obj04_push_object_list_array_content[] = 
{
   { 1, { (uint8_t *)&g_obj04_att02_logical_name_element00, 6 }, 2, 0 }, 
   { 40, { (uint8_t *)&g_obj04_att02_logical_name_element01, 6 }, 1, 0 }, 
   { 8, { (uint8_t *)&g_obj04_att02_logical_name_element02, 6 }, 2, 0 }, 
   { 1, { (uint8_t *)&g_obj04_att02_logical_name_element03, 6 }, 2, 0 }
};
/* Declare for variable of push_object_list (class - 40, atrribute - 02)*/
const class40_push_object_array_t g_dlms_ic40_obj04_att02_push_object_list  = { (class40_push_object_t *)&g_dlms_ic40_obj04_push_object_list_array_content, 4 };


/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj04_att03_get
* Description   : Object name       : Push setup 4
*                 Object index      : 04
*                 Class             : 40
*                 Attribute order   : 03
*                 Attribute name    : send_destination_and_method
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class40_send_destination_and_method_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj04_att03_get(distributor_params_t * p_params, class40_send_destination_and_method_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	 This is structure of send destinationa and methods, please set following  this.
	 class40_send_destination_and_method_t
	 {
	         class40_transport_service_t    transport_service;
	         OctetString                    destination;
	         class40_message_type_t         message;
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
	//class40_transport_service_t transport_service_link = CLASS_40_TRANSPORT_SERVICE_HDLC;[generated template code]
	//uint8_t destination_content_link[] = { 0x00 };[generated template code]
	//class40_message_type_t message_link = CLASS_40_MESSAGE_TYPE_A_XDR_ENC_xDLMS_APDU;[generated template code]

	/* Set data link to p_get_attribute */
	//p_attribute_get->transport_service = transport_service_link;[generated template code]
	//memcpy(p_attribute_get->destination.p_content, &destination_content_link, 1);[generated template code]
	//p_attribute_get->destination.length = 1;[generated template code]
	//p_attribute_get->message = message_link;[generated template code]

	/* Start user code here */
	return send_destination_and_method_attribute03_get(p_params, p_attribute_get, 4);//channel = 4;
	/* End user code here */

	/* Return result of this, please check again result value */
	//return result;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj04_att03_set
* Description   : Object name       : Push setup 4
*                 Object index      : 04
*                 Class             : 40
*                 Attribute order   : 03
*                 Attribute name    : send_destination_and_method
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class40_send_destination_and_method_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj04_att03_set(distributor_params_t * p_params, class40_send_destination_and_method_t * p_attribute_set)
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
	 This is structure of send destinationa and methods, please set following  this.
	 class40_send_destination_and_method_t
	 {
	         class40_transport_service_t    transport_service;
	         OctetString                    destination;
	         class40_message_type_t         message;
	 };
	*********************************************/


	
	/* Start user code here */
	return send_destination_and_method_attribute03_set(p_params, p_attribute_set, 4);//Channel = 4
	/* End user code here */
	/* Return result of this, please check again result value */
	//return result;
}

/* Please update your array size following your setting change by asigning under variable */
/* For communication_window */
const uint16_t r_dlms_ic40_obj04_att04_array_length = PUSH_MAX_WINDOW_SUPPORT;
/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj04_att04_get
* Description   : Object name       : Push setup 4
*                 Object index      : 04
*                 Class             : 40
*                 Attribute order   : 04
*                 Attribute name    : communication_window
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class40_comm_window_array_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj04_att04_get(distributor_params_t * p_params, class40_comm_window_array_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
	/*
	 * Not implemented(default), r_dlms_ic40_obj04_att04_array_length is assigned 0, response is array - 0 element(0100)
	 * Implemented, but r_dlms_ic40_obj04_att04_array_length is assigned 0, response is array - 0 element(0100)
	 */


	/*********************************************
	 This is element definition
	 class40_comm_window_t
	 {
	     date_time_t start_time;
	     date_time_t end_time;
	}

	 This is array definition
	 class40_comm_window_array_t
	 {
	       uint8_t* p_content;
	       uint16_t length;
	 }
	 p_content: this is pointer of variable class40_comm_window_t[]
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


	/* Element 00 */
	//date_time_t start_time_link_element00 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};[generated template code]
	//date_time_t end_time_link_element00 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};[generated template code]


	/* Set length for this array */
	//p_attribute_get->length = r_dlms_ic40_obj04_att04_array_length;[generated template code]

	/* Set value for element at 0 */
	//p_attribute_get->p_content[0].start_time = start_time_link_element00;[generated template code]
	//p_attribute_get->p_content[0].end_time = end_time_link_element00;[generated template code]



	/* Start user code here */
	return communication_window_attribute04_get(p_params, p_attribute_get, 4);//channel = 4
	/* End user code here */

	/* Return result of this, please check again result value */
	//return result;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj04_att04_set
* Description   : Object name       : Push setup 4
*                 Object index      : 04
*                 Class             : 40
*                 Attribute order   : 04
*                 Attribute name    : communication_window
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class40_comm_window_array_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj04_att04_set(distributor_params_t * p_params, class40_comm_window_array_t * p_attribute_set)
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
	 This is element definition
	 class40_comm_window_t
	 {
	     date_time_t start_time;
	     date_time_t end_time;
	}

	 This is array definition
	 class40_comm_window_array_t
	 {
	       uint8_t* p_content;
	       uint16_t length;
	 }
	 p_content: this is pointer of variable class40_comm_window_t[]
	*********************************************/


	
	/* Start user code here */
	return communication_window_attribute04_set(p_params, p_attribute_set, 4);//channel = 4
	/* End user code here */
	/* Return result of this, please check again result value */
	//return result;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj04_att05_get
* Description   : Object name       : Push setup 4
*                 Object index      : 04
*                 Class             : 40
*                 Attribute order   : 05
*                 Attribute name    : randomisation_start_interval
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint16_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj04_att05_get(distributor_params_t * p_params, uint16_t * p_attribute_get)
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
	//uint16_t link_data = 0;[generated template code]
	/* Set value */
	//*((uint16_t *)p_attribute_get) = link_data;[generated template code]

	/* Start user code here */
	*p_attribute_get = g_push_setup[4].delay_start_max;//channel = 4;
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj04_att05_set
* Description   : Object name       : Push setup 4
*                 Object index      : 04
*                 Class             : 40
*                 Attribute order   : 05
*                 Attribute name    : randomisation_start_interval
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint16_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj04_att05_set(distributor_params_t * p_params, uint16_t * p_attribute_set)
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
	Data type:uint16_t(long-unsigned)
	*********************************************/


	
	/* Start user code here */
	if(R_DLMS_Push_Set_RandomisationStartInterval(4, *p_attribute_set) != RLT_SUCCESS)//channel = 4
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_SUCCESS;
	}
	/* End user code here */
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj04_att06_get
* Description   : Object name       : Push setup 4
*                 Object index      : 04
*                 Class             : 40
*                 Attribute order   : 06
*                 Attribute name    : number_of_retries
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint8_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj04_att06_get(distributor_params_t * p_params, uint8_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint8_t(unsigned)
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
	//uint8_t link_data = 0;[generated template code]
	/* Set value */
	//*((uint8_t *)p_attribute_get) = link_data;[generated template code]

	/* Start user code here */
	*p_attribute_get = g_push_setup[4].retried_num_max;//channel = 4
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj04_att06_set
* Description   : Object name       : Push setup 4
*                 Object index      : 04
*                 Class             : 40
*                 Attribute order   : 06
*                 Attribute name    : number_of_retries
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint8_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj04_att06_set(distributor_params_t * p_params, uint8_t * p_attribute_set)
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
	Data type:uint8_t(unsigned)
	*********************************************/


	
	/* Start user code here */
	if(R_DLMS_Push_Set_NumberOfRetry(4, *p_attribute_set) != RLT_SUCCESS)//channel = 4
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_SUCCESS;
	}
	/* End user code here */
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj04_att07_get
* Description   : Object name       : Push setup 4
*                 Object index      : 04
*                 Class             : 40
*                 Attribute order   : 07
*                 Attribute name    : repetition_delay
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {3, Push}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint16_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj04_att07_get(distributor_params_t * p_params, uint16_t * p_attribute_get)
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
	//uint16_t link_data = 0;[generated template code]
	/* Set value */
	//*((uint16_t *)p_attribute_get) = link_data;[generated template code]

	/* Start user code here */
	*p_attribute_get = g_push_setup[4].delay_retry_max;//Channel = 4
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj04_att07_set
* Description   : Object name       : Push setup 4
*                 Object index      : 04
*                 Class             : 40
*                 Attribute order   : 07
*                 Attribute name    : repetition_delay
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint16_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj04_att07_set(distributor_params_t * p_params, uint16_t * p_attribute_set)
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
	Data type:uint16_t(long-unsigned)
	*********************************************/


	
	/* Start user code here */
	if(R_DLMS_Push_Set_RepetitionDelay(4, *p_attribute_set) != RLT_SUCCESS)//channel = 4
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_SUCCESS;
	}
	/* End user code here */
}


/******************************************************************************
* Function Name : R_DLMS_USER_ic40_obj04_meth01_action
* Description   : Object name       : Push setup 4
*                 Object index      : 04
*                 Class             : 40
*                 Method order      : 01
*                 Method name       : push
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: Push
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj04_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Activates the push process leading to the elaboration and the sending of
	*  the push data taking into account the values of the attributes defined 
	*  in the given instance of this IC.
	* p_data_from_client ::= integer(0)->NOT REQUIREMENT.
	*************************************************************************/


	/**************************************************************
	This is enum of return result value. 
	Default is VAL_ACTION_RESULT_OTHER_REASON
	* typedef enum																															 *
	* {																																		 *
	* 	VAL_ACTION_RESULT_SUCCESS 						= 0   ,																				 *
	* 	VAL_ACTION_RESULT_HARDWARE_FAULT 				= 1   ,																				 *
	* 	VAL_ACTION_RESULT_TEMPORARY_FAILURE 			= 2   ,																				 *
	* 	VAL_ACTION_RESULT_READ_WRITE_DENIED 			= 3   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNDEFINED 				= 4   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNAVAILABLE 			= 11  ,																				 *
	* 	VAL_ACTION_RESULT_TYPE_UNMATCHED 				= 12  ,																				 *
	* 	VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED 		= 13  ,																				 *
	* 	VAL_ACTION_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14  ,																				 *
	* 	VAL_ACTION_RESULT_LONG_ACTION_ABORTED 			= 15  ,																				 *
	* 	VAL_ACTION_RESULT_NO_LONG_ACTION_IN_PROGRESS 	= 16  ,																				 *
	* 	VAL_ACTION_RESULT_OTHER_REASON 					= 250 ,																				 *
	* } ActionResult_Value;																													 *
	
	*****************************************************************/
	/* Start user code here */
	R_DLMS_Push_SetFlag(4);//Channel = 4	
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}


