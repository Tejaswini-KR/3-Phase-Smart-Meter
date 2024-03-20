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
* File Name    : em_display.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : CCRL
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : EM Display Application Layer APIs
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Driver layer */
#include "r_cg_macrodriver.h"
#include "typedef.h"            /* GCSE Standard definitions */
#include "r_cg_wdt.h"
#include "r_cg_rtc.h"

/* Wrapper layer */
#include "wrp_app_ext.h"

/* Application layer */
#include "platform.h"
#include "r_lcd_display.h"      /* LCD Display Application Layer */
#include "r_lcd_config.h"
#include "em_display.h"         /* EM Display Application Layer */
#include "event.h"
#include "inst_read.h"
#include "r_tariff.h"
#include "r_max_demand.h"
#include "powermgmt.h"
/* Display tamper condition */
//#include "memory_ext.h"
#include "em_core.h"
#include <math.h>
/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define EM_LCD_EXPORT_ENERGY           (0)
#define EM_LCD_IMPORT_ENERGY           (1)

#define EM_LCD_CAPACITIVE_REACTIVE     (0)
#define EM_LCD_INDUCTIVE_REACTIVE      (1)

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
/*
 * Common display: LCD on all, Unit Code, SW ver., Date, Time, etc
 */
static void EM_DisplayUnitCode(void);
static void EM_LCD_DisplaySoftVersion(void);
static void EM_DisplayDate(void);
static void EM_DisplayInstantTime(void);

/* Volt */
static void EM_LCD_DisplayInstantVolt_Phase_R(void);
static void EM_LCD_DisplayInstantVolt_Phase_Y(void);
static void EM_LCD_DisplayInstantVolt_Phase_B(void);
static void EM_LCD_DisplayInstantVolt_Total(void);

/* Current */
static void EM_LCD_DisplayInstantCurrent_Phase_R(void);
static void EM_LCD_DisplayInstantCurrent_Phase_Y(void);
static void EM_LCD_DisplayInstantCurrent_Phase_B(void);
static void EM_LCD_DisplayInstantCurrent_Neutral(void);
static void EM_LCD_DisplayInstantCurrent_Total(void);

static void EM_LCD_DisplayPowerFactor_Phase_R(void);
static void EM_LCD_DisplayPowerFactor_Phase_Y(void);
static void EM_LCD_DisplayPowerFactor_Phase_B(void);
static void EM_LCD_DisplayPowerFactor_Total(void);

static void EM_LCD_DisplayLineFrequency(void);

/* Power */
static void EM_LCD_DisplayInstantActPower_Phase_R(void);
static void EM_LCD_DisplayInstantActPower_Phase_Y(void);
static void EM_LCD_DisplayInstantActPower_Phase_B(void);
static void EM_LCD_DisplayInstantActPower_Total(void);

static void EM_LCD_DisplayInstantReactPower_Phase_R(void);
static void EM_LCD_DisplayInstantReactPower_Phase_Y(void);
static void EM_LCD_DisplayInstantReactPower_Phase_B(void);
static void EM_LCD_DisplayInstantReactPower_Total(void);

static void EM_LCD_DisplayInstantFundamentalActPower_Phase_R(void);
static void EM_LCD_DisplayInstantFundamentalActPower_Phase_Y(void);
static void EM_LCD_DisplayInstantFundamentalActPower_Phase_B(void);
static void EM_LCD_DisplayInstantFundamentalActPower_Total(void);

static void EM_LCD_DisplayInstantAppPower_Phase_R(void);
static void EM_LCD_DisplayInstantAppPower_Phase_Y(void);
static void EM_LCD_DisplayInstantAppPower_Phase_B(void);
static void EM_LCD_DisplayInstantAppPower_Total(void);

/* Current SUM vector */
static void EM_LCD_DisplayPhaseCurrentSumVector(void);

/* THD */
static void EM_LCD_DisplayVoltageTHD_Phase_R(void);
static void EM_LCD_DisplayVoltageTHD_Phase_Y(void);
static void EM_LCD_DisplayVoltageTHD_Phase_B(void);
static void EM_LCD_DisplayCurrentTHD_Phase_R(void);
static void EM_LCD_DisplayCurrentTHD_Phase_Y(void);
static void EM_LCD_DisplayCurrentTHD_Phase_B(void);

/* Energy */
static void EM_LCD_DisplayImportActiveEnergy(void);
static void EM_LCD_DisplayImportCapacitiveReactiveEnergy(void);
static void EM_LCD_DisplayImportInductiveReactiveEnergy(void);
static void EM_LCD_DisplayImportApparentEnergy(void);
static void EM_LCD_DisplayExportActiveEnergy(void);
static void EM_LCD_DisplayExportCapacitiveReactiveEnergy(void);
static void EM_LCD_DisplayExportInductiveReactiveEnergy(void);
static void EM_LCD_DisplayExportApparentEnergy(void);

static void EM_LCD_DisplayImportActiveEnergyTariff(void);
static void EM_LCD_DisplayImportCapacitiveReactiveEnergyTariff(void);
static void EM_LCD_DisplayImportInductiveReactiveEnergyTariff(void);
static void EM_LCD_DisplayImportApparentEnergyTariff(void);
static void EM_LCD_DisplayExportActiveEnergyTariff(void);
static void EM_LCD_DisplayExportCapacitiveReactiveEnergyTariff(void);
static void EM_LCD_DisplayExportInductiveReactiveEnergyTariff(void);
static void EM_LCD_DisplayExportApparentEnergyTariff(void);

/* Max Demand */
static void EM_LCD_DisplayActMaxDemand(void);
static void EM_LCD_DisplayCapacitiveReactiveMaxDemand(void);
static void EM_LCD_DisplayInductiveReactiveMaxDemand(void);
static void EM_LCD_DisplayAppMaxDemand(void);

/* Support calculation/display function */
void EM_LCD_DisplayPOR(void);

static void EM_LCD_DisplayStatus(void);

/* Counter variable , etc. */
static uint8_t      g_is_display_changed_next = 1;
static uint8_t      g_DispCounter = 0;  /* first position is voltage */
static uint8_t      g_auto_roll = 1;
static uint8_t      g_is_por = 0;

typedef void (* fp_display_t)(void);
/* Function pointer for EM Get Tariff Energy */
typedef uint8_t (* fp_tariff_t)(uint8_t tariff, float32_t * energy);

/*
* Display list, scroll over at end
* Append or move the display API inside this list for arrangement
* of LCD display
*/
const fp_display_t fp_display[] = 
{
    /*
    * Common display: LCD on all, Unit Code, SW ver., Date, Time, etc
    */
    LCD_DisplayAll,
    //EM_DisplayUnitCode,
    //EM_LCD_DisplaySoftVersion,
    EM_DisplayDate,
    EM_DisplayInstantTime,

    /*
    * Instant parameters: VRMS, IRMS, Fundamental RMS, Power, Energy, etc
    */
    /* VRMS */
    EM_LCD_DisplayInstantVolt_Phase_R,
    EM_LCD_DisplayInstantVolt_Phase_Y,
    EM_LCD_DisplayInstantVolt_Phase_B,
    EM_LCD_DisplayInstantVolt_Total,

    /* IRMS */
    EM_LCD_DisplayInstantCurrent_Phase_R,
    EM_LCD_DisplayInstantCurrent_Phase_Y,
    EM_LCD_DisplayInstantCurrent_Phase_B,
    EM_LCD_DisplayInstantCurrent_Total,
    EM_LCD_DisplayInstantCurrent_Neutral,

    /* Current SUM vector */
    EM_LCD_DisplayPhaseCurrentSumVector,

    /* PF */
    EM_LCD_DisplayPowerFactor_Phase_R,
    EM_LCD_DisplayPowerFactor_Phase_Y,
    EM_LCD_DisplayPowerFactor_Phase_B,
    EM_LCD_DisplayPowerFactor_Total,

    /* Freq */
    EM_LCD_DisplayLineFrequency,

    /* Power */
    EM_LCD_DisplayInstantActPower_Phase_R,
    EM_LCD_DisplayInstantActPower_Phase_Y,
    EM_LCD_DisplayInstantActPower_Phase_B,
    EM_LCD_DisplayInstantActPower_Total,

    EM_LCD_DisplayInstantReactPower_Phase_R,
    EM_LCD_DisplayInstantReactPower_Phase_Y,
    EM_LCD_DisplayInstantReactPower_Phase_B,
    EM_LCD_DisplayInstantReactPower_Total,
    
    EM_LCD_DisplayInstantFundamentalActPower_Phase_R,
    EM_LCD_DisplayInstantFundamentalActPower_Phase_Y,
    EM_LCD_DisplayInstantFundamentalActPower_Phase_B,
    EM_LCD_DisplayInstantFundamentalActPower_Total,
    
    EM_LCD_DisplayInstantAppPower_Phase_R,
    EM_LCD_DisplayInstantAppPower_Phase_Y,
    EM_LCD_DisplayInstantAppPower_Phase_B,
    EM_LCD_DisplayInstantAppPower_Total,

    /* THD */
    EM_LCD_DisplayVoltageTHD_Phase_R,
    EM_LCD_DisplayVoltageTHD_Phase_Y,
    EM_LCD_DisplayVoltageTHD_Phase_B,
    EM_LCD_DisplayCurrentTHD_Phase_R,
    EM_LCD_DisplayCurrentTHD_Phase_Y,
    EM_LCD_DisplayCurrentTHD_Phase_B,

    /* Energy */
    /* Import Energy (sum all tariff) */
    EM_LCD_DisplayImportActiveEnergy,
    EM_LCD_DisplayImportCapacitiveReactiveEnergy,
    EM_LCD_DisplayImportInductiveReactiveEnergy,
    EM_LCD_DisplayImportApparentEnergy,

    /* Export Energy (sum all tariff) */
    EM_LCD_DisplayExportActiveEnergy,
    EM_LCD_DisplayExportCapacitiveReactiveEnergy,
    EM_LCD_DisplayExportInductiveReactiveEnergy,
    EM_LCD_DisplayExportApparentEnergy,

    /* Import Energy (each tariff) */
    EM_LCD_DisplayImportActiveEnergyTariff,
    EM_LCD_DisplayImportCapacitiveReactiveEnergyTariff,
    EM_LCD_DisplayImportInductiveReactiveEnergyTariff,
    EM_LCD_DisplayImportApparentEnergyTariff,

    /* Export Energy (each tariff) */
    EM_LCD_DisplayExportActiveEnergyTariff,
    EM_LCD_DisplayExportCapacitiveReactiveEnergyTariff,
    EM_LCD_DisplayExportInductiveReactiveEnergyTariff,
    EM_LCD_DisplayExportApparentEnergyTariff,

    /* Max demand */
    EM_LCD_DisplayActMaxDemand,
    EM_LCD_DisplayCapacitiveReactiveMaxDemand,
    EM_LCD_DisplayInductiveReactiveMaxDemand,
    EM_LCD_DisplayAppMaxDemand,

    /* Don't delete me, always end this list with NULL */
    NULL,
};

