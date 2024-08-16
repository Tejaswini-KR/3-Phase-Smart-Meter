/******************************************************************************
Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : event.h
* Version      : 1.00
* Description  : Event Header file
******************************************************************************
* History : DD.MM.YYYY Version Description
******************************************************************************/

#ifndef _EVENT_H
#define _EVENT_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_cg_macrodriver.h"
#include "typedef.h"

#include "em_core.h"                /* EM Core */

#include "r_load_ctrl.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

#if(defined( R_LOAD_CONTROL_ENABLE ) && R_LOAD_CONTROL_ENABLE == TRUE)
#define EVENT_LOAD_CONTROL                  (R_LOAD_CONTROL_ENABLE)
#else
#define EVENT_LOAD_CONTROL                  (FALSE)
#endif

#define EVENT_OK        0
#define EVENT_ERROR     1
/* Define profiles entries for event */
#define VOLTAGE_EVENTS_MAX_ENTRIES          (50)
#define CURRENT_EVENTS_MAX_ENTRIES          (50)
#define POWER_EVENTS_MAX_ENTRIES            (20)
#define TRANS_EVENTS_MAX_ENTRIES            (50)
#define OTHER_EVENTS_MAX_ENTRIES            (50)
#define NON_ROLLOVER_EVENTS_MAX_ENTRIES     (1)
#define CONTROL_EVENTS_MAX_ENTRIES          (50)
/******************************************************************
 * Event ID definition
 ******************************************************************/
/* 3 phase meter */
/* Voltage Related */
#define EVENT_ID_UR_MISSING_OCCURRENCE                                              (1)
#define EVENT_ID_UR_MISSING_RESTORATION                                             (2)
#define EVENT_ID_UY_MISSING_OCCURRENCE                                              (3)
#define EVENT_ID_UY_MISSING_RESTORATION                                             (4)
#define EVENT_ID_UB_MISSING_OCCURRENCE                                              (5)
#define EVENT_ID_UB_MISSING_RESTORATION                                             (6)

#define EVENT_ID_OVERVOLTAGE_OCCURRENCE                                             (7)
#define EVENT_ID_OVERVOLTAGE_RESTORATION                                            (8)
#define EVENT_ID_LOW_VOLTAGE_OCCURRENCE                                             (9)
#define EVENT_ID_LOW_VOLTAGE_RESTORATION                                            (10)
#define EVENT_ID_VOLTAGE_UNBALANCE_OCCURRENCE                                       (11)
#define EVENT_ID_VOLTAGE_UNBALANCE_RESTORATION                                      (12)

/* Current Related */
#define EVENT_ID_IR_REVERSE_OCCURRENCE                                              (51)
#define EVENT_ID_IR_REVERSE_RESTORATION                                             (52)
#define EVENT_ID_IY_REVERSE_OCCURRENCE                                              (53)
#define EVENT_ID_IY_REVERSE_RESTORATION                                             (54)
#define EVENT_ID_IB_REVERSE_OCCURRENCE                                              (55)
#define EVENT_ID_IB_REVERSE_RESTORATION                                             (56)

#define EVENT_ID_CURRENT_UNBALANCE_OCCURRENCE                                       (63)
#define EVENT_ID_CURRENT_UNBALANCE_RESTORATION                                      (64)
#define EVENT_ID_CURRENT_BYPASS_OCCURRENCE                                          (65)
#define EVENT_ID_CURRENT_BYPASS_RESTORATION                                         (66)
#define EVENT_ID_OVER_CURRENT_OCCURRENCE                                            (67)
#define EVENT_ID_OVER_CURRENT_RESTORATION                                           (68)

/* Power Related */
#define EVENT_ID_POWER_FAILURE_OCCURRENCE                                           (101)
#define EVENT_ID_POWER_FAILURE_RESTORATION                                          (102)

