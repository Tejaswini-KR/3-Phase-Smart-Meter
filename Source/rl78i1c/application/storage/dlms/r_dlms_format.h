/***********************************************************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
************************************************************************************************************************
* File Name    : r_dlms_format.h
* Version      : Version
* Description  : Description
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
***********************************************************************************************************************/

/* Start user code for version control. Do not edit comment generated here */
// 2018-03-29 New creation

// 2018-03-29
//				Change offset to 0x0400, so the metrology have more space. Later for 3P
//				Change storage structure of activity calendar:
//				Add reserved space

// EEPROM
// (Generated on 2018-06-05 14:40:41)		New generate
// (Update    on 2018-08-02 11:36:26)		Add IP for Push setup
// (update    on 2018-08-08 08:31:45)		Separate buffer info of Event table into 6 parts
// (update    on 2018-08-14 13:52:23)		Add billing date items
// (update    on 2018-08-15 13:03:52)		Add backup process state for TOD
// (update    on 2018-08-28 09:40:09)		Add backup items for Block load and Daily load (KWh and KVAh, import and export)
// (update    on 2018-11-07 13:35:44)		Add more reserved space for event log
// (update    on 2019-01-09 11:25:59)		Add last memory address
// (update    on 2019-01-16 14:13:21)		Restructure activity calendar profile, group invidual element into struct
// (update    on 2019-02-20 14:50:04)		Add Block load capture enable flag
// (update    on 2019-09-18 15:41:53)		Demolish day_id sharing table

/* End user code. Do not edit comment generated here */

#ifndef _R_DLMS_STORAGE_MAP_H
#define _R_DLMS_STORAGE_MAP_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Driver */
#include "r_cg_macrodriver.h"

/* Common */
#include "typedef.h"
#include "compiler.h"

/* DLMS Application */
#include "r_dlms_storage.h"
#include "r_dlms_app.h"
//#include "r_dlms_tod.h"
#include "r_dlms_push.h"
#include "r_dlms_scheduler.h"
#include "r_dlms_event.h"
//#include "r_dlms_ctrl.h"
#include "r_meter_format.h"
/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Start user code for macro. Do not edit comment generated here */
												/* 0xFE000000 + (Version = v02.01.04) */
#define STORAGE_EEPROM_CURRENT_VERISON			(0xFE020104)
												/* 0xFE000000 + (Version = v02.01.03) */
#define STORAGE_DATAFLASH_CURRENT_VERISON		(0xFE020103)


/* End user code. Do not edit comment generated here */
/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/


/* Start user code for typedef. Do not edit comment generated here */

#define ONE_EVENT_FULL_LOG         ONE_EVENT_ENERGY_DATA_LOG
#define ONE_EVENT_SHORT_LOG        ONE_EVENT_ID_LOG

/* RTC Date Time */
typedef struct tag_STORAGE_RTC_DATE_TIME
{
	/* Total: 8 bytes */
	uint8_t Sec;        /* Second */
	uint8_t Min;        /* Minute */
	uint8_t Hour;       /* Hour */
	uint8_t Day;        /* Day */
	uint8_t Week;       /* Day of week */
	uint8_t Month;      /* Month */
	uint8_t Year;       /* Year (ony 2 ending digit) */

	uint8_t reserved;   /* Reserved Byte (Padding) - NO USE */

} STORAGE_RTC_DATE_TIME;
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
EEPROM MEMORY MAP
***********************************************************************************************************************/


/* Generated on : Wednesday, January 15, 2020 */
/* root */
/***********************************************************************************************************************
EEPROM_DLMS MEMORY MAP
***********************************************************************************************************************/


/*--------------------------------------------------------------------------------------*/
/* GROUP: EEPROM BASE , Address = 0x0000 */
#define STORAGE_EEPROM_DLMS_EEPROM_BASE_GROUP    		(STORAGE_EEPROM_METER_FORMAT_LAST_ADDR)

/*--------------------------------------------------------------------------------------*/
/* GROUP: Header , Address = 0x0400 */
#define STORAGE_EEPROM_DLMS_HEADER_GROUP                             (STORAGE_EEPROM_DLMS_EEPROM_BASE_GROUP)

/* Code, 0x0400 */
#define STORAGE_EEPROM_DLMS_CODE_ADDR                                (STORAGE_EEPROM_DLMS_HEADER_GROUP)
#define STORAGE_EEPROM_DLMS_CODE_SIZE                                (0)

/* Usage, 0x0404 */
#define STORAGE_EEPROM_DLMS_USAGE_ADDR                               (STORAGE_EEPROM_DLMS_CODE_ADDR + STORAGE_EEPROM_DLMS_CODE_SIZE)
#define STORAGE_EEPROM_DLMS_USAGE_SIZE                               (sizeof(uint16_t))

/* PADDING */
#define STORAGE_EEPROM_DLMS_HEADER_GROUP_END_ADDR (STORAGE_EEPROM_DLMS_USAGE_ADDR + STORAGE_EEPROM_DLMS_USAGE_SIZE)
#define STORAGE_EEPROM_DLMS_HEADER_GROUP_PADDING (0x007A)

/*--------------------------------------------------------------------------------------*/
/* GROUP: Parameter , Address = 0x0480 */
#define STORAGE_EEPROM_DLMS_PARAMETER_GROUP      (STORAGE_EEPROM_DLMS_HEADER_GROUP_END_ADDR + STORAGE_EEPROM_DLMS_HEADER_GROUP_PADDING)

/* Meter serial number, 0x0480 */
#define STORAGE_EEPROM_DLMS_METER_SERIAL_NUMBER_ADDR                 (STORAGE_EEPROM_DLMS_PARAMETER_GROUP)
#define STORAGE_EEPROM_DLMS_METER_SERIAL_NUMBER_SIZE                 (sizeof(uint8_t) * 16)

/* Manufature year, 0x0490 */
#define STORAGE_EEPROM_DLMS_MANUFATURE_YEAR_ADDR                     (STORAGE_EEPROM_DLMS_METER_SERIAL_NUMBER_ADDR + STORAGE_EEPROM_DLMS_METER_SERIAL_NUMBER_SIZE)
#define STORAGE_EEPROM_DLMS_MANUFATURE_YEAR_SIZE                     (sizeof(uint8_t) * 4)

/* Total power on, 0x0494 */
#define STORAGE_EEPROM_DLMS_TOTAL_POWER_ON_ADDR                      (STORAGE_EEPROM_DLMS_MANUFATURE_YEAR_ADDR + STORAGE_EEPROM_DLMS_MANUFATURE_YEAR_SIZE)
#define STORAGE_EEPROM_DLMS_TOTAL_POWER_ON_SIZE                      (sizeof(uint32_t))

/* Billing power on, 0x0498 */
#define STORAGE_EEPROM_DLMS_BILLING_POWER_ON_ADDR                    (STORAGE_EEPROM_DLMS_TOTAL_POWER_ON_ADDR + STORAGE_EEPROM_DLMS_TOTAL_POWER_ON_SIZE)
#define STORAGE_EEPROM_DLMS_BILLING_POWER_ON_SIZE                    (sizeof(uint32_t))

