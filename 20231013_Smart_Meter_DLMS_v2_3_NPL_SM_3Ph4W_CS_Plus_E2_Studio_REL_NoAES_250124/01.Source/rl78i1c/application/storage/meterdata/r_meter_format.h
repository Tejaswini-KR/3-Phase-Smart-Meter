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
* File Name    : r_meter_format.h
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : CCRL
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : Storage Format Header file

* Note         : NEED TO CHANGE THIS FILE WHEN
*              :   . EM CORE TYPE DEFINITION IS CHANGED, OR
*              :   . EEPROM START ADDRESS IS CHANGED
* Caution      : DATA ALIGNMENT
*              :    DATA ALIGNMENT ON THIS FORMAT IS 2-BYTES ALIGNMENT, EVEN ADDRESS.
*              :    PLEASE DON'T CHANGE TO OTHER ALIGNMENT SETTING.
*              :    WHEN CHANGE THE DATA ALIGNMENT SETTING, IT WILL DAMAGE THE FORMAT
*              :    ON EEPROM
*              :
*              : BIT FIELD FORMAT
*              :    BIT FIELD FORMAT IS FROM LSB FIRST
*              :    PLEASE DON'T CHANGE THIS SETTING ON THE COMPILE OPTION (IF SUPPORTED)

***********************************************************************************************************************/

#ifndef _STORAGE_FORMAT_H
#define _STORAGE_FORMAT_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "typedef.h"        /* GSCE Standard Typedef */

/* Middleware */
#include "em_type.h"        /* EM Core Type Definitions */
#include "em_constraint.h"

/* Application */
#include "eeprom.h"         /* EEPROM MW */
#include "r_tariff.h"
#include "r_max_demand.h"
#include "event.h"
#include "r_scheduler.h"
#include "inst_read.h"
#include "r_activity_cal.h"

/******************************************************************************
Macro definitions for Typedef
******************************************************************************/
#define SUPPORT_UNIT_CODE_LEN               (20)
#define SUPPORT_FW_VER_LEN                  (11)
#define SUPPORT_METER_TYPE_LEN              (4)

/* User define */
#define SUPPORT_DEVICEID_LEN (11)
#define BLOCKLOAD_PARTITION (3500) //(95000)
#define DAILY_PARTITION (1000)
#define BILLING_PARTITION (4000)


/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/*====================================================================================================================*/
/* EEPROM Information */
#define STORAGE_EEPROM_START_ADDR 						EPR_DEVICE_START_ADDR   /* EEPROM Start address */
#define STORAGE_EEPROM_SIZE 							EPR_DEVICE_SIZE              /* EEPROM Size */
#define STORAGE_EEPROM_PAGESIZE 						EPR_DEVICE_PAGESIZE      /* EEPROM Page Size */


/*====================================================================================================================*/

#define STORAGE_EEPROM_SUB_MODULE_EM_CORE       (1)
#define STORAGE_EEPROM_SUB_MODULE_GLOBAL        (1)
#define STORAGE_EEPROM_SUB_MODULE_COMMON        (1)
#define STORAGE_EEPROM_SUB_MODULE_ENERGY        (1)
#define STORAGE_EEPROM_SUB_MODULE_ENERGY_MDM    (1)
#define STORAGE_EEPROM_SUB_MODULE_ENERGY_TARIFF (1)
#define STORAGE_EEPROM_SUB_MODULE_SCHEDULER     (1)
#define STORAGE_EEPROM_SUB_MODULE_EVENT_LOG     (1)
#define STORAGE_EEPROM_SUB_MODULE_BLOCKLOAD     (1)
#define STORAGE_EEPROM_SUB_MODULE_DAILYLOAD     (1)
#define STORAGE_EEPROM_SUB_MODULE_BILLING       (1)	
#define STORAGE_EEPROM_SUB_MODULE_CAL           (1)

#if(defined( R_LOAD_CONTROL_ENABLE ) && R_LOAD_CONTROL_ENABLE == TRUE)
    #define STORAGE_EEPROM_SUB_MODULE_LOAD_CTRL     (1)	
#else
    #define STORAGE_EEPROM_SUB_MODULE_LOAD_CTRL     (0)	
#endif

/*****************************************
* Sub module: EM_CORE
******************************************/
#if (STORAGE_EEPROM_SUB_MODULE_EM_CORE == 1)

    /* Partition */
    #define STORAGE_EEPROM_EM_CORE_PARTITION_ADDR (STORAGE_EEPROM_START_ADDR + 0)
    #define STORAGE_EEPROM_EM_CORE_PARTITION_SIZE (sizeof(uint8_t) * 256  )


	/* Sub module EM_CORE last address */
    #define STORAGE_EEPROM_EM_CORE_LAST_ADDR (STORAGE_EEPROM_EM_CORE_PARTITION_ADDR + STORAGE_EEPROM_EM_CORE_PARTITION_SIZE)


#endif /* EM_CORE */


/*****************************************
* Sub module: Global
******************************************/
#if (STORAGE_EEPROM_SUB_MODULE_GLOBAL == 1)

    /* Header Code */
    #define STORAGE_EEPROM_GLOBAL_HEADER_CODE_ADDR (STORAGE_EEPROM_EM_CORE_LAST_ADDR)
    #define STORAGE_EEPROM_GLOBAL_HEADER_CODE_SIZE (sizeof(uint32_t) )

    /*  Sub module Global padding */
    #define STORAGE_EEPROM_GLOBAL_PADDING_ADDR (STORAGE_EEPROM_GLOBAL_HEADER_CODE_ADDR + STORAGE_EEPROM_GLOBAL_HEADER_CODE_SIZE)
    #define STORAGE_EEPROM_GLOBAL_PADDING_SIZE (10)

	/* Sub module Global last address */
    #define STORAGE_EEPROM_GLOBAL_LAST_ADDR (STORAGE_EEPROM_GLOBAL_PADDING_ADDR + STORAGE_EEPROM_GLOBAL_PADDING_SIZE)

    #undef STORAGE_EEPROM_METER_FORMAT_LAST_ADDR
    #define STORAGE_EEPROM_METER_FORMAT_LAST_ADDR	(STORAGE_EEPROM_GLOBAL_LAST_ADDR)