/* Transaction Related */
#define EVENT_ID_REAL_TIME_CLOCK_DATE_AND_TIME                                      (151)
#define EVENT_ID_DEMAND_INTEGRATION_PERIOD                                          (152)
#define EVENT_ID_PROFILE_CAPTURE_PERIOD                                             (153)
#define EVENT_ID_SINGLEACTION_SCHEDULE_FOR_BILLING_DATES                            (154)
#define EVENT_ID_ACTIVITY_CALENDAR_FOR_TIME_ZONES                                   (155)
#define EVENT_ID_NEW_FIRMWARE_ACTIVATED                                             (157)
#define EVENT_ID_LOAD_LIMIT_KW_SET                                                  (158)
#define EVENT_ID_ENABLED_LOAD_LIMIT_FUNCTION                                        (159)
#define EVENT_ID_DISABLED_LOAD_LIMIT_FUNCTION                                       (160)
#define EVENT_ID_LLS_SECRET_MR_CHANGE                                               (161)
#define EVENT_ID_HLS_KEY_US_CHANGE                                                  (162)
#define EVENT_ID_HLS_KEY_FW_CHANGE                                                  (163)
#define EVENT_ID_GLOBAL_KEY_CHANGE                                                  (164)
#define EVENT_ID_ESWFCHANGE                                                         (165)
#define EVENT_ID_MD_RESET                                                           (166)
#define EVENT_ID_PASSIVE_RELAY_TIME													(182)

/* Others */
#define EVENT_ID_INFLUENCE_OF_PERMANENT_MAGNET_OR_ACDC_ELECTROMAGNET_OCCURRENCE     (201)
#define EVENT_ID_INFLUENCE_OF_PERMANENT_MAGNET_OR_ACDC_ELECTROMAGNET_RESTORATION    (202)
#define EVENT_ID_NEUTRAL_DISTURBANCE_HF_AND_DC_OCCURRENCE                           (203)
#define EVENT_ID_NEUTRAL_DISTURBANCE_HF_AND_DC_RESTORATION                          (204)
#define EVENT_ID_VERY_LOW_PF_OCCURRENCE                                             (205)
#define EVENT_ID_VERY_LOW_PF_RESTORATION                                            (206)
#define EVENT_ID_NEUTRAL_MISSING_OCCURRENCE                                         (207)
#define EVENT_ID_NEUTRAL_MISSING_RESTORATION                                        (208)
#define EVENT_ID_PLUG_IN_COMM_MODULE_REMOVAL_OCCURRENCE                             (209)
#define EVENT_ID_PLUG_IN_COMM_MODULE_REMOVAL_RESTORATION                            (210)
#define EVENT_ID_POSTPAID_MODE                                                      (211)
#define EVENT_ID_PREPAID_MODE                                                       (212)
#define EVENT_ID_FORWARDED_ONLY_MODE                                                (213)
#define EVENT_ID_IMPORT_AND_EXPORT_MODE                                             (214)
#define EVENT_ID_OVERLOAD_OCCURRENCE                                                (215)
#define EVENT_ID_OVERLOAD_RESTORATION                                               (216)

/* Non-rollover Events */
#define EVENT_ID_METER_COVER_OPENING_OCCURRENCE                                     (251)

/* Control Events */
#define EVENT_ID_LOAD_SWITCH_STATUS_DISCONNECTED_OCCURRENCE                         (301)
#define EVENT_ID_LOAD_SWITCH_STATUS_CONNECTED_OCCURRENCE                            (302)

/* ID = Not specified */
#define EVENT_ID_LAST_GASP_OCCURRENCE                                               (0xFFFF)
#define EVENT_ID_LAST_GASP_RESTORATION                                              (0xFFFF)
#define EVENT_ID_FIRST_BREATH_OCCURENCE                                             (0xFFFF)
#define EVENT_ID_FIRST_BREATH_RESTORATION                                           (0xFFFF)
#define EVENT_ID_INCREASE_BILLING_COUNTER                                           (0xFFFF)

/******************************************************************
 * Event Status Bit definition
 ******************************************************************/
// Bit 255 		: Not push
// Bit 1-127	: Event bit

/* Three phase meter */
#define R_EVENT_BIT_R_PHASE_VOLTAGE_MISSING_FOR_3_PHASE_METER                       (0)
#define R_EVENT_BIT_Y_PHASE_VOLTAGE_MISSING                                         (1)
#define R_EVENT_BIT_B_PHASE_VOLTAGE_MISSING                                         (2)
#define R_EVENT_BIT_OVER_VOLTAGE_IN_ANY_PHASE                                       (3)
#define R_EVENT_BIT_LOW_VOLTAGE_IN_ANY_PHASE                                        (4)
#define R_EVENT_BIT_VOLTAGE_UNBALANCE                                               (5)
#define R_EVENT_BIT_R_PHASE_CURRENT_REVERSE                                         (6)
#define R_EVENT_BIT_Y_PHASE_CURRENT_REVERSE                                         (7)
#define R_EVENT_BIT_B_PHASE_CURRENT_REVERSE                                         (8)
#define R_EVENT_BIT_CURRENT_UNBALANCE                                               (9)
#define R_EVENT_BIT_CURRENT_BYPASS_SHORT                                            (10)
#define R_EVENT_BIT_OVER_CURRENT_IN_ANY_PHASE                                       (11)
#define R_EVENT_BIT_VERY_LOW_PF                                                     (12)