/* Billing counter , 0x049C */
#define STORAGE_EEPROM_DLMS_BILLING_COUNTER_ADDR                     (STORAGE_EEPROM_DLMS_BILLING_POWER_ON_ADDR + STORAGE_EEPROM_DLMS_BILLING_POWER_ON_SIZE)
#define STORAGE_EEPROM_DLMS_BILLING_COUNTER_SIZE                     (sizeof(uint32_t))

/* Tamper counter, 0x04A0 */
#define STORAGE_EEPROM_DLMS_TAMPER_COUNTER_ADDR                      (STORAGE_EEPROM_DLMS_BILLING_COUNTER_ADDR + STORAGE_EEPROM_DLMS_BILLING_COUNTER_SIZE)
#define STORAGE_EEPROM_DLMS_TAMPER_COUNTER_SIZE                      (sizeof(uint32_t))

/* PC, 0x04A4 */
#define STORAGE_EEPROM_DLMS_PC_ADDR                                  (STORAGE_EEPROM_DLMS_TAMPER_COUNTER_ADDR + STORAGE_EEPROM_DLMS_TAMPER_COUNTER_SIZE)
#define STORAGE_EEPROM_DLMS_PC_SIZE                                  (sizeof(uint32_t))

/* Blockload period, 0x04A8 */
#define STORAGE_EEPROM_DLMS_BLOCKLOAD_PERIOD_ADDR                    (STORAGE_EEPROM_DLMS_PC_ADDR + STORAGE_EEPROM_DLMS_PC_SIZE)
#define STORAGE_EEPROM_DLMS_BLOCKLOAD_PERIOD_SIZE                    (sizeof(uint32_t))

/* Demand ip, 0x04AC */
#define STORAGE_EEPROM_DLMS_DEMAND_IP_ADDR                           (STORAGE_EEPROM_DLMS_BLOCKLOAD_PERIOD_ADDR + STORAGE_EEPROM_DLMS_BLOCKLOAD_PERIOD_SIZE)
#define STORAGE_EEPROM_DLMS_DEMAND_IP_SIZE                           (sizeof(uint32_t))

/* Timezone, 0x04B0 */
#define STORAGE_EEPROM_DLMS_TIMEZONE_ADDR                            (STORAGE_EEPROM_DLMS_DEMAND_IP_ADDR + STORAGE_EEPROM_DLMS_DEMAND_IP_SIZE)
#define STORAGE_EEPROM_DLMS_TIMEZONE_SIZE                            (sizeof(uint16_t))

/* Old time, 0x04B2 */
#define STORAGE_EEPROM_DLMS_OLD_TIME_ADDR                            (STORAGE_EEPROM_DLMS_TIMEZONE_ADDR + STORAGE_EEPROM_DLMS_TIMEZONE_SIZE)
#define STORAGE_EEPROM_DLMS_OLD_TIME_SIZE                            (sizeof(uint8_t) * 8)

/* ESW, 0x04BA */
#define STORAGE_EEPROM_DLMS_ESW_ADDR                                 (STORAGE_EEPROM_DLMS_OLD_TIME_ADDR + STORAGE_EEPROM_DLMS_OLD_TIME_SIZE)
#define STORAGE_EEPROM_DLMS_ESW_SIZE                                 (sizeof(uint8_t) * 16)

/* ESWF, 0x04CA */
#define STORAGE_EEPROM_DLMS_ESWF_ADDR                                (STORAGE_EEPROM_DLMS_ESW_ADDR + STORAGE_EEPROM_DLMS_ESW_SIZE)
#define STORAGE_EEPROM_DLMS_ESWF_SIZE                                (sizeof(uint8_t) * 16)

/* EventCode, 0x04DA */
#define STORAGE_EEPROM_EVENTCODE_ADDR                           (STORAGE_EEPROM_DLMS_ESWF_ADDR + STORAGE_EEPROM_DLMS_ESWF_SIZE)
#define STORAGE_EEPROM_EVENTCODE_SIZE                           (sizeof(uint16_t) * EVENT_PROFILE_NUMBER)

/* Relay status, 0x04E8 */
#define STORAGE_EEPROM_DLMS_RELAY_STATUS_ADDR                        (STORAGE_EEPROM_EVENTCODE_ADDR + STORAGE_EEPROM_EVENTCODE_SIZE)
#define STORAGE_EEPROM_DLMS_RELAY_STATUS_SIZE                        (sizeof(uint8_t))

/* Ctrl threshold normal, 0x04E9 */
#define STORAGE_EEPROM_DLMS_CTRL_THRESHOLD_NORMAL_ADDR               (STORAGE_EEPROM_DLMS_RELAY_STATUS_ADDR + STORAGE_EEPROM_DLMS_RELAY_STATUS_SIZE)
#define STORAGE_EEPROM_DLMS_CTRL_THRESHOLD_NORMAL_SIZE               (sizeof(uint32_t))

/* Ctrl threshold emergency, 0x04ED */
#define STORAGE_EEPROM_DLMS_CTRL_THRESHOLD_EMERGENCY_ADDR            (STORAGE_EEPROM_DLMS_CTRL_THRESHOLD_NORMAL_ADDR + STORAGE_EEPROM_DLMS_CTRL_THRESHOLD_NORMAL_SIZE)
#define STORAGE_EEPROM_DLMS_CTRL_THRESHOLD_EMERGENCY_SIZE            (sizeof(uint32_t))

/* SMO_1_LEN, 0x04F1 */
#define STORAGE_EEPROM_DLMS_SMO_1_LEN_ADDR                           (STORAGE_EEPROM_DLMS_CTRL_THRESHOLD_EMERGENCY_ADDR + STORAGE_EEPROM_DLMS_CTRL_THRESHOLD_EMERGENCY_SIZE)
#define STORAGE_EEPROM_DLMS_SMO_1_LEN_SIZE                           (sizeof(uint8_t))

/* SMO_1, 0x04F2 */
#define STORAGE_EEPROM_DLMS_SMO_1_ADDR                               (STORAGE_EEPROM_DLMS_SMO_1_LEN_ADDR + STORAGE_EEPROM_DLMS_SMO_1_LEN_SIZE)
#define STORAGE_EEPROM_DLMS_SMO_1_SIZE                               (sizeof(uint8_t) * 128)

/* SMO_1_Padding, 0x0572 */
#define STORAGE_EEPROM_DLMS_SMO_1_PADDING_ADDR                       (STORAGE_EEPROM_DLMS_SMO_1_ADDR + STORAGE_EEPROM_DLMS_SMO_1_SIZE)
#define STORAGE_EEPROM_DLMS_SMO_1_PADDING_SIZE                       (sizeof(uint8_t))

