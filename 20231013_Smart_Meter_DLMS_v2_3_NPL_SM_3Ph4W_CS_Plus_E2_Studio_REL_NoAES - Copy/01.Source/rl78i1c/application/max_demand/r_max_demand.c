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
/* Copyright (C) 2011 Renesas Electronics Corporation. All rights reserved.  */
/****************************************************************************** 
* File Name    : r_max_demand.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : Energy max demand functions
******************************************************************************
* History : DD.MM.YYYY Version Description
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_wdt.h"
#include <string.h>

/* Wrapper */
#include "wrp_app_ext.h"

/* Application */
#include "r_max_demand.h"
#include "r_tariff.h"
#include "inst_read.h"
#include "r_meter_format.h"
#include "storage.h"

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Macro definitions
******************************************************************************/
#define MDM_SCALING_DIVISOR              (1000.0f)

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
r_mdm_t g_mdm;

MDM_FUNC void r_mdm_convert_tariff_to_mdm_counter(r_mdm_counter_t * p_mdm_counter, r_tariff_counter_t * p_tariff_counter);
MDM_FUNC float32_t r_mdm_integrate_energy(float32_t energy, uint16_t seconds);
MDM_FUNC float32_t r_mdm_measurement_get_current_max_value_by_energy_type(uint16_t offset);
MDM_FUNC float32_t r_mdm_measurement_get_current_average_demand_by_energy_type(uint16_t mdm_offset, uint16_t tariff_offset);

/******************************************************************************
* Function Name: void r_mdm_convert_tariff_to_mdm_counter(r_mdm_counter_t * p_mdm_counter, r_tariff_counter_t * p_tariff_counter)
* Description  : Convert tariff to mdm counter
* Arguments    : r_mdm_counter_t * p_mdm_counter: pointer to output max demand counter
*              : r_tariff_counter_t * p_tariff_counter: pointer to input tariff counter
* Return Value : None
******************************************************************************/
MDM_FUNC void r_mdm_convert_tariff_to_mdm_counter(r_mdm_counter_t * p_mdm_counter, r_tariff_counter_t * p_tariff_counter)
{
    p_mdm_counter->active                  = p_tariff_counter->active_imp;
    p_mdm_counter->reactive_cap            = p_tariff_counter->reactive_cap_imp;
    p_mdm_counter->reactive_ind            = p_tariff_counter->reactive_ind_imp;
    p_mdm_counter->apparent                = p_tariff_counter->apparent_imp;
}

/******************************************************************************
* Function Name: float32_t r_mdm_integrate_energy(float32_t energy, uint16_t seconds)
* Description  : MDM Helper function: integrate the energy in a period of seconds
* Arguments    : float32_t energy: accumulated energy
*              : uint16_t seconds: time duration for the above accumulated energy
* Return Value : float32_t: derived power value
******************************************************************************/
MDM_FUNC float32_t r_mdm_integrate_energy(float32_t energy, uint16_t seconds)
{
    return (energy / ((float32_t)seconds / 3600.0f));
}

/******************************************************************************
* Function Name: float32_t r_mdm_measurement_get_current_max_value_by_energy_type(uint16_t offset)
* Description  : MDM Get current max demand value of a specific counter
* Arguments    : float32_t *p_max_value: output pointer to max demand value
*              : uint16_t offset: byte offset from counter to max demand counter structure
* Return Value : None
******************************************************************************/
MDM_FUNC float32_t r_mdm_measurement_get_current_max_value_by_energy_type(uint16_t offset)
{
    float32_t result;
    EPR_Read(
        STORAGE_EEPROM_ENERGY_MDM_MAX_VALUE_ADDR + offset,
        (uint8_t *)&result,
        sizeof(float32_t)
    );
    return result / MDM_SCALING_DIVISOR;
}

/******************************************************************************
* Function Name: float32_t r_mdm_measurement_get_timezone_max_value_by_energy_type(uint8_t tariff_no, uint16_t offset)
* Description  : MDM Get current max demand value of a specific counter
* Arguments    : float32_t *p_max_value: output pointer to max demand value
*              : uint16_t offset: byte offset from counter to max demand counter structure
	           : uint8_t tariff_no: tariff number
* Return Value : None
******************************************************************************/
MDM_FUNC float32_t r_mdm_measurement_get_timezone_max_value_by_energy_type(uint8_t tariff_no, uint16_t offset)
{
    float32_t result;
    EPR_Read(
        STORAGE_EEPROM_ENERGY_MDM_MAX_VALUE_TZ_ADDR + (tariff_no * sizeof(r_mdm_counter_t)) + offset,
        (uint8_t *)&result,
        sizeof(float32_t)
    );
    return result / MDM_SCALING_DIVISOR;
}

