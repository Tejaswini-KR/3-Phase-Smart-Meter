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
* File Name    : r_dlms_object_class04.c
* Version      : 2.00
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 03/01/2023 
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_library_process.h"

#include "r_dlms_config.h"
#include "r_dlms_classes.h"
#include "r_dlms_class04.h"
#include "r_dlms_objects.h"
#include "r_dlms_type.h"

#include "r_dlms_usercode_class04.h"

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

/******************************************************************************
Private global variables and functions
******************************************************************************/



/*---------------------------------------------------------------------------*/
/*Class 04 record table*/
/*---------------------------------------------------------------------------*/
const class04_child_record_t	g_objects_child_table_class04[] =
{
	/* 00 - MD kW for TZ1 */
	{ 
		{1,   0,   1,   6,   1,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic04_obj00_att03_Scaler_Unit,
		CHOICE(CHOICE_OCTET_STRING(10), NULL),
		NULL,

	},

	/* 01 - MD kW for TZ2 */
	{ 
		{1,   0,   1,   6,   2,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic04_obj01_att03_Scaler_Unit,
		CHOICE(CHOICE_OCTET_STRING(10), NULL),
		NULL,

	},

	/* 02 - MD kW for TZ3 */
	{ 
		{1,   0,   1,   6,   3,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic04_obj02_att03_Scaler_Unit,
		CHOICE(CHOICE_OCTET_STRING(10), NULL),
		NULL,

	},

	/* 03 - MD kW for TZ4 */
	{ 
		{1,   0,   1,   6,   4,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic04_obj03_att03_Scaler_Unit,
		CHOICE(CHOICE_OCTET_STRING(10), NULL),
		NULL,

	},

	/* 04 - MD kW for TZ5 */
	{ 
		{1,   0,   1,   6,   5,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic04_obj04_att03_Scaler_Unit,
		CHOICE(CHOICE_OCTET_STRING(10), NULL),
		NULL,

	},

	/* 05 - MD kW for TZ6 */
	{ 
		{1,   0,   1,   6,   6,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic04_obj05_att03_Scaler_Unit,
		CHOICE(CHOICE_OCTET_STRING(10), NULL),
		NULL,

	},

	/* 06 - MD kW for TZ7 */
	{ 
		{1,   0,   1,   6,   7,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic04_obj06_att03_Scaler_Unit,
		CHOICE(CHOICE_OCTET_STRING(10), NULL),
		NULL,

	},

	/* 07 - MD kW for TZ8 */
	{ 
		{1,   0,   1,   6,   8,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic04_obj07_att03_Scaler_Unit,
		CHOICE(CHOICE_OCTET_STRING(10), NULL),
		NULL,

	},

	/* 08 - MD kVA for TZ1 */
	{ 
		{1,   0,   9,   6,   1,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic04_obj08_att03_Scaler_Unit,
		CHOICE(CHOICE_OCTET_STRING(10), NULL),
		NULL,

	},

	/* 09 - MD kVA for TZ2 */
	{ 
		{1,   0,   9,   6,   2,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic04_obj09_att03_Scaler_Unit,
		CHOICE(CHOICE_OCTET_STRING(10), NULL),
		NULL,

	},

	/* 10 - MD kVA for TZ3 */
	{ 
		{1,   0,   9,   6,   3,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic04_obj10_att03_Scaler_Unit,
		CHOICE(CHOICE_OCTET_STRING(10), NULL),
		NULL,

	},

	/* 11 - MD kVA for TZ4 */
	{ 
		{1,   0,   9,   6,   4,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic04_obj11_att03_Scaler_Unit,
		CHOICE(CHOICE_OCTET_STRING(10), NULL),
		NULL,

	},

	/* 12 - MD kVA for TZ5 */
	{ 
		{1,   0,   9,   6,   5,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic04_obj12_att03_Scaler_Unit,
		CHOICE(CHOICE_OCTET_STRING(10), NULL),
		NULL,

	},

	/* 13 - MD kVA for TZ7 */
	{ 
		{1,   0,   9,   6,   7,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic04_obj13_att03_Scaler_Unit,
		CHOICE(CHOICE_OCTET_STRING(10), NULL),
		NULL,

	},

	/* 14 - MD kVA for TZ8 */
	{ 
		{1,   0,   9,   6,   8,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic04_obj14_att03_Scaler_Unit,
		CHOICE(CHOICE_OCTET_STRING(10), NULL),
		NULL,

	},

	/* 15 - MD kVA for TZ6 */
	{ 
		{1,   0,   9,   6,   6,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic04_obj15_att03_Scaler_Unit,
		CHOICE(CHOICE_OCTET_STRING(10), NULL),
		NULL,

	},

	/* 16 - Maximum Demand  kVA */
	{ 
		{1,   0,   9,   6,   0,   255},
		(access_right_t *)g_objects_access_right_table[6],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic04_obj16_att03_Scaler_Unit,
		CHOICE(CHOICE_OCTET_STRING(10), NULL),
		NULL,

	},

	/* 17 - Maximum Demand kW */
	{ 
		{1,   0,   1,   6,   0,   255},
		(access_right_t *)g_objects_access_right_table[6],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic04_obj17_att03_Scaler_Unit,
		CHOICE(CHOICE_OCTET_STRING(10), NULL),
		NULL,

	},


};

const uint16_t 	g_objects_child_table_class04_length = sizeof(g_objects_child_table_class04) / sizeof(class04_child_record_t);



/******************************************************************************
* Function Name : R_DLMS_OBJECTS_Class04Distributor
* Interface     : void R_DLMS_OBJECTS_Class04Distributor(
*               :     distributor_params_t * p_param,
*               : );
* Description   : User distributor function for GET/SET/ACTION service of class 04
* Arguments     : distributor_params_t * p_param: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_OBJECTS_Class04Distributor(distributor_params_t *p_params)
{
	class04_child_record_t	* p_class04_obj = (class04_child_record_t *)p_params->p_child_record;
	void * p_object;
	uint16_t length;
	uint8_t result;

	/*
	* ---------------------------
	* >>> IMPLEMENTATION NOTE <<<
	* ---------------------------
	*
	* Attr0 and Attr1 are handled on abstract class function already (READ ONLY). Please process other object attrs from attr no 2.
	* In default of processing, this function is called twice, BEFORE and AFTER the class distributor function call.
	* Check the value of (p_params->distributor_state) to know the calling to this function is in before or after class distributor
	*
	* Calling sequence with class distributor function is as below:
	*
	*    // User distributor function is called first with distribution state = DIST_BEFORE_CLASS_FUNCTION
	*    if (fp_user_func != NULL) {
	*    	if (p_params->handled == FALSE) {
	*    		p_params->distributor_state = DIST_BEFORE_CLASS_FUNCTION;
	*    		(*fp_user_func)(p_params);
	*    	}
	*    }
	*
	*    // Class distributor function is called in second with distribution state = DIST_UNDER_CLASS_FUNCTION
	*    if (fp_class_func != NULL) {
	*    	if (p_params->handled == FALSE) {
	*    		p_params->distributor_state = DIST_UNDER_CLASS_FUNCTION;
	*    		(*fp_class_func)(p_params);
	*    	}
	*    }
	*
	*    // User distributor function is called first with distribution state = DIST_AFTER_CLASS_FUNCTION
	*    if (fp_user_func != NULL) {
	*    	if (p_params->handled == FALSE) {
	*    		p_params->distributor_state = DIST_AFTER_CLASS_FUNCTION;
	*    		(*fp_user_func)(p_params);
	*    	}
	*    }
	*
	* To break the calling sequence above, on this function (user function), write below code at a desired location:
	*
	*    p_params->handled = TRUE;
	*
	*/
	
	if (p_params->req_type == REQ_TYPE_GET)
	{
		result = p_params->result.result.data_access;
		switch (p_params->descriptor.attr.attribute_id)
		{
			case 2:
				if (p_params->distributor_state == DIST_BEFORE_CLASS_FUNCTION)
				{
					p_params->handled = FALSE;

					switch(p_params->child_index)
					{
#if defined(CLASS04_OBJ00_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ00_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 0:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_02(p_params, p_class04_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj00_att02_get(p_params, &p_class04_obj->value);
							break;

#endif
#if defined(CLASS04_OBJ01_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ01_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 1:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_02(p_params, p_class04_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj01_att02_get(p_params, &p_class04_obj->value);
							break;

#endif
#if defined(CLASS04_OBJ02_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ02_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 2:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_02(p_params, p_class04_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj02_att02_get(p_params, &p_class04_obj->value);
							break;

#endif
#if defined(CLASS04_OBJ03_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ03_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 3:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_02(p_params, p_class04_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj03_att02_get(p_params, &p_class04_obj->value);
							break;

#endif
#if defined(CLASS04_OBJ04_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ04_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 4:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_02(p_params, p_class04_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj04_att02_get(p_params, &p_class04_obj->value);
							break;

#endif
#if defined(CLASS04_OBJ05_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ05_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 5:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_02(p_params, p_class04_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj05_att02_get(p_params, &p_class04_obj->value);
							break;

#endif
#if defined(CLASS04_OBJ06_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ06_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 6:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_02(p_params, p_class04_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj06_att02_get(p_params, &p_class04_obj->value);
							break;

#endif
#if defined(CLASS04_OBJ07_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ07_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 7:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_02(p_params, p_class04_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj07_att02_get(p_params, &p_class04_obj->value);
							break;

#endif
#if defined(CLASS04_OBJ08_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ08_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 8:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_02(p_params, p_class04_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj08_att02_get(p_params, &p_class04_obj->value);
							break;

#endif
#if defined(CLASS04_OBJ09_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ09_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 9:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_02(p_params, p_class04_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj09_att02_get(p_params, &p_class04_obj->value);
							break;

#endif
#if defined(CLASS04_OBJ10_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ10_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 10:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_02(p_params, p_class04_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj10_att02_get(p_params, &p_class04_obj->value);
							break;

#endif
#if defined(CLASS04_OBJ11_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ11_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 11:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_02(p_params, p_class04_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj11_att02_get(p_params, &p_class04_obj->value);
							break;

#endif
#if defined(CLASS04_OBJ12_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ12_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 12:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_02(p_params, p_class04_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj12_att02_get(p_params, &p_class04_obj->value);
							break;

#endif
#if defined(CLASS04_OBJ13_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ13_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 13:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_02(p_params, p_class04_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj13_att02_get(p_params, &p_class04_obj->value);
							break;

#endif
#if defined(CLASS04_OBJ14_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ14_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 14:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_02(p_params, p_class04_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj14_att02_get(p_params, &p_class04_obj->value);
							break;

#endif
#if defined(CLASS04_OBJ15_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ15_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 15:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_02(p_params, p_class04_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj15_att02_get(p_params, &p_class04_obj->value);
							break;

#endif
#if defined(CLASS04_OBJ16_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ16_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 16:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_02(p_params, p_class04_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj16_att02_get(p_params, &p_class04_obj->value);
							break;

#endif
#if defined(CLASS04_OBJ17_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ17_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 17:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_02(p_params, p_class04_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj17_att02_get(p_params, &p_class04_obj->value);
							break;

#endif

						default:
							break;
					}

				}
				else
				{
					/* Nothing code here */
				}
				break;
			case 4:
				if (p_params->distributor_state == DIST_BEFORE_CLASS_FUNCTION)
				{
					p_params->handled = FALSE;

					switch(p_params->child_index)
					{
#if defined(CLASS04_OBJ00_ATTR04_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ00_ATTR04_GET_USERFUNCTION_ENABLE == TRUE)
						case 0:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_04(p_params, p_class04_obj->status);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj00_att04_get(p_params, &p_class04_obj->status);
							break;

#endif
#if defined(CLASS04_OBJ01_ATTR04_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ01_ATTR04_GET_USERFUNCTION_ENABLE == TRUE)
						case 1:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_04(p_params, p_class04_obj->status);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj01_att04_get(p_params, &p_class04_obj->status);
							break;

#endif
#if defined(CLASS04_OBJ02_ATTR04_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ02_ATTR04_GET_USERFUNCTION_ENABLE == TRUE)
						case 2:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_04(p_params, p_class04_obj->status);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj02_att04_get(p_params, &p_class04_obj->status);
							break;

#endif
#if defined(CLASS04_OBJ03_ATTR04_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ03_ATTR04_GET_USERFUNCTION_ENABLE == TRUE)
						case 3:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_04(p_params, p_class04_obj->status);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj03_att04_get(p_params, &p_class04_obj->status);
							break;

#endif
#if defined(CLASS04_OBJ04_ATTR04_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ04_ATTR04_GET_USERFUNCTION_ENABLE == TRUE)
						case 4:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_04(p_params, p_class04_obj->status);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj04_att04_get(p_params, &p_class04_obj->status);
							break;

#endif
#if defined(CLASS04_OBJ05_ATTR04_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ05_ATTR04_GET_USERFUNCTION_ENABLE == TRUE)
						case 5:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_04(p_params, p_class04_obj->status);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj05_att04_get(p_params, &p_class04_obj->status);
							break;

#endif
#if defined(CLASS04_OBJ06_ATTR04_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ06_ATTR04_GET_USERFUNCTION_ENABLE == TRUE)
						case 6:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_04(p_params, p_class04_obj->status);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj06_att04_get(p_params, &p_class04_obj->status);
							break;

#endif
#if defined(CLASS04_OBJ07_ATTR04_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ07_ATTR04_GET_USERFUNCTION_ENABLE == TRUE)
						case 7:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_04(p_params, p_class04_obj->status);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj07_att04_get(p_params, &p_class04_obj->status);
							break;

#endif
#if defined(CLASS04_OBJ08_ATTR04_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ08_ATTR04_GET_USERFUNCTION_ENABLE == TRUE)
						case 8:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_04(p_params, p_class04_obj->status);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj08_att04_get(p_params, &p_class04_obj->status);
							break;

#endif
#if defined(CLASS04_OBJ09_ATTR04_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ09_ATTR04_GET_USERFUNCTION_ENABLE == TRUE)
						case 9:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_04(p_params, p_class04_obj->status);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj09_att04_get(p_params, &p_class04_obj->status);
							break;

#endif
#if defined(CLASS04_OBJ10_ATTR04_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ10_ATTR04_GET_USERFUNCTION_ENABLE == TRUE)
						case 10:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_04(p_params, p_class04_obj->status);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj10_att04_get(p_params, &p_class04_obj->status);
							break;

#endif
#if defined(CLASS04_OBJ11_ATTR04_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ11_ATTR04_GET_USERFUNCTION_ENABLE == TRUE)
						case 11:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_04(p_params, p_class04_obj->status);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj11_att04_get(p_params, &p_class04_obj->status);
							break;

#endif
#if defined(CLASS04_OBJ12_ATTR04_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ12_ATTR04_GET_USERFUNCTION_ENABLE == TRUE)
						case 12:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_04(p_params, p_class04_obj->status);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj12_att04_get(p_params, &p_class04_obj->status);
							break;

#endif
#if defined(CLASS04_OBJ13_ATTR04_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ13_ATTR04_GET_USERFUNCTION_ENABLE == TRUE)
						case 13:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_04(p_params, p_class04_obj->status);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj13_att04_get(p_params, &p_class04_obj->status);
							break;

#endif
#if defined(CLASS04_OBJ14_ATTR04_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ14_ATTR04_GET_USERFUNCTION_ENABLE == TRUE)
						case 14:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_04(p_params, p_class04_obj->status);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj14_att04_get(p_params, &p_class04_obj->status);
							break;

#endif
#if defined(CLASS04_OBJ15_ATTR04_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ15_ATTR04_GET_USERFUNCTION_ENABLE == TRUE)
						case 15:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_04(p_params, p_class04_obj->status);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj15_att04_get(p_params, &p_class04_obj->status);
							break;

#endif
#if defined(CLASS04_OBJ16_ATTR04_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ16_ATTR04_GET_USERFUNCTION_ENABLE == TRUE)
						case 16:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_04(p_params, p_class04_obj->status);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj16_att04_get(p_params, &p_class04_obj->status);
							break;

#endif
#if defined(CLASS04_OBJ17_ATTR04_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ17_ATTR04_GET_USERFUNCTION_ENABLE == TRUE)
						case 17:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_04(p_params, p_class04_obj->status);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj17_att04_get(p_params, &p_class04_obj->status);
							break;

#endif

						default:
							break;
					}

				}
				else
				{
					/* Nothing code here */
				}
				break;
			case 5:
				if (p_params->distributor_state == DIST_BEFORE_CLASS_FUNCTION)
				{
					p_params->handled = FALSE;

					switch(p_params->child_index)
					{
						case 0:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_05(p_params, p_class04_obj->p_capture_time);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj00_att05_get(p_params, p_class04_obj->p_capture_time);
							break;

						case 1:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_05(p_params, p_class04_obj->p_capture_time);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj01_att05_get(p_params, p_class04_obj->p_capture_time);
							break;

						case 2:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_05(p_params, p_class04_obj->p_capture_time);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj02_att05_get(p_params, p_class04_obj->p_capture_time);
							break;

						case 3:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_05(p_params, p_class04_obj->p_capture_time);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj03_att05_get(p_params, p_class04_obj->p_capture_time);
							break;

						case 4:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_05(p_params, p_class04_obj->p_capture_time);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj04_att05_get(p_params, p_class04_obj->p_capture_time);
							break;

						case 5:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_05(p_params, p_class04_obj->p_capture_time);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj05_att05_get(p_params, p_class04_obj->p_capture_time);
							break;

						case 6:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_05(p_params, p_class04_obj->p_capture_time);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj06_att05_get(p_params, p_class04_obj->p_capture_time);
							break;

						case 7:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_05(p_params, p_class04_obj->p_capture_time);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj07_att05_get(p_params, p_class04_obj->p_capture_time);
							break;

						case 8:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_05(p_params, p_class04_obj->p_capture_time);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj08_att05_get(p_params, p_class04_obj->p_capture_time);
							break;

						case 9:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_05(p_params, p_class04_obj->p_capture_time);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj09_att05_get(p_params, p_class04_obj->p_capture_time);
							break;

						case 10:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_05(p_params, p_class04_obj->p_capture_time);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj10_att05_get(p_params, p_class04_obj->p_capture_time);
							break;

						case 11:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_05(p_params, p_class04_obj->p_capture_time);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj11_att05_get(p_params, p_class04_obj->p_capture_time);
							break;

						case 12:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_05(p_params, p_class04_obj->p_capture_time);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj12_att05_get(p_params, p_class04_obj->p_capture_time);
							break;

						case 13:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_05(p_params, p_class04_obj->p_capture_time);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj13_att05_get(p_params, p_class04_obj->p_capture_time);
							break;

						case 14:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_05(p_params, p_class04_obj->p_capture_time);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj14_att05_get(p_params, p_class04_obj->p_capture_time);
							break;

						case 15:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_05(p_params, p_class04_obj->p_capture_time);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj15_att05_get(p_params, p_class04_obj->p_capture_time);
							break;

						case 16:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_05(p_params, p_class04_obj->p_capture_time);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj16_att05_get(p_params, p_class04_obj->p_capture_time);
							break;

						case 17:
							/* Clone new attribute */
							R_DLMS_IC04_REDIRECT_05(p_params, p_class04_obj->p_capture_time);
							/* APPLICATION */
							result = R_DLMS_USER_ic04_obj17_att05_get(p_params, p_class04_obj->p_capture_time);
							break;


						default:
							break;
					}

				}
				else
				{
					/* Nothing code here */
				}
				break;

			default:
				break;
		}
		p_params->result.result.data_access = (DataAccessResult_Value)result;
	}
	else if(p_params->req_type == REQ_TYPE_SET)
	{
		result = p_params->result.result.data_access;
		switch (p_params->descriptor.attr.attribute_id)
		{
			case 2:
				if ((p_params->distributor_state == DIST_AFTER_CLASS_FUNCTION)&&
			      (p_params->service_params.decode_success == TRUE))
				{
					p_params->service_params.sync = FALSE;

					switch(p_params->child_index)
					{
#if defined(CLASS04_OBJ00_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ00_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 0:
							result = R_DLMS_USER_ic04_obj00_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ01_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ01_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 1:
							result = R_DLMS_USER_ic04_obj01_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ02_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ02_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 2:
							result = R_DLMS_USER_ic04_obj02_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ03_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ03_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 3:
							result = R_DLMS_USER_ic04_obj03_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ04_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ04_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 4:
							result = R_DLMS_USER_ic04_obj04_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ05_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ05_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 5:
							result = R_DLMS_USER_ic04_obj05_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ06_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ06_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 6:
							result = R_DLMS_USER_ic04_obj06_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ07_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ07_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 7:
							result = R_DLMS_USER_ic04_obj07_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ08_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ08_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 8:
							result = R_DLMS_USER_ic04_obj08_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ09_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ09_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 9:
							result = R_DLMS_USER_ic04_obj09_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ10_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ10_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 10:
							result = R_DLMS_USER_ic04_obj10_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ11_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ11_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 11:
							result = R_DLMS_USER_ic04_obj11_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ12_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ12_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 12:
							result = R_DLMS_USER_ic04_obj12_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ13_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ13_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 13:
							result = R_DLMS_USER_ic04_obj13_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ14_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ14_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 14:
							result = R_DLMS_USER_ic04_obj14_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ15_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ15_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 15:
							result = R_DLMS_USER_ic04_obj15_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ16_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ16_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 16:
							result = R_DLMS_USER_ic04_obj16_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ17_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ17_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 17:
							result = R_DLMS_USER_ic04_obj17_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							

						default:
							break;
					}

				}
				else
				{
					/* Nothing code here */
				}
				break;
			case 4:
				if ((p_params->distributor_state == DIST_AFTER_CLASS_FUNCTION)&&
			      (p_params->service_params.decode_success == TRUE))
				{
					p_params->service_params.sync = FALSE;

					switch(p_params->child_index)
					{
#if defined(CLASS04_OBJ00_ATTR04_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ00_ATTR04_SET_USERFUNCTION_ENABLE == TRUE)
						case 0:
							result = R_DLMS_USER_ic04_obj00_att04_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ01_ATTR04_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ01_ATTR04_SET_USERFUNCTION_ENABLE == TRUE)
						case 1:
							result = R_DLMS_USER_ic04_obj01_att04_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ02_ATTR04_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ02_ATTR04_SET_USERFUNCTION_ENABLE == TRUE)
						case 2:
							result = R_DLMS_USER_ic04_obj02_att04_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ03_ATTR04_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ03_ATTR04_SET_USERFUNCTION_ENABLE == TRUE)
						case 3:
							result = R_DLMS_USER_ic04_obj03_att04_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ04_ATTR04_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ04_ATTR04_SET_USERFUNCTION_ENABLE == TRUE)
						case 4:
							result = R_DLMS_USER_ic04_obj04_att04_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ05_ATTR04_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ05_ATTR04_SET_USERFUNCTION_ENABLE == TRUE)
						case 5:
							result = R_DLMS_USER_ic04_obj05_att04_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ06_ATTR04_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ06_ATTR04_SET_USERFUNCTION_ENABLE == TRUE)
						case 6:
							result = R_DLMS_USER_ic04_obj06_att04_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ07_ATTR04_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ07_ATTR04_SET_USERFUNCTION_ENABLE == TRUE)
						case 7:
							result = R_DLMS_USER_ic04_obj07_att04_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ08_ATTR04_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ08_ATTR04_SET_USERFUNCTION_ENABLE == TRUE)
						case 8:
							result = R_DLMS_USER_ic04_obj08_att04_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ09_ATTR04_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ09_ATTR04_SET_USERFUNCTION_ENABLE == TRUE)
						case 9:
							result = R_DLMS_USER_ic04_obj09_att04_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ10_ATTR04_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ10_ATTR04_SET_USERFUNCTION_ENABLE == TRUE)
						case 10:
							result = R_DLMS_USER_ic04_obj10_att04_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ11_ATTR04_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ11_ATTR04_SET_USERFUNCTION_ENABLE == TRUE)
						case 11:
							result = R_DLMS_USER_ic04_obj11_att04_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ12_ATTR04_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ12_ATTR04_SET_USERFUNCTION_ENABLE == TRUE)
						case 12:
							result = R_DLMS_USER_ic04_obj12_att04_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ13_ATTR04_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ13_ATTR04_SET_USERFUNCTION_ENABLE == TRUE)
						case 13:
							result = R_DLMS_USER_ic04_obj13_att04_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ14_ATTR04_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ14_ATTR04_SET_USERFUNCTION_ENABLE == TRUE)
						case 14:
							result = R_DLMS_USER_ic04_obj14_att04_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ15_ATTR04_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ15_ATTR04_SET_USERFUNCTION_ENABLE == TRUE)
						case 15:
							result = R_DLMS_USER_ic04_obj15_att04_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ16_ATTR04_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ16_ATTR04_SET_USERFUNCTION_ENABLE == TRUE)
						case 16:
							result = R_DLMS_USER_ic04_obj16_att04_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS04_OBJ17_ATTR04_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ17_ATTR04_SET_USERFUNCTION_ENABLE == TRUE)
						case 17:
							result = R_DLMS_USER_ic04_obj17_att04_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							

						default:
							break;
					}

				}
				else
				{
					/* Nothing code here */
				}
				break;

			default:
				break;
		}
		p_params->result.result.data_access = (DataAccessResult_Value)result;
	}
	else if (p_params->req_type == REQ_TYPE_ACTION)
	{
		result = p_params->result.result.action;
		switch (p_params->descriptor.method.method_id)
		{
			case 1:
				if (p_params->distributor_state == DIST_AFTER_CLASS_FUNCTION)
				{

					switch(p_params->child_index)
					{
						case 16:
							result = R_DLMS_USER_ic04_obj16_meth01_action(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

						case 17:
							result = R_DLMS_USER_ic04_obj17_meth01_action(p_params, (void *)p_params->service_params.malloc.p_content);
							break;


						default:
							break;
					}

				}
				else
				{
					/* Nothing code here */
				}
				break;

			default:
				break;
		}
	
		p_params->result.result.action = (ActionResult_Value)result;
	}
	else
	{
	 /* Nothing code here */
	}
}