/***********************************************************************************************************************
* Function Name: void EM_DisplaySequence(void)
* Description  : 
* Arguments    : none
* Output       : none
* Return Value : none               
***********************************************************************************************************************/
void EM_DisplaySequence(void)
{   
    /* Refresh the LCD if 1s changed */
    if (g_event_request_flag.is_lcd_refresh || g_is_display_changed_next == 1) 
    {
        /* Clear before display new parameter */
        if (g_is_display_changed_next == 1)
        {
            LCD_ClearAll();
            g_is_display_changed_next = 0;
        }
        
        /* Display the parameter */
        if (fp_display[g_DispCounter] != NULL)
        {
            (fp_display[g_DispCounter])();
        }
        
        /* Display status */
        if (g_DispCounter != 0)
        {
            EM_LCD_DisplayStatus();
        }
        
        g_event_request_flag.is_lcd_refresh = 0;
        R_WDT_Restart();
    }

    if (g_auto_roll)
    {
        if (g_event_request_flag.is_lcd_scroll)
        {
            g_DispCounter++;
            if (fp_display[g_DispCounter] == NULL)
            {
                g_DispCounter = 0;
            }
            g_is_display_changed_next = 1;
            g_event_request_flag.is_lcd_scroll = 0;
        }   
    }

    R_WDT_Restart();
}


/***********************************************************************************************************************
* Function Name: void EM_DisplayStatus(EM_STATUS *status)
* Description  : Display tamper status of EM
* Arguments    : none
* Output       : none
* Return Value : none
***********************************************************************************************************************/
static void EM_LCD_DisplayStatus(void)
{
    if (EVENT_IsCurrentReverse_R() ||
        EVENT_IsCurrentReverse_Y() ||
        EVENT_IsCurrentReverse_B())
    {
        LCD_DisplaySpSign(S_REV);
    }
    else
    {
        LCD_ClearSpSign(S_REV);
    }
    
    if (EVENT_IsMagnetic() == 1)
    {
        LCD_DisplaySpSign(S_MAG);
    }
    else
    {
        LCD_ClearSpSign(S_MAG);
    }

    #ifdef POWER_MANAGEMENT_ENABLE
    if (POWERMGMT_IsVBATLow() != 0)
    {
//        LCD_DisplaySpSign(S_T10);
//        LCD_ClearSpSign(S_T11);
//        LCD_ClearSpSign(S_T12);
//        LCD_ClearSpSign(S_T13);
    }
    else
    {
//        LCD_DisplaySpSign(S_T10);
//        LCD_DisplaySpSign(S_T11);
//        LCD_DisplaySpSign(S_T12);
//        LCD_DisplaySpSign(S_T13);
    }
    
    if (POWERMGMT_IsVRTCLow() != 0)
    {
        LCD_DisplaySpSign(S_T9);
    }
    else 
    {
        LCD_ClearSpSign(S_T9);
    }
    #else
    if (LVDVRTCF == 1)
    {
        LCD_DisplaySpSign(S_T9);
    }
    else 
    {
        LCD_ClearSpSign(S_T9);
    }
    #endif /* POWER_MANAGEMENT_ENABLE */

}

/*  Display instantaneous measured value */
/***********************************************************************************************************************
* Function Name: void EM_DisplayUnitCode(void)
* Description  : Display unit code on LCD screen (now, it is fixed RE0001)
* Arguments    : none
* Output       : none
* Return Value : none               
***********************************************************************************************************************/
static void EM_DisplayUnitCode(void)
{
    LCD_ClearAll();
    LCD_DisplayDigit(9, 30);//U
    LCD_DisplayDigit(10, 23);//n
    LCD_DisplayDigit(11, 12);//C
    LCD_DisplayDigit(12, 24);//O
    LCD_DisplayDigit(13, 13);//D
    LCD_DisplayDigit(14, 14);//E
    LCD_DisplayDigit(1, LCD_CHAR_A);
    LCD_DisplayDigit(2, LCD_CHAR_E);
    LCD_DisplayDigit(3, 23);//n
    LCD_DisplayDigit(4, 0);
    LCD_DisplayDigit(5, 0);
    LCD_DisplayDigit(6, 3);
    LCD_DisplayDigit(7, 7);
    LCD_ClearSpSign(S_TIME);
}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplaySoftVersion(void)
* Description  : Display unit code on LCD screen (now, it is fixed RE0001)
* Arguments    : none
* Output       : none
* Return Value : none               
***********************************************************************************************************************/
static void EM_LCD_DisplaySoftVersion(void)
{
	LCD_DisplayDigit(9, 30);//V
    LCD_DisplayDigit(10, 14);//E
    LCD_DisplayDigit(11, 27);//R
    LCD_DisplayDigit(1, 30);//U
    LCD_DisplayDigit(2, 23);//n
    LCD_DisplayDigit(3, 0);
    LCD_DisplayDigit(4, 1);
    LCD_DisplayDigit(5, 0);
	LCD_DisplayDigit(6, 9);
	LCD_DisplayDigit(7, 2);
	LCD_DisplayDigit(8, 3);
}

/***********************************************************************************************************************
* Function Name: void EM_DisplayInstantTime(void)
* Description  : Display time (hh:mm:ss) and TIME sign on LCD screen
* Arguments    : none
* Output       : none
* Return Value : none               
***********************************************************************************************************************/
static void EM_DisplayInstantTime(void)
{
    rtc_counter_value_t data;
    TIME_DATA_INFO      disp_data;
    
    /* Get RTC data */
    R_RTC_Get_CalendarCounterValue(&data);
    
    /* Set time data to display */
    disp_data.hour  = data.hour;
    disp_data.min   = data.min;
    disp_data.sec   = data.sec;
	LCD_DisplayDigit(9, 0);//0
    LCD_WriteRAMDigitInfo(LCD_RAM_START_ADDRESS + 17, (0x1 << 7));//.
    LCD_DisplayDigit(10, 9);//9
    LCD_WriteRAMDigitInfo(LCD_RAM_START_ADDRESS + 16, (0x1 << 7));//.
    LCD_DisplayDigit(11, 1);//1
	
    LCD_DisplayTime(disp_data, 1);
    
    /* Display TIME sign */
    if (g_is_por != 0)
    {
       // LCD_DisplaySpSign(S_TOD);
    }
    LCD_DisplaySpSign(S_TIME);
}

/***********************************************************************************************************************
* Function Name: void EM_DisplayDate(void)
* Description  : Display time (dd:MM:yy) and DATE sign on LCD screen
* Arguments    : none
* Output       : none
* Return Value : none               
***********************************************************************************************************************/
static void EM_DisplayDate(void)
{
    rtc_counter_value_t data;
    TIME_DATA_INFO      disp_data;
    
    /* Get RTC data */
    R_RTC_Get_CalendarCounterValue(&data);
    
    /* Set time data to display */
    disp_data.hour  = data.day;
    disp_data.min   = data.month;
    disp_data.sec   = (uint8_t)data.year;
    LCD_DisplayDigit(9, 0);//0
    LCD_WriteRAMDigitInfo(LCD_RAM_START_ADDRESS + 17, (0x1 << 7));//.
    LCD_DisplayDigit(10, 9);//9
    LCD_WriteRAMDigitInfo(LCD_RAM_START_ADDRESS + 16, (0x1 << 7));//.
    LCD_DisplayDigit(11, 2);//2
	
    LCD_DisplayTime(disp_data, 1);
    
    /* Display DATE sign */
    if (g_is_por != 0)
    {
        //LCD_DisplaySpSign(S_TOD);
    }
    LCD_DisplaySpSign(S_DATE);
}

