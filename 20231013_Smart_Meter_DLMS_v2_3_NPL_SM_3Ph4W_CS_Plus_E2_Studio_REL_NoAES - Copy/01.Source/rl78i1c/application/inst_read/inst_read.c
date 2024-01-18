/**********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2019 Renesas Electronics Corporation. All rights reserved.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * File Name    : inst_read.c
 * Version      : 1.0
 * Description  : Perform periodic snapshot of system parameters and shared globally
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         :
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
/* Driver */
#include "r_cg_macrodriver.h"   /* MD Macro Driver */
#include "r_cg_wdt.h"           /* MD WDT Driver */

/* Code Standard */
#include "typedef.h"            /* GSCE Standard Typedef */

/* EM */
#include "em_type.h"
#include "em_measurement.h"
#include "em_operation.h"

/* Application */
#include "inst_read.h"

/* Standard Library */
#include <string.h>

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#define INST_BUFFER_SIZE           (10)
#define SNAPSHOT_ENERGY_COUNTERS   (TRUE)

#ifndef BCD2DEC
#define BCD2DEC(x)  ((x & 0xF) + (x >> 4) * 10)
#endif

/**********************************************************************************************************************
 Local Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/

/* debug direct power output will override the inst direct power output */
#ifdef __DEBUG
volatile float32_t g_debug_direct_power_output_value = -1.0f;
#endif

float32_t g_inst_read_fixed_power_output_value = -1.0f;
uint8_t g_inst_read_is_fixed_power_output = 0;
uint8_t g_inst_read_snapshot_capture_state = 1;             /* Enable snapshot capture */

static uint8_t read_id = 0;
static uint8_t write_id = 0;
static s_capture_em_data_t inst_buff[INST_BUFFER_SIZE];

s_capture_em_data_t * gp_inst_DataPop = NULL;
s_capture_em_data_t * gp_inst_LastDataPop = &inst_buff[0];

EM_INST_READ_PARAMS g_inst_read_params;

void R_INST_DataPush(EM_INST_READ_PARAMS *p_snapshot_data);

/**********************************************************************************************************************
 Private (static) variables and functions
 *********************************************************************************************************************/

static void Convert_BcdRTC_To_DecimalRTC(rtc_counter_value_t *p_rtc_value_out, rtc_counter_value_t *p_rtc_value_in);
/******************************************************************************
* Function Name : Convert_BcdRTC_To_DecimalRTC
* Interface     : rtc_counter_value_t Convert_BcdRTC_To_DecimalRTC(rtc_counter_value_t *p_rtc_value)
* Description   :
* Arguments     : rtc_counter_value_t *p_rtc_value_out
*                 rtc_counter_value_t *p_rtc_value_in
* Return Value  : none
******************************************************************************/
static void Convert_BcdRTC_To_DecimalRTC(rtc_counter_value_t *p_rtc_value_out, rtc_counter_value_t *p_rtc_value_in)
{
	/* Convert from BCD to DEC */
	p_rtc_value_out->sec    = BCD2DEC(p_rtc_value_in->sec);
	p_rtc_value_out->min    = BCD2DEC(p_rtc_value_in->min);
	p_rtc_value_out->hour   = BCD2DEC(p_rtc_value_in->hour);
	p_rtc_value_out->day    = BCD2DEC(p_rtc_value_in->day);
	p_rtc_value_out->week   = BCD2DEC(p_rtc_value_in->week);
	p_rtc_value_out->month  = BCD2DEC(p_rtc_value_in->month);
	p_rtc_value_out->year   = BCD2DEC(p_rtc_value_in->year);
}

/**********************************************************************************************************************
* Function Name: void INST_READ_RTC_InterruptCallBack(void)
* Description  : 0.5s tick for reading system snapshot
*              : NOTE: please put this under 0.5s RTC
* Arguments    : None
* Return Value : None
 *********************************************************************************************************************/
