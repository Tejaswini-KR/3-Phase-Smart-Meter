/***********************************************************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
************************************************************************************************************************
* File Name    : r_dlms_calendar
* Version      : 1.00
* Description  : Description
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
***********************************************************************************************************************/
// 16.12.2020 New create

#ifndef _R_DLMS_CTRL_LIMITER_H
#define _R_DLMS_CTRL_LIMITER_H

/**********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_cg_macrodriver.h" 

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/
/* Class 71 - limiter */
extern float32_t g_limiter_ThresholdNormal;
extern float32_t g_limiter_ThresholdEmergency;
extern uint32_t g_limiter_MinOverThresholdDuration;
extern uint32_t g_limiter_MinUnderThresholdDuration;

/* Class 70 - disconnect control */
extern uint8_t g_ctrl_ControlState;
extern uint8_t g_ctrl_ControlMode;
/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/
/* Class 71 - limiter */
uint8_t R_LIMITER_ThresholdActiveGet(float32_t * p_out_data);
uint8_t R_LIMITER_ThresholdNormalSet(float32_t * p_data_in);
uint8_t R_LIMITER_ThresholdEmergencySet(float32_t * p_data_in);
uint8_t R_LIMITER_MinOverThresholdDurationSet(uint32_t * p_data_in);
uint8_t R_LIMITER_MinUnderThresholdDurationSet(uint32_t * p_data_in);
uint8_t R_LIMITER_ActiveGet(uint8_t * p_data_in);		

/* Class 70 - disconnect control */
uint8_t R_CTRL_ControlModeSet(uint8_t * p_data_in);
uint8_t R_CTRL_DisconnectAction(void);
uint8_t R_CTRL_ConnectAction(void);
#endif /* _R_DLMS_CTRL_LIMITER_H */