/*  Display instantaneous measured value */

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantVolt(EM_LINE line)
* Description  : Display instanatanous measured voltage for a specifed phase
* Arguments    : EM_LINE line: Line want to display
* Output       : none
* Return Value : none           
***********************************************************************************************************************/
static void EM_LCD_DisplayInstantVolt(EM_LINE line)
{
    if (line <= LINE_TOTAL)
    {
        LCD_DisplayFloat(g_inst_read_params.vrms[line]);
    }
    else
    {
        LCD_DisplayFloat(0.0f);
    }

    /* Display "V" sign */
    LCD_DisplaySpSign(S_T2);
}


/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantVolt_Phase_R(void)
* Description  : Display instanatanous measured voltage
* Arguments    : none
* Output       : none
* Return Value : none           
***********************************************************************************************************************/
static void EM_LCD_DisplayInstantVolt_Phase_R(void)
{
    EM_LCD_DisplayInstantVolt(LINE_PHASE_R);
    /* Display "R" sign */
    //LCD_DisplaySpSign(S_R);
	LCD_DisplayDigit(1,1);
}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantVolt_Phase_Y(void)
* Description  : Display instanatanous measured voltage
* Arguments    : none
* Output       : none
* Return Value : none           
***********************************************************************************************************************/
static void EM_LCD_DisplayInstantVolt_Phase_Y(void)
{
    EM_LCD_DisplayInstantVolt(LINE_PHASE_Y);
    /* Display "Y" sign */
    //LCD_DisplaySpSign(S_Y);
	LCD_DisplayDigit(1,2);
}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantVolt_Phase_B(void)
* Description  : Display instanatanous measured voltage
* Arguments    : none
* Output       : none
* Return Value : none           
***********************************************************************************************************************/
static void EM_LCD_DisplayInstantVolt_Phase_B(void)
{
    EM_LCD_DisplayInstantVolt(LINE_PHASE_B);
    /* Display "B" sign */
    //LCD_DisplaySpSign(S_B);
	LCD_DisplayDigit(1,3);
}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantVolt_Total(void)
* Description  : Display instanatanous measured voltage
* Arguments    : none
* Output       : none
* Return Value : none           
***********************************************************************************************************************/
static void EM_LCD_DisplayInstantVolt_Total(void)
{
    EM_LCD_DisplayInstantVolt(LINE_TOTAL);
    /* Display <none> sign */
    
}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantCurrent(void)
* Description  : Display instantanous measured phase current
* Arguments    : EM_LINE line: Line want to display
* Output       : none
* Return Value : none
***********************************************************************************************************************/
static void EM_LCD_DisplayInstantCurrent(EM_LINE line)
{
    /* Modify to get enough length for LCD if necessary */
    if (line <= LINE_TOTAL)
    {
        LCD_DisplayFloat(g_inst_read_params.irms[line]);
    }
    else
    {
        LCD_DisplayFloat(0.0f);
    }

    /* Display "A" sign */
    LCD_DisplaySpSign(S_T4);
    //LCD_DisplaySpSign(S_T5);
}



/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantCurrent_Phase_R(void)
* Description  : Display instantanous measured phase current
* Arguments    : none
* Output       : none
* Return Value : none
***********************************************************************************************************************/
static void EM_LCD_DisplayInstantCurrent_Phase_R(void)
{
    EM_LCD_DisplayInstantCurrent(LINE_PHASE_R);
    /* Display "R" sign */
    //LCD_DisplaySpSign(S_R);
	LCD_DisplayDigit(1,1);
}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantCurrent_Phase_Y(void)
* Description  : Display instantanous measured neutral current
* Arguments    : none
* Output       : none
* Return Value : none
***********************************************************************************************************************/
static void EM_LCD_DisplayInstantCurrent_Phase_Y(void)
{
    EM_LCD_DisplayInstantCurrent(LINE_PHASE_Y);
    /* Display "Y" sign */
    //LCD_DisplaySpSign(S_Y);
	LCD_DisplayDigit(1,2);
}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantCurrent_Phase_B(void)
* Description  : Display instantanous measured neutral current
* Arguments    : none
* Output       : none
* Return Value : none
***********************************************************************************************************************/
static void EM_LCD_DisplayInstantCurrent_Phase_B(void)
{
    EM_LCD_DisplayInstantCurrent(LINE_PHASE_B);
    /* Display "B" sign */
    //LCD_DisplaySpSign(S_B);
	LCD_DisplayDigit(1,3);
}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantCurrent_Neutral(void)
* Description  : Display instantanous measured neutral current
* Arguments    : none
* Output       : none
* Return Value : none
***********************************************************************************************************************/
static void EM_LCD_DisplayInstantCurrent_Neutral(void)
{
    EM_LCD_DisplayInstantCurrent(LINE_NEUTRAL);
    /* Display N at digit 9 */
    //LCD_DisplayDigit(1, 22);
}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantCurrent_Total(void)
* Description  : Display instantanous measured neutral current
* Arguments    : none
* Output       : none
* Return Value : none
***********************************************************************************************************************/
static void EM_LCD_DisplayInstantCurrent_Total(void)
{
    EM_LCD_DisplayInstantCurrent(LINE_TOTAL);
    /* Display <blank> at digit 9 */
}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantActPower_Phase_R(void)
* Description  : Display instantanous measured active power
* Arguments    : EM_LINE line: Line want to display
* Output       : none
* Return Value : none
***********************************************************************************************************************/
static void EM_LCD_DisplayInstantActPower(EM_LINE line)
{
    /* Modify to get enough length for LCD if necessary */
    if (line <= LINE_TOTAL)
    {
        LCD_DisplayFloat(g_inst_read_params.active_power[line]);
    }
    else
    {
        LCD_DisplayFloat(0.0f);
    }

    /* Display "W" sign */
    LCD_DisplaySpSign(S_T2);
    LCD_DisplaySpSign(S_T3);
    //LCD_DisplaySpSign(S_T4);
}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantActPower_Phase_R(void)
* Description  : Display instantanous measured active power of phase R
* Arguments    : none
* Output       : none
* Return Value : none           
***********************************************************************************************************************/
static void EM_LCD_DisplayInstantActPower_Phase_R(void)
{
    EM_LCD_DisplayInstantActPower(LINE_PHASE_R);
    /* Display "R" sign */
    //LCD_DisplaySpSign(S_R);
	LCD_DisplayDigit(1,1);
}
/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantActPower_Phase_Y(void)
* Description  : Display instantanous measured active power of phase Y
* Arguments    : none
* Output       : none
* Return Value : none           
***********************************************************************************************************************/
static void EM_LCD_DisplayInstantActPower_Phase_Y(void)
{
    EM_LCD_DisplayInstantActPower(LINE_PHASE_Y);
    /* Display "Y" sign */
    //LCD_DisplaySpSign(S_Y);
	LCD_DisplayDigit(1,2);
}
/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantActPower_Phase_B(void)
* Description  : Display instantanous measured active power of phase B
* Arguments    : none
* Output       : none
* Return Value : none           
***********************************************************************************************************************/
static void EM_LCD_DisplayInstantActPower_Phase_B(void)
{
    EM_LCD_DisplayInstantActPower(LINE_PHASE_B);
    /* Display "B" sign */
    //LCD_DisplaySpSign(S_B);
	LCD_DisplayDigit(1,3);
}
/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantActPower_Total(void)
* Description  : Display instantanous measured active total power
* Arguments    : none
* Output       : none
* Return Value : none           
***********************************************************************************************************************/
static void EM_LCD_DisplayInstantActPower_Total(void)
{
    EM_LCD_DisplayInstantActPower(LINE_TOTAL);
    /* Display <blank> sign */

}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantReactPower(EM_LINE line)
* Description  : Display instantaneous measured reactive power of phase line
* Arguments    : EM_LINE line: Line want to display
* Output       : none
* Return Value : none
***********************************************************************************************************************/
static void EM_LCD_DisplayInstantReactPower(EM_LINE line)
{
    /* Modify to get enough length for LCD if necessary */
    if (line <= LINE_TOTAL)
    {
        LCD_DisplayFloat(g_inst_read_params.reactive_power[line]);
    }
    else
    {
        LCD_DisplayFloat(0.0f);
    }

    /* Display "VAr" sign */
    LCD_DisplaySpSign(S_T2);
    LCD_DisplaySpSign(S_T4);
    LCD_DisplaySpSign(S_T5);
}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantReactPower_Phase_R(void)
* Description  : Display instantaneous measured reactive power of phase R
* Arguments    : none
* Output       : none
* Return Value : none           
***********************************************************************************************************************/
static void EM_LCD_DisplayInstantReactPower_Phase_R(void)
{
    EM_LCD_DisplayInstantReactPower(LINE_PHASE_R);
    /* Display "R" sign */
    //LCD_DisplaySpSign(S_R);
	LCD_DisplayDigit(1,1);
}
/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantReactPower_Phase_Y(void)
* Description  : Display instantaneous measured reactive power of phase Y
* Arguments    : none
* Output       : none
* Return Value : none           
***********************************************************************************************************************/
static void EM_LCD_DisplayInstantReactPower_Phase_Y(void)
{
    EM_LCD_DisplayInstantReactPower(LINE_PHASE_Y);
    /* Display "Y" sign */
    //LCD_DisplaySpSign(S_Y);
	LCD_DisplayDigit(1,2);
}
/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantReactPower_Phase_B(void)
* Description  : Display instantaneous measured reactive power
* Arguments    : none
* Output       : none
* Return Value : none           
***********************************************************************************************************************/
static void EM_LCD_DisplayInstantReactPower_Phase_B(void)
{
    EM_LCD_DisplayInstantReactPower(LINE_PHASE_B);
    /* Display "B" sign */
    //LCD_DisplaySpSign(S_B);
	LCD_DisplayDigit(1,3);
}
/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantActPower_Total(void)
* Description  : Display instantaneous measured reactive total power
* Arguments    : none
* Output       : none
* Return Value : none           
***********************************************************************************************************************/
static void EM_LCD_DisplayInstantReactPower_Total(void)
{
    EM_LCD_DisplayInstantReactPower(LINE_TOTAL);
    /* Display <blank> sign */
}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantFundamentalActPower(EM_Line line)
* Description  : Display instantanous measured fundamental active power
* Arguments    : EM_LINE line: Line want to display
* Output       : none
* Return Value : none           
***********************************************************************************************************************/
 static void EM_LCD_DisplayInstantFundamentalActPower(EM_LINE line)
 {
   /* Modify to get enough length for LCD if necessary */
   /* TBD */
   
   /* Display measured value */
   LCD_DisplayFloat(g_inst_read_params.fundamental_power[line]);
     
   /* Display "W" sign */
   	LCD_DisplaySpSign(S_T2);
    LCD_DisplaySpSign(S_T3);
 
   /* Display F0 at digit 7 and 8 */
   LCD_DisplayDigit(8, LCD_CHAR_F);
   LCD_DisplayDigit(9, 0); 
 }
 