/* SMO_2_LEN, 0x0573 */
#define STORAGE_EEPROM_DLMS_SMO_2_LEN_ADDR                           (STORAGE_EEPROM_DLMS_SMO_1_PADDING_ADDR + STORAGE_EEPROM_DLMS_SMO_1_PADDING_SIZE)
#define STORAGE_EEPROM_DLMS_SMO_2_LEN_SIZE                           (sizeof(uint8_t))

/* SMO_2, 0x0574 */
#define STORAGE_EEPROM_DLMS_SMO_2_ADDR                               (STORAGE_EEPROM_DLMS_SMO_2_LEN_ADDR + STORAGE_EEPROM_DLMS_SMO_2_LEN_SIZE)
#define STORAGE_EEPROM_DLMS_SMO_2_SIZE                               (sizeof(uint8_t) * 128)

/* SMO_2_Padding, 0x05F4 */
#define STORAGE_EEPROM_DLMS_SMO_2_PADDING_ADDR                       (STORAGE_EEPROM_DLMS_SMO_2_ADDR + STORAGE_EEPROM_DLMS_SMO_2_SIZE)
#define STORAGE_EEPROM_DLMS_SMO_2_PADDING_SIZE                       (sizeof(uint8_t))

/* Billing date, 0x05F5 */
#define STORAGE_EEPROM_DLMS_BILLING_DATE_ADDR                        (STORAGE_EEPROM_DLMS_SMO_2_PADDING_ADDR + STORAGE_EEPROM_DLMS_SMO_2_PADDING_SIZE)
#define STORAGE_EEPROM_DLMS_BILLING_DATE_SIZE                        (sizeof(R_DLMS_RTC_T))

/* Blockload state, 0x05FB */
#define STORAGE_EEPROM_DLMS_BLOCKLOAD_STATE_ADDR                     (STORAGE_EEPROM_DLMS_BILLING_DATE_ADDR + STORAGE_EEPROM_DLMS_BILLING_DATE_SIZE)
#define STORAGE_EEPROM_DLMS_BLOCKLOAD_STATE_SIZE                     (sizeof(uint8_t))

/* Kwh block, 0x05FC */
#define STORAGE_EEPROM_DLMS_KWH_BLOCK_ADDR                           (STORAGE_EEPROM_DLMS_BLOCKLOAD_STATE_ADDR + STORAGE_EEPROM_DLMS_BLOCKLOAD_STATE_SIZE)
#define STORAGE_EEPROM_DLMS_KWH_BLOCK_SIZE                           (sizeof(uint32_t))

/* Kvah block, 0x0600 */
#define STORAGE_EEPROM_DLMS_KVAH_BLOCK_ADDR                          (STORAGE_EEPROM_DLMS_KWH_BLOCK_ADDR + STORAGE_EEPROM_DLMS_KWH_BLOCK_SIZE)
#define STORAGE_EEPROM_DLMS_KVAH_BLOCK_SIZE                          (sizeof(uint32_t))

/* Voltage average block, 0x0604 */
#define STORAGE_EEPROM_DLMS_VOLTAGE_AVERAGE_BLOCK_ADDR               (STORAGE_EEPROM_DLMS_KVAH_BLOCK_ADDR + STORAGE_EEPROM_DLMS_KVAH_BLOCK_SIZE)
#define STORAGE_EEPROM_DLMS_VOLTAGE_AVERAGE_BLOCK_SIZE               (sizeof(uint32_t))

/* Current average block, 0x0608 */
#define STORAGE_EEPROM_DLMS_CURRENT_AVERAGE_BLOCK_ADDR               (STORAGE_EEPROM_DLMS_VOLTAGE_AVERAGE_BLOCK_ADDR + STORAGE_EEPROM_DLMS_VOLTAGE_AVERAGE_BLOCK_SIZE)
#define STORAGE_EEPROM_DLMS_CURRENT_AVERAGE_BLOCK_SIZE               (sizeof(uint32_t))

/* Kwh block export, 0x060C */
#define STORAGE_EEPROM_DLMS_KWH_BLOCK_EXPORT_ADDR                    (STORAGE_EEPROM_DLMS_CURRENT_AVERAGE_BLOCK_ADDR + STORAGE_EEPROM_DLMS_CURRENT_AVERAGE_BLOCK_SIZE)
#define STORAGE_EEPROM_DLMS_KWH_BLOCK_EXPORT_SIZE                    (sizeof(uint32_t))

/* Kvah block export, 0x0610 */
#define STORAGE_EEPROM_DLMS_KVAH_BLOCK_EXPORT_ADDR                   (STORAGE_EEPROM_DLMS_KWH_BLOCK_EXPORT_ADDR + STORAGE_EEPROM_DLMS_KWH_BLOCK_EXPORT_SIZE)
#define STORAGE_EEPROM_DLMS_KVAH_BLOCK_EXPORT_SIZE                   (sizeof(uint32_t))

/* Kwh day, 0x0614 */
#define STORAGE_EEPROM_DLMS_KWH_DAY_ADDR                             (STORAGE_EEPROM_DLMS_KVAH_BLOCK_EXPORT_ADDR + STORAGE_EEPROM_DLMS_KVAH_BLOCK_EXPORT_SIZE)
#define STORAGE_EEPROM_DLMS_KWH_DAY_SIZE                             (sizeof(uint32_t))

/* Kvah day, 0x0618 */
#define STORAGE_EEPROM_DLMS_KVAH_DAY_ADDR                            (STORAGE_EEPROM_DLMS_KWH_DAY_ADDR + STORAGE_EEPROM_DLMS_KWH_DAY_SIZE)
#define STORAGE_EEPROM_DLMS_KVAH_DAY_SIZE                            (sizeof(uint32_t))

/* Kwh day export, 0x061C */
#define STORAGE_EEPROM_DLMS_KWH_DAY_EXPORT_ADDR                      (STORAGE_EEPROM_DLMS_KVAH_DAY_ADDR + STORAGE_EEPROM_DLMS_KVAH_DAY_SIZE)
#define STORAGE_EEPROM_DLMS_KWH_DAY_EXPORT_SIZE                      (sizeof(uint32_t))

/* Kvah day export, 0x0620 */
#define STORAGE_EEPROM_DLMS_KVAH_DAY_EXPORT_ADDR                     (STORAGE_EEPROM_DLMS_KWH_DAY_EXPORT_ADDR + STORAGE_EEPROM_DLMS_KWH_DAY_EXPORT_SIZE)
#define STORAGE_EEPROM_DLMS_KVAH_DAY_EXPORT_SIZE                     (sizeof(uint32_t))

/* Old time blockload, 0x0624 */
#define STORAGE_EEPROM_DLMS_OLD_TIME_BLOCKLOAD_ADDR                  (STORAGE_EEPROM_DLMS_KVAH_DAY_EXPORT_ADDR + STORAGE_EEPROM_DLMS_KVAH_DAY_EXPORT_SIZE)
#define STORAGE_EEPROM_DLMS_OLD_TIME_BLOCKLOAD_SIZE                  (sizeof(R_DLMS_RTC_T))

