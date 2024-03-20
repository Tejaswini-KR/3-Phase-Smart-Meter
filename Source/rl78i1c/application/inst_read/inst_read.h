/******************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : dataflash.h
* Version      : 1.00
* Description  : Data Flash Application Layer APIs
******************************************************************************
* History : DD.MM.YYYY Version Description
******************************************************************************/

#ifndef _INST_READ_H
#define _INST_READ_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_wdt.h"           /* MD WDT Driver */
#include "r_cg_rtc.h"
#include "em_type.h"
#include "typedef.h"        /* GSCE Standard Typedef */

#include "em_constraint.h"
#include "em_type.h"
/******************************************************************************
Typedef definitions
******************************************************************************/
typedef struct tagEMInstantRead
{
    float32_t   vrms[EM_CALC_NUM_OF_LINE];
    float32_t   irms[EM_CALC_NUM_OF_LINE];
    float32_t   freq[EM_CALC_NUM_OF_LINE];
    float32_t   vector_sum_irms;

    float32_t   power_factor[EM_CALC_NUM_OF_LINE];
    EM_PF_SIGN  power_factor_sign[EM_CALC_NUM_OF_LINE];

    float32_t   active_power[EM_CALC_NUM_OF_LINE];
    float32_t   apparent_power[EM_CALC_NUM_OF_LINE];
    float32_t   reactive_power[EM_CALC_NUM_OF_LINE];
    float32_t   phase_angle[EM_VOL_CHANNEL_NUM];
    float32_t   current_phase_angle[EM_CALC_NUM_OF_LINE];
    float32_t   current_neutral_angle[EM_CALC_NUM_OF_LINE];
    float32_t   fundamental_power[EM_CALC_NUM_OF_LINE];
    float32_t   fundamental_vrms[EM_CALC_NUM_OF_LINE];
    float32_t   fundamental_irms[EM_CALC_NUM_OF_LINE];
    float32_t   voltage_thd[EM_CALC_NUM_OF_LINE];
    float32_t   current_thd[EM_CALC_NUM_OF_LINE];
    float32_t   power_thd[EM_CALC_NUM_OF_LINE];

	float32_t     active_energy_total_import;
    float32_t     active_energy_total_export;
    float32_t     reactive_energy_lag_total_import;
    float32_t     reactive_energy_lag_total_export;
    float32_t     reactive_energy_lead_total_import;
    float32_t     reactive_energy_lead_total_export;
    float32_t     apparent_energy_total_import;
    float32_t     apparent_energy_total_export;

} EM_INST_READ_PARAMS;

typedef struct tag_capture_em_data
{
    EM_INST_READ_PARAMS value;
    rtc_counter_value_t capture_time; 
} s_capture_em_data_t;

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Variable Externs
******************************************************************************/
extern EM_INST_READ_PARAMS g_inst_read_params;
extern s_capture_em_data_t * gp_inst_DataPop;
extern s_capture_em_data_t * gp_inst_LastDataPop;

/******************************************************************************
Functions Prototypes
******************************************************************************/
void INST_READ_RTC_InterruptCallBack(void);
s_capture_em_data_t * R_INST_DataPop(void);
s_capture_em_data_t * R_INST_LastDataPop(void);
void R_INST_DataPopAll(void);
void R_INST_SetSnapshotCaptureState(uint8_t state);

void R_INST_UpdateEnergyByPowerAndTime(float32_t power, float32_t seconds);

#endif /* _INST_READ_H */