#endif /* Global */


/*****************************************
* Sub module: Common
******************************************/
#if (STORAGE_EEPROM_SUB_MODULE_COMMON == 1)

    /* Rtc */
    #define STORAGE_EEPROM_COMMON_RTC_ADDR (STORAGE_EEPROM_GLOBAL_LAST_ADDR)
    #define STORAGE_EEPROM_COMMON_RTC_SIZE (sizeof(rtc_counter_value_t))
    /* Snapshot_value */
    #define STORAGE_EEPROM_COMMON_SNAPSHOT_VALUE_ADDR (STORAGE_EEPROM_COMMON_RTC_ADDR + STORAGE_EEPROM_COMMON_RTC_SIZE)
    #define STORAGE_EEPROM_COMMON_SNAPSHOT_VALUE_SIZE (sizeof(EM_INST_READ_PARAMS) * 2 )

	/* Sub module Common last address */
    #define STORAGE_EEPROM_COMMON_LAST_ADDR (STORAGE_EEPROM_COMMON_SNAPSHOT_VALUE_ADDR + STORAGE_EEPROM_COMMON_SNAPSHOT_VALUE_SIZE)

    #undef STORAGE_EEPROM_METER_FORMAT_LAST_ADDR
    #define STORAGE_EEPROM_METER_FORMAT_LAST_ADDR	(STORAGE_EEPROM_COMMON_LAST_ADDR)

#endif /* Common */


/*****************************************
* Sub module: Energy_MDM
******************************************/
#if (STORAGE_EEPROM_SUB_MODULE_ENERGY_MDM == 1)

    /* State */
    #define STORAGE_EEPROM_ENERGY_MDM_STATE_ADDR (STORAGE_EEPROM_COMMON_LAST_ADDR)
    #define STORAGE_EEPROM_ENERGY_MDM_STATE_SIZE (sizeof(r_mdm_t))
    /* Moving Average buffer */
    #define STORAGE_EEPROM_ENERGY_MDM_MOVING_AVERAGE_BUFFER_ADDR (STORAGE_EEPROM_ENERGY_MDM_STATE_ADDR + STORAGE_EEPROM_ENERGY_MDM_STATE_SIZE)
    #define STORAGE_EEPROM_ENERGY_MDM_MOVING_AVERAGE_BUFFER_SIZE (sizeof(r_mdm_counter_t) * 15 )
    
    /* Current max value for energy total */
    #define STORAGE_EEPROM_ENERGY_MDM_MAX_VALUE_ADDR (STORAGE_EEPROM_ENERGY_MDM_MOVING_AVERAGE_BUFFER_ADDR + STORAGE_EEPROM_ENERGY_MDM_MOVING_AVERAGE_BUFFER_SIZE)
    #define STORAGE_EEPROM_ENERGY_MDM_MAX_VALUE_SIZE (sizeof(r_mdm_counter_t))
	/* Max active value capture time for energy total */
    #define STORAGE_EEPROM_ENERGY_MDM_MAX_ACTIVE_CAPTURE_TIME_ADDR (STORAGE_EEPROM_ENERGY_MDM_MAX_VALUE_ADDR + STORAGE_EEPROM_ENERGY_MDM_MAX_VALUE_SIZE)
    #define STORAGE_EEPROM_ENERGY_MDM_MAX_ACTIVE_CAPTURE_TIME_SIZE (sizeof(rtc_counter_value_t))
	/* Max apparent value capture time for energy total */
    #define STORAGE_EEPROM_ENERGY_MDM_MAX_APPARENT_CAPTURE_TIME_ADDR (STORAGE_EEPROM_ENERGY_MDM_MAX_ACTIVE_CAPTURE_TIME_ADDR + STORAGE_EEPROM_ENERGY_MDM_MAX_ACTIVE_CAPTURE_TIME_SIZE)
    #define STORAGE_EEPROM_ENERGY_MDM_MAX_APPARENT_CAPTURE_TIME_SIZE (sizeof(rtc_counter_value_t))
	
    /* Current max value for each timezone */
    #define STORAGE_EEPROM_ENERGY_MDM_MAX_VALUE_TZ_ADDR (STORAGE_EEPROM_ENERGY_MDM_MAX_APPARENT_CAPTURE_TIME_ADDR + STORAGE_EEPROM_ENERGY_MDM_MAX_APPARENT_CAPTURE_TIME_SIZE)
    #define STORAGE_EEPROM_ENERGY_MDM_MAX_VALUE_TZ_SIZE (sizeof(r_mdm_counter_t) * 8 )
    /* Max active value capture time for each timezone*/
    #define STORAGE_EEPROM_ENERGY_MDM_MAX_ACTIVE_TZ_CAPTURE_TIME_ADDR (STORAGE_EEPROM_ENERGY_MDM_MAX_VALUE_TZ_ADDR + STORAGE_EEPROM_ENERGY_MDM_MAX_VALUE_TZ_SIZE)
    #define STORAGE_EEPROM_ENERGY_MDM_MAX_ACTIVE_TZ_CAPTURE_TIME_SIZE (sizeof(rtc_counter_value_t) * 8 )
	/* Max apparent value capture time for each timezone*/
    #define STORAGE_EEPROM_ENERGY_MDM_MAX_APPARENT_TZ_CAPTURE_TIME_ADDR (STORAGE_EEPROM_ENERGY_MDM_MAX_ACTIVE_TZ_CAPTURE_TIME_ADDR + STORAGE_EEPROM_ENERGY_MDM_MAX_ACTIVE_TZ_CAPTURE_TIME_SIZE)
    #define STORAGE_EEPROM_ENERGY_MDM_MAX_APPARENT_TZ_CAPTURE_TIME_SIZE (sizeof(rtc_counter_value_t) * 8 )
	
	/*  Sub module Energy_MDM padding */
    #define STORAGE_EEPROM_ENERGY_MDM_PADDING_ADDR (STORAGE_EEPROM_ENERGY_MDM_MAX_APPARENT_TZ_CAPTURE_TIME_ADDR + STORAGE_EEPROM_ENERGY_MDM_MAX_APPARENT_TZ_CAPTURE_TIME_SIZE)
    #define STORAGE_EEPROM_ENERGY_MDM_PADDING_SIZE (10)

	/* Sub module Energy_MDM last address */
    #define STORAGE_EEPROM_ENERGY_MDM_LAST_ADDR (STORAGE_EEPROM_ENERGY_MDM_PADDING_ADDR + STORAGE_EEPROM_ENERGY_MDM_PADDING_SIZE)

    #undef STORAGE_EEPROM_METER_FORMAT_LAST_ADDR
    #define STORAGE_EEPROM_METER_FORMAT_LAST_ADDR	(STORAGE_EEPROM_ENERGY_MDM_LAST_ADDR)

