/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2013, 2015 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : startup.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : Start-up source File
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Driver */
#include "r_cg_macrodriver.h"   /* CG Macro Driver */
#include "r_cg_userdefine.h"    /* CG User Define */
#include "r_cg_port.h"          /* Port Driver*/
#include "r_cg_sau.h"           /* Serial Driver */
#include "r_cg_rtc.h"           /* RTC Driver */
#include "r_cg_dsadc.h"         /* DSADC Driver */

/* Wrapper/User */

/* MW/Core */
#include "em_core.h"            /* EM Core APIs */

/* Application */
#include "platform.h"           /* Default Platform Information Header */
#include "config_storage.h"
#include "startup.h"            /* Startup Header File */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/
extern uint8_t g_uart2_received_char;

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/
uint8_t g_reset_flag;

st_em_startup_diag_t g_em_startup_diag;

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name    : static uint8_t config_data_load(EM_CALIBRATION * p_calib, st_em_setting_t * p_em_setting)
* Description      : Load Configuration Page from MCU DataFlash memory
* Arguments        : uint8_t init_status: initialization status
* Return Value     : Execution Status
*                  :    CONFIG_OK         Load data OK
*                  :    CONFIG_ERROR         Load data error
***********************************************************************************************************************/
static uint8_t config_data_load( EM_CALIBRATION * p_calib, st_em_setting_t * p_em_setting)
{
    uint8_t init_status;

    /* Assign pointer for phase degree in calib holder value */
    p_calib->sw_phase_correction.phase_r.i_phase_degrees = p_em_setting->degree_list_r;
    p_calib->sw_phase_correction.phase_y.i_phase_degrees = p_em_setting->degree_list_y;
    p_calib->sw_phase_correction.phase_b.i_phase_degrees = p_em_setting->degree_list_b;

    /* Assign pointer for gain in calib to holder value */
    p_calib->sw_gain.phase_r.i_gain_values = p_em_setting->gain_list_r;
    p_calib->sw_gain.phase_y.i_gain_values = p_em_setting->gain_list_y;
    p_calib->sw_gain.phase_b.i_gain_values = p_em_setting->gain_list_b;
    
    /* Init config */
    init_status = CONFIG_Init(0);

    /* Check device format */
    if (init_status == CONFIG_OK)       /* Initial successful, already formatted */
    {

    }
    /* Initial successful, but not formatted */
    else if (init_status == CONFIG_NOT_FORMATTED)
    {
        /* Format device */
        if (CONFIG_Format() != CONFIG_OK)
        {
            /* When format fail,
             * we need to beak the start-up process here */     
            return CONFIG_ERROR;   /* Format fail */
        }       
        else    /* format ok */
        {

        }
    }
    /* Restore data from storage in every load config */
    if (CONFIG_LoadEMCalib(p_calib, &p_em_setting->regs) != CONFIG_OK)
    {
        NOP();
    }
    else
    {
        NOP();
    }

    /* Load data sucessfully */
    return CONFIG_OK;
}

/***********************************************************************************************************************
* Function Name    : void start_peripheral_and_app(void)
* Description      : Start-up no checking, just diag code
* Arguments        : None
* Return Value     : None
***********************************************************************************************************************/
void start_peripheral_and_app(void)
{
    EM_CALIBRATION           calib;
    st_em_setting_t          em_hold_setting_value;

    /* Init configuration and restore calibration data from dataflash */
    g_em_startup_diag.config_load_status = config_data_load(&calib, &em_hold_setting_value);

    /* Init load data from storage for ADC driver */
    R_DSADC_SetGain(em_hold_setting_value.regs);
    
    /* Init for EM */
    g_em_startup_diag.em_init_status = EM_Init((EM_PLATFORM_PROPERTY FAR_PTR *)&g_EM_DefaultProperty, &calib);
    
    /* Starting metrology */
    g_em_startup_diag.em_start_status = EM_Start();

    /*****************************************************************
    * Start all peripheral, device, EM Core
    ******************************************************************/
    /* Start peripherals */
    R_RTC_Start();  
    R_RTC_Set_ConstPeriodInterruptOn(SEC1_2);

    /* Start other peripherals */

    /* Change UART configuration */
    R_UART2_SetConfig(SAU_STD_LENGTH_8, SAU_STD_PARITY_NONE, SAU_STD_STOPBITS_1);
    R_UART2_SetBaudRate(SAU_STD_BAUD_RATE_9600);
    R_UART2_Start();
    R_UART2_Receive(&g_uart2_received_char, 1);
    
    /* System checking end, turn off peripherals */

}

/***********************************************************************************************************************
* Function Name    : void startup(void)
* Description      : Start-up energy meter
* Arguments        : None
* Return Value     : None
***********************************************************************************************************************/
void startup(void)
{
    g_reset_flag = RESF;
    
    start_peripheral_and_app();
}