/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantFundamentalActPower_Phase_R(void)
* Description  : Display instantanous measured fundamental active power on phase R
* Arguments    : none
* Output       : none
* Return Value : none           
***********************************************************************************************************************/
 static void EM_LCD_DisplayInstantFundamentalActPower_Phase_R(void)
 {
    EM_LCD_DisplayInstantFundamentalActPower(LINE_PHASE_R);
    /* Display "R" sign */
    //LCD_DisplaySpSign(S_R);
	LCD_DisplayDigit(1, 1);
 }
 
/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantFundamentalActPower_Phase_Y(void)
* Description  : Display instantanous measured fundamental active power on phase Y
* Arguments    : none
* Output       : none
* Return Value : none           
***********************************************************************************************************************/
 static void EM_LCD_DisplayInstantFundamentalActPower_Phase_Y(void)
 {
    EM_LCD_DisplayInstantFundamentalActPower(LINE_PHASE_Y);
    /* Display "Y" sign */
    //LCD_DisplaySpSign(S_Y);
	LCD_DisplayDigit(1, 2);
 }
 
/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantFundamentalActPower_Phase_B(void)
* Description  : Display instantanous measured fundamental active power on phase B
* Arguments    : none
* Output       : none
* Return Value : none           
***********************************************************************************************************************/
 static void EM_LCD_DisplayInstantFundamentalActPower_Phase_B(void)
 {
    EM_LCD_DisplayInstantFundamentalActPower(LINE_PHASE_B);
    /* Display "B" sign */
    //LCD_DisplaySpSign(S_B);
	LCD_DisplayDigit(1, 3);
 }

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantFundamentalActPower_Total(void)
* Description  : Display instantanous measured fundamental active power total
* Arguments    : none
* Output       : none
* Return Value : none           
***********************************************************************************************************************/
 static void EM_LCD_DisplayInstantFundamentalActPower_Total(void)
 {
    EM_LCD_DisplayInstantFundamentalActPower(LINE_TOTAL);
    /* Display <blank> sign */
    
 }
 
/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantAppPower(void)
* Description  : Display instantaneous measured apparent power
* Arguments    : EM_LINE line: Line want to display
* Output       : none
* Return Value : none
***********************************************************************************************************************/
static void EM_LCD_DisplayInstantAppPower(EM_LINE line)
{
    /* Modify to get enough length for LCD if necessary */
    if (line <= LINE_TOTAL)
    {
        LCD_DisplayFloat(g_inst_read_params.apparent_power[line]);
    }
    else
    {
        LCD_DisplayFloat(0.0f);
    }

    /* Display "VA" sign */
    LCD_DisplaySpSign(S_T2);
    LCD_DisplaySpSign(S_T4);
    LCD_DisplaySpSign(S_T5);
}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantAppPower_Phase_R(void)
* Description  : Display instantaneous measured apparent power of phase R
* Arguments    : none
* Output       : none
* Return Value : none                                         
***********************************************************************************************************************/
static void EM_LCD_DisplayInstantAppPower_Phase_R(void)
{
    EM_LCD_DisplayInstantAppPower(LINE_PHASE_R);
    /* Display "R" sign */
    //LCD_DisplaySpSign(S_R);
	LCD_DisplayDigit(1, 1);
}
/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantAppPower_Phase_Y(void)
* Description  : Display instantaneous measured apparent power of phase Y
* Arguments    : none
* Output       : none
* Return Value : none                                         
***********************************************************************************************************************/
static void EM_LCD_DisplayInstantAppPower_Phase_Y(void)
{
    EM_LCD_DisplayInstantAppPower(LINE_PHASE_Y);
    /* Display "Y" sign */
    //LCD_DisplaySpSign(S_Y);
	LCD_DisplayDigit(1, 2);
}
/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantAppPower_Phase_B(void)
* Description  : Display instantaneous measured apparent power of phase B
* Arguments    : none
* Output       : none
* Return Value : none                                         
***********************************************************************************************************************/
static void EM_LCD_DisplayInstantAppPower_Phase_B(void)
{
    EM_LCD_DisplayInstantAppPower(LINE_PHASE_B);
    /* Display "B" sign */
    //LCD_DisplaySpSign(S_B);
	LCD_DisplayDigit(1, 3);
}
/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayInstantAppPower_Total(void)
* Description  : Display instantaneous measured total apparent power
* Arguments    : none
* Output       : none
* Return Value : none
***********************************************************************************************************************/
static void EM_LCD_DisplayInstantAppPower_Total(void)
{
    EM_LCD_DisplayInstantAppPower(LINE_TOTAL);
    /* Display <blank> sign */
}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayLineFrequency(void)
* Description  : Display operation line frequency of EM
* Arguments    : none
* Output       : none
* Return Value : none
***********************************************************************************************************************/
static void EM_LCD_DisplayLineFrequency(void)
{
    /* Modify to get enough length for LCD if necessary */
    LCD_DisplayFloat(g_inst_read_params.freq[LINE_TOTAL]);
    
    /* Display "h" sign */
    LCD_DisplaySpSign(S_T7);
    LCD_DisplaySpSign(S_T8);
}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayPowerFactor(void)
* Description  : Display power factor of input signal
* Arguments    : EM_LINE line: Line want to display
* Output       : none
* Return Value : none
***********************************************************************************************************************/
static void EM_LCD_DisplayPowerFactor(EM_LINE line)
{
    float32_t   pf;
    EM_PF_SIGN  pf_sign;

    /* Modify to get enough length for LCD if necessary */
    if (line <= LINE_TOTAL)
    {
		pf = g_inst_read_params.power_factor[line];
    	pf_sign = g_inst_read_params.power_factor_sign[line];
		
        LCD_DisplayFloat(pf);

        if (pf_sign == PF_SIGN_LEAD_C)
        {
            LCD_DisplayDigit(1, LCD_CHAR_C);
        }
        else if (pf_sign == PF_SIGN_LAG_L)
        {
            LCD_DisplayDigit(1, LCD_CHAR_L);
        }
        else if (pf_sign == PF_SIGN_UNITY)
        {
            LCD_ClearDigit(1);
        }
    }
    else
    {
        LCD_DisplayFloat(0.0f);
        LCD_ClearDigit(1);
    }

    /* Display "PF" sign */
    LCD_DisplayDigit(8, LCD_CHAR_P);
    LCD_DisplayDigit(9, LCD_CHAR_F);
}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayPowerFactor_Phase_R(void)
* Description  : Display power factor of input signal on phase R
* Arguments    : none
* Output       : none
* Return Value : none
***********************************************************************************************************************/
static void EM_LCD_DisplayPowerFactor_Phase_R(void)
{
    EM_LCD_DisplayPowerFactor(LINE_PHASE_R);
    /* Display "R" sign */
    //LCD_DisplaySpSign(S_R);
	LCD_DisplayDigit(1, 1);
}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayPowerFactor_Phase_Y(void)
* Description  : Display power factor of input signal on phase Y
* Arguments    : none
* Output       : none
* Return Value : none
***********************************************************************************************************************/
static void EM_LCD_DisplayPowerFactor_Phase_Y(void)
{
    EM_LCD_DisplayPowerFactor(LINE_PHASE_Y);
    /* Display "Y" sign */
    //LCD_DisplaySpSign(S_Y);
	LCD_DisplayDigit(1, 2);
}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayPowerFactor_Phase_B(void)
* Description  : Display power factor of input signal on phase B
* Arguments    : none
* Output       : none
* Return Value : none           
***********************************************************************************************************************/
static void EM_LCD_DisplayPowerFactor_Phase_B(void)
{
    EM_LCD_DisplayPowerFactor(LINE_PHASE_B);
    /* Display "B" sign */
    //LCD_DisplaySpSign(S_B);
	LCD_DisplayDigit(1, 3);
}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayPowerFactor_Total(void)
* Description  : Display power factor of input signal Total
* Arguments    : none
* Output       : none
* Return Value : none           
***********************************************************************************************************************/
static void EM_LCD_DisplayPowerFactor_Total(void)
{
    EM_LCD_DisplayPowerFactor(LINE_TOTAL);
    /* Display <blank> sign */
    
}