/******************************************************************************
* Function Name: void R_MDM_Init(void)
* Description  : Initialization for max demand application
* Arguments    : None
* Return Value : None
******************************************************************************/
MDM_FUNC void R_MDM_Init(void)
{

}

/******************************************************************************
* Function Name: void R_MDM_PollingProcessing(void)
* Description  : Polling processing for max demand
* Arguments    : None
* Return Value : None
******************************************************************************/
MDM_FUNC void R_MDM_PollingProcessing(void)
{
    /* Update capture time from snapshot */
    if (gp_inst_DataPop != NULL)
    {
        g_mdm.last_read_capture_time_snapshot = gp_inst_DataPop->capture_time;
    }

    /* Process max demand period end */
    if (g_event_request_flag.is_max_demand_end)
    {
        uint16_t period_in_seconds;
        uint8_t i;
        uint8_t bChangedValue = 0;
		uint8_t current_tariff;
        r_mdm_counter_t demand_counter;
        r_mdm_counter_t max_demand_counter;
		r_mdm_counter_t tz_max_demand_counter;
        r_mdm_counter_t current_demand_counter;
        r_mdm_counter_t temporary_demand_counter;
        r_tariff_counter_t tariff_counter;
		
		current_tariff = g_tariff.current_tariff_no;
        /* Get total energy counter from tariff to calculate (from snapshot also) */
        R_TARIFF_GetTotalEnergyCounter(&tariff_counter);
        r_mdm_convert_tariff_to_mdm_counter(&current_demand_counter, &tariff_counter);

        /* Calculate the accumulated energy for max demand calculation */
        demand_counter.active       = current_demand_counter.active         - g_mdm.last_period_counter.active;
        demand_counter.reactive_cap = current_demand_counter.reactive_cap   - g_mdm.last_period_counter.reactive_cap;
        demand_counter.reactive_ind = current_demand_counter.reactive_ind   - g_mdm.last_period_counter.reactive_ind;
        demand_counter.apparent     = current_demand_counter.apparent       - g_mdm.last_period_counter.apparent;

        /* Assign back the last period counter */
        g_mdm.last_period_counter = current_demand_counter;
        g_mdm.start_time = g_mdm.last_read_capture_time_snapshot;
        /* Round up to nearest period block */
        g_mdm.start_time.sec = 0;
        g_mdm.start_time.min = ((uint16_t)g_mdm.start_time.min / g_demand_integration_period) * g_demand_integration_period;

        /* Integrate the energy to get demand power for this period */
        period_in_seconds = (uint16_t)g_demand_integration_period * 60;
        demand_counter.active       = r_mdm_integrate_energy(demand_counter.active, period_in_seconds);
        demand_counter.reactive_cap = r_mdm_integrate_energy(demand_counter.reactive_cap, period_in_seconds);
        demand_counter.reactive_ind = r_mdm_integrate_energy(demand_counter.reactive_ind, period_in_seconds);
        demand_counter.apparent     = r_mdm_integrate_energy(demand_counter.apparent, period_in_seconds);

        /* Push this period demand counter into buffer */
        EPR_Write(
            STORAGE_EEPROM_ENERGY_MDM_MOVING_AVERAGE_BUFFER_ADDR +
            (g_mdm.period_index * sizeof(r_mdm_counter_t)),
            (uint8_t *)&demand_counter,
            sizeof(r_mdm_counter_t)
        );

        /* Average the buffer */
        memset(&demand_counter, 0, sizeof(r_mdm_counter_t));
        for (i = 0; i < g_demand_number_of_period; i++)
        {
            EPR_Read(
                STORAGE_EEPROM_ENERGY_MDM_MOVING_AVERAGE_BUFFER_ADDR +
                (i * sizeof(r_mdm_counter_t)),
                (uint8_t *)&temporary_demand_counter,
                sizeof(r_mdm_counter_t)
            );
            /* Add up the average counter */
            demand_counter.active       += temporary_demand_counter.active;
            demand_counter.reactive_cap += temporary_demand_counter.reactive_cap;
            demand_counter.reactive_ind += temporary_demand_counter.reactive_ind;
            demand_counter.apparent     += temporary_demand_counter.apparent;
        }
        /* Average the result */
        demand_counter.active       /= g_demand_number_of_period;
        demand_counter.reactive_cap /= g_demand_number_of_period;
        demand_counter.reactive_ind /= g_demand_number_of_period;
        demand_counter.apparent     /= g_demand_number_of_period;
        
        /* Is max demand interval end (period * number of period)? */
        g_mdm.period_index++;
        if (g_mdm.period_index >= g_demand_number_of_period)
        {
            /* Update the max demand for this period */
            g_mdm.period_index = 0;

            /* Get max demand of current tariff from EEPROM */
            EPR_Read(
                STORAGE_EEPROM_ENERGY_MDM_MAX_VALUE_TZ_ADDR + (current_tariff * sizeof(r_mdm_counter_t)),
                (uint8_t *)&tz_max_demand_counter,
                sizeof(r_mdm_counter_t)
            );
            
            bChangedValue = 0;

            /* Check if there's new max demand */
            if (tz_max_demand_counter.active < demand_counter.active)
            {
                tz_max_demand_counter.active = demand_counter.active;
                bChangedValue = 1;	
				/* Update capture time for new max active */
				EPR_Write(
                    STORAGE_EEPROM_ENERGY_MDM_MAX_ACTIVE_TZ_CAPTURE_TIME_ADDR + (current_tariff * sizeof(rtc_counter_value_t)),
                    (uint8_t *)&g_mdm.last_read_capture_time_snapshot,
                    sizeof(rtc_counter_value_t)
                );
            }
			
            if (tz_max_demand_counter.reactive_cap < demand_counter.reactive_cap)
            {
                tz_max_demand_counter.reactive_cap = demand_counter.reactive_cap;
                bChangedValue = 1;
            }
			
            if (tz_max_demand_counter.reactive_ind < demand_counter.reactive_ind)
            {
                tz_max_demand_counter.reactive_ind = demand_counter.reactive_ind;
                bChangedValue = 1;
            }
			
            if (tz_max_demand_counter.apparent < demand_counter.apparent)
            {
                tz_max_demand_counter.apparent = demand_counter.apparent;
                bChangedValue = 1;				
				/* Update capture time for new max apparent */
				EPR_Write(
                    STORAGE_EEPROM_ENERGY_MDM_MAX_APPARENT_TZ_CAPTURE_TIME_ADDR + (current_tariff * sizeof(rtc_counter_value_t)),
                    (uint8_t *)&g_mdm.last_read_capture_time_snapshot,
                    sizeof(rtc_counter_value_t)
                );
            }

            /* Update the new max demand for current tariff */
            if (bChangedValue) 
            {
                EPR_Write(
                    STORAGE_EEPROM_ENERGY_MDM_MAX_VALUE_TZ_ADDR + (current_tariff * sizeof(r_mdm_counter_t)),
                    (uint8_t *)&tz_max_demand_counter,
                    sizeof(r_mdm_counter_t)
                );
			
				/* Continue checking max demand for energy total if max demand of current tariff is updated */
				bChangedValue = 0;
				
				/* Get max demand of energy total from EEPROM */
	            EPR_Read(
	                STORAGE_EEPROM_ENERGY_MDM_MAX_VALUE_ADDR,
	                (uint8_t *)&max_demand_counter,
	                sizeof(r_mdm_counter_t)
	            );

	            /* Check if there's new max demand */
	            if (max_demand_counter.active < demand_counter.active)
	            {
	                max_demand_counter.active = demand_counter.active;
					
					/* Update capture time for new max active of energy total */
					EPR_Write(
	                    STORAGE_EEPROM_ENERGY_MDM_MAX_ACTIVE_CAPTURE_TIME_ADDR,
	                    (uint8_t *)&g_mdm.last_read_capture_time_snapshot,
	                    sizeof(rtc_counter_value_t)
	                );
	                bChangedValue = 1;
	            }
	            if (max_demand_counter.reactive_cap < demand_counter.reactive_cap)
	            {
	                max_demand_counter.reactive_cap = demand_counter.reactive_cap;
	                bChangedValue = 1;
	            }
	            if (max_demand_counter.reactive_ind < demand_counter.reactive_ind)
	            {
	                max_demand_counter.reactive_ind = demand_counter.reactive_ind;
	                bChangedValue = 1;
	            }
	            if (max_demand_counter.apparent < demand_counter.apparent)
	            {
	                max_demand_counter.apparent = demand_counter.apparent;
					
					/* Update capture time for new max apparent of energy total */
					EPR_Write(
	                    STORAGE_EEPROM_ENERGY_MDM_MAX_APPARENT_CAPTURE_TIME_ADDR,
	                    (uint8_t *)&g_mdm.last_read_capture_time_snapshot,
	                    sizeof(rtc_counter_value_t)
	                );
	                bChangedValue = 1;
	            }

	            /* Update the new max demand for energy total */
	            if (bChangedValue) 
	            {
	                EPR_Write(
	                    STORAGE_EEPROM_ENERGY_MDM_MAX_VALUE_ADDR,
	                    (uint8_t *)&max_demand_counter,
	                    sizeof(r_mdm_counter_t)
	                );
	            }
					
            }
        }

        /* Store last average counter */
        g_mdm.last_average_value = demand_counter;

	    g_event_request_flag.is_max_demand_end = 0;
    }
}

