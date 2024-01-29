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
* Copyright (C) 2015, 2017 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_main.c
* Version      : Code Generator for RL78/I1C V1.01.00.02 [15 May 2017]
* Device(s)    : R5F10NPJ
* Tool-Chain   : CCRL
* Description  : This file implements main function.
* Creation Date: 3/22/2019
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_tau.h"
#include "r_cg_wdt.h"
#include "r_cg_sau.h"
#include "r_cg_iica.h"
#include "r_cg_rtc.h"
#include "r_cg_dsadc.h"
#include "r_cg_mac32bit.h"
#include "r_cg_12adc.h"
#include "r_cg_dtc.h"
#include "r_cg_elc.h"
/* Start user code for include. Do not edit comment generated here */
#include "wrp_em_sw_config.h"
#include "wrp_em_adc.h"
#include "wrp_em_pulse.h"
#include "wrp_app_mcu.h"
#include "em_core.h"
#include "startup.h"
#include "platform.h"
#include "config_storage.h"
#include "inst_read.h"
#include "r_calib.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "em_display.h" 
#include "r_cg_lcd.h"
#include "r_lcd_display.h"      /* LCD Display Application Layer */
#include "r_lcd_config.h"
#include "em_display.h"         /* EM Display Application Layer */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

#define RELAY_PULSE_DURATION_COUNT  20000

#ifndef RELAY_ON
#define RELAY_ON    0
#endif

#ifndef RELAY_OFF
#define RELAY_OFF   1
#endif

#define RELAY_PHASE_R_PRESET          (BIT_SELECT(P3, 6))  /* PHASE R 1 - Net: Relay_01*/
#define RELAY_PHASE_R_SET             (BIT_SELECT(P3, 7))  /* PHASE R 2 - Net: Relay_00*/
#define RELAY_PHASE_Y_PRESET          (BIT_SELECT(P3, 4))  /* PHASE Y 1 - Net: Relay_11*/
#define RELAY_PHASE_Y_SET             (BIT_SELECT(P3, 5))  /* PHASE Y 2 - Net: Relay_10*/
#define RELAY_PHASE_B_PRESET          (BIT_SELECT(P3, 2))  /* PHASE B 1 - Net: Relay_21*/
#define RELAY_PHASE_B_SET             (BIT_SELECT(P3, 3))  /* PHASE B 2 - Net: Relay_20*/
/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
uint8_t g_uart2_send_end;
uint8_t g_uart2_received_char;
uint8_t g_uart2_received_end = 0;
volatile uint8_t calib_result = 0;
extern unsigned int disp_counter;