void INST_READ_RTC_InterruptCallBack(void)
{

    static uint8_t count = 0;
    
    count++;
    
    if (count >= 2)
    {
        EM_LINE line;

        /* Update the parameter */
        for (line = LINE_PHASE_R; line <= LINE_TOTAL; line++)
        {
            /* VRMS */
            g_inst_read_params.vrms[line] = EM_GetVoltageRMS(line);

            /* IRMS */
            g_inst_read_params.irms[line] = EM_GetCurrentRMS(line);

            /* Line Frequency */
            g_inst_read_params.freq[line] = EM_GetLineFrequency(line);

            /* Power factor */
            g_inst_read_params.power_factor[line] = EM_GetPowerFactor(line);
            g_inst_read_params.power_factor_sign[line] = EM_GetPowerFactorSign(line);

            /* Active power */
            g_inst_read_params.active_power[line] = EM_GetActivePower(line);

            /* Reactive power */
            g_inst_read_params.reactive_power[line] = EM_GetReactivePower(line);

            /* Apparent power */
            g_inst_read_params.apparent_power[line] = EM_GetApparentPower(line);


            /* Fundamental VRMS */
            g_inst_read_params.fundamental_vrms[line] = EM_GetFundamentalVoltageRMS(line);

            /* Fundamental IRMS */
            g_inst_read_params.fundamental_irms[line] = EM_GetFundamentalCurrentRMS(line);

            /* Fundamental active power */
            g_inst_read_params.fundamental_power[line] = EM_GetFundamentalActivePower(line);

            /* Voltage THD */
            g_inst_read_params.voltage_thd[line] = EM_GetVoltageTHD(line) * 100.0f;

            /* Current THD */
            g_inst_read_params.current_thd[line] = EM_GetCurrentTHD(line) * 100.0f;

            /* Power THD */
            g_inst_read_params.power_thd[line] = EM_GetActivePowerTHD(line) * 100.0f;

            /* Current phase to phase angle */
            g_inst_read_params.current_phase_angle[line] = EM_GetCurrentPhaseAngle(line, (EM_LINE)((line + 1) % LINE_NEUTRAL));

            /* Current neutral to phase angle */
            g_inst_read_params.current_neutral_angle[line] = EM_GetCurrentPhaseAngle(LINE_NEUTRAL, line);

        }

        /* Voltage phase to phase angle */
        g_inst_read_params.phase_angle[LINE_PHASE_R] = EM_GetPhaseAngleRtoY();
        g_inst_read_params.phase_angle[LINE_PHASE_Y] = EM_GetPhaseAngleYtoB();
        g_inst_read_params.phase_angle[LINE_PHASE_B] = EM_GetPhaseAngleBtoR();


        /* Vector sum current, 3 decimal */
        g_inst_read_params.vector_sum_irms = EM_GetPhaseCurrentSumVector();

		{
	    	EM_OPERATION_DATA em_energy_data;
            EM_ENERGY_VALUE em_energy_value;
            
            /* Critical section, energy update in DSAD */
            DI();
	        EM_GetOperationData(&em_energy_data);
            EI();
            EM_EnergyDataToEnergyValue(&em_energy_data, &em_energy_value);
	        g_inst_read_params.active_energy_total_import           = em_energy_value.integer.active_imp        + em_energy_value.decimal.active_imp      ;
	        g_inst_read_params.active_energy_total_export           = em_energy_value.integer.active_exp        + em_energy_value.decimal.active_exp      ;
	        g_inst_read_params.reactive_energy_lag_total_import     = em_energy_value.integer.reactive_ind_imp  + em_energy_value.decimal.reactive_ind_imp;
	        g_inst_read_params.reactive_energy_lag_total_export     = em_energy_value.integer.reactive_ind_exp  + em_energy_value.decimal.reactive_ind_exp;
	        g_inst_read_params.reactive_energy_lead_total_import    = em_energy_value.integer.reactive_cap_imp  + em_energy_value.decimal.reactive_cap_imp;
	        g_inst_read_params.reactive_energy_lead_total_export    = em_energy_value.integer.reactive_cap_exp  + em_energy_value.decimal.reactive_cap_exp;
	        g_inst_read_params.apparent_energy_total_import         = em_energy_value.integer.apparent_imp      + em_energy_value.decimal.apparent_imp    ;
	        g_inst_read_params.apparent_energy_total_export         = em_energy_value.integer.apparent_exp      + em_energy_value.decimal.apparent_exp    ;
        }
        
        if (g_inst_read_snapshot_capture_state == 0)
        {
            /* Not pushing new snapshot to buffer */
        }
        else if (g_inst_read_snapshot_capture_state == 1)
        {
            /* Push snapshot to buffer */
            R_INST_DataPush(&g_inst_read_params);
        }
        else {
            /* Other case not supported yet */
        } 
        /* Reset counting, start updating system parameters as below */
        count = 0;
    }
}