/* Common to 3 Phase and single phase meter */
#define R_EVENT_BIT_MAGNET                                                          (81)
#define R_EVENT_BIT_NEUTRAL_DISTURBANCE_DC                                          (82)
#define R_EVENT_BIT_METER_COVER_OPENING                                             (83)
#define R_EVENT_BIT_METER_LOAD_DISCONNECTED_CONNECTED                               (84)
#define R_EVENT_BIT_LAST_GASP                                                       (85)
#define R_EVENT_BIT_FIRST_BREATH                                                    (86)
#define R_EVENT_BIT_INCREASE_IN_BILLING_COUNTER                                     (87)

#define R_EVENT_BIT_CURRENT_REVERSE                                                 (255)   // 255: not push current reverse event, 6: Push current reverse event.

/* Event tamper configuration */
#define EVENT_TAMPER_MAGNET_ENERGY_UPDATE_MODE                                      (EVENT_TAMPER_UPDATE_BY_SPECIFIED_POWER)
#define EVENT_TAMPER_CASE_OPEN_ENERGY_UPDATE_MODE                                   (EVENT_TAMPER_UPDATE_BY_SPECIFIED_POWER)
#define EVENT_TAMPER_DC_DETECTION_ENERGY_UPDATE_MODE                                (EVENT_TAMPER_UPDATE_NORMAL)
	
#define EVENT_TAMPER_MAGNET_SPECIFIED_POWER                                         (6600.0f)
#define EVENT_TAMPER_CASE_OPEN_SPECIFIED_POWER                                      (13200.0f)
#define EVENT_TAMPER_DC_DETECTION_SPECIFIED_POWER                                   (9900.0f)

/* Event config*/
#define EVENT_CONFIG_LOW_VOLTAGE_THRESHOLD                     (170.0f)
#define EVENT_CONFIG_OVER_VOLTAGE_THRESHOLD                    (280.0f)
#define EVENT_CONFIG_OVER_CURRENT_THRESHOLD                    (50.0f)
#define EVENT_CONFIG_FREQ_LOW_THRESHOLD                        (47.5f)
#define EVENT_CONFIG_FREQ_HIGH_THRESHOLD                       (52.5f)
#define EVENT_CONFIG_PF_LOW_THRESHOLD                          (0.5f)
//#define EVENT_CONFIG_OVERLOAD_THRESHOLD                                             (12000)   // Configured by external applications
#define EVENT_CONFIG_VOLTAGE_UNBALANCE_THRESHOLD               (0.005f)    /* Ratio of compare voltage line to difference of next voltage line */
#define EVENT_CONFIG_IVECTOR_RMS_UNBALANCE_THRESHOLD           (0.05f)     /* RMS Min Threshold for IVector to determine Current Unbalance */
#define EVENT_CONFIG_CURRENT_BYPASS_THRESHOLD                  (0.025f)    /* Start check when greater than 25mA */

#define EVENT_CONFIG_VRMS_AVERAGE_THRESHOLD                    (75.0f)

// Calculate & store energy of DG in separate registers
#define ENERGY_ENABLE_DG_ENERGY

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef enum tag_EVENT_TYPE_T
{
    EVENT_TYPE_VOLTAGE_RELATED,
    EVENT_TYPE_CURRENT_RELATED,
    EVENT_TYPE_POWER_RELATED,
    EVENT_TYPE_TRANSACTION_RELATED,
    EVENT_TYPE_OTHERS,
    EVENT_TYPE_NON_ROLLOVER_EVENTS,
    EVENT_TYPE_CONTROL_EVENTS,
	EVENT_TYPE_UNSPECIFIED = 0xFA,
	EVENT_TYPE_NOT_APPLICABLE = 0xFE,
	EVENT_TYPE_UNKNOWN = 0xFF
} EVENT_TYPE_T;