/***********************************************************************************************************************
* Function Name : COMMAND_InvokeCalibration
* Interface     : void COMMAND_InvokeCalibration(void)
* Description   : 
* Arguments     : None:
* Function Calls: 
* Return Value  : None
***********************************************************************************************************************/
uint8_t COMMAND_InvokeCalibration(uint16_t calib_c, uint16_t calib_cp, float32_t calib_imax, float32_t calib_v, float32_t calib_i, uint8_t calib_neutral)
{
    EM_CALIBRATION calib;
    r_calib_args_t calib_args;
    r_calib_output_t calib_output;
    r_calib_work_t calib_work;   
    uint8_t line;
    uint8_t line_max;
    uint8_t rlt, em_rlt;
    dsad_channel_t  channel;                /* Choose calibrated channel */
    float32_t       degree_list[EM_GAIN_PHASE_NUM_LEVEL_MAX];
    float32_t       gain_list[EM_GAIN_PHASE_NUM_LEVEL_MAX];
    
    /* Include neutral calibration? */
    if (calib_neutral)
    {
        line_max = 4;
    }
    else
    {
        line_max = 3;
    }

    for (line = 0; line < line_max; line++)
    {
        /* Initialize calib arguments */
        R_CALIB_SetDefaultCalibArgs(&calib_args);

        calib_args.num_of_gain_used = EM_SW_PROPERTY_ADC_GAIN_NUMBER_LEVEL;
        if (BIT_SELECT(FLMODE, 3) == 0)
        {
            /* 24MHz CPU HOCO, Fs 3906.25Hz */
            calib_args.is_high_fs = FALSE;
            calib_args.cpu_clock = 24;
        }
        else
        {
            /* 32MHz CPU HOCO, Fs 5208.33Hz*/
            calib_args.is_high_fs = TRUE;
            calib_args.cpu_clock = 32;
        }
        calib_args.cpu_clock = calib_args.cpu_clock / (1 << HOCODIV);

        calib_args.fac = EM_PLATFORM_PROPERTY_TARGET_AC_SOURCE_FREQUENCY;
        calib_args.cb_notify = NULL;
        
        calib_args.cycle = calib_c;
        calib_args.cycle_angle = calib_cp;
        calib_args.imax = calib_imax;
        calib_args.v = calib_v;
        calib_args.i = calib_i;
        calib_args.line = (EM_LINE)line;
        
        memset(&degree_list[0], 0, sizeof(degree_list));
        memset(&gain_list[0], 0, sizeof(gain_list));
      
        #if (EM_SW_PROPERTY_ADC_GAIN_NUMBER_LEVEL_PHASE_R != 1)
        if (line == (uint8_t)LINE_PHASE_R)
        {
            calib_args.imax = 0.0f;
        }
        #endif /* EM_SW_PROPERTY_ADC_GAIN_NUMBER_LEVEL_PHASE_R != 1*/
        
        #if (EM_SW_PROPERTY_ADC_GAIN_NUMBER_LEVEL_PHASE_Y != 1)
        if (line == (uint8_t)LINE_PHASE_Y)
        {
            calib_args.imax = 0.0f;
        }
        #endif /* EM_SW_PROPERTY_ADC_GAIN_NUMBER_LEVEL_PHASE_Y != 1 */
        
        #if (EM_SW_PROPERTY_ADC_GAIN_NUMBER_LEVEL_PHASE_B != 1)
        if (line == (uint8_t)LINE_PHASE_B)
        {
            calib_args.imax = 0.0f;
        }
        #endif /* EM_SW_PROPERTY_ADC_GAIN_NUMBER_LEVEL_PHASE_B != 1*/

        calib = EM_GetCalibInfo();
        
        /* Calibrating */
        rlt = R_CALIB_Calibrate(&calib_args, &calib_work, &calib_output);
        
        if (rlt == R_CALIB_OK)
        {
            #if 0
            calib_output.angle_error = calib_output.angle_error - EM_CT_GetPhaseAngleCompensation((EM_LINE)calib_args.line, calib_args.i);
            if (calib_args.num_of_gain_used != 1)
            {
                calib_output.angle_error1 = calib_output.angle_error1 - EM_CT_GetPhaseAngleCompensation((EM_LINE)calib_args.line, calib_args.i);
            }
            #endif
            
            /* Initialize the angle and gain list */
            memset(&degree_list[0], 0, sizeof(degree_list));
            memset(&gain_list[0], 0, sizeof(gain_list));

            degree_list[0] = calib_output.angle_error;
            gain_list[0] = calib_output.gain;
            if (calib_args.num_of_gain_used != 1)
            {
                degree_list[1] = calib_output.angle_error1;
                gain_list[1] = calib_output.gain1;
            }

            if (calib_args.line == LINE_PHASE_R)
            {
                calib.sampling_frequency = calib_output.fs;
                calib.coeff.phase_r.vrms = calib_output.vcoeff;
                calib.coeff.phase_r.irms = calib_output.icoeff;
                calib.coeff.phase_r.active_power = calib_output.pcoeff;
                calib.coeff.phase_r.reactive_power = calib_output.pcoeff;
                calib.coeff.phase_r.apparent_power = calib_output.pcoeff;
                calib.sw_phase_correction.phase_r.i_phase_degrees = degree_list;
                calib.sw_gain.phase_r.i_gain_values = gain_list;
            }
            else if (calib_args.line == LINE_PHASE_Y)
            {
                calib.sampling_frequency = calib_output.fs;
                calib.coeff.phase_y.vrms = calib_output.vcoeff;
                calib.coeff.phase_y.irms = calib_output.icoeff;
                calib.coeff.phase_y.active_power = calib_output.pcoeff;
                calib.coeff.phase_y.reactive_power = calib_output.pcoeff;
                calib.coeff.phase_y.apparent_power = calib_output.pcoeff;
                calib.sw_phase_correction.phase_y.i_phase_degrees = degree_list;
                calib.sw_gain.phase_y.i_gain_values = gain_list;
            }
            else if (calib_args.line == LINE_PHASE_B)
            {
                calib.sampling_frequency = calib_output.fs;
                calib.coeff.phase_b.vrms = calib_output.vcoeff;
                calib.coeff.phase_b.irms = calib_output.icoeff;
                calib.coeff.phase_b.active_power = calib_output.pcoeff;
                calib.coeff.phase_b.reactive_power = calib_output.pcoeff;
                calib.coeff.phase_b.apparent_power = calib_output.pcoeff;
                calib.sw_phase_correction.phase_b.i_phase_degrees = degree_list;
                calib.sw_gain.phase_b.i_gain_values = gain_list;
            }
            else
            {
                calib.coeff.neutral.irms = calib_output.icoeff;
            }

            {
                /* Stop EM operation */
                EM_Stop();

                /* Set calibrated data */
                em_rlt = EM_SetCalibInfo(&calib);
                if (em_rlt != EM_OK)
                {
                    /* Set calibration failed */
                    EM_Start();
                    return em_rlt;
                }

                /* Backup calibrated data into Storage Memory */
                if (CONFIG_Backup(CONFIG_ITEM_CALIB) != CONFIG_OK)
                {
                    /* Restart the EM */
                    EM_Start();
                    return 3;
                }
            }
        }
        else
        {
            /* Restart the EM */
            EM_Start();
            return rlt;
        }

        EM_Start();
    }
    
    return rlt;
}

