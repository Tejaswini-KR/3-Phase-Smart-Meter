/***********************************************************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
************************************************************************************************************************
* File Name    : r_dlms_factory_config.h
* Version      : v1.0
* Description  : Factory config for DLMS
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
***********************************************************************************************************************/

#ifndef _R_DLMS_FACTORY_CONFIG_H
#define _R_DLMS_FACTORY_CONFIG_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/* Nameplate default value */

#define METER_FLAG_ID                               "REI"
#define METER_SERIAL_NUMBER_FIRST					"00000000000"				/* First 11 ASCII char */
#define METER_SERIAL_NUMBER_LAST					"00045"						/* Last   5 ASCII char */
#define METER_MANUFACTURE                           "RENESAS ELECTRONICS INDIA PRIVATE LIMITED"
#define METER_CATEGORY                              "D2"
#define METER_CURRENT_RATING                        "5-60A"
#define METER_YEAR_OF_MANUFACTURE                   "2018"
#define METER_FIRMWARE_VERSION                      "V2.0 Ind"

#define METER_SERIAL_NUMBER                         METER_SERIAL_NUMBER_FIRST METER_SERIAL_NUMBER_LAST
#define METER_LOGICAL_DEVICE_NAME                   METER_FLAG_ID METER_SERIAL_NUMBER_LAST                 /* FLAG_ID + Last 5 digits of meter serial number */
#define METER_DEVICE_ID								METER_FLAG_ID METER_SERIAL_NUMBER

#define METER_TYPE                                  (6)  /* 1P a.c. static direct connected Wh smart meter */

#define R_DLMS_TIME_ZONE_DEFAULT                    (330)

#define R_DLMS_ESWF_DEFAULT                         { 0x18, 0x10, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00 }

/* Time Interval between auto-reconnection attempt */
#define TIME_INTERVAL_DEFAULT						(120)			/* 2 (min) */
#define LOCK_OUT_TIME_DEFAULT						(300)

/* Number of Auto reconnection attempts */
#define NO_OF_REPETITIONS_DEFAULT					(4)

#if(defined( R_LOAD_LIMIT_DATA_TYPE ) && R_LOAD_LIMIT_DATA_TYPE == 0)
	/* Integer - kW */ 
	#define LIMITER_THRESHOLD_NORMAL_DEFAULT	        (6)		/* 2 kW */
	#define LIMITER_THRESHOLD_EMERGENCY_DEFAULT	        (6)		/* 2 kW */
#else
	/* Float - W */
	#define LIMITER_THRESHOLD_NORMAL_DEFAULT	        (6600.0f)		/* 6600W */
	#define LIMITER_THRESHOLD_EMERGENCY_DEFAULT	        (6600.0f)		/* 6600W */
#endif /* R_LOAD_LIMIT_DATA_TYPE */

#define LIMITER_DURATION_DEFAULT	                (TIME_INTERVAL_DEFAULT)

#define LOADCTRL_STATE_DEFAULT						(2)
#define LOADCTRL_MODE_DEFAULT						(6)

/* 
 * Relay activation date and time:
 * Format = { 
 *             year_high, year_low, month, day_of_month, day_of_week, 
 * 	           hour, minute, second, hundredths, deviation_high, deviation_low, clock_status 
 * }
 */
#define RELAY_ACTIVATION_DATE_AND_TIME_DEFAULT		{ 0x07, 0xE2, 0x01, 0x01, 0x01, 12 , 34, 56, 0x00, 0x01, 0xA4, 0x00 }

#define DEMAND_INTEGRATION_PERIOD_DEFAULT	        (900)   /* 15 min */
#define BLOCKLOAD_CAPTURE_PERIOD_DEFAULT	        (1800)   /* 30 min */

/* {Sec, Min, Hour, Day, Week, Month, Year (only 2 ending digit)} */
#define BILLING_SCHEDULE_DEFAULT	                { 00,   00,     00,    1, 0xFF, 0xFF, 0xFF}
#define IMG_ACT_SCHEDULE_DEFAULT	                { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
#define PUSH_01_SCHEDULE_DEFAULT	                { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
#define PUSH_02_SCHEDULE_DEFAULT	                { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}


#define PUSH_DESTINATION_SERVICE_DEFAULT	        (PUSH_TRANSPORT_SERVICE_TCP)
#define PUSH_DESTINATION_ADDRESS_DEFAULT	        { 192, 168 , 0, 5 }
#define PUSH_DESTINATION_PORT_DEFAULT	            4059
#define PUSH_NUMBER_OF_RETRIES_DEFAULT				3

/* Default push window: 0h-> 20h */
#define PUSH_WINDOW_START_TIME_DEFAULT				{  00,  00,  00,   0xFF,  0xFF, 0xFF,  0xFF }		/* Sec, Min, Hour, Day, Week, Month, Year */
#define PUSH_WINDOW_END_TIME_DEFAULT				{  00,  00,  20,   0xFF,  0xFF, 0xFF,  0xFF }		/* Sec, Min, Hour, Day, Week, Month, Year */

#define R_DLMS_LLS_SECRET_DEFAULT                   "ABCDEFGH"
#define R_DLMS_HLS_KEY_US_DEFAULT                   "RENESAS_P6wRJ21F"
#define R_DLMS_HLS_KEY_FW_DEFAULT                   "RENESAS_ABCDEFGH"

#define R_DLMS_MASTER_KEY_DEFAULT                   "RES_MasterKeyAll"

#define R_DLMS_SHARED_GUK_DEFAULT                   "RES_UnicastAssc0"
#define R_DLMS_SHARED_GBK_DEFAULT                   "RES_BroadcastKey"
#define R_DLMS_SHARED_AUK_DEFAULT                   "RES_AuthenKey000"

#define R_DLMS_IHD_GUK_DEFAULT                      "RES_UnicastAssc5"
#define R_DLMS_IHD_GBK_DEFAULT                      "RES_BroadKey0005"
#define R_DLMS_IHD_AUK_DEFAULT                      "RES_AuthenKey005"

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/

#endif /* _R_DLMS_FACTORY_CONFIG_H */