#define LAST_EVENT_TYPE         (EVENT_TYPE_CONTROL_EVENTS)

typedef enum tagEventStateType
{
    EVENT_STATE_RELEASE,    /* Release state */
    EVENT_STATE_ENTER,      /* Enter state */
} EVENT_STATE_T;

typedef enum tagEventType
{   
    NONE_NAME = 0,
    EVENT_VOLTAGE_MISSING_R,
    EVENT_VOLTAGE_MISSING_Y,
    EVENT_VOLTAGE_MISSING_B,
    EVENT_OVER_VOLTAGE,
    EVENT_LOW_VOLTAGE,
    EVENT_VOLTAGE_UNBALANCE,
    EVENT_CURRENT_REVERSE_R,
    EVENT_CURRENT_REVERSE_Y,
    EVENT_CURRENT_REVERSE_B,
    EVENT_CURRENT_UNBALANCE,
    EVENT_CURRENT_BYPASS,
    EVENT_OVER_CURRENT,
    EVENT_POWER_FAILED,
    EVENT_MAGNET,
    EVENT_DC_DETECTED,
    EVENT_LOW_PF,
    EVENT_OVERLOAD,
    EVENT_CASE_OPEN,
    EVENT_FREQ_OUT_RANGE,

} EVENT_NAME_T;

/* Event state */
typedef struct tagEventOneEventTick
{
    uint8_t occurred_count;
    uint8_t restored_count;
    EVENT_STATE_T current_state;

} EVENT_ONE_EVENT_TICK;

typedef struct tageEventOneEventNoTick
{
    EVENT_STATE_T current_state;

} EVENT_ONE_EVENT_NOTICK;

typedef struct tagEventTick
{
    /* Voltage */
    EVENT_ONE_EVENT_TICK voltage_missing_R ;    /* Voltage Missing R phase */
    EVENT_ONE_EVENT_TICK voltage_missing_Y ;    /* Voltage Missing Y phase */
    EVENT_ONE_EVENT_TICK voltage_missing_B ;    /* Voltage Missing B phase */

    EVENT_ONE_EVENT_TICK over_voltage;          /* Over Voltage */
    EVENT_ONE_EVENT_TICK low_voltage;           /* Low Voltage */
    EVENT_ONE_EVENT_TICK voltage_unbalance;     /* Voltage Unbalance */

    /* Current */
    EVENT_ONE_EVENT_TICK current_reverse_R;     /* Current Reverse R phase */
    EVENT_ONE_EVENT_TICK current_reverse_Y;     /* Current Reverse Y phase */
    EVENT_ONE_EVENT_TICK current_reverse_B;     /* Current Reverse B phase */
    
    EVENT_ONE_EVENT_TICK current_unbalance;     /* Current Unbalance */
    EVENT_ONE_EVENT_TICK current_bypass;        /* Current Bypass */
    EVENT_ONE_EVENT_TICK over_current;          /* Over Current */

    /* Power management */
    EVENT_ONE_EVENT_NOTICK power_failed;        /* Power Failures */
	
    /* Others */
    EVENT_ONE_EVENT_TICK magnet;                /* Magnetic */
    EVENT_ONE_EVENT_TICK dc_detected;           /* DC detection */
    EVENT_ONE_EVENT_TICK low_pf;                /* Low power factor */
    EVENT_ONE_EVENT_NOTICK paid_mode;           /* Paid mode */
    EVENT_ONE_EVENT_NOTICK meter_mode;          /* Forwarded only mode/Import and Export mode */
    EVENT_ONE_EVENT_TICK overload;              /* Overload */
    EVENT_ONE_EVENT_TICK comm_module;           /* Comm module removal */

    /* Non rollover */
    EVENT_ONE_EVENT_TICK case_open;             /* Case open */
    
    /* Control */
    EVENT_ONE_EVENT_TICK relay_status;          /* Relay Disc/Reconnect */

    EVENT_ONE_EVENT_TICK freq_out_range;        /* Frequency out of range */
    EVENT_ONE_EVENT_NOTICK rtc_failed;          /* RTC battery failed */


} EVENT_INFO;