/******************************************************************************
* Function Name: uint8_t R_MDM_Reset(ENERGY_SOURCE source)
* Description  : Reset max demand value
* Arguments    : ENERGY_SOURCE source: Max demand source (active, [reactive], apparent, all)
* Return Value : uint8_t, execution status
*              : MDM_RET_OK               Normal end
******************************************************************************/
MDM_FUNC uint8_t R_MDM_Reset(void)
{
    r_mdm_counter_t capture_start_demand_counter;
    r_tariff_counter_t tariff_counter;

    /* Capture current total energy counter */
    R_TARIFF_GetTotalEnergyCounter(&tariff_counter);
    r_mdm_convert_tariff_to_mdm_counter(&capture_start_demand_counter, &tariff_counter);
	
    /* Reset state, update last period counter and keep last read capture time snapshot */
    g_mdm.last_period_counter = capture_start_demand_counter;
    g_mdm.start_time = g_mdm.last_read_capture_time_snapshot;
    memset((uint8_t *)&g_mdm.last_average_value, 0, sizeof(r_mdm_counter_t));
    g_mdm.period_index = 0;

	R_MDM_Format();
	
    /* Backup state to EEPROM */
    EPR_Write(
        STORAGE_EEPROM_ENERGY_MDM_STATE_ADDR,
        (uint8_t *)&g_mdm,
        STORAGE_EEPROM_ENERGY_MDM_STATE_SIZE
    );

    /* Reset max demand capture time of total energy */
    EPR_Write(
        STORAGE_EEPROM_ENERGY_MDM_MAX_ACTIVE_CAPTURE_TIME_ADDR,
        (uint8_t *)&g_mdm.last_read_capture_time_snapshot,
        STORAGE_EEPROM_ENERGY_MDM_MAX_ACTIVE_CAPTURE_TIME_SIZE
    );
	EPR_Write(
        STORAGE_EEPROM_ENERGY_MDM_MAX_APPARENT_CAPTURE_TIME_ADDR,
        (uint8_t *)&g_mdm.last_read_capture_time_snapshot,
        STORAGE_EEPROM_ENERGY_MDM_MAX_APPARENT_CAPTURE_TIME_SIZE
    );

    return MDM_RET_OK;
}