/* Ctrl min over duration, 0x062A */
#define STORAGE_EEPROM_DLMS_CTRL_MIN_OVER_DURATION_ADDR              (STORAGE_EEPROM_DLMS_OLD_TIME_BLOCKLOAD_ADDR + STORAGE_EEPROM_DLMS_OLD_TIME_BLOCKLOAD_SIZE)
#define STORAGE_EEPROM_DLMS_CTRL_MIN_OVER_DURATION_SIZE              (sizeof(uint32_t))

/* Ctrl min under duration, 0x062E */
#define STORAGE_EEPROM_DLMS_CTRL_MIN_UNDER_DURATION_ADDR             (STORAGE_EEPROM_DLMS_CTRL_MIN_OVER_DURATION_ADDR + STORAGE_EEPROM_DLMS_CTRL_MIN_OVER_DURATION_SIZE)
#define STORAGE_EEPROM_DLMS_CTRL_MIN_UNDER_DURATION_SIZE             (sizeof(uint32_t))

/* Blockload capture enable, 0x0632 */
#define STORAGE_EEPROM_DLMS_BLOCKLOAD_CAPTURE_ENABLE_ADDR            (STORAGE_EEPROM_DLMS_CTRL_MIN_UNDER_DURATION_ADDR + STORAGE_EEPROM_DLMS_CTRL_MIN_UNDER_DURATION_SIZE)
#define STORAGE_EEPROM_DLMS_BLOCKLOAD_CAPTURE_ENABLE_SIZE            (sizeof(uint8_t))

/* Meter mode, 0x0633 */
#define STORAGE_EEPROM_DLMS_METER_MODE_ADDR                          (STORAGE_EEPROM_DLMS_BLOCKLOAD_CAPTURE_ENABLE_ADDR + STORAGE_EEPROM_DLMS_BLOCKLOAD_CAPTURE_ENABLE_SIZE)
#define STORAGE_EEPROM_DLMS_METER_MODE_SIZE                          (sizeof(uint8_t))

/* Payment mode, 0x0634 */
#define STORAGE_EEPROM_DLMS_PAYMENT_MODE_ADDR                        (STORAGE_EEPROM_DLMS_METER_MODE_ADDR + STORAGE_EEPROM_DLMS_METER_MODE_SIZE)
#define STORAGE_EEPROM_DLMS_PAYMENT_MODE_SIZE                        (sizeof(uint8_t))

/* Clock status, 0x0635 */
#define STORAGE_EEPROM_DLMS_CLOCK_STATUS_ADDR                        (STORAGE_EEPROM_DLMS_PAYMENT_MODE_ADDR + STORAGE_EEPROM_DLMS_PAYMENT_MODE_SIZE)
#define STORAGE_EEPROM_DLMS_CLOCK_STATUS_SIZE                        (sizeof(uint8_t))

/* billing_events, 0x0636 */
#define STORAGE_EEPROM_DLMS_BILLING_EVENTS_ADDR                      (STORAGE_EEPROM_DLMS_CLOCK_STATUS_ADDR + STORAGE_EEPROM_DLMS_CLOCK_STATUS_SIZE)
#define STORAGE_EEPROM_DLMS_BILLING_EVENTS_SIZE                      (sizeof(uint16_t))

/* PADDING */
#define STORAGE_EEPROM_DLMS_PARAMETER_GROUP_END_ADDR (STORAGE_EEPROM_DLMS_BILLING_EVENTS_ADDR + STORAGE_EEPROM_DLMS_BILLING_EVENTS_SIZE)
#define STORAGE_EEPROM_DLMS_PARAMETER_GROUP_PADDING (0x000A)

/*--------------------------------------------------------------------------------------*/
/* GROUP: Push , Address = 0x0642 */
#define STORAGE_EEPROM_DLMS_PUSH_GROUP           (STORAGE_EEPROM_DLMS_PARAMETER_GROUP_END_ADDR + STORAGE_EEPROM_DLMS_PARAMETER_GROUP_PADDING)

/* Push status, 0x0642 */
#define STORAGE_EEPROM_DLMS_PUSH_STATUS_ADDR                         (STORAGE_EEPROM_DLMS_PUSH_GROUP)
#define STORAGE_EEPROM_DLMS_PUSH_STATUS_SIZE                         (sizeof(uint8_t) * PUSH_OBJECT_NUMBER)

/* Push trigger, 0x0647 */
#define STORAGE_EEPROM_DLMS_PUSH_TRIGGER_ADDR                        (STORAGE_EEPROM_DLMS_PUSH_STATUS_ADDR + STORAGE_EEPROM_DLMS_PUSH_STATUS_SIZE)
#define STORAGE_EEPROM_DLMS_PUSH_TRIGGER_SIZE                        (sizeof(uint8_t) * PUSH_OBJECT_NUMBER)

/* Rand interval, 0x064C */
#define STORAGE_EEPROM_DLMS_RAND_INTERVAL_ADDR                       (STORAGE_EEPROM_DLMS_PUSH_TRIGGER_ADDR + STORAGE_EEPROM_DLMS_PUSH_TRIGGER_SIZE)
#define STORAGE_EEPROM_DLMS_RAND_INTERVAL_SIZE                       (sizeof(uint16_t) * PUSH_OBJECT_NUMBER)

/* Number retry, 0x0656 */
#define STORAGE_EEPROM_DLMS_NUMBER_RETRY_ADDR                        (STORAGE_EEPROM_DLMS_RAND_INTERVAL_ADDR + STORAGE_EEPROM_DLMS_RAND_INTERVAL_SIZE)
#define STORAGE_EEPROM_DLMS_NUMBER_RETRY_SIZE                        (sizeof(uint8_t) * PUSH_OBJECT_NUMBER)

/* Retry delay time, 0x065B */
#define STORAGE_EEPROM_DLMS_RETRY_DELAY_TIME_ADDR                    (STORAGE_EEPROM_DLMS_NUMBER_RETRY_ADDR + STORAGE_EEPROM_DLMS_NUMBER_RETRY_SIZE)
#define STORAGE_EEPROM_DLMS_RETRY_DELAY_TIME_SIZE                    (sizeof(uint16_t) * PUSH_OBJECT_NUMBER)

/* Push_protocol, 0x0665 */
#define STORAGE_EEPROM_DLMS_PUSH_PROTOCOL_ADDR                       (STORAGE_EEPROM_DLMS_RETRY_DELAY_TIME_ADDR + STORAGE_EEPROM_DLMS_RETRY_DELAY_TIME_SIZE)
#define STORAGE_EEPROM_DLMS_PUSH_PROTOCOL_SIZE                       (sizeof(uint8_t) * PUSH_OBJECT_NUMBER)

