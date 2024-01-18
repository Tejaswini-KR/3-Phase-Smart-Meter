/******************************************************************************
Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_usercode_class04.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023 
******************************************************************************/

#ifndef R_DLMS_USERCODE_CLASS04_H
#define R_DLMS_USERCODE_CLASS04_H


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_class04.h"
#include "r_dlms_user.h"
#include "r_dlms_type.h"
/******************************************************************************
Macro definitions
******************************************************************************/

/* Index: 00; Name: MD kW for TZ1; Logical name: 1.0.1.6.1.255 */
/* Attribute 02 */
#define  CLASS04_OBJ00_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ00_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)
/* Attribute 04 */
#define  CLASS04_OBJ00_ATTR04_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ00_ATTR04_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 01; Name: MD kW for TZ2; Logical name: 1.0.1.6.2.255 */
/* Attribute 02 */
#define  CLASS04_OBJ01_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ01_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)
/* Attribute 04 */
#define  CLASS04_OBJ01_ATTR04_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ01_ATTR04_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 02; Name: MD kW for TZ3; Logical name: 1.0.1.6.3.255 */
/* Attribute 02 */
#define  CLASS04_OBJ02_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ02_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)
/* Attribute 04 */
#define  CLASS04_OBJ02_ATTR04_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ02_ATTR04_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 03; Name: MD kW for TZ4; Logical name: 1.0.1.6.4.255 */
/* Attribute 02 */
#define  CLASS04_OBJ03_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ03_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)
/* Attribute 04 */
#define  CLASS04_OBJ03_ATTR04_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ03_ATTR04_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 04; Name: MD kW for TZ5; Logical name: 1.0.1.6.5.255 */
/* Attribute 02 */
#define  CLASS04_OBJ04_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ04_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)
/* Attribute 04 */
#define  CLASS04_OBJ04_ATTR04_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ04_ATTR04_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 05; Name: MD kW for TZ6; Logical name: 1.0.1.6.6.255 */
/* Attribute 02 */
#define  CLASS04_OBJ05_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ05_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)
/* Attribute 04 */
#define  CLASS04_OBJ05_ATTR04_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ05_ATTR04_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 06; Name: MD kW for TZ7; Logical name: 1.0.1.6.7.255 */
/* Attribute 02 */
#define  CLASS04_OBJ06_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ06_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)
/* Attribute 04 */
#define  CLASS04_OBJ06_ATTR04_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ06_ATTR04_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 07; Name: MD kW for TZ8; Logical name: 1.0.1.6.8.255 */
/* Attribute 02 */
#define  CLASS04_OBJ07_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ07_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)
/* Attribute 04 */
#define  CLASS04_OBJ07_ATTR04_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ07_ATTR04_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 08; Name: MD kVA for TZ1; Logical name: 1.0.9.6.1.255 */
/* Attribute 02 */
#define  CLASS04_OBJ08_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ08_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)
/* Attribute 04 */
#define  CLASS04_OBJ08_ATTR04_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ08_ATTR04_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 09; Name: MD kVA for TZ2; Logical name: 1.0.9.6.2.255 */
/* Attribute 02 */
#define  CLASS04_OBJ09_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ09_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)
/* Attribute 04 */
#define  CLASS04_OBJ09_ATTR04_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ09_ATTR04_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 10; Name: MD kVA for TZ3; Logical name: 1.0.9.6.3.255 */
/* Attribute 02 */
#define  CLASS04_OBJ10_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ10_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)
/* Attribute 04 */
#define  CLASS04_OBJ10_ATTR04_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ10_ATTR04_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 11; Name: MD kVA for TZ4; Logical name: 1.0.9.6.4.255 */
/* Attribute 02 */
#define  CLASS04_OBJ11_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ11_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)
/* Attribute 04 */
#define  CLASS04_OBJ11_ATTR04_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ11_ATTR04_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 12; Name: MD kVA for TZ5; Logical name: 1.0.9.6.5.255 */
/* Attribute 02 */
#define  CLASS04_OBJ12_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ12_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)
/* Attribute 04 */
#define  CLASS04_OBJ12_ATTR04_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ12_ATTR04_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 13; Name: MD kVA for TZ7; Logical name: 1.0.9.6.7.255 */
/* Attribute 02 */
#define  CLASS04_OBJ13_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ13_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)
/* Attribute 04 */
#define  CLASS04_OBJ13_ATTR04_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ13_ATTR04_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 14; Name: MD kVA for TZ8; Logical name: 1.0.9.6.8.255 */
/* Attribute 02 */
#define  CLASS04_OBJ14_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ14_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)
/* Attribute 04 */
#define  CLASS04_OBJ14_ATTR04_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ14_ATTR04_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 15; Name: MD kVA for TZ6; Logical name: 1.0.9.6.6.255 */
/* Attribute 02 */
#define  CLASS04_OBJ15_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ15_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)
/* Attribute 04 */
#define  CLASS04_OBJ15_ATTR04_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ15_ATTR04_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 16; Name: Maximum Demand  kVA; Logical name: 1.0.9.6.0.255 */
/* Attribute 02 */
#define  CLASS04_OBJ16_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ16_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)
/* Attribute 04 */
#define  CLASS04_OBJ16_ATTR04_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ16_ATTR04_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 17; Name: Maximum Demand kW; Logical name: 1.0.1.6.0.255 */
/* Attribute 02 */
#define  CLASS04_OBJ17_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ17_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)
/* Attribute 04 */
#define  CLASS04_OBJ17_ATTR04_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ17_ATTR04_SET_USERFUNCTION_ENABLE                  (FALSE)

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Variable Externs
******************************************************************************/
extern const scaler_unit_t g_dlms_ic04_obj00_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic04_obj01_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic04_obj02_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic04_obj03_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic04_obj04_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic04_obj05_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic04_obj06_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic04_obj07_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic04_obj08_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic04_obj09_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic04_obj10_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic04_obj11_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic04_obj12_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic04_obj13_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic04_obj14_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic04_obj15_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic04_obj16_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic04_obj17_att03_Scaler_Unit;