#endif /* Energy_MDM */


/*****************************************
* Sub module: Energy_Tariff
******************************************/
#if (STORAGE_EEPROM_SUB_MODULE_ENERGY_TARIFF == 1)

    /* State */
    #define STORAGE_EEPROM_ENERGY_TARIFF_STATE_ADDR (STORAGE_EEPROM_ENERGY_MDM_LAST_ADDR)
    #define STORAGE_EEPROM_ENERGY_TARIFF_STATE_SIZE (sizeof(r_tariff_t))
    /* Tz */
    #define STORAGE_EEPROM_ENERGY_TARIFF_TZ_ADDR (STORAGE_EEPROM_ENERGY_TARIFF_STATE_ADDR + STORAGE_EEPROM_ENERGY_TARIFF_STATE_SIZE)
    #define STORAGE_EEPROM_ENERGY_TARIFF_TZ_SIZE (sizeof(r_tariff_counter_t) * 16 )
    /* Lookup Timeslot-tariff_number */
    #define STORAGE_EEPROM_ENERGY_TARIFF_LOOKUP_TIMESLOT_TARIFF_NUMBER_ADDR (STORAGE_EEPROM_ENERGY_TARIFF_TZ_ADDR + STORAGE_EEPROM_ENERGY_TARIFF_TZ_SIZE)
    #define STORAGE_EEPROM_ENERGY_TARIFF_LOOKUP_TIMESLOT_TARIFF_NUMBER_SIZE (sizeof(uint8_t) * 16)
    /*  Sub module Energy_Tariff padding */
    #define STORAGE_EEPROM_ENERGY_TARIFF_PADDING_ADDR (STORAGE_EEPROM_ENERGY_TARIFF_LOOKUP_TIMESLOT_TARIFF_NUMBER_ADDR + STORAGE_EEPROM_ENERGY_TARIFF_LOOKUP_TIMESLOT_TARIFF_NUMBER_SIZE)
    #define STORAGE_EEPROM_ENERGY_TARIFF_PADDING_SIZE (10)

	/* Sub module Energy_Tariff last address */
    #define STORAGE_EEPROM_ENERGY_TARIFF_LAST_ADDR (STORAGE_EEPROM_ENERGY_TARIFF_PADDING_ADDR + STORAGE_EEPROM_ENERGY_TARIFF_PADDING_SIZE)

    #undef STORAGE_EEPROM_METER_FORMAT_LAST_ADDR
    #define STORAGE_EEPROM_METER_FORMAT_LAST_ADDR	(STORAGE_EEPROM_ENERGY_TARIFF_LAST_ADDR)

#endif /* Energy_Tariff */


