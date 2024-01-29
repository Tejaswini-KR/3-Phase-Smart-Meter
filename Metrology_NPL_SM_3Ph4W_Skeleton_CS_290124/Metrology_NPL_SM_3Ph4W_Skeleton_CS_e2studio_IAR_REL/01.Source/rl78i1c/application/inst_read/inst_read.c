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


/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
Macro definitions
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
EM_INST_READ_PARAMS g_inst_read_params;

/******************************************************************************
* Function Name: void INST_READ_RTC_InterruptCallBack(void)
* Description  : Capture instantaneous parameters from metrology
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

        /* Reset counting, start updating system parameters as below */
        count = 0;
    }
}

