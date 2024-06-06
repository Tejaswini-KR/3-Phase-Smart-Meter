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
#include "r_cg_sau.h"           /* Serial Driver */
#include "r_cg_lcd.h"           /* LCD Driver */
#include "r_cg_lvd.h"           /* LVD Driver */
#include "r_cg_rtc.h"           /* RTC Driver */
#include "r_cg_dsadc.h"
#include "r_cg_12adc.h"
#include "r_cg_tau.h"
#include "r_cg_lvd.h"
#include "r_cg_iica.h"
#include "r_cg_wdt.h"

/* Wrapper/User */
#include "wrp_em_sw_config.h"

/* MW/Core */
#include "em_core.h"        /* EM Core APIs */

/* Application */
#include "platform.h"       /* Default Platform Information Header */
#include "config_storage.h"
#include "startup.h"        /* Startup Header File */

/* Driver */
#include "r_cg_userdefine.h"    /* CG User Define */
#include "r_cg_port.h"          /* Port Driver*/
#include "r_cg_cgc.h"           /* CG CGC Driver */
#include "r_cg_intp.h"          /* CG Interrupt Driver*/

/* Standard library */
#include <stddef.h>
#include <stdlib.h>

/* Wrapper/User */
#include "wrp_app_uart.h"
#include "wrp_app_mcu.h"
/* Metrology */
#include "em_core.h"            /* EM Core APIs */
#include "storage_em.h"
/* Application */
#include "dataflash.h"
#include "r_lcd_display.h"
#include "em_display.h"         /* EM Display */
#include "storage.h"
#include "event.h"              /* Event Header File */
#include "relay.h"              /* Relay management module */
#include "debug.h"
#include "r_meter_cmd.h"
#include "eeprom.h"
#include "bl_serialflash.h"
#include "r_dlms_main.h"
#include "r_dlms_app.h"

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct tagStartupDiag
{
    uint8_t storage_init;
} startup_diag_t;
/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/
uint8_t g_reset_flag;

st_em_startup_diag_t g_em_startup_diag;

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
static uint8_t config_data_load(EM_CALIBRATION * p_calib, st_em_setting_t * p_em_setting);
startup_diag_t g_startup_diag;
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
    
    /* Check device format to get out config data */  
    if (init_status == CONFIG_OK)   /* Initial successful, already formatted */
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
        else        /* format ok */
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
 * Function Name: em_energy_data_load
 * Description  : Load energy data from storage eeprom to metrology counter 
 * Arguments    : NA
 * Return Value : uint8_t
 **********************************************************************************************************************/
static uint8_t em_energy_data_load(void)
{
    EM_OPERATION_DATA energy_data;

    EPR_Init();

    /* Load from eeprom */
    if (STORAGE_EM_Restore() != EM_STORAGE_OK)
    {
        return EM_STORAGE_ERROR;
    }

    return EM_STORAGE_OK;
}
/***********************************************************************************************************************
* Function Name    : void start_peripheral_and_app(void)
* Description      : Start-up no checking, just diag code
* Arguments        : None
* Return Value     : Execution Status
*                  :    STARTUP_OK              Start-up Ok
*                  :    STARTUP_ERROR           Startup error
***********************************************************************************************************************/
void start_peripheral_and_app(void)
{
    /*****************************************************************
    * Metrology init
    ******************************************************************/
    EM_CALIBRATION      calib;
    st_em_setting_t     em_hold_setting_value;


	/* TODO: need to enable switch Flash mode when integrate Bootloader */
    /* Switch to HS later using temperature sensor before metrology started, if not need temperature measurement, no need to enable it */
    if (FLASH_MODE_IS_HS() == 0)
    {
     	FLASH_MODE_LS_TO_HS();
     //BL_UpdateFslDescriptor(0, 6);   /* Full speed, 6Mhz */
    }
	
    /* Init configuration and restore calibration data from dataflash */
    g_em_startup_diag.config_load_status = config_data_load(&calib, &em_hold_setting_value);

    /* Init load data from storage for ADC driver */
    R_DSADC_SetGain(em_hold_setting_value.regs);
   
    /* Init for EM */
    g_em_startup_diag.em_init_status = EM_Init((EM_PLATFORM_PROPERTY FAR_PTR *)&g_EM_DefaultProperty, &calib);

    /* Init eeprom and restore EM energy counter from eeprom */
    g_em_startup_diag.energy_load_status = em_energy_data_load();

    /* Starting metrology */
    g_em_startup_diag.em_start_status = EM_Start();
    
    /*****************************************************************
    * Initial all
    ******************************************************************/
    /* Start peripherals */
    R_RTC_Start();  
    R_RTC_Set_ConstPeriodInterruptOn(SEC1_2);
    

    /* UART */
    R_UART2_SetConfig(SAU_STD_LENGTH_8, SAU_STD_PARITY_NONE, SAU_STD_STOPBITS_1);
    R_UART2_SetBaudRate(SAU_STD_BAUD_RATE_9600);
    R_UART2_Start();

    #ifdef __DEBUG
    WRP_UART_SetConfig(WRP_UART_LENGTH_8, WRP_UART_PARITY_NONE, WRP_UART_STOPBITS_1);
    WRP_UART_SetBaudRate(WRP_UART_BAUD_RATE_9600);
    DEBUG_Init();
    DEBUG_Start();
    #endif /* __DEBUG */
	
	// MODBUS_UART
    R_UART1_SetConfig(SAU_STD_LENGTH_8, SAU_STD_PARITY_NONE, SAU_STD_STOPBITS_1);
    R_UART1_SetBaudRate(SAU_STD_BAUD_RATE_9600);
    R_UART1_Start();

    /* LCD */
    //R_LCD_PowerOn(1);
	R_LCD_PowerOn(0);

    /* Key */
    R_INTC0_Start();                                /* Rly_sens_2 */
    R_INTC1_Start();                                /* Hall */
    R_INTC8_Start();                                /* Rly_sens_0 */
    R_INTC9_Start();                                /* Rly_sens_1 */
    R_INTRTCIC0_Start();                            /* Case */
    R_INTRTCIC1_Start();                            /* SW2 */
    R_INTRTCIC2_Start();                            /* SW1 */

    /* Timer */
    R_TAU0_Channel0_Start();

    /* LVD */
    R_LVD_Start_EXLVD();
    R_LVD_Start_VBAT();
    R_LVD_Start_VRTC();

    /* Init storage to prepare data for application before init application */
    g_startup_diag.storage_init = STORAGE_Init(0);

    /* Start other application */
    R_INST_SetSnapshotCaptureState(1);
    BL_SFL_Init();
    R_SCHEDULER_Init();
    R_TARIFF_Init();
    R_MDM_Init();
    EVENT_Init();

    #if(defined( R_LOAD_CONTROL_ENABLE ) && R_LOAD_CONTROL_ENABLE == TRUE)
        R_LOAD_CTRL_Init();
        R_LIMITER_Init();
    #endif /* R_LOAD_CONTROL_ENABLE */
    
    WRP_UART_Start();
     
    #ifdef _DLMS
    R_DLMS_MAIN_Init();

    #endif /* _DLMS */
    R_METER_CMD_Init();

    /* Inform power on event */
    EVENT_PowerOn();
}