/*****************************************
* Sub module: Scheduler
******************************************/
#if (STORAGE_EEPROM_SUB_MODULE_SCHEDULER == 1)

    /* Data */
    #define STORAGE_EEPROM_SCHEDULER_DATA_ADDR (STORAGE_EEPROM_ENERGY_TARIFF_LAST_ADDR)
    #define STORAGE_EEPROM_SCHEDULER_DATA_SIZE (sizeof(scheduler_storage_t) * MAX_SCHEDULER_NUMBER)
    /* SAS date time */
    #define STORAGE_EEPROM_SCHEDULER_SAS_DATE_TIME_ADDR (STORAGE_EEPROM_SCHEDULER_DATA_ADDR + STORAGE_EEPROM_SCHEDULER_DATA_SIZE)
    #define STORAGE_EEPROM_SCHEDULER_SAS_DATE_TIME_SIZE (sizeof(r_scheduler_datetime_t) * SCHEDULE_EXECUTION_TIME_MAX_SUPPORT)
    /* SAS execution flag */
    #define STORAGE_EEPROM_SCHEDULER_SAS_EXECUTION_FLAG_ADDR (STORAGE_EEPROM_SCHEDULER_SAS_DATE_TIME_ADDR + STORAGE_EEPROM_SCHEDULER_SAS_DATE_TIME_SIZE)
    #define STORAGE_EEPROM_SCHEDULER_SAS_EXECUTION_FLAG_SIZE (sizeof(uint16_t) * MAX_SCHEDULER_NUMBER)
    /* Demand Integration Period */
    #define STORAGE_EEPROM_SCHEDULER_DEMAND_INTEGRATION_PERIOD_ADDR (STORAGE_EEPROM_SCHEDULER_SAS_EXECUTION_FLAG_ADDR + STORAGE_EEPROM_SCHEDULER_SAS_EXECUTION_FLAG_SIZE)
    #define STORAGE_EEPROM_SCHEDULER_DEMAND_INTEGRATION_PERIOD_SIZE (sizeof(uint16_t))
    /* Demand Number of Period */
    #define STORAGE_EEPROM_SCHEDULER_DEMAND_NUMBER_OF_PERIOD_ADDR (STORAGE_EEPROM_SCHEDULER_DEMAND_INTEGRATION_PERIOD_ADDR + STORAGE_EEPROM_SCHEDULER_DEMAND_INTEGRATION_PERIOD_SIZE)
    #define STORAGE_EEPROM_SCHEDULER_DEMAND_NUMBER_OF_PERIOD_SIZE (sizeof(uint16_t))
    /*  Sub module Scheduler padding */
    #define STORAGE_EEPROM_SCHEDULER_PADDING_ADDR (STORAGE_EEPROM_SCHEDULER_DEMAND_NUMBER_OF_PERIOD_ADDR + STORAGE_EEPROM_SCHEDULER_DEMAND_NUMBER_OF_PERIOD_SIZE)
    #define STORAGE_EEPROM_SCHEDULER_PADDING_SIZE (10)

	/* Sub module Scheduler last address */
    #define STORAGE_EEPROM_SCHEDULER_LAST_ADDR (STORAGE_EEPROM_SCHEDULER_PADDING_ADDR + STORAGE_EEPROM_SCHEDULER_PADDING_SIZE)

    #undef STORAGE_EEPROM_METER_FORMAT_LAST_ADDR
    #define STORAGE_EEPROM_METER_FORMAT_LAST_ADDR	(STORAGE_EEPROM_SCHEDULER_LAST_ADDR)

#endif /* Scheduler */


/*****************************************
* Sub module: Event_Log
******************************************/
#if (STORAGE_EEPROM_SUB_MODULE_EVENT_LOG == 1)

    /* Header code */
    #define STORAGE_EEPROM_EVENT_LOG_HEADER_CODE_ADDR (STORAGE_EEPROM_SCHEDULER_LAST_ADDR)
    #define STORAGE_EEPROM_EVENT_LOG_HEADER_CODE_SIZE (sizeof(uint32_t) )

    /* Event State */
    #define STORAGE_EEPROM_EVENT_LOG_EVENT_STATE_ADDR (STORAGE_EEPROM_EVENT_LOG_HEADER_CODE_ADDR + STORAGE_EEPROM_EVENT_LOG_HEADER_CODE_SIZE)
    #define STORAGE_EEPROM_EVENT_LOG_EVENT_STATE_SIZE (sizeof(EVENT_INFO))
    /* Tamper Counter */
    #define STORAGE_EEPROM_EVENT_LOG_TAMPER_COUNTER_ADDR (STORAGE_EEPROM_EVENT_LOG_EVENT_STATE_ADDR + STORAGE_EEPROM_EVENT_LOG_EVENT_STATE_SIZE)
    #define STORAGE_EEPROM_EVENT_LOG_TAMPER_COUNTER_SIZE (sizeof(uint32_t))
    /* Table info */
    #define STORAGE_EEPROM_EVENT_LOG_TABLE_INFO_ADDR (STORAGE_EEPROM_EVENT_LOG_TAMPER_COUNTER_ADDR + STORAGE_EEPROM_EVENT_LOG_TAMPER_COUNTER_SIZE)
    #define STORAGE_EEPROM_EVENT_LOG_TABLE_INFO_SIZE (sizeof(EventTableHeader_t) * 7 )
    /* Voltage */
    #define STORAGE_EEPROM_EVENT_LOG_VOLTAGE_ADDR (STORAGE_EEPROM_EVENT_LOG_TABLE_INFO_ADDR + STORAGE_EEPROM_EVENT_LOG_TABLE_INFO_SIZE)
    #define STORAGE_EEPROM_EVENT_LOG_VOLTAGE_SIZE (sizeof(EVENT_PARAMS_T) * VOLTAGE_EVENTS_MAX_ENTRIES)
    /* Current */
    #define STORAGE_EEPROM_EVENT_LOG_CURRENT_ADDR (STORAGE_EEPROM_EVENT_LOG_VOLTAGE_ADDR + STORAGE_EEPROM_EVENT_LOG_VOLTAGE_SIZE)
    #define STORAGE_EEPROM_EVENT_LOG_CURRENT_SIZE (sizeof(EVENT_PARAMS_T) * CURRENT_EVENTS_MAX_ENTRIES)
    /* Power */
    #define STORAGE_EEPROM_EVENT_LOG_POWER_ADDR (STORAGE_EEPROM_EVENT_LOG_CURRENT_ADDR + STORAGE_EEPROM_EVENT_LOG_CURRENT_SIZE)
    #define STORAGE_EEPROM_EVENT_LOG_POWER_SIZE (sizeof(EVENT_PARAMS_SHORT_T) * POWER_EVENTS_MAX_ENTRIES)
    /* Transaction */
    #define STORAGE_EEPROM_EVENT_LOG_TRANSACTION_ADDR (STORAGE_EEPROM_EVENT_LOG_POWER_ADDR + STORAGE_EEPROM_EVENT_LOG_POWER_SIZE)
    #define STORAGE_EEPROM_EVENT_LOG_TRANSACTION_SIZE (sizeof(EVENT_PARAMS_SHORT_T) * TRANS_EVENTS_MAX_ENTRIES)
    /* Other */
    #define STORAGE_EEPROM_EVENT_LOG_OTHER_ADDR (STORAGE_EEPROM_EVENT_LOG_TRANSACTION_ADDR + STORAGE_EEPROM_EVENT_LOG_TRANSACTION_SIZE)
    #define STORAGE_EEPROM_EVENT_LOG_OTHER_SIZE (sizeof(EVENT_PARAMS_T) * OTHER_EVENTS_MAX_ENTRIES)
    /* Nonrollover */
    #define STORAGE_EEPROM_EVENT_LOG_NONROLLOVER_ADDR (STORAGE_EEPROM_EVENT_LOG_OTHER_ADDR + STORAGE_EEPROM_EVENT_LOG_OTHER_SIZE)
    #define STORAGE_EEPROM_EVENT_LOG_NONROLLOVER_SIZE (sizeof(EVENT_PARAMS_SHORT_T) * NON_ROLLOVER_EVENTS_MAX_ENTRIES)
    /* Control */
    #define STORAGE_EEPROM_EVENT_LOG_CONTROL_ADDR (STORAGE_EEPROM_EVENT_LOG_NONROLLOVER_ADDR + STORAGE_EEPROM_EVENT_LOG_NONROLLOVER_SIZE)
    #define STORAGE_EEPROM_EVENT_LOG_CONTROL_SIZE (sizeof(EVENT_PARAMS_SHORT_T) * CONTROL_EVENTS_MAX_ENTRIES)
    /*  Sub module Event_Log padding */
    #define STORAGE_EEPROM_EVENT_LOG_PADDING_ADDR (STORAGE_EEPROM_EVENT_LOG_CONTROL_ADDR + STORAGE_EEPROM_EVENT_LOG_CONTROL_SIZE)
    #define STORAGE_EEPROM_EVENT_LOG_PADDING_SIZE (10)

	/* Sub module Event_Log last address */
    #define STORAGE_EEPROM_EVENT_LOG_LAST_ADDR (STORAGE_EEPROM_EVENT_LOG_PADDING_ADDR + STORAGE_EEPROM_EVENT_LOG_PADDING_SIZE)

    #undef STORAGE_EEPROM_METER_FORMAT_LAST_ADDR
    #define STORAGE_EEPROM_METER_FORMAT_LAST_ADDR	(STORAGE_EEPROM_EVENT_LOG_LAST_ADDR)