/* Push_ip_config, 0x066A */
#define STORAGE_EEPROM_DLMS_PUSH_IP_CONFIG_ADDR                      (STORAGE_EEPROM_DLMS_PUSH_PROTOCOL_ADDR + STORAGE_EEPROM_DLMS_PUSH_PROTOCOL_SIZE)
#define STORAGE_EEPROM_DLMS_PUSH_IP_CONFIG_SIZE                      (sizeof(uint8_t) * 20 * PUSH_OBJECT_NUMBER)

/* Push_message_type, 0x06CE */
#define STORAGE_EEPROM_DLMS_PUSH_MESSAGE_TYPE_ADDR                   (STORAGE_EEPROM_DLMS_PUSH_IP_CONFIG_ADDR + STORAGE_EEPROM_DLMS_PUSH_IP_CONFIG_SIZE)
#define STORAGE_EEPROM_DLMS_PUSH_MESSAGE_TYPE_SIZE                   (sizeof(uint8_t) * PUSH_OBJECT_NUMBER)

/* Push_port, 0x06D3 */
#define STORAGE_EEPROM_DLMS_PUSH_PORT_ADDR                           (STORAGE_EEPROM_DLMS_PUSH_MESSAGE_TYPE_ADDR + STORAGE_EEPROM_DLMS_PUSH_MESSAGE_TYPE_SIZE)
#define STORAGE_EEPROM_DLMS_PUSH_PORT_SIZE                           (sizeof(uint8_t) * PUSH_OBJECT_NUMBER)

/* Push_window, 0x06D8 */
#define STORAGE_EEPROM_DLMS_PUSH_WINDOW_ADDR                         (STORAGE_EEPROM_DLMS_PUSH_PORT_ADDR + STORAGE_EEPROM_DLMS_PUSH_PORT_SIZE)
#define STORAGE_EEPROM_DLMS_PUSH_WINDOW_SIZE                         (sizeof(push_window_t) * PUSH_OBJECT_NUMBER * PUSH_MAX_WINDOW_SUPPORT)

/* Push_num_of_window, 0x0750 */
#define STORAGE_EEPROM_DLMS_PUSH_NUM_OF_WINDOW_ADDR                  (STORAGE_EEPROM_DLMS_PUSH_WINDOW_ADDR + STORAGE_EEPROM_DLMS_PUSH_WINDOW_SIZE)
#define STORAGE_EEPROM_DLMS_PUSH_NUM_OF_WINDOW_SIZE                  (sizeof(uint8_t) * PUSH_OBJECT_NUMBER)

/* PADDING */
#define STORAGE_EEPROM_DLMS_PUSH_GROUP_END_ADDR  (STORAGE_EEPROM_DLMS_PUSH_NUM_OF_WINDOW_ADDR + STORAGE_EEPROM_DLMS_PUSH_NUM_OF_WINDOW_SIZE)
#define STORAGE_EEPROM_DLMS_PUSH_GROUP_PADDING   (0x000A)


/*--------------------------------------------------------------------------------------*/
/* GROUP: Comm Profile , Address = 0x079F */
#define STORAGE_EEPROM_DLMS_COMM_PROFILE_GROUP   (STORAGE_EEPROM_DLMS_PUSH_GROUP_END_ADDR + STORAGE_EEPROM_DLMS_PUSH_GROUP_PADDING)

/* Tcpupd port, 0x079F */
#define STORAGE_EEPROM_DLMS_TCPUPD_PORT_ADDR                         (STORAGE_EEPROM_DLMS_COMM_PROFILE_GROUP)
#define STORAGE_EEPROM_DLMS_TCPUPD_PORT_SIZE                         (sizeof(uint32_t))

/* Ipv4 address, 0x07A3 */
#define STORAGE_EEPROM_DLMS_IPV4_ADDRESS_ADDR                        (STORAGE_EEPROM_DLMS_TCPUPD_PORT_ADDR + STORAGE_EEPROM_DLMS_TCPUPD_PORT_SIZE)
#define STORAGE_EEPROM_DLMS_IPV4_ADDRESS_SIZE                        (sizeof(uint8_t) * 4)

/* Ipv6 address, 0x07A7 */
#define STORAGE_EEPROM_DLMS_IPV6_ADDRESS_ADDR                        (STORAGE_EEPROM_DLMS_IPV4_ADDRESS_ADDR + STORAGE_EEPROM_DLMS_IPV4_ADDRESS_SIZE)
#define STORAGE_EEPROM_DLMS_IPV6_ADDRESS_SIZE                        (sizeof(uint8_t) * 16)

/* MAC address, 0x07B7 */
#define STORAGE_EEPROM_DLMS_MAC_ADDRESS_ADDR                         (STORAGE_EEPROM_DLMS_IPV6_ADDRESS_ADDR + STORAGE_EEPROM_DLMS_IPV6_ADDRESS_SIZE)
#define STORAGE_EEPROM_DLMS_MAC_ADDRESS_SIZE                         (sizeof(uint8_t) * 4)

/* Hdlc comm_speed , 0x07BB */
#define STORAGE_EEPROM_DLMS_HDLC_COMM_SPEED_ADDR                     (STORAGE_EEPROM_DLMS_MAC_ADDRESS_ADDR + STORAGE_EEPROM_DLMS_MAC_ADDRESS_SIZE)
#define STORAGE_EEPROM_DLMS_HDLC_COMM_SPEED_SIZE                     (sizeof(uint8_t))

/* Hdlc windows_size_tx, 0x07BC */
#define STORAGE_EEPROM_DLMS_HDLC_WINDOWS_SIZE_TX_ADDR                (STORAGE_EEPROM_DLMS_HDLC_COMM_SPEED_ADDR + STORAGE_EEPROM_DLMS_HDLC_COMM_SPEED_SIZE)
#define STORAGE_EEPROM_DLMS_HDLC_WINDOWS_SIZE_TX_SIZE                (sizeof(uint16_t))

/* Hdlc windows_size_rx, 0x07BE */
#define STORAGE_EEPROM_DLMS_HDLC_WINDOWS_SIZE_RX_ADDR                (STORAGE_EEPROM_DLMS_HDLC_WINDOWS_SIZE_TX_ADDR + STORAGE_EEPROM_DLMS_HDLC_WINDOWS_SIZE_TX_SIZE)
#define STORAGE_EEPROM_DLMS_HDLC_WINDOWS_SIZE_RX_SIZE                (sizeof(uint16_t))

/* Hdlc max_info_length_tx, 0x07C0 */
#define STORAGE_EEPROM_DLMS_HDLC_MAX_INFO_LENGTH_TX_ADDR             (STORAGE_EEPROM_DLMS_HDLC_WINDOWS_SIZE_RX_ADDR + STORAGE_EEPROM_DLMS_HDLC_WINDOWS_SIZE_RX_SIZE)
#define STORAGE_EEPROM_DLMS_HDLC_MAX_INFO_LENGTH_TX_SIZE             (sizeof(uint16_t))

