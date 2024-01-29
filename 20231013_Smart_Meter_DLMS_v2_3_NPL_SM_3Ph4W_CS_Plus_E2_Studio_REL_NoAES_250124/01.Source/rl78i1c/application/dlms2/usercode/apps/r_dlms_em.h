/***********************************************************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
************************************************************************************************************************
* File Name    : r_dlms_calendar
* Version      : 1.00
* Description  : Description
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
***********************************************************************************************************************/
// 21.12.2020 New create

#ifndef _R_DLMS_EM_H
#define _R_DLMS_EM_H

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
/* Class 01 */
extern uint16_t g_EM_MaxDemandIntegrationPeriod;
/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/

/* Class 01 */
uint8_t R_EM_MaxDemandIntegrationPeriodSet(uint16_t period);

#endif /* _R_DLMS_EM_H */