/******************************************************************************
 * Function Name: R_MDM_NextPeriod
 * Description  : Terminate the current period, calculate demand, update max value and capture time
 * Arguments    : rtc_counter_value_t *p_input_time
 * Return Value : void
******************************************************************************/
MDM_FUNC void R_MDM_NextPeriod(rtc_counter_value_t *p_input_time)
{
    uint16_t    real_pos, active_pos;

    real_pos = (((uint16_t)p_input_time->hour) * 60 + p_input_time->min) / g_demand_integration_period;
    active_pos = (((uint16_t)g_mdm.start_time.hour) * 60 + g_mdm.start_time.min) / g_demand_integration_period;
    
    /* Check if different days or blocks */
    if (p_input_time->year  != g_mdm.start_time.year   ||
        p_input_time->month != g_mdm.start_time.month  ||
        p_input_time->day   != g_mdm.start_time.day    ||
        real_pos            != active_pos ||
        (0))
    {
        /* Integration period changed, conclude the current period and start new period */
        g_event_request_flag.is_max_demand_end = 1;
        /* Manually sync max demand last capture time */
        g_mdm.last_read_capture_time_snapshot = *p_input_time;
        R_MDM_PollingProcessing();
    }
    else
    {
        /* Integration period not changed */
    }
}

/******************************************************************************
* Function Name: float32_t R_MDM_GetActiveMaxDemand(void)
* Description  : Measurement API (present in kW)
* Arguments    : None
* Return Value : float32_t, the active max demand value
******************************************************************************/
MDM_FUNC float32_t R_MDM_GetActiveMaxDemand(void)
{
    return r_mdm_measurement_get_current_max_value_by_energy_type(offsetof(r_mdm_counter_t, active));
}

