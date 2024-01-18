/******************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : em_type.h
* Version      : 1.00
* Description  : EM Core Type Definitions
******************************************************************************
* History : DD.MM.YYYY Version Description
******************************************************************************/

#ifndef _EM_TYPE_H
#define _EM_TYPE_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "compiler.h"
#include "typedef.h"        /* GSCE Standard Typedef */
#include "em_constraint.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define EM_SW_SAMP_TYPE                                 int32_t                                 /* Sampling Data Type */

/******************************************************************************
Typedef definitions
******************************************************************************/
/* EM Wire Selection */
typedef enum tagEMLine
{
    LINE_PHASE_R = 0,
    LINE_PHASE_Y,
    LINE_PHASE_B,
    LINE_NEUTRAL,
    LINE_TOTAL,
} EM_LINE;

/* Fundamental sequence definition */
typedef enum tagEMFundSequence
{
    EM_SW_FUND_SEQUENCE_PHASE_R    = 1,
    EM_SW_FUND_SEQUENCE_PHASE_Y    = 2,
    EM_SW_FUND_SEQUENCE_PHASE_B    = 4,
    EM_SW_FUND_SEQUENCE_PHASE_ALL  = 8,
} EM_FUND_SEQUENCE;

typedef enum tagEMPFSign
{
    PF_SIGN_LEAD_C  = -1,       /* Lead, C */
    PF_SIGN_UNITY   = 0,        /* Unity */
    PF_SIGN_LAG_L   = 1     /* Lag, L */
} EM_PF_SIGN;

/* EM Status */
typedef struct tagEMStatus
{
    uint16_t   noload_active_R             :1;     /* Active No-Load status */
    uint16_t   noload_active_Y             :1;     /* Active No-Load status */
    uint16_t   noload_active_B             :1;     /* Active No-Load status */
    uint16_t   noload_reactive_R           :1;     /* Reactive No-Load status */
    uint16_t   noload_reactive_Y           :1;     /* Reactive No-Load status */
    uint16_t   noload_reactive_B           :1;     /* Reactive No-Load status */
    uint16_t   voltage_sag_R               :1;     /* Voltage sag */
    uint16_t   voltage_sag_Y               :1;     /* Voltage sag */
    uint16_t   voltage_sag_B               :1;     /* Voltage sag */
    uint16_t   voltage_swell_R             :1;     /* Voltage swell */
    uint16_t   voltage_swell_Y             :1;     /* Voltage swell */
    uint16_t   voltage_swell_B             :1;     /* Voltage swell */

} EM_STATUS;

/* EM Energy Counter */
typedef struct tagEMEnergyCounter
{
    uint64_t active_imp;
    uint64_t active_exp;
    uint64_t reactive_ind_imp;
    uint64_t reactive_ind_exp;
    uint64_t reactive_cap_imp;
    uint64_t reactive_cap_exp;
    uint64_t apparent_imp;
    uint64_t apparent_exp;
} EM_ENERGY_COUNTER;

typedef struct tagEMEnergyValue
{
    struct {
        uint64_t active_imp;
        uint64_t active_exp;
        uint64_t reactive_ind_imp;
        uint64_t reactive_ind_exp;
        uint64_t reactive_cap_imp;
        uint64_t reactive_cap_exp;
        uint64_t apparent_imp;
        uint64_t apparent_exp;
    } integer;
    
    struct {
        float32_t active_imp;
        float32_t active_exp;
        float32_t reactive_ind_imp;
        float32_t reactive_ind_exp;
        float32_t reactive_cap_imp;
        float32_t reactive_cap_exp;
        float32_t apparent_imp;
        float32_t apparent_exp;
    } decimal;
} EM_ENERGY_VALUE;

/* EM Platform Property
 * (Can NOT change in run-time, select ONCE and then FIXED) */
typedef struct tagEMPlatformProperty
{
    uint8_t                 target_ac_source_frequency;         /* Target AC Source frequency (50Hz or 60Hz) */
    uint8_t                 reserved;                           /* No use */
    
} EM_PLATFORM_PROPERTY;


/* EM Calibration Informations
 * (Can change in run-time) */