/***********************************************************************************************************************
* Function Name    : void stop_peripheral(void)
* Description      : Stop peripheral, but not stop application
* Arguments        : None
* Return Value     : Execution Status
*                  :    STARTUP_OK              Start-up Ok
*                  :    STARTUP_ERROR           Startup error
***********************************************************************************************************************/
void stop_peripheral(void)
{
    /* Note: VRTCEN manage outside of this API */
    LCD_ClearAll();
    R_LCD_PowerOff();
    R_IICA0_Stop();
    R_UART0_Stop();
    R_UART2_Stop();
    R_TAU0_Channel0_Stop();
    R_TAU0_Channel2_Stop();
    R_INTC1_Stop();
//    R_INTC3_Stop();
    /* Leave RTCIC (LCD scroll and Case open) running */
    R_PORT_StopCreate();
    R_12ADC_Stop();
//    R_TMPS_Stop();
    /* RTC keep running, only mask off RTC periodic interrupt */
    RTCRMK = 1U; //Not using R_RTC_Stop(); it included stop counting, alarm and reset bit set
    R_DSADC_Stop();
    R_LVD_Stop_VBAT();
    R_LVD_Stop_VRTC();

    /* TODO: need to enable switch Flash mode when integrate Bootloader */
    /* Switch to LS for larger operating range */
    if (FLASH_MODE_IS_HS() == 1)
    {
       FLASH_MODE_HS_TO_LS();
     //BL_UpdateFslDescriptor(1, 6);   /* Wide-voltage, 6Mhz */
    }
}



/***********************************************************************************************************************
* Function Name    : void startup(void)
* Description      : Start-up energy meter
* Arguments        : None
* Functions Called : State selection for startup
* Return Value     : Execution Status
*                  :    STARTUP_OK              Start-up Ok
*                  :    STARTUP_ERROR           Startup error
***********************************************************************************************************************/
void startup(void)
{
    uint8_t *p;
	
    g_reset_flag = RESF;
    start_peripheral_and_app();

#if(defined(R_DLMS_APPS_MALLOC_USING) && (R_DLMS_APPS_MALLOC_USING == TRUE))
	/*
	 * Allocate almost of heap RAM (margin 8 bytes) as a "big chunk" to make all free() calls
	 * in between the "big chunk" act as to reform the "big chunk".
	 * This helps some nested malloc() easier to success on requesting a bigger demand, in nested calls.
	 * https://www.embedded.com/print/4007638
	 */
	p = malloc(g_cnst_REL_sizeof_sysheap - 8);
	if (p != NULL) {
		free(p);
		p = NULL;
	}
#endif
}