/***********************************************************************************************************************
* Function Name : uart_printf
* Interface     : int uart_printf(const char __far *format, ...)
* Description   : This function print out a string with format to UART2
*               : Not overriding compiler default printf due to different near far specification
* Arguments     : const char * format:
* Return Value  : int
 **********************************************************************************************************************/
int uart_printf(const char __far *format, ...)
{
    uint8_t buffer[256];
    uint16_t length;
    #ifdef __ICCRL78__
    va_list     arg = { NULL };
    #else
    va_list     arg = NULL; 
    #endif /* __ICCRL78__ */
    
    /* Parse the argument list, print to buffer string */
    va_start(arg, format);
    
    /* Format the string */
    length = vsprintf((char *)buffer, (const char *)format, arg);
    
    /* Print out to UART2 TX: optical port */
    if (length > 0)
    {
        g_uart2_send_end = 0;
        R_UART2_Send(buffer, length);
        while(g_uart2_send_end == 0)
        {
            R_WDT_Restart();
        }
    }

    va_end(arg);
    
    return length;
}

/***********************************************************************************************************************
 * Function Name: print_instantaneous_params
 * Description  : NA
 * Arguments    : void
 * Return Value : void
 **********************************************************************************************************************/
void print_instantaneous_params(void)
{
    char param_format[] = "  %-15s, %# 15.5f, %s\n\r";
    
    EM_INST_READ_PARAMS params;

    /* Pull global variables to local first */
    params = g_inst_read_params;
    uart_printf("\n\r");
    uart_printf("Instantaneous parameters:");
    uart_printf("\n\r");
    uart_printf(param_format, "VRMS_R"          , params.vrms[LINE_PHASE_R]                 , "(V)");
    uart_printf(param_format, "VRMS_Y"          , params.vrms[LINE_PHASE_Y]                 , "(V)");
    uart_printf(param_format, "VRMS_B"          , params.vrms[LINE_PHASE_B]                 , "(V)");
    uart_printf(param_format, "VRMS_T"          , params.vrms[LINE_TOTAL]                   , "(V)");
    uart_printf(param_format, "IRMS_R"          , params.irms[LINE_PHASE_R]                 , "(A)");
    uart_printf(param_format, "IRMS_Y"          , params.irms[LINE_PHASE_Y]                 , "(A)");
    uart_printf(param_format, "IRMS_B"          , params.irms[LINE_PHASE_B]                 , "(A)");
    uart_printf(param_format, "IRMS_T"          , params.irms[LINE_TOTAL]                   , "(A)");
    uart_printf(param_format, "IRMS_N"          , params.irms[LINE_NEUTRAL]                 , "(A)");
    uart_printf(param_format, "IVECT"           , params.vector_sum_irms                    , "(A)");
    uart_printf(param_format, "ACT_R"           , params.active_power[LINE_PHASE_R]         , "(Watt)");
    uart_printf(param_format, "ACT_Y"           , params.active_power[LINE_PHASE_Y]         , "(Watt)");
    uart_printf(param_format, "ACT_B"           , params.active_power[LINE_PHASE_B]         , "(Watt)");
    uart_printf(param_format, "ACT_T"           , params.active_power[LINE_TOTAL]           , "(Watt)");
    uart_printf(param_format, "REA_R"           , params.reactive_power[LINE_PHASE_R]       , "(VAr)");
    uart_printf(param_format, "REA_Y"           , params.reactive_power[LINE_PHASE_Y]       , "(VAr)");
    uart_printf(param_format, "REA_B"           , params.reactive_power[LINE_PHASE_B]       , "(VAr)");
    uart_printf(param_format, "REA_T"           , params.reactive_power[LINE_TOTAL]         , "(VAr)");
    uart_printf(param_format, "APP_R"           , params.apparent_power[LINE_PHASE_R]       , "(VA)");
    uart_printf(param_format, "APP_Y"           , params.apparent_power[LINE_PHASE_Y]       , "(VA)");
    uart_printf(param_format, "APP_B"           , params.apparent_power[LINE_PHASE_B]       , "(VA)");
    uart_printf(param_format, "APP_T"           , params.apparent_power[LINE_TOTAL]         , "(VA)");
    uart_printf(param_format, "Fund_ACT_R"      , params.fundamental_power[LINE_PHASE_R]    , "(Watt)");
    uart_printf(param_format, "Fund_ACT_Y"      , params.fundamental_power[LINE_PHASE_Y]    , "(Watt)");
    uart_printf(param_format, "Fund_ACT_B"      , params.fundamental_power[LINE_PHASE_B]    , "(Watt)");
    uart_printf(param_format, "Fund_ACT_T"      , params.fundamental_power[LINE_TOTAL]      , "(Watt)");
    uart_printf(param_format, "PF_R"            , params.power_factor[LINE_PHASE_R]         , " ");
    uart_printf(param_format, "PF_Y"            , params.power_factor[LINE_PHASE_Y]         , " ");
    uart_printf(param_format, "PF_B"            , params.power_factor[LINE_PHASE_B]         , " ");
    uart_printf(param_format, "PF_T"            , params.power_factor[LINE_TOTAL]           , " ");
    uart_printf(param_format, "Freq_R"          , params.freq[LINE_PHASE_R]                 , "(Hz)");
    uart_printf(param_format, "Freq_Y"          , params.freq[LINE_PHASE_Y]                 , "(Hz)");
    uart_printf(param_format, "Freq_B"          , params.freq[LINE_PHASE_B]                 , "(Hz)");
    uart_printf(param_format, "Freq_T"          , params.freq[LINE_TOTAL]                   , "(Hz)");
    uart_printf(param_format, "E_ACT_IMP"       , params.active_energy_total_import         , "(Wh)");
    uart_printf(param_format, "E_ACT_EXP"       , params.active_energy_total_export         , "(Wh)");
    uart_printf(param_format, "E_IND_REA_IMP"   , params.reactive_energy_lag_total_import   , "(VArh)");
    uart_printf(param_format, "E_IND_REA_EXP"   , params.reactive_energy_lag_total_export   , "(VArh)");
    uart_printf(param_format, "E_CAP_REA_IMP"   , params.reactive_energy_lead_total_import  , "(VArh)");
    uart_printf(param_format, "E_CAP_REA_EXP"   , params.reactive_energy_lead_total_export  , "(VArh)");
    uart_printf(param_format, "E_APP_IMP"       , params.apparent_energy_total_import       , "(VAh)");
    uart_printf(param_format, "E_APP_EXP"       , params.apparent_energy_total_export       , "(VAh)");
    uart_printf("\n\r");
}
/***********************************************************************************************************************
 End of function print_instantaneous_params
***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: print_metrology_version
 * Description  : NA
 * Arguments    : void
 * Return Value : void
 **********************************************************************************************************************/
