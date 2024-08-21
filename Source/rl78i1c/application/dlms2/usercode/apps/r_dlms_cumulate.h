/***********************************************************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
************************************************************************************************************************
* File Name    : r_dlms_cumulate
* Version      : v1.0
* Description  : Description
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
***********************************************************************************************************************/

#ifndef _R_DLMS_CUMULATE_H
#define _R_DLMS_CUMULATE_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "typedef.h"


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/

extern uint32_t g_dlms_program_cnt;                          /* (2 bytes) Programming counter                       */
/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/

uint8_t R_DLMS_Get_Counter (uint16_t counter_id, uint32_t *p_data);
uint8_t R_DLMS_Set_Counter (uint16_t counter_id, uint32_t data);


/* RESET */
uint8_t R_DLMS_Reset_BillingPON (void);

/* API */
uint8_t R_DLMS_Cumulative_PC(void);
uint8_t R_DLMS_Cumulative_BillingCounter (void);

uint8_t R_DLMS_FormatBillingCounter(void);
void R_DLMS_Shift_BillingCounter(uint8_t number_of_months_shift);

void R_DLMS_CumulateRestore(void);
void R_DLMS_CumulateBackup(void);
#endif /* _R_DLMS_CUMULATE_H */