/*
* LCD Energy display function
*/

/******************************************************************************
* Function Name: void EM_LCD_DisplayImportExportStatus(uint8_t is_import)
* Description  : Display import or export status on LCD
* Arguments    : uint8_t is_import: energy direction
* Output       : none
* Return Value : none
******************************************************************************/
static void EM_LCD_DisplayImportExportStatus(uint8_t is_import)
{
    if (is_import == EM_LCD_IMPORT_ENERGY)
    {
        /* Display "import" sign "1" on digit 9 */
        LCD_DisplayDigit(9, 1);
    }
    else
    {
        /* Display "export" sign "E" on digit 9 */
        //LCD_DisplayDigit(9, LCD_CHAR_E);
    }
}

/******************************************************************************
* Function Name: void EM_LCD_DisplayInputActiveEnergy(float32_t value, uint8_t is_import)
* Description  : Display input reactive energy on LCD with energy direction option
* Arguments    : float32_t value: energy value
*              : uint8_t is_import: energy direction
* Output       : none
* Return Value : none
******************************************************************************/
static void EM_LCD_DisplayInputActiveEnergy(float32_t value, uint8_t is_import)
{
    LCD_DisplayFloat(value);

    /* Display "kWh" sign */
    LCD_DisplaySpSign(S_T1);
    LCD_DisplaySpSign(S_T2);
    LCD_DisplaySpSign(S_T3);
    LCD_DisplaySpSign(S_T4);
    LCD_DisplaySpSign(S_T7);

    /* Display import & export status */
    EM_LCD_DisplayImportExportStatus(is_import);
}

/******************************************************************************
* Function Name: void EM_LCD_DisplayInputApparentEnergy(float32_t value, uint8_t is_import, uint8_t is_inductive)
* Description  : Display input reactive energy on LCD with energy direction and reactive type option
* Arguments    : float32_t value: energy value
*              : uint8_t is_import: energy direction
*              : uint8_t is_inductive: reactive type
* Output       : none
* Return Value : none
******************************************************************************/
static void EM_LCD_DisplayInputReactiveEnergy(float32_t value, uint8_t is_import, uint8_t is_inductive)
{
    LCD_DisplayFloat(value);

    /* Display "kVArh" sign */
    LCD_DisplaySpSign(S_T1);	//k
    LCD_DisplaySpSign(S_T2);	//v
    LCD_DisplaySpSign(S_T4);	//A
    LCD_DisplaySpSign(S_T5);	//r
    //LCD_DisplaySpSign(S_T6);
    LCD_DisplaySpSign(S_T7);	//h

    if (is_inductive == EM_LCD_INDUCTIVE_REACTIVE)
    {
        /* Display "L" as Lag at digit 1 */
        LCD_DisplayDigit(1, LCD_CHAR_L);
    }
    else
    {
        /* Display "C" as Lead at digit 1 */
        LCD_DisplayDigit(1, LCD_CHAR_C);
    }

    /* Display import & export status */
    EM_LCD_DisplayImportExportStatus(is_import);
}

/******************************************************************************
* Function Name: void EM_LCD_DisplayInputApparentEnergy(float32_t value)
* Description  : Display input apparent energy on LCD
* Arguments    : float32_t value: apparent energy value
* Output       : none
* Return Value : none
******************************************************************************/
static void EM_LCD_DisplayInputApparentEnergy(float32_t value, uint8_t is_import)
{
    LCD_DisplayFloat(value);

    /* Display "kVAh" sign */
    LCD_DisplaySpSign(S_T1);
    LCD_DisplaySpSign(S_T2);
    LCD_DisplaySpSign(S_T4);
    LCD_DisplaySpSign(S_T5);
    LCD_DisplaySpSign(S_T7);

    /* Display import & export status */
    EM_LCD_DisplayImportExportStatus(is_import);
}

/******************************************************************************
* Function Name: void EM_LCD_DisplayTariffNumber(uint8_t tariff_no)
* Description  : Display tariff number on LCD
* Arguments    : uint8_t tariff_no:
* Output       : none
* Return Value : none
******************************************************************************/
static void EM_LCD_DisplayTariffNumber(uint8_t tariff_no)
{
    /* Display tariff number at digit 8 */
    LCD_DisplayDigit(8, tariff_no);
}

/******************************************************************************
* Function Name: void EM_LCD_DisplayInputActiveEnergyTariff(fp_tariff_t fp_tariff, uint8_t is_import)
* Description  : Call to get the tariff reactive energy with option of energy direction
* Arguments    : fp_tariff_t fp_tariff: function pointer to tariff function on EM
*              : uint8_t is_import: energy direction
* Output       : none
* Return Value : none
******************************************************************************/
static void EM_LCD_DisplayInputActiveEnergyTariff(fp_tariff_t fp_tariff, uint8_t is_import)
{
    float   act_energy;
    uint8_t current_tariff;
    uint8_t return_status;

    /* Get the current active active tariff */
    current_tariff = g_tariff.current_tariff_no;

    /* Get active energy at active tariff */
    return_status = fp_tariff(current_tariff, &act_energy);

    if (return_status == EM_OK)
    {
        EM_LCD_DisplayInputActiveEnergy(act_energy, is_import);

        EM_LCD_DisplayTariffNumber(current_tariff);
    }
}

/******************************************************************************
* Function Name: void EM_LCD_DisplayInputReactiveEnergyTariff(fp_tariff_t fp_tariff, uint8_t is_import, uint8_t is_inductive)
* Description  : Call to get the tariff reactive energy with option of energy direction and reactive type
* Arguments    : fp_tariff_t fp_tariff: function pointer to tariff function on EM
*              : uint8_t is_import: energy direction
*              : uint8_t is_inductive: reactive type
* Output       : none
* Return Value : none
******************************************************************************/
static void EM_LCD_DisplayInputReactiveEnergyTariff(fp_tariff_t fp_tariff, uint8_t is_import, uint8_t is_inductive)
{
    float   react_energy;
    uint8_t current_tariff;
    uint8_t return_status;

    /* Get the current active active tariff */
    current_tariff = g_tariff.current_tariff_no;

    /* Get active energy at active tariff */
    return_status = fp_tariff(current_tariff, &react_energy);

    if (return_status == EM_OK)
    {
        EM_LCD_DisplayInputReactiveEnergy(react_energy, is_import, is_inductive);

        EM_LCD_DisplayTariffNumber(current_tariff);
    }
}

/******************************************************************************
* Function Name: void EM_LCD_DisplayInputReactiveMaxDemand(uint32_t value, uint8_t is_inductive)
* Description  : Call to display max demand unit and reactive type sign
* Arguments    : uint32_t value: max demand value (integer number)
*              : uint8_t is_inductive: reactive type
* Output       : none
* Return Value : none
******************************************************************************/
static void EM_LCD_DisplayInputReactiveMaxDemand(float32_t value, uint8_t is_inductive)
{
    float   react_energy;
    uint8_t current_tariff;
    uint8_t return_status;

    return_status = LCD_DisplayFloat(value);
    if (return_status == LCD_WRONG_INPUT_ARGUMENT)
    {
        /* TODO: notice input value is out of range */
    }

    /* Display "kVar" sign */
   LCD_DisplaySpSign(S_T1);
    LCD_DisplaySpSign(S_T2);
    LCD_DisplaySpSign(S_T4);
    LCD_DisplaySpSign(S_T5);
    //LCD_DisplaySpSign(S_T6);


    /* Display "MD" sign on LCD screen */
    LCD_DisplaySpSign(S_MD);

    if (is_inductive == EM_LCD_INDUCTIVE_REACTIVE)
    {
        /* Display "L" as Lag at digit 1 */
        LCD_DisplayDigit(1, LCD_CHAR_L);
    }
    else
    {
        /* Display "C" as Lead at digit 1 */
        LCD_DisplayDigit(1, LCD_CHAR_C);
    }
}

/******************************************************************************
* Function Name: void EM_LCD_DisplayImportActiveEnergy(void)
* Description  : Display import active enegy (sum of all tariff) of EM
* Arguments    : none
* Output       : none
* Return Value : none
******************************************************************************/
static void EM_LCD_DisplayImportActiveEnergy(void)
{
    /* Modify to get enough length for LCD if necessary */
    /* TBD */

    /* Display measured value */
    EM_LCD_DisplayInputActiveEnergy(R_TARIFF_GetImportActiveEnergyTotal(), EM_LCD_IMPORT_ENERGY);
}

/******************************************************************************
* Function Name: void EM_LCD_DisplayImportCapacitiveReactiveEnergy(void)
* Description  : Display import capacitive reactive enegy (sum of all tariff) of EM
* Arguments    : none
* Output       : none
* Return Value : none
******************************************************************************/
static void EM_LCD_DisplayImportCapacitiveReactiveEnergy(void)
{
    /* Modify to get enough length for LCD if necessary */
    /* TBD */

    /* Display measured value */
    EM_LCD_DisplayInputReactiveEnergy(R_TARIFF_GetImportCapacitiveReactiveEnergyTotal(), EM_LCD_IMPORT_ENERGY, EM_LCD_CAPACITIVE_REACTIVE);
}