/* Event flag */
typedef union tagEventFlag
{
    struct tagEventFlag_bit
    {   
        /* ENERGY monitoring */
        /* Voltage */
        uint8_t is_voltage_missing_R    :1;         /* Voltage Missing */
        uint8_t is_voltage_missing_Y    :1;         /* Voltage Missing */
        uint8_t is_voltage_missing_B    :1;         /* Voltage Missing */

        uint8_t is_over_voltage         :1;         /* Over Voltage */
        uint8_t is_low_voltage          :1;         /* Low Voltage */
        uint8_t is_voltage_unbalance    :1;         /* Voltage Unbalance */

        /* Current */
        uint8_t is_current_reverse_R    :1;         /* Current Reverse */
        uint8_t is_current_reverse_Y    :1;         /* Current Reverse */
        uint8_t is_current_reverse_B    :1;         /* Current Reverse */

        uint8_t is_current_unbalance    :1;         /* Current Unbalance */
        uint8_t is_current_bypass       :1;         /* Current Bypass */
        uint8_t is_over_current         :1;         /* Over Current */

        /* Power management */
        uint8_t is_power_failed         :1;         /* Power Failures */
		
        /* Transaction */
        uint8_t set_rtc                 :1;         /* Set RTC */
        uint8_t set_dip                 :1;         /* Set Demand Integration Period */
        uint8_t set_pcp                 :1;         /* Set Profile Capture Period */
        uint8_t set_billing_dates       :1;         /* Set SAS for Billing Dates */
        uint8_t md_reset                :1;         /* MD reset */

        /* Others */
        uint8_t is_magnet               :1;         /* Magnetic */
        uint8_t is_dc_detected          :1;         /* DC detection */
        uint8_t is_low_pf               :1;         /* Low power factor */
        uint8_t paid_mode               :1;         /* Paid mode */
        uint8_t meter_mode              :1;         /* Forwarded only mode/Import and Export mode */
        uint8_t is_overload             :1;         /* Overload */

        /* Non rollover */
        uint8_t is_case_open            :1;         /* Case open */

        uint8_t bill_counter            :1;         /* Increase in billing counter */

        /* Transaction */
        uint8_t set_calendar            :1;         /* Set Activity  Calendar for Timezones */
        uint8_t fw_activated            :1;         /* New firmware activated */
        uint8_t set_loadlimit           :1;         /* Load limit (kW) set */
        uint8_t enb_loadlimit_fn        :1;         /* Enabled load limit function */
        uint8_t dis_loadlimit_fn        :1;         /* Disabled load limit function */
        uint8_t set_lls                 :1;         /* LLS secret (MR) change */
        uint8_t set_hls_us              :1;         /* HLS secret (US) change */
        uint8_t set_hls_fw              :1;         /* HLS secret (FW) change */
        uint8_t set_global_key          :1;         /* Global key change */
        uint8_t set_eswf                :1;         /* ESWF change */
        
        /* Others */
        uint8_t comm_module             :1;         /* Comm module removal */

        /* Control */
        uint8_t relay_status_changed    :1;         /* Relay Disc/Reconnect*/
    
		
    } bits ;

    uint64_t value;

} EVENT_FLAG;

typedef struct tagEventRequestFlag
{
    uint16_t is_fw_activation       :1;     /* Firmware Activation */
    uint16_t is_max_demand_end      :1;     /* Max demand */
    uint16_t is_tariff_changed      :1;     /* Tariff changed */
    uint16_t is_lcd_refresh         :1;     /* LCD refresh */
    uint16_t is_lcd_scroll          :1;     /* LCD scroll next */
    uint16_t is_billing_request     :1;     /* Billing request */
    uint16_t is_blockload_request   :1;     /* Blockload request */
    uint16_t is_relay_switch        :1;     /* Relay switch */
    uint16_t event_alert            :1;     /* Event Alert */
    uint16_t periodic_msg_1         :1;     /* Periodic message 1 */
    uint16_t periodic_msg_2         :1;     /* Periodic message 2 */    
    uint16_t is_cal_active_req      :1;     /* Activity Calendar activation*/
    uint16_t is_rtc_failed          :1;     /* RTC battery failed */
    uint16_t is_freq_out_range      :1;     /* Frequency out of range */
    uint16_t is_dailyload_request   :1;     /* Daily load request */
    uint16_t is_rtc_revert          :1;
    uint16_t is_rtc_forward         :1;
	
	uint16_t act_cal_season_change         :1;     /* Activity calendar change */
    uint16_t act_cal_week_profile_change   :1;      /* Update week profile */
	
    uint16_t min_interval           :1;     /* 1 minute interval to count meter power on duration */
    
} EVENT_REQUEST_FLAG;