/* Hdlc max_info_length_rx, 0x07C2 */
#define STORAGE_EEPROM_DLMS_HDLC_MAX_INFO_LENGTH_RX_ADDR             (STORAGE_EEPROM_DLMS_HDLC_MAX_INFO_LENGTH_TX_ADDR + STORAGE_EEPROM_DLMS_HDLC_MAX_INFO_LENGTH_TX_SIZE)
#define STORAGE_EEPROM_DLMS_HDLC_MAX_INFO_LENGTH_RX_SIZE             (sizeof(uint16_t))

/* Hdlc inter_octet_timeout, 0x07C4 */
#define STORAGE_EEPROM_DLMS_HDLC_INTER_OCTET_TIMEOUT_ADDR            (STORAGE_EEPROM_DLMS_HDLC_MAX_INFO_LENGTH_RX_ADDR + STORAGE_EEPROM_DLMS_HDLC_MAX_INFO_LENGTH_RX_SIZE)
#define STORAGE_EEPROM_DLMS_HDLC_INTER_OCTET_TIMEOUT_SIZE            (sizeof(uint16_t))

/* Hdlc inactivity_timeout, 0x07C6 */
#define STORAGE_EEPROM_DLMS_HDLC_INACTIVITY_TIMEOUT_ADDR             (STORAGE_EEPROM_DLMS_HDLC_INTER_OCTET_TIMEOUT_ADDR + STORAGE_EEPROM_DLMS_HDLC_INTER_OCTET_TIMEOUT_SIZE)
#define STORAGE_EEPROM_DLMS_HDLC_INACTIVITY_TIMEOUT_SIZE             (sizeof(uint16_t))

/* Hdlc device_address, 0x07C8 */
#define STORAGE_EEPROM_DLMS_HDLC_DEVICE_ADDRESS_ADDR                 (STORAGE_EEPROM_DLMS_HDLC_INACTIVITY_TIMEOUT_ADDR + STORAGE_EEPROM_DLMS_HDLC_INACTIVITY_TIMEOUT_SIZE)
#define STORAGE_EEPROM_DLMS_HDLC_DEVICE_ADDRESS_SIZE                 (sizeof(uint16_t))

/* PADDING */
#define STORAGE_EEPROM_DLMS_COMM_PROFILE_GROUP_END_ADDR (STORAGE_EEPROM_DLMS_HDLC_DEVICE_ADDRESS_ADDR + STORAGE_EEPROM_DLMS_HDLC_DEVICE_ADDRESS_SIZE)
#define STORAGE_EEPROM_DLMS_COMM_PROFILE_GROUP_PADDING (0x0014)

/*--------------------------------------------------------------------------------------*/
/* GROUP: Firmware upgrade  , Address = 0x07DE */
#define STORAGE_EEPROM_DLMS_FIRMWARE_UPGRADE_GROUP (STORAGE_EEPROM_DLMS_COMM_PROFILE_GROUP_END_ADDR + STORAGE_EEPROM_DLMS_COMM_PROFILE_GROUP_PADDING)

/* Img block size, 0x07DE */
#define STORAGE_EEPROM_DLMS_IMG_BLOCK_SIZE_ADDR                      (STORAGE_EEPROM_DLMS_FIRMWARE_UPGRADE_GROUP)
#define STORAGE_EEPROM_DLMS_IMG_BLOCK_SIZE_SIZE                      (sizeof(uint32_t))

/* Img bitstring, 0x07E2 */
#define STORAGE_EEPROM_DLMS_IMG_BITSTRING_ADDR                       (STORAGE_EEPROM_DLMS_IMG_BLOCK_SIZE_ADDR + STORAGE_EEPROM_DLMS_IMG_BLOCK_SIZE_SIZE)
#define STORAGE_EEPROM_DLMS_IMG_BITSTRING_SIZE                       (sizeof(uint8_t) * 512)

/* Img bitstring length, 0x09E2 */
#define STORAGE_EEPROM_DLMS_IMG_BITSTRING_LENGTH_ADDR                (STORAGE_EEPROM_DLMS_IMG_BITSTRING_ADDR + STORAGE_EEPROM_DLMS_IMG_BITSTRING_SIZE)
#define STORAGE_EEPROM_DLMS_IMG_BITSTRING_LENGTH_SIZE                (sizeof(uint16_t))

/* Img status, 0x09E4 */
#define STORAGE_EEPROM_DLMS_IMG_STATUS_ADDR                          (STORAGE_EEPROM_DLMS_IMG_BITSTRING_LENGTH_ADDR + STORAGE_EEPROM_DLMS_IMG_BITSTRING_LENGTH_SIZE)
#define STORAGE_EEPROM_DLMS_IMG_STATUS_SIZE                          (sizeof(uint8_t))

/* Img size, 0x09E5 */
#define STORAGE_EEPROM_DLMS_IMG_SIZE_ADDR                            (STORAGE_EEPROM_DLMS_IMG_STATUS_ADDR + STORAGE_EEPROM_DLMS_IMG_STATUS_SIZE)
#define STORAGE_EEPROM_DLMS_IMG_SIZE_SIZE                            (sizeof(uint32_t))

/* Img identification length, 0x09E9 */
#define STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_LENGTH_ADDR           (STORAGE_EEPROM_DLMS_IMG_SIZE_ADDR + STORAGE_EEPROM_DLMS_IMG_SIZE_SIZE)
#define STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_LENGTH_SIZE           (sizeof(uint16_t))

/* Img identification, 0x09EB */
#define STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_ADDR                  (STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_LENGTH_ADDR + STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_LENGTH_SIZE)
#define STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_SIZE                  (sizeof(uint8_t) * 48)

/* Img signature, 0x0A1B */
#define STORAGE_EEPROM_DLMS_IMG_SIGNATURE_ADDR                       (STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_ADDR + STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_SIZE)
#define STORAGE_EEPROM_DLMS_IMG_SIGNATURE_SIZE                       (sizeof(uint8_t) * 4)

/* PADDING */
#define STORAGE_EEPROM_DLMS_FIRMWARE_UPGRADE_GROUP_END_ADDR (STORAGE_EEPROM_DLMS_IMG_SIGNATURE_ADDR + STORAGE_EEPROM_DLMS_IMG_SIGNATURE_SIZE)
#define STORAGE_EEPROM_DLMS_FIRMWARE_UPGRADE_GROUP_PADDING (0x0010)

/*--------------------------------------------------------------------------------------*/
/* Asosciation secret key , 0x0220 group */
#define STORAGE_EEPROM_DLMS_ASOSCIATION_SECRET_KEY_GROUP     (STORAGE_EEPROM_DLMS_FIRMWARE_UPGRADE_GROUP_END_ADDR + STORAGE_EEPROM_DLMS_FIRMWARE_UPGRADE_GROUP_PADDING)

/* LLS Secret MR len , 0x0220 */
#define STORAGE_EEPROM_DLMS_LLS_SECRET_MR_LEN_ADDR           STORAGE_EEPROM_DLMS_ASOSCIATION_SECRET_KEY_GROUP
#define STORAGE_EEPROM_DLMS_LLS_SECRET_MR_LEN_SIZE           ( sizeof(uint8_t) * 1 )    /* 1 (Bytes) x 1 */