/******************************************************************************
Functions Prototypes
******************************************************************************/
uint8_t R_DLMS_USER_ic04_obj00_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj00_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj00_att04_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj00_att04_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj00_att05_get(distributor_params_t * p_params, date_time_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj01_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj01_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj01_att04_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj01_att04_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj01_att05_get(distributor_params_t * p_params, date_time_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj02_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj02_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj02_att04_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj02_att04_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj02_att05_get(distributor_params_t * p_params, date_time_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj03_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj03_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj03_att04_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj03_att04_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj03_att05_get(distributor_params_t * p_params, date_time_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj04_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj04_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj04_att04_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj04_att04_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj04_att05_get(distributor_params_t * p_params, date_time_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj05_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj05_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj05_att04_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj05_att04_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj05_att05_get(distributor_params_t * p_params, date_time_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj06_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj06_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj06_att04_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj06_att04_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj06_att05_get(distributor_params_t * p_params, date_time_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj07_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj07_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj07_att04_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj07_att04_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj07_att05_get(distributor_params_t * p_params, date_time_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj08_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj08_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj08_att04_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj08_att04_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj08_att05_get(distributor_params_t * p_params, date_time_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj09_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj09_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj09_att04_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj09_att04_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj09_att05_get(distributor_params_t * p_params, date_time_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj10_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj10_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj10_att04_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj10_att04_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj10_att05_get(distributor_params_t * p_params, date_time_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj11_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj11_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj11_att04_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj11_att04_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj11_att05_get(distributor_params_t * p_params, date_time_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj12_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj12_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj12_att04_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj12_att04_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj12_att05_get(distributor_params_t * p_params, date_time_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj13_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj13_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj13_att04_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj13_att04_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj13_att05_get(distributor_params_t * p_params, date_time_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj14_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj14_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj14_att04_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj14_att04_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj14_att05_get(distributor_params_t * p_params, date_time_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj15_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj15_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj15_att04_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj15_att04_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj15_att05_get(distributor_params_t * p_params, date_time_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj16_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj16_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj16_att04_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj16_att04_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj16_att05_get(distributor_params_t * p_params, date_time_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj16_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client);
uint8_t R_DLMS_USER_ic04_obj17_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj17_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj17_att04_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj17_att04_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj17_att05_get(distributor_params_t * p_params, date_time_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj17_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client);

#endif /* R_DLMS_USERCODE_CLASS04_H */