typedef struct tagEventPersistentTime
{
    /* EM */
    /* Voltage */
    uint8_t     voltage_missing_R_occur;        /* Voltage Missing R phase Occurred*/
    uint8_t     voltage_missing_R_restore;      /* Voltage Missing R phase Restored*/
    uint8_t     voltage_missing_Y_occur;        /* Voltage Missing Y phase Occurred*/
    uint8_t     voltage_missing_Y_restore;      /* Voltage Missing Y phase Restored*/
    uint8_t     voltage_missing_B_occur;        /* Voltage Missing B phase Occurred*/
    uint8_t     voltage_missing_B_restore;      /* Voltage Missing B phase Restored*/

    uint8_t     over_voltage_occur;             /* Over Voltage Occurred*/
    uint8_t     over_voltage_restore;           /* Over Voltage Restored*/
    uint8_t     low_voltage_occur;              /* Low Voltage Occurred */
    uint8_t     low_voltage_restore;            /* Low Voltage Restored*/
    uint8_t     voltage_unbalance_occur;        /* Voltage Unbalance Occurred*/
    uint8_t     voltage_unbalance_restore;      /* Voltage Unbalance Restored*/

    /* Current */
    uint8_t     current_reverse_R_occur;        /* Current Reverse R phase Occurred */
    uint8_t     current_reverse_R_restore;      /* Current Reverse R phase Restored*/
    uint8_t     current_reverse_Y_occur;        /* Current Reverse Y phase Occurred */
    uint8_t     current_reverse_Y_restore;      /* Current Reverse Y phase Restored*/   
    uint8_t     current_reverse_B_occur;        /* Current Reverse B phase Occurred */
    uint8_t     current_reverse_B_restore;      /* Current Reverse B phase Restored*/    
    uint8_t     current_unbalance_occur;        /* Current Unbalance Occurred*/
    uint8_t     current_unbalance_restore;      /* Current Unbalance Restored*/
    uint8_t     current_bypass_occur;           /* Current By Pass Occurred*/
    uint8_t     current_bypass_restore;         /* Current By Pass Restored*/
    uint8_t     over_current_occur;             /* Over Current Occurred*/
    uint8_t     over_current_restore;           /* Over Current Restored*/

    /* Power management */
    uint8_t     power_fail;                     /* Power Failures Occurred */
    uint8_t     power_restore;                  /* Power Failures Restored*/

    /* Others */
    uint8_t     magnet_occur;                   /* Magnetic Occurred*/
    uint8_t     magnet_restore;                 /* Magnetic Restored*/
    uint8_t     dc_occur;                       /* DC detection Occurred*/
    uint8_t     dc_restore;                     /* DC detection Restored*/
    uint8_t     low_power_pf_occur;             /* Low power factor Occurred*/
    uint8_t     low_power_pf_restore;           /* Low power factor Restored*/
    uint8_t     overload_occur;                 /* Overload Occurred*/
    uint8_t     overload_restore;               /* Overload Restored*/
    
    /* Non rollover */
    uint8_t     case_open;                      /* Case open Occurred*/
    uint8_t     freq_out_range;                 /* Frequency out of range Occurred */
    
} EVENT_PERSISTENT_TIME;

typedef struct tagRelayPersistentTime
{
    /* EM */
    /* ENERGY monitoring */
    uint8_t   relay_disc;                   /* Relay Disconnect */
    uint8_t   relay_reconn;                 /* Relay Reconnect */
    
} RELAY_PERSISTENT_TIME;

typedef struct tagEventDateTime
{
    uint8_t Sec;       /* Second */
    uint8_t Min;       /* Minute */
    uint8_t Hour;      /* Hour */
    uint8_t Day;       /* Day */
    uint8_t Week;      /* Day of week */
    uint8_t Month;     /* Month */
    uint16_t Year;     /* Year */

} EVENT_DATE_TIME_T;

typedef uint16_t EVENT_ID_T;

typedef struct tagEventParametersSnapshotShort
{
    EVENT_DATE_TIME_T captured_time;
    EVENT_ID_T code;

} EVENT_PARAMS_SHORT_T;