/* LLS Secret MR , 0x0221 */
#define STORAGE_EEPROM_DLMS_LLS_SECRET_MR_ADDR               STORAGE_EEPROM_DLMS_LLS_SECRET_MR_LEN_ADDR + STORAGE_EEPROM_DLMS_LLS_SECRET_MR_LEN_SIZE
#define STORAGE_EEPROM_DLMS_LLS_SECRET_MR_SIZE               ( sizeof(uint8_t) * 16 )    /* 1 (Bytes) x 16 */

/* HLS Key US len , 0x0231 */
#define STORAGE_EEPROM_DLMS_HLS_KEY_US_LEN_ADDR              STORAGE_EEPROM_DLMS_LLS_SECRET_MR_ADDR + STORAGE_EEPROM_DLMS_LLS_SECRET_MR_SIZE
#define STORAGE_EEPROM_DLMS_HLS_KEY_US_LEN_SIZE              ( sizeof(uint8_t) * 1 )    /* 1 (Bytes) x 1 */

/* HLS Key US  , 0x0232 */
#define STORAGE_EEPROM_DLMS_HLS_KEY_US_ADDR                  STORAGE_EEPROM_DLMS_HLS_KEY_US_LEN_ADDR + STORAGE_EEPROM_DLMS_HLS_KEY_US_LEN_SIZE
#define STORAGE_EEPROM_DLMS_HLS_KEY_US_SIZE                  ( sizeof(uint8_t) * 16 )    /* 1 (Bytes) x 16 */

/* HLS Key FW len , 0x0242 */
#define STORAGE_EEPROM_DLMS_HLS_KEY_FW_LEN_ADDR              STORAGE_EEPROM_DLMS_HLS_KEY_US_ADDR + STORAGE_EEPROM_DLMS_HLS_KEY_US_SIZE
#define STORAGE_EEPROM_DLMS_HLS_KEY_FW_LEN_SIZE              ( sizeof(uint8_t) * 1 )    /* 1 (Bytes) x 1 */

/* HLS Key FW , 0x0243 */
#define STORAGE_EEPROM_DLMS_HLS_KEY_FW_ADDR                  STORAGE_EEPROM_DLMS_HLS_KEY_FW_LEN_ADDR + STORAGE_EEPROM_DLMS_HLS_KEY_FW_LEN_SIZE
#define STORAGE_EEPROM_DLMS_HLS_KEY_FW_SIZE                  ( sizeof(uint8_t) * 16 )    /* 1 (Bytes) x 16 */

/* Asso key 3 len , 0x0253 */
#define STORAGE_EEPROM_DLMS_ASSO_KEY_3_LEN_ADDR              STORAGE_EEPROM_DLMS_HLS_KEY_FW_ADDR + STORAGE_EEPROM_DLMS_HLS_KEY_FW_SIZE
#define STORAGE_EEPROM_DLMS_ASSO_KEY_3_LEN_SIZE              ( sizeof(uint8_t) * 1 )    /* 1 (Bytes) x 1 */

/* Asso key 3 , 0x0254 */
#define STORAGE_EEPROM_DLMS_ASSO_KEY_3_ADDR                  STORAGE_EEPROM_DLMS_ASSO_KEY_3_LEN_ADDR + STORAGE_EEPROM_DLMS_ASSO_KEY_3_LEN_SIZE
#define STORAGE_EEPROM_DLMS_ASSO_KEY_3_SIZE                  ( sizeof(uint8_t) * 16 )    /* 1 (Bytes) x 16 */

/* Asso key 4 len , 0x0264 */
#define STORAGE_EEPROM_DLMS_ASSO_KEY_4_LEN_ADDR              STORAGE_EEPROM_DLMS_ASSO_KEY_3_ADDR + STORAGE_EEPROM_DLMS_ASSO_KEY_3_SIZE
#define STORAGE_EEPROM_DLMS_ASSO_KEY_4_LEN_SIZE              ( sizeof(uint8_t) * 1 )    /* 1 (Bytes) x 1 */

/* Asso key 4 , 0x0265 */
#define STORAGE_EEPROM_DLMS_ASSO_KEY_4_ADDR                  STORAGE_EEPROM_DLMS_ASSO_KEY_4_LEN_ADDR + STORAGE_EEPROM_DLMS_ASSO_KEY_4_LEN_SIZE
#define STORAGE_EEPROM_DLMS_ASSO_KEY_4_SIZE                  ( sizeof(uint8_t) * 16 )    /* 1 (Bytes) x 16 */

/*--------------------------------------------------------------------------------------*/
/* HLS key , 0x0286 group */
#define STORAGE_EEPROM_DLMS_HLS_KEY_GROUP            (STORAGE_EEPROM_DLMS_ASSO_KEY_4_ADDR + STORAGE_EEPROM_DLMS_ASSO_KEY_4_SIZE)

/* Master key len , 0x0286 */
#define STORAGE_EEPROM_DLMS_MASTER_KEY_LEN_ADDR              STORAGE_EEPROM_DLMS_HLS_KEY_GROUP
#define STORAGE_EEPROM_DLMS_MASTER_KEY_LEN_SIZE              ( sizeof(uint8_t) * 1 )    /* 1 (Bytes) x 1 */

/* Master key , 0x0287 */
#define STORAGE_EEPROM_DLMS_MASTER_KEY_ADDR                  STORAGE_EEPROM_DLMS_MASTER_KEY_LEN_ADDR + STORAGE_EEPROM_DLMS_MASTER_KEY_LEN_SIZE
#define STORAGE_EEPROM_DLMS_MASTER_KEY_SIZE                  ( sizeof(uint8_t) * 16 )    /* 1 (Bytes) x 16 */

/* Unicast key len , 0x0297 */
#define STORAGE_EEPROM_DLMS_UNICAST_KEY_LEN_ADDR             STORAGE_EEPROM_DLMS_MASTER_KEY_ADDR + STORAGE_EEPROM_DLMS_MASTER_KEY_SIZE
#define STORAGE_EEPROM_DLMS_UNICAST_KEY_LEN_SIZE             ( sizeof(uint8_t) * 1 )    /* 1 (Bytes) x 1 */

/* Unicast key , 0x0298 */
#define STORAGE_EEPROM_DLMS_UNICAST_KEY_ADDR                 STORAGE_EEPROM_DLMS_UNICAST_KEY_LEN_ADDR + STORAGE_EEPROM_DLMS_UNICAST_KEY_LEN_SIZE
#define STORAGE_EEPROM_DLMS_UNICAST_KEY_SIZE                 ( sizeof(uint8_t) * 16 )    /* 1 (Bytes) x 16 */

/* Invocation Counter EK0, 0x0A9E */
#define STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK0_ADDR      STORAGE_EEPROM_DLMS_UNICAST_KEY_ADDR + STORAGE_EEPROM_DLMS_UNICAST_KEY_SIZE
#define STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK0_SIZE      (sizeof(uint32_t) * 2)