/******************************************************************************
* Function Name: float32_t R_MDM_GetCapacitiveReactiveMaxDemand(void)
* Description  : Measurement API (present in kVAr)
* Arguments    : None
* Return Value : float32_t, the reactive max demand value
******************************************************************************/
MDM_FUNC float32_t R_MDM_GetCapacitiveReactiveMaxDemand(void)
{
    return r_mdm_measurement_get_current_max_value_by_energy_type(offsetof(r_mdm_counter_t, reactive_cap));
}

/******************************************************************************
* Function Name: float32_t R_MDM_GetInductiveReactiveMaxDemand(void)
* Description  : Measurement API (present in kVAr)
* Arguments    : None
* Return Value : float32_t, the reactive max demand value
******************************************************************************/
MDM_FUNC float32_t R_MDM_GetInductiveReactiveMaxDemand(void)
{
    return r_mdm_measurement_get_current_max_value_by_energy_type(offsetof(r_mdm_counter_t, reactive_ind));
}

/******************************************************************************
* Function Name: float32_t R_MDM_GetApparentMaxDemand(void)
* Description  : Measurement API (present in kVA)
* Arguments    : None
* Return Value : float32_t, the apparent max demand value
******************************************************************************/
MDM_FUNC float32_t R_MDM_GetApparentMaxDemand(void)
{
    return r_mdm_measurement_get_current_max_value_by_energy_type(offsetof(r_mdm_counter_t, apparent));
}

/******************************************************************************
* Function Name: uint8_t R_MDM_GetActiveMaxDemandCapturedTime(rtc_counter_value_t * p_rtc)
* Description  : MDM Get captured time when max demand value changed
* Arguments    : rtc_counter_value_t * p_rtc: output pointer to energy rtc
* Return Value : None
******************************************************************************/
MDM_FUNC uint8_t R_MDM_GetActiveMaxDemandCapturedTime(rtc_counter_value_t * p_rtc)
{
	if (p_rtc == NULL)
    {
        return MDM_RET_ERROR_PARAMS;
    }
	else 
	{
	    EPR_Read(
	        STORAGE_EEPROM_ENERGY_MDM_MAX_ACTIVE_CAPTURE_TIME_ADDR,
	        (uint8_t *)p_rtc,
	        STORAGE_EEPROM_ENERGY_MDM_MAX_ACTIVE_CAPTURE_TIME_SIZE
	    );
		return MDM_RET_OK;
	}
}

/******************************************************************************
* Function Name: uint8_t R_MDM_GetApparentMaxDemandCapturedTime(rtc_counter_value_t * p_rtc)
* Description  : MDM Get captured time when max demand value changed
* Arguments    : rtc_counter_value_t * p_rtc: output pointer to energy rtc
* Return Value : None
******************************************************************************/
MDM_FUNC uint8_t R_MDM_GetApparentMaxDemandCapturedTime(rtc_counter_value_t * p_rtc)
{
    if (p_rtc == NULL)
    {
         return MDM_RET_ERROR_PARAMS;
    }
	else
	{
	    EPR_Read(
	        STORAGE_EEPROM_ENERGY_MDM_MAX_APPARENT_CAPTURE_TIME_ADDR,
	        (uint8_t *)p_rtc,
	        STORAGE_EEPROM_ENERGY_MDM_MAX_APPARENT_CAPTURE_TIME_SIZE
	    );
		return MDM_RET_OK;
	}
}