void print_metrology_version(void)
{
    /* Import from metrology library version info */
    extern const uint8_t FAR_PTR g_em_lib_type[];
    extern const uint8_t FAR_PTR g_em_lib_target_platform[];
    extern const uint8_t FAR_PTR g_em_lib_git_revision[];
    extern const uint8_t FAR_PTR g_em_lib_compiler[];
    extern const uint8_t FAR_PTR g_em_lib_build_date[];
    extern char __far * _COM_strcpy_ff(char __far *s1, const char __far *s2);
    
    char buffer[128];
    
    uart_printf("\n\r");
    uart_printf("Metrology library version info:");
    uart_printf("\n\r");
    memset(buffer, 0, sizeof(buffer)); _COM_strcpy_ff(buffer,(const char FAR_PTR *)g_em_lib_type);             uart_printf("Library type: %s \n\r", buffer);
    memset(buffer, 0, sizeof(buffer)); _COM_strcpy_ff(buffer,(const char FAR_PTR *)g_em_lib_target_platform);  uart_printf("Target platform: %s \n\r", buffer);
    memset(buffer, 0, sizeof(buffer)); _COM_strcpy_ff(buffer,(const char FAR_PTR *)g_em_lib_git_revision);     uart_printf("Git revision: %s \n\r", buffer);
    memset(buffer, 0, sizeof(buffer)); _COM_strcpy_ff(buffer,(const char FAR_PTR *)g_em_lib_compiler);         uart_printf("Built compiler: %s \n\r", buffer);
    memset(buffer, 0, sizeof(buffer)); _COM_strcpy_ff(buffer,(const char FAR_PTR *)g_em_lib_build_date);       uart_printf("Build date: %s \n\r", buffer);
}
/***********************************************************************************************************************
 End of function print_metrology_version
***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: print_running_coefficient
 * Description  : NA
 * Arguments    : void
 * Return Value : void
 **********************************************************************************************************************/
