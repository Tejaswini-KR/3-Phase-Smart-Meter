/******************************************************************************
Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_usercode_class22.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023 
******************************************************************************/

#ifndef R_DLMS_USERCODE_CLASS22_H
#define R_DLMS_USERCODE_CLASS22_H


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_class22.h"
#include "r_dlms_user.h"
#include "r_dlms_type.h"
/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Variable Externs
******************************************************************************/
extern const class22_executed_script_t g_dlms_ic22_obj00_att02_executed_script;
extern const class22_exe_time_type_t g_dlms_ic22_obj00_att03_type;
extern const uint16_t r_dlms_ic22_obj00_att04_array_length;
extern const class22_executed_script_t g_dlms_ic22_obj01_att02_executed_script;
extern const class22_exe_time_type_t g_dlms_ic22_obj01_att03_type;
extern const uint16_t r_dlms_ic22_obj01_att04_array_length;
extern const class22_executed_script_t g_dlms_ic22_obj02_att02_executed_script;
extern const class22_exe_time_type_t g_dlms_ic22_obj02_att03_type;
extern const uint16_t r_dlms_ic22_obj02_att04_array_length;
extern const class22_executed_script_t g_dlms_ic22_obj03_att02_executed_script;
extern const class22_exe_time_type_t g_dlms_ic22_obj03_att03_type;
extern const uint16_t r_dlms_ic22_obj03_att04_array_length;

/******************************************************************************
Functions Prototypes
******************************************************************************/
uint8_t R_DLMS_USER_ic22_obj00_att04_get(distributor_params_t * p_params, class22_exe_time_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic22_obj00_att04_set(distributor_params_t * p_params, class22_exe_time_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic22_obj01_att04_get(distributor_params_t * p_params, class22_exe_time_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic22_obj01_att04_set(distributor_params_t * p_params, class22_exe_time_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic22_obj02_att04_get(distributor_params_t * p_params, class22_exe_time_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic22_obj02_att04_set(distributor_params_t * p_params, class22_exe_time_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic22_obj03_att04_get(distributor_params_t * p_params, class22_exe_time_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic22_obj03_att04_set(distributor_params_t * p_params, class22_exe_time_array_t * p_attribute_get);

#endif /* R_DLMS_USERCODE_CLASS22_H */