#endif /* Event_Log */


/*****************************************
* Sub module: Blockload
******************************************/
#if (STORAGE_EEPROM_SUB_MODULE_BLOCKLOAD == 1)

    /* Partition */
    #define STORAGE_EEPROM_BLOCKLOAD_PARTITION_ADDR (STORAGE_EEPROM_EVENT_LOG_LAST_ADDR)
    #define STORAGE_EEPROM_BLOCKLOAD_PARTITION_SIZE (sizeof(uint8_t) * BLOCKLOAD_PARTITION)

	/* Sub module Blockload last address */
    #define STORAGE_EEPROM_BLOCKLOAD_LAST_ADDR (STORAGE_EEPROM_BLOCKLOAD_PARTITION_ADDR + STORAGE_EEPROM_BLOCKLOAD_PARTITION_SIZE)

    #undef STORAGE_EEPROM_METER_FORMAT_LAST_ADDR
    #define STORAGE_EEPROM_METER_FORMAT_LAST_ADDR	(STORAGE_EEPROM_BLOCKLOAD_LAST_ADDR)

#endif /* Blockload */


/*****************************************
* Sub module: Dailyload
******************************************/
#if (STORAGE_EEPROM_SUB_MODULE_DAILYLOAD == 1)

    /* Partition */
    #define STORAGE_EEPROM_DAILYLOAD_PARTITION_ADDR (STORAGE_EEPROM_BLOCKLOAD_LAST_ADDR)
    #define STORAGE_EEPROM_DAILYLOAD_PARTITION_SIZE (sizeof(uint8_t) * DAILY_PARTITION)
    /*  Sub module Dailyload padding */
    #define STORAGE_EEPROM_DAILYLOAD_PADDING_ADDR (STORAGE_EEPROM_DAILYLOAD_PARTITION_ADDR + STORAGE_EEPROM_DAILYLOAD_PARTITION_SIZE)
    #define STORAGE_EEPROM_DAILYLOAD_PADDING_SIZE (10)

	/* Sub module Dailyload last address */
    #define STORAGE_EEPROM_DAILYLOAD_LAST_ADDR (STORAGE_EEPROM_DAILYLOAD_PADDING_ADDR + STORAGE_EEPROM_DAILYLOAD_PADDING_SIZE)

    #undef STORAGE_EEPROM_METER_FORMAT_LAST_ADDR
    #define STORAGE_EEPROM_METER_FORMAT_LAST_ADDR	(STORAGE_EEPROM_DAILYLOAD_LAST_ADDR)

#endif /* Dailyload */