/******************************************************************************
* Function Name: void EM_LCD_DisplayImportInductiveReactiveEnergy(void)
* Description  : Display import inductive reactive enegy (sum of all tariff) of EM
* Arguments    : none
* Output       : none
* Return Value : none
******************************************************************************/
static void EM_LCD_DisplayImportInductiveReactiveEnergy(void)
{
    /* Modify to get enough length for LCD if necessary */
    /* TBD */

    /* Display measured value */
    EM_LCD_DisplayInputReactiveEnergy(R_TARIFF_GetImportInductiveReactiveEnergyTotal(), EM_LCD_IMPORT_ENERGY, EM_LCD_INDUCTIVE_REACTIVE);
}

/******************************************************************************
* Function Name: void EM_LCD_DisplayImportApparentEnergy(void)
* Description  : Display apparent enegy (sum of all tariff) of EM
* Arguments    : none
* Output       : none
* Return Value : none
******************************************************************************/
static void EM_LCD_DisplayImportApparentEnergy(void)
{
    /* Modify to get enough length for LCD if necessary */
    /* TBD */

    /* Display measured value */
    EM_LCD_DisplayInputApparentEnergy(R_TARIFF_GetImportApparentEnergyTotal(), EM_LCD_IMPORT_ENERGY);
}

/******************************************************************************
* Function Name: void EM_LCD_DisplayExportActiveEnergy(void)
* Description  : Display export active enegy (sum of all tariff) of EM
* Arguments    : none
* Output       : none
* Return Value : none
******************************************************************************/
static void EM_LCD_DisplayExportActiveEnergy(void)
{
    /* Modify to get enough length for LCD if necessary */
    /* TBD */

    /* Display measured value */
    EM_LCD_DisplayInputActiveEnergy(R_TARIFF_GetExportActiveEnergyTotal(), EM_LCD_EXPORT_ENERGY);
}

/******************************************************************************
* Function Name: void EM_LCD_DisplayExportCapacitiveReactiveEnergy(void)
* Description  : Display export capacitive reactive enegy (sum of all tariff) of EM
* Arguments    : none
* Output       : none
* Return Value : none
******************************************************************************/
static void EM_LCD_DisplayExportCapacitiveReactiveEnergy(void)
{
    /* Modify to get enough length for LCD if necessary */
    /* TBD */

    /* Display measured value */
    EM_LCD_DisplayInputReactiveEnergy(R_TARIFF_GetExportCapacitiveReactiveEnergyTotal(), EM_LCD_EXPORT_ENERGY, EM_LCD_CAPACITIVE_REACTIVE);
}

/******************************************************************************
* Function Name: void EM_LCD_DisplayExportInductiveReactiveEnergy(void)
* Description  : Display export inductive reactive enegy (sum of all tariff) of EM
* Arguments    : none
* Output       : none
* Return Value : none
******************************************************************************/
static void EM_LCD_DisplayExportInductiveReactiveEnergy(void)
{
    /* Modify to get enough length for LCD if necessary */
    /* TBD */

    /* Display measured value */
    EM_LCD_DisplayInputReactiveEnergy(R_TARIFF_GetExportInductiveReactiveEnergyTotal(), EM_LCD_EXPORT_ENERGY, EM_LCD_INDUCTIVE_REACTIVE);
}

/******************************************************************************
* Function Name: void EM_LCD_DisplayExportApparentEnergy(void)
* Description  : Display apparent enegy (sum of all tariff) of EM
* Arguments    : none
* Output       : none
* Return Value : none
******************************************************************************/
static void EM_LCD_DisplayExportApparentEnergy(void)
{
    /* Modify to get enough length for LCD if necessary */
    /* TBD */

    /* Display measured value */
    EM_LCD_DisplayInputApparentEnergy(R_TARIFF_GetExportApparentEnergyTotal(), EM_LCD_EXPORT_ENERGY);
}

/******************************************************************************
* Function Name: void EM_LCD_DisplayImportActiveEnergyTariff(void)
* Description  : Display import active energy follow tariff
* Arguments    : none
* Output       : none
* Return Value : none
******************************************************************************/
static void EM_LCD_DisplayImportActiveEnergyTariff(void)
{
    EM_LCD_DisplayInputActiveEnergyTariff(R_TARIFF_GetImportActiveEnergyTariff, EM_LCD_IMPORT_ENERGY);
}

/******************************************************************************
* Function Name: void EM_LCD_DisplayImportCapacitiveReactiveEnergyTariff(void)
* Description  : Display import capacitive reactive energy follow tariff
* Arguments    : none
* Output       : none
* Return Value : none
******************************************************************************/
static void EM_LCD_DisplayImportCapacitiveReactiveEnergyTariff(void)
{
    EM_LCD_DisplayInputReactiveEnergyTariff(R_TARIFF_GetImportCapacitiveReactiveEnergyTariff, EM_LCD_IMPORT_ENERGY, EM_LCD_CAPACITIVE_REACTIVE);
}

/******************************************************************************
* Function Name: void EM_LCD_DisplayImportInductiveReactiveEnergyTariff(void)
* Description  : Display import inductive reactive energy follow tariff
* Arguments    : none
* Output       : none
* Return Value : none
******************************************************************************/
static void EM_LCD_DisplayImportInductiveReactiveEnergyTariff(void)
{
    EM_LCD_DisplayInputReactiveEnergyTariff(R_TARIFF_GetImportInductiveReactiveEnergyTariff, EM_LCD_IMPORT_ENERGY, EM_LCD_INDUCTIVE_REACTIVE);
}

/******************************************************************************
* Function Name: void EM_LCD_DisplayImportApparentEnergyTariff(void)
* Description  : Display apparent energy follow tariff
* Arguments    : none
* Output       : none
* Return Value : none
******************************************************************************/
static void EM_LCD_DisplayImportApparentEnergyTariff(void)
{
    float   app_energy;
    uint8_t current_tariff;
    uint8_t return_status;

    /* Get the current active active tariff */
    current_tariff = g_tariff.current_tariff_no;

    /* Get apparent energy at active tariff */
    return_status = R_TARIFF_GetImportApparentEnergyTariff(current_tariff, &app_energy);
    if (return_status == EM_OK)
    {
        EM_LCD_DisplayInputApparentEnergy(app_energy, EM_LCD_IMPORT_ENERGY);

        EM_LCD_DisplayTariffNumber(current_tariff);
    }
}

/******************************************************************************
* Function Name: void EM_LCD_DisplayExportActiveEnergyTariff(void)
* Description  : Display export active energy follow tariff
* Arguments    : none
* Output       : none
* Return Value : none
******************************************************************************/
static void EM_LCD_DisplayExportActiveEnergyTariff(void)
{
    EM_LCD_DisplayInputActiveEnergyTariff(R_TARIFF_GetExportActiveEnergyTariff, EM_LCD_EXPORT_ENERGY);
}

/******************************************************************************
* Function Name: void EM_LCD_DisplayExportCapacitiveReactiveEnergyTariff(void)
* Description  : Display export capacitive reactive energy follow tariff
* Arguments    : none
* Output       : none
* Return Value : none
******************************************************************************/
static void EM_LCD_DisplayExportCapacitiveReactiveEnergyTariff(void)
{
    EM_LCD_DisplayInputReactiveEnergyTariff(R_TARIFF_GetExportCapacitiveReactiveEnergyTariff, EM_LCD_EXPORT_ENERGY, EM_LCD_CAPACITIVE_REACTIVE);
}

/******************************************************************************
* Function Name: void EM_LCD_DisplayExportInductiveReactiveEnergyTariff(void)
* Description  : Display export inductive reactive energy follow tariff
* Arguments    : none
* Output       : none
* Return Value : none
******************************************************************************/
static void EM_LCD_DisplayExportInductiveReactiveEnergyTariff(void)
{
    EM_LCD_DisplayInputReactiveEnergyTariff(R_TARIFF_GetExportInductiveReactiveEnergyTariff, EM_LCD_EXPORT_ENERGY, EM_LCD_INDUCTIVE_REACTIVE);
}

