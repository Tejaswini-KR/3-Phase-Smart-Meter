/******************************************************************************
Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_usercode_class03.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023 
******************************************************************************/

#ifndef R_DLMS_USERCODE_CLASS03_H
#define R_DLMS_USERCODE_CLASS03_H


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_class03.h"
#include "r_dlms_user.h"
#include "r_dlms_type.h"
/******************************************************************************
Macro definitions
******************************************************************************/

/* Index: 00; Name: System PF for billing period Import; Logical name: 1.0.13.0.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ00_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ00_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 01; Name: Billing date; Logical name: 0.0.0.1.2.255 */
/* Attribute 02 */
#define  CLASS03_OBJ01_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ01_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 02; Name: Cumulative Energy kVAh TZ1; Logical name: 1.0.9.8.1.255 */
/* Attribute 02 */
#define  CLASS03_OBJ02_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ02_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 03; Name: Cumulative Energy kVAh TZ2; Logical name: 1.0.9.8.2.255 */
/* Attribute 02 */
#define  CLASS03_OBJ03_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ03_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 04; Name: Cumulative Energy kWh TZ3; Logical name: 1.0.1.8.3.255 */
/* Attribute 02 */
#define  CLASS03_OBJ04_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ04_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 05; Name: Cumulative Energy kVAh TZ3; Logical name: 1.0.9.8.3.255 */
/* Attribute 02 */
#define  CLASS03_OBJ05_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ05_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 06; Name: Cumulative Energy kVAh TZ4; Logical name: 1.0.9.8.4.255 */
/* Attribute 02 */
#define  CLASS03_OBJ06_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ06_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 07; Name: Cumulative Energy kWh TZ1 ; Logical name: 1.0.1.8.1.255 */
/* Attribute 02 */
#define  CLASS03_OBJ07_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ07_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 08; Name: Cumulative Energy kWh TZ2; Logical name: 1.0.1.8.2.255 */
/* Attribute 02 */
#define  CLASS03_OBJ08_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ08_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 09; Name: Cumulative Energy kWh TZ4; Logical name: 1.0.1.8.4.255 */
/* Attribute 02 */
#define  CLASS03_OBJ09_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ09_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 10; Name: Billing power ON duration; Logical name: 0.0.94.91.13.255 */
/* Attribute 02 */
#define  CLASS03_OBJ10_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ10_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 11; Name: Cumulative Energy kWh TZ5; Logical name: 1.0.1.8.5.255 */
/* Attribute 02 */
#define  CLASS03_OBJ11_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ11_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 12; Name: Cumulative energy kWh TZ6; Logical name: 1.0.1.8.6.255 */
/* Attribute 02 */
#define  CLASS03_OBJ12_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ12_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 13; Name: Cumulative energy kVAh TZ5; Logical name: 1.0.9.8.5.255 */
/* Attribute 02 */
#define  CLASS03_OBJ13_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ13_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 14; Name: Cumulative energy kVAh TZ6; Logical name: 1.0.9.8.6.255 */
/* Attribute 02 */
#define  CLASS03_OBJ14_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ14_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 15; Name: Cumulative energy kWh for TZ7; Logical name: 1.0.1.8.7.255 */
/* Attribute 02 */
#define  CLASS03_OBJ15_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ15_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 16; Name: Cumulative energy kWh for TZ8; Logical name: 1.0.1.8.8.255 */
/* Attribute 02 */
#define  CLASS03_OBJ16_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ16_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 17; Name: Cumulative energy kVAh for TZ7; Logical name: 1.0.9.8.7.255 */
/* Attribute 02 */
#define  CLASS03_OBJ17_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ17_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 18; Name: Cumulative energy kVAh for TZ8; Logical name: 1.0.9.8.8.255 */
/* Attribute 02 */
#define  CLASS03_OBJ18_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ18_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 19; Name: Block Energy kVAh import BL; Logical name: 1.0.9.29.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ19_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ19_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 20; Name: Block Energy kVAh Export; Logical name: 1.0.10.29.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ20_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ20_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 21; Name: Block Energy kWh Import; Logical name: 1.0.1.29.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ21_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ21_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 22; Name: Block Energy kWh Export; Logical name: 1.0.2.29.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ22_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ22_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 23; Name: Current IR BL; Logical name: 1.0.31.27.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ23_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ23_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 24; Name: Voltage VRN BL; Logical name: 1.0.32.27.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ24_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ24_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 25; Name: Current IY BL; Logical name: 1.0.51.27.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ25_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ25_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 26; Name: Voltage VYN BL; Logical name: 1.0.52.27.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ26_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ26_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 27; Name: Current IB BL; Logical name: 1.0.71.27.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ27_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ27_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 28; Name: Voltage VBN BL; Logical name: 1.0.72.27.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ28_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ28_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 29; Name: Cumulative power OFF; Logical name: 0.0.94.91.8.255 */
/* Attribute 02 */
#define  CLASS03_OBJ29_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ29_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 30; Name: Current IR; Logical name: 1.0.31.7.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ30_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ30_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 31; Name: Current IY; Logical name: 1.0.51.7.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ31_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ31_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 32; Name: Signed power factor B phase; Logical name: 1.0.73.7.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ32_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ32_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 33; Name: Signed power factor R phase; Logical name: 1.0.33.7.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ33_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ33_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 34; Name: Signed power factor Y phase; Logical name: 1.0.53.7.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ34_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ34_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 35; Name: Three phase power factor PF; Logical name: 1.0.13.7.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ35_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ35_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 36; Name: Signed reactive power; Logical name: 1.0.3.7.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ36_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ36_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 37; Name: Cumulative energy Q1; Logical name: 1.0.5.8.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ37_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ37_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 38; Name: Cumulative energy Q2; Logical name: 1.0.6.8.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ38_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ38_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 39; Name: Cumulative energy Q3; Logical name: 1.0.7.8.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ39_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ39_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 40; Name: Cumulative energy Q4; Logical name: 1.0.8.8.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ40_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ40_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 41; Name: Cumulative Energy kWh Export; Logical name: 1.0.2.8.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ41_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ41_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 42; Name: Cumulative Energy kVAh Export; Logical name: 1.0.10.8.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ42_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ42_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 43; Name: Current IB; Logical name: 1.0.71.7.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ43_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ43_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 44; Name: Voltage VBN; Logical name: 1.0.72.7.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ44_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ44_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 45; Name: Voltage VRN; Logical name: 1.0.32.7.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ45_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ45_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 46; Name: Voltage VYN; Logical name: 1.0.52.7.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ46_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ46_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 47; Name: Signed Active Power  ; Logical name: 1.0.1.7.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ47_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ47_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 48; Name: Apparent Power; Logical name: 1.0.9.7.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ48_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ48_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 49; Name: Frequency; Logical name: 1.0.14.7.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ49_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ49_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 50; Name: Cumulative Energy kVAh Import; Logical name: 1.0.9.8.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ50_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ50_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 51; Name: Cumulative Energy kWh import; Logical name: 1.0.1.8.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ51_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ51_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 52; Name: Cumulative Energy kWh ; Logical name: 1.0.1.9.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ52_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ52_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Variable Externs
******************************************************************************/
extern const scaler_unit_t g_dlms_ic03_obj00_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj01_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj02_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj03_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj04_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj05_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj06_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj07_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj08_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj09_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj10_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj11_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj12_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj13_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj14_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj15_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj16_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj17_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj18_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj19_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj20_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj21_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj22_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj23_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj24_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj25_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj26_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj27_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj28_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj29_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj30_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj31_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj32_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj33_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj34_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj35_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj36_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj37_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj38_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj39_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj40_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj41_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj42_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj43_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj44_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj45_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj46_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj47_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj48_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj49_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj50_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj51_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj52_att03_Scaler_Unit;

/******************************************************************************
Functions Prototypes
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj00_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj00_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj01_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj01_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj02_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj02_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj03_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj03_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj04_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj04_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj05_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj05_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj06_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj06_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj07_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj07_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj08_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj08_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj09_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj09_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj10_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj10_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj11_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj11_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj12_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj12_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj13_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj13_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj14_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj14_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj15_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj15_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj16_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj16_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj17_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj17_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj18_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj18_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj19_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj19_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj20_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj20_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj21_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj21_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj22_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj22_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj23_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj23_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj24_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj24_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj25_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj25_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj26_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj26_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj27_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj27_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj28_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj28_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj29_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj29_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj30_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj30_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj31_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj31_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj32_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj32_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj33_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj33_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj34_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj34_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj35_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj35_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj36_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj36_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj37_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj37_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj38_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj38_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj39_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj39_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj40_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj40_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj41_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj41_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj42_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj42_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj43_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj43_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj44_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj44_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj45_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj45_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj46_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj46_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj47_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj47_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj48_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj48_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj49_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj49_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj50_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj50_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj51_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj51_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj52_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj52_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);

#endif /* R_DLMS_USERCODE_CLASS03_H */