/*****************************************
* Sub module: Billing
******************************************/
#if (STORAGE_EEPROM_SUB_MODULE_BILLING == 1)

    /* Partition */
    #define STORAGE_EEPROM_BILLING_PARTITION_ADDR (STORAGE_EEPROM_DAILYLOAD_LAST_ADDR)
    #define STORAGE_EEPROM_BILLING_PARTITION_SIZE (sizeof(uint8_t) * BILLING_PARTITION)
    /*  Sub module Billing padding */
    #define STORAGE_EEPROM_BILLING_PADDING_ADDR (STORAGE_EEPROM_BILLING_PARTITION_ADDR + STORAGE_EEPROM_BILLING_PARTITION_SIZE)
    #define STORAGE_EEPROM_BILLING_PADDING_SIZE (10)

	/* Sub module Billing last address */
    #define STORAGE_EEPROM_BILLING_LAST_ADDR (STORAGE_EEPROM_BILLING_PADDING_ADDR + STORAGE_EEPROM_BILLING_PADDING_SIZE)

    #undef STORAGE_EEPROM_METER_FORMAT_LAST_ADDR
    #define STORAGE_EEPROM_METER_FORMAT_LAST_ADDR	(STORAGE_EEPROM_BILLING_LAST_ADDR)

#endif /* Billing */


/*****************************************
* Sub module: Cal
******************************************/
#if (STORAGE_EEPROM_SUB_MODULE_CAL == 1)

    /* Name_active */
    #define STORAGE_EEPROM_CAL_NAME_ACTIVE_ADDR (STORAGE_EEPROM_BILLING_LAST_ADDR)
    #define STORAGE_EEPROM_CAL_NAME_ACTIVE_SIZE (sizeof(r_act_cal_name_t))
    /* Season_active */
    #define STORAGE_EEPROM_CAL_SEASON_ACTIVE_ADDR (STORAGE_EEPROM_CAL_NAME_ACTIVE_ADDR + STORAGE_EEPROM_CAL_NAME_ACTIVE_SIZE)
    #define STORAGE_EEPROM_CAL_SEASON_ACTIVE_SIZE (sizeof(r_act_cal_season_profile_t))
    /* Week_active */
    #define STORAGE_EEPROM_CAL_WEEK_ACTIVE_ADDR (STORAGE_EEPROM_CAL_SEASON_ACTIVE_ADDR + STORAGE_EEPROM_CAL_SEASON_ACTIVE_SIZE)
    #define STORAGE_EEPROM_CAL_WEEK_ACTIVE_SIZE (sizeof(r_act_cal_week_profile_t))
    /* Day_active */
    #define STORAGE_EEPROM_CAL_DAY_ACTIVE_ADDR (STORAGE_EEPROM_CAL_WEEK_ACTIVE_ADDR + STORAGE_EEPROM_CAL_WEEK_ACTIVE_SIZE)
    #define STORAGE_EEPROM_CAL_DAY_ACTIVE_SIZE (sizeof(r_act_cal_day_profile_t))
    /* Name_passive */
    #define STORAGE_EEPROM_CAL_NAME_PASSIVE_ADDR (STORAGE_EEPROM_CAL_DAY_ACTIVE_ADDR + STORAGE_EEPROM_CAL_DAY_ACTIVE_SIZE)
    #define STORAGE_EEPROM_CAL_NAME_PASSIVE_SIZE (sizeof(r_act_cal_name_t))
    /* season_passive */
    #define STORAGE_EEPROM_CAL_SEASON_PASSIVE_ADDR (STORAGE_EEPROM_CAL_NAME_PASSIVE_ADDR + STORAGE_EEPROM_CAL_NAME_PASSIVE_SIZE)
    #define STORAGE_EEPROM_CAL_SEASON_PASSIVE_SIZE (sizeof(r_act_cal_season_profile_t))
    /* week_passive */
    #define STORAGE_EEPROM_CAL_WEEK_PASSIVE_ADDR (STORAGE_EEPROM_CAL_SEASON_PASSIVE_ADDR + STORAGE_EEPROM_CAL_SEASON_PASSIVE_SIZE)
    #define STORAGE_EEPROM_CAL_WEEK_PASSIVE_SIZE (sizeof(r_act_cal_week_profile_t))
    /* day_passive */
    #define STORAGE_EEPROM_CAL_DAY_PASSIVE_ADDR (STORAGE_EEPROM_CAL_WEEK_PASSIVE_ADDR + STORAGE_EEPROM_CAL_WEEK_PASSIVE_SIZE)
    #define STORAGE_EEPROM_CAL_DAY_PASSIVE_SIZE (sizeof(r_act_cal_day_profile_t))
    /* activation_time */
    #define STORAGE_EEPROM_CAL_ACTIVATION_TIME_ADDR (STORAGE_EEPROM_CAL_DAY_PASSIVE_ADDR + STORAGE_EEPROM_CAL_DAY_PASSIVE_SIZE)
    #define STORAGE_EEPROM_CAL_ACTIVATION_TIME_SIZE (sizeof(rtc_counter_value_t))
    /* exe_state */
    #define STORAGE_EEPROM_CAL_EXE_STATE_ADDR (STORAGE_EEPROM_CAL_ACTIVATION_TIME_ADDR + STORAGE_EEPROM_CAL_ACTIVATION_TIME_SIZE)
    #define STORAGE_EEPROM_CAL_EXE_STATE_SIZE (sizeof(uint8_t))
    /* processing_state */
    #define STORAGE_EEPROM_CAL_PROCESSING_STATE_ADDR (STORAGE_EEPROM_CAL_EXE_STATE_ADDR + STORAGE_EEPROM_CAL_EXE_STATE_SIZE)
    #define STORAGE_EEPROM_CAL_PROCESSING_STATE_SIZE (sizeof(uint8_t))
    /* active_state */
    #define STORAGE_EEPROM_CAL_ACTIVE_STATE_ADDR (STORAGE_EEPROM_CAL_PROCESSING_STATE_ADDR + STORAGE_EEPROM_CAL_PROCESSING_STATE_SIZE)
    #define STORAGE_EEPROM_CAL_ACTIVE_STATE_SIZE (sizeof(uint8_t))
    /* season_state */
    #define STORAGE_EEPROM_CAL_SEASON_STATE_ADDR (STORAGE_EEPROM_CAL_ACTIVE_STATE_ADDR + STORAGE_EEPROM_CAL_ACTIVE_STATE_SIZE)
    #define STORAGE_EEPROM_CAL_SEASON_STATE_SIZE (sizeof(uint8_t))
    /* activation_time_long */
    #define STORAGE_EEPROM_CAL_ACTIVATION_TIME_LONG_ADDR (STORAGE_EEPROM_CAL_SEASON_STATE_ADDR + STORAGE_EEPROM_CAL_SEASON_STATE_SIZE)
    #define STORAGE_EEPROM_CAL_ACTIVATION_TIME_LONG_SIZE (sizeof(uint8_t) * 12 )

	/* Sub module Cal last address */
    #define STORAGE_EEPROM_CAL_LAST_ADDR (STORAGE_EEPROM_CAL_ACTIVATION_TIME_LONG_ADDR + STORAGE_EEPROM_CAL_ACTIVATION_TIME_LONG_SIZE)

    #undef STORAGE_EEPROM_METER_FORMAT_LAST_ADDR
    #define STORAGE_EEPROM_METER_FORMAT_LAST_ADDR	(STORAGE_EEPROM_CAL_LAST_ADDR)