typedef struct tagEventParametersSnapshot
{
    EVENT_DATE_TIME_T captured_time;
    EVENT_ID_T code;

    float32_t IR;
    float32_t IY;
    float32_t IB;

    float32_t VRN;
    float32_t VYN;
    float32_t VBN;

    float32_t PF_R;
    float32_t PF_Y;
    float32_t PF_B;

    float32_t ActiveEnergyImport;
    float32_t ActiveEnergyExport;

    uint32_t TamperCounter;

} EVENT_PARAMS_T;

typedef struct tagEVENT_ARGS_T
{
    EVENT_TYPE_T type;
    EVENT_STATE_T status;
    uint8_t esw_bit_number;    /*Event Status Word bit number*/
    EVENT_PARAMS_T data;

} EVENT_ARGS_T;

typedef struct tagEventTableConfig_t
{
    uint32_t TableStartAddr;
    uint32_t MaxEntries;
    uint8_t  IsRollover;
    uint8_t  LogSize;

} EventTableConfig_t;

typedef struct tagEventTableHeader_t
{
    uint16_t StartPosition;
    uint16_t EntriesInUse;

}EventTableHeader_t;

typedef enum e_r_event_tamper_update_mode
{
    EVENT_TAMPER_UPDATE_NORMAL,
    EVENT_TAMPER_UPDATE_BY_SPECIFIED_POWER,
} r_event_tamper_update_mode;

typedef void(*EVENT_PLUGIN_CALLBACK)  (EVENT_ARGS_T *);
/******************************************************************************
Variable Externs
******************************************************************************/
extern EVENT_INFO g_event_state;
extern EVENT_FLAG  g_event_flag;
extern EVENT_REQUEST_FLAG g_event_request_flag;
extern EVENT_ARGS_T  EventArgs;
extern uint32_t    g_tamper_counter;
extern uint32_t g_powerfailure_counter;
extern EVENT_PERSISTENT_TIME g_event_persistent_time;
extern RELAY_PERSISTENT_TIME g_relay_persistent_time;
/******************************************************************************
Functions Prototypes
*****************************************************************************/
/*
* DLMS Obis data linkage
*/
/* Class 07 */
uint8_t R_EVENT_EntriesInUseGet(EVENT_TYPE_T event_type, uint32_t * p_data_out);
uint8_t R_EVENT_ProfileEntriesGet(EVENT_TYPE_T event_type, uint32_t * p_data_out);
uint8_t R_EVENT_ResetLog(EVENT_TYPE_T event_type);
EVENT_PARAMS_T R_EVENT_GetEntry(EVENT_TYPE_T EventType, uint16_t EntryIndex);

/* Call to this API to register all event callback */
uint8_t EVENT_Init(void);

uint8_t EVENT_StorageFormat(void);
uint8_t EVENT_StorageRestore(void);
uint8_t EVENT_StorageBackup(void);

void EVENT_Detector(void);
void EVENT_Logging(void);
void EVENT_Distributor(void);
void EVENT_StorageWrite(EVENT_ARGS_T * pEventArgs);

void EVENT_AccumulateTamperCounter(EVENT_ARGS_T *pEventArgs);
void EVENT_CheckAndTriggerTamperEnergyAccumulation(void);
/* Call to this API on while loop of main() */

void EVENT_PollingProcessing(void);

/* Event acknowledgement functions */
uint8_t EVENT_IsAllEventProcessed(void);

uint8_t EVENT_IsCurrentReverse_R(void);
uint8_t EVENT_IsCurrentReverse_Y(void);
uint8_t EVENT_IsCurrentReverse_B(void);

uint8_t EVENT_IsCaseOpen(void);
uint8_t EVENT_IsMagnetic(void);
uint8_t EVENT_IsLastGasp(void);


/* Event callback */
void EVENT_PowerFail(EVENT_STATE_T state);
void EVENT_CaseOpen(EVENT_STATE_T state);
void EVENT_PowerOn(void);

float32_t EVENT_GetOverLoadThreshold(void);
void      EVENT_SetOverLoadThreshold(float32_t value);

void EVENT_RegisterPluginCallback(uint8_t slot, EVENT_PLUGIN_CALLBACK p_fn_callback);
void EVENT_ForwardToPluginFn(EVENT_ARGS_T *pEvent_arg);



#endif /* _EVENT_H */