typedef struct tagEMCalibrationCoeffPhase
{   
    /* Co-efficient (Used for both HW Support & SW Support) */
    /* RMS Co-efficient */
    float32_t   vrms;               /* VRMS Co-efficient */
    float32_t   irms;               /* IRMS Co-efficient - Phase Current Co-efficient */
    
    /* Power Co-efficient (for phase line) */
    float32_t   active_power;       /* Active power co-efficient */
    float32_t   reactive_power;     /* Reactive power co-efficient */
    float32_t   apparent_power;     /* Apparent power co-efficient */
    
} EM_CALIB_COEFF_PHASE;

typedef struct tagEMCalibrationCoeffNeutral
{   
    float32_t   irms;               /* IRMS Co-efficient - Phase Current Co-efficient */
    
} EM_CALIB_COEFF_NEUTRAL;

typedef struct tagEMCalibPhaseCorrection
{
    float32_t FAR_PTR *i_phase_degrees;    /* I Phase Angle Degree List */
    
} EM_CALIB_PHASE;

typedef struct tagEMCalibGain
{
    float32_t FAR_PTR *i_gain_values;      /* I Gain Value List */

} EM_CALIB_GAIN;

typedef struct tagEMCalibration
{
    float32_t       sampling_frequency; /* Actual sampling frequency of the meter */

    struct
    {
        EM_CALIB_COEFF_PHASE    phase_r;
        EM_CALIB_COEFF_PHASE    phase_y;
        EM_CALIB_COEFF_PHASE    phase_b;
        EM_CALIB_COEFF_NEUTRAL  neutral;
    } coeff;
    
    struct
    {
        EM_CALIB_PHASE  phase_r;
        EM_CALIB_PHASE  phase_y;
        EM_CALIB_PHASE  phase_b;
    } sw_phase_correction;
    
    struct
    {
        EM_CALIB_GAIN   phase_r;
        EM_CALIB_GAIN   phase_y;
        EM_CALIB_GAIN   phase_b;
        
    }  sw_gain;
    
    
} EM_CALIBRATION;       /* EM Calibration Informations */

/* EM System State */
typedef enum tagEMSystemState
{
    SYSTEM_STATE_UNINITIALIZED = 0,     /* Uninitialized */
    SYSTEM_STATE_INITIALIZED,           /* Initialized */
    SYSTEM_STATE_RUNNING                /* Running */
} EM_SYSTEM_STATE;  /* EM System State */

typedef struct tagEMSamples
{
    /* Phase_R */
    struct
    {
        EM_SW_SAMP_TYPE     i;              /* Current */
        EM_SW_SAMP_TYPE     v;              /* Voltage */
        EM_SW_SAMP_TYPE     v90;            /* Voltage 90 degree phase shift */
        EM_SW_SAMP_TYPE     i_fund;         /* Filtered current for fundamental calculation */
        EM_SW_SAMP_TYPE     v_fund;         /* Filtered voltage for fundamental calculation */
        
    } phase_r;
    
    /* Phase_Y */
    struct
    {
        EM_SW_SAMP_TYPE     i;              /* Current */
        EM_SW_SAMP_TYPE     v;              /* Voltage */
        EM_SW_SAMP_TYPE     v90;            /* Voltage 90 degree phase shift */
        EM_SW_SAMP_TYPE     i_fund;         /* Filtered current for fundamental calculation */
        EM_SW_SAMP_TYPE     v_fund;         /* Filtered voltage for fundamental calculation */
        
    } phase_y;
    
    /* Phase_B */
    struct
    {
        EM_SW_SAMP_TYPE     i;              /* Current */
        EM_SW_SAMP_TYPE     v;              /* Voltage */
        EM_SW_SAMP_TYPE     v90;            /* Voltage 90 degree phase shift */
        EM_SW_SAMP_TYPE     i_fund;         /* Filtered current for fundamental calculation */
        EM_SW_SAMP_TYPE     v_fund;         /* Filtered voltage for fundamental calculation */
        
    } phase_b;
    
    /* Neutral */
    struct 
    {
        EM_SW_SAMP_TYPE     i;              /* Current */
    } neutral;
    
    /* Status info */
    struct
    {
        EM_FUND_SEQUENCE    fund_sequence;   /* Accumulation sequence of filtered signal */
        uint8_t             reserved;        /* Reserved */
    } status;
    
} EM_SAMPLES;