/******************************************************************************
* Function Name: void EM_LCD_DisplayExportApparentEnergyTariff(void)
* Description  : Display apparent energy follow tariff
* Arguments    : none
* Output       : none
* Return Value : none
******************************************************************************/
static void EM_LCD_DisplayExportApparentEnergyTariff(void)
{
    float   app_energy;
    uint8_t current_tariff;
    uint8_t return_status;

    /* Get the current active active tariff */
    current_tariff = g_tariff.current_tariff_no;

    /* Get apparent energy at active tariff */
    return_status = R_TARIFF_GetExportApparentEnergyTariff(current_tariff, &app_energy);
    if (return_status == EM_OK)
    {
        EM_LCD_DisplayInputApparentEnergy(app_energy, EM_LCD_EXPORT_ENERGY);

        EM_LCD_DisplayTariffNumber(current_tariff);
    }
}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayPhaseCurrentSumVector(void)
* Description  : Display vector value of EM
* Arguments    : none
* Output       : none
* Return Value : none
***********************************************************************************************************************/
static void EM_LCD_DisplayPhaseCurrentSumVector(void)
{
    float32_t vector = g_inst_read_params.vector_sum_irms;
    /* Modify to get enough length for LCD if necessary */
    /* TBD */
    
    /* Display measured value */
    /* TBD */
    LCD_DisplayFloat(vector);
    
    /* Display "A" Sign */
    LCD_DisplaySpSign(S_T4);
    //LCD_DisplaySpSign(S_T5);
    
    /* Display "S" sign --> number "5" at digit 9 */
    LCD_DisplayDigit(9, 5); 

}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayVoltageTHD(EM_LINE line)
* Description  : Display THD value of EM
* Arguments    : EM_LINE line: Line want to display
* Output       : none
* Return Value : none
***********************************************************************************************************************/
static void EM_LCD_DisplayVoltageTHD(EM_LINE line)
{

    /* Modify to get enough length for LCD if necessary */
    /* TBD */

    /* Display measured value */
    /* TBD */
    LCD_DisplayFloat(g_inst_read_params.voltage_thd[line]);

    /* Display "Hd" at digit 8 and 9 */
    LCD_DisplayDigit(8, LCD_CHAR_H);
    LCD_DisplayDigit(9, LCD_CHAR_D);

    /* Display V Sign */
    LCD_DisplaySpSign(S_T2);
}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayVoltageTHD_Phase_R(void)
* Description  : Display THD of EM on phase R
* Arguments    : none
* Output       : none
* Return Value : none           
***********************************************************************************************************************/
static void EM_LCD_DisplayVoltageTHD_Phase_R(void)
{
    EM_LCD_DisplayVoltageTHD(LINE_PHASE_R);
    
    /* Display "R" sign */
    //LCD_DisplaySpSign(S_R);
	LCD_DisplayDigit(1,1);
}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayVoltageTHD_Phase_Y(void)
* Description  : Display THR of EM on phase Y
* Arguments    : none
* Output       : none
* Return Value : none           
***********************************************************************************************************************/
static void EM_LCD_DisplayVoltageTHD_Phase_Y(void)
{
    EM_LCD_DisplayVoltageTHD(LINE_PHASE_Y);
    
    /* Display "Y" sign */
    //LCD_DisplaySpSign(S_Y);
	LCD_DisplayDigit(1,2);
}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayVoltageTHD_Phase_B(void)
* Description  : Display THR on phase B of EM
* Arguments    : none
* Output       : none
* Return Value : none
***********************************************************************************************************************/
static void EM_LCD_DisplayVoltageTHD_Phase_B(void)
{
    EM_LCD_DisplayVoltageTHD(LINE_PHASE_B);
    
    /* Display "B" sign */
    //LCD_DisplaySpSign(S_B);
	LCD_DisplayDigit(1,3);
}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayCurrentTHD(EM_LINE line)
* Description  : Display THD of EM
* Arguments    : none
* Output       : none
* Return Value : none
***********************************************************************************************************************/
static void EM_LCD_DisplayCurrentTHD(EM_LINE line)
{
    /* Modify to get enough length for LCD if necessary */
    /* TBD */

    /* Display measured value */
    /* TBD */
    LCD_DisplayFloat(g_inst_read_params.current_thd[line]);

    /* Display "Hd" at digit 8 and 9 */
    LCD_DisplayDigit(8, LCD_CHAR_H);
    LCD_DisplayDigit(9, LCD_CHAR_D);

    /* Display "A" Sign */
    LCD_DisplaySpSign(S_T4);
    LCD_DisplaySpSign(S_T5);
}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayCurrentTHD_Phase_R(void)
* Description  : Display THD of EM on phase R
* Arguments    : none
* Output       : none
* Return Value : none           
***********************************************************************************************************************/
static void EM_LCD_DisplayCurrentTHD_Phase_R(void)
{
    EM_LCD_DisplayCurrentTHD(LINE_PHASE_R);
    
    /* Display "R" sign */
    //LCD_DisplaySpSign(S_R);
	LCD_DisplayDigit(1,1);
}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayCurrentTHD_Phase_Y(void)
* Description  : Display THR of EM on phase Y
* Arguments    : none
* Output       : none
* Return Value : none           
***********************************************************************************************************************/
static void EM_LCD_DisplayCurrentTHD_Phase_Y(void)
{
    EM_LCD_DisplayCurrentTHD(LINE_PHASE_Y);
    
    /* Display "Y" sign */
    //LCD_DisplaySpSign(S_Y);
	LCD_DisplayDigit(1,2);
}

/***********************************************************************************************************************
* Function Name: void EM_LCD_DisplayCurrentTHD_Phase_B(void)
* Description  : Display THR of EM on phase B
* Arguments    : none
* Output       : none
* Return Value : none
***********************************************************************************************************************/
static void EM_LCD_DisplayCurrentTHD_Phase_B(void)
{
    EM_LCD_DisplayCurrentTHD(LINE_PHASE_B);
    
    /* Display "B" sign */
    //LCD_DisplaySpSign(S_B);
	LCD_DisplayDigit(1,3);
}

/******************************************************************************
* Function Name: void EM_LCD_DisplayActMaxDemand(void)
* Description  : Display active max demand value
* Arguments    : none
* Output       : none
* Return Value : none
******************************************************************************/
static void EM_LCD_DisplayActMaxDemand(void)
{
    float32_t   actMD;
    uint8_t     return_status;

    actMD = R_MDM_GetActiveMaxDemand();

    /* Modify to get enough length for LCD if necessary */
    /* TBD */

    /* Display measured value */
    return_status = LCD_DisplayFloat(actMD);
    if (return_status == LCD_WRONG_INPUT_ARGUMENT)
    {
        /* TODO: notice input value is out of range */
    }

    /* Display "kW" sign */
    LCD_DisplaySpSign(S_T1);
    LCD_DisplaySpSign(S_T2);
    LCD_DisplaySpSign(S_T3);
    LCD_DisplaySpSign(S_T4);

    /* Display "MD" sign on LCD screen */
    LCD_DisplaySpSign(S_MD);
}

/******************************************************************************
* Function Name: void EM_LCD_DisplayCapacitiveReactiveMaxDemand(void)
* Description  : Display capacitive reactive max demand value
* Arguments    : none
* Output       : none
* Return Value : none
******************************************************************************/
void EM_LCD_DisplayCapacitiveReactiveMaxDemand(void)
{
    EM_LCD_DisplayInputReactiveMaxDemand(R_MDM_GetCapacitiveReactiveMaxDemand(), EM_LCD_CAPACITIVE_REACTIVE);
}

/******************************************************************************
* Function Name: void EM_LCD_DisplayInductiveReactiveMaxDemand(void)
* Description  : Display inductive reactive max demand value
* Arguments    : none
* Output       : none
* Return Value : none
******************************************************************************/
void EM_LCD_DisplayInductiveReactiveMaxDemand(void)
{
    EM_LCD_DisplayInputReactiveMaxDemand(R_MDM_GetInductiveReactiveMaxDemand(), EM_LCD_INDUCTIVE_REACTIVE);
}

/******************************************************************************
* Function Name: void EM_LCD_DisplayAppMaxDemand(void)
* Description  : Display apparent max demand value
* Arguments    : none
* Output       : none
* Return Value : none
******************************************************************************/
static void EM_LCD_DisplayAppMaxDemand(void)
{
    float32_t   appMD;
    uint8_t     return_status;

    appMD = R_MDM_GetApparentMaxDemand();

    /* Modify to get enough length for LCD if necessary */
    /* TBD */

    /* Display measured value */
    return_status = LCD_DisplayFloat(appMD);
    if (return_status == LCD_WRONG_INPUT_ARGUMENT)
    {
        /* TODO: notice input value is out of range */
    }

    /* Display "kVA" sign */
    LCD_DisplaySpSign(S_T1);
    LCD_DisplaySpSign(S_T2);
    LCD_DisplaySpSign(S_T4);
    LCD_DisplaySpSign(S_T5);

    /* Display "MD" sign on LCD screen */
    LCD_DisplaySpSign(S_MD);
}

/***********************************************************************************************************************
* Function Name: void LCD_SwitchAutoRoll(void)
* Description  : Toogle between using auto roll and not use auto roll
* Arguments    : none
* Output       : [g_auto_roll]: flag to determine if using auto roll or not
* Return Value : 
***********************************************************************************************************************/
void LCD_SwitchAutoRoll(void)
{
    /* Toogle auto scroll flag */
    g_auto_roll ^= 0x1;

}

/***********************************************************************************************************************
* Function Name: void LCD_ChangeNext(void)
* Description  : Switch to the next display value on EM
* Arguments    : none
* Output       : [g_display_pos] determine the order of displayed information
* Return Value : none
***********************************************************************************************************************/
void LCD_ChangeNext(void)
{
    /* Determine the next kind of value which is displayed on LCD */
    g_DispCounter++;
    if (fp_display[g_DispCounter] == NULL)
    {
        g_DispCounter = 0;
    }
    g_is_display_changed_next = 1;

}

/* Display some extra information */