#endif /* Cal */


/*****************************************
* Sub module: Load ctrl
******************************************/
#if (STORAGE_EEPROM_SUB_MODULE_LOAD_CTRL == 1)

    /* state */
    #define STORAGE_EEPROM_LOAD_CTRL_STATE_ADDR (STORAGE_EEPROM_CAL_LAST_ADDR)
    #define STORAGE_EEPROM_LOAD_CTRL_STATE_SIZE (sizeof(uint8_t))
    /* mode */
    #define STORAGE_EEPROM_LOAD_CTRL_MODE_ADDR (STORAGE_EEPROM_LOAD_CTRL_STATE_ADDR + STORAGE_EEPROM_LOAD_CTRL_STATE_SIZE)
    #define STORAGE_EEPROM_LOAD_CTRL_MODE_SIZE (sizeof(uint8_t))
    /* threshold normal */
    #define STORAGE_EEPROM_LOAD_CTRL_THRESHOLD_NORMAL_ADDR (STORAGE_EEPROM_LOAD_CTRL_MODE_ADDR + STORAGE_EEPROM_LOAD_CTRL_MODE_SIZE)
    #define STORAGE_EEPROM_LOAD_CTRL_THRESHOLD_NORMAL_SIZE (sizeof(uint32_t))
    /* threshold emergency */
    #define STORAGE_EEPROM_LOAD_CTRL_THRESHOLD_EMERGENCY_ADDR (STORAGE_EEPROM_LOAD_CTRL_THRESHOLD_NORMAL_ADDR + STORAGE_EEPROM_LOAD_CTRL_THRESHOLD_NORMAL_SIZE)
    #define STORAGE_EEPROM_LOAD_CTRL_THRESHOLD_EMERGENCY_SIZE (sizeof(uint32_t))
    /* min over duration */
    #define STORAGE_EEPROM_LOAD_CTRL_MIN_OVER_DURATION_ADDR (STORAGE_EEPROM_LOAD_CTRL_THRESHOLD_EMERGENCY_ADDR + STORAGE_EEPROM_LOAD_CTRL_THRESHOLD_EMERGENCY_SIZE)
    #define STORAGE_EEPROM_LOAD_CTRL_MIN_OVER_DURATION_SIZE (sizeof(uint32_t))
    /* min under duration */
    #define STORAGE_EEPROM_LOAD_CTRL_MIN_UNDER_DURATION_ADDR (STORAGE_EEPROM_LOAD_CTRL_MIN_OVER_DURATION_ADDR + STORAGE_EEPROM_LOAD_CTRL_MIN_OVER_DURATION_SIZE)
    #define STORAGE_EEPROM_LOAD_CTRL_MIN_UNDER_DURATION_SIZE (sizeof(uint32_t))
    /* Relay status */
    #define STORAGE_EEPROM_LOAD_CTRL_RELAY_STATUS_ADDR (STORAGE_EEPROM_LOAD_CTRL_MIN_UNDER_DURATION_ADDR + STORAGE_EEPROM_LOAD_CTRL_MIN_UNDER_DURATION_SIZE)
    #define STORAGE_EEPROM_LOAD_CTRL_RELAY_STATUS_SIZE (sizeof(uint8_t))
    /* Relay Progress Status */
    #define STORAGE_EEPROM_LOAD_CTRL_RELAY_PROGRESS_STATUS_ADDR (STORAGE_EEPROM_LOAD_CTRL_RELAY_STATUS_ADDR + STORAGE_EEPROM_LOAD_CTRL_RELAY_STATUS_SIZE)
    #define STORAGE_EEPROM_LOAD_CTRL_RELAY_PROGRESS_STATUS_SIZE (sizeof(RelayProgessStatus_t))

	/* Sub module Load ctrl last address */
    #define STORAGE_EEPROM_LOAD_CTRL_LAST_ADDR (STORAGE_EEPROM_LOAD_CTRL_RELAY_PROGRESS_STATUS_ADDR + STORAGE_EEPROM_LOAD_CTRL_RELAY_PROGRESS_STATUS_SIZE)

    #undef STORAGE_EEPROM_METER_FORMAT_LAST_ADDR
    #define STORAGE_EEPROM_METER_FORMAT_LAST_ADDR	(STORAGE_EEPROM_LOAD_CTRL_LAST_ADDR)

#endif /* Load ctrl */


/*====================================================================================================================*/