void print_running_coefficient(void)
{
    char param_format[] = "  %-15s, %# 15.5f\n\r";
    
    EM_CALIBRATION calib = EM_GetCalibInfo();
    uart_printf("\n\r");
    uart_printf("Calibration info: \n\r");
    uart_printf("\n\r");
    uart_printf(param_format, "FS" , calib.sampling_frequency);
    uart_printf(param_format, "V_R" , calib.coeff.phase_r.vrms);
    uart_printf(param_format, "V_Y" , calib.coeff.phase_y.vrms);
    uart_printf(param_format, "V_B" , calib.coeff.phase_b.vrms);
    uart_printf(param_format, "I_R" , calib.coeff.phase_r.irms);
    uart_printf(param_format, "I_Y" , calib.coeff.phase_y.irms);
    uart_printf(param_format, "I_B" , calib.coeff.phase_b.irms);
    uart_printf(param_format, "ACT_R" , calib.coeff.phase_r.active_power);
    uart_printf(param_format, "ACT_Y" , calib.coeff.phase_y.active_power);
    uart_printf(param_format, "ACT_B" , calib.coeff.phase_b.active_power);
    uart_printf(param_format, "REA_R" , calib.coeff.phase_r.reactive_power);
    uart_printf(param_format, "REA_Y" , calib.coeff.phase_y.reactive_power);
    uart_printf(param_format, "REA_B" , calib.coeff.phase_b.reactive_power);
    uart_printf(param_format, "APP_R" , calib.coeff.phase_r.apparent_power);
    uart_printf(param_format, "APP_Y" , calib.coeff.phase_y.apparent_power);
    uart_printf(param_format, "APP_B" , calib.coeff.phase_b.apparent_power);
    uart_printf(param_format, "ANGLE0_R" , calib.sw_phase_correction.phase_r.i_phase_degrees[0]);
    uart_printf(param_format, "ANGLE0_Y" , calib.sw_phase_correction.phase_y.i_phase_degrees[0]);
    uart_printf(param_format, "ANGLE0_B" , calib.sw_phase_correction.phase_b.i_phase_degrees[0]);
    uart_printf(param_format, "ANGLE1_R" , calib.sw_phase_correction.phase_r.i_phase_degrees[1]);
    uart_printf(param_format, "ANGLE1_Y" , calib.sw_phase_correction.phase_y.i_phase_degrees[1]);
    uart_printf(param_format, "ANGLE1_B" , calib.sw_phase_correction.phase_b.i_phase_degrees[1]);
    uart_printf(param_format, "GAIN0_R" , calib.sw_gain.phase_y.i_gain_values[0]);
    uart_printf(param_format, "GAIN0_Y" , calib.sw_gain.phase_y.i_gain_values[0]);
    uart_printf(param_format, "GAIN0_B" , calib.sw_gain.phase_y.i_gain_values[0]);
    uart_printf(param_format, "GAIN1_R" , calib.sw_gain.phase_y.i_gain_values[1]);
    uart_printf(param_format, "GAIN1_Y" , calib.sw_gain.phase_y.i_gain_values[1]);
    uart_printf(param_format, "GAIN1_B" , calib.sw_gain.phase_y.i_gain_values[1]);
    uart_printf("\n\r");
}
/***********************************************************************************************************************
 End of function print_running_coefficient
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name    : void RELAY_SwitchOn(void)
* Description      : 
* Arguments        : None
* Functions Called : None
* Return Value     : None
***********************************************************************************************************************/
void RELAY_SwitchOn(void)
{
    uint16_t i;

    RELAY_PHASE_R_PRESET    = RELAY_OFF;      /* for PHASE R */
    RELAY_PHASE_R_SET       = RELAY_ON;       /* for PHASE R */
    RELAY_PHASE_Y_PRESET    = RELAY_OFF;      /* for PHASE Y */
    RELAY_PHASE_Y_SET       = RELAY_ON;       /* for PHASE Y */
    RELAY_PHASE_B_PRESET    = RELAY_OFF;      /* for PHASE B */
    RELAY_PHASE_B_SET       = RELAY_ON;       /* for PHASE B */
    
    for (i = 0; i < RELAY_PULSE_DURATION_COUNT; i++)
    {   
        NOP();
        NOP();
    }
    
    RELAY_PHASE_R_PRESET    = RELAY_OFF;      /* for PHASE R */
    RELAY_PHASE_R_SET       = RELAY_OFF;      /* for PHASE R */
    RELAY_PHASE_Y_PRESET    = RELAY_OFF;      /* for PHASE Y */
    RELAY_PHASE_Y_SET       = RELAY_OFF;      /* for PHASE Y */
    RELAY_PHASE_B_PRESET    = RELAY_OFF;      /* for PHASE B */
    RELAY_PHASE_B_SET       = RELAY_OFF;      /* for PHASE B */

}