/***********************************************************************************************************************
* Function Name: void LCD_DisplayTime(TIME_DATA_INFO time_info, uint8_t is_used_BCD)
* Description  : Display the set time of EM on LCD screen
* Arguments    : [time_info]struct which store the displayed time
*              : [is_used_BCD] = 1 : displayed time is on BCD type
*              :               = 0 : displayed time is on normal type
* Output       : [LCD_WRONG_INPUT_ARGUMENT] input argument error
*              : [LCD_INPUT_OK]             input argument ok
* Return Value : none           
***********************************************************************************************************************/
uint8_t LCD_DisplayTime(TIME_DATA_INFO time_info, uint8_t is_used_BCD)
{
    uint32_t    disp_data;
    uint8_t     is_zero_hour = 0;
    
    /* If input data is BCD type, convert it into normal type */
    if (is_used_BCD == 1)
    {
        time_info.sec  = WRP_EXT_Bcd2Dec(time_info.sec);
        time_info.min  = WRP_EXT_Bcd2Dec(time_info.min);
        time_info.hour = WRP_EXT_Bcd2Dec(time_info.hour);
    }
    
    /* Display time on LCD */
    /* Check hour value to guarantee it differs than 0 */
    if (time_info.hour <= 0)
    {
        is_zero_hour = 1;
        /* Add 1 to hour to compensate displayed value */
        time_info.hour = 1;
    }
    
    disp_data  = time_info.hour * (uint32_t)10000;
    disp_data += time_info.min * (uint32_t)100;
    disp_data += time_info.sec;

    LCD_DisplayIntWithPos(disp_data, 8);
    /* If the digit of hour less than 10 */
    if (is_zero_hour == 1)
    {
        LCD_DisplayDigit(4, 0); /* Display 0 at lower digit of hour value */
    }
    if (time_info.hour < 10)
    {
        LCD_DisplayDigit(3, 0); /* Display 0 at higher digit of hour value */
    }
    
    /* Clear the 8th digit on LCD */
    //LCD_ClearDigit(8);
    
    /* Diplay ":" between hour:min:sec */
    LCD_DisplaySpSign(S_D1);
    
    return LCD_INPUT_OK;
}

/***********************************************************************************************************************
* Function Name: void LCD_DisplayFloat(float32_t fnum)
* Description  : Display float number on LCD screen
* Arguments    : [fNum] displayed number
* Output       : none
* Return Value : LCD_INPUT_WRONG_ARGUMENT: length of integer part is more than 5
               : LCD_OK: length of input number is ok
***********************************************************************************************************************/
uint8_t LCD_DisplayFloat(float32_t fnum)
{
    /* Information of input number */
    uint8_t     i;          
    //uint8_t   sign;           /* Get sign of input number */
    //float         f_fra_part;     /* Integer and fraction part of fnum at float type */
    uint8_t     num_fra_digit;  /* Get the number of number on fractional part */
    
    /* Information for displaying process */
    uint8_t     disp_status = LCD_INPUT_OK;
    uint8_t     is_zero_point = 0;
    uint8_t     is_input_float_number = 0;  /* Check the input type */
    uint32_t    ref_value = 1;
    
    /* Check the validation of fnum */
    if (fnum > 9999999) /* Out of allowable range of float type
                         * supported by CA78K0 compiler */
    {
        disp_status = LCD_WRONG_INPUT_ARGUMENT;
    }
    
    /* Get the number of digit on fractional part */
    num_fra_digit = (LCD_LAST_POS_DIGIT - g_DecInfo.pos) + 1;
    
    /* Check if input number is flaoting type or integer type */
    //f_fra_part = fnum - (int32_t)fnum;
    is_input_float_number = 1;
    
    /* Check if the input number is on [0,1] */
    if ((fnum >= 0) && (fnum < 1))
    {
        is_zero_point = 1;
        /* Compensate data when displayed digit less than number of digit on fractional part */
        fnum += 1;          
    }
    if ((fnum > -1) && (fnum <0 ))
    {
        is_zero_point = 1;
        /* Compensate data when displayed digit less than number of digit on fractional part */
        fnum -= 1;          
    }
    
    /* Convert the floating type into integer type */
    if (is_input_float_number == 1)
    {
        for (i = 0; i < num_fra_digit; i++)
        {
            fnum *= 10;
            ref_value *= 10;
        }
    }
    
    /* The input number is less than 1/(10^(fra_digit)) */
//    if ((WRP_EXT_Absf(fnum) < (ref_value + 1)) && (is_zero_point == 1))
//    {
//        fnum = 100;
//    }
    
    /* Display integer number */
    disp_status = LCD_DisplayIntWithPos((int32_t)fnum, LCD_LAST_POS_DIGIT);

    /* Display 0 if input number in [0,1] */
    if (is_zero_point == 1)
    {
        LCD_DisplayDigit(g_DecInfo.pos - 1, 0);
    }
    
    /* Display decimal point */
    if (is_input_float_number == 1)
    {
        LCD_DisplaySpSign(g_DecInfo.sign);
    }

    return disp_status;
}

/***********************************************************************************************************************
* Function Name: void LCD_DisplayFloat3Digit(float32_t fnum)
* Description  : Display float number on LCD screen
* Arguments    : [fNum] displayed number
* Output       : none
* Return Value : LCD_INPUT_WRONG_ARGUMENT: length of integer part is more than 5
               : LCD_OK: length of input number is ok
***********************************************************************************************************************/
uint8_t LCD_DisplayFloat3Digit(float32_t fnum)
{
    /* Information of input number */
    uint8_t     i;
    //uint8_t   sign;           /* Get sign of input number */
    //float         f_fra_part;     /* Integer and fraction part of fnum at float type */
    uint8_t     num_fra_digit;  /* Get the number of number on fractional part */
    
    /* Information for displaying process */
    uint8_t     disp_status = LCD_INPUT_OK;
    uint8_t     is_zero_point = 0;
    uint8_t     is_input_float_number = 0;  /* Check the input type */
    uint32_t    ref_value = 1;
    
    /* Check the validation of fnum */
    if (WRP_EXT_Absf(fnum) < 0.001)
    {
        fnum = 0;
    }
    if (fnum >= 9999999) /* Out of allowable range of float type
                         * supported by CA78K0 compiler */
    {
        disp_status = LCD_WRONG_INPUT_ARGUMENT;
        fnum = fnum/1000;
    }
    
    /* Get the number of digit on fractional part */    
    num_fra_digit = (LCD_LAST_POS_DIGIT - g_DecInfo1.pos) + 1;
    
    /* Check if input number is flaoting type or integer type */
    //f_fra_part = fnum - (int32_t)fnum;
    is_input_float_number = 1;
    
    /* Check if the input number is on [0,1] */
    if ((fnum >= 0) && (fnum < 1))
    {
        is_zero_point = 1;
        /* Compensate data when displayed digit less than number of digit on fractional part */
        fnum += 1;          
    }
    if ((fnum > -1) && (fnum <0 ))
    {
        is_zero_point = 1;
        /* Compensate data when displayed digit less than number of digit on fractional part */
        fnum -= 1;          
    }
    
    /* Convert the floating type into integer type */
    if (is_input_float_number == 1)
    {
        for (i = 0; i < num_fra_digit; i++)
        {
            fnum *= 10;
            ref_value *= 10;
        }
    }   
    
    /* Display integer number */
    disp_status = LCD_DisplayIntWithPos((int32_t)fnum, LCD_LAST_POS_DIGIT);

    /* Display 0 if input number in [0,1] */
    if (is_zero_point == 1)
    {
        LCD_DisplayDigit(g_DecInfo1.pos - 1, 0);
    }
    
    /* Display decimal point */
    if (is_input_float_number == 1)
    {
        LCD_DisplaySpSign(g_DecInfo1.sign);
    }

    return disp_status;
}

/***********************************************************************************************************************
* Function Name: uint8_t LCD_DisplayIntWithPos(long lNum, uint8_t position)
* Description  : Display integer number on LCD at specified position
* Arguments    : 
*              : 
* Output       : 
* Return Value : LCD_WRONG_INPUT_ARGUMENT: input wrong argument
*              : LCD_INPUT_OK: input OK argument
***********************************************************************************************************************/
uint8_t LCD_DisplayIntWithPos(long lNum, int8_t position)
{
    int8_t pos = position;
    int8_t sign;            /* store the sign of value: positive, negative */
    uint8_t is_disp_error = LCD_INPUT_OK;
    
    /* check pos */
    if ((pos > LCD_LAST_POS_DIGIT) || (pos < LCD_FIRST_POS_DIGIT))
    {
        return LCD_WRONG_INPUT_ARGUMENT;
    }
    
    /* get the sign of value */
    sign = (lNum < 0) ? -1 : 1;
    lNum *= sign;               /* Get absolusted value of fNum for displaying */
    
    /* Clear all decimal point */
//    LCD_ClearSpSign(S_D2);
//    LCD_ClearSpSign(S_D4);
//    LCD_ClearSpSign(S_D5);
//    LCD_ClearSpSign(S_D6);
    
    /* display all digit */
    do
    {
        LCD_DisplayDigit(pos--, (uint8_t)(lNum % 10));
        lNum /= 10;
    } while (lNum && pos >= LCD_FIRST_POS_DIGIT);
    
    if ((lNum != 0) && (pos < LCD_FIRST_POS_DIGIT)) /* overflow */
    {
        is_disp_error = LCD_WRONG_INPUT_ARGUMENT;
    }
    
    /* display the sign if there are some remain digit in the main region */
    if (sign < 0)
    {
        if (pos >= LCD_FIRST_POS_DIGIT)
        {
            LCD_DisplayDigit(pos--, LCD_MINUS_SIGN);
        }
        else
        {
            is_disp_error = LCD_WRONG_INPUT_ARGUMENT;
        }
    }
    
    /* Clear all other digit at left hand */
    while (pos >= LCD_FIRST_POS_DIGIT)
    {
        LCD_ClearDigit(pos--);
    }

    return is_disp_error;
}

/******************************************************************************
* Function Name: void EM_LCD_DisplayPOR(void)
* Description  : Display the sign to mark as PORSR
* Arguments    : None
* Return Value : NOne
******************************************************************************/
void EM_LCD_DisplayPOR(void)
{
    g_is_por = 0x01;
}