/******************************************************************************
* Function Name : R_INST_DataPush
* Interface     : void R_INST_DataPush(EM_INST_READ_PARAMS *p_snapshot_data)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_INST_DataPush(EM_INST_READ_PARAMS *p_snapshot_data)
{
    /* Push snapshot data to array */
    inst_buff[write_id].value = *p_snapshot_data;
    R_RTC_Get_CalendarCounterValue(&inst_buff[write_id].capture_time);

    Convert_BcdRTC_To_DecimalRTC(&inst_buff[write_id].capture_time, &inst_buff[write_id].capture_time);

    /* Increase write id or reset to 0 if hit to the last index */
    if (write_id == (INST_BUFFER_SIZE - 1))
    {
        write_id = 0;
    }
    else
    {
        write_id++;
    }
}

/******************************************************************************
* Function Name : R_INST_LastDataPop
* Interface     : s_capture_em_data_t* R_INST_LastDataPop(void)
* Description   : 
* Arguments     :
* Return Value  : s_capture_em_data_t*
******************************************************************************/
s_capture_em_data_t* R_INST_LastDataPop(void)
{
    return (inst_buff + read_id);
}


/******************************************************************************
* Function Name : R_INST_DataPop
* Interface     : s_capture_em_data_t * R_INST_DataPop(void)
* Description   :
* Arguments     : None
* Return Value  : s_capture_em_data_t * 
*               : (NULL)   : Circuler buffer is empty
*               : Not NULL : Pointer to captured data
******************************************************************************/
s_capture_em_data_t * R_INST_DataPop(void)
{
    if (write_id == read_id)
    {
        gp_inst_DataPop = NULL;
    }
    else
    {
        gp_inst_DataPop = inst_buff + read_id;
        gp_inst_LastDataPop = gp_inst_DataPop;

        if (read_id == INST_BUFFER_SIZE - 1)
        {
            read_id = 0;
        }
        else
        {
            read_id++;
        }
    }
    
    return gp_inst_DataPop;
}

/******************************************************************************
* Function Name : R_INST_DataPopAll
* Interface     : void R_INST_DataPopAll(void)
* Description   : Pop out all snapshot in queue
*               :   gp_inst_DataPop NULL after final call
*               :   gp_inst_LastDataPop last pop out buffer
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_INST_DataPopAll(void)
{
    while (R_INST_DataPop() != NULL)
    {
        R_WDT_Restart();
    }
}

/******************************************************************************
* Function Name : R_INST_SetSnapshotCaptureState
* Interface     : void R_INST_SetSnapshotCaptureState(uint8_t state)
* Description   : Set snapshot capture state. This will affect snapshot push only
*               : Updating the g_inst_read_params, blink, tamper energy still normally
* Arguments     : uint8_t state
*               :   0: Not pushing snapshot to inst_buff
*               :   1: Push snapshot to inst_buff every 1s
*               :   Other value: invalid, not set
* Return Value  : None
******************************************************************************/
void R_INST_SetSnapshotCaptureState(uint8_t state)
{
    if (state == 0 || state == 1)
    {
        g_inst_read_snapshot_capture_state = state;
    }
    else
    {
        /* Invalid value, not set */
    }
}

/******************************************************************************
* Function Name: void R_INST_UpdateEnergyByPowerAndTime(
*              :     float32_t power,
*              :     float32_t second
*              : );
* Description  : Update the energy by power (watt) x time (seconds) (to import only)
* Arguments    : float32_t power  : Specifed active, apparent power value to accumulate the energy
*              : float32_t second : Time in second of power to calculate the energy
* Return Value : None
******************************************************************************/
void R_INST_UpdateEnergyByPowerAndTime(float32_t power, float32_t seconds)
{	
	EM_OPERATION_DATA em_energy_data;
    EM_ENERGY_VALUE em_energy_value;

    float32_t   wh_and_vah_counter;
    
    /* Calculate the energy base on power x time (1s for current snapshot period) */
    wh_and_vah_counter = (power * seconds) / (3600.0f);

    /* Initialize (clear) all energy counter */
    memset(&em_energy_value, 0, sizeof(em_energy_value));
	memset(&em_energy_data, 0, sizeof(em_energy_data));
    /* No reactive, active equal apparent (UPF) */
    em_energy_value.integer.active_imp = 
    em_energy_value.integer.apparent_imp = wh_and_vah_counter;
    em_energy_value.decimal.active_imp =
    em_energy_value.decimal.apparent_imp = wh_and_vah_counter - (uint32_t)wh_and_vah_counter;

    /* Call directly to EM and update the counter */
	EM_EnergyValueToEnergyData(&em_energy_data, &em_energy_value);
    EM_AddEnergyData(&em_energy_data);
}