/* Broadcast key len , 0x02A8 */
#define STORAGE_EEPROM_DLMS_BROADCAST_KEY_LEN_ADDR           STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK0_ADDR + STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK0_SIZE
#define STORAGE_EEPROM_DLMS_BROADCAST_KEY_LEN_SIZE           ( sizeof(uint8_t) * 1 )    /* 1 (Bytes) x 1 */

/* Broadcast key , 0x02A9 */
#define STORAGE_EEPROM_DLMS_BROADCAST_KEY_ADDR               STORAGE_EEPROM_DLMS_BROADCAST_KEY_LEN_ADDR + STORAGE_EEPROM_DLMS_BROADCAST_KEY_LEN_SIZE
#define STORAGE_EEPROM_DLMS_BROADCAST_KEY_SIZE               ( sizeof(uint8_t) * 16 )    /* 1 (Bytes) x 16 */

/* Invocation Counter EK1, 0x0AA6 */
#define STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK1_ADDR      STORAGE_EEPROM_DLMS_BROADCAST_KEY_ADDR + STORAGE_EEPROM_DLMS_BROADCAST_KEY_SIZE
#define STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK1_SIZE      (sizeof(uint32_t) * 2)

/* Authen key len , 0x02B9 */
#define STORAGE_EEPROM_DLMS_AUTHEN_KEY_LEN_ADDR              STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK1_ADDR + STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK1_SIZE
#define STORAGE_EEPROM_DLMS_AUTHEN_KEY_LEN_SIZE              ( sizeof(uint8_t) * 1 )    /* 1 (Bytes) x 1 */

/* Authen key , 0x02BA */
#define STORAGE_EEPROM_DLMS_AUTHEN_KEY_ADDR                  STORAGE_EEPROM_DLMS_AUTHEN_KEY_LEN_ADDR + STORAGE_EEPROM_DLMS_AUTHEN_KEY_LEN_SIZE
#define STORAGE_EEPROM_DLMS_AUTHEN_KEY_SIZE                  ( sizeof(uint8_t) * 16 )    /* 1 (Bytes) x 16 */

/* Unicast key IHD , 0x02CA */
#define STORAGE_EEPROM_DLMS_UNICAST_KEY_IHD_ADDR             STORAGE_EEPROM_DLMS_AUTHEN_KEY_ADDR + STORAGE_EEPROM_DLMS_AUTHEN_KEY_SIZE
#define STORAGE_EEPROM_DLMS_UNICAST_KEY_IHD_SIZE             ( sizeof(uint8_t) * 16 )    /* 1 (Bytes) x 16 */

/* Unicast key IHD len , 0x02DA */
#define STORAGE_EEPROM_DLMS_UNICAST_KEY_IHD_LEN_ADDR         STORAGE_EEPROM_DLMS_UNICAST_KEY_IHD_ADDR + STORAGE_EEPROM_DLMS_UNICAST_KEY_IHD_SIZE
#define STORAGE_EEPROM_DLMS_UNICAST_KEY_IHD_LEN_SIZE         ( sizeof(uint8_t) * 1 )    /* 1 (Bytes) x 1 */

/* Invocation Counter EK2, 0x0AAE */
#define STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK2_ADDR      STORAGE_EEPROM_DLMS_UNICAST_KEY_IHD_LEN_ADDR + STORAGE_EEPROM_DLMS_UNICAST_KEY_IHD_LEN_SIZE
#define STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK2_SIZE      (sizeof(uint32_t) * 2)

/* Broadcast key IHD len , 0x02DB */
#define STORAGE_EEPROM_DLMS_BROADCAST_KEY_IHD_LEN_ADDR       STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK2_ADDR + STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK2_SIZE
#define STORAGE_EEPROM_DLMS_BROADCAST_KEY_IHD_LEN_SIZE       ( sizeof(uint8_t) * 1 )    /* 1 (Bytes) x 1 */

/* Broadcast key IHD , 0x02DC */
#define STORAGE_EEPROM_DLMS_BROADCAST_KEY_IHD_ADDR           STORAGE_EEPROM_DLMS_BROADCAST_KEY_IHD_LEN_ADDR + STORAGE_EEPROM_DLMS_BROADCAST_KEY_IHD_LEN_SIZE
#define STORAGE_EEPROM_DLMS_BROADCAST_KEY_IHD_SIZE           ( sizeof(uint8_t) * 16 )    /* 1 (Bytes) x 16 */


/* Invocation Counter EK3, 0x0AB6 */
#define STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK3_ADDR      STORAGE_EEPROM_DLMS_BROADCAST_KEY_IHD_ADDR + STORAGE_EEPROM_DLMS_BROADCAST_KEY_IHD_SIZE
#define STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK3_SIZE      (sizeof(uint32_t) * 2)

/* Authen key IHD len , 0x02EC */
#define STORAGE_EEPROM_DLMS_AUTHEN_KEY_IHD_LEN_ADDR          STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK3_ADDR + STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK3_SIZE
#define STORAGE_EEPROM_DLMS_AUTHEN_KEY_IHD_LEN_SIZE          ( sizeof(uint8_t) * 1 )    /* 1 (Bytes) x 1 */

/* Authen key IHD , 0x02ED */
#define STORAGE_EEPROM_DLMS_AUTHEN_KEY_IHD_ADDR              STORAGE_EEPROM_DLMS_AUTHEN_KEY_IHD_LEN_ADDR + STORAGE_EEPROM_DLMS_AUTHEN_KEY_IHD_LEN_SIZE
#define STORAGE_EEPROM_DLMS_AUTHEN_KEY_IHD_SIZE              ( sizeof(uint8_t) * 16 )    /* 1 (Bytes) x 16 */

/* PADDING */
#define STORAGE_EEPROM_DLMS_ASSOCIATION_SECRET_KEY_GROUP_END_ADDR (STORAGE_EEPROM_DLMS_AUTHEN_KEY_IHD_ADDR + STORAGE_EEPROM_DLMS_AUTHEN_KEY_IHD_SIZE)
#define STORAGE_EEPROM_DLMS_ASSOCIATION_SECRET_KEY_GROUP_PADDING (0x000A)
/*--------------------------------------------------------------------------------------*/

#define STORAGE_EEPROM_DLMS_LAST_ADDR                       (STORAGE_EEPROM_DLMS_ASSOCIATION_SECRET_KEY_GROUP_END_ADDR + STORAGE_EEPROM_DLMS_ASSOCIATION_SECRET_KEY_GROUP_PADDING)

/***********************************************************************************************************************
EEPROM BACKUP/RESTORE MACRO
***********************************************************************************************************************/


/***********************************************************************************************************************
DATAFLASH MEMORY MAP
***********************************************************************************************************************/




#endif /* _R_DLMS_STORAGE_MAP_H */