STATIC_ASSERT(STORAGE_EEPROM_GLOBAL_HEADER_CODE_ADDR    > 0x00FF                                 );
STATIC_ASSERT(STORAGE_EEPROM_COMMON_RTC_ADDR            >= STORAGE_EEPROM_GLOBAL_LAST_ADDR       );
STATIC_ASSERT(STORAGE_EEPROM_ENERGY_MDM_STATE_ADDR      >= STORAGE_EEPROM_COMMON_RTC_ADDR        );
STATIC_ASSERT(STORAGE_EEPROM_ENERGY_TARIFF_STATE_ADDR   >= STORAGE_EEPROM_ENERGY_MDM_LAST_ADDR   );
STATIC_ASSERT(STORAGE_EEPROM_SCHEDULER_DATA_ADDR        >= STORAGE_EEPROM_ENERGY_TARIFF_LAST_ADDR);
STATIC_ASSERT(STORAGE_EEPROM_EVENT_LOG_HEADER_CODE_ADDR >= STORAGE_EEPROM_SCHEDULER_LAST_ADDR    );
STATIC_ASSERT(STORAGE_EEPROM_BLOCKLOAD_PARTITION_ADDR   >= STORAGE_EEPROM_EVENT_LOG_LAST_ADDR    );
STATIC_ASSERT(STORAGE_EEPROM_DAILYLOAD_PARTITION_ADDR   >= STORAGE_EEPROM_BLOCKLOAD_LAST_ADDR    );
STATIC_ASSERT(STORAGE_EEPROM_BILLING_PARTITION_ADDR     >= STORAGE_EEPROM_DAILYLOAD_LAST_ADDR    );
STATIC_ASSERT(STORAGE_EEPROM_CAL_NAME_ACTIVE_ADDR       >= STORAGE_EEPROM_BILLING_LAST_ADDR      );

#if (STORAGE_EEPROM_SUB_MODULE_LOAD_CTRL == 1)
STATIC_ASSERT(STORAGE_EEPROM_LOAD_CTRL_STATE_ADDR       >= STORAGE_EEPROM_CAL_LAST_ADDR          );
#endif

/*************************************************************************************************************************
 * DATAFLASH
*********************************************************************************************************************** */

#define STORAGE_CONFIG_NAMEPLATE_START_ADDR   (0x0000)
#define STORAGE_CONFIG_SUB_MODULE_NAMEPLATE (1)	

/*****************************************
* Sub module: Nameplate
******************************************/
#if (STORAGE_CONFIG_SUB_MODULE_NAMEPLATE == 1)

    /* FlagID */
    #define STORAGE_CONFIG_NAMEPLATE_FLAGID_ADDR (STORAGE_CONFIG_NAMEPLATE_START_ADDR + 512)
    #define STORAGE_CONFIG_NAMEPLATE_FLAGID_SIZE (sizeof(uint8_t) * 4  )

    /* SN */
    #define STORAGE_CONFIG_NAMEPLATE_SN_ADDR (STORAGE_CONFIG_NAMEPLATE_FLAGID_ADDR + STORAGE_CONFIG_NAMEPLATE_FLAGID_SIZE)
    #define STORAGE_CONFIG_NAMEPLATE_SN_SIZE (sizeof(uint8_t) * 20 )
    /* Mfr name */
    #define STORAGE_CONFIG_NAMEPLATE_MFR_NAME_ADDR (STORAGE_CONFIG_NAMEPLATE_SN_ADDR + STORAGE_CONFIG_NAMEPLATE_SN_SIZE)
    #define STORAGE_CONFIG_NAMEPLATE_MFR_NAME_SIZE (sizeof(uint8_t) * 50 )
    /* FW version */
    #define STORAGE_CONFIG_NAMEPLATE_FW_VERSION_ADDR (STORAGE_CONFIG_NAMEPLATE_MFR_NAME_ADDR + STORAGE_CONFIG_NAMEPLATE_MFR_NAME_SIZE)
    #define STORAGE_CONFIG_NAMEPLATE_FW_VERSION_SIZE (sizeof(uint8_t) * 16 )
    /* Meter Type */
    #define STORAGE_CONFIG_NAMEPLATE_METER_TYPE_ADDR (STORAGE_CONFIG_NAMEPLATE_FW_VERSION_ADDR + STORAGE_CONFIG_NAMEPLATE_FW_VERSION_SIZE)
    #define STORAGE_CONFIG_NAMEPLATE_METER_TYPE_SIZE (sizeof(uint8_t) * 2 )
    /* Category */
    #define STORAGE_CONFIG_NAMEPLATE_CATEGORY_ADDR (STORAGE_CONFIG_NAMEPLATE_METER_TYPE_ADDR + STORAGE_CONFIG_NAMEPLATE_METER_TYPE_SIZE)
    #define STORAGE_CONFIG_NAMEPLATE_CATEGORY_SIZE (sizeof(uint8_t) * 2 )
    /* LDN */
    #define STORAGE_CONFIG_NAMEPLATE_LDN_ADDR (STORAGE_CONFIG_NAMEPLATE_CATEGORY_ADDR + STORAGE_CONFIG_NAMEPLATE_CATEGORY_SIZE)
    #define STORAGE_CONFIG_NAMEPLATE_LDN_SIZE (sizeof(uint8_t) * 10 )

	/* Sub module Nameplate last address */
    #define STORAGE_CONFIG_NAMEPLATE_LAST_ADDR (STORAGE_CONFIG_NAMEPLATE_LDN_ADDR + STORAGE_CONFIG_NAMEPLATE_LDN_SIZE)


#endif /* Nameplate */

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/

#endif /* _STORAGE_FORMAT_H */