/******************************************************************************
* Function Name: uint8_t R_MDM_GetActiveMaxDemandTz(uint8_t tariff_no, float32_t * p_result)
* Description  : Measurement API (present in kW)
* Arguments    : uint8_t tariff_no: tariff number
* Return Value : float32_t, the active max demand value of timezone
******************************************************************************/
MDM_FUNC uint8_t R_MDM_GetActiveMaxDemandTz(uint8_t tariff_no, float32_t * p_result)
{
	if ((tariff_no > (SCHEDULER_NUMBER_OF_TARIFF_TIMESLOT_MAX - 1)) || (p_result == NULL))
	{
        return MDM_RET_ERROR_PARAMS;
    }
    else 
	{
		*p_result = r_mdm_measurement_get_timezone_max_value_by_energy_type(tariff_no, offsetof(r_mdm_counter_t, active));
    	return MDM_RET_OK;
	}
}

/******************************************************************************
* Function Name: uint8_t R_MDM_GetCapacitiveReactiveMaxDemandTz(uint8_t tariff_no, float32_t * p_result)
* Description  : Measurement API (present in kVAr)
* Arguments    : uint8_t tariff_no: tariff number
* Return Value : float32_t, the reactive max demand value of timezone
******************************************************************************/
MDM_FUNC uint8_t R_MDM_GetCapacitiveReactiveMaxDemandTz(uint8_t tariff_no, float32_t * p_result)
{
	if ((tariff_no > (SCHEDULER_NUMBER_OF_TARIFF_TIMESLOT_MAX - 1)) || (p_result == NULL))
	{
        return MDM_RET_ERROR_PARAMS;
    }
    else 
	{
		*p_result = r_mdm_measurement_get_timezone_max_value_by_energy_type(tariff_no, offsetof(r_mdm_counter_t, reactive_cap));
    	return MDM_RET_OK;
	}
}

/******************************************************************************
* Function Name: uint8_t R_MDM_GetInductiveReactiveMaxDemandTz(uint8_t tariff_no, float32_t * p_result)
* Description  : Measurement API (present in kVAr)
* Arguments    : uint8_t tariff_no: tariff number
* Return Value : float32_t, the reactive max demand value of timezone
******************************************************************************/
MDM_FUNC uint8_t R_MDM_GetInductiveReactiveMaxDemandTz(uint8_t tariff_no, float32_t * p_result)
{
	if ((tariff_no > (SCHEDULER_NUMBER_OF_TARIFF_TIMESLOT_MAX - 1)) || (p_result == NULL))
	{
        return MDM_RET_ERROR_PARAMS;
    }
    else 
	{
		*p_result = r_mdm_measurement_get_timezone_max_value_by_energy_type(tariff_no, offsetof(r_mdm_counter_t, reactive_ind));
    	return MDM_RET_OK;
	}
}

/******************************************************************************
* Function Name: uint8_t R_MDM_GetApparentMaxDemandTz(uint8_t tariff_no, float32_t * p_result)
* Description  : Measurement API (present in kVA)
* Arguments    : uint8_t tariff_no: tariff number
* Return Value : float32_t, the apparent max demand value of timezone
******************************************************************************/
MDM_FUNC uint8_t R_MDM_GetApparentMaxDemandTz(uint8_t tariff_no, float32_t * p_result)
{
	if ((tariff_no > (SCHEDULER_NUMBER_OF_TARIFF_TIMESLOT_MAX - 1)) || (p_result == NULL))
	{
        return MDM_RET_ERROR_PARAMS;
    }
    else 
	{
		*p_result = r_mdm_measurement_get_timezone_max_value_by_energy_type(tariff_no, offsetof(r_mdm_counter_t, apparent));
    	return MDM_RET_OK;
	}
}