uint8_t g_calib;
uint8_t g_print;
uint8_t g_version;
uint8_t g_coeff;

#define ENABLE_KEY_PRESS_TRIGGER	(0)
#define ENABLE_UART_TRIGGER	        (0)
/* End user code. Do not edit comment generated here */

static void R_MAIN_UserInit(void);
void EM_DisplaySequence(void);
/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
    R_MAIN_UserInit();
    /* Start user code. Do not edit comment generated here */
    startup();
	//g_calib = 1;
	g_print = 1;
    /* To always close the relay in Smart Meter platform, avoid alarm on GFUVE */
    //RELAY_SwitchOn();
    
    while (1U)
    {
		if(g_calib == 0)
		{
//			LCD_DisplayDigit(1,12);
//			LCD_DisplayDigit(2,10);
//			LCD_DisplayDigit(3,21);
//			LCD_DisplayDigit(5,13);
//			LCD_DisplayDigit(6,23);
			
			if(disp_counter>=2000)
			{
				EM_DisplaySequence();
				disp_counter = 0;
			}
		}
		else
		{
			//LCD_DisplayDigit(1,12);
			//LCD_DisplayDigit(2,10);
			//LCD_DisplayDigit(1,21);
		}
		
		
        #if (ENABLE_KEY_PRESS_TRIGGER == 1)
        /* Calibration trigger: SW1 Key press */
        if (P15_bit.no2 == 0)
        {
            g_calib = 1;
        }
        
        /* Snapshot print out trigger: SW2 Key press */
        if (P15_bit.no0 == 0)
        {
            g_print = 1;
        }
        #endif
        
        #if (ENABLE_UART_TRIGGER == 1)
        /* Poll for receiveing characters and trigger corresponding action */
        {
            uint8_t b;
            if (g_uart2_received_end == 1)
            {
                g_uart2_received_end = 0;
                
                b = g_uart2_received_char;
                if (0) {}
                else if (b == 'C') {
                    g_calib = 1;
                }
                else if (b == 'P') {
                    g_print = 1;
                }
                else if (b == 'V') {
                    g_version = 1;
                }
                else if (b == 'O') {
                    g_coeff = 1;
                }
                else {
                    /* Unsupported char */
                }
            }
        }
        #endif
		
        /* Calibration */
        if (g_calib == 1)
        {
            /* Short delay for calibration stabilization */
            uart_printf("\n\rStart autocalibration: \n\r");
            {
                uint32_t i;
                for (i = 0; i < 10; i++)
                {
                    MCU_Delay(50000);
                    R_WDT_Restart();
                }
            }
            calib_result = COMMAND_InvokeCalibration(
                150,        /* c */
                150,        /* cp */
                60.0f,      /* imax */
                220.0f,     /* v */
                5.0f,       /* i */
                0           /* calib_neutral? */
            );
            uart_printf("Autocalibration end\n\r");
            uart_printf("Calibration status: %d \n\r", calib_result);

            NOP();
            g_calib = 0;
        }

        /* Snapshot print out */
        if (g_print == 1)
        {
            print_instantaneous_params();
            g_print = 0;
        }
        
        /* Print out version info */
        if (g_version == 1)
        {
            print_metrology_version();
            
            g_version = 0;
        }
        
        /* Print out calibration data */
        if (g_coeff == 1)
        {
            print_running_coefficient();
            
            g_coeff = 0;
        }

        R_WDT_Restart();
    }
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */
    EI();
	R_TAU0_Channel0_Start();
	R_LCD_Voltage_On();
	R_LCD_Start();
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
