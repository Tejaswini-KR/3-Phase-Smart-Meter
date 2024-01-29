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
#include "r_cg_intp.h"
#include "r_cg_lcd.h"
#include "r_cg_lvd.h"
#include "r_cg_12adc.h"
#include "r_cg_dtc.h"
#include "r_cg_elc.h"
/* Start user code for include. Do not edit comment generated here */
#include "wrp_em_sw_config.h"
#include "wrp_em_adc.h"
#include "wrp_em_pulse.h"
#include "wrp_app_mcu.h"
#include "em_core.h"
#include "r_calib.h"
#include "startup.h"
#include "platform.h"
#include "config_storage.h"
#include "inst_read.h"
#include "key.h"
#include "event.h"
#include "em_display.h"
#include "debug.h"
#include "powermgmt.h"
#include "relay.h"
#include "r_meter_cmd.h"
#include "r_max_demand.h"
#include "r_tariff.h"
#include "r_scheduler.h"
#include "r_loadsurvey.h"
#include "r_activity_cal.h"
#include "r_load_ctrl.h"
#ifdef _DLMS
#include "r_dlms_main.h"
#endif
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
uint8_t LCD_DisplayDigit(uint8_t position, uint8_t value);
/* End user code. Do not edit comment generated here */

static void R_MAIN_UserInit(void);
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
    
    while (1U)
    {
        /* Power management control */
        POWERMGMT_PollingProcessing();

        if (POWERMGMT_GetMode() == POWERMGMT_MODE1)
        {
            /* Start Thread Scheduling  in Normal Mode or Neutral Missing Mode */
            /* KEY Polling Processing */
            KEY_PollingProcessing();
        
            /* LCD Polling Processing */
            EM_DisplaySequence();
            
            #ifndef __DEBUG
            #ifdef _DLMS
            /* DLMS Communication */
            R_DLMS_MAIN_PollingProcessing();
            #endif /* DLMS */
            #endif /* __DEBUG */
            
            /* STORAGE Polling Processing */
            CONFIG_PollingProcessing();
	        
            /* RELAY Polling Processing */
    	    #ifdef RELAY_CONTROL_ENABLE
            
                /* Load control */
                #if(defined( R_LOAD_CONTROL_ENABLE ) && R_LOAD_CONTROL_ENABLE == TRUE)
                R_LOAD_CTRL_PollingProcess();
                #endif /* R_LOAD_CONTROL_ENABLE */

                /* Relay on off */
                RELAY_PollingProcessing();
    	    #endif
	
            /* Scheduler Polling Processing */
            R_SCHEDULER_PollingProcessing();

            /* EVENT Polling Processing */
            EVENT_PollingProcessing();
 
	        /* MAX DEMAND Polling Processing */    
	        R_MDM_PollingProcessing();
	    
            /* Activity calendar Polling Processing */
            R_ACT_CAL_PollingProcessing();

	        /* TARIFF Polling Processing */    
	        R_TARIFF_PollingProcessing();

            /* LOADSURVEY Polling Processing */
            R_LOADSURVEY_PollingProcessing();
	    
            /* DEBUG Polling Processing */
            DEBUG_PollingProcessing();

            /* MeterCmd Polling Processing */
            R_METER_CMD_PollingProcessing();
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
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