/******************************************************************************
* Function Name: uint8_t R_MDM_GetMaxDemandActiveCapturedTimeTz(uint8_t tariff_no, rtc_counter_value_t * p_rtc)
* Description  : MDM Get captured time when max demand value changed
* Arguments    : uint8_t tariff_no: tariff number
                 rtc_counter_value_t * p_rtc: output pointer to energy rtc
* Return Value : None
******************************************************************************/
MDM_FUNC uint8_t R_MDM_GetMaxDemandActiveCapturedTimeTz(uint8_t tariff_no, rtc_counter_value_t * p_rtc)
{
    if ((tariff_no > (SCHEDULER_NUMBER_OF_TARIFF_TIMESLOT_MAX - 1)) || (p_rtc == NULL))
    {
        return MDM_RET_ERROR_PARAMS;
    }
	else 
	{	
	    EPR_Read(
	        STORAGE_EEPROM_ENERGY_MDM_MAX_ACTIVE_TZ_CAPTURE_TIME_ADDR + (tariff_no * sizeof(rtc_counter_value_t)),
	        (uint8_t *)p_rtc,
	        sizeof(rtc_counter_value_t)
	    );
		return MDM_RET_OK;
	}
}

/******************************************************************************
* Function Name: uint8_t R_MDM_GetMaxDemandApparentCapturedTimeTz(uint8_t tariff_no, rtc_counter_value_t * p_rtc)
* Description  : MDM Get captured time when max demand value changed
* Arguments    : uint8_t tariff_no: tariff number
                 rtc_counter_value_t * p_rtc: output pointer to energy rtc
* Return Value : None
******************************************************************************/
MDM_FUNC uint8_t R_MDM_GetMaxDemandApparentCapturedTimeTz(uint8_t tariff_no, rtc_counter_value_t * p_rtc)
{
    if ((tariff_no > (SCHEDULER_NUMBER_OF_TARIFF_TIMESLOT_MAX - 1)) || (p_rtc == NULL))
    {
        return MDM_RET_ERROR_PARAMS;
    }
	else 
	{
	    EPR_Read(
	        STORAGE_EEPROM_ENERGY_MDM_MAX_APPARENT_TZ_CAPTURE_TIME_ADDR + (tariff_no * sizeof(rtc_counter_value_t)),
	        (uint8_t *)p_rtc,
	        sizeof(rtc_counter_value_t)
	    );
		return MDM_RET_OK;
	}
}


/******************************************************************************
* Function Name : R_MDM_Format
* Interface     : uint8_t R_MDM_Format(void)
* Description   : format data, write default data to storage.
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
MDM_FUNC uint8_t R_MDM_Format(void)
{
	uint32_t    eeprom_addr;
    uint8_t     empty_page[STORAGE_EEPROM_PAGESIZE];
    uint16_t    size;
	
    /* Create empty_page */
    memset(empty_page, 0, sizeof(empty_page));

    /* Clear Whole EEPROM */
    eeprom_addr = STORAGE_EEPROM_ENERGY_MDM_STATE_ADDR;
    while (eeprom_addr < STORAGE_EEPROM_ENERGY_MDM_LAST_ADDR)
    {
        if ((STORAGE_EEPROM_ENERGY_MDM_LAST_ADDR - eeprom_addr) < STORAGE_EEPROM_PAGESIZE) {
            size = STORAGE_EEPROM_ENERGY_MDM_LAST_ADDR - eeprom_addr;
        }
        else {
            size = STORAGE_EEPROM_PAGESIZE;
        }

        if (EPR_Write(eeprom_addr, empty_page, size) != EPR_OK)
        {
            return STORAGE_ERROR;
        }

        eeprom_addr += size;

        R_WDT_Restart();
    }

    /* Formatted */
	return STORAGE_OK;
}

/******************************************************************************
* Function Name : R_MDM_Restore
* Interface     : uint8_t R_MDM_Restore(void)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
MDM_FUNC uint8_t R_MDM_Restore(void)
{
	/* Read data of MDM state from EEPROM */
	EPR_Read(STORAGE_EEPROM_ENERGY_MDM_STATE_ADDR, (uint8_t *)&g_mdm, sizeof(r_mdm_t));
	
	return STORAGE_OK;
}

/******************************************************************************
* Function Name : R_MDM_Backup
* Interface     : uint8_t R_MDM_Backup(void)
* Description   : 
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
MDM_FUNC uint8_t R_MDM_Backup(void)
{
	/* Write data of MDM state to EEPROM */
	EPR_Write(STORAGE_EEPROM_ENERGY_MDM_STATE_ADDR, (uint8_t *)&g_mdm, sizeof(r_mdm_t));

	return STORAGE_OK;
}