typedef struct tagEMSoftwareProperty
{
    struct
    {
        struct
        {
            uint8_t     gain_num_level;                             /* (SW Support Only) ADC gain phase number of level */
            uint32_t    gain_upper_threshold;                       /* (SW Support Only) ADC gain phase upper threshold */
            uint32_t    gain_lower_threshold;                       /* (SW Support Only) ADC gain phase lower threshold */
        } phase_r;

        struct
        {
            uint8_t     gain_num_level;                             /* (SW Support Only) ADC gain phase number of level */
            uint32_t    gain_upper_threshold;                       /* (SW Support Only) ADC gain phase upper threshold */
            uint32_t    gain_lower_threshold;                       /* (SW Support Only) ADC gain phase lower threshold */
        } phase_y;

        struct
        {
            uint8_t     gain_num_level;                             /* (SW Support Only) ADC gain phase number of level */
            uint32_t    gain_upper_threshold;                       /* (SW Support Only) ADC gain phase upper threshold */
            uint32_t    gain_lower_threshold;                       /* (SW Support Only) ADC gain phase lower threshold */
        } phase_b;

    } adc;          /* ADC Module */

    struct
    {
        float32_t       irms_noload_threshold;      /* (SW Support Only) Set the threshold for IRMS No Load Detection (Ampere) */
        float32_t       power_noload_threshold;     /* (SW Support Only) Set the threshold for Power No Load Detection (Watt) */
        float32_t       no_voltage_threshold;       /* (SW Support Only) Set the threshold for No Voltage Detection (Volt) */
        float32_t       freq_low_threshold;         /* Lowest frequency (Hz) */
        float32_t       freq_high_threshold;        /* Highest frequency (Hz) */
        uint32_t        meter_constant;             /* Meter constant (imp/KWh) */
        float32_t       pulse_on_time;              /* Pulse on time (ms) */
        uint8_t         energy_pulse_ratio;         /* Ratio of energy step vs pulse meter constant: 1-255 */
        uint8_t         pulse_export_direction;     /* Option to output pulse for export direction: 0 or 1 */
        uint8_t         enable_pulse_reactive;              
        uint8_t         enable_pulse_apparent;

    } operation;    /* Metrology Operation */

    struct
    {
        uint8_t         power;
        uint8_t         rms;
        uint8_t         freq;
        uint8_t         pf;
    } rounding;     /* Metrology Rounding Digits */

    struct
    {
        float32_t       sag_rms_rise_threshold;                     /* (SW Support Only) The VRMS rising threshold to detect Sag Event (restoration) */
        float32_t       sag_rms_fall_threshold;                     /* (SW Support Only) The VRMS falling threshold to detect Sag Event (occurence) */
        float32_t       swell_rms_rise_threshold;                   /* (SW Support Only) The VRMS rising threshold to detect Swell Event (occurence) */
        float32_t       swell_rms_fall_threshold;                   /* (SW Support Only) The VRMS falling threshold to detect Swell Event (restoration) */
        uint16_t        sag_detection_half_cycle;                   /* (SW Support Only) Number of signal half-cycle to detect Sag Event, 0 means no detection */
        uint16_t        swell_detection_half_cycle;                 /* (SW Support Only) Number of signal half-cycle to detect Swell Event, 0 means no detection */
    } sag_swell;    /* Sag and Swell detection */

} EM_SW_PROPERTY;

typedef struct tagEMOperationData
{
    EM_ENERGY_COUNTER energy_counter;
    struct
    {
        uint32_t active_imp;
        uint32_t active_exp;
        uint32_t reactive_ind_imp;
        uint32_t reactive_ind_exp;
        uint32_t reactive_cap_imp;
        uint32_t reactive_cap_exp;
        uint32_t apparent_imp;
        uint32_t apparent_exp;
        uint8_t pulse_active;
        uint8_t pulse_reactive;
        uint8_t pulse_apparent;
        uint8_t padding;
    } remainder;
    
} EM_OPERATION_DATA;

typedef struct tagEMAccModeSamples
{
    EM_SW_SAMP_TYPE     signal0;
    EM_SW_SAMP_TYPE     signal1;
    EM_SW_SAMP_TYPE     signal2;
    EM_SW_SAMP_TYPE     signal3;
    EM_SW_SAMP_TYPE     signal4;
    EM_SW_SAMP_TYPE     signal5;
} EM_ACCMODE_SAMPLES;

typedef struct tagEMAccModeAccumulator
{
    float32_t acc0;
    float32_t acc1;
    float32_t acc2;
} EM_ACCMODE_ACCUMULATOR;

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/

#endif /* _EM_TYPE_H */
