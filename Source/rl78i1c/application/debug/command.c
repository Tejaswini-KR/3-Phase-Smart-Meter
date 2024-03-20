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
* File Name    : command.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : Command processing source File
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#ifdef __DEBUG

/* Driver */
#include "r_cg_macrodriver.h"   /* CG Macro Driver */
#include "r_cg_rtc.h"           /* RTC Driver */
#include "r_cg_dsadc.h"         /* DSAD Driver */
#include "r_cg_wdt.h"           /* WDT Driver */

/* Wrapper */
#include "wrp_em_sw_config.h"   /* EM Software Config */
#include "wrp_em_adc.h"
//#include "wrp_em_adc_data.h"
#include "wrp_em_pulse.h"
#include "wrp_em_mcu.h"
#include "wrp_app_ext.h"
#include "wrp_em_adc.h"

/* MW/Core, Common */
#include "em_core.h"            /* EM Core APIs */
//#include "em_conversion.h"      /* EM Conversion APIs */
//#include "em_maths.h"           /* EM Maths APIs */
#include "wrp_em_sw_property.h"      /* EM Core Shared Header */

/* Application */
#include "startup.h"
#include "r_meter_format.h"     /* EEPROM Format */
#include "config_format.h"      /* DATALFLASH Format */
#include "eeprom.h"             /* EEPROM Driver */
#include "dataflash.h"          /* DATALFLASH Driver */
#include "storage.h"            /* Storage Header File */
#include "config_storage.h"     /* Storage Header File */
#include "event.h"              /* Event Header File */
#include "r_calib.h"            /* Auto Calibration Module */
#include "platform.h"
#include "em_fft.h"
#include "inst_read.h"
#include "r_nameplate.h"
#include "r_tariff.h"
#include "r_max_demand.h"
#include "r_abnormal_operating.h"
#include "r_nameplate.h"
#include "r_calib.h"
#include "r_scheduler.h"
#include "r_loadsurvey.h"

#include "bl_serialflash.h"

/* Debug Only */
#ifdef __DEBUG
#include <stdlib.h>          /* Standard IO */
#include <stdio.h>          /* Standard IO */
#include <stdarg.h>         /* Variant argument */
#include <string.h>         /* String Standard Lib */
#include <math.h>           /* Mathematic Standard Lib */
#include <limits.h>         /* Number limits definitions */
#include "cmd.h"            /* CMD Prompt Driver */

#ifdef METER_ENABLE_MEASURE_CPU_LOAD
#include "load_test.h"
#endif

#endif




#include "storage_em.h"

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
/* Command Invoker Function */
typedef uint8_t (*FUNC)(uint8_t *arg_str);

/* Command Item */
typedef struct tagCommandTable
{
    const uint8_t   *cmd_name;
    const uint8_t   *params;
    const uint8_t   *description;
    const FUNC      func;
} COMMAND_ITEM;

/* Measured data */
typedef struct tagMeasuredData
{
    float32_t       vrms[EM_CALC_NUM_OF_LINE];
    float32_t       irms[EM_CALC_NUM_OF_LINE];
    float32_t       vector_sum_irms;

    float32_t       power_factor[EM_CALC_NUM_OF_LINE]; 
    EM_PF_SIGN      power_factor_sign[EM_CALC_NUM_OF_LINE];

    float32_t       freq[EM_CALC_NUM_OF_LINE];

    float32_t       active_power[EM_CALC_NUM_OF_LINE];
    float32_t       reactive_power[EM_CALC_NUM_OF_LINE];
    float32_t       apparent_power[EM_CALC_NUM_OF_LINE];

    float32_t       fundamental_vrms[EM_CALC_NUM_OF_LINE];
    float32_t       fundamental_irms[EM_CALC_NUM_OF_LINE];
    float32_t       fundamental_power[EM_CALC_NUM_OF_LINE];

    float32_t       voltage_thd[EM_CALC_NUM_OF_LINE];
    float32_t       current_thd[EM_CALC_NUM_OF_LINE];
    float32_t       power_thd[EM_CALC_NUM_OF_LINE];

    float32_t       phase_angle[EM_CALC_NUM_OF_LINE];
    float32_t       current_phase_angle[EM_CALC_NUM_OF_LINE];
    float32_t       current_neutral_angle[EM_CALC_NUM_OF_LINE];

    float32_t       energy_total_import_active;
    float32_t       energy_total_import_capacitive_reactive;
    float32_t       energy_total_import_inductive_reactive;
    float32_t       energy_total_import_apparent;
    float32_t       energy_total_export_active;
    float32_t       energy_total_export_capacitive_reactive;
    float32_t       energy_total_export_inductive_reactive;
    float32_t       energy_total_export_apparent;

    float32_t       energy_tariff_import_active;
    float32_t       energy_tariff_import_capacitive_reactive;
    float32_t       energy_tariff_import_inductive_reactive;
    float32_t       energy_tariff_import_apparent;
    float32_t       energy_tariff_export_active;
    float32_t       energy_tariff_export_capacitive_reactive;
    float32_t       energy_tariff_export_inductive_reactive;
    float32_t       energy_tariff_export_apparent;

    float32_t       mdm_active;
    float32_t       mdm_capacitive_reactive;
    float32_t       mdm_inductive_reactive;
    float32_t       mdm_apparent;

    float32_t       current_average_demand_active;
    float32_t       current_average_demand_capacitive_reactive;
    float32_t       current_average_demand_inductive_reactive;
    float32_t       current_average_demand_apparent;

    float32_t       last_average_demand_active;
    float32_t       last_average_demand_capacitive_reactive;
    float32_t       last_average_demand_inductive_reactive;
    float32_t       last_average_demand_apparent;
    
} COMMAND_MEASURED_DATA;

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Command Status */
#define COMMAND_OK          0
#define COMMAND_ERROR       1

/* Command Invoker Statement & Table Length */
#define INVOKE_COMMAND(index, arg_str)  {                                                   \
                                            if (cmd_table[index].func != NULL)              \
                                            {                                               \
                                                (*cmd_table[index].func)(arg_str);          \
                                            }                                               \
                                        }
#define COMMAND_TABLE_LENGTH    (sizeof(cmd_table) / sizeof(COMMAND_ITEM))

#define IF_CTRL_C_BREAK()       {if(CMD_IsCtrlKeyReceived())                                            \
                                {                                                                       \
                                    CMD_Printf((uint8_t *)"\n\rCTRL + C is pressed! Break!\n\r");       \
                                    CMD_AckCtrlKeyReceived();                                           \
                                                                                                        \
                                    /* Break printout here */                                           \
                                    break;                                                              \
                                }}   

/***********************************************************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/
/* Import from dataflash */
extern uint8_t DATAFLASH_ReadHeaderStatus(uint8_t block, uint8_t *buf);
extern uint8_t DATAFLASH_ReadHeaderCRC(uint8_t bank, uint8_t *buf);
extern uint8_t DATAFLASH_InternalRead(uint32_t addr, uint8_t* buf, uint16_t size);

/* Import from Wrapper */
extern EM_SAMPLES g_wrp_adc_samples;
extern void (NEAR_FUNC * g_wrp_adc_signal_ready_cb_and_return)(void);

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/******************************************************************************
Private global variables and functions
******************************************************************************/
/* Static variables */
extern const uint16_t scheduler_exe_time_maximum_support[];
static COMMAND_MEASURED_DATA g_em_core_data;
#ifdef __CA78K0R__
/* Math error exception */
static uint16_t g_matherr_type = 0;
#endif

#define EM_MAX_SAMPLE_BUFFER        (10)
volatile uint16_t            g_sample_count = EM_MAX_SAMPLE_BUFFER;
volatile EM_SW_SAMP_TYPE     g_sample0[EM_MAX_SAMPLE_BUFFER];
volatile EM_SW_SAMP_TYPE     g_sample1[EM_MAX_SAMPLE_BUFFER];
volatile uint8_t             g_sample1_direction = 0;    /* I1 */
const uint16_t      g_sample_max_count = EM_MAX_SAMPLE_BUFFER;

/* Sub-function (static for module) */
static uint8_t * COMMAND_GetScanOneParam(
    uint8_t *output,
    uint16_t size,
    uint8_t *input,
    uint8_t *ahead_str,
    uint8_t *break_str
);
static uint16_t  COMMAND_ConvertFromHexString(uint8_t *str, uint8_t *b_found);

/* Command Invoker */
static uint8_t COMMAND_InvokeUsage(uint8_t *arg_str);                           /* Usage */
static uint8_t COMMAND_InvokeStartEM(uint8_t *arg_str);                         /* Start EM */
static uint8_t COMMAND_InvokeStopEM(uint8_t *arg_str);                          /* Stop EM */
static uint8_t COMMAND_InvokeRestartEM(uint8_t *arg_str);                       /* Restart EM */
static uint8_t COMMAND_InvokeDisplay(uint8_t *arg_str);                         /* Display */
static uint8_t COMMAND_InvokeRtc(uint8_t *arg_str);                             /* RTC */
static uint8_t COMMAND_InvokeSetRtc(uint8_t *arg_str);                          /* Set RTC */
static uint8_t COMMAND_InvokeBackup(uint8_t *arg_str);                          /* Backup */
static uint8_t COMMAND_InvokeRestore(uint8_t *arg_str);                         /* Restore */
static uint8_t COMMAND_InvokeReadMemory(uint8_t *arg_str);                      /* Read Memory */
static uint8_t COMMAND_InvokeWriteMemory(uint8_t *arg_str);                     /* Write Memory */
static uint8_t COMMAND_InvokeAddEnergyLog(uint8_t *arg_str);                    /* Add energy log */
static uint8_t COMMAND_InvokeAddTamperLog(uint8_t *arg_str);                    /* Add tamper log */
static uint8_t COMMAND_InvokeFormatMemory(uint8_t *arg_str);                    /* Format Memory */
static uint8_t COMMAND_InvokeReadPlatformInfo(uint8_t *arg_str);                /* Read Platform Info */
static uint8_t COMMAND_InvokeReadDTFLHeader(uint8_t *arg_str);                  /* Read DTFL header */
static uint8_t COMMAND_InvokeEraseDTFL(uint8_t *arg_str);                       /* Erase DTFL content */
//static uint8_t COMMAND_InvokeDumpSample(uint8_t *arg_str);                      /* Dump waveform samples */
static uint8_t COMMAND_InvokeCalibration(uint8_t *arg_str);                     /* Calibration */
static uint8_t COMMAND_InvokeSetCalibInfo(uint8_t *arg_str);                    /* Set calibration info */
//static uint8_t COMMAND_InvokeSetConfig(uint8_t *arg_str);                       /* Set configuration */
//static uint8_t COMMAND_InvokeGetSetPulseConfig(uint8_t *arg_str);
static uint8_t COMMAND_InvokeGetSetPulsePower(uint8_t *arg_str);

static uint8_t COMMAND_InvokeDSADPowerGetSet(uint8_t *arg_str);                 /* Get,set DSAD channel power state */
static uint8_t COMMAND_InvokeDSADPhaseGetSet(uint8_t *arg_str);                 /* Get,set DSAD phase delay */
static uint8_t COMMAND_InvokeDSADHpfGetSet(uint8_t *arg_str);                   /* Get,set DSAD HPF information */
static uint8_t COMMAND_InvokeDSADGainGetSet(uint8_t *arg_str);                  /* Get,set DSAD gain */
static uint8_t COMMAND_InvokeCPULoad(uint8_t *arg_str);                         /* Measure CPU Load */
static uint8_t COMMAND_InvokeReadTamperLog(uint8_t *arg_str);                   /* Read and print specific tamper log detail */
static uint8_t COMMAND_InvokeGetCurrentTamperLogIndex(uint8_t *arg_str);        /* Read the current tamper log index */
static uint8_t COMMAND_InvokeSetMaxDemandConfig(uint8_t *arg_str);
static uint8_t COMMAND_InvokeResetMaxDemandData(uint8_t *arg_str);
static uint8_t COMMAND_InvokeNextMaxDemandPeriod(uint8_t *arg_str);
static uint8_t COMMAND_InvokeDisplayTariffAll(uint8_t *arg_str);
static uint8_t COMMAND_InvokeResetTariff(uint8_t *arg_str);
static uint8_t COMMAND_InvokeDisplayMdmAll(uint8_t *arg_str);
static uint8_t COMMAND_InvokeDisplayBufferMdm(uint8_t *arg_str);
static uint8_t COMMAND_InvokeTariffConfiguration(uint8_t *arg_str);

static uint8_t COMMAND_InvokeClearEmEnergyCounter(uint8_t *arg_str);
static uint8_t COMMAND_InvokeGetBankStatusInfo(uint8_t *arg_str);
static uint8_t COMMAND_InvokeBankSwap(uint8_t *arg_str);
static uint8_t COMMAND_InvokeInvertBootFlagAndReset(uint8_t *arg_str);
static uint8_t COMMAND_InvokeDisplayInstantaneous(uint8_t *arg_str);
#ifdef EM_FFT_ENABLE
static uint8_t COMMAND_InvokeFFT(uint8_t *arg_str);
#endif /* EM_FFT_ENABLE */
static uint8_t COMMAND_InvokeDisplayTariffStorageAll(uint8_t *arg_str);
static uint8_t  COMMAND_InvokeDisplayScheduleConfig(uint8_t *arg_str);
static uint8_t ConvertDateTimeFromClient(uint8_t *arg_str, rtc_counter_value_t * p_rtctime);
static uint8_t  COMMAND_InvokeAddSchedule(uint8_t *arg_str);
static uint8_t  COMMAND_InvokeClearSchedule(uint8_t *arg_str);
static uint8_t  COMMAND_InvokeEditSchedule(uint8_t *arg_str);
static uint8_t  COMMAND_InvokeScheduleBackup(uint8_t *arg_str);
static uint8_t  COMMAND_InvokeScheduleRestore(uint8_t *arg_str);
static uint8_t  COMMAND_InvokeEventGet(uint8_t *arg_str);
static uint8_t COMMAND_InvokeClearEventLog(uint8_t *arg_str);
static uint8_t COMMAND_InvokeDisplayDailyLoad(uint8_t *arg_str);
static uint8_t COMMAND_InvokeDisplayBilling(uint8_t *arg_str);

static uint8_t COMMAND_InvokeActCalendarEdit(uint8_t *arg_str);
static uint8_t COMMAND_InvokeActCalendarDisplay(uint8_t *arg_str);
static uint8_t COMMAND_InvokeCopPassiveProfileToActive(uint8_t *arg_str);

static uint8_t Calibration_Service(uint16_t calib_c, uint16_t calib_cp, float32_t calib_imax, float32_t calib_v, float32_t calib_i, uint8_t calib_neutral);

static uint8_t COMMAND_InvokeGetService(uint8_t *arg_str);
static uint8_t COMMAND_InvokeSetService(uint8_t *arg_str);

void print_rtc_time(void);
void print_name_platetable(void);
void print_block_load_survey(void);
void print_daily_load_survey(void);
void print_billing(void);
void print_event_table(uint8_t event_type);
void print_charge_table(void);
void print_token_transfer_table(void);
void print_schedulerv(uint8_t data_id);
void print_activity_calendar(void);

uint8_t R_DEBUG_CommandServiceSet(uint8_t service_param, uint32_t data);
uint8_t R_DEBUG_CommandServiceGet(uint8_t service_type, uint8_t service_params, uint32_t* p_out_data);
uint8_t g_debug_notification_enable_flag = FALSE;
const uint8_t SRT_FORMAT_RTC[] = "%02x/%02x/20%02x %02x:%02x:%02x %02x, ";

/* Command Table */
static const COMMAND_ITEM   cmd_table[] = 
{
    /* ---------------------------------------------------------------------------------------------------------------------*/
    /* Command Name     Parameter                   Description                                     Func Pointer */
    /* ---------------------------------------------------------------------------------------------------------------------*/
    {(const uint8_t *)"?"               ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Help"                                                         ,   COMMAND_InvokeUsage                     },
    {(const uint8_t *)"cls"             ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Clear screen"                                                 ,   NULL                                    },      /* CMD module processed it internally */
    {(const uint8_t *)"start"           ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Start EM"                                                     ,   COMMAND_InvokeStartEM                   },
    {(const uint8_t *)"stop"            ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Stop EM"                                                      ,   COMMAND_InvokeStopEM                    },
    {(const uint8_t *)"restart"         ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Restart EM"                                                   ,   COMMAND_InvokeRestartEM                 },  
    {(const uint8_t *)"display"         ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Display current measured data"                                ,   COMMAND_InvokeDisplay                   },  
    {(const uint8_t *)"rtc"             ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Display current RTC time"                                     ,   COMMAND_InvokeRtc                       },
    {(const uint8_t *)"setrtc"          ,   (const uint8_t *)"dd/mm/yy hh:mm:ss"                        ,   (const uint8_t *)"Set RTC time"                                                 ,   COMMAND_InvokeSetRtc                    },
    {(const uint8_t *)"backup"          ,   (const uint8_t *)"selection"                                ,   (const uint8_t *)"Backup to Storage Memory"                                     ,   COMMAND_InvokeBackup                    },
    {(const uint8_t *)"restore"         ,   (const uint8_t *)"selection"                                ,   (const uint8_t *)"Restore from Storage Memory"                                  ,   COMMAND_InvokeRestore                   },
    {(const uint8_t *)"readmem"         ,   (const uint8_t *)"type(0:EEP,1:DTFL) addr size [cast]"      ,   (const uint8_t *)"Read memory type at addr, size, display value"                ,   COMMAND_InvokeReadMemory                },
    {(const uint8_t *)"writemem"        ,   (const uint8_t *)"type(0:EEP,1:DTFL) addr size value"       ,   (const uint8_t *)"Write memory type at addr, size with value"                   ,   COMMAND_InvokeWriteMemory               },
    {(const uint8_t *)"readdtflhead"    ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Read DataFlash status header"                                 ,   COMMAND_InvokeReadDTFLHeader            },
    {(const uint8_t *)"erasedtfl"       ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Erase content of dataflash"                                   ,   COMMAND_InvokeEraseDTFL                 },
    //{(const uint8_t *)"addenergylog"    ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Add an energy log record to EEPROM"                           ,   COMMAND_InvokeAddEnergyLog              },
    //{(const uint8_t *)"addtamperlog"    ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Add an tamper log record to EEPROM"                           ,   COMMAND_InvokeAddTamperLog              },
    {(const uint8_t *)"formatmem"       ,   (const uint8_t *)"type(0:EEP,1:DTFL)"                       ,   (const uint8_t *)"Format memory type (followed r_meter_format.h)"                       ,   COMMAND_InvokeFormatMemory              },
    {(const uint8_t *)"readinfo"        ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Read platform info"                                           ,   COMMAND_InvokeReadPlatformInfo          },
//    {(const uint8_t *)"dump"            ,   (const uint8_t *)"current"                                  ,   (const uint8_t *)"Dump waveform from EM Core"                                   ,   COMMAND_InvokeDumpSample                },
    {(const uint8_t *)"calib"           ,   (const uint8_t *)"c cp imax v i w "                         ,   (const uint8_t *)"Calibrate (cycle,cycle_phase,imax,V,I,wire)"                  ,   COMMAND_InvokeCalibration               },
    {(const uint8_t *)"setcalib"        ,   (const uint8_t *)"get:leave empty; set:1 later follow guide",   (const uint8_t *)"Manually set calib info"                                      ,   COMMAND_InvokeSetCalibInfo              },    
//    {(const uint8_t *)"setconfig"       ,   (const uint8_t *)"get:leave empty; set:1 later follow guide",   (const uint8_t *)"Manually set configuration"                                   ,   COMMAND_InvokeSetConfig                 },    
//    {(const uint8_t *)"pconfig"         ,   (const uint8_t *)"get:empty; set: pconst_total, pontime"    ,   (const uint8_t *)"Get, Set pulse config: pulse constant and on time"            ,   COMMAND_InvokeGetSetPulseConfig         },
    {(const uint8_t *)"ppower"          ,   (const uint8_t *)"get:empty; set: watt pulse3 pulse4"       ,   (const uint8_t *)"Get, Set pulse power value"                                   ,   COMMAND_InvokeGetSetPulsePower          },
    {(const uint8_t *)"dspower"         ,   (const uint8_t *)"get:leave empty; set:ch state(1/0) "      ,   (const uint8_t *)"Get, Set DSAD Channel Power"                                  ,   COMMAND_InvokeDSADPowerGetSet           },
    {(const uint8_t *)"dsphase"         ,   (const uint8_t *)"get:leave empty; set:ch step "            ,   (const uint8_t *)"Get, Set DSAD Phase Delay"                                    ,   COMMAND_InvokeDSADPhaseGetSet           },
    {(const uint8_t *)"dshpf"           ,   (const uint8_t *)"get:leave empty; set:ch state(1/0) cutoff",   (const uint8_t *)"Get, Set DSAD HPF state"                                      ,   COMMAND_InvokeDSADHpfGetSet             },
    {(const uint8_t *)"dsgain"          ,   (const uint8_t *)"get:leave empty; set:ch gain"             ,   (const uint8_t *)"Get, Set DSAD Gain Setting"                                   ,   COMMAND_InvokeDSADGainGetSet            },
    {(const uint8_t *)"cpuload"         ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Measure the CPU Load"                                         ,   COMMAND_InvokeCPULoad                   },
    {(const uint8_t *)"mdmconfig"       ,   (const uint8_t *)"get:empty; set: min num_of_period"        ,   (const uint8_t *)"Get, Set max demand configuration"                            ,   COMMAND_InvokeSetMaxDemandConfig        },
    {(const uint8_t *)"mdmreset"        ,   (const uint8_t *)"empty, no effect, 1 reset all mdm"        ,   (const uint8_t *)"Reset max demand state "                                      ,   COMMAND_InvokeResetMaxDemandData        },
    {(const uint8_t *)"mdmnext"         ,   (const uint8_t *)"empty, no effect, 1 next mdm period"      ,   (const uint8_t *)"Next max demand period"                                       ,   COMMAND_InvokeNextMaxDemandPeriod       },
    {(const uint8_t *)"mdmdisp"         ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Display all max demand information "                          ,   COMMAND_InvokeDisplayMdmAll             },
    {(const uint8_t *)"mdmbuff"         ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Display max demand buffer "                                   ,   COMMAND_InvokeDisplayBufferMdm          },
    {(const uint8_t *)"tardisp"         ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Display all tariff energy "                                   ,   COMMAND_InvokeDisplayTariffAll          },
    {(const uint8_t *)"tarstorage"      ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Display all tariff energy log in storage"                     ,   COMMAND_InvokeDisplayTariffStorageAll   },
    {(const uint8_t *)"tarreset"        ,   (const uint8_t *)"1"                                        ,   (const uint8_t *)"Reset tariff"                                                 ,   COMMAND_InvokeResetTariff               },
    {(const uint8_t *)"tarconfig"       ,   (const uint8_t *)"get:empty; sets of hh:mm/tariff_no"       ,   (const uint8_t *)"Get, Set tariff configuration"                                ,   COMMAND_InvokeTariffConfiguration       },
//    {(const uint8_t *)"tplog"           ,   (const uint8_t *)"index: 1-200"                             ,   (const uint8_t *)"Read tamper log by index"                                     ,   COMMAND_InvokeReadTamperLog             },
//    {(const uint8_t *)"tpindex"         ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Get current tamper log index"                                 ,   COMMAND_InvokeGetCurrentTamperLogIndex  },
    {(const uint8_t *)"clrenergy"       ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Clear EM energy counter in eeprom and ram"                    ,   COMMAND_InvokeClearEmEnergyCounter      },
    {(const uint8_t *)"binfo"           ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Get bank status information"                                  ,   COMMAND_InvokeGetBankStatusInfo         },
    {(const uint8_t *)"bswap"           ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Swap bank"                                                    ,   COMMAND_InvokeBankSwap                  },
    {(const uint8_t *)"binvr"           ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Invert boot flag and reset"                                   ,   COMMAND_InvokeInvertBootFlagAndReset    },
    #ifdef EM_FFT_ENABLE
    {(const uint8_t *)"fft"             ,   (const uint8_t *)"command"                                  ,   (const uint8_t *)"Display FFT Harmonic"                                         ,   COMMAND_InvokeFFT                       },
    #endif /* EM_FFT_ENABLE */
    {(const uint8_t *)"insdisp"         ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Display instantaneous snap shot"                              ,   COMMAND_InvokeDisplayInstantaneous      },
    {(const uint8_t *)"scheduledisp"    ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Display all scheudler"                                        ,   COMMAND_InvokeDisplayScheduleConfig      },
    {(const uint8_t *)"scheduleadd"     ,   (const uint8_t *)"[schedule_id] [dd/mm/yy hh:mm:ss ww]"     ,   (const uint8_t *)"Add new schedule at schedule_ID"                              ,   COMMAND_InvokeAddSchedule                },
    {(const uint8_t *)"scheduleclr"     ,   (const uint8_t *)"[schedule_id]"                            ,   (const uint8_t *)"Clear all element of scheduler_ID"                            ,   COMMAND_InvokeClearSchedule                },
    {(const uint8_t *)"scheduleedit"    ,   (const uint8_t *)"[schedule_id] [exe_id] [dd/mm/yy hh:mm:ss ww]" ,   (const uint8_t *)"Edit schedule"                                           ,   COMMAND_InvokeEditSchedule                },
    {(const uint8_t *)"schedulebackup"  ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Schedule backup"                                              ,   COMMAND_InvokeScheduleBackup                },
    {(const uint8_t *)"schedulerestore" ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Schedule restore"                                             ,   COMMAND_InvokeScheduleRestore               },
    {(const uint8_t *)"caledit"         ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Set activity calendar"                                        ,   COMMAND_InvokeActCalendarEdit           },
    {(const uint8_t *)"caldisp"         ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Display all activity calendar setting"                        ,   COMMAND_InvokeActCalendarDisplay           },
    {(const uint8_t *)"actpassive"      ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Activate passive profile of Activity calendar"                ,   COMMAND_InvokeCopPassiveProfileToActive           },
    {(const uint8_t *)"getevent"        ,   (const uint8_t *)"type_event_id"                            ,   (const uint8_t *)"Event trigger, type event ID following IS15959"               ,   COMMAND_InvokeEventGet                      },
    {(const uint8_t *)"cleareventlog"   ,   (const uint8_t *)""                                         ,   (const uint8_t *)"Clear memory for event"                                       ,   COMMAND_InvokeClearEventLog                 },
    {(const uint8_t *)"dailydisp"       ,   (const uint8_t *)"entry number"                             ,   (const uint8_t *)"display daily load"                                           ,   COMMAND_InvokeDisplayDailyLoad                 },
    {(const uint8_t *)"billingdisp"     ,   (const uint8_t *)"entry number"                             ,   (const uint8_t *)"display billing load"                                       ,   COMMAND_InvokeDisplayBilling                 },
    {(const uint8_t *)"read"            ,   (const uint8_t *)"<object_id>"                              ,   (const uint8_t *)"EM Read Service"                                              ,   COMMAND_InvokeGetService                },
    {(const uint8_t *)"write"           ,   (const uint8_t *)"<object_id> <data>"                       ,   (const uint8_t *)"EM Write Service"                                             ,   COMMAND_InvokeSetService                },
};

static const uint8_t * const g_mem_epr = (const uint8_t *)"EEPROM";
static const uint8_t * const g_mem_dtfl = (const uint8_t *)"DATAFLASH";
static const uint8_t * const g_mem_extflash = (const uint8_t *)"EX_FLASH";
static const uint8_t g_hpf_type[4][8] = {
    "0.607Hz",
    "1.214Hz",
    "2.429Hz",
    "4.857Hz"
};
static const uint8_t line_break[] = "+---------------------------------------------------------------------------------------------------------------------------------------------+\n\r";
static const uint8_t param_format[] = "| %- 32s | %# 15.3f | %# 15.3f | %# 15.3f | %# 15.3f | %# 15.3f | %- 15s|\n\r";
static const uint8_t param_format_energy[] = "|%- 6s|%# 15.3f|%# 15.3f|%# 15.3f|%# 15.3f|%# 15.3f|%# 15.3f|%# 15.3f|%# 15.3f|\n\r";
static const uint8_t param_format_demand[] = "|%- 6s|%# 15.3f|%# 15.3f|%02d/%02d/20%02d %02d:%02d:%02d %02d|\n\r";
static const uint8_t param_format_tariff[] = "| %- 28s (%1d) | %# 15.3f | %# 15.3f | %# 15.3f | %# 15.3f | %# 15.3f | %- 15s|\n\r";
static const uint8_t param_format_s[] = "| %- 32s | %# 15s | %# 15s | %# 15s | %# 15s | %# 15s | %- 15s|\n\r";
static const uint8_t param_format_d[] = "| %- 32s | %# 5d | %- 5d| %s\n\r";
static const uint8_t param_format_schedule[] = "| %- 32s | %# 5d | %- 5d|%- 5d|\n\r";
static const uint8_t param_format_time[] = "| %- 32s | %02d/%02d/20%02d %02d:%02d:%02d %02d %-12s|\n\r";
static const uint8_t param_format_rtc[] = "%02x/%02x/20%02x %02x:%02x:%02x %02x, ";

/******************************************************************************
* Function Name    : void matherr(struct exception *x)
* Description      : Mathematic error exception callback
* Arguments        : struct exception *x
* Functions Called : None
* Return Value     : None
******************************************************************************/
#ifdef __CA78K0R__
void matherr(struct exception *x)
{
    g_matherr_type = x->type;
}
#endif

/******************************************************************************
* Function Name : COMMAND_GetUnsigned16
* Interface     : static uint16_t COMMAND_GetUnsigned16(uint8_t *buffer)
* Description   : Get unsigned int 16 bit from buffer
* Arguments     : uint8_t * buffer: Buffer to cast to uint16_t
* Function Calls: None
* Return Value  : static uint16_t
******************************************************************************/
static uint16_t COMMAND_GetUnsigned16(uint8_t *buffer)
{
    uint16_t u16;
    u16  = (uint16_t)buffer[0];
    u16 |= (uint16_t)buffer[1] << 8;
    
    return (u16);
}

/******************************************************************************
* Function Name : COMMAND_GetUnsigned32
* Interface     : static uint32_t COMMAND_GetUnsigned32(uint8_t *buffer)
* Description   : Get unsigned long 32 bit from buffer
* Arguments     : uint8_t * buffer: Buffer to cast to uint32_t
* Function Calls: None
* Return Value  : static uint32_t
******************************************************************************/
static uint32_t COMMAND_GetUnsigned32(uint8_t *buffer)
{
    uint32_t u32;
    u32  = (uint32_t)buffer[0];
    u32 |= (uint32_t)buffer[1] << 8;
    u32 |= (uint32_t)buffer[2] << 16;
    u32 |= (uint32_t)buffer[3] << 24;
    
    return (u32);
}

/***********************************************************************************************************************
* Function Name : COMMAND_IsFloatNumber
* Interface     : static uint8_t COMMAND_IsFloatNumber(uint8_t *buffer)
* Description   : Check whether the input buffer is number or not
* Arguments     : uint8_t * buffer: Buffer to check
* Function Calls: None
* Return Value  : static uin8t_t: 1 if buffer is number or 0 if buffer contain characters
***********************************************************************************************************************/
static uint8_t COMMAND_IsFloatNumber(uint8_t *buffer)
{
    /* Note this function not check the NULL buffer */
    uint8_t dot_count = 0;
    uint8_t plus_count = 0;
    uint8_t minus_count = 0;
    
    while(*buffer != 0)
    {
        if ((*buffer >= '0' && *buffer <='9') || (*buffer == '.') 
            || (*buffer == '+') || (*buffer == '-'))
        {
            /* Check number of '.' sign */
            if (*buffer == '.')
            {
                dot_count++;
                if (dot_count > 1)
                {
                    return 0;   
                }
            }
            
            /* Check number of '+' sign */
            if (*buffer == '+')
            {
                plus_count++;
                if (plus_count > 1)
                {
                    return 0;   
                }
            }
            
            /* Check number of '-' sign */
            if (*buffer == '-')
            {
                minus_count++;
                if (minus_count > 1)
                {
                    return 0;   
                }
            }
            buffer++;
        }
        else
        {
            return 0;   
        }
    }
    
    return 1;
}

/******************************************************************************
* Function Name    : static uint8_t *COMMAND_GetScanOneParam(
*                  :     uint8_t *output,
*                  :     uint16_t size,
*                  :     uint8_t *input,
*                  :     uint8_t *ahead_str,
*                  :     uint8_t *break_str
*                  : );
* Description      : Command Get One Parameter
* Arguments        : uint8_t *output: Output buffer
*                  : uint16_t size: Size of output buffer
*                  : uint8_t *input: Input buffer
*                  : uint8_t *ahead_str: Char array to skip the ahead the arg_str
*                  : uint8_t *break_str: Char array to break the scan processing
* Functions Called : None
* Return Value     : Next location of parameter
******************************************************************************/
static uint8_t *COMMAND_GetScanOneParam(uint8_t *output,
                                        uint16_t size,
                                        uint8_t *input,
                                        uint8_t *ahead_str,
                                        uint8_t *break_str)
{
    uint8_t i, j, break_len, ahead_len;
    
    /* Check parameter */
    if (output == NULL || size == 0 ||
        input  == NULL || break_str == NULL)
    {
        return NULL;
    }

    if (ahead_str != NULL && *ahead_str != 0)
    {
        ahead_len = (uint8_t)strlen((char *)ahead_str);
        
        /* skip all ahead char that found on arg_str */
        while (*input != 0)
        {
            for (j = 0; j < ahead_len; j++)
            {
                if (ahead_str[j] == *input)
                    break;
            }
            
            /* is found in break_str? */
            if (j != ahead_len)
            {
                input++;
            }
            else    /* Not found */
            {
                break;  /* Break the outsize loop */
            }
        }
    }
    
    /* Is have remain char? */
    if (*input != 0)
    {   
        /* clear output buffer */
        memset(output, 0, size);
        
        /* Get the lenght of break_str */
        break_len = (uint8_t)strlen((char *)break_str);
    
        /* Scan the parameter */
        i = 0;
        while (i < size && *input != 0)
        {
            for (j = 0; j < break_len; j++)
            {
                if (break_str[j] == *input)
                    break;
            }

            /* is found in break_str?
             * --> end of scanning */
            if (j != break_len)
            {
                break;  /* end of scanning */
            }
            else    /* Not found --> continue to scan */
            {
                /* Update to buffer */
                output[i] = *input;
            
                /* scan next byte */
                input++;
                i++;
            }
        }
        
        return input;
    }
    else
    {
        return NULL;
    }
}

/******************************************************************************
* Function Name    : static uint16_t COMMAND_HexStringToUnsigned16(uint8_t *str)
* Description      : Command Convert Hex String to number
* Arguments        : uint8_t *str: Hex string
* Functions Called : None
* Return Value     : None
******************************************************************************/
static uint16_t COMMAND_HexStringToUnsigned16(uint8_t *str, uint8_t *b_found)
{
    uint16_t    rlt = 0;
    uint8_t     hexnum;
    
    *b_found = 0; /* Not found */
    
    /* Check parameter */
    if (str == NULL)
    {
        return 0;
    }
    
    /* point to 'x' char */
    while (*str != 0 && *str != 'x')
    {
        str++;
    }
    
    /* end string? */
    if (*str == 0 || (*(str+1)) == 0)
    {
        return 0;
    }
    
    str++;  /* skip 'x' */
    while ( *str != 0  &&       /* not end string?, and */
            ((*str >= '0' &&
              *str <= '9') ||       /* is numberic char?, or */
             (*str >= 'a' &&
              *str <= 'f') ||       /* is in 'a-f'?, or */
             (*str >= 'A' &&
              *str <= 'F')) )       /* is in 'A-F'? */
    {
        *b_found = 1;   /* found */
        
        if (*str >= 'a')
        {
            hexnum = 10 + (*str - 'a');     /* Get number */
        }
        else if (*str >= 'A')
        {
            hexnum = 10 + (*str - 'A');
        }
        else
        {
            hexnum = *str - '0';
        }

        rlt  = rlt << 4;
        rlt += hexnum;

        /* next char */
        str++;
    }
    
    return rlt;
}

/******************************************************************************
* Function Name    : static uint16_t COMMAND_DecStringToNum16_Logic(uint8_t *str)
* Description      : Command Logic part of converting decimal string to 16bit number
* Arguments        : uint8_t *str: Hex string
*                  : uint8_t *b_found: is found number? 
* Functions Called : None
* Return Value     : None
******************************************************************************/
static uint16_t COMMAND_DecStringToNum16_Logic(uint8_t *str, uint8_t *b_found)
{
    uint16_t    rlt = 0;
    uint8_t     decnum;
 
    /* No pointer checking here, this serve as logic implementation only */
    while ( *str != 0  &&       /* not end string?, and */
            (*str >= '0' &&
              *str <= '9'))     /* is numberic char?*/
    {
        *b_found = 1;   /* found */

        decnum = *str - '0';
        
        rlt  = rlt * 10;
        rlt += decnum;

        /* next char */
        str++;
    }
    
    return rlt;
}

/******************************************************************************
* Function Name    : static uint16_t COMMAND_DecStringToUnsigned16(uint8_t *str)
* Description      : Command Convert Dec String to number
* Arguments        : uint8_t *str: Hex string
* Functions Called : None
* Return Value     : None
******************************************************************************/
static uint16_t COMMAND_DecStringToUnsigned16(uint8_t *str, uint8_t *b_found)
{
    uint16_t    rlt;
    
    *b_found = 0; /* Not found */
    
    /* Check parameter */
    if (str == NULL)
    {
        return 0;
    }
        
    /* end string? */
    if (*str == 0)
    {
        return 0;
    }
    
    rlt = COMMAND_DecStringToNum16_Logic(str, b_found);
    
    return rlt;
}


/******************************************************************************
* Function Name    : static uint16_t COMMAND_DecStringToSigned16(uint8_t *str)
* Description      : Command Convert Dec String to number
* Arguments        : uint8_t *str: Hex string
* Functions Called : None
* Return Value     : None
******************************************************************************/
static int16_t COMMAND_DecStringToSigned16(uint8_t *str, uint8_t *b_found)
{
    int16_t     rlt;
    uint16_t    rlt_u;
    int16_t     sign;
    
    *b_found = 0; /* Not found */
    
    /* Check parameter */
    if (str == NULL)
    {
        return 0;
    }
        
    /* end string? */
    if (*str == 0)
    {
        return 0;
    }
    
    sign = (*str == '-') ? -1 : 1;
    if (sign == -1)
    {
        str++;
    }
    
    rlt_u = COMMAND_DecStringToNum16_Logic(str, b_found);
    
    /* Is input number in range of signed 16bit number? */
    if (sign == -1)
    {
        if (rlt_u > ((uint16_t)INT_MAX + 1))
        {
            *b_found = 0;
        }
    }
    else
    {
        if (rlt_u > INT_MAX)
        {
            *b_found = 0;
        }
    }
    
    /* Number checking OK, get sign to result */
    rlt = ((int16_t)rlt_u * sign);
    
    return rlt;
}

/******************************************************************************
* Function Name    : static uint32_t COMMAND_DecStringToNum32_Logic(uint8_t *str)
* Description      : Command Logic part of converting decimal string to 16bit number
* Arguments        : uint8_t *str: Hex string
*                  : uint8_t *b_found: is found number?
* Functions Called : None
* Return Value     : None
******************************************************************************/
static uint32_t COMMAND_DecStringToNum32_Logic(uint8_t *str, uint8_t *b_found)
{
    uint32_t    rlt = 0;
    uint8_t     decnum;

    /* No pointer checking here, this serve as logic implementation only */
    while (*str != 0 &&       /* not end string?, and */
        (*str >= '0' &&
        *str <= '9'))     /* is numberic char?*/
    {
        *b_found = 1;   /* found */

        decnum = *str - '0';

        rlt = rlt * 10;
        rlt += decnum;

        /* next char */
        str++;
    }

    return rlt;
}

/******************************************************************************
* Function Name    : static uint32_t COMMAND_DecStringToUnsigned32(uint8_t *str)
* Description      : Command Convert Dec String to number
* Arguments        : uint8_t *str: Hex string
* Functions Called : None
* Return Value     : None
******************************************************************************/
static uint32_t COMMAND_DecStringToUnsigned32(uint8_t *str, uint8_t *b_found)
{
    uint32_t    rlt;

    *b_found = 0; /* Not found */

                  /* Check parameter */
    if (str == NULL)
    {
        return 0;
    }

    /* end string? */
    if (*str == 0)
    {
        return 0;
    }

    rlt = COMMAND_DecStringToNum32_Logic(str, b_found);

    return rlt;
}

/******************************************************************************
* Function Name    : static int32_t COMMAND_DecStringToSigned32(uint8_t *str)
* Description      : Command Convert Dec String to number
* Arguments        : uint8_t *str: Hex string
* Functions Called : None
* Return Value     : None
******************************************************************************/
static int32_t COMMAND_DecStringToSigned32(uint8_t *str, uint8_t *b_found)
{
    int32_t     rlt;
    uint32_t    rlt_u;
    int32_t     sign;

    *b_found = 0; /* Not found */

                  /* Check parameter */
    if (str == NULL)
    {
        return 0;
    }

    /* end string? */
    if (*str == 0)
    {
        return 0;
    }

    sign = (*str == '-') ? -1 : 1;
    if (sign == -1)
    {
        str++;
    }

    rlt_u = COMMAND_DecStringToNum32_Logic(str, b_found);

    /* Is input number in range of signed 32bit number? */
    if (sign == -1)
    {
        if (rlt_u > ((uint32_t)LONG_MAX + 1))
        {
            *b_found = 0;
        }
    }
    else
    {
        if (rlt_u > LONG_MAX)
        {
            *b_found = 0;
        }
    }

    /* Number checking OK, get sign to result */
    rlt = ((int32_t)rlt_u * sign);

    return rlt;
}

/******************************************************************************
* Function Name    : static uint16_t COMMAND_HexBufferToUnsigned16(uint8_t *str, uint16_t len, uint8_t *b_found)
* Description      : Command Convert Hex Buffer to number
* Arguments        : uint8_t *str: Hex string
* Functions Called : None
* Return Value     : None
******************************************************************************/
static uint16_t COMMAND_HexBufferToUnsigned16(uint8_t *buf, uint16_t len, uint8_t *b_found)
{
    uint16_t    pos = 0;
    uint16_t    rlt = 0;
    uint8_t     hexnum;
    
    *b_found = 0; /* Not found */
    
    /* Check parameter */
    if (buf == NULL || len == 0)
    {
        return 0;
    }
    
    /* point to 'x' char */
    while (pos < len && buf[pos] != 'x')
    {
        pos++;
    }
    
    /* end of buffer? */
    if (pos == len)
    {
        return 0;
    }
    
    pos++;  /* skip 'x' */
    while ( pos < len  &&       /* not end string?, and */
            ((buf[pos] >= '0' &&
              buf[pos] <= '9') ||       /* is numberic char?, or */
             (buf[pos] >= 'a' &&
              buf[pos] <= 'f') ||       /* is in 'a-f'?, or */
             (buf[pos] >= 'A' &&
              buf[pos] <= 'F')) )       /* is in 'A-F'? */
    {
        *b_found = 1;   /* found */
        
        if (buf[pos] >= 'a')
        {
            hexnum = 10 + (buf[pos] - 'a');     /* Get number */
        }
        else if (buf[pos] >= 'A')
        {
            hexnum = 10 + (buf[pos] - 'A');
        }
        else
        {
            hexnum = buf[pos] - '0';
        }

        rlt  = rlt << 4;
        rlt += hexnum;

        /* next char */
        pos++;
    }
    
    return rlt;
}

/******************************************************************************
* Function Name : COMMAND_GetPowerFactorSignName
* Interface     : static const uint8_t* COMMAND_GetPowerFactorSignName(EM_PF_SIGN sign)
* Description   : Get the PF sign name
* Arguments     : EM_PF_SIGN sign: The sign of power factor
* Function Calls: None
* Return Value  : static const uint8_t*
******************************************************************************/
static const uint8_t* COMMAND_GetPowerFactorSignName(EM_PF_SIGN sign)
{
    switch (sign)
    {
        case PF_SIGN_LEAD_C:
            return (const uint8_t*)"PF_SIGN_LEAD_C";
        case PF_SIGN_UNITY:
            return (const uint8_t*)"PF_SIGN_UNITY";
        case PF_SIGN_LAG_L:
            return (const uint8_t*)"PF_SIGN_LAG_L";
        default:
            return (const uint8_t*)"";
    }
}

/******************************************************************************
* Function Name : COMMAND_GetPowerFactorSignName
* Interface     : static const uint8_t* COMMAND_GetPowerFactorSignName(EM_PF_SIGN sign)
* Description   : Get the DSAD gain name
* Arguments     : dsad_gain_t gain: The gain of DSAD channel
* Function Calls: None
* Return Value  : static const uint8_t*
******************************************************************************/
static const uint8_t* COMMAND_GetDsadGainName(dsad_gain_t gain)
{
    switch (gain)
    {
        case GAIN_X1:
            return (const uint8_t*)"GAIN_X1";
        case GAIN_X2:
            return (const uint8_t*)"GAIN_X2";
        case GAIN_X4:
            return (const uint8_t*)"GAIN_X4";
        case GAIN_X8:
            return (const uint8_t*)"GAIN_X8";
        case GAIN_X16:
            return (const uint8_t*)"GAIN_X16";
        case GAIN_X32:
            return (const uint8_t*)"GAIN_X32";
        default:
            return (const uint8_t*)"UNKNOWN";
    }
}

/******************************************************************************
* Function Name    : static uint16_t COMMAND_DecBufferToUnsigned16(uint8_t *str, uint16_t len, uint8_t *b_found)
* Description      : Command Convert Dec Buffer to number
* Arguments        : uint8_t *buf: Dec buffer
* Functions Called : None
* Return Value     : None
******************************************************************************/
static uint16_t COMMAND_DecBufferToUnsigned16(uint8_t *buf, uint16_t len, uint8_t *b_found)
{
    uint16_t    pos = 0;
    uint16_t    rlt = 0;
    uint8_t     decnum;
    
    *b_found = 0; /* Not found */
    
    /* Check parameter */
    if (buf == NULL)
    {
        return 0;
    }
        
    /* end string? */
    if (len == 0)
    {
        return 0;
    }
    
    while ( pos < len &&        /* not end string?, and */
            (buf[pos] >= '0' &&
              buf[pos] <= '9'))     /* is numberic char?*/
    {
        *b_found = 1;   /* found */

        decnum = buf[pos] - '0';
        
        rlt  = rlt * 10;
        rlt += decnum;

        /* next char */
        pos++;
    }
    
    return rlt;
}

/********************************************************************************************
* Function Name    : static uint8_t COMMAND_FastInputScan(uint8_t *output, uint8_t * input)
* Description      : Command Convert Fast input parameter
*                  : Ex1: Input "0-3" ==> Output: {0,1,2,3}
*                  : Ex2: Input "0-1,2,3-4" ==> Output: {0,1,2,3,4}
* Arguments        : uint8_t *input: Input argument string
*                  : uint8_t *output: Output decoded argument in byte array
* Functions Called : None
* Return Value     : None
********************************************************************************************/
#define DELIMITER_SIGN              (',')
#define UPTO_SIGN                   ('-')

static uint8_t COMMAND_FastInputScan(uint8_t *output, uint8_t * input, uint8_t len_limit)
{
    uint8_t i;
    
    uint8_t pos_deli_start = 0, pos_deli_stop = 0;
    uint8_t pos_upto;
    
    uint8_t range_start, range_stop;
    uint8_t decoded_num;
    
    uint8_t input_len;
    uint8_t is_found;
    uint8_t upto_cnt = 0;
    
    /* Check for NULL argument */
    if (output == NULL || input == NULL)
    {
        return 1;                           //NULL params
    }
    
    /* Check first character */
    if (*input == DELIMITER_SIGN || *input == UPTO_SIGN)
    {
        return 2;                           //Wrong format  
    }
    
    /* Get length of input string */
    input_len = (uint8_t)strlen((const char *)input);
    
    /* Check last character */
    if (input[input_len] == DELIMITER_SIGN || input[input_len] == UPTO_SIGN)
    {
        return 2;                           //Wrong format  
    }
    
    /* Clear the buffer */
    memset(output, 0, len_limit);
    
    while (pos_deli_stop < input_len)
    {
        /* Find next DELIMITER_SIGN */
        for (i=pos_deli_start; i < input_len; i++)
        {
            pos_deli_stop = i;
            if (input[i] == DELIMITER_SIGN)
            {
                break;              //Found the delimiter
            }
            
            if (i == (input_len - 1))
            {
                pos_deli_stop++;    /* In case reach the end, need to increase one more time*/  
            }
        }
        
        /* Now, got the range of  input*/
        /* Find the UPTO_SIGN */
        for (i=pos_deli_start; i < pos_deli_stop; i++)
        {
            if (input[i] == UPTO_SIGN)
            {
                upto_cnt++;
                pos_upto = i;
            }
        }
        
        if (upto_cnt > 1)
        {
            return 2;                       //Wrong format, duplicate UPTO_SIGN 
        }
        else
        {
            if (upto_cnt == 1)
            {
                //Have upto_sign ==> decode
                /* Range start */
                range_start = (uint8_t)COMMAND_DecBufferToUnsigned16(&input[pos_deli_start],
                                                                        pos_upto - pos_deli_start,
                                                                        &is_found);
                
                /* Range stop */
                range_stop = (uint8_t)COMMAND_DecBufferToUnsigned16(&input[pos_upto+1],
                                                                        pos_deli_stop - 1 - pos_upto,
                                                                        &is_found);
                if (is_found &&
                    (range_start < len_limit) && (range_stop < len_limit))
                {
                    while(range_start <= range_stop)
                    {
                        *output++ = range_start;
                        range_start++;
                    }
                }
                else
                {
                    return 2;               //Wrong data    
                }
            }
            else
            {
                //No upto_sign ==> decode normally
                decoded_num = (uint8_t)COMMAND_DecBufferToUnsigned16(&input[pos_deli_start],
                                                                        pos_deli_stop - pos_deli_start,
                                                                        &is_found);
                if(is_found && 
                    (decoded_num < len_limit))
                {
                    *output++ = decoded_num;
                }
                else
                {
                    return 2;                   //Wrong data    
                }
            }
        }
        upto_cnt = 0;                           /* Reset upto_cnt */
        pos_deli_start = pos_deli_stop + 1;     /* Jump to pos after delimiter */
    }
    
    return 0;
}

/******************************************************************************
* Function Name    : static EM_LINE COMMAND_GetEMLine(uint8_t input)
* Description      : Get enumerator EM_LINE from input
* Arguments        : uint8_t input: line phase value to parse
* Functions Called : None
* Return Value     : EM_LINE
******************************************************************************/
static EM_LINE COMMAND_GetEMLine(uint8_t input)
{
    /* Check lower-case, upper-case, number */
    if ( input == 'r' || input == 'R' || input == 0 )
    {
        return LINE_PHASE_R;
    }
    else if ( input == 'y' || input == 'Y' || input == 1 )
    {
        return LINE_PHASE_Y;
    }
    else if ( input == 'b' || input == 'B' || input == 2 )
    {
        return LINE_PHASE_B;
    }
    else if ( input == 'n' || input == 'N' || input == 3 )
    {
        return LINE_NEUTRAL;
    }
    else
    {
        return LINE_TOTAL;
    }
}

/******************************************************************************
* Function Name    : static uint8_t COMMAND_InvokeUsage(uint8_t *arg_str)
* Description      : Command Invoke Usage
* Arguments        : uint8_t index: Command index
*                  : uint8_t *arg_str: Arguments string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
******************************************************************************/
static uint8_t COMMAND_InvokeUsage(uint8_t *arg_str)
{
    uint8_t i;
    
    CMD_SendString((uint8_t *)"\n\r");
    CMD_SendString((uint8_t *)"----------------------------------------------------------------------------------------------------------\n\r");
    CMD_Printf((uint8_t *)" %- 15s %- 42s %s\n\r", "Command Name", "Parameter", "Description");
    CMD_SendString((uint8_t *)"----------------------------------------------------------------------------------------------------------\n\r");
    for (i = 0; i < COMMAND_TABLE_LENGTH; i++)
    {
        R_WDT_Restart();
        CMD_Printf( (uint8_t *)" %- 15s %- 42s %s\n\r",
                    cmd_table[i].cmd_name,
                    cmd_table[i].params,
                    cmd_table[i].description);
    }
    
    return 0;
}

/******************************************************************************
* Function Name    : static uint8_t COMMAND_InvokeStartEM(uint8_t *arg_str)
* Description      : Command Invoke Start EM
* Arguments        : uint8_t index: Command index
*                  : uint8_t *arg_str: Arguments string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
******************************************************************************/
static uint8_t COMMAND_InvokeStartEM(uint8_t *arg_str)
{
    CMD_SendString((uint8_t *)"\n\rStarting EM...");
    if (EM_Start() == EM_OK)
    {
        CMD_SendString((uint8_t *)"OK\n\r");
    }
    else
    {
        CMD_SendString((uint8_t *)"FAILED\n\r");
    }
    
    return 0;
}

/******************************************************************************
* Function Name    : static uint8_t COMMAND_InvokeStopEM(uint8_t *arg_str)
* Description      : Command Invoke Stop EM
* Arguments        : uint8_t index: Command index
*                  : uint8_t *arg_str: Arguments string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
******************************************************************************/
static uint8_t COMMAND_InvokeStopEM(uint8_t *arg_str)
{
    CMD_SendString((uint8_t *)"\n\rStopping EM...");
    if (EM_Stop() == EM_OK)
    {
        CMD_SendString((uint8_t *)"OK\n\r");
    }
    else
    {
        CMD_SendString((uint8_t *)"FAILED\n\r");
    }
    
    return 0;
}

/******************************************************************************
* Function Name    : static uint8_t COMMAND_InvokeRestartEM(uint8_t *arg_str)
* Description      : Command Invoke Restart EM
* Arguments        : uint8_t index: Command index
*                  : uint8_t *arg_str: Arguments string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
******************************************************************************/
static uint8_t COMMAND_InvokeRestartEM(uint8_t *arg_str)
{
    CMD_SendString((uint8_t *)"\n\r Backup system state before reset...");
    STORAGE_Backup(STORAGE_ITEM_SYS_STATE);
    
    CMD_SendString((uint8_t *)"\n\r Prepare MCU software reset...reset immediately... \n\r");
    
    WRP_EXT_SoftReset();
    
    return 0;
}

/******************************************************************************
* Function Name    : static uint8_t COMMAND_InvokeDisplay(uint8_t *arg_str)
* Description      : Command Invoke Display
* Arguments        : uint8_t index: Command index
*                  : uint8_t *arg_str: Arguments string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
******************************************************************************/
//extern float32_t RTC_COMP_GetTemperature(uint8_t *out_mode, uint16_t *out_counter, float32_t * out_vs);
static uint8_t COMMAND_InvokeDisplay(uint8_t *arg_str)
{
    static const uint8_t param_format_angle[] = "| %- 32s | (to %1s) %# 8.3f | (to %1s) %# 8.3f | (to %1s) %# 8.3f | %# 15.3f | %# 15.3f | %- 15s|\n\r";
    static const uint8_t param_format_u[] = "| %- 32s | %# 15u | %# 15u | %# 15u | %# 15u | %# 15u | %- 15s|\n\r";
    float32_t   temps_degree;
    uint8_t     tariff_number;
    EM_INST_READ_PARAMS params;

    /* Pull global variables to local first */
    params = g_inst_read_params;

    CMD_Printf((uint8_t *)"\n\rWaiting for signal stable..."); 
    CMD_Printf((uint8_t *)"\n\r"); 
    
    tariff_number = g_tariff.current_tariff_no;
    //EM_GetInstData(&params);

    g_em_core_data.vrms[LINE_PHASE_R]                       = params.vrms[LINE_PHASE_R];
    g_em_core_data.vrms[LINE_PHASE_Y]                       = params.vrms[LINE_PHASE_Y];
    g_em_core_data.vrms[LINE_PHASE_B]                       = params.vrms[LINE_PHASE_B];
    g_em_core_data.vrms[LINE_TOTAL]                         = params.vrms[LINE_TOTAL];

    g_em_core_data.irms[LINE_PHASE_R]                       = params.irms[LINE_PHASE_R];
    g_em_core_data.irms[LINE_PHASE_Y]                       = params.irms[LINE_PHASE_Y];
    g_em_core_data.irms[LINE_PHASE_B]                       = params.irms[LINE_PHASE_B];
    g_em_core_data.irms[LINE_NEUTRAL]                       = params.irms[LINE_NEUTRAL];
    g_em_core_data.irms[LINE_TOTAL]                         = params.irms[LINE_TOTAL];
    g_em_core_data.vector_sum_irms                          = params.vector_sum_irms;

    g_em_core_data.power_factor[LINE_PHASE_R]               = params.power_factor[LINE_PHASE_R];
    g_em_core_data.power_factor[LINE_PHASE_Y]               = params.power_factor[LINE_PHASE_Y];
    g_em_core_data.power_factor[LINE_PHASE_B]               = params.power_factor[LINE_PHASE_B];
    g_em_core_data.power_factor[LINE_TOTAL]                 = params.power_factor[LINE_TOTAL];

    g_em_core_data.power_factor_sign[LINE_PHASE_R]          = params.power_factor_sign[LINE_PHASE_R];
    g_em_core_data.power_factor_sign[LINE_PHASE_Y]          = params.power_factor_sign[LINE_PHASE_Y];
    g_em_core_data.power_factor_sign[LINE_PHASE_B]          = params.power_factor_sign[LINE_PHASE_B];
    g_em_core_data.power_factor_sign[LINE_TOTAL]            = params.power_factor_sign[LINE_TOTAL];

    g_em_core_data.freq[LINE_PHASE_R]                       = params.freq[LINE_PHASE_R];
    g_em_core_data.freq[LINE_PHASE_Y]                       = params.freq[LINE_PHASE_Y];
    g_em_core_data.freq[LINE_PHASE_B]                       = params.freq[LINE_PHASE_B];
    g_em_core_data.freq[LINE_NEUTRAL]                       = params.freq[LINE_NEUTRAL];
    g_em_core_data.freq[LINE_TOTAL]                         = params.freq[LINE_TOTAL];

    g_em_core_data.active_power[LINE_PHASE_R]               = params.active_power[LINE_PHASE_R];
    g_em_core_data.active_power[LINE_PHASE_Y]               = params.active_power[LINE_PHASE_Y];
    g_em_core_data.active_power[LINE_PHASE_B]               = params.active_power[LINE_PHASE_B];
    g_em_core_data.active_power[LINE_TOTAL]                 = params.active_power[LINE_TOTAL];

    g_em_core_data.reactive_power[LINE_PHASE_R]             = params.reactive_power[LINE_PHASE_R];
    g_em_core_data.reactive_power[LINE_PHASE_Y]             = params.reactive_power[LINE_PHASE_Y];
    g_em_core_data.reactive_power[LINE_PHASE_B]             = params.reactive_power[LINE_PHASE_B];
    g_em_core_data.reactive_power[LINE_TOTAL]               = params.reactive_power[LINE_TOTAL];

    g_em_core_data.apparent_power[LINE_PHASE_R]             = params.apparent_power[LINE_PHASE_R];
    g_em_core_data.apparent_power[LINE_PHASE_Y]             = params.apparent_power[LINE_PHASE_Y];
    g_em_core_data.apparent_power[LINE_PHASE_B]             = params.apparent_power[LINE_PHASE_B];
    g_em_core_data.apparent_power[LINE_TOTAL]               = params.apparent_power[LINE_TOTAL];

    g_em_core_data.fundamental_vrms[LINE_PHASE_R]           = params.fundamental_vrms[LINE_PHASE_R];
    g_em_core_data.fundamental_vrms[LINE_PHASE_Y]           = params.fundamental_vrms[LINE_PHASE_Y];
    g_em_core_data.fundamental_vrms[LINE_PHASE_B]           = params.fundamental_vrms[LINE_PHASE_B];
    g_em_core_data.fundamental_vrms[LINE_TOTAL]             = params.fundamental_vrms[LINE_TOTAL];

    g_em_core_data.fundamental_irms[LINE_PHASE_R]           = params.fundamental_irms[LINE_PHASE_R];
    g_em_core_data.fundamental_irms[LINE_PHASE_Y]           = params.fundamental_irms[LINE_PHASE_Y];
    g_em_core_data.fundamental_irms[LINE_PHASE_B]           = params.fundamental_irms[LINE_PHASE_B];
    g_em_core_data.fundamental_irms[LINE_TOTAL]             = params.fundamental_irms[LINE_TOTAL];

    g_em_core_data.fundamental_power[LINE_PHASE_R]          = params.fundamental_power[LINE_PHASE_R];
    g_em_core_data.fundamental_power[LINE_PHASE_Y]          = params.fundamental_power[LINE_PHASE_Y];
    g_em_core_data.fundamental_power[LINE_PHASE_B]          = params.fundamental_power[LINE_PHASE_B];
    g_em_core_data.fundamental_power[LINE_TOTAL]            = params.fundamental_power[LINE_TOTAL];
    
    g_em_core_data.voltage_thd[LINE_PHASE_R]                = params.voltage_thd[LINE_PHASE_R];
    g_em_core_data.voltage_thd[LINE_PHASE_Y]                = params.voltage_thd[LINE_PHASE_Y];
    g_em_core_data.voltage_thd[LINE_PHASE_B]                = params.voltage_thd[LINE_PHASE_B];
    g_em_core_data.voltage_thd[LINE_TOTAL]                  = params.voltage_thd[LINE_TOTAL];

    g_em_core_data.current_thd[LINE_PHASE_R]                = params.current_thd[LINE_PHASE_R];
    g_em_core_data.current_thd[LINE_PHASE_Y]                = params.current_thd[LINE_PHASE_Y];
    g_em_core_data.current_thd[LINE_PHASE_B]                = params.current_thd[LINE_PHASE_B];
    g_em_core_data.current_thd[LINE_TOTAL]                  = params.current_thd[LINE_TOTAL];

    g_em_core_data.power_thd[LINE_PHASE_R]                  = params.power_thd[LINE_PHASE_R];
    g_em_core_data.power_thd[LINE_PHASE_Y]                  = params.power_thd[LINE_PHASE_Y];
    g_em_core_data.power_thd[LINE_PHASE_B]                  = params.power_thd[LINE_PHASE_B];
    g_em_core_data.power_thd[LINE_TOTAL]                    = params.power_thd[LINE_TOTAL];

    g_em_core_data.phase_angle[LINE_PHASE_R]                = params.phase_angle[LINE_PHASE_R];
    g_em_core_data.phase_angle[LINE_PHASE_Y]                = params.phase_angle[LINE_PHASE_Y];
    g_em_core_data.phase_angle[LINE_PHASE_B]                = params.phase_angle[LINE_PHASE_B];

    g_em_core_data.current_phase_angle[LINE_PHASE_R]        = params.current_phase_angle[LINE_PHASE_R];
    g_em_core_data.current_phase_angle[LINE_PHASE_Y]        = params.current_phase_angle[LINE_PHASE_Y];
    g_em_core_data.current_phase_angle[LINE_PHASE_B]        = params.current_phase_angle[LINE_PHASE_B];

    g_em_core_data.current_neutral_angle[LINE_PHASE_R]      = params.current_neutral_angle[LINE_PHASE_R];
    g_em_core_data.current_neutral_angle[LINE_PHASE_Y]      = params.current_neutral_angle[LINE_PHASE_Y];
    g_em_core_data.current_neutral_angle[LINE_PHASE_B]      = params.current_neutral_angle[LINE_PHASE_B];
    
    g_em_core_data.energy_total_import_active               = R_TARIFF_GetImportActiveEnergyTotal();
    g_em_core_data.energy_total_import_capacitive_reactive  = R_TARIFF_GetImportCapacitiveReactiveEnergyTotal();
    g_em_core_data.energy_total_import_inductive_reactive   = R_TARIFF_GetImportInductiveReactiveEnergyTotal();
    g_em_core_data.energy_total_import_apparent             = R_TARIFF_GetImportApparentEnergyTotal();
    g_em_core_data.energy_total_export_active               = R_TARIFF_GetExportActiveEnergyTotal();
    g_em_core_data.energy_total_export_capacitive_reactive  = R_TARIFF_GetExportCapacitiveReactiveEnergyTotal();
    g_em_core_data.energy_total_export_inductive_reactive   = R_TARIFF_GetExportInductiveReactiveEnergyTotal();
    g_em_core_data.energy_total_export_apparent             = R_TARIFF_GetExportApparentEnergyTotal();

    R_TARIFF_GetImportActiveEnergyTariff              (tariff_number, &g_em_core_data.energy_tariff_import_active);
    R_TARIFF_GetImportCapacitiveReactiveEnergyTariff  (tariff_number, &g_em_core_data.energy_tariff_import_capacitive_reactive);
    R_TARIFF_GetImportInductiveReactiveEnergyTariff   (tariff_number, &g_em_core_data.energy_tariff_import_inductive_reactive);
    R_TARIFF_GetImportApparentEnergyTariff            (tariff_number, &g_em_core_data.energy_tariff_import_apparent);
    R_TARIFF_GetExportActiveEnergyTariff              (tariff_number, &g_em_core_data.energy_tariff_export_active);
    R_TARIFF_GetExportCapacitiveReactiveEnergyTariff  (tariff_number, &g_em_core_data.energy_tariff_export_capacitive_reactive);
    R_TARIFF_GetExportInductiveReactiveEnergyTariff   (tariff_number, &g_em_core_data.energy_tariff_export_inductive_reactive);
    R_TARIFF_GetExportApparentEnergyTariff            (tariff_number, &g_em_core_data.energy_tariff_export_apparent);

    g_em_core_data.mdm_active               = R_MDM_GetActiveMaxDemand();
    g_em_core_data.mdm_capacitive_reactive  = R_MDM_GetCapacitiveReactiveMaxDemand();
    g_em_core_data.mdm_inductive_reactive   = R_MDM_GetInductiveReactiveMaxDemand();
    g_em_core_data.mdm_apparent             = R_MDM_GetApparentMaxDemand();

    //temps_degree                            = RTC_COMP_GetTemperature(NULL, NULL, NULL);
    
/* Display table */
    CMD_Printf((uint8_t *)"Instantaneous parameters: \n\r");
    CMD_SendString((uint8_t *)line_break);
    CMD_Printf((uint8_t *)"| %- 32s | %- 15s | %- 15s | %- 15s | %- 15s | %- 15s | %- 15s|\n\r", "Parameter", "Phase R", "Phase Y", "Phase B", "Neutral", "Total", "Unit");
    CMD_SendString((uint8_t *)line_break);

	CMD_Printf(
        (uint8_t *)param_format_angle, 
        "Phase angle",
        "Y", g_em_core_data.phase_angle[LINE_PHASE_R],
        "B", g_em_core_data.phase_angle[LINE_PHASE_Y],
        "R", g_em_core_data.phase_angle[LINE_PHASE_B],
        0.0f,
        0.0f,
        "Degree"
    );
    
    CMD_Printf(
        (uint8_t *)param_format_angle, 
        "Current angle",
        "Y", g_em_core_data.current_phase_angle[LINE_PHASE_R],
        "B", g_em_core_data.current_phase_angle[LINE_PHASE_Y],
        "R", g_em_core_data.current_phase_angle[LINE_PHASE_B],
        0.0f,
        0.0f,
        "Degree"
    );
    
    CMD_Printf(
        (uint8_t *)param_format_angle, 
        "Neutral angle",
        "Y",g_em_core_data.current_neutral_angle[LINE_PHASE_R],
        "B",g_em_core_data.current_neutral_angle[LINE_PHASE_Y],
        "R",g_em_core_data.current_neutral_angle[LINE_PHASE_B],
        0.0f,
        0.0f,
        "Degree"
    );
    CMD_Printf(
        (uint8_t *)param_format,
        "Voltage RMS",
        g_em_core_data.vrms[LINE_PHASE_R],
        g_em_core_data.vrms[LINE_PHASE_Y],
        g_em_core_data.vrms[LINE_PHASE_B],
        0.0f,
        g_em_core_data.vrms[LINE_TOTAL],
        "Volt"
    );

    CMD_Printf(
        (uint8_t *)param_format, 
        "Current RMS",
        g_em_core_data.irms[LINE_PHASE_R],
        g_em_core_data.irms[LINE_PHASE_Y],
        g_em_core_data.irms[LINE_PHASE_B],
        g_em_core_data.irms[LINE_NEUTRAL],
        g_em_core_data.irms[LINE_TOTAL],
        "Ampere"
    );

    CMD_Printf(
        (uint8_t *)param_format, 
        "Current Sum Vector",
        0.0f,
        0.0f,
        0.0f,
        g_em_core_data.vector_sum_irms,
        0.0f,
        "Ampere"
    );  
    
    CMD_Printf(
        (uint8_t *)param_format, 
        "Power Factor",
        g_em_core_data.power_factor[LINE_PHASE_R],
        g_em_core_data.power_factor[LINE_PHASE_Y],
        g_em_core_data.power_factor[LINE_PHASE_B],
        0.0f,
        g_em_core_data.power_factor[LINE_TOTAL],
        " "
    );  
    
    CMD_Printf(
        (uint8_t *)param_format_s, 
        "Power Factor Sign",
        COMMAND_GetPowerFactorSignName(g_em_core_data.power_factor_sign[LINE_PHASE_R]),
        COMMAND_GetPowerFactorSignName(g_em_core_data.power_factor_sign[LINE_PHASE_Y]),
        COMMAND_GetPowerFactorSignName(g_em_core_data.power_factor_sign[LINE_PHASE_B]),
        " ",
        COMMAND_GetPowerFactorSignName(g_em_core_data.power_factor_sign[LINE_TOTAL]),
        " "
    );  
    
    CMD_Printf(
        (uint8_t *)param_format,
        "Line Frequency",
        g_em_core_data.freq[LINE_PHASE_R],
        g_em_core_data.freq[LINE_PHASE_Y],
        g_em_core_data.freq[LINE_PHASE_B],
        g_em_core_data.freq[LINE_NEUTRAL],
        g_em_core_data.freq[LINE_TOTAL] ,
        "Hz"
    );

    CMD_SendString((uint8_t *)line_break);
    
    /* Power */
    CMD_Printf(
        (uint8_t *)param_format,
        "Active Power",
        g_em_core_data.active_power[LINE_PHASE_R],
        g_em_core_data.active_power[LINE_PHASE_Y],
        g_em_core_data.active_power[LINE_PHASE_B],
        0.0f,
        g_em_core_data.active_power[LINE_TOTAL],
        "Watt"
    );

    CMD_Printf(
        (uint8_t *)param_format,
        "Reactive Power",
        g_em_core_data.reactive_power[LINE_PHASE_R],
        g_em_core_data.reactive_power[LINE_PHASE_Y],
        g_em_core_data.reactive_power[LINE_PHASE_B],
        0.0f,
        g_em_core_data.reactive_power[LINE_TOTAL],
        "VAr"
    );
    CMD_Printf(
        (uint8_t *)param_format,
        "Apparent Power",
        g_em_core_data.apparent_power[LINE_PHASE_R],
        g_em_core_data.apparent_power[LINE_PHASE_Y],
        g_em_core_data.apparent_power[LINE_PHASE_B],
        0.0f,
        g_em_core_data.apparent_power[LINE_TOTAL],
        "VA"
    );
    
	CMD_SendString((uint8_t *)line_break);
	
    /* Fundamental */
    CMD_Printf(
        (uint8_t *)param_format, 
        "Filtered Voltage RMS",
        g_em_core_data.fundamental_vrms[LINE_PHASE_R],
        g_em_core_data.fundamental_vrms[LINE_PHASE_Y],
        g_em_core_data.fundamental_vrms[LINE_PHASE_B],
        0.0f,
        g_em_core_data.fundamental_vrms[LINE_TOTAL],
        "Volt"
    );
    
    CMD_Printf(
        (uint8_t *)param_format, 
        "Filtered Current RMS",
        g_em_core_data.fundamental_irms[LINE_PHASE_R],
        g_em_core_data.fundamental_irms[LINE_PHASE_Y],
        g_em_core_data.fundamental_irms[LINE_PHASE_B],
        0.0f,
        g_em_core_data.fundamental_irms[LINE_TOTAL],
        "Ampere"
    );
    
    CMD_Printf(
        (uint8_t *)param_format, 
        "Fund Active Power",
        g_em_core_data.fundamental_power[LINE_PHASE_R],
        g_em_core_data.fundamental_power[LINE_PHASE_Y],
        g_em_core_data.fundamental_power[LINE_PHASE_B],
        0.0f,
        g_em_core_data.active_power[LINE_TOTAL],
        "Watt"
    );
    
    CMD_Printf(
        (uint8_t *)param_format, 
        "Voltage THD",
        g_em_core_data.voltage_thd[LINE_PHASE_R],
        g_em_core_data.voltage_thd[LINE_PHASE_Y],
        g_em_core_data.voltage_thd[LINE_PHASE_B],
        0.0f,
        g_em_core_data.voltage_thd[LINE_TOTAL],
        "Percent"
    );
    
    CMD_Printf(
        (uint8_t *)param_format, 
        "Current THD",
        g_em_core_data.current_thd[LINE_PHASE_R],
        g_em_core_data.current_thd[LINE_PHASE_Y],
        g_em_core_data.current_thd[LINE_PHASE_B],
        0.0f,
        g_em_core_data.current_thd[LINE_TOTAL],
        "Percent"
    );
    
    CMD_Printf(
        (uint8_t *)param_format, 
        "Active Power THD",
        g_em_core_data.power_thd[LINE_PHASE_R],
        g_em_core_data.power_thd[LINE_PHASE_Y],
        g_em_core_data.power_thd[LINE_PHASE_B],
        0.0f,
        g_em_core_data.power_thd[LINE_TOTAL],
        "Percent"
    );
    
    /* Energy total (sum all tariff) */
    CMD_SendString((uint8_t *)line_break);

    CMD_Printf(
        (uint8_t *)param_format, 
        "Import Active Energy",
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        g_em_core_data.energy_total_import_active,
        "kWh"
    );
    CMD_Printf(
        (uint8_t *)param_format,
        "Import Reactive Energy (C)",
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        g_em_core_data.energy_total_import_capacitive_reactive,
        "kVArh"
    );
    CMD_Printf(
        (uint8_t *)param_format,
        "Import Reactive Energy (L)",
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        g_em_core_data.energy_total_import_inductive_reactive,
        "kVArh"
    );
    CMD_Printf(
        (uint8_t *)param_format,
        "Import Apparent Energy",
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        g_em_core_data.energy_total_import_apparent,
        "kVAh"
    );

    CMD_Printf(
        (uint8_t *)param_format, 
        "Export Active Energy",
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        g_em_core_data.energy_total_export_active,
        "kWh"
    );
    CMD_Printf(
        (uint8_t *)param_format, 
        "Export Reactive Energy (C)",
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        g_em_core_data.energy_total_export_capacitive_reactive,
        "kVArh"
    );
    CMD_Printf(
        (uint8_t *)param_format, 
        "Export Reactive Energy (L)",
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        g_em_core_data.energy_total_export_inductive_reactive,
        "kVArh"
    );
    CMD_Printf(
        (uint8_t *)param_format, 
        "Export Apparent Energy",
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        g_em_core_data.energy_total_export_apparent,
        "kVAh"
    );

    /* Energy tariff */
    CMD_SendString((uint8_t *)line_break);

    CMD_Printf(
        (uint8_t *)param_format_tariff,
        "Import Active Energy",
        tariff_number,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        g_em_core_data.energy_tariff_import_active,
        "kWh"
    );
    CMD_Printf(
        (uint8_t *)param_format_tariff,
        "Import Reactive Energy (C)",
        tariff_number,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        g_em_core_data.energy_tariff_import_capacitive_reactive,
        "kVArh"
    );
    CMD_Printf(
        (uint8_t *)param_format_tariff,
        "Import Reactive Energy (L)",
        tariff_number,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        g_em_core_data.energy_tariff_import_inductive_reactive,
        "kVArh"
    );
    CMD_Printf(
        (uint8_t *)param_format_tariff,
        "Import Apparent Energy",
        tariff_number,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        g_em_core_data.energy_tariff_import_apparent,
        "kVAh"
    );

    CMD_Printf(
        (uint8_t *)param_format_tariff,
        "Export Active Energy",
        tariff_number,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        g_em_core_data.energy_tariff_export_active,
        "kWh"
    );
    CMD_Printf(
        (uint8_t *)param_format_tariff,
        "Export Reactive Energy (C)",
        tariff_number,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        g_em_core_data.energy_tariff_export_capacitive_reactive,
        "kVArh"
    );
    CMD_Printf(
        (uint8_t *)param_format_tariff,
        "Export Reactive Energy (L)",
        tariff_number,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        g_em_core_data.energy_tariff_export_inductive_reactive,
        "kVArh"
    );
    CMD_Printf(
        (uint8_t *)param_format_tariff,
        "Export Apparent Energy",
        tariff_number,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        g_em_core_data.energy_tariff_export_apparent,
        "kVAh"
    );

    CMD_SendString((uint8_t *)line_break);

    CMD_Printf(
        (uint8_t *)param_format, 
        "Active Max Demand",
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        g_em_core_data.mdm_active,
        "kW"
    );
    CMD_Printf(
        (uint8_t *)param_format, 
        "Reactive Max Demand (C)",
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        g_em_core_data.mdm_capacitive_reactive,
        "kVAr"
    );
    CMD_Printf(
        (uint8_t *)param_format,
        "Reactive Max Demand (L)",
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        g_em_core_data.mdm_inductive_reactive,
        "kVAr"
    );
    CMD_Printf(
        (uint8_t *)param_format, 
        "Apparent Max Demand",
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        g_em_core_data.mdm_apparent,
        "kVA"
    );

    CMD_SendString((uint8_t *)line_break);

//    CMD_Printf(
//        (uint8_t *)param_format, 
//        "Ambient Temperature",
//        temps_degree,
//        "degree.C"
//    );
    
    CMD_SendString((uint8_t *)"\n");
    if (EVENT_IsCaseOpen() == 1)
    {
        CMD_SendString((uint8_t *)"CASE OPEN!\n");
    }
    if (EVENT_IsMagnetic() == 1)
    {
        CMD_SendString((uint8_t *)"MAG!\n");
    }
    if (EVENT_IsLastGasp() == 1)
    {
        CMD_SendString((uint8_t *)"Last Gasp!\n");
    }
//    CMD_SendString((uint8_t *)line_break);
    
    return 0;
}

/***********************************************************************************************************************
* Function Name    : static uint8_t COMMAND_InvokeRtc(uint8_t *arg_str)
* Description      : Command Invoke RTC
* Arguments        : uint8_t index: Command index
*                  : uint8_t *arg_str: Arguments string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
***********************************************************************************************************************/
static uint8_t COMMAND_InvokeRtc(uint8_t *arg_str)
{
    rtc_counter_value_t rtctime;
    
    R_RTC_Get_CalendarCounterValue(&rtctime);
    
    CMD_Printf((uint8_t *)"\n\rRTC Time: %02x/%02x/20%02x %02x:%02x:%02x %02x\n\r",
                rtctime.day,
                rtctime.month,
                rtctime.year,
                rtctime.hour,
                rtctime.min,
                rtctime.sec,
                rtctime.week);
                
    return 0;
}
/******************************************************************************
* Function Name : R_Calculate_Week
* Interface     : void R_Calculate_Week(
*               :     uint16_t year, uint16_t month, uint16_t day
*               : );
* Description   : Calculate day of week from day-month-year
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
uint8_t R_Calculate_Week ( uint8_t year_in, uint8_t month, uint8_t day )
{
    uint16_t adjustment, mm, yy, year;
    year = 2000 + year_in;
    /* Rosetta Code */
    adjustment = (14 - month) / 12;
    mm = month + 12 * adjustment - 2;
    yy = year - adjustment;

    adjustment = (day + (13 * mm - 1) / 5 + yy + yy / 4 - yy / 100 + yy / 400) % 7;

    return (adjustment);
}
/***********************************************************************************************************************
* Function Name    : static uint8_t COMMAND_InvokeSetRtc(uint8_t *arg_str)
* Description      : Command Invoke Set RTC
* Arguments        : uint8_t index: Command index
*                  : uint8_t *arg_str: Arguments string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
***********************************************************************************************************************/
static uint8_t COMMAND_InvokeSetRtc(uint8_t *arg_str)
{   
    //uint16_t timeout;
    uint8_t status;
    rtc_counter_value_t rtctime;
    uint8_t buffer[20];

    CMD_SendString((uint8_t *)"\n\rParameter(s): ");
    CMD_SendString((uint8_t *)arg_str);
    CMD_SendString((uint8_t *)"\n\r");
    
    /* Get Day parameter */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" /");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        /* get number */
        rtctime.day = (uint8_t)atoi((char *)buffer);
    }
    else
    {
        CMD_SendString((uint8_t *)"Parameter error\n\r");
        return 1;
    }
    
    /* Get Month parameter */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" /", (uint8_t *)" /");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        /* get number */
        rtctime.month = (uint8_t)atoi((char *)buffer);
    }
    else
    {
        CMD_SendString((uint8_t *)"Parameter error\n\r");
        return 1;
    }
    
    /* Get Year parameter */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" /", (uint8_t *)" ");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        /* get number */
        rtctime.year = (uint16_t)atoi((char *)buffer);
    }
    else
    {
        CMD_SendString((uint8_t *)"Parameter error\n\r");
        return 1;
    }
    
    /* Get Hour parameter */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" :");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        /* get number */
        rtctime.hour = (uint8_t)atoi((char *)buffer);
    }
    else
    {
        CMD_SendString((uint8_t *)"Parameter error\n\r");
        return 1;
    }

    /* Get Min parameter */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" :", (uint8_t *)" :");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        /* get number */
        rtctime.min = (uint8_t)atoi((char *)buffer);
    }
    else
    {
        CMD_SendString((uint8_t *)"Parameter error\n\r");
        return 1;
    }
    
    /* Get Sec parameter */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" :", (uint8_t *)" ");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        /* get number */
        rtctime.sec = (uint8_t)atoi((char *)buffer);
    }
    else
    {
        CMD_SendString((uint8_t *)"Parameter error\n\r");
        return 1;
    }
    
    /* Get Week parameter */
    rtctime.week = R_Calculate_Week(rtctime.year, rtctime.month, rtctime.day);

    rtctime.day = WRP_EXT_Dec2Bcd(rtctime.day);
    rtctime.month = WRP_EXT_Dec2Bcd(rtctime.month);
    rtctime.year  = WRP_EXT_Dec2Bcd(rtctime.year);
    rtctime.hour  = WRP_EXT_Dec2Bcd(rtctime.hour);
    rtctime.min = WRP_EXT_Dec2Bcd(rtctime.min);
    rtctime.sec = WRP_EXT_Dec2Bcd(rtctime.sec);
    rtctime.week = WRP_EXT_Dec2Bcd(rtctime.week);

    CMD_SendString((uint8_t *)"Set RTC time...");
    
    R_HANDLER_BackupBeforeApplyNewRTCValue(&rtctime);
    R_RTC_Set_CalendarCounterValue(rtctime);
    R_HANDLER_AfterApplyNewRTCValue();

    status = MD_OK;
    
    if (status == MD_OK)
    {
        CMD_SendString((uint8_t *)"OK\n\r");
    }
    else
    {
        CMD_SendString((uint8_t *)"FAILED\n\r");
    }
    
    return 0;
}

/***********************************************************************************************************************
* Function Name    : static uint8_t COMMAND_InvokeBackup(uint8_t *arg_str)
* Description      : Command Invoke Backup
* Arguments        : uint8_t index: Command index
*                  : uint8_t *arg_str: Arguments string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
***********************************************************************************************************************/
static uint8_t COMMAND_InvokeBackup(uint8_t *arg_str)
{
    uint8_t selection;
    uint8_t buffer[20];
    uint8_t b_found;
    
    CMD_SendString((uint8_t *)"\n\rParameter(s): ");
    CMD_SendString((uint8_t *)arg_str);
    CMD_SendString((uint8_t *)"\n\r");
    
    /* Get Selection parameter */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" ");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        /* Get hex first */
        selection = (uint8_t)COMMAND_HexStringToUnsigned16(buffer, &b_found);
        
        /* next for get number */
        if (b_found == 0)
        {
            selection = (uint8_t)atoi((char *)buffer);
        }
                
        if ((selection == CONFIG_ITEM_NONE) || (selection == STORAGE_ITEM_NONE))
        {
            CMD_SendString((uint8_t *)"Parameter error\n\r");
            return 1;       
        }
        
        /* Backup Item */
        CMD_SendString((uint8_t *)"Backup Item: ");
        if (selection & CONFIG_ITEM_CONFIG)
        {
            CMD_SendString((uint8_t *)"Configuration ");
        }
        if (selection & CONFIG_ITEM_CALIB)
        {
            CMD_SendString((uint8_t *)"Calibration ");
        }
        if (selection & STORAGE_ITEM_SYS_STATE)
        {
            CMD_SendString((uint8_t *)"System State ");
        }
            
        CMD_SendString((uint8_t *)"...");
        
        if (CONFIG_Backup(selection) != CONFIG_OK)
        {
            CMD_SendString((uint8_t *)"FAILED\n\r");
        }
        else
        {
            CMD_SendString((uint8_t *)"OK\n\r");
        }
        
        if (STORAGE_Backup(selection) != STORAGE_OK)
        {
            CMD_SendString((uint8_t *)"FAILED\n\r");
        }
        else
        {
            CMD_SendString((uint8_t *)"OK\n\r");
        }
    }
    else
    {
        CMD_SendString((uint8_t *)"Parameter error\n\r");
        return 1;
    }
    
    return 0;
}

/***********************************************************************************************************************
* Function Name    : static uint8_t COMMAND_InvokeRestore(uint8_t *arg_str)
* Description      : Command Invoke Restore
* Arguments        : uint8_t index: Command index
*                  : uint8_t *arg_str: Arguments string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
***********************************************************************************************************************/
static uint8_t COMMAND_InvokeRestore(uint8_t *arg_str)
{
    uint8_t selection;
    uint8_t buffer[20];
    uint8_t b_found;
    
    CMD_SendString((uint8_t *)"\n\rParameter(s): ");
    CMD_SendString((uint8_t *)arg_str);
    CMD_SendString((uint8_t *)"\n\r");
    
    /* Get Selection parameter */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" ");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        /* Get hex first */
        selection = (uint8_t)COMMAND_HexStringToUnsigned16(buffer, &b_found);
        
        /* next for get number */
        if (b_found == 0)
        {
            selection = (uint8_t)atoi((char *)buffer);
        }
                
        if (selection == STORAGE_ITEM_NONE)
        {
            CMD_SendString((uint8_t *)"Parameter error\n\r");
            return 1;       
        }
        
        
        /* Backup Item */
        CMD_SendString((uint8_t *)"Backup Item: ");
        if (selection & CONFIG_ITEM_CONFIG)
        {
            CMD_SendString((uint8_t *)"Configuration ");
        }
        if (selection & CONFIG_ITEM_CALIB)
        {
            CMD_SendString((uint8_t *)"Calibration ");
        }
        if (selection & STORAGE_ITEM_SYS_STATE)
        {
            CMD_SendString((uint8_t *)"System State ");
        }
    
        CMD_SendString((uint8_t *)"...");
        
        EM_Stop();
        /* Restore */
        
        if (CONFIG_Restore(selection) != CONFIG_OK)
        {
            CMD_SendString((uint8_t *)"FAILED\n\r");
            
        }
        else
        {
            CMD_SendString((uint8_t *)"OK\n\r");
        }
        
        if (STORAGE_Restore(selection) != STORAGE_OK)
        {
            CMD_SendString((uint8_t *)"FAILED\n\r");
           
        }
        else
        {
            CMD_SendString((uint8_t *)"OK\n\r");
        }
        
        EM_Start();
    }
    else
    {
        CMD_SendString((uint8_t *)"Parameter error\n\r");
        return 1;
    }
    
    return 0;
}

/***********************************************************************************************************************
* Function Name    : static uint8_t COMMAND_InvokeReadMemory(uint8_t *arg_str)
* Description      : Command Invoke Read Memory
* Arguments        : uint8_t index: Command index
*                  : uint8_t *arg_str: Arguments string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
***********************************************************************************************************************/
static uint8_t COMMAND_InvokeReadMemory(uint8_t *arg_str)
{
    static const uint16_t type_cast_size[7] =
    {
        1,  /* uint8_t */
        1,  /* int8_t */
        2,  /* uint16_t */
        2,  /* int16_t */
        4,  /* uint32_t */
        4,  /* int32_t */
        4,  /* float32_t */
    };
    
    uint32_t    addr;
    uint16_t    size, i, pagesize, count;
    uint8_t     b_found = 0;
    uint8_t     buffer[32];
    int8_t      cast_id = -1;
    uint16_t    u16;
    uint32_t    u32;
    float32_t   f32;
    uint8_t     mem_type;
    uint8_t const * p_mem_name;
    
    uint8_t (*FUNC_MemRead)(uint32_t addr, uint8_t *buf, uint16_t size);
    
    CMD_SendString((uint8_t *)"\n\rParameter(s): ");
    CMD_SendString((uint8_t *)arg_str);
    CMD_SendString((uint8_t *)"\n\r");
    
    /* Get memory type parameter */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" /");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        mem_type = buffer[0] - '0';
        
        if (mem_type == 0)
        {
            FUNC_MemRead = EPR_Read;
            p_mem_name = g_mem_epr;
        }
        else if (mem_type == 1)
        {
            FUNC_MemRead = DATAFLASH_Read;
            p_mem_name = g_mem_dtfl;
        }
        else if (mem_type == 2)
        {
            FUNC_MemRead = BL_SFL_DeviceRead;
            p_mem_name = g_mem_extflash;
        }
        else
        {
            CMD_SendString((uint8_t *)"\n\rUnsupported memery type!");
            return 1;
        }
    }
    else
    {
        CMD_SendString((uint8_t *)"Parameter error\n\r");
        return 1;
    }
    
    /* Get Addr parameter */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" ");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {
        /* Get hex first */
        addr = COMMAND_HexStringToUnsigned16(buffer, &b_found);
        
        /* next for get number */
        if (b_found == 0)
        {
            addr = atol((char *)buffer);
        }
    }
    else
    {
        CMD_SendString((uint8_t *)"Parameter error\n\r");
        return 1;
    }
    
    /* Get Size parameter */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" ");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        /* Get hex first */
        size = COMMAND_HexStringToUnsigned16(buffer, &b_found);
        
        /* next for get number */
        if (b_found == 0)
        {
            size = atoi((char *)buffer);
        }
    }
    else
    {
        CMD_SendString((uint8_t *)"Parameter error\n\r");
        return 1;
    }   
    
    /* Get Cast parameter */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" ");
    if (arg_str != NULL)
    {   
        /* found argument */
        if (strcmp("uint8_t", (const char*)buffer) == 0)
        {
            cast_id = 0;    /* uint8_t */
        }
        else if (strcmp("int8_t", (const char*)buffer) == 0)
        {
            cast_id = 1;    /* int8_t */
        }
        else if (strcmp("uint16_t", (const char*)buffer) == 0)
        {
            cast_id = 2;    /* uint16_t */
        }
        else if (strcmp("int16_t", (const char*)buffer) == 0)
        {
            cast_id = 3;    /* int16_t */
        }
        else if (strcmp("uint32_t", (const char*)buffer) == 0)
        {
            cast_id = 4;    /* uint32_t */
        }
        else if (strcmp("int32_t", (const char*)buffer) == 0)
        {
            cast_id = 5;    /* int32_t */
        }
        else if (strcmp("float32_t", (const char*)buffer) == 0)
        {
            cast_id = 6;    /* float32_t */
        }
        else
        {
            CMD_SendString((uint8_t *)"Parameter error\n\r");
            return 1;
        }
    }
    
    if (cast_id != -1)
    {
        CMD_Printf((uint8_t *)"\n\r--- %s Data (cast by %s) ---\n\r",p_mem_name, buffer);
    }
    else
    {
        CMD_Printf((uint8_t *)"\n\r--- %s Data (HEX, Max 1line = 32 bytes) ---\n\r", p_mem_name);   
    }

    count = 0;
    while (size > 0)
    {
        if (size >= 32)
        {
            pagesize = 32;
        }
        else
        {
            pagesize = size;
        }
        
        if (FUNC_MemRead(addr, buffer, pagesize) == EPR_OK)
        {
            if (cast_id != -1)
            {
                for (i = 0; i < pagesize; i += type_cast_size[cast_id])
                {
                    switch (cast_id)
                    {
                        case 0:/* uint8_t */
                            CMD_Printf((uint8_t *)"%05i - 0x%08lx: (0x%02x) %i\n\r", count, addr+i, (uint8_t)buffer[i], (uint8_t)buffer[i]);
                            break;
                            
                        case 1:/* int8_t */
                            CMD_Printf((uint8_t *)"%05i - 0x%08lx: (0x%02x) %i\n\r", count, addr+i, (uint8_t)buffer[i], (int8_t)buffer[i]);
                            break;
                            
                        case 2:/* uint16_t */
                            u16 = COMMAND_GetUnsigned16(&buffer[i]);
                            CMD_Printf((uint8_t *)"%05i - 0x%08lx: (0x%04x) %d\n\r", count, addr+i, u16, u16);
                            break;
                            
                        case 3:/* int16_t */
                            u16 = COMMAND_GetUnsigned16(&buffer[i]);
                            CMD_Printf((uint8_t *)"%05i - 0x%08lx: (0x%04x) %d\n\r", count, addr+i, u16, (int16_t)u16);
                            break;
                            
                        case 4:/* uint32_t */
                            u32 = COMMAND_GetUnsigned32(&buffer[i]);
                            CMD_Printf((uint8_t *)"%05i - 0x%08lx: (0x%08lx) %ld\n\r", count, addr+i, u32, u32);
                            break;
                            
                        case 5:/* int32_t */
                            u32 = COMMAND_GetUnsigned32(&buffer[i]);
                            CMD_Printf((uint8_t *)"%05i - 0x%08lx: (0x%08lx) %ld\n\r", count, addr+i, u32, (int32_t)u32);
                            break;
                            
                        case 6:/* float32_t */
                            u32 = COMMAND_GetUnsigned32(&buffer[i]);
                            f32 = *((float32_t *)&u32);
                            CMD_Printf((uint8_t *)"%05i - 0x%08lx: (0x%08lx) %.06f\n\r", count, addr+i, u32, f32);
                            break;
                            
                        default:
                            CMD_SendString((uint8_t *)"Internal error.\n\r");
                            return 2;
                    }

                    count++;
                }
            }
            else
            {
                for (i = 0; i < pagesize; i++)
                {
                    CMD_Printf((uint8_t *)"%02x ", buffer[i]);
                }
                CMD_SendString((uint8_t *)"\n\r");
            }
            
            /* New page */
            addr += pagesize;
            size -= pagesize;

            /* Break if CTRL+C is pressed */
            if (CMD_IsCtrlKeyReceived())
            {
                CMD_Printf((uint8_t *)"\n\rCTRL + C is pressed! Break!\n\r");
                CMD_AckCtrlKeyReceived();
                
                /* Break printout here */
                break;
            }

            R_WDT_Restart();
        }
        else
        {
            CMD_Printf((uint8_t *)"\n\rRead %s failed at page [addr:0x%04x%04x, size:%i]!\n\r", p_mem_name, (uint16_t)(addr >> 16), (uint16_t)addr, pagesize);
            break;
        }
    }
    
    CMD_Printf((uint8_t *)"--- %s Data -----------------\n\r", p_mem_name);
    
    return 0;
}

/***********************************************************************************************************************
* Function Name    : static uint8_t COMMAND_InvokeWriteMemory(uint8_t *arg_str)
* Description      : Command Invoke Write Memory
* Arguments        : uint8_t index: Command index
*                  : uint8_t *arg_str: Arguments string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
***********************************************************************************************************************/
static uint8_t COMMAND_InvokeWriteMemory(uint8_t *arg_str)
{
    uint32_t    addr;
    uint16_t    size, value, pagesize;
    uint8_t     b_found = 0;
    uint8_t     b_string = 0;
    uint8_t *   p_str_old;
    uint8_t     buffer[32];
    uint8_t     mem_type;
    uint8_t const * p_mem_name;
    
    uint8_t (*FUNC_MemWrite)(uint32_t addr, uint8_t *buf, uint16_t size);
    
    CMD_SendString((uint8_t *)"\n\rParameter(s): ");
    CMD_SendString((uint8_t *)arg_str);
    CMD_SendString((uint8_t *)"\n\r");
    
    /* Get memory type parameter */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" /");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        mem_type = buffer[0] - '0';
        
        if (mem_type)
        {
            FUNC_MemWrite = DATAFLASH_Write;
            p_mem_name = g_mem_dtfl;
        }
        else
        {
            FUNC_MemWrite = EPR_Write;
            p_mem_name = g_mem_epr;
        }
    }
    else
    {
        CMD_SendString((uint8_t *)"Parameter error\n\r");
        return 1;
    }
    
    /* Get Addr parameter */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" ");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        /* Get hex first */
        addr = COMMAND_HexStringToUnsigned16(buffer, &b_found);
        
        /* next for get number */
        if (b_found == 0)
        {
            addr = atol((char *)buffer);
        }
    }
    else
    {
        CMD_SendString((uint8_t *)"Parameter error\n\r");
        return 1;
    }
    
    /* Get Size parameter */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" ");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {
        /* Get hex first */
        size = COMMAND_HexStringToUnsigned16(buffer, &b_found);
        
        /* next for get number */
        if (b_found == 0)
        {
            size = atoi((char *)buffer);
        }
    }
    else
    {
        CMD_SendString((uint8_t *)"Parameter error\n\r");
        return 1;
    }
    
    /* Get string parameter */
    p_str_old = arg_str;
    arg_str   = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" (", (uint8_t *)")");
    
    /* is NOT have string parameter? */ 
    if (arg_str == NULL || *arg_str != ')')
    {
        /* scan number */
        arg_str = COMMAND_GetScanOneParam(buffer, 20, p_str_old, (uint8_t *)" ", (uint8_t *)" ");
        
        if (arg_str != NULL &&
            (buffer[0] >= '0' && buffer[0] <= '9'))
        {       
            /* Get hex first */
            value = COMMAND_HexStringToUnsigned16(buffer, &b_found);
            
            /* next for get number */
            if (b_found == 0)
            {
                value = atoi((char *)buffer);
            }
        }
        else
        {
            CMD_SendString((uint8_t *)"Parameter error\n\r");
            return 1;
        }
    }
    else
    {
        b_string = 1;
    }
    
    if (arg_str == NULL)
    {
        CMD_SendString((uint8_t *)"Parameter error\n\r");
        return 1;
    }   
    
    CMD_Printf((uint8_t *)"Start write to %s...", p_mem_name);
    
    while (size > 0)
    {
        if (size >= 32)
        {
            pagesize = 32;
        }
        else
        {
            pagesize = size;
        }

        if (b_string != 1)      
        {
            memset(buffer, value, pagesize);
        }

        /* write buffer */
        if (FUNC_MemWrite(addr, buffer, pagesize) == EPR_OK)
        {           
            /* New page */
            addr += pagesize;
            size -= pagesize;
        }
        else
        {
            CMD_Printf((uint8_t *)"\n\rWrite %s failed at page [addr:0x%04x%04x, size:%i]!\n\r", p_mem_name, (uint16_t)(addr >> 16), (uint16_t)addr, pagesize);
            return 1;
        }
        
        R_WDT_Restart();
    }
    
    CMD_SendString((uint8_t *)"OK\n\r");    
    
    return 0;
}

/***********************************************************************************************************************
* Function Name    : static uint8_t COMMAND_InvokeReadDTFLHeader(uint8_t *arg_str)
* Description      : Command Invoke Read the DataFlash header byte
* Arguments        : uint8_t *arg_str: Arguments string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
***********************************************************************************************************************/
static uint8_t COMMAND_InvokeReadDTFLHeader(uint8_t *arg_str)
{
    uint8_t status0, status1;
    uint16_t crc0, crc1;
    CMD_SendString((uint8_t *)"\n\r");
    CMD_SendString((uint8_t *)"DataFlash Bank 0 Header Status Read...");
    if (DATAFLASH_ReadHeaderStatus(0, &status0))
    {
        CMD_SendString((uint8_t *)"FAILED\n\r");
        return 1;
    }
    else
    {
        CMD_SendString((uint8_t *)"OK\n\r");
    }
    
    CMD_SendString((uint8_t *)"DataFlash Bank 0 Header CRC Read...");
    if (DATAFLASH_ReadHeaderCRC(0, (uint8_t *)&crc0))
    {
        CMD_SendString((uint8_t *)"FAILED\n\r");
        return 1;
    }
    else
    {
        CMD_SendString((uint8_t *)"OK\n\r");
    }
    
    CMD_SendString((uint8_t *)"DataFlash Bank 1 Header Status Read...");
    if (DATAFLASH_ReadHeaderStatus(1, &status1))
    {
        CMD_SendString((uint8_t *)"FAILED\n\r");
        return 1;
    }
    else
    {
        CMD_SendString((uint8_t *)"OK\n\r");
    }
    
    CMD_SendString((uint8_t *)"DataFlash Bank 1 Header CRC Read...");
    if (DATAFLASH_ReadHeaderCRC(1, (uint8_t *)&crc1))
    {
        CMD_SendString((uint8_t *)"FAILED\n\r");
        return 1;
    }
    else
    {
        CMD_SendString((uint8_t *)"OK\n\r");
    }
    
    
    
    /* Reading OK, print result */
    CMD_Printf((uint8_t *)"\n\r Bank 0, status: %s, CRC: 0x%x", (status0 == 1) ? "valid" : "invalid", crc0);
    CMD_Printf((uint8_t *)"\n\r Bank 1, status: %s, CRC: 0x%x", (status1 == 1) ? "valid" : "invalid", crc1);
    
    return 0;
}

/***********************************************************************************************************************
* Function Name    : static uint8_t COMMAND_InvokeEraseDTFL(uint8_t *arg_str)
* Description      : Command Invoke Erase DataFlash content
* Arguments        : uint8_t *arg_str: Arguments string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
***********************************************************************************************************************/
static uint8_t COMMAND_InvokeEraseDTFL(uint8_t *arg_str)
{
    CMD_SendString((uint8_t *)"\n\r");
    
    CMD_SendString((uint8_t *)"DataFlash Bank0 Clear...");
    if (DATAFLASH_BankErase(0) != DATAFLASH_OK)
    {
        CMD_SendString((uint8_t *)"FAILED\n\r");
        return 1;
    }
    else
    {
        /* OK */
        CMD_SendString((uint8_t *)"OK\n\r");
    }
    
    CMD_SendString((uint8_t *)"DataFlash Bank1 Clear...");
    if (DATAFLASH_BankErase(1) != DATAFLASH_OK)
    {
        CMD_SendString((uint8_t *)"FAILED\n\r");
        return 1;
    }
    else
    {
        /* OK */
        CMD_SendString((uint8_t *)"OK\n\r");
    }
    
    /* Restart the meter right after erase 
     * Purpose: the calibration information is cleared, will cause math error exception in CA
    */
    CMD_SendString((uint8_t *)"Restart meter now...");
    WRP_EXT_SoftReset();
    
    return 0;
}

/******************************************************************************
* Function Name    : static uint8_t COMMAND_InvokeAddEnergyLog(uint8_t *arg_str)
* Description      : Command Invoke Add Energy Log
* Arguments        : uint8_t index: Command index
*                  : uint8_t *arg_str: Arguments string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
******************************************************************************/
static uint8_t COMMAND_InvokeAddEnergyLog(uint8_t *arg_str)
{
    #if 0
    /* Disable this command until upgrading the meter energy and tamper log */
    uint8_t i, num;
    rtc_counter_value_t rtctime;
    ONE_MONTH_ENERGY_DATA_LOG   energy_log;
    
    CMD_Printf((uint8_t *)"\n\rStart to write energy log to EEPROM...");
    
    R_RTC_Get_CalendarCounterValue(&rtctime);
    
    energy_log.present_rtc_log.Sec   = rtctime.sec;     
    energy_log.present_rtc_log.Min   = rtctime.min;     
    energy_log.present_rtc_log.Hour  = rtctime.hour;      
    energy_log.present_rtc_log.Day   = rtctime.day;     
    energy_log.present_rtc_log.Week  = rtctime.week;      
    energy_log.present_rtc_log.Month = rtctime.month;     
    energy_log.present_rtc_log.Year  = (uint8_t)rtctime.year;     
    
    energy_log.present_max_demand.active   = EM_GetActiveMaxDemand();
    energy_log.present_max_demand.apparent = EM_GetApparentMaxDemand();

    energy_log.present_energy_total.import_active = EM_GetImportActiveEnergyTotal();
    energy_log.present_energy_total.import_capacitive_reactive = EM_GetImportCapacitiveReactiveEnergyTotal();
    energy_log.present_energy_total.import_inductive_reactive = EM_GetImportInductiveReactiveEnergyTotal();
    energy_log.present_energy_total.export_active = EM_GetExportActiveEnergyTotal();
    energy_log.present_energy_total.export_capacitive_reactive = EM_GetExportCapacitiveReactiveEnergyTotal();
    energy_log.present_energy_total.export_inductive_reactive = EM_GetExportInductiveReactiveEnergyTotal();
    energy_log.present_energy_total.apparent = EM_GetApparentEnergyTotal();
    
    num = ENERGY_GetConfig().number_tariff;
    for (i = 0; i < num; i++)
    {
        /*
        * Import
        */
        /* Active */
        while (EM_GetImportActiveEnergyTariff(i, &energy_log.present_energy_tariff[i].import_active) != EM_OK);

        /* Capacitive Reactive */
        while (EM_GetImportCapacitiveReactiveEnergyTariff(i, &energy_log.present_energy_tariff[i].import_capacitive_reactive) != EM_OK);

        /* Inductive Reactive */
        while (EM_GetImportInductiveReactiveEnergyTariff(i, &energy_log.present_energy_tariff[i].import_inductive_reactive) != EM_OK);

        /*
        * Export
        */
        /* Active */
        while (EM_GetExportActiveEnergyTariff(i, &energy_log.present_energy_tariff[i].export_active) != EM_OK);

        /* Capacitive Reactive */
        while (EM_GetExportCapacitiveReactiveEnergyTariff(i, &energy_log.present_energy_tariff[i].export_capacitive_reactive) != EM_OK);

        /* Inductive Reactive */
        while (EM_GetExportInductiveReactiveEnergyTariff(i, &energy_log.present_energy_tariff[i].export_inductive_reactive) != EM_OK);

        /* Apparent */
        while (EM_GetApparentEnergyTariff(i, &energy_log.present_energy_tariff[i].apparent) != EM_OK);
	}
	
    if (STORAGE_AddEnergyLog(&energy_log) == STORAGE_OK)
    {
        CMD_Printf((uint8_t *)"OK\n\r");
    }
    else
    {
        CMD_Printf((uint8_t *)"FAILED\n\r");
    }

#else
    CMD_SendString((uint8_t *)"\n\rNot implemented\n\r");
#endif

    return 0;
}

/***********************************************************************************************************************
* Function Name    : static uint8_t COMMAND_InvokeAddTamperLog(uint8_t *arg_str)
* Description      : Command Invoke Add Tamper Log
* Arguments        : uint8_t index: Command index
*                  : uint8_t *arg_str: Arguments string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
***********************************************************************************************************************/
static uint8_t COMMAND_InvokeAddTamperLog(uint8_t *arg_str)
{
    #if 0
    /* Disable this command until upgrading the meter energy and tamper log */
    rtc_counter_value_t rtctime;
    ONE_TAMPER_DATA_LOG tamper_log;

    CMD_SendString((uint8_t *)"\n\rStart to write tamper log to EEPROM...");
    
    R_RTC_Get_CalendarCounterValue(&rtctime);
    
    tamper_log.tamper_rtc_time.Sec   = rtctime.sec;     
    tamper_log.tamper_rtc_time.Min   = rtctime.min;     
    tamper_log.tamper_rtc_time.Hour  = rtctime.hour;      
    tamper_log.tamper_rtc_time.Day   = rtctime.day;     
    tamper_log.tamper_rtc_time.Week  = rtctime.week;      
    tamper_log.tamper_rtc_time.Month = rtctime.month;     
    tamper_log.tamper_rtc_time.Year  = (uint8_t)rtctime.year;     
    
    tamper_log.tamper_type.earth_connected = EM_GetStatus().earth_connected;

    if (STORAGE_AddTamperLog(&tamper_log) == STORAGE_OK)
    {
        CMD_SendString((uint8_t *)"OK\n\r");
    }
    else
    {
        CMD_SendString((uint8_t *)"FAILED\n\r");
    }

#else
    CMD_SendString((uint8_t *)"\n\rNot implemented\n\r");
#endif
    
    return 0;
}

/***********************************************************************************************************************
* Function Name    : static uint8_t COMMAND_InvokeFormatMemory(uint8_t *arg_str)
* Description      : Command Invoke Format Memory
* Arguments        : uint8_t index: Command index
*                  : uint8_t *arg_str: Arguments string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
***********************************************************************************************************************/
static uint8_t COMMAND_InvokeFormatMemory(uint8_t *arg_str)
{
    uint8_t buffer[20];
    uint8_t mem_type;

    uint8_t data_buffer[20];
    uint8_t reset_buffer[0x100];
    
    CMD_SendString((uint8_t *)"\n\rParameter(s): ");
    CMD_SendString((uint8_t *)arg_str);
    CMD_SendString((uint8_t *)"\n\r");
    
    /* Get memory type parameter */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" /");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        mem_type = buffer[0] - '0';
    }
    
    if (mem_type)
    {
        CMD_SendString((uint8_t *)"\n\rFormatting Configuration Page...");
        
        R_WDT_Restart();

        DATAFLASH_Write(0x00, reset_buffer, sizeof(reset_buffer));
    }
    else
    {
        CMD_SendString((uint8_t *)"\n\rFormatting Energy Counter");
        COMMAND_InvokeClearEmEnergyCounter(NULL);

        CMD_SendString((uint8_t *)"\n\rFormatting MeterData...");
        
        R_WDT_Restart();

        memset(data_buffer, 0, STORAGE_EEPROM_GLOBAL_HEADER_CODE_SIZE);

        /* Clear header code to trigger format process */
        EPR_Write(STORAGE_EEPROM_GLOBAL_HEADER_CODE_ADDR, data_buffer, STORAGE_EEPROM_GLOBAL_HEADER_CODE_SIZE);
    
    }

    CMD_SendString((uint8_t *)"Reset Meter...\n\r");
    WRP_EXT_SoftReset();

    return 0;
}


/***********************************************************************************************************************
* Function Name    : static uint8_t COMMAND_InvokeReadPlatformInfo(uint8_t *arg_str)
* Description      : Command Invoke Read Platform Info
* Arguments        : uint8_t index: Command index
*                  : uint8_t *arg_str: Arguments string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
***********************************************************************************************************************/
static uint8_t COMMAND_InvokeReadPlatformInfo(uint8_t *arg_str)
{
    const uint8_t nameplate_str[][25] = 
    {
        "0. Logical device name: ",
        "1. Meter serial number: ",
        "2. Manufacturer name  : ",
        "3. Device ID          : ",
        "4. Meter Category     : ",
        "5. Ib-Imax            : ",
        "6. Meter Year of mnf  : ",
        "7. Meter type         : ",
        "8. Firmware version   : ",
        "9. Flag ID            : ",
    };

    uint8_t buffer[120];
    uint16_t len;
    uint8_t i,j;

    CMD_Printf("[NAMEPLATE]\n\r");
    for (i = NAMEPLATE_ID_LDN; i <= NAMEPLATE_ID_FLAGID; i++)
    {
        CMD_Printf((uint8_t *)"%s", nameplate_str[i]);
        R_NAMEPLATE_GetByID(i, buffer, &len);
        buffer[len] = '\0';
        CMD_Printf((uint8_t *)"## %s ##",buffer);

        CMD_Printf((uint8_t *)"(HEX: ");
        for(j = 0;j < len; j++)
        {
            CMD_Printf((uint8_t *)"%02X",buffer[j]);
        }
        CMD_Printf((uint8_t *)")\n\r",buffer[j]);
    }

    CMD_Printf("[END]\n\r");

    return 0;
}

static void NEAR_FUNC signal_end_callback(void)
{
    /* Debug the signal */
    //#ifndef METER_ENABLE_MEASURE_CPU_LOAD
    //if (g_sample_count < EM_MAX_SAMPLE_BUFFER)
    //{
    //   g_sample0[g_sample_count] = g_wrp_adc_samples.v;
    //    if (g_sample1_direction == 0)
    //    {
    //        g_sample1[g_sample_count] = g_wrp_adc_samples.i1;
    //    }
    //    else if (g_sample1_direction == 1)
    //    {
    //        g_sample1[g_sample_count] = g_wrp_adc_samples.i2;
    //    }
    //    g_sample_count++;
    //}
    //#endif /* METER_ENABLE_MEASURE_CPU_LOAD */
}
/******************************************************************************
* Function Name    : static uint8_t COMMAND_InvokeDumpSample(uint8_t *arg_str)
* Description      : Command Invoke Dump ADC samples
* Arguments        : uint8_t index: Command index
*                  : uint8_t *arg_str: Arguments string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
******************************************************************************/
//static uint8_t COMMAND_InvokeDumpSample(uint8_t *arg_str)
//{
//    uint16_t i;
//    uint8_t buffer[20];

//    #ifndef METER_ENABLE_MEASURE_CPU_LOAD
//    /* Send request to EM Core to dump the waveform */
//    g_wrp_sample_count = 0;

//    R_WDT_Restart();
//    while (g_wrp_sample_count < EM_ADC_MAX_DEBUG_SAMPLE);
    
//    CMD_Printf((uint8_t *)"\n\r");
//    CMD_Printf((uint8_t *)"%-9s, %-9s, %-9s, %-9s, %-9s, %-9s, %-9s, %-9s, %-9s, %-9s\n\r", 
//                                "V-R","V-Y","V-B","V90-R","V90-Y","V90-B","I-R","I-Y","I-B","I-N");
    
//    R_WDT_Restart();
//    for (i = 0; i < g_wrp_sample_count; i++)
//    {
//        if (g_wrp_sample_int16[0][i] == 0)
//        {
//            g_wrp_sample_int16[0][i] = 1;
//        }
//        if (g_wrp_sample_int16[1][i] == 0)
//        {
//            g_wrp_sample_int16[1][i] = 1;
//        }
//        if (g_wrp_sample_int16[2][i] == 0)
//        {
//            g_wrp_sample_int16[2][i] = 1;
//        }
        
//        if (g_wrp_sample_int16[3][i] == 0)
//        {
//            g_wrp_sample_int16[3][i] = 1;
//        }
//        if (g_wrp_sample_int16[4][i] == 0)
//        {
//            g_wrp_sample_int16[4][i] = 1;
//        }
//        if (g_wrp_sample_int16[5][i] == 0)
//        {
//            g_wrp_sample_int16[5][i] = 1;
//        }
        
//        if (g_wrp_sample_int32[0][i] == 0)
//        {
//            g_wrp_sample_int32[0][i] = 1;
//        }
//        if (g_wrp_sample_int32[1][i] == 0)
//        {
//            g_wrp_sample_int32[1][i] = 1;
//        }
//        if (g_wrp_sample_int32[2][i] == 0)
//        {
//            g_wrp_sample_int32[2][i] = 1;
//        }
//        if (g_wrp_sample_int32[3][i] == 0)
//        {
//            g_wrp_sample_int32[3][i] = 1;
//        }
        
//        CMD_Printf((uint8_t *)"%-9.d, %-9.d, %-9.d, %-9.d, %-9.d, %-9.d, %-9.ld, %-9.ld, %-9.ld, %-9.ld\n\r", 
//                                g_wrp_sample_int16[0][i], g_wrp_sample_int16[1][i], g_wrp_sample_int16[2][i], 
//                                g_wrp_sample_int16[3][i], g_wrp_sample_int16[4][i], g_wrp_sample_int16[5][i], 
//                                g_wrp_sample_int32[0][i], g_wrp_sample_int32[1][i], g_wrp_sample_int32[2][i], g_wrp_sample_int32[3][i]);
//    }                 
//    #else
	
//    CMD_Printf((uint8_t *)"\n\r Not enable. Turn on by disable the macro METER_ENABLE_MEASURE_CPU_LOAD");
	
//    #endif /* METER_ENABLE_MEASURE_CPU_LOAD */
    
//    return 0;

//}

const uint8_t s_cnst_calib_params_back[] = { 0x1b , '[', '1','5', 'A', 0 };
const uint8_t s_cnst_calib_params_newline[] = "\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r";
//static void command_print_calibration(r_calib_output_t * p_output)
//{
//    dsad_channel_t channel;
//    uint16_t dsadphcr, dsadgcr;
//    switch (p_output->line)
//    {
//        case LINE_PHASE_R:
//            channel = EM_ADC_CURRENT_DRIVER_CHANNEL_PHASE_R;
//            break;
//        case LINE_PHASE_Y:
//            channel = EM_ADC_CURRENT_DRIVER_CHANNEL_PHASE_Y;
//            break;
//        case LINE_PHASE_B:
//            channel = EM_ADC_CURRENT_DRIVER_CHANNEL_PHASE_B;
//            break;
//        case LINE_NEUTRAL:
//            channel = EM_ADC_CURRENT_DRIVER_CHANNEL_NEUTRAL;
//            break;
//        default:
//            /* Unsupported line selection */
//            return;
//    }

//    dsadphcr = R_DSADC_GetChannelPhase(channel);
//    dsadgcr = R_DSADC_GetChannelGain(channel);

//    /* Refresh buffer line: note the number of param line then 
//    * Hardcode the s_cnst_calib_params_back and s_cnst_calib_params_newline
//    */
//    if (FALSE) {}
//    else if (p_output->step == R_CALIB_STEP_NOT_INITIATED)
//    {
//        /* First print, enter line break + x amount of new line (according to number of param line) */
//        CMD_Printf((uint8_t *)line_break);
//        CMD_Printf((uint8_t *)s_cnst_calib_params_newline);
//    }
//    else if (p_output->step == R_CALIB_STEP_FINISHED)
//    {
//        CMD_Printf((uint8_t *)line_break);
//    }
//    else
//    {
//        /* On update, up cursor by x amount of line (according to number of param line) */
//        CMD_Printf((uint8_t *)s_cnst_calib_params_back);
//        CMD_Printf((uint8_t *)"Calibrating step   = %d\n\r", p_output->step);
//        CMD_Printf((uint8_t *)"Voltage offset     = %16.6f\n\r", p_output->voffset);
//        CMD_Printf((uint8_t *)"Sampling frequency = %16.6f\n\r", p_output->fs);
//        CMD_Printf((uint8_t *)"Current gain       = %16.6f\n\r", p_output->gain);
//        CMD_Printf((uint8_t *)"Current gain1      = %16.6f\n\r", p_output->gain1);
//        CMD_Printf((uint8_t *)"V coeff            = %16.6f\n\r", p_output->vcoeff);
//        CMD_Printf((uint8_t *)"I coeff            = %16.6f\n\r", p_output->icoeff);
//        CMD_Printf((uint8_t *)"Power Coeff        = %16.6f\n\r", p_output->pcoeff);
//        CMD_Printf((uint8_t *)"Phase shift        = %16.6f\n\r", p_output->angle_error);
//        CMD_Printf((uint8_t *)"Phase shift1       = %16.6f\n\r", p_output->angle_error1);
//        CMD_Printf((uint8_t *)"V90 Step Offset    = %16.6f\n\r", p_output->angle90_offset);
//        CMD_Printf((uint8_t *)"Additional parameter:\n\r");
//        CMD_Printf((uint8_t *)"  + DSADPHCRx      = %04d\n\r", dsadphcr);
//        CMD_Printf((uint8_t *)"  + DSADGCRx       = %04d\n\r", dsadgcr);
//        CMD_Printf((uint8_t *)"  + TDR01          = %04d\n\r", TDR01);
//    }
    
//}

uint8_t parse_unsigned_integer_from_argstr(uint16_t *p_value_out, uint8_t **pp_arg_str)
{
    uint8_t         buffer[20];             /* Data buffer to store input arguments */

    *pp_arg_str = COMMAND_GetScanOneParam(buffer, 20, *pp_arg_str, (uint8_t *)" ", (uint8_t *)" "); 
    if (*pp_arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        /* get number */
        *p_value_out = (uint16_t)atol((char *)buffer);
    }
    else
    {
        CMD_SendString((uint8_t *)"Parameter error\n\r");
        return 1;
    }

    return 0;
}

/******************************************************************************
* Function Name   : COMMAND_InvokeCalibration
* Interface       : static void COMMAND_InvokeCalibration(uint8_t *arg_str)
* Description     : Command Invoke Calibration
* Arguments       : uint8_t * arg_str: Arguments string
* Function Calls  : None
* Return Value    : None
******************************************************************************/
static uint8_t COMMAND_InvokeCalibration(uint8_t *arg_str)
{
    /* Command buffer */
    uint8_t         buffer[20];             /* Data buffer to store input arguments */
    
    uint16_t calib_c;
    uint16_t calib_cp; 
    uint16_t calib_imax;
    uint16_t calib_v;
    uint16_t calib_i; 
    uint8_t calib_neutral;

    uint8_t calib_result = 0;
    uint8_t parse_result;

    /* Get c parameter */
    parse_result = parse_unsigned_integer_from_argstr(&calib_c, &arg_str);
    if (parse_result == 1)
    {
        return 1;
    }
        
    /* Get cp parameter */
    parse_result = parse_unsigned_integer_from_argstr(&calib_cp, &arg_str);
    if (parse_result == 1)
    {
        return 1;
    }
        
    /* Get imax parameter */
    parse_result = parse_unsigned_integer_from_argstr(&calib_imax, &arg_str);
    if (parse_result == 1)
    {
        return 1;
    }

    /* Get v parameter */
    parse_result = parse_unsigned_integer_from_argstr(&calib_v, &arg_str);
    if (parse_result == 1)
    {
        return 1;
    }

    /* Get i parameter */
    parse_result = parse_unsigned_integer_from_argstr(&calib_i, &arg_str);
    if (parse_result == 1)
    {
        return 1;
    }
        
    /* Get line parameter */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" "); 
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        /* get number */
        calib_neutral = atof((char *)buffer);   
    }
    else
    {
        CMD_Printf((uint8_t *)"Parameter error\n\r");
        return 1;
    }

    CMD_Printf((uint8_t *)"\n\rStart autocalibration: \n\r");
    calib_result = Calibration_Service(
        calib_c,
        calib_cp,
        calib_imax,
        calib_v,
        calib_i,
        calib_neutral
    );

    CMD_Printf((uint8_t *)"Autocalibration end\n\r");
    CMD_Printf((uint8_t *)"Calibration status: %d \n\r", calib_result);

    return 0;
}



/***********************************************************************************************************************
* Function Name : Calibration_Service
* Interface     : void Calibration_Service
* Description   : 
* Arguments     : None:
* Function Calls: 
* Return Value  : None
***********************************************************************************************************************/
static uint8_t Calibration_Service(uint16_t calib_c, uint16_t calib_cp, float32_t calib_imax, float32_t calib_v, float32_t calib_i, uint8_t calib_neutral)
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

/******************************************************************************
* Function Name    : static uint8_t scanf_float_params(uint8_t *p_msg, float32_t __far *p_variable)
* Description      : Request user to input float params
* Arguments        : uint8_t *p_msg: Prompt string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
******************************************************************************/
static uint8_t scanf_float_params(uint8_t *p_msg, float32_t __far *p_variable)
{
    uint8_t is_input_valid = 0;
    uint8_t *p_cmd;
    uint8_t b_input = 0;

    CMD_SendString((uint8_t *)p_msg);
    /* Wait for user input value */
    do
    {
        while (CMD_IsCmdReceived() == 0)
        {
            R_WDT_Restart();
        }
        p_cmd = CMD_Get();
        b_input = p_cmd[0];
        
        if (p_cmd[0] == 0)
        {
            is_input_valid = 1;
        }
        else
        {
            is_input_valid = COMMAND_IsFloatNumber(p_cmd);
            if (is_input_valid != 1)
            {
                CMD_Printf((uint8_t *)"\n\r   Invalid number, please retry");
            }
            else
            {
                (*p_variable) = (float32_t)atof((char *)p_cmd);
            }
        }
        CMD_AckCmdReceivedNoHeader();
        
    } while ((is_input_valid != 1));
    CMD_SendString((uint8_t *)"\n\r");
    
    return 0;
}

/******************************************************************************
* Function Name    : static uint8_t input_interger(uint8_t *p_msg, float32_t *p_variable)
* Description      : Request user to input float params
* Arguments        : uint8_t *p_msg: Prompt string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
******************************************************************************/
static uint8_t input_interger(uint8_t *p_msg, uint16_t *p_variable)
{
    uint8_t is_input_valid = 0;
    uint8_t *p_cmd;
    uint8_t b_input = 0;

    CMD_SendString((uint8_t *)p_msg);
    /* Wait for user input value */

    CMD_AckCmdReceivedNoHeader();
    do
    {
        while (CMD_IsCmdReceived() == 0)
        {
            R_WDT_Restart();
        }
        p_cmd = CMD_Get();
        b_input = p_cmd[0];
        
        if (p_cmd[0] == 0)
        {
            is_input_valid = 1;
        }
        else
        {
            (*p_variable) = (uint16_t)atoi((char *)p_cmd);
            is_input_valid = 1;
        }
        CMD_AckCmdReceivedNoHeader();
        
    } while ((is_input_valid != 1));
    CMD_SendString((uint8_t *)"\n\r");
    
    return 0;
}

/******************************************************************************
* Function Name    : static uint8_t input_interger(uint8_t *p_msg, float32_t *p_variable)
* Description      : Request user to input float params
* Arguments        : uint8_t *p_msg: Prompt string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
******************************************************************************/
static uint8_t input_ascii_string(uint8_t *p_msg, uint8_t *p_array, uint16_t *p_len)
{
    uint8_t is_input_valid = 0;
    uint8_t *p_cmd;
    uint8_t b_input = 0;
    uint8_t cmdstr[64];
    uint16_t i,j;

    CMD_SendString((uint8_t *)p_msg);
    /* Wait for user input value */

    CMD_AckCmdReceivedNoHeader();

    do
    {
        while (CMD_IsCmdReceived() == 0)
        {
            R_WDT_Restart();
        }
        p_cmd = CMD_Get();
        b_input = p_cmd[0];
        
        if (p_cmd[0] == 0)
        {
            is_input_valid = 1;
        }
        else
        {
            /* Get command */
            memset(cmdstr, 0, 64);

            /* Skip all ahead space */
            while (p_cmd[0] == ' ' && p_cmd[0] != 0)
            {
                p_cmd++;
            }
            
            /* Get command name */
            i = 0;
            *p_len = 0;
            while (p_cmd[0] != 0)
            {
                cmdstr[i++] = *p_cmd;
                p_cmd++;
                (*p_len)++;
            }

            memcpy((uint8_t *)p_array, (uint8_t *)cmdstr, *p_len);
			is_input_valid = 1;
        }
        CMD_AckCmdReceivedNoHeader();
        
    } while ((is_input_valid != 1));
    CMD_SendString((uint8_t *)"\n\r");
    
    return 0;
}

/******************************************************************************
* Function Name    : static uint8_t COMMAND_InvokeSetCalibInfo(uint8_t *arg_str)
* Description      : Command Invoke Set calibration info
* Arguments        : uint8_t *arg_str: Arguments string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
******************************************************************************/
static uint8_t COMMAND_InvokeSetCalibInfo(uint8_t *arg_str)
{
    EM_CALIBRATION  calib;           /* Calibrated data storage for EM core */
    uint8_t buffer[20];             /* Data buffer to store input arguments */

    uint8_t is_edit;    
    uint8_t rlt, em_rlt;

    CMD_SendString((uint8_t *)"\n\rParameter(s): ");
    CMD_SendString((uint8_t *)arg_str);
    CMD_SendString((uint8_t *)"\n\r");
    
    /* Get Addr parameter */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" ");
        
    if (arg_str != NULL)
    {
        if ((buffer[0] == '0' || buffer[0] == '1'))
        {
            is_edit = buffer[0] - '0';
        }
    }
    else
    {
        is_edit = 0;
    }

    /* Ack the lask received CMD */
    CMD_AckCmdReceivedNoHeader();
    
    /* Set current calibration info */
    calib = EM_GetCalibInfo();

//    R_DSADC_GetGainAndPhase(&regs);
    
//    driver_adc_gain0 = regs.gain0;
//    driver_adc_gain1 = regs.gain1;
    
    /* Display current information */
    CMD_SendString((uint8_t *)"\n\r Current calibration info:");
    CMD_SendString((uint8_t *)"\n\r Common:"); 
    CMD_Printf((uint8_t *)"\n\r - Sampling frequency: %.04f", calib.sampling_frequency);
    CMD_SendString((uint8_t *)"\n\r"); 
    CMD_SendString((uint8_t *)"\n\r Coefficient, Phase_R: ");
    CMD_Printf((uint8_t *)"\n\r - VRMS: %.04f", calib.coeff.phase_r.vrms);
    CMD_Printf((uint8_t *)"\n\r - IRMS: %.04f", calib.coeff.phase_r.irms);
    CMD_Printf((uint8_t *)"\n\r - Active: %.04f", calib.coeff.phase_r.active_power);
    CMD_Printf((uint8_t *)"\n\r - Reactive: %.04f", calib.coeff.phase_r.reactive_power);
    CMD_Printf((uint8_t *)"\n\r - Apparent: %.04f", calib.coeff.phase_r.apparent_power);
    
    CMD_SendString((uint8_t *)"\n\r"); 
    CMD_SendString((uint8_t *)"\n\r Coefficient, Phase_Y: ");
    CMD_Printf((uint8_t *)"\n\r - VRMS: %.04f", calib.coeff.phase_y.vrms);
    CMD_Printf((uint8_t *)"\n\r - IRMS: %.04f", calib.coeff.phase_y.irms);
    CMD_Printf((uint8_t *)"\n\r - Active: %.04f", calib.coeff.phase_y.active_power);
    CMD_Printf((uint8_t *)"\n\r - Reactive: %.04f", calib.coeff.phase_y.reactive_power);
    CMD_Printf((uint8_t *)"\n\r - Apparent: %.04f", calib.coeff.phase_y.apparent_power);

    CMD_SendString((uint8_t *)"\n\r"); 
    CMD_SendString((uint8_t *)"\n\r Coefficient, Phase_B: ");
    CMD_Printf((uint8_t *)"\n\r - VRMS: %.04f", calib.coeff.phase_b.vrms);
    CMD_Printf((uint8_t *)"\n\r - IRMS: %.04f", calib.coeff.phase_b.irms);
    CMD_Printf((uint8_t *)"\n\r - Active: %.04f", calib.coeff.phase_b.active_power);
    CMD_Printf((uint8_t *)"\n\r - Reactive: %.04f", calib.coeff.phase_b.reactive_power);
    CMD_Printf((uint8_t *)"\n\r - Apparent: %.04f", calib.coeff.phase_b.apparent_power);
    
    CMD_SendString((uint8_t *)"\n\r"); 
    CMD_SendString((uint8_t *)"\n\r Gain 0: ");
    CMD_Printf((uint8_t *)"\n\r Phase_R: %.06f", calib.sw_gain.phase_r.i_gain_values[0] );
    CMD_Printf((uint8_t *)"\n\r Phase_Y: %.06f", calib.sw_gain.phase_y.i_gain_values[0] );
    CMD_Printf((uint8_t *)"\n\r Phase_B: %.06f", calib.sw_gain.phase_b.i_gain_values[0] );
        
    CMD_SendString((uint8_t *)"\n\r"); 
    CMD_SendString((uint8_t *)"\n\r Gain 1: ");
    CMD_Printf((uint8_t *)"\n\r Phase_R: %.06f", calib.sw_gain.phase_r.i_gain_values[1] );
    CMD_Printf((uint8_t *)"\n\r Phase_Y: %.06f", calib.sw_gain.phase_y.i_gain_values[1] );
    CMD_Printf((uint8_t *)"\n\r Phase_B: %.06f", calib.sw_gain.phase_b.i_gain_values[1] );
    
    CMD_SendString((uint8_t *)"\n\r"); 
    CMD_SendString((uint8_t *)"\n\r ADC Gain: ");
    CMD_Printf((uint8_t *)"\n\r Neutral: %s", COMMAND_GetDsadGainName( R_DSADC_GetGainEnumValue( R_DSADC_GetChannelGain(EM_ADC_CURRENT_DRIVER_CHANNEL_NEUTRAL) )) );
        
    CMD_SendString((uint8_t *)"\n\r"); 
    CMD_SendString((uint8_t *)"\n\r Phase 0: ");
    CMD_Printf((uint8_t *)"\n\r Phase_R: %.06f degree", calib.sw_phase_correction.phase_r.i_phase_degrees[0]);
    CMD_Printf((uint8_t *)"\n\r Phase_Y: %.06f degree", calib.sw_phase_correction.phase_y.i_phase_degrees[0]);
    CMD_Printf((uint8_t *)"\n\r Phase_B: %.06f degree", calib.sw_phase_correction.phase_b.i_phase_degrees[0]);
        
    CMD_SendString((uint8_t *)"\n\r"); 
    CMD_SendString((uint8_t *)"\n\r Phase 1: ");
    CMD_Printf((uint8_t *)"\n\r Phase_R: %.06f degree", calib.sw_phase_correction.phase_r.i_phase_degrees[1]);
    CMD_Printf((uint8_t *)"\n\r Phase_Y: %.06f degree", calib.sw_phase_correction.phase_y.i_phase_degrees[1]);
    CMD_Printf((uint8_t *)"\n\r Phase_B: %.06f degree", calib.sw_phase_correction.phase_b.i_phase_degrees[1]);
    
    CMD_SendString((uint8_t *)"\n\r"); 
    
    if (is_edit)
    {
        CMD_SendString((uint8_t *)"\n\r"); 
        CMD_SendString((uint8_t *)"\n\r --- Follow instruction below to adjust calib info --- ");
        CMD_SendString((uint8_t *)"\n\r --- Leave empty, press enter to ignore changes --- ");
            
        CMD_SendString((uint8_t *)"\n\r SET SAMPLING FREQUENCY: "); 
        scanf_float_params((uint8_t *)"\n\r - Sampling frequency (Hz) > ",&calib.sampling_frequency);
        
        CMD_SendString((uint8_t *)"\n\r SET COEFFICIENTS FOR PHASE_R: ");
        scanf_float_params((uint8_t *)"\n\r - VRMS     >", &calib.coeff.phase_r.vrms);
        scanf_float_params((uint8_t *)"\n\r - IRMS     >", &calib.coeff.phase_r.irms);
        scanf_float_params((uint8_t *)"\n\r - Active   >", &calib.coeff.phase_r.active_power);
        scanf_float_params((uint8_t *)"\n\r - Reactive >", &calib.coeff.phase_r.reactive_power);
        scanf_float_params((uint8_t *)"\n\r - Apparent >", &calib.coeff.phase_r.apparent_power);

        CMD_SendString((uint8_t *)"\n\r SET COEFFICIENTS FOR PHASE_Y: ");
        scanf_float_params((uint8_t *)"\n\r - VRMS     >", &calib.coeff.phase_y.vrms);
        scanf_float_params((uint8_t *)"\n\r - IRMS     >", &calib.coeff.phase_y.irms);
        scanf_float_params((uint8_t *)"\n\r - Active   >", &calib.coeff.phase_y.active_power);
        scanf_float_params((uint8_t *)"\n\r - Reactive >", &calib.coeff.phase_y.reactive_power);
        scanf_float_params((uint8_t *)"\n\r - Apparent >", &calib.coeff.phase_y.apparent_power);

        CMD_SendString((uint8_t *)"\n\r SET COEFFICIENTS FOR PHASE_B: ");
        scanf_float_params((uint8_t *)"\n\r - VRMS     >", &calib.coeff.phase_b.vrms);
        scanf_float_params((uint8_t *)"\n\r - IRMS     >", &calib.coeff.phase_b.irms);
        scanf_float_params((uint8_t *)"\n\r - Active   >", &calib.coeff.phase_b.active_power);
        scanf_float_params((uint8_t *)"\n\r - Reactive >", &calib.coeff.phase_b.reactive_power);
        scanf_float_params((uint8_t *)"\n\r - Apparent >", &calib.coeff.phase_b.apparent_power);

        CMD_SendString((uint8_t *)"\n\r SET GAIN VALUE: ");
        scanf_float_params((uint8_t *)"\n\r - Gain[0], Phase_R   >", &calib.sw_gain.phase_r.i_gain_values[0] );
        scanf_float_params((uint8_t *)"\n\r - Gain[0], Phase_Y   >", &calib.sw_gain.phase_y.i_gain_values[0] );
        scanf_float_params((uint8_t *)"\n\r - Gain[0], Phase_B   >", &calib.sw_gain.phase_b.i_gain_values[0] );
        CMD_SendString((uint8_t *)"\n\r"); 
        scanf_float_params((uint8_t *)"\n\r - Gain[1], Phase_R   >", &calib.sw_gain.phase_r.i_gain_values[1] );
        scanf_float_params((uint8_t *)"\n\r - Gain[1], Phase_Y   >", &calib.sw_gain.phase_y.i_gain_values[1] );
        scanf_float_params((uint8_t *)"\n\r - Gain[1], Phase_B   >", &calib.sw_gain.phase_b.i_gain_values[1] );

        CMD_SendString((uint8_t *)"\n\r PHASE DEGREE: ");
        scanf_float_params((uint8_t *)"\n\r - [0] Phase_R: (degree) >", &calib.sw_phase_correction.phase_r.i_phase_degrees[0]);
        scanf_float_params((uint8_t *)"\n\r - [0] Phase_Y: (degree) >", &calib.sw_phase_correction.phase_y.i_phase_degrees[0]);
        scanf_float_params((uint8_t *)"\n\r - [0] Phase_B: (degree) >", &calib.sw_phase_correction.phase_b.i_phase_degrees[0]);
        CMD_SendString((uint8_t *)"\n\r"); 
        scanf_float_params((uint8_t *)"\n\r - [1] Phase_R: (degree) >", &calib.sw_phase_correction.phase_r.i_phase_degrees[1]);
        scanf_float_params((uint8_t *)"\n\r - [1] Phase_Y: (degree) >", &calib.sw_phase_correction.phase_y.i_phase_degrees[1]);
        scanf_float_params((uint8_t *)"\n\r - [1] Phase_B: (degree) >", &calib.sw_phase_correction.phase_b.i_phase_degrees[1]);

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
    
   return 0;
}
/******************************************************************************
* Function Name    : static uint8_t COMMAND_InvokeSetConfig(uint8_t *arg_str)
* Description      : Command Invoke Set configuration
* Arguments        : uint8_t *arg_str: Arguments string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
******************************************************************************/
static uint8_t COMMAND_InvokeSetConfig(uint8_t *arg_str)
{
    #if 0
    static const uint8_t param_time_slot[] = "\n\r%21d:   %-4d   %-6d   %-13d";
    
    EM_CONFIG       em_config;              /* EM Configuration */
    ENERGY_CONFIG   energy_config;          /* Energy configuration */
    uint8_t buffer[20];             /* Data buffer to store input arguments */
    
    uint16_t rlt;
    uint8_t         *p_cmd;
    uint8_t         b_input = 0;
    uint8_t         input_valid;
    MD_STATUS       status;
    uint8_t         is_edit;
    uint8_t         i;
    
    CMD_SendString((uint8_t *)"\n\rParameter(s): ");
    CMD_SendString((uint8_t *)arg_str);
    CMD_SendString((uint8_t *)"\n\r");
    
    /* Get Addr parameter */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" ");
    
    if (arg_str != NULL)
    {
        if ((buffer[0] == '0' || buffer[0] == '1'))
        {
            is_edit = buffer[0] - '0';
        }
    }
    else
    {
        is_edit = 0;
    }
    
    /* Ack the lask received CMD */
    CMD_AckCmdReceivedNoHeader();
    
    /* Set current configuration */
    energy_config = ENERGY_GetConfig();
    em_config = EM_GetConfig();
    
    /* Display current information */
    CMD_SendString((uint8_t *)"\n\r Current configuration info:");
    CMD_Printf((uint8_t *)"\n\r - Voltage low (V): %d", em_config.voltage_low);
    CMD_Printf((uint8_t *)"\n\r - Voltage high (V): %d", em_config.voltage_high);
    CMD_Printf((uint8_t *)"\n\r - Current high (A): %d", em_config.current_high);
    CMD_Printf((uint8_t *)"\n\r - Frequency low (Hz): %d", em_config.freq_low);
    CMD_Printf((uint8_t *)"\n\r - Frequency high (Hz): %d", em_config.freq_high);
    CMD_Printf((uint8_t *)"\n\r - Earth diff threshold (%%): %.04f", em_config.earth_diff_threshold);

    CMD_Printf((uint8_t *)"\n\r - Max demand period (minute): %d", energy_config.max_demand_period);
    CMD_Printf((uint8_t *)"\n\r - Number of tariff: %d", energy_config.number_tariff);
    CMD_Printf((uint8_t *)"\n\r - Number of time slot: %d", energy_config.number_timeslot);
    CMD_SendString((uint8_t *)"\n\r Time slot list array:   Hour   Minute   Tariff_number");
    for (i=0; i < METER_ENERGY_NUMBER_OF_TIMESLOT_MAX; i++)
    {
        CMD_Printf((uint8_t *)param_time_slot, i, 
            energy_config.timeslot_list[i].timestart.hour,
            energy_config.timeslot_list[i].timestart.minute,
            energy_config.timeslot_list[i].tariffno
        );
    }
    
    CMD_SendString((uint8_t *)"\n\r"); 
    
    if (is_edit)
    {
        /* Stop EM operation */
        CMD_Printf((uint8_t *)"\n\rStop Energy Management...");
        if (ENERGY_Stop() != ENERGY_RET_OK)
        {
            CMD_Printf((uint8_t *)"FAILED\n\r");
            return 1;
        }
        else
        {
            CMD_Printf((uint8_t *)"OK\n\r");
        }

        CMD_Printf((uint8_t *)"\n\rStop EM Core...");
        if (EM_Stop() != EM_OK)
        {
            CMD_Printf((uint8_t *)"FAILED\n\r");
            return 1;
        }
        else
        {
            CMD_Printf((uint8_t *)"OK\n\r");
        }
        
        CMD_SendString((uint8_t *)"\n\r"); 
        CMD_SendString((uint8_t *)"\n\r --- Follow instruction below to modify configuration --- ");
        CMD_SendString((uint8_t *)"\n\r --- Leave empty, press enter to ignore changes --- ");
        
        CMD_SendString((uint8_t *)"\n\r SET BASIC CONFIGURATION: ");
        /* Wait for user input value : voltage_low */
        do
        {
            CMD_SendString((uint8_t *)"\n\r   Voltage low (V) > ");
            while (CMD_IsCmdReceived() == 0)
            {
                R_WDT_Restart();
            }
            p_cmd = CMD_Get();
            b_input = p_cmd[0];
            
            if (p_cmd[0] == 0)
            {
                input_valid = 1;
            }
            else
            {
                rlt = COMMAND_DecStringToUnsigned16(p_cmd, &input_valid);
                
                if (input_valid != 1)
                {
                    CMD_Printf((uint8_t *)"\n\r   Invalid number, please retry");
                }
                else
                {
                    em_config.voltage_low = (uint16_t)rlt;
                }
            }
            CMD_AckCmdReceivedNoHeader();
            
        } while ((input_valid != 1));
        
        /* Wait for user input value : voltage_high */
        do
        {
            CMD_SendString((uint8_t *)"\n\r   Voltage high (V) > ");
            while (CMD_IsCmdReceived() == 0)
            {
                R_WDT_Restart();
            }
            p_cmd = CMD_Get();
            b_input = p_cmd[0];
            
            if (p_cmd[0] == 0)
            {
                input_valid = 1;
            }
            else
            {
                rlt = COMMAND_DecStringToUnsigned16(p_cmd, &input_valid);
                
                if (input_valid != 1)
                {
                    CMD_Printf((uint8_t *)"\n\r   Invalid number, please retry");
                }
                else
                {
                    em_config.voltage_high = rlt;
                }
            }
            CMD_AckCmdReceivedNoHeader();
            
        } while ((input_valid != 1));
        
        /* Wait for user input value : current_high */
        do
        {
            CMD_SendString((uint8_t *)"\n\r   Current high (A) > ");
            while (CMD_IsCmdReceived() == 0)
            {
                R_WDT_Restart();
            }
            p_cmd = CMD_Get();
            b_input = p_cmd[0];
            
            if (p_cmd[0] == 0)
            {
                input_valid = 1;
            }
            else
            {
                rlt = COMMAND_DecStringToUnsigned16(p_cmd, &input_valid);
                
                if (input_valid != 1)
                {
                    CMD_Printf((uint8_t *)"\n\r   Invalid number, please retry");
                }
                else
                {
                    em_config.current_high = (uint8_t)rlt;
                }
            }
            CMD_AckCmdReceivedNoHeader();
            
        } while ((input_valid != 1));
        
        /* Wait for user input value : freq_low */
        do
        {
            CMD_SendString((uint8_t *)"\n\r   Frequency Low (Hz) > ");
            while (CMD_IsCmdReceived() == 0)
            {
                R_WDT_Restart();
            }
            p_cmd = CMD_Get();
            b_input = p_cmd[0];
            
            if (p_cmd[0] == 0)
            {
                input_valid = 1;
            }
            else
            {
                rlt = COMMAND_DecStringToUnsigned16(p_cmd, &input_valid);
                
                if (input_valid != 1)
                {
                    CMD_Printf((uint8_t *)"\n\r   Invalid number, please retry");
                }
                else
                {
                    em_config.freq_low = (uint8_t)rlt;
                }
            }
            CMD_AckCmdReceivedNoHeader();
            
        } while ((input_valid != 1));
        
        /* Wait for user input value : freq_high */
        do
        {
            CMD_SendString((uint8_t *)"\n\r   Frequency High (Hz) > ");
            while (CMD_IsCmdReceived() == 0)
            {
                R_WDT_Restart();
            }
            p_cmd = CMD_Get();
            b_input = p_cmd[0];
            
            if (p_cmd[0] == 0)
            {
                input_valid = 1;
            }
            else
            {
                rlt = COMMAND_DecStringToUnsigned16(p_cmd, &input_valid);
                
                if (input_valid != 1)
                {
                    CMD_Printf((uint8_t *)"\n\r   Invalid number, please retry");
                }
                else
                {
                    em_config.freq_high = (uint8_t)rlt;
                }
            }
            CMD_AckCmdReceivedNoHeader();
            
        } while ((input_valid != 1));
        
        /* Wait for user input value : earth_diff_threshold */
        do
        {
            CMD_SendString((uint8_t *)"\n\r   Earth difference threshold (%) > ");
            while (CMD_IsCmdReceived() == 0)
            {
                R_WDT_Restart();
            }
            p_cmd = CMD_Get();
            b_input = p_cmd[0];
            
            if (p_cmd[0] == 0)
            {
                input_valid = 1;
            }
            else
            {
                input_valid = COMMAND_IsFloatNumber(p_cmd);
                if (input_valid != 1)
                {
                    CMD_Printf((uint8_t *)"\n\r   Invalid number, please retry");
                }
                else
                {
                    em_config.earth_diff_threshold = (float32_t)EM_atof(p_cmd);
                }
            }
            CMD_AckCmdReceivedNoHeader();
            
        } while ((input_valid != 1));

        /* Wait for user input value : max_demand_period */
        do
        {
            CMD_SendString((uint8_t *)"\n\r   Max Demand Period (minutes) > ");
            while (CMD_IsCmdReceived() == 0)
            {
                R_WDT_Restart();
            }
            p_cmd = CMD_Get();
            b_input = p_cmd[0];

            if (p_cmd[0] == 0)
            {
                input_valid = 1;
            }
            else
            {
                rlt = COMMAND_DecStringToUnsigned16(p_cmd, &input_valid);

                if (input_valid != 1)
                {
                    CMD_Printf((uint8_t *)"\n\r   Invalid number, please retry");
                }
                else
                {
                    energy_config.max_demand_period = (uint8_t)rlt;
                }
            }
            CMD_AckCmdReceivedNoHeader();

        } while ((input_valid != 1));
        
        /* Wait for user input value : number_tariff */
        do
        {
            CMD_SendString((uint8_t *)"\n\r   Number of tariffs > ");
            while (CMD_IsCmdReceived() == 0)
            {
                R_WDT_Restart();
            }
            p_cmd = CMD_Get();
            b_input = p_cmd[0];
            
            if (p_cmd[0] == 0)
            {
                input_valid = 1;
            }
            else
            {
                rlt = COMMAND_DecStringToUnsigned16(p_cmd, &input_valid);
                
                if ((rlt > METER_ENERGY_NUMBER_OF_TARIFF_MAX) ||
                    (rlt < METER_ENERGY_NUMBER_OF_TARIFF_MIN))
                {
                    input_valid = 0;
                }
                
                if (input_valid != 1)
                {
                    CMD_Printf((uint8_t *)"\n\r   Invalid number, please retry");
                }
                else
                {
                    energy_config.number_tariff = (uint8_t)rlt;
                }
            }
            CMD_AckCmdReceivedNoHeader();
            
        } while ((input_valid != 1));
        
        /* Wait for user input value : number_timeslot */
        do
        {
            CMD_SendString((uint8_t *)"\n\r   Number of time slot > ");
            while (CMD_IsCmdReceived() == 0)
            {
                R_WDT_Restart();
            }
            p_cmd = CMD_Get();
            b_input = p_cmd[0];
            
            if (p_cmd[0] == 0)
            {
                input_valid = 1;
            }
            else
            {
                rlt = COMMAND_DecStringToUnsigned16(p_cmd, &input_valid);
                if ((rlt > METER_ENERGY_NUMBER_OF_TIMESLOT_MAX) ||
                    (rlt < METER_ENERGY_NUMBER_OF_TIMESLOT_MIN))
                {
                    input_valid = 0;
                }
                
                if (input_valid != 1)
                {
                    CMD_Printf((uint8_t *)"\n\r   Invalid number, please retry");
                }
                else
                {
                    energy_config.number_timeslot = (uint8_t)rlt;
                }
            }
            CMD_AckCmdReceivedNoHeader();
            
        } while ((input_valid != 1));
        
        /* Wait for user input value : number_timeslot */
        for (i=0;i < METER_ENERGY_NUMBER_OF_TIMESLOT_MAX; i++)
        {
            do
            {
                CMD_Printf((uint8_t *)"\n\r   Timeslot%d (hour min tariff_no): > ", i);
                while (CMD_IsCmdReceived() == 0)
                {
                    R_WDT_Restart();
                }
                p_cmd = CMD_Get();
                b_input = p_cmd[0];
                
                if (p_cmd[0] == 0)
                {
                    input_valid = 1;
                }
                else
                {
                    p_cmd = COMMAND_GetScanOneParam(buffer, 20, p_cmd, (uint8_t *)" ", (uint8_t *)" ");
                    
                    if (p_cmd != NULL)
                    {
                        rlt       = COMMAND_DecStringToUnsigned16(buffer, &input_valid);
                        if (rlt > 23)
                        {
                            input_valid = 0;
                        }
                        
                        if (input_valid != 1)
                        {
                            CMD_Printf((uint8_t *)"\n\r   Invalid number, please retry");
                        }
                        else
                        {
                            energy_config.timeslot_list[i].timestart.hour = (uint8_t)rlt;
                        }
                    }
                    else
                    {
                        input_valid = 0;
                    }
                    
                    /* Continue with remaining params */
                    if (input_valid == 1)
                    {
                        p_cmd = COMMAND_GetScanOneParam(buffer, 20, p_cmd, (uint8_t *)" ", (uint8_t *)" ");
                        
                        if (p_cmd != NULL)
                        {
                            rlt       = COMMAND_DecStringToUnsigned16(buffer, &input_valid);
                            if (rlt > 59)
                            {
                                input_valid = 0;
                            }
                            
                            if (input_valid != 1)
                            {
                                CMD_Printf((uint8_t *)"\n\r   Invalid number, please retry");
                            }
                            else
                            {
                                energy_config.timeslot_list[i].timestart.minute = (uint8_t)rlt;
                            }
                        }
                        else
                        {
                            input_valid = 0;
                        }
                        
                    }
                    
                    /* Continue with remaining params */
                    if (input_valid == 1)
                    {
                        p_cmd = COMMAND_GetScanOneParam(buffer, 20, p_cmd, (uint8_t *)" ", (uint8_t *)" ");
                        
                        if (p_cmd != NULL)
                        {
                            rlt       = COMMAND_DecStringToUnsigned16(buffer, &input_valid);
                            if (rlt > energy_config.number_tariff)
                            {
                                input_valid = 0;
                            }
                            
                            if (input_valid != 1)
                            {
                                CMD_Printf((uint8_t *)"\n\r   Invalid number, please retry");
                            }
                            else
                            {
                                energy_config.timeslot_list[i].tariffno = (uint8_t)rlt;
                            }
                        }
                        else
                        {
                            input_valid = 0;
                        }
                        
                    }
                }
                CMD_AckCmdReceivedNoHeader();
                
            } while ((input_valid != 1));
        }
        
        CMD_SendString((uint8_t *)"\n\r");
        /* Set configuration data */
        CMD_Printf((uint8_t *)"Seting Energy Configuration...");
        if (ENERGY_SetConfig(&energy_config) != ENERGY_RET_OK)
        {
            CMD_Printf((uint8_t *)"FAILED\n\r");
        }
        else
        {
            CMD_Printf((uint8_t *)"OK\n\r");
        }

        CMD_Printf((uint8_t *)"Seting EM Core Configuration...");
        if (EM_SetConfig(&em_config) != EM_OK)
        {
            CMD_Printf((uint8_t *)"FAILED\n\r");
        }
        else
        {
            CMD_Printf((uint8_t *)"OK\n\r");
        }

        /* Start ENERGY operation */
        CMD_Printf((uint8_t *)"Start Energy maangement...");
        if (ENERGY_Start() != ENERGY_RET_OK)
        {
            CMD_Printf((uint8_t *)"FAILED\n\r");
            return 1;
        }
        else
        {
            CMD_Printf((uint8_t *)"OK\n\r");
        }
        
        /* Start EM operation */
        CMD_Printf((uint8_t *)"Start EM Core...");
        if (EM_Start() != EM_OK)
        {
            CMD_Printf((uint8_t *)"FAILED\n\r");
            return 1;
        }
        else
        {
            CMD_Printf((uint8_t *)"OK\n\r");
        }

        /* Backup calibrated data into Memory */
        CMD_Printf((uint8_t *)"Backup Configurations Into Storage...");
        if (CONFIG_Backup(CONFIG_ITEM_CONFIG) != EM_OK)
        {
            CMD_Printf((uint8_t *)"FAILED\n\r");
            return 1;
        }
        else
        {
            CMD_Printf((uint8_t *)"OK\n\r");
        }
    }
    #endif
    
    return 0;
}

/******************************************************************************
* Function Name   : COMMAND_InvokeGetSetPulseConfig
* Interface       : static void COMMAND_InvokeGetSetPulseConfig(uint8_t *arg_str)
* Description     : Command Invoke to get set pulse config
* Arguments       : uint8_t * arg_str: Arguments string
* Function Calls  : None
* Return Value    : None
******************************************************************************/
//static uint8_t COMMAND_InvokeGetSetPulseConfig(uint8_t *arg_str)
//{
//    uint8_t buffer[40];
//    uint8_t is_found;
//    uint8_t i = 0;
//    EM_CALIBRATION calib_info;
//    uint8_t result;

//    CMD_Printf((uint8_t *)"\n\r");

//    calib_info = EM_GetCalibInfo();

//    if (arg_str != NULL)
//    {
//        /* Scan  meter constant selection */
//        arg_str = COMMAND_GetScanOneParam(buffer, 40, arg_str, (uint8_t *)" ", (uint8_t *)" ");

//        if (arg_str != NULL)
//        {
//            calib_info.common.meter_constant = (uint16_t)COMMAND_DecStringToUnsigned16(buffer, &is_found);

//            if (is_found == 1)
//            {
//                if (calib_info.common.meter_constant < EM_METER_CONST_MIN) 
//                {
//                    CMD_Printf((uint8_t *)"Parameter error, input meter constant smaller than %d\n\r", EM_METER_CONST_MIN);
//                    return 1;
//                }
//                else if (calib_info.common.meter_constant > EM_METER_CONST_MAX) 
//                {
//                    CMD_Printf((uint8_t *)"Parameter error, input meter constant greater than %d\n\r", EM_METER_CONST_MAX);
//                    return 1;
//                }
                
//            }
//            else
//            {
//                CMD_Printf((uint8_t *)"Cannot parsed new parameter input\n\r");
//                return 1;
//            }

//        }
//        else
//        {
//            CMD_Printf((uint8_t *)"Cannot scan new parameter input\n\r");
//            return 1;
//        }

//        /* Scan pulse on time selection */
//        arg_str = COMMAND_GetScanOneParam(buffer, 40, arg_str, (uint8_t *)" ", (uint8_t *)" ");

//        if (arg_str != NULL)
//        {
//            calib_info.common.pulse_on_time = (uint16_t)EM_atof(buffer);

//            if (calib_info.common.pulse_on_time < EM_PULSE_ON_TIME_MIN) 
//            {
//                CMD_Printf((uint8_t *)"Parameter error, input pulse on time smaller than %d\n\r", EM_PULSE_ON_TIME_MIN);
//                return 1;
//            }
//        }
//        else
//        {
//            CMD_Printf((uint8_t *)"Cannot scan new parameter input\n\r");
//            return 1;
//        }

//        /* Stop EM operation */
//        CMD_Printf((uint8_t *)"Stopping EM ... ");
//        if (EM_Stop() != EM_OK) 
//        {
//            CMD_Printf((uint8_t *)"FAILED, new parameter not applied");
//            return 1;
//        }
//        else 
//        {
//            CMD_Printf((uint8_t *)"OK");
//        }
//        CMD_Printf((uint8_t *)"\n\r");

//        CMD_Printf((uint8_t *)"Setting new calibration info ... ");

//        result = EM_SetCalibInfo(&calib_info);

//        if (result != 0) 
//        {
//            CMD_Printf((uint8_t *)"FAILED, new parameter not applied");
//            return 1;
//        }
//        else 
//        {
//            CMD_Printf((uint8_t *)"OK");
//        }
//        CMD_Printf((uint8_t *)"\n\r");

//        /* Backup calibrated data into Storage Memory */
//        CMD_Printf((uint8_t *)"Backing up new calibration info ... ");
//        if (CONFIG_Backup(CONFIG_ITEM_CALIB) != CONFIG_OK)
//        {
//            CMD_Printf((uint8_t *)"FAILED, new parameter not restore on reset");
//            return 1;
//        }
//        else {
//            CMD_Printf((uint8_t *)"OK");
//        }
//        CMD_Printf((uint8_t *)"\n\r");

//        CMD_Printf((uint8_t *)"Restart EM ... OK");
//        EM_Start();
//        CMD_Printf((uint8_t *)"\n\r");

//        CMD_Printf((uint8_t *)"Set calibration info OK, new parameter applied\n\r");
//    }

//    CMD_Printf((uint8_t *)"\n\r");
//    CMD_Printf((uint8_t *)"Pulse on time: %-10.3f (ms) \n\r", (float32_t)calib_info.common.pulse_on_time);
//    CMD_Printf((uint8_t *)"Meter constant: %lu (imp/kWh | imp/kvarh) \n\r", (uint32_t)calib_info.common.meter_constant);

//    return 0;
//}

extern volatile float32_t g_debug_direct_power_output_value;
/******************************************************************************
* Function Name   : COMMAND_InvokeGetSetPulsePower
* Interface       : static void COMMAND_InvokeGetSetPulsePower(uint8_t *arg_str)
* Description     : Command Invoke to get set pulse power
* Arguments       : uint8_t * arg_str: Arguments string
* Function Calls  : None
* Return Value    : None
******************************************************************************/
static uint8_t COMMAND_InvokeGetSetPulsePower(uint8_t *arg_str)
{
    uint8_t buffer[40];
    uint8_t is_found;
    uint8_t i = 0;
    float32_t pulse_power;
    uint8_t result;

    CMD_Printf((uint8_t *)"\n\r");

    if (arg_str != NULL)
    {
        /* Scan pulse on time selection */
        arg_str = COMMAND_GetScanOneParam(buffer, 40, arg_str, (uint8_t *)" ", (uint8_t *)" ");

        if (arg_str != NULL)
        {
            pulse_power = atof((char *)buffer);
        }
        else
        {
            CMD_Printf((uint8_t *)"Cannot scan new parameter input\n\r");
            return 1;
        }

        g_debug_direct_power_output_value = pulse_power;

        CMD_Printf((uint8_t *)"Set direct pulse power OK\n\r");
    }

    CMD_Printf((uint8_t *)"\n\r");
    CMD_Printf((uint8_t *)"Direct pulse power value: %-10.3f (W) \n\r", g_debug_direct_power_output_value);
    CMD_Printf((uint8_t *)"Bypass calculated power : %s\n\r", (g_debug_direct_power_output_value >= 0.0f) ? "Yes" : "No");

    return 0;
}

/******************************************************************************
* Function Name    : static uint8_t COMMAND_InvokeSetDSADChannelPower(uint8_t *arg_str)
* Description      : Command Invoke DSAD Channel Power
* Arguments        : uint8_t index: Command index
*                  : uint8_t *arg_str: Arguments string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
******************************************************************************/
static uint8_t COMMAND_InvokeDSADPowerGetSet(uint8_t *arg_str)
{
    uint8_t buffer[40];
    
    uint16_t operation;
    uint8_t is_found;
    uint16_t set_value = 0;
    uint8_t fast_scan_status;
    
    uint8_t dsad_channel[4];
    uint8_t i = 0;
    
    static const uint8_t line_break[]   = "+----------------------------------+\n\r";
    
    CMD_Printf((uint8_t *)"\n\r");  
    
    memset(&dsad_channel, 0, sizeof(dsad_channel));
    
    if (arg_str != NULL)
    {
        /* Scan the arguments */
        arg_str = COMMAND_GetScanOneParam(buffer, 40, arg_str, (uint8_t *)" ", (uint8_t *)" ");
        
        fast_scan_status = COMMAND_FastInputScan(dsad_channel, buffer, 4);

        if (fast_scan_status != 0)
        {
            CMD_Printf((uint8_t *)"Parameter error, check channel selection\n\r");  
            return 1;
        }
        
        arg_str = COMMAND_GetScanOneParam(buffer, 40, arg_str, (uint8_t *)" ", (uint8_t *)" ");
        if (arg_str != NULL)
        {
            operation = COMMAND_DecStringToUnsigned16(buffer, &is_found);
            
            if (is_found != 1 || 
                (operation != 0 && operation != 1))
            {
                CMD_Printf((uint8_t *)"Parameter error, operation is 0 or 1 only\n\r"); 
                return 1;
            }
            
            /* Up to here, parameter is OK, set the value for DSADMR */
            
            while ((i < 4) &&
                    (dsad_channel[i] != 0 || i == 0))
            {
                if (operation)
                {
                    DSADMR |= 0x0101 << dsad_channel[i];
                }
                else
                {
                    DSADMR &= (uint16_t)(~(0x0101 << dsad_channel[i]));
                }
                i++;
            }
            
            CMD_Printf((uint8_t *)"Set channel power state OK\n\r");
        }
        else
        {
            CMD_Printf((uint8_t *)"No state input\n\r");
            return 1;
        }
    }
    
    CMD_Printf((uint8_t *)line_break);
    CMD_Printf((uint8_t *)"DSAD Channel power state as below: \n\r");
    CMD_Printf((uint8_t *)line_break);  
    
    CMD_Printf((uint8_t *)"%-10s %-10s %-10s %-10s\n\r", 
                                "CH0",
                                "CH1",
                                "CH2",
                                "CH3"); 
    CMD_Printf((uint8_t *)"%-10s %-10s %-10s %-10s\n\r",
                                (DSADMR & 0x0101) ? "ON" : "OFF",
                                (DSADMR & 0x0202) ? "ON" : "OFF",
                                (DSADMR & 0x0404) ? "ON" : "OFF",
                                (DSADMR & 0x0808) ? "ON" : "OFF");
    return 0;   
}

/******************************************************************************
* Function Name    : static uint8_t COMMAND_InvokeDSADPhaseGetSet(uint8_t *arg_str)
* Description      : Command Invoke DSAD Channel Phase Adjustment
* Arguments        : uint8_t index: Command index
*                  : uint8_t *arg_str: Arguments string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
******************************************************************************/
static uint8_t COMMAND_InvokeDSADPhaseGetSet(uint8_t *arg_str)
{
    uint8_t buffer[40];
    uint8_t dsad_channel[4];
    uint16_t phase_value;
    uint8_t is_found;
    uint8_t fast_scan_status;
    uint16_t *ptr_phcr_base = (uint16_t *)&DSADPHCR0;
    uint8_t i = 0;
    
    static const uint8_t line_break[]   = "+----------------------------------+\n\r";
    
    CMD_Printf((uint8_t *)"\n\r");  
    
    if (arg_str != NULL)
    {
        /* Scan the arguments */
        arg_str = COMMAND_GetScanOneParam(buffer, 40, arg_str, (uint8_t *)" ", (uint8_t *)" ");
        
        fast_scan_status = COMMAND_FastInputScan(dsad_channel, buffer, 4);

        if (fast_scan_status != 0)
        {
            CMD_Printf((uint8_t *)"Parameter error, check channel selection\n\r");  
            return 1;
        }
        
        arg_str = COMMAND_GetScanOneParam(buffer, 40, arg_str, (uint8_t *)" ", (uint8_t *)" ");
        
        
        if (arg_str != NULL)
        {
            phase_value = COMMAND_DecStringToUnsigned16(buffer, &is_found);
            
            if (is_found != 1 || 
                (phase_value > 1151))
            {
                CMD_Printf((uint8_t *)"Parameter error, phase value is incorrect\n\r"); 
                return 1;
            }
            
            /* Up to here, parameter is OK, set the value for DSADPHCRx */
            
            while ((i < 4) &&
                    (dsad_channel[i] != 0 || i == 0))
            {
                *(ptr_phcr_base + dsad_channel[i]) = phase_value;
                i++;
            }
            
            CMD_Printf((uint8_t *)"Set phase OK\n\r");  
        }
        else
        {
            CMD_Printf((uint8_t *)"No phase step input\n\r");
            return 1;   
        }
    }
    
    CMD_Printf((uint8_t *)line_break);
    CMD_Printf((uint8_t *)"DSAD Phase value is as below: \n\r");
    CMD_Printf((uint8_t *)line_break);
    
    
    CMD_Printf((uint8_t *)"%-18s %-12s %-12s %-12s %-12s\n\r", 
                                " ",
                                "CH0",
                                "CH1",
                                "CH2",
                                "CH3");
    CMD_Printf((uint8_t *)"%-18s %-2s%-10x %-2s%-10x %-2s%-10x %-2s%-10x\n\r",
                                "Delay step (hex)",
                                "0x",DSADPHCR0,
                                "0x",DSADPHCR1,
                                "0x",DSADPHCR2,
                                "0x",DSADPHCR3);
    CMD_Printf((uint8_t *)"%-18s %-12d %-12d %-12d %-12d\n\r",
                                "Delay step (dec)",
                                DSADPHCR0,
                                DSADPHCR1,
                                DSADPHCR2,
                                DSADPHCR3);
    return 0;
}


/******************************************************************************
* Function Name    : static uint8_t COMMAND_InvokeDSADHpfGetSet(uint8_t *arg_str)
* Description      : Command Invoke DSAD Channels High-pass filter
* Arguments        : uint8_t index: Command index
*                  : uint8_t *arg_str: Arguments string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
******************************************************************************/
static uint8_t COMMAND_InvokeDSADHpfGetSet(uint8_t *arg_str)
{
    uint8_t buffer[40];
    uint8_t dsad_channel[4];
    uint8_t hpf_cutoff;
    uint8_t state;
    uint8_t is_found;
    uint8_t fast_scan_status;
    uint8_t i = 0;
    
    static const uint8_t line_break[]   = "+----------------------------------+\n\r";
    
    CMD_Printf((uint8_t *)"\n\r");  
    
    if (arg_str != NULL)
    {
        /* Scan channel selection */
        arg_str = COMMAND_GetScanOneParam(buffer, 40, arg_str, (uint8_t *)" ", (uint8_t *)" ");
        
        fast_scan_status = COMMAND_FastInputScan(dsad_channel, buffer, 4);

        if (fast_scan_status != 0)
        {
            CMD_Printf((uint8_t *)"Parameter error, check channel selection\n\r");  
            return 1;
        }
        
        /* Scan state selection */
        arg_str = COMMAND_GetScanOneParam(buffer, 40, arg_str, (uint8_t *)" ", (uint8_t *)" ");

        if (arg_str != NULL)
        {
            state = (uint8_t)COMMAND_DecStringToUnsigned16(buffer, &is_found);
        
            if (is_found != 1 || 
                state > 1)
            {
                CMD_Printf((uint8_t *)"Parameter error, state selection uncorrect\n\r");    
                return 1;
            }
        }
        else
        {
            CMD_Printf((uint8_t *)"No state parameter input\n\r");
            return 1;       
        }
        
        if (state == 1)
        {
            /* Scan cut-off frequency selection */
            arg_str = COMMAND_GetScanOneParam(buffer, 40, arg_str, (uint8_t *)" ", (uint8_t *)" ");
            
            if (arg_str != NULL)
            {
                hpf_cutoff = (uint8_t)COMMAND_DecStringToUnsigned16(buffer, &is_found);
                
                if (is_found != 1 || 
                    hpf_cutoff > 3)
                {
                    CMD_Printf((uint8_t *)"Parameter error, cut-off frequency 0-3 only\n\r");   
                    return 1;
                }
            }
            else
            {
                CMD_Printf((uint8_t *)"No cut-off parameter input\n\r");
                return 1;
            }
        }
        /* Up to here, parameter is OK, set the value for DSADHPFCR */
        
        /* Set channel hpf operation state */
        while ((i < 4) &&
                (dsad_channel[i] != 0 || i == 0))
        {
            if (state == 1)
            {
                /* Must clear bit 4 and 5 */
                DSADHPFCR &= (uint8_t)~(1<<dsad_channel[i] | 0x30);
            }
            else
            {
                DSADHPFCR |= (uint8_t)(1<<dsad_channel[i]);
            }
            i++;
        }
        
        if (state == 1)
        {
            /* Set cut-off frequency */
            DSADHPFCR &= 0x0F;
            DSADHPFCR |= (hpf_cutoff << 6);
        }
        CMD_Printf((uint8_t *)"Set HPF OK\n\r");    
    }
    
    CMD_Printf((uint8_t *)line_break);
    CMD_Printf((uint8_t *)"DSAD High-pass filter information: \n\r");
    CMD_Printf((uint8_t *)line_break);
    CMD_Printf((uint8_t *)"%-10s %-10s %-10s %-10s %-18s\n\r", 
                                "CH0",
                                "CH1",
                                "CH2",
                                "CH3",
                                "Cut-off Frequency");
    CMD_Printf((uint8_t *)"%-10s %-10s %-10s %-10s %-18s\n\r",
                                (DSADHPFCR&0x01) ? "OFF" : "ON",
                                (DSADHPFCR&0x02) ? "OFF" : "ON",
                                (DSADHPFCR&0x04) ? "OFF" : "ON",
                                (DSADHPFCR&0x08) ? "OFF" : "ON",
                                g_hpf_type[(DSADHPFCR & 0xC0) >> 6]);

    return 0;
}

/******************************************************************************
* Function Name    : static uint8_t COMMAND_InvokeDSADGainGetSet(uint8_t *arg_str)
* Description      : Command Invoke DSAD Gain Get/Set
* Arguments        : uint8_t index: Command index
*                  : uint8_t *arg_str: Arguments string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
******************************************************************************/
static uint8_t COMMAND_InvokeDSADGainGetSet(uint8_t *arg_str)
{
    uint8_t buffer[40];
    uint8_t dsad_channel[4];
    uint16_t gain_value;
    uint8_t is_found;
    uint8_t fast_scan_status;
    uint8_t *ptr_gain_base = (uint8_t *)&DSADGCR0;
    uint8_t i = 0;
    
    static const uint8_t line_break[]   = "+----------------------------------+\n\r";
    
    CMD_Printf((uint8_t *)"\n\r");  
    
    if (arg_str != NULL)
    {
        /* Scan the arguments */
        arg_str = COMMAND_GetScanOneParam(buffer, 40, arg_str, (uint8_t *)" ", (uint8_t *)" ");
        
        fast_scan_status = COMMAND_FastInputScan(dsad_channel, buffer, 4);

        if (fast_scan_status != 0)
        {
            CMD_Printf((uint8_t *)"Parameter error, check channel selection\n\r");  
            return 1;
        }
        
        arg_str = COMMAND_GetScanOneParam(buffer, 40, arg_str, (uint8_t *)" ", (uint8_t *)" ");
        
        
        if (arg_str != NULL)
        {
            gain_value = COMMAND_DecStringToUnsigned16(buffer, &is_found);
            
            if (is_found != 1 || 
                ((gain_value != 1) &&
                (gain_value != 2) &&
                (gain_value != 4) &&
                (gain_value != 8) &&
                (gain_value != 16) &&
                (gain_value != 32) &&
                (1)
                )
                )
            {
                CMD_Printf((uint8_t *)"Parameter error, gain value is 1,2,4,8,16,32 only \n\r"); 
                return 1;
            }
            
            /* Up to here, parameter is OK, set the value for DSADPHCRx */
            
            while ((i < 4) &&
                    (dsad_channel[i] != 0 || i == 0))
            {
                R_DSADC_SetChannelGain(
                        (dsad_channel_t)dsad_channel[i],
                        R_DSADC_GetGainEnumValue((uint8_t)gain_value)
                    );
                i++;
            }
            
            CMD_Printf((uint8_t *)"Set gain OK\n\r");  
        }
        else
        {
            CMD_Printf((uint8_t *)"No gain value input\n\r");
            return 1;   
        }
    }
    
    CMD_Printf((uint8_t *)line_break);
    CMD_Printf((uint8_t *)"DSAD Gain value is as below: \n\r");
    CMD_Printf((uint8_t *)line_break);
    
    
    CMD_Printf((uint8_t *)"%-18s %-12s %-12s %-12s %-12s\n\r", 
                                " ",
                                "CH0",
                                "CH1",
                                "CH2",
                                "CH3");
    CMD_Printf((uint8_t *)"%-18s %-12s %-12s %-12s %-12s\n\r",
                                "Gain value",
                                COMMAND_GetDsadGainName( R_DSADC_GetGainEnumValue( R_DSADC_GetChannelGain((dsad_channel_t)0) )),
                                COMMAND_GetDsadGainName( R_DSADC_GetGainEnumValue( R_DSADC_GetChannelGain((dsad_channel_t)1) )),
                                COMMAND_GetDsadGainName( R_DSADC_GetGainEnumValue( R_DSADC_GetChannelGain((dsad_channel_t)2) )),
                                COMMAND_GetDsadGainName( R_DSADC_GetGainEnumValue( R_DSADC_GetChannelGain((dsad_channel_t)3) ))
                        );
    return 0;
}

/******************************************************************************
* Function Name   : COMMAND_InvokeCPULoad
* Interface       : static void COMMAND_InvokeCPULoad(uint8_t *arg_str)
* Description     : Command Invoke Watch DSAD
* Arguments       : uint8_t * arg_str: Arguments string
* Function Calls  : None
* Return Value    : None
******************************************************************************/
static uint8_t COMMAND_InvokeCPULoad(uint8_t *arg_str)
{
    #ifdef METER_ENABLE_MEASURE_CPU_LOAD
    
    float max_dsad_time     = 0.0f;
    float min_dsad_time     = 0.0f;
    float avg_dsad_time     = 0.0f;
    EM_CALIBRATION calib    = EM_GetCalibInfo();
    
    LOADTEST_TAU_Init();
    
    g_timer0_dsad_sum_counter = 0;
    g_timer0_dsad_maxcounter = 0;
    g_timer0_dsad_mincounter = 0xFFFF;
    g_dsad_count = 0;
    g_timer0_diff = 0;
    
    CMD_Printf((uint8_t *)"\n\r");
    CMD_Printf((uint8_t *)"\n\rStarted measuring DSAD functions performance");
    CMD_Printf((uint8_t *)"\n\rPlease wait for about %0.3f seconds while system measuring",(float)g_dsad_max_count * 0.000256f);
    while(g_dsad_count < g_dsad_max_count)
    {
        R_WDT_Restart();    
    }
    
    /* 
        Substract cycles not related to EM processing (from Timer start to Timer stop
            No need now
    */
    g_timer0_dsad_maxcounter -= (0);
    
    max_dsad_time   = ((float)g_timer0_dsad_maxcounter      / (float)(LOADTEST_CGC_GetClock())) / 1000.0f;
    min_dsad_time   = ((float)g_timer0_dsad_mincounter      / (float)(LOADTEST_CGC_GetClock())) / 1000.0f;
    avg_dsad_time   = ((float)g_timer0_dsad_sum_counter     / ((float)(LOADTEST_CGC_GetClock()) * g_dsad_max_count)) / 1000.0f;
    
    CMD_Printf((uint8_t *)"\n\r-------------------------------------------");
    
    CMD_Printf((uint8_t *)"\n\r% -35s %00.3fus",
                            "Max CPU time spent in DSAD:",
                            max_dsad_time * 1e6f
              );
              
    CMD_Printf((uint8_t *)"\n\r% -35s %00.3f%%",
                            "Max CPU Load in percentage:",
                            ((max_dsad_time * calib.common.sampling_frequency)*100.0f)
              );
              
    CMD_Printf((uint8_t *)"\n\r% -35s %00.3fus",
                            "Min CPU time spent in DSAD:",
                            min_dsad_time * 1e6f
              );
              
    CMD_Printf((uint8_t *)"\n\r% -35s %00.3f%%",
                            "Min CPU Load in percentage:",
                            ((min_dsad_time * calib.common.sampling_frequency)*100.0f)
              );

    CMD_Printf((uint8_t *)"\n\r% -35s %00.3fus",
                            "Average CPU time spent in DSAD:",
                            avg_dsad_time * 1e6f
              );
              
    CMD_Printf((uint8_t *)"\n\r% -35s %00.3f%%",
                            "Average CPU Load in percentage:",
                            ((avg_dsad_time * calib.common.sampling_frequency)*100.0f)
              );              
              
    CMD_Printf((uint8_t *)"\n\r-------------------------------------------");

    LOADTEST_TAU_DeInit();
    
    #else
    
    CMD_Printf((uint8_t *)"\n\r Not enable. Turn on by define METER_ENABLE_MEASURE_CPU_LOAD");
    
    #endif /* METER_ENABLE_MEASURE_CPU_LOAD */

    
    return 0;   
}

/******************************************************************************
* Function Name   : COMMAND_InvokeSetMaxDemandConfig
* Interface       : static void COMMAND_InvokeSetMaxDemandConfig(uint8_t *arg_str)
* Description     : Command Invoke Set Max Demand Configuration
*                   Usage:  CMD> mdmconfig
* Arguments       : uint8_t * arg_str: Arguments string
* Function Calls  : None
* Return Value    : None
******************************************************************************/
static uint8_t COMMAND_InvokeSetMaxDemandConfig(uint8_t *arg_str)
{
//    uint8_t buffer[20];             /* Data buffer to store input arguments */
//    uint32_t period;
//    uint16_t number_of_period;
//    uint8_t period_in_minute;
//    uint8_t total_period_in_minute;
//    r_mdm_t mdm_config;

//    CMD_Printf((uint8_t *)"\n\r");

//    /* Get period (in seconds) parameter */
//    if (arg_str != NULL) {

//        arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" ");
//        if (arg_str != NULL) {
//            /* get period in seconds */
//            period = (uint32_t)EM_atol(buffer);

//        }
//        else {
//            CMD_Printf((uint8_t *)"Parameter error\n\r");
//            return 1;
//        }

//        /* Get number of period parameter */
//        arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" ");
//        if (arg_str != NULL) {
//            /* get period in seconds */
//            number_of_period = (uint16_t)EM_atol(buffer);

//            if (number_of_period < SCHEDULER_MAX_DEMAND_NUMBER_OF_PERIOD_MIN ||
//                number_of_period > SCHEDULER_MAX_DEMAND_NUMBER_OF_PERIOD_MAX ||
//                (0)) {
//                CMD_Printf((uint8_t *)"Parameter error: number of period between %d(s) and %d(s)\n\r",
//                    ((uint16_t)SCHEDULER_MAX_DEMAND_NUMBER_OF_PERIOD_MIN),
//                    ((uint16_t)SCHEDULER_MAX_DEMAND_NUMBER_OF_PERIOD_MAX)
//                );
//                return 1;
//            }
//        }
//        else {
//            CMD_Printf((uint8_t *)"Parameter error\n\r");
//            return 1;
//        }

//        /* Check again the combination of period and number of period */
//        period_in_minute = period / 60;
//        total_period_in_minute = (uint8_t)(period_in_minute * number_of_period);

//        CMD_Printf((uint8_t *)"Calculated total period in minutes: %d\n\r", total_period_in_minute);

//        /* Checking the max demand period */
//        if (((24 * 60) % total_period_in_minute) != 0) {
//            CMD_Printf((uint8_t *)"Parameter error: total period must be rounded up by 1 minute\n\r",
//                ((uint16_t)SCHEDULER_MAX_DEMAND_NUMBER_OF_PERIOD_MIN),
//                ((uint16_t)SCHEDULER_MAX_DEMAND_NUMBER_OF_PERIOD_MAX)
//            );
//            return 1;
//        }

//        if (((total_period_in_minute) < SCHEDULER_MAX_DEMAND_PERIOD_MIN) ||
//            ((total_period_in_minute) > SCHEDULER_MAX_DEMAND_PERIOD_MAX) ||
//            (0)) {
//            CMD_Printf((uint8_t *)"Parameter error: total period is out of range (%d minute - %d minute) \n\r",
//                SCHEDULER_MAX_DEMAND_PERIOD_MIN,
//                SCHEDULER_MAX_DEMAND_PERIOD_MAX
//            );
//            return 1;
//        }

//        /* Setting to energy max demand configuration */

//        mdm_config.period = period_in_minute;
//        mdm_config.period_index = number_of_period;

//        CMD_Printf((uint8_t *)"Setting max demand configuration ... ");
//        if (R_MDM_SetPassiveConfig(&mdm_config) != ENERGY_RET_OK) {
//            CMD_Printf((uint8_t *)"FAILED\n\r");
//            return 1;
//        }
//        else {
//            CMD_Printf((uint8_t *)"OK\n\r");
//        }

//        /* Raise request to apply passive max demand configuration */
//        R_MDM_RequestActivatePassiveConfig();

//        return 0;
//    }

//    /* Read the parameter */
//    mdm_config = R_MDM_GetConfig();

//    CMD_Printf((uint8_t *)"Period (minutes)   : %d \n\r", mdm_config.period);
//    CMD_Printf((uint8_t *)"Number of period   : %d \n\r", mdm_config.period_index);
//    CMD_Printf((uint8_t *)"Interval (minutes) : %d \n\r", mdm_config.period * mdm_config.number_of_period);
//    CMD_Printf((uint8_t *)"Period counter     : %d \n\r", R_MDM_GetCurrentPeriodCounter());
//    CMD_Printf((uint8_t *)"Demand Buffer index: %d \n\r", R_MDM_GetCurrentDemandBufferIndex());

    return 0;
}

/******************************************************************************
* Function Name   : COMMAND_InvokeResetMaxDemandData
* Interface       : static void COMMAND_InvokeResetMaxDemandData(uint8_t *arg_str)
* Description     : Command Invoke Reset Max Demand Data
* Arguments       : uint8_t * arg_str: Arguments string
* Function Calls  : None
* Return Value    : None
******************************************************************************/
static uint8_t COMMAND_InvokeResetMaxDemandData(uint8_t *arg_str)
{
    uint8_t buffer[20];             /* Data buffer to store input arguments */
    uint8_t confirm;

    CMD_Printf((uint8_t *)"\n\r");

    /* Get period (in seconds) parameter */
    if (arg_str != NULL) {
        arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" ");
        if (arg_str != NULL) {
            /* get period in seconds */
            confirm = (uint8_t)atoi((char *)buffer);

            if (confirm != 1) {
                CMD_Printf((uint8_t *)"Confirm code not equal to 1, no action done\n\r");
                return 1;
            }

            CMD_Printf((uint8_t *)"Reset max demand... ");
            R_MDM_Reset();
            CMD_Printf((uint8_t *)"OK\n\r");
        }
        else {
            CMD_Printf((uint8_t *)"Parameter error\n\r");
            return 1;
        }
    }
    else {
        CMD_Printf((uint8_t *)"No parameter received, please input 1 to confirm reset of max demand \n\r");
    }

    return 0;
}

/******************************************************************************
* Function Name   : COMMAND_InvokeNextMaxDemandPeriod
* Interface       : static void COMMAND_InvokeNextMaxDemandPeriod(uint8_t *arg_str)
* Description     : Command Invoke Reuqest Next Max Demand Period
* Arguments       : uint8_t * arg_str: Arguments string
* Function Calls  : None
* Return Value    : None
******************************************************************************/
static uint8_t COMMAND_InvokeNextMaxDemandPeriod(uint8_t *arg_str)
{
    uint8_t buffer[20];             /* Data buffer to store input arguments */
    uint8_t confirm;

    CMD_Printf((uint8_t *)"\n\r");

    /* Get period (in seconds) parameter */
    if (arg_str != NULL) {
        arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" ");
        if (arg_str != NULL) {
            /* get period in seconds */
            confirm = (uint8_t)atoi((char *)buffer);

            if (confirm != 1) {
                CMD_Printf((uint8_t *)"Confirm code not equal to 1, no action done\n\r");
                return 1;
            }

            CMD_Printf((uint8_t *)"Request next max demand period... ");
            R_MDM_NextPeriod(&gp_inst_LastDataPop->capture_time);
            CMD_Printf((uint8_t *)"OK\n\r");
        }
        else {
            CMD_Printf((uint8_t *)"Parameter error\n\r");
            return 1;
        }
    }
    else {
        CMD_Printf((uint8_t *)"No parameter received, please input 1 to confirm request to next max demand period \n\r");
    }

    return 0;
}

/******************************************************************************
* Function Name   : COMMAND_InvokeDisplayMdmAll
* Interface       : static void COMMAND_InvokeDisplayMdmAll(uint8_t *arg_str)
* Description     : Command Invoke Display all max demand data
* Arguments       : uint8_t * arg_str: Arguments string
* Function Calls  : None
* Return Value    : None
******************************************************************************/
static uint8_t COMMAND_InvokeDisplayMdmAll(uint8_t *arg_str)
{
    r_mdm_counter_t mdm_max_counter;
    r_mdm_counter_t mdm_current_average_counter;
    r_mdm_counter_t mdm_last_average_counter;
    r_mdm_counter_t mdm_start_period_counter, mdm_start_interval_counter;
    rtc_counter_value_t rtctime, mdm_start_period_time, mdm_start_interval_time;

    uint8_t i;
    uint8_t get_status, get_status2;
    r_mdm_counter_t mdm_counter;
    float32_t mdm_value;
    rtc_counter_value_t mdm_capture_time;

    const uint8_t param_format_timeshort[] = ", %02d/%02d/20%02d %02d:%02d:%02d"; // DD/MM/YYYY HH:MM:SS
	
	const char* const display_format[] = 
    {
        /* SlotID = MDM_ACTIVE_TOTAL   */   "\n\r   1. Active Total MDM         (kW)  :  %0.2f",
        /* SlotID = MDM_ACTIVE_TOTAL   */   "\n\r   2. Capacitive Reactive MDM  (kVAr):  %0.2f",
        /* SlotID = MDM_ACTIVE_TOTAL   */   "\n\r   2. Inductive Reactive MDM   (kVAr):  %0.2f",
        /* SlotID = MDM_APPARENT_TOTAL */   "\n\r   3. Apparent Total           (kVA) :  %0.2f",
    };
	
    const char* const display_format_tz[] = 
    {
        /* SlotID = MDM_ACTIVE_TZ1     */   "\n\r   MDM Active TZ1     (kW , RTC):  %# 15.3f",
        /* SlotID = MDM_ACTIVE_TZ2     */   "\n\r   MDM Active TZ2     (kW , RTC):  %# 15.3f",
        /* SlotID = MDM_ACTIVE_TZ3     */   "\n\r   MDM Active TZ3     (kW , RTC):  %# 15.3f",
        /* SlotID = MDM_ACTIVE_TZ4     */   "\n\r   MDM Active TZ4     (kW , RTC):  %# 15.3f",
        /* SlotID = MDM_ACTIVE_TZ5     */   "\n\r   MDM Active TZ5     (kW , RTC):  %# 15.3f",
        /* SlotID = MDM_ACTIVE_TZ6     */   "\n\r   MDM Active TZ6     (kW , RTC):  %# 15.3f",
        /* SlotID = MDM_ACTIVE_TZ7     */   "\n\r   MDM Active TZ7     (kW , RTC):  %# 15.3f",
        /* SlotID = MDM_ACTIVE_TZ8     */   "\n\r   MDM Active TZ8     (kW , RTC):  %# 15.3f",
    };
	
	const char* const display_format_apparent_tz[] = 
    {
        /* SlotID = MDM_APPARENT_TZ1   */   "\n\r   MDM Apparent TZ1   (kVA, RTC):  %# 15.3f",
        /* SlotID = MDM_APPARENT_TZ2   */   "\n\r   MDM Apparent TZ2   (kVA, RTC):  %# 15.3f",
        /* SlotID = MDM_APPARENT_TZ3   */   "\n\r   MDM Apparent TZ3   (kVA, RTC):  %# 15.3f",
        /* SlotID = MDM_APPARENT_TZ4   */   "\n\r   MDM Apparent TZ4   (kVA, RTC):  %# 15.3f",
        /* SlotID = MDM_APPARENT_TZ5   */   "\n\r   MDM Apparent TZ5   (kVA, RTC):  %# 15.3f",
        /* SlotID = MDM_APPARENT_TZ6   */   "\n\r   MDM Apparent TZ6   (kVA, RTC):  %# 15.3f",
        /* SlotID = MDM_APPARENT_TZ7   */   "\n\r   MDM Apparent TZ7   (kVA, RTC):  %# 15.3f",
        /* SlotID = MDM_APPARENT_TZ8   */   "\n\r   MDM Apparent TZ8   (kVA, RTC):  %# 15.3f"
    };
    
    /* Measurement API */
    mdm_max_counter.active                      = R_MDM_GetActiveMaxDemand();
    mdm_max_counter.reactive_cap                = R_MDM_GetCapacitiveReactiveMaxDemand();
    mdm_max_counter.reactive_ind                = R_MDM_GetInductiveReactiveMaxDemand();
    mdm_max_counter.apparent                    = R_MDM_GetApparentMaxDemand();
    
	CMD_Printf((uint8_t *)display_format[0], mdm_max_counter.active);
    CMD_Printf((uint8_t *)display_format[1], mdm_max_counter.reactive_cap);
    CMD_Printf((uint8_t *)display_format[2], mdm_max_counter.reactive_ind);
    CMD_Printf((uint8_t *)display_format[3], mdm_max_counter.apparent);

    CMD_Printf((uint8_t *)"\n\r   Capture Time (RTC): ");
    R_MDM_GetActiveMaxDemandCapturedTime(&mdm_capture_time);
    CMD_Printf((uint8_t *)param_format_timeshort,
        mdm_capture_time.day,
        mdm_capture_time.month,
        mdm_capture_time.year,
        mdm_capture_time.hour,
        mdm_capture_time.min,
        mdm_capture_time.sec
    );
	
	CMD_Printf((uint8_t *)"\n\r");
	
    for (i = 0; i < (uint8_t)MDM_MAX_TIMEZONE_SUPPORT; i++)
    {
        memset(&mdm_counter, 0, sizeof(r_mdm_counter_t));
        get_status = R_MDM_GetActiveMaxDemandTz(i, &mdm_value);
        get_status2 = R_MDM_GetMaxDemandActiveCapturedTimeTz(i, &mdm_capture_time);
        if (get_status == MDM_RET_OK && get_status2 == MDM_RET_OK)
        {
            CMD_Printf((uint8_t *)display_format_tz[i], mdm_value);
            CMD_Printf((uint8_t *)param_format_timeshort,
                mdm_capture_time.day,
                mdm_capture_time.month,
                mdm_capture_time.year,
                mdm_capture_time.hour,
                mdm_capture_time.min,
                mdm_capture_time.sec
            );
        }
        else
        {
            CMD_SendString((uint8_t *)"Get failed!");
        }  
    }
    
    for (i = 0; i < (uint8_t)MDM_MAX_TIMEZONE_SUPPORT; i++)
    {
        memset(&mdm_counter, 0, sizeof(r_mdm_counter_t));
        get_status = R_MDM_GetApparentMaxDemandTz(i, &mdm_value);
        get_status2 = R_MDM_GetMaxDemandApparentCapturedTimeTz(i, &mdm_capture_time);
        if (get_status == MDM_RET_OK && get_status2 == MDM_RET_OK)
        {
            CMD_Printf((uint8_t *)display_format_apparent_tz[i], mdm_value);
            CMD_Printf((uint8_t *)param_format_timeshort,
                mdm_capture_time.day,
                mdm_capture_time.month,
                mdm_capture_time.year,
                mdm_capture_time.hour,
                mdm_capture_time.min,
                mdm_capture_time.sec
            );
        }
        else
        {
            CMD_SendString((uint8_t *)"Get failed!");
        }  
    }

    CMD_SendString((uint8_t *)"\n\r");

    return 0;
}

/******************************************************************************
* Function Name   : COMMAND_InvokeDisplayBufferMdm
* Interface       : static void COMMAND_InvokeDisplayBufferMdm(uint8_t *arg_str)
* Description     : Command Invoke Display max demand average buffer
* Arguments       : uint8_t * arg_str: Arguments string
* Function Calls  : None
* Return Value    : None
******************************************************************************/
static uint8_t COMMAND_InvokeDisplayBufferMdm(uint8_t *arg_str)
{
//#if 1    
//    r_mdm_counter_t mdm_buffer;
//    r_mdm_t mdm_config;
//    r_tariff_t tariff_config;
//    uint8_t i;

//    const char* const display_format[] = 
//    {
//        "\n\r   Active Demand Counter       (kW) [%d]: %0.2f",
//        "\n\r   Reactive Demand Counter C (kVAr) [%d]: %0.2f",
//        "\n\r   Reactive Demand Counter L (kVAr) [%d]: %0.2f",
//        "\n\r   Apparent Demand Counter    (kVA) [%d]: %0.2f"
//    };

//    mdm_config = ENERGY_MDM_GetConfig();
   
//    for (i = 0; i < mdm_config.number_of_period; i++)
//    {
//        EPR_Read(
//            STORAGE_EEPROM_ENERGY_MDM_MOVING_AVERAGE_BUFFER_ADDR + ((uint16_t)i * sizeof(ENERGY_MDM_COUNTER)),
//            (uint8_t *)&mdm_buffer,
//            sizeof(ENERGY_MDM_COUNTER)
//        );

//        CMD_SendString((uint8_t *)"\n\rDemand buffer:");
//        /* Print out information */
//        CMD_SendString((uint8_t *)line_break);
        
//		CMD_Printf((uint8_t *)display_format[0], i, mdm_buffer.active);
//        CMD_Printf((uint8_t *)display_format[1], i, mdm_buffer.reactive_cap);
//        CMD_Printf((uint8_t *)display_format[2], i, mdm_buffer.reactive_ind);
//        CMD_Printf((uint8_t *)display_format[3], i, mdm_buffer.apparent);
//    }
//    /* Print out information */
//    CMD_SendString((uint8_t *)"\n\r");
//#else
//    CMD_SendString((uint8_t *)"\n\rNot implemented");
//#endif

    return 0;
}
/******************************************************************************
* Function Name   : COMMAND_InvokeDisplayTariffAll
* Interface       : static void COMMAND_InvokeDisplayTariffAll(uint8_t *arg_str)
* Description     : Command Invoke Display all tariff
* Arguments       : uint8_t * arg_str: Arguments string
* Function Calls  : None
* Return Value    : None
******************************************************************************/
static uint8_t COMMAND_InvokeDisplayTariffAll(uint8_t *arg_str)
{
    static const uint8_t param_format_tariff_tz[] = "| %- 28s TZ(%1d) | %# 15.3f | %- 15s|\n\r";
    static const uint8_t line_break_tz[] = "+---------------------------------------------------------------------+";
    r_tariff_counter_t counter_tariff;
    r_tariff_counter_t counter_tariff_number;
    uint8_t tariff_number = 0;

    CMD_SendString((uint8_t *)"\n\r");
    R_TARIFF_GetTotalEnergyCounter(&counter_tariff);
    counter_tariff.active_imp /= 1000.0f;
    counter_tariff.active_exp /= 1000.0f;
    counter_tariff.reactive_cap_imp /= 1000.0f;
    counter_tariff.reactive_cap_exp /= 1000.0f;
    counter_tariff.reactive_ind_imp /= 1000.0f;
    counter_tariff.reactive_ind_exp /= 1000.0f;
    counter_tariff.apparent_imp /= 1000.0f;
    counter_tariff.apparent_exp /= 1000.0f;
	
    CMD_SendString((uint8_t *)line_break_tz);
	CMD_SendString((uint8_t *)"\n\r");
    CMD_Printf(
        (uint8_t *)param_format_tariff_tz,
        "Import Active Energy",
		0,
        counter_tariff.active_imp,
        "kWh"
    );
    CMD_Printf(
        (uint8_t *)param_format_tariff_tz,
        "Import Reactive Energy (C)",
		0,
        counter_tariff.reactive_cap_imp,
        "kVArh"
    );
    CMD_Printf(
        (uint8_t *)param_format_tariff_tz,
        "Import Reactive Energy (L)",
		0,
        counter_tariff.reactive_ind_imp,
        "kVArh"
    );
    CMD_Printf(
        (uint8_t *)param_format_tariff_tz,
        "Import Apparent Energy",
		0,
        counter_tariff.apparent_imp,
        "kVAh"
    );
    CMD_Printf(
        (uint8_t *)param_format_tariff_tz,
        "Export Active Energy",
		0,
        counter_tariff.active_exp,
        "kWh"
    );
    CMD_Printf(
        (uint8_t *)param_format_tariff_tz,
        "Export Reactive Energy (C)",
		0,
        counter_tariff.reactive_cap_exp,
        "kVArh"
    );
    CMD_Printf(
        (uint8_t *)param_format_tariff_tz,
        "Export Reactive Energy (L)",
		0,
        counter_tariff.reactive_ind_exp,
        "kVArh"
    );
    CMD_Printf(
        (uint8_t *)param_format_tariff_tz,
        "Export Apparent Energy",
		0,
        counter_tariff.apparent_exp,
        "kVAh"
    );
    
    for (tariff_number = 0; tariff_number < SCHEDULER_NUMBER_OF_TARIFF_TIMESLOT_MAX; tariff_number++)
    {
        R_TARIFF_GetImportActiveEnergyTariff(tariff_number, &counter_tariff_number.active_imp);
        R_TARIFF_GetExportActiveEnergyTariff(tariff_number, &counter_tariff_number.active_exp);
        R_TARIFF_GetImportCapacitiveReactiveEnergyTariff(tariff_number, &counter_tariff_number.reactive_cap_imp);
        R_TARIFF_GetExportCapacitiveReactiveEnergyTariff(tariff_number, &counter_tariff_number.reactive_cap_exp);
        R_TARIFF_GetImportInductiveReactiveEnergyTariff(tariff_number, &counter_tariff_number.reactive_ind_imp);
        R_TARIFF_GetExportInductiveReactiveEnergyTariff(tariff_number, &counter_tariff_number.reactive_ind_exp);
        R_TARIFF_GetImportApparentEnergyTariff(tariff_number, &counter_tariff_number.apparent_imp);
        R_TARIFF_GetExportApparentEnergyTariff(tariff_number, &counter_tariff_number.apparent_exp);
		
        /* Print out information */
        CMD_SendString((uint8_t *)line_break_tz);
		CMD_SendString((uint8_t *)"\n\r");
        CMD_Printf(
            (uint8_t *)param_format_tariff_tz,
            "Import Active Energy",
            tariff_number + 1,
            counter_tariff_number.active_imp,
            "kWh"
        );
        CMD_Printf(
            (uint8_t *)param_format_tariff_tz,
            "Import Reactive Energy (C)",
            tariff_number + 1,
            counter_tariff_number.reactive_cap_imp,
            "kVArh"
        );
        CMD_Printf(
            (uint8_t *)param_format_tariff_tz,
            "Import Reactive Energy (L)",
            tariff_number + 1,
            counter_tariff_number.reactive_ind_imp,
            "kVArh"
        );
        CMD_Printf(
            (uint8_t *)param_format_tariff_tz,
            "Import Apparent Energy",
            tariff_number + 1,
            counter_tariff_number.apparent_imp,
            "kVAh"
        );
        CMD_Printf(
            (uint8_t *)param_format_tariff_tz,
            "Export Active Energy",
            tariff_number + 1,
            counter_tariff_number.active_exp,
            "kWh"
        );
        CMD_Printf(
            (uint8_t *)param_format_tariff_tz,
            "Export Reactive Energy (C)",
            tariff_number + 1,
            counter_tariff_number.reactive_cap_exp,
            "kVArh"
        );
        CMD_Printf(
            (uint8_t *)param_format_tariff_tz,
            "Export Reactive Energy (L)",
            tariff_number + 1,
            counter_tariff_number.reactive_ind_exp,
            "kVArh"
        );
        CMD_Printf(
            (uint8_t *)param_format_tariff_tz,
            "Export Apparent Energy",
            tariff_number + 1,
            counter_tariff_number.apparent_exp,
            "kVAh"
        );
    }
    CMD_SendString((uint8_t *)line_break_tz);
	CMD_SendString((uint8_t *)"\n\r");
    return 0;
}

/******************************************************************************
* Function Name   : COMMAND_InvokeDisplayTariffStorageAll
* Interface       : static void COMMAND_InvokeDisplayTariffStorageAll(uint8_t *arg_str)
* Description     : Command Invoke Display all tariff
* Arguments       : uint8_t * arg_str: Arguments string
* Function Calls  : None
* Return Value    : None
******************************************************************************/
static uint8_t COMMAND_InvokeDisplayTariffStorageAll(uint8_t *arg_str)
{
    //r_tariff_counter_t counter_tariff;
    //r_tariff_counter_t tariff_config;
    //uint16_t tariff_number;
//
    //
    //tariff_config = R_TARIFF_GetConfig();
    //for (tariff_number = 0; tariff_number < tariff_config.number_tariff; tariff_number++)
    //{
    //    R_TARIFF_Storage_GetTariffCounter(tariff_number, &counter_tariff);
    //    counter_tariff.active_imp /= 1000.0f;
    //    counter_tariff.active_exp /= 1000.0f;
    //    counter_tariff.reactive_cap_imp /= 1000.0f;
    //    counter_tariff.reactive_cap_exp /= 1000.0f;
    //    counter_tariff.reactive_ind_imp /= 1000.0f;
    //    counter_tariff.reactive_ind_exp /= 1000.0f;
    //    counter_tariff.apparent_imp /= 1000.0f;
    //    counter_tariff.apparent_exp /= 1000.0f;
//
    //    /* Print out information */
    //    CMD_SendString((uint8_t *)line_break);
//
    //    CMD_Printf(
    //        (uint8_t *)param_format_tariff,
    //        "Import Active Energy",
    //        tariff_number,
    //        counter_tariff.active_imp,
    //        "kWh"
    //    );
    //    CMD_Printf(
    //        (uint8_t *)param_format_tariff,
    //        "Import Reactive Energy (C)",
    //        tariff_number,
    //        counter_tariff.reactive_cap_imp,
    //        "kVArh"
    //    );
    //    CMD_Printf(
    //        (uint8_t *)param_format_tariff,
    //        "Import Reactive Energy (L)",
    //        tariff_number,
    //        counter_tariff.reactive_ind_imp,
    //        "kVArh"
    //    );
    //    CMD_Printf(
    //        (uint8_t *)param_format_tariff,
    //        "Import Apparent Energy",
    //        tariff_number,
    //        counter_tariff.apparent_imp,
    //        "kVAh"
    //    );
//
    //    CMD_Printf(
    //        (uint8_t *)param_format_tariff,
    //        "Export Active Energy",
    //        tariff_number,
    //        counter_tariff.active_exp,
    //        "kWh"
    //    );
    //    CMD_Printf(
    //        (uint8_t *)param_format_tariff,
    //        "Export Reactive Energy (C)",
    //        tariff_number,
    //        counter_tariff.reactive_cap_exp,
    //        "kVArh"
    //    );
    //    CMD_Printf(
    //        (uint8_t *)param_format_tariff,
    //        "Export Reactive Energy (L)",
    //        tariff_number,
    //        counter_tariff.reactive_ind_exp,
    //        "kVArh"
    //    );
    //    CMD_Printf(
    //        (uint8_t *)param_format_tariff,
    //        "Export Apparent Energy",
    //        tariff_number,
    //        counter_tariff.apparent_exp,
    //        "kVAh"
    //    );
    //}
    //CMD_SendString((uint8_t *)line_break);
//
    return 0;
}
/******************************************************************************
* Function Name   : COMMAND_InvokeResetTariff
* Interface       : static void COMMAND_InvokeResetTariff(uint8_t *arg_str)
* Description     : Command Invoke Reset all tariff
* Arguments       : uint8_t * arg_str: Arguments string
* Function Calls  : None
* Return Value    : None
******************************************************************************/
static uint8_t COMMAND_InvokeResetTariff(uint8_t *arg_str)
{
    uint8_t buffer[20];             /* Data buffer to store input arguments */
    uint8_t confirm;

    CMD_Printf((uint8_t *)"\n\r");

   /* Get period (in seconds) parameter */
    if (arg_str != NULL) {
        arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" ");
        if (arg_str != NULL) {
            /* get period in seconds */
            confirm = (uint8_t)atoi((char *)buffer);

            if (confirm != 1) {
                CMD_Printf((uint8_t *)"Confirm code not equal to 1, no action done\n\r");
                return 1;
            }

            CMD_Printf((uint8_t *)"Reset tariff all... ");
            R_TARIFF_Format();
            CMD_Printf((uint8_t *)"OK\n\r");
        }
        else {
            CMD_Printf((uint8_t *)"Parameter error\n\r");
            return 1;
        }
    }
    else 
    {
        CMD_Printf((uint8_t *)"No parameter received, please input 1 to confirm reset of max demand \n\r");
    }

    return 0;
}
/******************************************************************************
* Function Name   : COMMAND_InvokeTariffConfiguration
* Interface       : static void COMMAND_InvokeTariffConfiguration(uint8_t *arg_str)
* Description     : Command Invoke GetSet Tariff configuration
* Arguments       : uint8_t * arg_str: Arguments string
* Function Calls  : None
* Return Value    : None
******************************************************************************/
static uint8_t COMMAND_InvokeTariffConfiguration(uint8_t *arg_str)
{
//    static const uint8_t params_tariff_config[] = "%-8d | %-2d: %-14d | %-13d | \n\r";
//    /* Data buffer to store input arguments */
//    uint8_t buffer[20];             
//    r_tariff_t tariff_config;
//    ENERGY_TIME_SLOT temp_timeslot;
//    ENERGY_RET result;
//    uint16_t i;

//    CMD_Printf((uint8_t *)"\n\r");

//    memset(&tariff_config, 0, sizeof(ENERGY_TARIFF_CONFIG));

//    /* Get parameter set */
//    if (arg_str != NULL)
//    {
//        while (arg_str != NULL && tariff_config.number_timeslot < METER_ENERGY_NUMBER_OF_TIMESLOT_MAX) {
//            /* Hour */
//            arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)":");
//            if (arg_str != NULL) {
//                /* get timeslot start hour */
//                temp_timeslot.timestart.hour = (uint32_t)EM_atol(buffer);
//                if (temp_timeslot.timestart.hour > 23) {
//                    CMD_Printf((uint8_t *)"Parameter error: hour within 0-23 only \n\r");
//                }
//            }
//            else {
//                CMD_Printf((uint8_t *)"Parameter error: current parsed timeslot: %d\n\r", tariff_config.number_timeslot);
//                return 1;
//            }
//            /* Min */
//            arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)":", (uint8_t *)"/");
//            if (arg_str != NULL) {
//                /* get timeslot start minute */
//                temp_timeslot.timestart.minute = (uint32_t)EM_atol(buffer);
//                if (temp_timeslot.timestart.minute > 59) {
//                    CMD_Printf((uint8_t *)"Parameter error: hour within 0-59 only \n\r");
//                }
//            }
//            else {
//                CMD_Printf((uint8_t *)"Parameter error: current parsed timeslot: %d\n\r", tariff_config.number_timeslot);
//                return 1;
//            }
//            /* Tariff number */
//            arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)"/", (uint8_t *)" ");
//            if (arg_str != NULL) {
//                /* get timeslot start minute */
//                temp_timeslot.tariffno = (uint32_t)EM_atol(buffer);
//            }
//            else {
//                CMD_Printf((uint8_t *)"Parameter error: current parsed timeslot: %d\n\r", tariff_config.number_timeslot);
//                return 1;
//            }

//            /* Copy the time slot into timeslot configuration */
//            tariff_config.timeslot_list[tariff_config.number_timeslot] = temp_timeslot;
//            /* Increase number of timeslot */
//            tariff_config.number_timeslot++;

//            /* Calculate number of tariff, it's the max number of tariff set */
//            if (tariff_config.number_tariff < (temp_timeslot.tariffno + 1)) {
//                tariff_config.number_tariff = (temp_timeslot.tariffno + 1);
//            }
//        }

//        /* Checking parameter */
//        CMD_Printf((uint8_t *)"Validating tariff configuration ... ");
//        result = R_TARIFF_ValidateConfig(&tariff_config);
//        if (result != ENERGY_RET_OK) {
//            CMD_Printf((uint8_t *)"FAILED\n\r");
//            return 1;
//        }
//        else {
//            CMD_Printf((uint8_t *)"OK\n\r");
//        }

//        CMD_Printf((uint8_t *)"Setting tariff configuration ... ");
//        if (R_TARIFF_SetPassiveConfig(&tariff_config) != ENERGY_RET_OK) {
//            CMD_Printf((uint8_t *)"FAILED\n\r");
//            return 1;
//        }
//        else {
//            CMD_Printf((uint8_t *)"OK\n\r");
//        }

//        /* Raise request to apply configuration */
//        R_TARIFF_RequestActivatePassiveConfig();

//        return 0;
//    }

//    /* Read the parameter */
//    tariff_config = R_TARIFF_GetConfig();

//    CMD_Printf((uint8_t *)"Number of tariff   : %d \n\r", tariff_config.number_tariff);
//    CMD_Printf((uint8_t *)"Number of timeslot : %d \n\r", tariff_config.number_timeslot);
//    CMD_Printf((uint8_t *)"Timeslot | Start time (HH:MM) | Tariff number |\n\r");
//    for (i = 0; i < tariff_config.number_timeslot; i++)
//    {
//        CMD_Printf((uint8_t *)params_tariff_config, 
//            i,
//            tariff_config.timeslot_list[i].timestart.hour,
//            tariff_config.timeslot_list[i].timestart.minute,
//            tariff_config.timeslot_list[i].tariffno
//        );
//    }

    return 0;
}
/******************************************************************************
* Function Name   : COMMAND_InvokeReadTamperLog
* Interface       : static void COMMAND_InvokeReadTamperLog(uint8_t *arg_str)
* Description     : Command Invoke to read the tamper log at index
* Arguments       : uint8_t * arg_str: Arguments string
* Function Calls  : None
* Return Value    : None
******************************************************************************/
static uint8_t COMMAND_InvokeReadTamperLog(uint8_t *arg_str)
{
    #if 0
    /* Disable this command until upgrading the meter energy and tamper log */
    uint8_t buffer[20];             /* Data buffer to store input arguments */                
    uint8_t index;
    ONE_TAMPER_DATA_LOG tamper_log;
    uint32_t address;
    
    /* Get line parameter */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" "); 
    if (arg_str != NULL)
    {   
        /* get number */
        index = (uint8_t)atoi((char *)buffer);
        
        if ((index >= 200))
        {
            CMD_SendString((uint8_t *)"\n\rParameter error\n\r");
            return 1;
        }
        
    }
    else
    {
        CMD_SendString((uint8_t *)"\n\rParameter error\n\r");
        return 1;
    }
    
    /* Read tamper log from EEPROM */
    address = STORAGE_EEPROM_TAMPER_DATA_LOG_ADDR;
    address += sizeof(ONE_TAMPER_DATA_LOG) * (uint32_t)index;
    
    EPR_Read(address, (uint8_t *)&tamper_log, sizeof(ONE_TAMPER_DATA_LOG));
    
    /* Display data */
    CMD_Printf((uint8_t *)"\n\rTamper log index: %u\n\r", index);
    CMD_Printf((uint8_t *)"RTC Time: %02x/%02x/20%02x %02x:%02x:%02x %02x\n\r",
                tamper_log.tamper_rtc_time.Day      ,
                tamper_log.tamper_rtc_time.Month    ,
                tamper_log.tamper_rtc_time.Year     ,
                tamper_log.tamper_rtc_time.Hour     ,
                tamper_log.tamper_rtc_time.Min      ,
                tamper_log.tamper_rtc_time.Sec      ,
                tamper_log.tamper_rtc_time.Week) ;
                
    CMD_SendString((uint8_t *)"Tamper list: \n\r");
    CMD_Printf((uint8_t *)"  %20s: %u\n\r", "Earth connected", tamper_log.tamper_type.earth_connected);
    CMD_Printf((uint8_t *)"  %20s: %u\n\r", "Neutral missing", tamper_log.tamper_type.neutral_missing);
    CMD_Printf((uint8_t *)"  %20s: %u\n\r", "Case open", tamper_log.tamper_type.case_open);
    CMD_Printf((uint8_t *)"  %20s: %u\n\r", "Magnet", tamper_log.tamper_type.magnet);
    CMD_Printf((uint8_t *)"  %20s: %u\n\r", "Power failed", tamper_log.tamper_type.power_failure);
    #endif
    
    return 0;
}

//extern STORAGE_EEPROM_HEADER g_storage_header;

/******************************************************************************
* Function Name   : COMMAND_InvokeGetCurrentTamperLogIndex
* Interface       : static void COMMAND_InvokeGetCurrentTamperLogIndex(uint8_t *arg_str)
* Description     : Command Invoke to read the tamper log index
* Arguments       : uint8_t * arg_str: Arguments string
* Function Calls  : None
* Return Value    : None
******************************************************************************/
static uint8_t COMMAND_InvokeGetCurrentTamperLogIndex(uint8_t *arg_str)
{
    //uint16_t index;
    //
    //index = g_storage_header.cur_tamper_log_index;
    //
    //CMD_Printf((uint8_t *)"\n\rCurrent tamper log index: %u\n\r", index);
    
    return 0;
}
/******************************************************************************
* Function Name   : COMMAND_InvokeClearEmEnergyCounter
* Interface       : static void COMMAND_InvokeClearEmEnergyCounter(uint8_t *arg_str)
* Description     : Command
* Arguments       : uint8_t * arg_str: Arguments string
* Function Calls  : None
* Return Value    : None
******************************************************************************/
static uint8_t COMMAND_InvokeClearEmEnergyCounter(uint8_t *arg_str)
{
   EM_OPERATION_DATA energy_data;

   /* Clear energy counter in storage */
   CMD_Printf((uint8_t *)"\n\r");
   CMD_Printf((uint8_t *)"Clear energy counter in storage (eeprom) \n\r");
   STORAGE_EM_Format();

   CMD_Printf((uint8_t *)"Load formatted data in EEPROM to RAM \n\r");
   STORAGE_EM_Restore();

   CMD_Printf((uint8_t *)"DONE\n\r");
    
   return 0;
}


/******************************************************************************
* Function Name   : COMMAND_InvokeGetBankStatusInfo
* Interface       : static void COMMAND_InvokeGetBankStatusInfo(uint8_t *arg_str)
* Description     : Command Invoke to read the tamper log index
* Arguments       : uint8_t * arg_str: Arguments string
* Function Calls  : None
* Return Value    : None
******************************************************************************/
typedef struct tagDeviceSignature
{
    uint8_t device_name[11];
    uint32_t code_flash_size;
    uint32_t data_flash_size;
} device_signature_t;

/***********************************************************************************************************************
 * Function Name: get_device_signature
 * Description  : NA
 * Arguments    : device_signature_t * p_signature
 * Return Value : None
 **********************************************************************************************************************/
//static device_signature_t get_device_signature(void)
//{
    //device_signature_t signature;

//    /* Signature layout in ROM, reference:
//    * Application note: r01an3701ej0100_rl78
//    * User manual: FLASH chapter, table Signature Data List
//    */
//    /* First 10 byte, device name, manually finalize string with 0 on 11th byte */
//    BL_memcpy_nf(&signature.device_name[0], (const void FAR_PTR *)0xEFFD5, 10);
//    signature.device_name[10] = 0;
//    /* Next 3 byte: code flash final address, +1 become size */
//    signature.code_flash_size = 0;
//    BL_memcpy_nf(&signature.code_flash_size, (const void FAR_PTR *)0xEFFDF, 3);
//    signature.code_flash_size +=1;
//    /* Next 3 byte: data flash final address, +1 become size */
//    signature.data_flash_size = 0;
//    BL_memcpy_nf(&signature.data_flash_size, (const void FAR_PTR *)0xEFFE2, 3);
//    signature.data_flash_size +=1;
//    /* Dataflash starting from 0xF1000 */
//    signature.data_flash_size -= 0xF1000;
    
    //return signature;
//}

//static uint8_t check_device_support_bankswap(void)
//{
//    device_signature_t device_signature;
//    uint8_t is_applicable_device;

//    device_signature = get_device_signature();

//    /* Check for RL78I1C 512k device (possible solution to avoid using specific feature of certain MCU) */
//    if (device_signature.device_name[4] == '0' && 
//        //[5] 'N' I1C
//        device_signature.device_name[5] == 'N' && 
//        //[6] pin count (any)
//        //[7] ROM size
//        device_signature.device_name[7] == 'L' &&
//        (1))
//    {
//        is_applicable_device = 1;
//    }
//    else
//    {
//        is_applicable_device = 0;
//    }

//    return is_applicable_device;
//}

//static void print_device_information(void)
//{
//    device_signature_t device_signature;
//    uint8_t temp[4];

//    device_signature = get_device_signature();

//    CMD_Printf((uint8_t *)"Device name: %s\n\r", device_signature.device_name);
//    CMD_Printf((uint8_t *)"Bankswap support: %s\n\r", check_device_support_bankswap() == 1 ? "YES" : "NO");
//    CMD_Printf((uint8_t *)"Code flash size: 0x%08lx (%lu) bytes \n\r", 
//                            device_signature.code_flash_size, device_signature.code_flash_size);
//    CMD_Printf((uint8_t *)"Code flash size: 0x%08lx (%lu) bytes \n\r", 
//                            device_signature.data_flash_size, device_signature.data_flash_size);
//}

static void print_image_header(void)
{
//    bl_image_header_t image_header;

//    BL_IMAGE_GetHeaderInfo(&image_header, BL_IMAGE_CURRENT_BANK);

//    CMD_Printf((uint8_t *)"Platform name: %s\n\r", image_header.identifier);
//    CMD_Printf((uint8_t *)"Software version: v%d.%d.%d\n\r", 
//                                image_header.software_version[2], 
//                                image_header.software_version[1],
//                                image_header.software_version[0]);
//    CMD_Printf((uint8_t *)"User program size: dec: %lu, hex: 0x%05lx (bytes)\n\r", image_header.user_app_size, image_header.user_app_size);
//    CMD_Printf((uint8_t *)"User program hash: 0x%02hx \n\r", image_header.user_app_hash);
//    CMD_Printf((uint8_t *)"User program transfer time (dd/MM/yyyy hh:mm:ss wd): %02d/%02d/%04d %02d:%02d:%02d %02d\n\r", 
//                                image_header.transfer_time.day,
//                                image_header.transfer_time.mon,
//                                image_header.transfer_time.yr,
//                                image_header.transfer_time.hr,
//                                image_header.transfer_time.min,
//                                image_header.transfer_time.sec,
//                                image_header.transfer_time.wk
//                                );
//    CMD_Printf((uint8_t *)"User program activate time (dd/MM/yyyy hh:mm:ss wd): %02d/%02d/%04d %02d:%02d:%02d %02d\n\r", 
//                                image_header.activate_time.day,
//                                image_header.activate_time.mon,
//                                image_header.activate_time.yr,
//                                image_header.activate_time.hr,
//                                image_header.activate_time.min,
//                                image_header.activate_time.sec,
//                                image_header.activate_time.wk
//                                );
}

/******************************************************************************
* Function Name   : COMMAND_InvokeGetBankStatusInfo
* Interface       : static void COMMAND_InvokeGetBankStatusInfo(uint8_t *arg_str)
* Description     : Command Invoke to bank status info
* Arguments       : uint8_t * arg_str: Arguments string
* Function Calls  : None
* Return Value    : None
******************************************************************************/
static uint8_t COMMAND_InvokeGetBankStatusInfo(uint8_t *arg_str)
{
//    uint8_t boot_flag;
//    uint16_t j;
//    uint8_t status = 0;
    
//    CMD_Printf("\n\r");
    
//    CMD_PrintfWithColor(PRINT_COLOR_VT100_YELLOW, (uint8_t *)"Reading device information (embedded in reserved FLASH) \n\r");
//    print_device_information();

//    CMD_PrintfWithColor(PRINT_COLOR_VT100_YELLOW, (uint8_t *)"Reading image header at address 0x%05lx \n\r", USER_APP_START_ADDRESS);
//    print_image_header();
    
//    if (check_device_support_bankswap() == 0)
//    {
//        CMD_Printf((uint8_t *)"This command used for device support bankswap only\n\r");
//        return 1;
//    }

//    CMD_PrintfWithColor(PRINT_COLOR_VT100_YELLOW, (uint8_t *)"Reading self-programming flash\n\r");
//    {
//        uint8_t version[25];
//        BL_memcpy_nf(version, FSL_GetVersionString(), 24);
//        version[24] = 0;
//        CMD_Printf((uint8_t *)"FSL Library version: %s \n\r", &version[0]);
//    }

//    BL_FLASH_GetBootFlag(&boot_flag);
//    CMD_Printf((uint8_t *)"Boot flag: %d\n\r", boot_flag);

    return 0;

}

/******************************************************************************
* Function Name   : COMMAND_InvokeBankSwap
* Interface       : static void COMMAND_InvokeBankSwap(uint8_t *arg_str)
* Description     : Command Invoke to read the tamper log index
* Arguments       : uint8_t * arg_str: Arguments string
* Function Calls  : None
* Return Value    : None
******************************************************************************/
static uint8_t COMMAND_InvokeBankSwap(uint8_t *arg_str)
{
//    CMD_Printf((uint8_t *)"\n\r");


//    /* Backup energy data first, non-stop will not affect, but also backup for safety */
//    CMD_Printf((uint8_t *)"Backup energy data first ... ");
//    {
//        EM_ENERGY_DATA energy_data;
//        EM_GetEnergyCounter(&energy_data);
//        STORAGE_EM_SetEnergyData(&energy_data);
//    }
//    CMD_Printf((uint8_t *)"DONE \n\r");

//    CMD_Printf((uint8_t *)"Executing bank swap on the fly then branch back to user app entry \n\r");
    
//    {
//        bl_image_header_t image_header;
//        BL_IMAGE_GetHeaderInfo(&image_header, BL_IMAGE_CURRENT_BANK);
//        BL_IncreaseSoftwareVersion(&image_header.software_version[0]);
//        BL_IMAGE_SetSoftwareVersion(&image_header.software_version[0]);
//    }

//    /* Non-stop metrology firmware upgrade */
//    EM_RunOnRam_NonStopBankSwap();

    return 0;
}

/******************************************************************************
* Function Name   : COMMAND_InvokeInvertBootFlagAndReset
* Interface       : static void COMMAND_InvokeInvertBootFlagAndReset(uint8_t *arg_str)
* Description     : Command Invoke to read the tamper log index
* Arguments       : uint8_t * arg_str: Arguments string
* Function Calls  : None
* Return Value    : None
******************************************************************************/
static uint8_t COMMAND_InvokeInvertBootFlagAndReset(uint8_t *arg_str)
{
//    CMD_Printf((uint8_t *)"\n\r");


//    /* Backup energy data first, non-stop will not affect, but also backup for safety */
//    CMD_Printf((uint8_t *)"Backup energy data first ... ");
//    {
//        EM_ENERGY_DATA energy_data;
//        EM_GetEnergyCounter(&energy_data);
//        STORAGE_EM_SetEnergyData(&energy_data);
//    }
//    CMD_Printf((uint8_t *)"DONE \n\r");

//    CMD_Printf((uint8_t *)"Executing invert boot flag then reset \n\r");
//    {
//        bl_image_header_t image_header;
//        BL_IMAGE_GetHeaderInfo(&image_header, BL_IMAGE_CURRENT_BANK);
//        BL_IncreaseSoftwareVersion(&image_header.software_version[0]);
//        BL_IMAGE_SetSoftwareVersion(&image_header.software_version[0]);
//    }
//    {
//        BL_FLASH_Prepare();
//        DI();
//        FSL_InvertBootFlag();
//        BL_FLASH_CleanUp();
//        FSL_ForceReset();
//    }

    return 0;
}

/******************************************************************************
* Function Name    : static uint8_t COMMAND_InvokeDisplay(uint8_t *arg_str)
* Description      : Command Invoke Display
* Arguments        : uint8_t index: Command index
*                  : uint8_t *arg_str: Arguments string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
******************************************************************************/
#ifdef EM_FFT_ENABLE
static uint8_t COMMAND_InvokeFFT(uint8_t *arg_str)
{
    uint8_t buffer[40];
    uint8_t fft_command = 0;
    uint16_t j = 0;
    
    /* Get command parameter */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" /");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        /* get number */
        fft_command = (uint8_t)atoi((char *)buffer);
    }
    else
    {
        CMD_Printf((uint8_t *)"\n\r Command = 0: Help");
    	CMD_Printf((uint8_t *)"\n\r Command = 1: Harmonic");
    	CMD_Printf((uint8_t *)"\n\r Command = 2: Dump buffer");
    	CMD_Printf((uint8_t *)"\n\r Command = 3: Block fft process");
    	CMD_Printf((uint8_t *)"\n\r Command = 4: Unblock fft process");
        return 1;
    }
    if(fft_command == 0)
    {
    	CMD_Printf((uint8_t *)"\n\r Command = 0: Help");
    	CMD_Printf((uint8_t *)"\n\r Command = 1: Harmonic");
    	CMD_Printf((uint8_t *)"\n\r Command = 2: Dump buffer");
    	CMD_Printf((uint8_t *)"\n\r Command = 3: Block fft process");
    	CMD_Printf((uint8_t *)"\n\r Command = 4: Unblock fft process");
    }
    if(fft_command == 1)
    {
        CMD_Printf((uint8_t *)"\n\rHarmonic:");
        CMD_Printf((uint8_t *)"\n\rR_V Y_V B_Y R_I Y_I B_I");
        
        for( j = 0 ; j < EM_FFT_MAX_HARMONIC ; j++ )
        {
            CMD_Printf((uint8_t *)"\n\r%3d %3d %3d %3d %3d %3d",
            em_fft_harmonic.phase_r.v[j],
            em_fft_harmonic.phase_y.v[j],
            em_fft_harmonic.phase_b.v[j],
            em_fft_harmonic.phase_r.i[j],
            em_fft_harmonic.phase_y.i[j],
            em_fft_harmonic.phase_b.i[j]
            );
        }
    }
    if(fft_command == 2)
    {
    	for( j = 0 ; j < FFT_POINTS ; j++ )
    	{
    		CMD_Printf((uint8_t *)"\n\r%d" , em_fft_buffer[j]);
    	}
    }
    if(fft_command == 3)
    {
    	CMD_Printf((uint8_t *)"\n\rFFT process was blocked!");
    	em_fft_dump_buffer = 0;
    }
    if((fft_command > 4) && (fft_command < 10)) /* For six channel */
    {
    	CMD_Printf((uint8_t *)"\n\rFFT process was unblocked!");
    	em_fft_dump_buffer = fft_command;
    }
    return 0;
}
#endif /* EM_FFT_ENABLE */

/******************************************************************************
* Function Name   : COMMAND_InvokeDisplayInstantaneous
* Interface       : static void COMMAND_InvokeDisplayInstantaneous(uint8_t *arg_str)
* Description     : Command Invoke to read instantaneous snapshot
* Arguments       : uint8_t * arg_str: Arguments string
* Function Calls  : None
* Return Value    : None
******************************************************************************/
static uint8_t COMMAND_InvokeDisplayInstantaneous(uint8_t *arg_str)
{
    CMD_Printf((uint8_t *)"\n\r");
    CMD_SendString((uint8_t *)line_break);
    CMD_Printf((uint8_t *)"| %- 32s | %- 15s | %- 15s | %- 15s | %- 15s | %- 15s | %- 15s|\n\r", "Parameter", "Phase R", "Phase Y", "Phase B", "Neutral", "Total", "Unit");
    CMD_SendString((uint8_t *)line_break);

    CMD_Printf(
            (uint8_t *)param_format,
            "vrms",
            g_inst_read_params.vrms[LINE_PHASE_R],
            g_inst_read_params.vrms[LINE_PHASE_Y],
            g_inst_read_params.vrms[LINE_PHASE_B],
            0.0f,
            g_inst_read_params.vrms[LINE_TOTAL],
            "Volt "
        );
    CMD_Printf(
            (uint8_t *)param_format,
            "irms",
            g_inst_read_params.irms[LINE_PHASE_R],
            g_inst_read_params.irms[LINE_PHASE_Y],
            g_inst_read_params.irms[LINE_PHASE_B],
            g_inst_read_params.irms[LINE_NEUTRAL],
            g_inst_read_params.irms[LINE_TOTAL],
            "Ampere "
        );
    CMD_Printf(
            (uint8_t *)param_format,
            "power_factor",
            g_inst_read_params.power_factor[LINE_PHASE_R],
            g_inst_read_params.power_factor[LINE_PHASE_Y],
            g_inst_read_params.power_factor[LINE_PHASE_B],
            0.0f,
            g_inst_read_params.power_factor[LINE_TOTAL],
            " "
        );
    CMD_Printf(
            (uint8_t *)param_format_s,
            "power_factor_sign",
            COMMAND_GetPowerFactorSignName(g_inst_read_params.power_factor_sign[LINE_PHASE_R]),
            COMMAND_GetPowerFactorSignName(g_inst_read_params.power_factor_sign[LINE_PHASE_Y]),
            COMMAND_GetPowerFactorSignName(g_inst_read_params.power_factor_sign[LINE_PHASE_B]),
            " ",
            COMMAND_GetPowerFactorSignName(g_inst_read_params.power_factor_sign[LINE_TOTAL]),
            " "
        );
		
    CMD_Printf(
            (uint8_t *)param_format,
            "Line Frequency",
            g_inst_read_params.freq[LINE_PHASE_R],
            g_inst_read_params.freq[LINE_PHASE_Y],
            g_inst_read_params.freq[LINE_PHASE_B],
            g_inst_read_params.freq[LINE_NEUTRAL],
            g_inst_read_params.freq[LINE_TOTAL] ,
            "Hz"
        );
    CMD_Printf(
            (uint8_t *)param_format,
            "active_power",
            g_inst_read_params.active_power[LINE_PHASE_R],
            g_inst_read_params.active_power[LINE_PHASE_Y],
            g_inst_read_params.active_power[LINE_PHASE_B],
            0.0f,
            g_inst_read_params.active_power[LINE_TOTAL],
            "Watt"
        );
    CMD_Printf(
            (uint8_t *)param_format,
            "reactive_power",
            g_inst_read_params.reactive_power[LINE_PHASE_R],
            g_inst_read_params.reactive_power[LINE_PHASE_Y],
            g_inst_read_params.reactive_power[LINE_PHASE_B],
            0.0f,
            g_inst_read_params.reactive_power[LINE_TOTAL],
            "VAr"
        );
    CMD_Printf(
            (uint8_t *)param_format,
            "apparent_power",
            g_inst_read_params.apparent_power[LINE_PHASE_R],
            g_inst_read_params.apparent_power[LINE_PHASE_Y],
            g_inst_read_params.apparent_power[LINE_PHASE_B],
            0.0f,
            g_inst_read_params.apparent_power[LINE_TOTAL],
            "VA"
        );
    CMD_Printf(
            (uint8_t *)param_format, 
            "Filtered Voltage RMS",
            g_inst_read_params.fundamental_vrms[LINE_PHASE_R],
            g_inst_read_params.fundamental_vrms[LINE_PHASE_Y],
            g_inst_read_params.fundamental_vrms[LINE_PHASE_B],
            0.0f,
            g_inst_read_params.fundamental_vrms[LINE_TOTAL],
            "Volt"
    );
    
    CMD_Printf(
            (uint8_t *)param_format, 
            "Filtered Current RMS",
            g_inst_read_params.fundamental_irms[LINE_PHASE_R],
            g_inst_read_params.fundamental_irms[LINE_PHASE_Y],
            g_inst_read_params.fundamental_irms[LINE_PHASE_B],
            0.0f,
            g_inst_read_params.fundamental_irms[LINE_TOTAL],
            "Ampere"
    );
    
    CMD_Printf(
            (uint8_t *)param_format, 
            "Fund Active Power",
            g_inst_read_params.fundamental_power[LINE_PHASE_R],
            g_inst_read_params.fundamental_power[LINE_PHASE_Y],
            g_inst_read_params.fundamental_power[LINE_PHASE_B],
            0.0f,
            g_inst_read_params.active_power[LINE_TOTAL],
            "Watt"
    );
    
    CMD_Printf(
            (uint8_t *)param_format, 
            "Voltage THD",
            g_inst_read_params.voltage_thd[LINE_PHASE_R],
            g_inst_read_params.voltage_thd[LINE_PHASE_Y],
            g_inst_read_params.voltage_thd[LINE_PHASE_B],
            0.0f,
            g_inst_read_params.voltage_thd[LINE_TOTAL],
            "Percent"
    );
    
    CMD_Printf(
            (uint8_t *)param_format, 
            "Current THD",
            g_inst_read_params.current_thd[LINE_PHASE_R],
            g_inst_read_params.current_thd[LINE_PHASE_Y],
            g_inst_read_params.current_thd[LINE_PHASE_B],
            0.0f,
            g_inst_read_params.current_thd[LINE_TOTAL],
            "Percent"
    );
    
    CMD_Printf(
            (uint8_t *)param_format, 
            "Active Power THD",
            g_inst_read_params.power_thd[LINE_PHASE_R],
            g_inst_read_params.power_thd[LINE_PHASE_Y],
            g_inst_read_params.power_thd[LINE_PHASE_B],
            0.0f,
            g_inst_read_params.power_thd[LINE_TOTAL],
            "Percent"
    );
    CMD_Printf(
            (uint8_t *)param_format,
            "active_energy_total_import",
            0.0f,
            0.0f,
            0.0f,
            0.0f,
            g_inst_read_params.active_energy_total_import,
            "kWh"
        );
    CMD_Printf(
            (uint8_t *)param_format,
            "active_energy_total_export",
            0.0f,
            0.0f,
            0.0f,
            0.0f,
            g_inst_read_params.active_energy_total_export,
            "kWh"
        );
    CMD_Printf(
            (uint8_t *)param_format,
            "reactive_energy_lag_total_import",
            0.0f,
            0.0f,
            0.0f,
            0.0f,
            g_inst_read_params.reactive_energy_lag_total_import,
            "kVArh"
        );
    CMD_Printf(
            (uint8_t *)param_format,
            "reactive_energy_lag_total_export",
            0.0f,
            0.0f,
            0.0f,
            0.0f,
            g_inst_read_params.reactive_energy_lag_total_export,
            "kVArh "
        );
    CMD_Printf(
            (uint8_t *)param_format,
            "reactive_energy_lead_total_import",
            0.0f,
            0.0f,
            0.0f,
            0.0f,
            g_inst_read_params.reactive_energy_lead_total_import,
            "kVArh "
        );
    CMD_Printf(
            (uint8_t *)param_format,
            "reactive_energy_lead_total_export",
            0.0f,
            0.0f,
            0.0f,
            0.0f,
            g_inst_read_params.reactive_energy_lead_total_export,
            "kVArh "
        );
    CMD_Printf(
            (uint8_t *)param_format,
            "apparent_energy_total_import",
            0.0f,
            0.0f,
            0.0f,
            0.0f,
            g_inst_read_params.apparent_energy_total_import,
            "kVArh "
        );
    CMD_Printf(
            (uint8_t *)param_format,
            "apparent_energy_total_export",
            0.0f,
            0.0f,
            0.0f,
            0.0f,
            g_inst_read_params.apparent_energy_total_export,
            "kVArh"
        );
        CMD_SendString((uint8_t *)line_break);
    return 0;
}

/***********************************************************************************************************************
* Function Name    : static uint8_t ConvertDateTimeFromClient(uint8_t *arg_str)
* Description      : Command Invoke Set RTC
* Arguments        : uint8_t index: Command index
*                  : uint8_t *arg_str: Arguments string
* Functions Called : None
* Return Value     : uint8_t, execution code, 0 is success
***********************************************************************************************************************/
static uint8_t ConvertDateTimeFromClient(uint8_t *arg_str, rtc_counter_value_t * p_rtctime)
{   
    //uint16_t timeout;
    uint8_t status;
    uint8_t buffer[20];

    
    /* Get Day parameter */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" /");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        /* get number */
        p_rtctime->day = (uint8_t)atoi((char *)buffer);
    }
    else
    {
        return 0;
    }
    
    /* Get Month parameter */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" /", (uint8_t *)" /");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        /* get number */
        p_rtctime->month = (uint8_t)atoi((char *)buffer);
    }
    else
    {
        return 0;
    }
    
    /* Get Year parameter */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" /", (uint8_t *)" ");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        /* get number */
        p_rtctime->year = (uint8_t)atoi((char *)buffer);
    }
    else
    {
        return 0;
    }
    
    /* Get Hour parameter */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" :");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        /* get number */
        p_rtctime->hour = (uint8_t)atoi((char *)buffer);
    }
    else
    {
        return 0;
    }

    /* Get Min parameter */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" :", (uint8_t *)" :");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        /* get number */
        p_rtctime->min = (uint8_t)atoi((char *)buffer);
    }
    else
    {
        return 0;
    }
    
    /* Get Sec parameter */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" :", (uint8_t *)" ");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        /* get number */
        p_rtctime->sec = (uint8_t)atoi((char *)buffer);
    }
    else
    {
        return 0;
    }
    
    /* Get Week parameter */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" ");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        /* get number */
        p_rtctime->week = (uint8_t)atoi((char *)buffer);
    }
    else
    {
        return 0;
    }
    
    return 1;
}

/******************************************************************************
* Function Name : COMMAND_InvokeAddSchedule
* Interface     : uint8_t COMMAND_InvokeAddSchedule(uint8_t *arg_str)
* Description   : 
* Arguments     : rtc_counter_value_t *p_rtcvalue: RTC value from snapshot (BCD format)
* Return Value  : None
******************************************************************************/
static uint8_t  COMMAND_InvokeClearSchedule(uint8_t *arg_str)
{
    uint8_t status;
    uint8_t buffer[20];
    rtc_counter_value_t rtctime;
    uint8_t schedule_id;
    uint8_t exec_id;
    /* convert Schedule ID */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" /");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        /* get number */
        schedule_id = (uint8_t)atoi((char *)buffer);
        if(schedule_id > MAX_SCHEDULER_NUMBER)
        {
            CMD_SendString((uint8_t *)"Scheudle ID out scope\n\r");
            return 1;
        }
    }
    else
    {
        CMD_SendString((uint8_t *)"Parameter error\n\r");
        return 1;
    }

    g_scheduler[schedule_id].number_of_exe_time = 0;

    CMD_SendString((uint8_t *)"\n\rClear sucessfully\n\r");

    return 0;
}
/******************************************************************************
* Function Name : COMMAND_InvokeAddSchedule
* Interface     : uint8_t COMMAND_InvokeAddSchedule(uint8_t *arg_str)
* Description   : 
* Arguments     : rtc_counter_value_t *p_rtcvalue: RTC value from snapshot (BCD format)
* Return Value  : None
******************************************************************************/
static uint8_t  COMMAND_InvokeAddSchedule(uint8_t *arg_str)
{
    uint8_t status;
    uint8_t buffer[20];
    rtc_counter_value_t rtctime;
    uint8_t schedule_id;
    uint8_t exec_id;
    /* convert Schedule ID */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" /");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        /* get number */
        schedule_id = (uint8_t)atoi((char *)buffer);
        if(schedule_id > MAX_SCHEDULER_NUMBER)
        {
            CMD_SendString((uint8_t *)"Scheudle ID out scope\n\r");
            return 1;
        }
    }
    else
    {
        CMD_SendString((uint8_t *)"Parameter error\n\r");
        return 1;
    }

    
    if (ConvertDateTimeFromClient(arg_str, &rtctime) == 0)
    {   
        CMD_SendString((uint8_t *)"Parameter error\n\r");
        return 1;
    }
    else
    {

    }
    if (g_scheduler[schedule_id].number_of_exe_time >= scheduler_exe_time_maximum_support[schedule_id])
    {
        g_scheduler[schedule_id].number_of_exe_time = 0;
    }
    exec_id = g_scheduler[schedule_id].number_of_exe_time;
    g_scheduler[schedule_id].p_execution_time[exec_id].Day = rtctime.day;
    g_scheduler[schedule_id].p_execution_time[exec_id].Month = rtctime.month;
    g_scheduler[schedule_id].p_execution_time[exec_id].Year = rtctime.year;
    g_scheduler[schedule_id].p_execution_time[exec_id].Hour = rtctime.hour;
    g_scheduler[schedule_id].p_execution_time[exec_id].Min = rtctime.min;
    g_scheduler[schedule_id].p_execution_time[exec_id].Sec = rtctime.sec;
    g_scheduler[schedule_id].p_execution_time[exec_id].Week = rtctime.week;
    /* Increase number of */
    g_scheduler[schedule_id].number_of_exe_time++;

    R_SCHEDULER_BackupByID(schedule_id);

    CMD_SendString((uint8_t *)"\n\rSet sucessfully\n\r");

    return 0;
}
/******************************************************************************
* Function Name : COMMAND_InvokeEditSchedule
* Interface     : uint8_t COMMAND_InvokeEditSchedule(uint8_t *arg_str)
* Description   : 
* Arguments     : rtc_counter_value_t *p_rtcvalue: RTC value from snapshot (BCD format)
* Return Value  : None
******************************************************************************/
static uint8_t  COMMAND_InvokeEditSchedule(uint8_t *arg_str)
{
    uint8_t status;
    uint8_t buffer[20];
    rtc_counter_value_t rtctime;
    uint8_t schedule_id;
    uint8_t exec_id;

    /* convert Schedule ID */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" /");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        /* get number */
        schedule_id = (uint8_t)atoi((char *)buffer);
        if(schedule_id > MAX_SCHEDULER_NUMBER)
        {
            CMD_SendString((uint8_t *)"Scheudle ID out scope\n\r");
            return 1;
        }
    }
    else
    {
        CMD_SendString((uint8_t *)"Parameter error\n\r");
        return 1;
    }

    /* convert exe time ID */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" /");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        /* get number */
        exec_id = (uint8_t)atoi((char *)buffer);
        if (exec_id >= scheduler_exe_time_maximum_support[schedule_id])
        {
            CMD_SendString((uint8_t *)"Execution time ID out scope\n\r");
            return 1;
        }
    }
    else
    {
        CMD_SendString((uint8_t *)"Parameter error\n\r");
        return 1;
    }

    
    if (ConvertDateTimeFromClient(arg_str, &rtctime) == 0)
    {   
        CMD_SendString((uint8_t *)"Parameter error\n\r");
        return 1;
    }
    else
    {

    }

    g_scheduler[schedule_id].p_execution_time[exec_id].Day = rtctime.day;
    g_scheduler[schedule_id].p_execution_time[exec_id].Month = rtctime.month;
    g_scheduler[schedule_id].p_execution_time[exec_id].Year = rtctime.year;
    g_scheduler[schedule_id].p_execution_time[exec_id].Hour = rtctime.hour;
    g_scheduler[schedule_id].p_execution_time[exec_id].Min = rtctime.min;
    g_scheduler[schedule_id].p_execution_time[exec_id].Sec = rtctime.sec;
    g_scheduler[schedule_id].p_execution_time[exec_id].Week = rtctime.week;

    R_SCHEDULER_BackupByID(schedule_id);

    CMD_SendString((uint8_t *)"\n\rSet sucessfully\n\r");
    return 0;
}

const uint8_t *const g_sched_name[] =
{
    "Schedule for Tariff",
    "Schedule for Periodic channel 0",
    "Schedule for Periodic channel 1",
    "Schedule for Billing",
    "Schedule for Firmware activation",
    "Schedule for Activity calendar - Activation Passive Profile",
    "Schedule for Activity calendar - Season Changed",
};

/******************************************************************************
* Function Name : COMMAND_InvokeDisplayScheduleConfig
* Interface     : uint8_t COMMAND_InvokeDisplayScheduleConfig(uint8_t *arg_str)
* Description   : 
* Arguments     : rtc_counter_value_t *p_rtcvalue: RTC value from snapshot (BCD format)
* Return Value  : None
******************************************************************************/
static uint8_t  COMMAND_InvokeDisplayScheduleConfig(uint8_t *arg_str)
{

    uint8_t i, j;
    CMD_Printf((uint8_t *)"\n\r");
    /* Turn 'matched' bit to TRUE if hit schedule */
    for (i = 0; i < MAX_SCHEDULER_NUMBER; i++)
    {   
        CMD_Printf((uint8_t *)"\n\r");
        CMD_Printf((uint8_t *) line_break);
        CMD_Printf(
                (uint8_t *)param_format_d,
                "Schedule[index,is matched] ",
                i,
                g_scheduler[i].matched,
                g_sched_name[i]
        );

        for (j = 0; j < g_scheduler[i].number_of_exe_time; j++)
        {
            CMD_Printf((uint8_t *)"\n\r   Date time at %02d: %02d/%02d/%02d %02d:%02d:%02d %02d",
                j,
                g_scheduler[i].p_execution_time[j].Day,
                g_scheduler[i].p_execution_time[j].Month,
                g_scheduler[i].p_execution_time[j].Year,
                g_scheduler[i].p_execution_time[j].Hour,
                g_scheduler[i].p_execution_time[j].Min,
                g_scheduler[i].p_execution_time[j].Sec,
                g_scheduler[i].p_execution_time[j].Week
            );
        }
    }

    CMD_Printf((uint8_t *) line_break);
    CMD_Printf((uint8_t *)"END.\n\r");

    return 0;
}
/******************************************************************************
* Function Name : COMMAND_InvokeScheduleBackup
* Interface     : uint8_t COMMAND_InvokeScheduleBackup(uint8_t *arg_str)
* Description   : 
* Arguments     : rtc_counter_value_t *p_rtcvalue: RTC value from snapshot (BCD format)
* Return Value  : None
******************************************************************************/
static uint8_t  COMMAND_InvokeScheduleBackup(uint8_t *arg_str)
{
    uint8_t i, j;

    /* Turn 'matched' bit to TRUE if hit schedule */
    for (i = 0; i < MAX_SCHEDULER_NUMBER; i++)
    {
        if(R_SCHEDULER_BackupByID(i) == 0)
        {
 
        }
        else
        {
                CMD_Printf(
                (uint8_t *)param_format_d,
                "Backup failed at schedule id: ",
                i,
                " ");
                return 1;
        }
        
    }
    CMD_SendString((uint8_t *)"\n\r Backup sucessfully\n\r");
    return 0;
}
/******************************************************************************
* Function Name : COMMAND_InvokeScheduleRestore
* Interface     : uint8_t COMMAND_InvokeScheduleRestore(uint8_t *arg_str)
* Description   : 
* Arguments     : rtc_counter_value_t *p_rtcvalue: RTC value from snapshot (BCD format)
* Return Value  : None
******************************************************************************/
static uint8_t  COMMAND_InvokeScheduleRestore(uint8_t *arg_str)
{
    uint8_t i, j;

    /* Turn 'matched' bit to TRUE if hit schedule */
    for (i = 0; i < MAX_SCHEDULER_NUMBER; i++)
    {
        if(R_SCHEDULER_Restore() == 0)
        {
 
        }
        else
        {
                CMD_Printf(
                "Restore fail");
                return 1;
        }
        
    }
    CMD_SendString((uint8_t *)"\n\r Restore sucessfully\n\r");
    return 0;
}
/******************************************************************************
* Function Name : COMMAND_InvokeEventTrigger
* Interface     : uint8_t COMMAND_InvokeEventTrigger(uint8_t *arg_str)
* Description   : 
* Arguments     : rtc_counter_value_t *p_rtcvalue: RTC value from snapshot (BCD format)
* Return Value  : None
******************************************************************************/
static uint8_t  COMMAND_InvokeEventGet(uint8_t *arg_str)
{
    uint8_t buffer[20];
    uint8_t event_type;
    uint32_t entries_in_use = 0;
    /* convert exe time ID */
    EVENT_PARAMS_T   event_parameters;
    uint16_t i;

    /* convert Schedule ID */
    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" /");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        /* get number */
        event_type = (uint8_t)atoi((char *)buffer);
    }
    else
    {
        CMD_SendString((uint8_t *)"Parameter error\n\r");
        return 1;
    }

    CMD_SendString((uint8_t *)"\r\n------------------------------\n\r");
    R_EVENT_EntriesInUseGet((EVENT_TYPE_T)event_type, &entries_in_use);
    if(entries_in_use == 0)
    {
        CMD_SendString((uint8_t *)"No event captured \n\r");
    }
    for(i = 0; i < entries_in_use; i++)
    {
        /* Get event record from event application */
        event_parameters = R_EVENT_GetEntry((EVENT_TYPE_T)event_type, i);
        CMD_Printf((uint8_t *)"|Index: %02d | event code: %02d |\n\r",
                    i,
                    event_parameters.code);
    }
    return 0;
}
/******************************************************************************
* Function Name : COMMAND_InvokeClearEventLog
* Interface     : uint8_t COMMAND_InvokeClearEventLog(uint8_t *arg_str)
* Description   : 
* Arguments     : rtc_counter_value_t *p_rtcvalue: RTC value from snapshot (BCD format)
* Return Value  : None
******************************************************************************/
static uint8_t COMMAND_InvokeClearEventLog(uint8_t *arg_str)
{
    uint32_t    eeprom_addr;
    uint8_t     empty_page[STORAGE_EEPROM_PAGESIZE];
    uint16_t    size;
    uint8_t     i;

    /* Create empty_page */
    memset(empty_page, 0, sizeof(empty_page));

    /* Clear Whole EEPROM */
    eeprom_addr = STORAGE_EEPROM_EVENT_LOG_HEADER_CODE_ADDR;
    while (eeprom_addr < STORAGE_EEPROM_EVENT_LOG_LAST_ADDR)
    {
        if ((STORAGE_EEPROM_EVENT_LOG_LAST_ADDR - eeprom_addr) < STORAGE_EEPROM_PAGESIZE) {
            size = STORAGE_EEPROM_EVENT_LOG_LAST_ADDR - eeprom_addr;
        }
        else {
            size = STORAGE_EEPROM_PAGESIZE;
        }

        if (EPR_Write(eeprom_addr, empty_page, size) != EPR_OK)
        {
            return STORAGE_ERROR;
        }

        eeprom_addr += size;

        R_WDT_Restart();
    }

    for (i = 0; i < (uint8_t)LAST_EVENT_TYPE ; i++)
    {
        R_EVENT_ResetLog((EVENT_TYPE_T)i);
    }

    EVENT_StorageRestore();
    /* Formatted */
    return 0;
}
/******************************************************************************
* Function Name   : COMMAND_InvokeDisplayDailyLoad
* Interface       : static void COMMAND_InvokeDisplayDailyLoad(uint8_t *arg_str)
* Description     : 
* Arguments       : uint8_t * arg_str: Arguments string
* Function Calls  : None
* Return Value    : None
******************************************************************************/
static uint8_t COMMAND_InvokeDisplayDailyLoad(uint8_t *arg_str)
{       
    r_daily_load_t daily_load_storage;
    uint32_t dailyload_entry_in_use;
    uint8_t get_result;
    uint8_t buffer[20];

    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" /");
    
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        /* get number */
        dailyload_entry_in_use = (uint8_t)atoi((char *)buffer);
    }
    else
    {
        CMD_SendString((uint8_t *)"Parameter error\n\r");
        return 1;
    }
    CMD_SendString((uint8_t *)"\r\n------------------------------\n\r");

    //memset(&daily_load_storage, 0, sizeof(r_daily_load_t));
    get_result = R_DAILYLOAD_GetEntryByIndex(dailyload_entry_in_use, &daily_load_storage);

    if (get_result)
	{

	}
	else
	{   
        CMD_SendString((uint8_t *)"No entry data\n\r");
		return FALSE;
	}

    CMD_SendString((uint8_t *)"\n\r");
    CMD_SendString((uint8_t *)line_break);
    CMD_Printf((uint8_t *)"Daily load entry  %03u\n\r",dailyload_entry_in_use);
    CMD_SendString((uint8_t *)"Daily load storge \n\r");
    CMD_Printf((uint8_t *)"%02d/%02d/20%02d %02d:%02d:%02d %02d\n\r",
                daily_load_storage.CaptureTime.day,
                daily_load_storage.CaptureTime.month,
                daily_load_storage.CaptureTime.year,
                daily_load_storage.CaptureTime.hour,
                daily_load_storage.CaptureTime.min,
                daily_load_storage.CaptureTime.sec,
                daily_load_storage.CaptureTime.week);
    CMD_Printf((uint8_t *)"Import Active Energy        = %16.3f\n\r", daily_load_storage.EnergykWhImport);
    CMD_Printf((uint8_t *)"Import Apparent Energy        = %16.3f\n\r", daily_load_storage.EnergykVAhImport);
    CMD_Printf((uint8_t *)"Export Active Energy       = %16.3f\n\r", daily_load_storage.EnergykWhExport);
    CMD_Printf((uint8_t *)"Export Apparent Energy    = %16.3f\n\r", daily_load_storage.EnergykVAhExport);
    CMD_SendString((uint8_t *)line_break);
    return 0;
}



/******************************************************************************
* Function Name   : COMMAND_InvokeActCalendarDisplay
* Interface       : static void COMMAND_InvokeActCalendarDisplay(uint8_t *arg_str)
* Description     : 
* Arguments       : uint8_t * arg_str: Arguments string
* Function Calls  : None
* Return Value    : None
******************************************************************************/
static uint8_t COMMAND_InvokeActCalendarDisplay(uint8_t *arg_str)
{
    print_activity_calendar();

    return 0;
}

/******************************************************************************
* Function Name   : COMMAND_InvokeCopPassiveProfileToActive
* Interface       : static void COMMAND_InvokeCopPassiveProfileToActive(uint8_t *arg_str)
* Description     : 
* Arguments       : uint8_t * arg_str: Arguments string
* Function Calls  : None
* Return Value    : None
******************************************************************************/
static uint8_t COMMAND_InvokeCopPassiveProfileToActive(uint8_t *arg_str)
{
    CMD_Printf("\n\rCopy activity calendar passive profile to active profile....");
    R_ACT_CAL_RequestCopyPassiveToActive();
    CMD_Printf("OK\n\r");

    return 0;
}

/******************************************************************************
* Function Name   : COMMAND_InvokeActCalendarEdit
* Interface       : static void COMMAND_InvokeActCalendarEdit(uint8_t *arg_str)
* Description     : 
* Arguments       : uint8_t * arg_str: Arguments string
* Function Calls  : None
* Return Value    : None
******************************************************************************/
static uint8_t COMMAND_InvokeActCalendarEdit(uint8_t *arg_str)
{
    uint16_t u16_value;
    uint16_t i,j;

    uint8_t temp_buff[64];
    uint16_t len;

    uint8_t buffer[20];

    uint8_t *p_argstr;

    uint8_t set_id;

    uint8_t attribute_edit = 1;

    uint8_t set_result = FALSE;


    uint16_t u16_len;


    arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" /");
    if (arg_str != NULL &&
        (buffer[0] >= '0' && buffer[0] <= '9'))
    {   
        /* get number */
        attribute_edit = (uint8_t)atoi((char *)buffer);
    }
    else
    {
        CMD_SendString((uint8_t *)"Parameter error\n\r");
        return 1;
    }

    CMD_SendString((uint8_t *)"\n\r"); 
    CMD_SendString((uint8_t *)"\n\r --- Follow instruction below to set Passive Calendar profile --- ");
    CMD_SendString((uint8_t *)"\n\r --- Leave empty, press enter to ignore changes --- ");	

    switch (attribute_edit)
    {
        case 1:
        case 2:
        case 3:
        case 4:
            CMD_SendString((uint8_t *)"\n\rActive Profile is read-only!");
            return 0;

        case 5:
            {
            	r_act_cal_name_t calendar_name;
            	calendar_name.len = 0;
            	memset(&calendar_name.value, 0 ,NAME_LENGTH_MAX);
                CMD_SendString((uint8_t *)"\n\r5. Season name (Passive) > \n\r");
                input_ascii_string((uint8_t *)" - Name : > ", (uint8_t *)calendar_name.value, &u16_len);
                calendar_name.len = (uint8_t)u16_len;
                if (u16_len <= NAME_LENGTH_MAX)
                {
                    set_result = R_ACT_CAL_Backup_CalendarName_Passive(&calendar_name);
                }
                else
                {
                    CMD_Printf((uint8_t *)"\n\r [Error] Length should smaller than %d", NAME_LENGTH_MAX);
                }
            }

            break;
        case 6:
            /*  6. Season Profile (Passive)
                Num of entry : 				<user input>	enter/.
                Name : 						<user input>	enter/.
                Start Time : 				<user input>	enter/.
                Week :						<user input>	enter/.
                */
                {
                    r_act_cal_season_profile_t  season_profile;
                    season_profile = R_ACT_CAL_Restore_SeasonProfile(TRUE);

                    CMD_SendString((uint8_t *)"\n\r 5. Season Profile (Passive)\n\r");
                    input_interger((uint8_t *)"\n\r - Num of entry ([0 -> 2]) > ", &u16_len);
                    season_profile.num = (uint8_t)u16_len;

                    if (season_profile.num <= SEASON_PROFILE_ELEMENT_MAX)
                    {
                        for (i = 0; i<season_profile.num; i++)
                        {
                            CMD_Printf((uint8_t *)"\n\r [Input Entry no %02d]\n\r", i);
                            input_ascii_string((uint8_t *)" - Name : > ", season_profile.entry[i].name.value, &u16_len);
                            season_profile.entry[i].name.len = u16_len;
                            input_ascii_string((uint8_t *)" - Start Time : > ", temp_buff, &len);
                            ConvertDateTimeFromClient(temp_buff, &season_profile.entry[i].start_time);
                            input_ascii_string((uint8_t *)" - Week : > ", season_profile.entry[i].week.value, &u16_len);
                            season_profile.entry[i].week.len = u16_len;
                        }
                        
                        set_result = R_ACT_CAL_Backup_SeasonProfile_Passive(&season_profile);
                    }
                }

             break;
        case 7:

                // 7. Week Profile (Passive)
                // Num of entry : 				<user input>	enter/.
                // Entry: 0
                // + Name : week_0 (len = 6)	<user input> week_0 	enter/.
                // + Data :					<user input>  00 00 00 00 00 00 00	enter/.

                {
                    r_act_cal_week_profile_t    week_profile;
                    week_profile = R_ACT_CAL_Restore_WeekProfile(TRUE);
                    CMD_SendString((uint8_t *)"\n\r 6. Week Profile (Passive)\n\r");
                    input_interger((uint8_t *)"\n\r - Num of entry (u16) > ", &u16_len);
                    week_profile.num = (uint8_t)u16_len;
                    if (week_profile.num <= WEEK_PROFILE_ELEMENT_MAX)
                    {
                        for (i = 0;i<week_profile.num;i++)
                        {
                            CMD_Printf((uint8_t *)"\n\r Input Entry %d\n\r", i);
                            input_ascii_string((uint8_t *)" - Name : > ", (uint8_t *)week_profile.entry[i].name.value, &u16_len);
                            week_profile.entry[i].name.len = (uint8_t)u16_len;
                            input_ascii_string((uint8_t *)" - Data : > ", temp_buff, &len);

                            p_argstr = temp_buff;
                            for (j = 0; j < 7; j++)
                            {
                                p_argstr = COMMAND_GetScanOneParam(buffer, 20, p_argstr, (uint8_t *)" ", (uint8_t *)" ");
                                week_profile.entry[i].data[j] = (uint8_t)atoi((void *)buffer);
                            }
                        }
                        set_result = R_ACT_CAL_Backup_WeekProfile_Passive(&week_profile);
                    }
                }

                break;
        case 8:

                /* 7. Day Profile (Passive)
                    Num of entry : 1			<user input>	enter/.
                    Entry: 0
                    ID : 00						<user input>	enter/.
                    |  Num of Action: 06
                    |  Action [00]: 00:00 , 1 (HH:MM, ScriptID)
                    |  Action [01]: 06:00 , 2 (HH:MM, ScriptID)
                    |  Action [02]: 12:00 , 3 (HH:MM, ScriptID)
                    |  Action [03]: 13:00 , 4 (HH:MM, ScriptID)
                    |  Action [04]: 18:00 , 5 (HH:MM, ScriptID)
                    |  Action [05]: 20:00 , 6 (HH:MM, ScriptID)
                */	
                {
                    r_act_cal_day_profile_t day_profile;
                    day_profile = R_ACT_CAL_Restore_DayProfile(TRUE);
                    CMD_SendString((uint8_t *)"\n\r 8. Day Profile (Passive)\n\r");
                    input_interger((uint8_t *)"\n\r - Num of profiles (u16) > ", &u16_len);
					day_profile.num = (uint8_t)u16_len;
                    if (day_profile.num <= DAY_PROFILE_ELEMENT_MAX)
                    {
                        for (i = 0;i<day_profile.num;i++)
                        {
                            CMD_Printf((uint8_t *)"\n\r Input Entry %d\n\r", i);
                            input_interger((uint8_t *)" - Num of action : > ", &u16_len);
							day_profile.entry[i].numberOfAction = (uint8_t)u16_len;

                            p_argstr = temp_buff;
                            for (j = 0; j < day_profile.entry[i].numberOfAction; j++)
                            {
                                CMD_Printf((uint8_t *)"\n\r Action [%2d] (HH:MM, ScriptID): ", j);
                                input_ascii_string((uint8_t *)"", temp_buff, &len);

                                p_argstr = COMMAND_GetScanOneParam(buffer, 20, p_argstr, (uint8_t *)" ", (uint8_t *)":");
                                day_profile.entry[i].action[j].hour = (uint8_t)atoi((void *)buffer);

                                p_argstr = COMMAND_GetScanOneParam(buffer, 20, p_argstr, (uint8_t *)" ", (uint8_t *)",");
                                day_profile.entry[i].action[j].min = (uint8_t)atoi((void *)buffer);

                                p_argstr = COMMAND_GetScanOneParam(buffer, 20, p_argstr, (uint8_t *)" ", (uint8_t *)" ");
                                day_profile.entry[i].action[j].scriptID = (uint8_t)atoi((void *)buffer);
                            }
                        }
                    }

                    set_result = R_ACT_CAL_Backup_DayProfile_Passive(&day_profile);
                }
            break;

        case 9:
            {
                rtc_counter_value_t schedule_time;
                CMD_SendString((uint8_t *)"\n\r 9. Activation passive profile time > ");
                input_ascii_string((uint8_t *)"", temp_buff, &len);

                if (ConvertDateTimeFromClient(temp_buff, &schedule_time) == 0)
                {   
                    CMD_SendString((uint8_t *)"Parameter error\n\r");
                    return 1;
                }
                else
                {  
                    set_result = R_ACT_CAL_Set_ActivateTime(&schedule_time);
                }
            }
            
            break;
    
        default:
            break;
    }

    if (set_result == TRUE)
    {
        CMD_SendString((uint8_t *)"\n\rSet successful!\n\r");
    }
    else
    {
        CMD_SendString((uint8_t *)"\n\rSet failed!\n\r");
    }
	
	return 0;
}

/******************************************************************************
* Function Name   : COMMAND_InvokeDisplayBilling
* Interface       : static void COMMAND_InvokeDisplayBilling(uint8_t *arg_str)
* Description     : 
* Arguments       : uint8_t * arg_str: Arguments string
* Function Calls  : None
* Return Value    : None
******************************************************************************/
static uint8_t COMMAND_InvokeDisplayBilling(uint8_t *arg_str)
{       
        uint32_t index;
        uint32_t billing_entry_in_use;
        r_billing_t billing_load_storage;
        uint8_t get_result;
        uint8_t buffer[20];

        arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" /");
    
        if (arg_str != NULL &&
            (buffer[0] >= '0' && buffer[0] <= '9'))
        {   
            /* get number */
            index = (uint8_t)atoi((char *)buffer);
        }
        else
        {
            CMD_SendString((uint8_t *)"Parameter error\n\r");
            return 1;
        }
        CMD_SendString((uint8_t *)"\r\n------------------------------\n\r");

        //memset(&billing_load_storage, 0, sizeof(r_billing_t));
        R_BILLING_GetEntryInUse(&billing_entry_in_use);
        if (index >= billing_entry_in_use)
        {
            get_result = R_BILLING_GetEntryByIndex(index, &billing_load_storage);
        }
        else
        {
            get_result = R_BILLING_Get_CurrentCycleBillingParameters(&billing_load_storage);
        }

        if (get_result)
	    {

	    }
	    else
	    {
            CMD_SendString((uint8_t *)"No entry data\n\r");
		    return FALSE;
	    }

        CMD_SendString((uint8_t *)"\n\r");
        CMD_SendString((uint8_t *)line_break);
        CMD_Printf((uint8_t *)"Billing counter %03u \n\r", g_billing_counter);
        CMD_Printf((uint8_t *)"Billing load entry %03u \n\r", index);
        CMD_SendString((uint8_t *)"Billing load storage \n\r");
        CMD_Printf((uint8_t *)"%02d/%02d/20%02d %02d:%02d:%02d %02d\n\r",
                    billing_load_storage.CaptureTime.day,
                    billing_load_storage.CaptureTime.month,
                    billing_load_storage.CaptureTime.year,
                    billing_load_storage.CaptureTime.hour,
                    billing_load_storage.CaptureTime.min,
                    billing_load_storage.CaptureTime.sec,
                    billing_load_storage.CaptureTime.week);

        CMD_Printf((uint8_t *)"AveragePowerFactor       = %16.3f\n\r", billing_load_storage.AveragePowerFactor);
        CMD_Printf((uint8_t *)"CumulativeEnergykWh       = %16.3f\n\r", billing_load_storage.CumulativeEnergykWh);
        CMD_Printf((uint8_t *)"CumulativeEnergykWh_TZ1   = %16.3f\n\r", billing_load_storage.CumulativeEnergykWh_TZ1);
        CMD_Printf((uint8_t *)"CumulativeEnergykWh_TZ2   = %16.3f\n\r", billing_load_storage.CumulativeEnergykWh_TZ2);
        CMD_Printf((uint8_t *)"CumulativeEnergykWh_TZ3   = %16.3f\n\r", billing_load_storage.CumulativeEnergykWh_TZ3);
        CMD_Printf((uint8_t *)"CumulativeEnergykWh_TZ4   = %16.3f\n\r", billing_load_storage.CumulativeEnergykWh_TZ4);
        CMD_Printf((uint8_t *)"CumulativeEnergykWh_TZ5   = %16.3f\n\r", billing_load_storage.CumulativeEnergykWh_TZ5);
        CMD_Printf((uint8_t *)"CumulativeEnergykWh_TZ6   = %16.3f\n\r", billing_load_storage.CumulativeEnergykWh_TZ6);
        CMD_Printf((uint8_t *)"CumulativeEnergykWh_TZ7   = %16.3f\n\r", billing_load_storage.CumulativeEnergykWh_TZ7);
        CMD_Printf((uint8_t *)"CumulativeEnergykWh_TZ8   = %16.3f\n\r", billing_load_storage.CumulativeEnergykWh_TZ8);

        CMD_Printf((uint8_t *)"CumulativeEnergykVAh       = %16.3f\n\r", billing_load_storage.CumulativeEnergykVAh);
        CMD_Printf((uint8_t *)"CumulativeEnergykVAh_TZ1   = %16.3f\n\r", billing_load_storage.CumulativeEnergykVAh_TZ1);
        CMD_Printf((uint8_t *)"CumulativeEnergykVAh_TZ2   = %16.3f\n\r", billing_load_storage.CumulativeEnergykVAh_TZ2);
        CMD_Printf((uint8_t *)"CumulativeEnergykVAh_TZ3   = %16.3f\n\r", billing_load_storage.CumulativeEnergykVAh_TZ3);
        CMD_Printf((uint8_t *)"CumulativeEnergykVAh_TZ4   = %16.3f\n\r", billing_load_storage.CumulativeEnergykVAh_TZ4);
        CMD_Printf((uint8_t *)"CumulativeEnergykVAh_TZ5   = %16.3f\n\r", billing_load_storage.CumulativeEnergykVAh_TZ5);
        CMD_Printf((uint8_t *)"CumulativeEnergykVAh_TZ6   = %16.3f\n\r", billing_load_storage.CumulativeEnergykVAh_TZ6);
        CMD_Printf((uint8_t *)"CumulativeEnergykVAh_TZ7   = %16.3f\n\r", billing_load_storage.CumulativeEnergykVAh_TZ7);
        CMD_Printf((uint8_t *)"CumulativeEnergykVAh_TZ8   = %16.3f\n\r", billing_load_storage.CumulativeEnergykVAh_TZ8);

        CMD_Printf((uint8_t *)"MDkW       = %16.3f\n\r", billing_load_storage.MDkW);
        CMD_Printf((uint8_t *)"MDkW_TZ1   = %16.3f\n\r", billing_load_storage.MDkW_TZ1);
        CMD_Printf((uint8_t *)"MDkW_TZ2   = %16.3f\n\r", billing_load_storage.MDkW_TZ2);
        CMD_Printf((uint8_t *)"MDkW_TZ3   = %16.3f\n\r", billing_load_storage.MDkW_TZ3);
        CMD_Printf((uint8_t *)"MDkW_TZ4   = %16.3f\n\r", billing_load_storage.MDkW_TZ4);
        CMD_Printf((uint8_t *)"MDkW_TZ5   = %16.3f\n\r", billing_load_storage.MDkW_TZ5);
        CMD_Printf((uint8_t *)"MDkW_TZ6   = %16.3f\n\r", billing_load_storage.MDkW_TZ6);
        CMD_Printf((uint8_t *)"MDkW_TZ7   = %16.3f\n\r", billing_load_storage.MDkW_TZ7);
        CMD_Printf((uint8_t *)"MDkW_TZ8   = %16.3f\n\r", billing_load_storage.MDkW_TZ8);
        CMD_SendString((uint8_t *)"MDkWDateTime \n\r");
        CMD_Printf((uint8_t *)"%02d/%02d/20%02d %02d:%02d:%02d %02d\n\r",
                    billing_load_storage.MDkWDateTime.day,
                    billing_load_storage.MDkWDateTime.month,
                    billing_load_storage.MDkWDateTime.year,
                    billing_load_storage.MDkWDateTime.hour,
                    billing_load_storage.MDkWDateTime.min,
                    billing_load_storage.MDkWDateTime.sec,
                    billing_load_storage.MDkWDateTime.week);
        CMD_SendString((uint8_t *)"MDkWDateTime_TZ1 \n\r");
        CMD_Printf((uint8_t *)"%02d/%02d/20%02d %02d:%02d:%02d %02d\n\r",
                    billing_load_storage.MDkWDateTime_TZ1.day,
                    billing_load_storage.MDkWDateTime_TZ1.month,
                    billing_load_storage.MDkWDateTime_TZ1.year,
                    billing_load_storage.MDkWDateTime_TZ1.hour,
                    billing_load_storage.MDkWDateTime_TZ1.min,
                    billing_load_storage.MDkWDateTime_TZ1.sec,
                    billing_load_storage.MDkWDateTime_TZ1.week);
        CMD_SendString((uint8_t *)"MDkWDateTime_TZ2 \n\r");
        CMD_Printf((uint8_t *)"%02d/%02d/20%02d %02d:%02d:%02d %02d\n\r",
                    billing_load_storage.MDkWDateTime_TZ2.day,
                    billing_load_storage.MDkWDateTime_TZ2.month,
                    billing_load_storage.MDkWDateTime_TZ2.year,
                    billing_load_storage.MDkWDateTime_TZ2.hour,
                    billing_load_storage.MDkWDateTime_TZ2.min,
                    billing_load_storage.MDkWDateTime_TZ2.sec,
                    billing_load_storage.MDkWDateTime_TZ2.week);
        CMD_SendString((uint8_t *)"MDkWDateTime_TZ3 \n\r");
        CMD_Printf((uint8_t *)"%02d/%02d/20%02d %02d:%02d:%02d %02d\n\r",
                    billing_load_storage.MDkWDateTime_TZ3.day,
                    billing_load_storage.MDkWDateTime_TZ3.month,
                    billing_load_storage.MDkWDateTime_TZ3.year,
                    billing_load_storage.MDkWDateTime_TZ3.hour,
                    billing_load_storage.MDkWDateTime_TZ3.min,
                    billing_load_storage.MDkWDateTime_TZ3.sec,
                    billing_load_storage.MDkWDateTime_TZ3.week);
                    CMD_SendString((uint8_t *)"MDkWDateTime_TZ4 \n\r");
        CMD_Printf((uint8_t *)"%02d/%02d/20%02d %02d:%02d:%02d %02d\n\r",
                    billing_load_storage.MDkWDateTime_TZ4.day,
                    billing_load_storage.MDkWDateTime_TZ4.month,
                    billing_load_storage.MDkWDateTime_TZ4.year,
                    billing_load_storage.MDkWDateTime_TZ4.hour,
                    billing_load_storage.MDkWDateTime_TZ4.min,
                    billing_load_storage.MDkWDateTime_TZ4.sec,
                    billing_load_storage.MDkWDateTime_TZ4.week);
                    CMD_SendString((uint8_t *)"MDkWDateTime_TZ5 \n\r");
        CMD_Printf((uint8_t *)"%02d/%02d/20%02d %02d:%02d:%02d %02d\n\r",
                    billing_load_storage.MDkWDateTime_TZ5.day,
                    billing_load_storage.MDkWDateTime_TZ5.month,
                    billing_load_storage.MDkWDateTime_TZ5.year,
                    billing_load_storage.MDkWDateTime_TZ5.hour,
                    billing_load_storage.MDkWDateTime_TZ5.min,
                    billing_load_storage.MDkWDateTime_TZ5.sec,
                    billing_load_storage.MDkWDateTime_TZ5.week);
                    CMD_SendString((uint8_t *)"MDkWDateTime_TZ6 \n\r");
        CMD_Printf((uint8_t *)"%02d/%02d/20%02d %02d:%02d:%02d %02d\n\r",
                    billing_load_storage.MDkWDateTime_TZ6.day,
                    billing_load_storage.MDkWDateTime_TZ6.month,
                    billing_load_storage.MDkWDateTime_TZ6.year,
                    billing_load_storage.MDkWDateTime_TZ6.hour,
                    billing_load_storage.MDkWDateTime_TZ6.min,
                    billing_load_storage.MDkWDateTime_TZ6.sec,
                    billing_load_storage.MDkWDateTime_TZ6.week);
        CMD_SendString((uint8_t *)"MDkWDateTime_TZ7 \n\r");
        CMD_Printf((uint8_t *)"%02d/%02d/20%02d %02d:%02d:%02d %02d\n\r",
                    billing_load_storage.MDkWDateTime_TZ7.day,
                    billing_load_storage.MDkWDateTime_TZ7.month,
                    billing_load_storage.MDkWDateTime_TZ7.year,
                    billing_load_storage.MDkWDateTime_TZ7.hour,
                    billing_load_storage.MDkWDateTime_TZ7.min,
                    billing_load_storage.MDkWDateTime_TZ7.sec,
                    billing_load_storage.MDkWDateTime_TZ7.week);
        CMD_SendString((uint8_t *)"MDkWDateTime_TZ8 \n\r");
        CMD_Printf((uint8_t *)"%02d/%02d/20%02d %02d:%02d:%02d %02d\n\r",
                    billing_load_storage.MDkWDateTime_TZ8.day,
                    billing_load_storage.MDkWDateTime_TZ8.month,
                    billing_load_storage.MDkWDateTime_TZ8.year,
                    billing_load_storage.MDkWDateTime_TZ8.hour,
                    billing_load_storage.MDkWDateTime_TZ8.min,
                    billing_load_storage.MDkWDateTime_TZ8.sec,
                    billing_load_storage.MDkWDateTime_TZ8.week);
        CMD_Printf((uint8_t *)"MDkVA       = %16.3f\n\r", billing_load_storage.MDkVA);
        CMD_Printf((uint8_t *)"MDkVA_TZ1   = %16.3f\n\r", billing_load_storage.MDkVA_TZ1);
        CMD_Printf((uint8_t *)"MDkVA_TZ2   = %16.3f\n\r", billing_load_storage.MDkVA_TZ2);
        CMD_Printf((uint8_t *)"MDkVA_TZ3   = %16.3f\n\r", billing_load_storage.MDkVA_TZ3);
        CMD_Printf((uint8_t *)"MDkVA_TZ4   = %16.3f\n\r", billing_load_storage.MDkVA_TZ4);
        CMD_Printf((uint8_t *)"MDkVA_TZ5   = %16.3f\n\r", billing_load_storage.MDkVA_TZ5);
        CMD_Printf((uint8_t *)"MDkVA_TZ6   = %16.3f\n\r", billing_load_storage.MDkVA_TZ6);
        CMD_Printf((uint8_t *)"MDkVA_TZ7   = %16.3f\n\r", billing_load_storage.MDkVA_TZ7);
        CMD_Printf((uint8_t *)"MDkVA_TZ8   = %16.3f\n\r", billing_load_storage.MDkVA_TZ8);
        CMD_SendString((uint8_t *)"MDkVADateTime \n\r");
        CMD_Printf((uint8_t *)"%02d/%02d/20%02d %02d:%02d:%02d %02d\n\r",
                    billing_load_storage.MDkVADateTime.day,
                    billing_load_storage.MDkVADateTime.month,
                    billing_load_storage.MDkVADateTime.year,
                    billing_load_storage.MDkVADateTime.hour,
                    billing_load_storage.MDkVADateTime.min,
                    billing_load_storage.MDkVADateTime.sec,
                    billing_load_storage.MDkVADateTime.week);
        CMD_SendString((uint8_t *)"MDkVADateTime_TZ1 \n\r");
        CMD_Printf((uint8_t *)"%02d/%02d/20%02d %02d:%02d:%02d %02d\n\r",
                    billing_load_storage.MDkVADateTime_TZ1.day,
                    billing_load_storage.MDkVADateTime_TZ1.month,
                    billing_load_storage.MDkVADateTime_TZ1.year,
                    billing_load_storage.MDkVADateTime_TZ1.hour,
                    billing_load_storage.MDkVADateTime_TZ1.min,
                    billing_load_storage.MDkVADateTime_TZ1.sec,
                    billing_load_storage.MDkVADateTime_TZ1.week);
        CMD_SendString((uint8_t *)"MDkVADateTime_TZ2 \n\r");
        CMD_Printf((uint8_t *)"%02d/%02d/20%02d %02d:%02d:%02d %02d\n\r",
                    billing_load_storage.MDkVADateTime_TZ2.day,
                    billing_load_storage.MDkVADateTime_TZ2.month,
                    billing_load_storage.MDkVADateTime_TZ2.year,
                    billing_load_storage.MDkVADateTime_TZ2.hour,
                    billing_load_storage.MDkVADateTime_TZ2.min,
                    billing_load_storage.MDkVADateTime_TZ2.sec,
                    billing_load_storage.MDkVADateTime_TZ2.week);
        CMD_SendString((uint8_t *)"MDkVADateTime_TZ3 \n\r");
        CMD_Printf((uint8_t *)"%02d/%02d/20%02d %02d:%02d:%02d %02d\n\r",
                    billing_load_storage.MDkVADateTime_TZ3.day,
                    billing_load_storage.MDkVADateTime_TZ3.month,
                    billing_load_storage.MDkVADateTime_TZ3.year,
                    billing_load_storage.MDkVADateTime_TZ3.hour,
                    billing_load_storage.MDkVADateTime_TZ3.min,
                    billing_load_storage.MDkVADateTime_TZ3.sec,
                    billing_load_storage.MDkVADateTime_TZ3.week);
                    CMD_SendString((uint8_t *)"MDkVADateTime_TZ4 \n\r");
        CMD_Printf((uint8_t *)"%02d/%02d/20%02d %02d:%02d:%02d %02d\n\r",
                    billing_load_storage.MDkVADateTime_TZ4.day,
                    billing_load_storage.MDkVADateTime_TZ4.month,
                    billing_load_storage.MDkVADateTime_TZ4.year,
                    billing_load_storage.MDkVADateTime_TZ4.hour,
                    billing_load_storage.MDkVADateTime_TZ4.min,
                    billing_load_storage.MDkVADateTime_TZ4.sec,
                    billing_load_storage.MDkVADateTime_TZ4.week);
                    CMD_SendString((uint8_t *)"MDkVADateTime_TZ5 \n\r");
        CMD_Printf((uint8_t *)"%02d/%02d/20%02d %02d:%02d:%02d %02d\n\r",
                    billing_load_storage.MDkVADateTime_TZ5.day,
                    billing_load_storage.MDkVADateTime_TZ5.month,
                    billing_load_storage.MDkVADateTime_TZ5.year,
                    billing_load_storage.MDkVADateTime_TZ5.hour,
                    billing_load_storage.MDkVADateTime_TZ5.min,
                    billing_load_storage.MDkVADateTime_TZ5.sec,
                    billing_load_storage.MDkVADateTime_TZ5.week);
                    CMD_SendString((uint8_t *)"MDkVADateTime_TZ6 \n\r");
        CMD_Printf((uint8_t *)"%02d/%02d/20%02d %02d:%02d:%02d %02d\n\r",
                    billing_load_storage.MDkVADateTime_TZ6.day,
                    billing_load_storage.MDkVADateTime_TZ6.month,
                    billing_load_storage.MDkVADateTime_TZ6.year,
                    billing_load_storage.MDkVADateTime_TZ6.hour,
                    billing_load_storage.MDkVADateTime_TZ6.min,
                    billing_load_storage.MDkVADateTime_TZ6.sec,
                    billing_load_storage.MDkVADateTime_TZ6.week);
        CMD_SendString((uint8_t *)"MDkVADateTime_TZ7 \n\r");
        CMD_Printf((uint8_t *)"%02d/%02d/20%02d %02d:%02d:%02d %02d\n\r",
                    billing_load_storage.MDkVADateTime_TZ7.day,
                    billing_load_storage.MDkVADateTime_TZ7.month,
                    billing_load_storage.MDkVADateTime_TZ7.year,
                    billing_load_storage.MDkVADateTime_TZ7.hour,
                    billing_load_storage.MDkVADateTime_TZ7.min,
                    billing_load_storage.MDkVADateTime_TZ7.sec,
                    billing_load_storage.MDkVADateTime_TZ7.week);
        CMD_SendString((uint8_t *)"MDkVADateTime_TZ8 \n\r");
        CMD_Printf((uint8_t *)"%02d/%02d/20%02d %02d:%02d:%02d %02d\n\r",
                    billing_load_storage.MDkVADateTime_TZ8.day,
                    billing_load_storage.MDkVADateTime_TZ8.month,
                    billing_load_storage.MDkVADateTime_TZ8.year,
                    billing_load_storage.MDkVADateTime_TZ8.hour,
                    billing_load_storage.MDkVADateTime_TZ8.min,
                    billing_load_storage.MDkVADateTime_TZ8.sec,
                    billing_load_storage.MDkVADateTime_TZ8.week);
        CMD_Printf((uint8_t *)"PowerONduration   = %16.3d\n\r", billing_load_storage.PowerONduration);
        CMD_Printf((uint8_t *)"CumulativeEnergykWh_Export       = %16.3f\n\r", billing_load_storage.CumulativeEnergykWh_Export);
        CMD_Printf((uint8_t *)"CumulativeEnergykVAh_Export        = %16.3f\n\r", billing_load_storage.CumulativeEnergykVAh_Export);
        CMD_Printf((uint8_t *)"CumulativeEnergykVArh_QI       = %16.3f\n\r", billing_load_storage.CumulativeEnergykVArh_QI);
        CMD_Printf((uint8_t *)"CumulativeEnergykVArh_QII    = %16.3f\n\r", billing_load_storage.CumulativeEnergykVArh_QII);
        CMD_Printf((uint8_t *)"CumulativeEnergykVArh_QIII      = %16.3f\n\r", billing_load_storage.CumulativeEnergykVArh_QIII);
        CMD_Printf((uint8_t *)"CumulativeEnergykVArh_QIV   = %16.3f\n\r", billing_load_storage.CumulativeEnergykVArh_QIV);
        CMD_SendString((uint8_t *)line_break);
        return 0;
}

/******************************************************************************
* Function Name : COMMAND_InvokeGetService
* Interface     : uint8_t COMMAND_InvokeGetService(uint8_t *arg_str)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
static uint8_t COMMAND_InvokeGetService(uint8_t *arg_str)
{
    uint8_t buffer[20];             /* Data buffer to store input arguments */
    uint32_t input_value;
    
    uint32_t service_type = 0x03;
    uint32_t service_params;
    uint32_t value;

    CMD_Printf((uint8_t *)"\n\r");

    /* Get value parameter */
    if (arg_str != NULL) {
        arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" ");
        if (arg_str != NULL) {
            service_params = (uint8_t)atoi((void *)buffer);
        }
        else {
            CMD_Printf((uint8_t *)"Parameter error\n\r");
            return 1;
        }

    }

    R_DEBUG_CommandServiceGet(service_type, service_params, &value);

    return 0;
}

/******************************************************************************
* Function Name : COMMAND_InvokeSetService
* Interface     : uint8_t COMMAND_InvokeSetService(uint8_t *arg_str)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
static uint8_t COMMAND_InvokeSetService(uint8_t *arg_str)
{
    uint8_t buffer[20];             /* Data buffer to store input arguments */
    uint32_t input_value;
    
    uint32_t service_object_id;
    uint32_t service_params;
    uint32_t value;

    uint32_t u32value = 0.0f;

    uint8_t input_valid;

    CMD_Printf((uint8_t *)"\n\r");

    /* Get value parameter */
    if (arg_str != NULL) {
        arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" ");
        if (arg_str != NULL) {
            service_object_id = (uint8_t)atoi((void *)buffer);
        }
        else {
            CMD_Printf((uint8_t *)"Parameter error\n\r");
            return 1;
        }
        
        if (service_object_id != 0x00)
        {
            arg_str = COMMAND_GetScanOneParam(buffer, 20, arg_str, (uint8_t *)" ", (uint8_t *)" ");

            u32value = atol((char *)buffer);
        }
    }

    R_DEBUG_CommandServiceSet(service_object_id, u32value);

    return 0;
}


/******************************************************************************
* Function Name : R_DEBUG_CommandServiceGet
* Interface     : uint8_t R_DEBUG_CommandServiceGet(uint8_t service_type, uint8_t service_params, uint32_t* p_out_data)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DEBUG_CommandServiceGet(uint8_t service_type, uint8_t service_param , uint32_t* p_out_data)
{
    uint32_t u32value;
    float32_t f32value = 0.0f;

    uint8_t buffer[120];
    uint16_t len;
    
    uint8_t i;

    EM_SW_PROPERTY FAR_PTR *sw_property;

    gp_inst_LastDataPop;

    if (service_type == 0x03)       // EM READ
    {
        switch (service_param)
        {
            case 0x00:     // Service info help

                CMD_Printf((uint8_t *)"%# 3d : %s\n\r", 0x00, "Help");

                CMD_Printf((uint8_t *)"%# 3d : %s\n\r", 0x01, "[R]   Meter serial number");
                CMD_Printf((uint8_t *)"%# 3d : %s\n\r", 0x04, "[R]   Tariff Configure");
                CMD_Printf((uint8_t *)"%# 3d : %s\n\r", 0x05, "[R]   RTC");
                CMD_Printf((uint8_t *)"%# 3d : %s\n\r", 0x07, "[R]   Meter constant (Pulses/ (KWh | KVarh | KVAh) ");
                CMD_Printf((uint8_t *)"%# 3d : %s\n\r", 0x08, "[R]   Meter firmware version");

                CMD_Printf((uint8_t *)"%# 3d : %s\n\r", 0x30, "[R]   Nameplate table");

                CMD_Printf((uint8_t *)"%# 3d : %s\n\r", 0x31, "[R]   Load survey table");
                CMD_Printf((uint8_t *)"%# 3d : %s\n\r", 0x32, "[R]   Daily load survey table");
                CMD_Printf((uint8_t *)"%# 3d : %s\n\r", 0x33, "[R]   Billing record table");
                
                CMD_Printf((uint8_t *)"%# 3d : %s\n\r", 0x34, "[R]   Event table - voltage");
                CMD_Printf((uint8_t *)"%# 3d : %s\n\r", 0x35, "[R]   Event table - current related");
                CMD_Printf((uint8_t *)"%# 3d : %s\n\r", 0x36, "[R]   Event table - power related");
                CMD_Printf((uint8_t *)"%# 3d : %s\n\r", 0x37, "[R]   Event table - transaction related");
                CMD_Printf((uint8_t *)"%# 3d : %s\n\r", 0x38, "[R]   Event table - others table");
                CMD_Printf((uint8_t *)"%# 3d : %s\n\r", 0x39, "[R]   Event table - non-rollover");
                CMD_Printf((uint8_t *)"%# 3d : %s\n\r", 0x3A, "[R]   Event table - control");

                CMD_Printf((uint8_t *)"%# 3d : %s\n\r", 0x50, "[RW]  Event Notificaiton (0: Off, 1: On)");
                CMD_Printf((uint8_t *)"%# 3d : %s\n\r", 0x5C, "[RW]  Demand Period (mins) (Available: 5, 15, 30, 60)");
                CMD_Printf((uint8_t *)"%# 3d : %s\n\r", 0x5D, "[RW]  Block load period (s) (900, 1800, 2700, 3600)");

                return TRUE;

            case 0x01:     // Meter serial number
                R_NAMEPLATE_GetByID(NAMEPLATE_ID_SN, buffer, &len);
                buffer[len] = '\0';
                CMD_Printf((uint8_t *)"%s\n\r",buffer);
                return TRUE;

            case 0x04:     // Tariff Configure
                
                break;

            case 0x05:     // RTC
                print_rtc_time();
                return TRUE;

            case 0x07:     // Meter constant
                sw_property = EM_SW_GetProperty();
                CMD_Printf((uint8_t *)"%d\n\r", sw_property->operation.meter_constant);
                return TRUE;
                
            case 0x08:     // Firmware version
                R_NAMEPLATE_GetByID(NAMEPLATE_ID_FIRMWARE_VERSION, buffer, &len);
                buffer[len] = '\0';
                CMD_Printf((uint8_t *)"%s\n\r",buffer);
                return TRUE;
            
            case 0x30:     // Nameplate table
                print_name_platetable();

                return TRUE;

            case 0x31:     // Load survey table
                print_block_load_survey();
                return TRUE;
            case 0x32:     // Daily load survey table
                print_daily_load_survey();
                return TRUE;
            case 0x33:     // Billing record table
                print_billing();
                return TRUE;

            case 0x34:     // EVENT_TYPE_VOLTAGE_RELATED
                print_event_table(0);
                return TRUE;
            case 0x35:     // EVENT_TYPE_CURRENT_RELATED
                print_event_table(1);
                return TRUE;
            case 0x36:     // EVENT_TYPE_POWER_RELATED
                print_event_table(2);
                return TRUE;
            case 0x37:     // EVENT_TYPE_TRANSACTION_RELATED
                print_event_table(3);
                return TRUE;
            case 0x38:     // EVENT_TYPE_OTHERS
                print_event_table(4);
                return TRUE;
            case 0x39:     // EVENT_TYPE_NON_ROLLOVER_EVENTS
                print_event_table(5);
                return TRUE;
            case 0x3A:     // EVENT_TYPE_CONTROL_EVENTS
                print_event_table(6);
                return TRUE;

            case 0x50:
                CMD_Printf((uint8_t *)"EventNoti = %s \n\r", g_debug_notification_enable_flag?"On":"Off");
                return TRUE;

            case 0x5C:
                CMD_Printf((uint8_t *)"Demand intergration period = %d (mins) \n\r", g_demand_integration_period);
                return TRUE;

            case 0x5D:
                CMD_Printf((uint8_t *)"Block load capture period = %d (secs) \n\r", g_blockload_capture_period);
                return TRUE;

            case 0x60:
            case 0x61:
            case 0x62:
            case 0x63:
            case 0x64:
            case 0x65:
            case 0x66:
            case 0x67:
            case 0x68:
            case 0x69:
                print_schedulerv(service_param);
                return TRUE;

            case 0x80:
                print_activity_calendar();
                return TRUE;

            case 0xD0:      // Scheduler
                break;
            default:
                CMD_Printf("Unsupported or reserved");
                return TRUE;

        }

        CMD_Printf("%-# 0.4f", f32value);

    }
    else if (service_type == 0x02)
    {

    }

    return TRUE;
}


/******************************************************************************
* Function Name : R_DEBUG_CommandServiceGet
* Interface     : uint8_t R_DEBUG_CommandServiceGet(uint8_t service_param, uint32_t data)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DEBUG_CommandServiceSet(uint8_t service_param, uint32_t data)
{
    switch (service_param)
    {
        case 0x50:
            if (TRUE == (uint8_t)data){
                g_debug_notification_enable_flag = TRUE;
                CMD_Printf("Event notification is enabled");
            }
            else
            {
				g_debug_notification_enable_flag = FALSE;
				CMD_Printf("Event notification is disabled");
            }
            return 0;

        case 0x5C:
            g_demand_integration_period = data;
            return 0;

        case 0x5D:
            R_BLOCKLOAD_SetProfileCapturePeriod((uint16_t)data);
            return 0;

        default:
            CMD_Printf("Unsupported or reserved");
            return 0;
    }

}

/******************************************************************************
* Function Name : print_rtc_time
* Interface     : void print_rtc_time(void)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void print_rtc_time(void)
{
    rtc_counter_value_t rtctime;

    R_RTC_Get_CalendarCounterValue(&rtctime);

    CMD_Printf((uint8_t *)"%02x/%02x/%02x %02x:%02x:%02x %02x",
        rtctime.day,
        rtctime.month,
        rtctime.year,
        rtctime.hour,
        rtctime.min,
        rtctime.sec,
        rtctime.week);
                
}


/******************************************************************************
* Function Name : print_rtc_time
* Interface     : void print_rtc_time(void)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void print_rtc_counter( rtc_counter_value_t *p_rtctime)
{
    CMD_Printf((uint8_t *)"%02x/%02x/%02x %02x:%02x:%02x %02x, ",
        p_rtctime->day,
        p_rtctime->month,
        p_rtctime->year,
        p_rtctime->hour,
        p_rtctime->min,
        p_rtctime->sec,
        p_rtctime->week);            
}

/******************************************************************************
* Function Name : print_schedulerv
* Interface     : void print_schedulerv(uint8_t data_id)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void print_schedulerv(uint8_t data_id)
{
    uint8_t scheduler_id = data_id - 0x60;
    uint8_t num_of_element;
    uint8_t buffer[40];
    uint16_t i;
    
    rtc_counter_value_t schedule_data_rtc;
    
    if (scheduler_id >= MAX_SCHEDULER_NUMBER) {
        return;
    }
    
    CMD_Printf((uint8_t *)"\n\r");

    CMD_Printf((uint8_t *)"[SCHEDULER] %d\n\r", scheduler_id);
    
    num_of_element = R_SCHEDULER_ExecutionTimeArrayLengthGet(scheduler_id);
    CMD_Printf((uint8_t *)"Number of element: %d\n\r", num_of_element);

    CMD_Printf((uint8_t *)"| no , YYMMWWDD hhmmss |\n\r", num_of_element);
    for (i = 0; i < num_of_element; i++)
    {
        CMD_Printf((uint8_t *)"%d, ", i);

        R_SCHEDULER_ExecutionDateGet(buffer, scheduler_id, i);

        CMD_Printf((uint8_t *)"%02X", buffer[0]); // YY Year (00 -> 99)
        CMD_Printf((uint8_t *)"%02X", buffer[1]); // MM Month (1 -> 12)
        CMD_Printf((uint8_t *)"%02X", buffer[2]); // WW Day of Week (0 Monday, 1 Tue, ... )
        CMD_Printf((uint8_t *)"%02X", buffer[3]); // DD Day of Month (1st, 2nd, ... 31th)
        CMD_Printf((uint8_t *)" ", buffer[0]);

        R_SCHEDULER_ExecutionTimeGet(buffer, scheduler_id, i);
        CMD_Printf((uint8_t *)"%02X", buffer[0]); // hh
        CMD_Printf((uint8_t *)"%02X", buffer[1]); // mm
        CMD_Printf((uint8_t *)"%02X", buffer[2]); // ss

        CMD_Printf((uint8_t *)"\n\r");
    }

    CMD_Printf((uint8_t *)"[END]\n\r");
    
}

/******************************************************************************
* Function Name : print_block_load_survey
* Interface     : void print_block_load_survey(void)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void print_block_load_survey(void)
{
    uint32_t entry_in_used;
    uint32_t profile_entry;
    r_block_load_t bl;
    uint16_t i;
	uint8_t divider;
	uint16_t capture_period = 0;

	R_BLOCKLOAD_GetProfileCapturePeriod(&capture_period);
	divider = (uint8_t)( capture_period / (15 * 60));

	R_BLOCKLOAD_GetEntryInUse(&entry_in_used, divider);
    R_BLOCKLOAD_GetProfileEntry(&profile_entry, divider);

    CMD_Printf((uint8_t *)"Block Load Table \n\r");
    CMD_Printf((uint8_t *)"-------------------------\n\r");
    CMD_Printf((uint8_t *)"Profile Capacity: %2d\n\r", profile_entry);
    CMD_Printf((uint8_t *)"Current In Used: %2d\n\r", entry_in_used);
    CMD_Printf((uint8_t *)"Capture period: %2d (s)\n\r", capture_period);
    CMD_Printf((uint8_t *)"-------------------------\n\r");
    CMD_Printf((uint8_t *)"TABLE START\n\r");
    CMD_Printf((uint8_t *)"Index, RTC , Avg I_R , Avg I_Y , Avg I_B , Avg V_R , Avg V_Y , Avg V_B , EnergykWhImport , EnergykVAhImport , EnergykWhExport , EnergykVAhExport\n\r");

    for (i = 0; i < entry_in_used; i++)
    {
        R_BLOCKLOAD_GetEntryByIndex(i, divider, &bl);

        CMD_Printf((uint8_t *)"%2d, ", i);

        bl.CaptureTime.min += (g_blockload_capture_period / 60);
        if (bl.CaptureTime.min >= 60)
        {
            bl.CaptureTime.min = 0;
            bl.CaptureTime.hour += 1;
            if (bl.CaptureTime.hour >= 24)
            {
                bl.CaptureTime.hour = 0;
                R_LoadSurvey_FindNextDay(&bl.CaptureTime);
            }
        }

        CMD_Printf((uint8_t *)param_format_rtc,
            WRP_EXT_Dec2Bcd(bl.CaptureTime.day),
            WRP_EXT_Dec2Bcd(bl.CaptureTime.month),
            WRP_EXT_Dec2Bcd(bl.CaptureTime.year),
            WRP_EXT_Dec2Bcd(bl.CaptureTime.hour),
            WRP_EXT_Dec2Bcd(bl.CaptureTime.min),
            WRP_EXT_Dec2Bcd(bl.CaptureTime.sec),
            WRP_EXT_Dec2Bcd(bl.CaptureTime.week));

        CMD_Printf((uint8_t *)" %# 9.4f", bl.Current_R);
        CMD_Printf((uint8_t *)", %# 9.4f", bl.Current_Y);
        CMD_Printf((uint8_t *)", %# 9.4f", bl.Current_B);
        CMD_Printf((uint8_t *)", %# 9.4f", bl.Voltage_R);
        CMD_Printf((uint8_t *)", %# 9.4f", bl.Voltage_Y);
        CMD_Printf((uint8_t *)", %# 9.4f", bl.Voltage_B);
        CMD_Printf((uint8_t *)", %# 9.4f", bl.EnergykWhImport);
        CMD_Printf((uint8_t *)", %# 9.4f", bl.EnergykVAhImport);
        CMD_Printf((uint8_t *)", %# 9.4f", bl.EnergykWhExport);
        CMD_Printf((uint8_t *)", %# 9.4f", bl.EnergykVAhExport);
        CMD_Printf((uint8_t *)"\n\r");


        /* Break if CTRL+C is pressed */
        IF_CTRL_C_BREAK();

    }

    CMD_Printf((uint8_t *)"END\n\r");

}

/******************************************************************************
* Function Name : print_daily_load_survey
* Interface     : void print_daily_load_survey(void)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void print_daily_load_survey(void)
{
    uint32_t entry_in_used;
    uint32_t profile_entry;
    r_daily_load_t dl;
    uint16_t i;
	uint8_t divider;
	uint16_t capture_period = 0;

	R_DAILYLOAD_GetEntryInUse(&entry_in_used);
    R_DAILYLOAD_GetProfileEntry(&profile_entry);

    CMD_Printf((uint8_t *)"Daily Load Table \n\r");
    CMD_Printf((uint8_t *)"Profile Capacity: %2d\n\r", profile_entry);
    CMD_Printf((uint8_t *)"Current In Used: %2d\n\r", entry_in_used);

    CMD_Printf((uint8_t *)"TABLE START\n\r");
    CMD_Printf((uint8_t *)"Index, RTC , EnergykWhImport , EnergykVAhImport , EnergykWhExport , EnergykVAhExport\n\r");

    for (i = 0; i < entry_in_used; i++)
    {
        R_DAILYLOAD_GetEntryByIndex(i, &dl);
        
        CMD_Printf((uint8_t *)"%2d, ", i);

        if (dl.CaptureTime.hour == 24)
        {
            dl.CaptureTime.hour = 0;
            R_LoadSurvey_FindNextDay(&dl.CaptureTime);
        }

        CMD_Printf((uint8_t *)param_format_rtc,
            WRP_EXT_Dec2Bcd(dl.CaptureTime.day),
            WRP_EXT_Dec2Bcd(dl.CaptureTime.month),
            WRP_EXT_Dec2Bcd(dl.CaptureTime.year),
            WRP_EXT_Dec2Bcd(dl.CaptureTime.hour),
            WRP_EXT_Dec2Bcd(dl.CaptureTime.min),
            WRP_EXT_Dec2Bcd(dl.CaptureTime.sec),
            WRP_EXT_Dec2Bcd(dl.CaptureTime.week));

        CMD_Printf((uint8_t *)" %# 9.4f, %# 9.4f, %# 9.4f, %# 9.4f\n\r",
            dl.EnergykWhImport,
            dl.EnergykVAhImport,
            dl.EnergykWhExport,
            dl.EnergykVAhExport);
    }

    CMD_Printf((uint8_t *)"END\n\r");

}

/******************************************************************************
* Function Name : print_billing
* Interface     : void print_billing(void)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void print_billing(void)
{
    uint32_t entry_in_used;
    uint32_t profile_entry;
    r_billing_t bill;
    uint16_t i;
	uint8_t divider;
	uint16_t capture_period = 0;


	R_BILLING_GetEntryInUse(&entry_in_used);
	R_BILLING_GetProfileEntry(&profile_entry);

    CMD_Printf((uint8_t *)"\n\r");
    CMD_Printf((uint8_t *)"Profile Capacity: %2d\n\r", profile_entry);
    CMD_Printf((uint8_t *)"Current In Used: %2d\n\r", entry_in_used);

    //CMD_Printf((uint8_t *)"RTC                    | EnergykWhImport | EnergykVAhImport | EnergykWhExport | EnergykVAhExport\n\r");
    
    CMD_Printf((uint8_t *)"TABLE START\n\r");
    
    /* Print header */
    CMD_Printf("Index, RTC, AveragePowerFactor, CumulativeEnergykWh, ");
    for(i=1;i <= 8;i++)
    {
        CMD_Printf("CumulativeEnergykWh_TZ%d, ", i);
    }
    CMD_Printf("CumulativeEnergykVAh, ");
    for(i=1;i <= 8;i++)
    {
        CMD_Printf("CumulativeEnergykVAh_TZ%d, ", i);
    }
    CMD_Printf("MD_kW, ");
    for(i=1;i <= 8;i++)
    {
        CMD_Printf("MD_kW TZ%d, ", i);
    }
    CMD_Printf("MDM_kW_DateTime, ");
    for(i=1;i <= 8;i++)
    {
        CMD_Printf("MDM_kW_DateTime TZ%d, ", i);
    }
    CMD_Printf("MD_kVA, ");
    for(i=1;i <= 8;i++)
    {
        CMD_Printf("MD_kVA TZ%d, ", i);
    }
    CMD_Printf("MDM_kVA_DateTime, ");
    for(i=1;i <= 8;i++)
    {
        CMD_Printf("MDM_kVA_DateTime TZ%d, ", i);
    }
    CMD_Printf("PowerONduration, ");

    CMD_Printf("CumulativeEnergykWh_Export, ");
    CMD_Printf("CumulativeEnergykVAh_Export, ");
    CMD_Printf("CumulativeEnergykVArh_QI, ");
    CMD_Printf("CumulativeEnergykVArh_QII, ");
    CMD_Printf("CumulativeEnergykVArh_QIII, ");
    CMD_Printf("CumulativeEnergykVArh_QIV ");
    CMD_Printf("\n\r");

    for (i = 0; i < entry_in_used; i++)
    {
        R_BILLING_GetEntryByIndex(i, &bill);

        CMD_Printf((uint8_t *)"%2d, ", i);

        CMD_Printf((uint8_t *)param_format_rtc,
            WRP_EXT_Dec2Bcd(bill.CaptureTime.day),
            WRP_EXT_Dec2Bcd(bill.CaptureTime.month),
            WRP_EXT_Dec2Bcd(bill.CaptureTime.year),
            WRP_EXT_Dec2Bcd(bill.CaptureTime.hour),
            WRP_EXT_Dec2Bcd(bill.CaptureTime.min),
            WRP_EXT_Dec2Bcd(bill.CaptureTime.sec),
            WRP_EXT_Dec2Bcd(bill.CaptureTime.week));

        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.AveragePowerFactor);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.CumulativeEnergykWh);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.CumulativeEnergykWh_TZ1);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.CumulativeEnergykWh_TZ2);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.CumulativeEnergykWh_TZ3);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.CumulativeEnergykWh_TZ4);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.CumulativeEnergykWh_TZ5);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.CumulativeEnergykWh_TZ6);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.CumulativeEnergykWh_TZ7);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.CumulativeEnergykWh_TZ8);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.CumulativeEnergykVAh);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.CumulativeEnergykVAh_TZ1);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.CumulativeEnergykVAh_TZ2);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.CumulativeEnergykVAh_TZ3);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.CumulativeEnergykVAh_TZ4);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.CumulativeEnergykVAh_TZ5);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.CumulativeEnergykVAh_TZ6);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.CumulativeEnergykVAh_TZ7);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.CumulativeEnergykVAh_TZ8);

        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.MDkW);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.MDkW_TZ1);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.MDkW_TZ2);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.MDkW_TZ3);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.MDkW_TZ4);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.MDkW_TZ5);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.MDkW_TZ6);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.MDkW_TZ7);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.MDkW_TZ8);
        
        //CMD_Printf((uint8_t *)"%# 9.4f ",bill.MDkWDateTime);
        print_rtc_counter((rtc_counter_value_t *)&bill.MDkWDateTime);
        print_rtc_counter((rtc_counter_value_t *)&bill.MDkWDateTime_TZ1);
        print_rtc_counter((rtc_counter_value_t *)&bill.MDkWDateTime_TZ2);
        print_rtc_counter((rtc_counter_value_t *)&bill.MDkWDateTime_TZ3);
        print_rtc_counter((rtc_counter_value_t *)&bill.MDkWDateTime_TZ4);
        print_rtc_counter((rtc_counter_value_t *)&bill.MDkWDateTime_TZ5);
        print_rtc_counter((rtc_counter_value_t *)&bill.MDkWDateTime_TZ6);
        print_rtc_counter((rtc_counter_value_t *)&bill.MDkWDateTime_TZ7);
        print_rtc_counter((rtc_counter_value_t *)&bill.MDkWDateTime_TZ8);

        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.MDkVA);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.MDkVA_TZ1);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.MDkVA_TZ2);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.MDkVA_TZ3);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.MDkVA_TZ4);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.MDkVA_TZ5);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.MDkVA_TZ6);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.MDkVA_TZ7);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.MDkVA_TZ8);
        
        //CMD_Printf((uint8_t *)"%# 9.4f ",bill.MDkWDateTime);
        print_rtc_counter((rtc_counter_value_t *)&bill.MDkWDateTime);
        print_rtc_counter((rtc_counter_value_t *)&bill.MDkWDateTime_TZ1);
        print_rtc_counter((rtc_counter_value_t *)&bill.MDkWDateTime_TZ2);
        print_rtc_counter((rtc_counter_value_t *)&bill.MDkWDateTime_TZ3);
        print_rtc_counter((rtc_counter_value_t *)&bill.MDkWDateTime_TZ4);
        print_rtc_counter((rtc_counter_value_t *)&bill.MDkWDateTime_TZ5);
        print_rtc_counter((rtc_counter_value_t *)&bill.MDkWDateTime_TZ6);
        print_rtc_counter((rtc_counter_value_t *)&bill.MDkWDateTime_TZ7);
        print_rtc_counter((rtc_counter_value_t *)&bill.MDkWDateTime_TZ8);

        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.PowerONduration);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.CumulativeEnergykWh_Export);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.CumulativeEnergykVAh_Export);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.CumulativeEnergykVArh_QI);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.CumulativeEnergykVArh_QII);
        CMD_Printf((uint8_t *)"%# 9.4f, ",bill.CumulativeEnergykVArh_QIII);
        CMD_Printf((uint8_t *)"%# 9.4f ",bill.CumulativeEnergykVArh_QIV);
        CMD_Printf((uint8_t *)"\n\r");
    }

    CMD_Printf((uint8_t *)"END\n\r");

}



/******************************************************************************
* Function Name : print_event0_table
* Interface     : void print_event0_table(void)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void print_event_table(uint8_t event_type)
{
    uint32_t entry_in_used;
    uint32_t profile_entry;
    EVENT_PARAMS_T entry;
    uint16_t i;

	R_EVENT_EntriesInUseGet((EVENT_TYPE_T)event_type, &entry_in_used);
    R_EVENT_ProfileEntriesGet((EVENT_TYPE_T)event_type, &profile_entry);

    CMD_Printf((uint8_t *)"\n\r");
    CMD_Printf((uint8_t *)"Profile Capacity: %2d\n\r", profile_entry);
    CMD_Printf((uint8_t *)"Current In Used: %2d\n\r", entry_in_used);

    CMD_Printf((uint8_t *)"TABLE START\n\r");

    CMD_Printf((uint8_t *)"Index, CaptureTime, ");
    CMD_Printf((uint8_t *)"Event Code ");

    if (event_type == (uint8_t)EVENT_TYPE_VOLTAGE_RELATED ||
            event_type == (uint8_t)EVENT_TYPE_CURRENT_RELATED ||
            event_type == (uint8_t)EVENT_TYPE_OTHERS)
    {
        CMD_Printf((uint8_t *)", IR, ");  
        CMD_Printf((uint8_t *)"IY, ");  
        CMD_Printf((uint8_t *)"IB, ");  
        CMD_Printf((uint8_t *)"VRN, ");  
        CMD_Printf((uint8_t *)"VYN, ");  
        CMD_Printf((uint8_t *)"VBN, ");  
        CMD_Printf((uint8_t *)"PF_R, ");  
        CMD_Printf((uint8_t *)"PF_Y, ");  
        CMD_Printf((uint8_t *)"PF_B, ");  
        CMD_Printf((uint8_t *)"ActiveEnergyImport, ");  
        CMD_Printf((uint8_t *)"TamperCounter ");  
    }
    CMD_Printf((uint8_t *)"\n\r");

    for (i = 0; i < entry_in_used; i++)
    {
        entry = R_EVENT_GetEntry((EVENT_TYPE_T)event_type, i);

        CMD_Printf((uint8_t *)"%3d ,", i);

        CMD_Printf((uint8_t *)param_format_rtc,
            WRP_EXT_Dec2Bcd(entry.captured_time.Day),
            WRP_EXT_Dec2Bcd(entry.captured_time.Month),
            WRP_EXT_Dec2Bcd(entry.captured_time.Year),
            WRP_EXT_Dec2Bcd(entry.captured_time.Hour),
            WRP_EXT_Dec2Bcd(entry.captured_time.Min),
            WRP_EXT_Dec2Bcd(entry.captured_time.Sec),
            WRP_EXT_Dec2Bcd(entry.captured_time.Week));

        CMD_Printf((uint8_t *)"%# 4d "  , entry.code);

        if (event_type == (uint8_t)EVENT_TYPE_VOLTAGE_RELATED ||
            event_type == (uint8_t)EVENT_TYPE_CURRENT_RELATED ||
            event_type == (uint8_t)EVENT_TYPE_OTHERS)
        {
            CMD_Printf((uint8_t *)", %# 9.4f , ", entry.IR);
            CMD_Printf((uint8_t *)"%# 9.4f , ", entry.IY);
            CMD_Printf((uint8_t *)"%# 9.4f , ", entry.IB);
            CMD_Printf((uint8_t *)"%# 9.4f , ", entry.VRN);
            CMD_Printf((uint8_t *)"%# 9.4f , ", entry.VYN);
            CMD_Printf((uint8_t *)"%# 9.4f , ", entry.VBN);
            CMD_Printf((uint8_t *)"%# 9.4f , ", entry.PF_R);
            CMD_Printf((uint8_t *)"%# 9.4f , ", entry.PF_Y);
            CMD_Printf((uint8_t *)"%# 9.4f , ", entry.PF_B);
            CMD_Printf((uint8_t *)"%# 9.4f , ", entry.ActiveEnergyImport);
            CMD_Printf((uint8_t *)"%# 4d",    entry.TamperCounter);
        }

        CMD_Printf((uint8_t *)"\n\r");

    }

    CMD_Printf((uint8_t *)"END\n\r");

}

/******************************************************************************
* Function Name : print_name_platetable
* Interface     : void print_name_platetable(void)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void print_name_platetable(void)
{
    const uint8_t nameplate_str[][25] = 
    {
        "0. Logical device name: ",
        "1. Meter serial number: ",
        "2. Manufacturer name  : ",
        "3. Device ID          : ",
        "4. Meter Category     : ",
        "5. Ib-Imax            : ",
        "6. Meter Year of mnf  : ",
        "7. Meter type         : ",
        "8. Firmware version   : ",
        "9. Flag ID            : ",
    };

    uint8_t buffer[120];
    uint16_t len;
    uint8_t i,j;

    CMD_Printf("[NAMEPLATE]\n\r");
    for (i = NAMEPLATE_ID_LDN; i <= NAMEPLATE_ID_FLAGID; i++)
    {
        CMD_Printf((uint8_t *)"%s", nameplate_str[i]);
        R_NAMEPLATE_GetByID(i, buffer, &len);
        buffer[len] = '\0';
        CMD_Printf((uint8_t *)"## %s ##",buffer);

        CMD_Printf((uint8_t *)"(HEX: ");
        for(j = 0;j < len; j++)
        {
            CMD_Printf((uint8_t *)"%02X",buffer[j]);
        }
        CMD_Printf((uint8_t *)")\n\r",buffer[j]);
    }

    CMD_Printf("[END]\n\r");

}


void calendar_check_name_len(uint8_t *p_buffer, uint8_t *p_len)
{
    if (*p_len > NAME_LENGTH_MAX) { 
        CMD_Printf((uint8_t *)"\n\r[Error] Length too long! (>%d)\n\r", NAME_LENGTH_MAX);
        *p_len = NAME_LENGTH_MAX;
    }
    p_buffer[*p_len] = '\0';
}


/******************************************************************************
* Function Name : print_activity_calendar
* Interface     : void print_activity_calendar(void)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void print_activity_calendar(void)
{
    uint16_t len;
    uint8_t i,j;

    uint8_t is_Passive = FALSE;

    r_act_cal_name_t            calendar_name;
    r_act_cal_season_profile_t  season_profile;
    r_act_cal_season_t          active_season;
    r_act_cal_week_profile_t    week_profile;
    r_act_cal_day_profile_t     day_profile;
    r_act_cal_week_t            active_week_profile;
    r_act_cal_day_t             active_day_profile;
    rtc_counter_value_t         activation_time;

    CMD_Printf("\n\r[Activity Calendar]\n\r");

    CMD_Printf((uint8_t *)"\n\r1. Calendar Name (Active): ");
    calendar_name = R_ACT_CAL_Restore_CalendarName(is_Passive);
    if (calendar_name.len > NAME_LENGTH_MAX) { 
        CMD_Printf((uint8_t *)"\n\r[Error] Length too long! (>%d)", NAME_LENGTH_MAX);
        calendar_name.len = NAME_LENGTH_MAX;
    }
    calendar_name.value[calendar_name.len] = '\0';
    CMD_Printf((uint8_t *)"%s (len = %d)\n\r", calendar_name.value, calendar_name.len);

    CMD_Printf((uint8_t *)"2. Season Profile (Active)\n\r");
    season_profile = R_ACT_CAL_Restore_SeasonProfile(is_Passive);
    CMD_Printf("     Num of entry : %d\n\r", season_profile.num);
    for(i = 0; i < season_profile.num; i++)
    {
		CMD_Printf("     [Entry %02d]\n\r", i);
        calendar_check_name_len(season_profile.entry[i].name.value, &season_profile.entry[i].name.len);
        CMD_Printf("     + Name : %s (len = %d)\n\r", season_profile.entry[i].name.value, season_profile.entry[i].name.len);
        CMD_Printf("     + Start Time : ");
        print_rtc_counter(&season_profile.entry[i].start_time);

        calendar_check_name_len(season_profile.entry[i].week.value, &season_profile.entry[i].week.len);
        CMD_Printf("\n\r     + Week : %s (len = %d)\n\r", season_profile.entry[i].week.value, season_profile.entry[i].week.len);
    }

    CMD_Printf((uint8_t *)"3. Week Profile (Active)\n\r");
    week_profile = R_ACT_CAL_Restore_WeekProfile(is_Passive);
    CMD_Printf("     Num of entry : %d\n\r", week_profile.num);
    for(i = 0; i < week_profile.num; i++)
    {
        CMD_Printf("     Entry: %d\n\r",i);
        calendar_check_name_len(week_profile.entry[i].name.value, &week_profile.entry[i].name.len);
        CMD_Printf("     + Name : %s (len = %d)\n\r", week_profile.entry[i].name.value, week_profile.entry[i].name.len);
        CMD_Printf("     + Data : ");
        for(j = 0;j<7;j++)
        {
            CMD_Printf("%02d ", week_profile.entry[i].data[j]);
        }
        CMD_Printf("\n\r");
    }

    CMD_Printf((uint8_t *)"4. Day Profile (Active)\n\r");
    day_profile = R_ACT_CAL_Restore_DayProfile(is_Passive);
    CMD_Printf("     Num of entry : %d\n\r", day_profile.num);
    for(i = 0; i < day_profile.num; i++)
    {
        CMD_Printf("     Entry: %d\n\r", i);
        CMD_Printf("     ID : %02d\n\r", day_profile.entry[i].dayID);
        CMD_Printf("     +  Num of Action: %02d\n\r", day_profile.entry[i].numberOfAction);
        for(j = 0;j < day_profile.entry[i].numberOfAction;j++)
        {
            CMD_Printf("     +  Action [%02d]: %02d:%02d , %02d (HH:MM, ScriptID)\n\r", 
                    j, 
                    day_profile.entry[i].action[j].hour, 
                    day_profile.entry[i].action[j].min, 
                    day_profile.entry[i].action[j].scriptID);
        }
        CMD_Printf("\n\r");
    }

    is_Passive = TRUE;

    CMD_Printf((uint8_t *)"5. Calendar Name (Passive): ");
    calendar_name = R_ACT_CAL_Restore_CalendarName(is_Passive);
    if (calendar_name.len > NAME_LENGTH_MAX) { 
        CMD_Printf((uint8_t *)"\n\r[Error] Length too long! (>%d)", NAME_LENGTH_MAX);
        calendar_name.len = NAME_LENGTH_MAX;
    }
    calendar_name.value[calendar_name.len] = '\0';
    CMD_Printf((uint8_t *)"%s (len = %d)\n\r", calendar_name.value, calendar_name.len);

    CMD_Printf((uint8_t *)"6. Season Profile (Passive)\n\r");
    season_profile = R_ACT_CAL_Restore_SeasonProfile(is_Passive);
    CMD_Printf("     Num of entry : %d\n\r", season_profile.num);
    for(i = 0; i < season_profile.num; i++)
    {
        CMD_Printf("     [Entry %02d]\n\r", i);
        calendar_check_name_len(season_profile.entry[i].name.value, &season_profile.entry[i].name.len);
        CMD_Printf("     + Name : %s (len = %d)\n\r", season_profile.entry[i].name.value, season_profile.entry[i].name.len);
        CMD_Printf("     + Start Time : ");
        print_rtc_counter(&season_profile.entry[i].start_time);

        calendar_check_name_len(season_profile.entry[i].week.value, &season_profile.entry[i].week.len);
        CMD_Printf("\n\r     + Week : %s (len = %d)\n\r", season_profile.entry[i].week.value, season_profile.entry[i].week.len);
    }

    CMD_Printf((uint8_t *)"7. Week Profile (Passive)\n\r");
    week_profile = R_ACT_CAL_Restore_WeekProfile(is_Passive);
    CMD_Printf("     Num of entry : %d\n\r", week_profile.num);
    for(i = 0; i < week_profile.num; i++)
    {
        CMD_Printf("     Entry: %d\n\r",i);
        calendar_check_name_len(week_profile.entry[i].name.value, &week_profile.entry[i].name.len);
        CMD_Printf("     + Name : %s (len = %d)\n\r", week_profile.entry[i].name.value, week_profile.entry[i].name.len);
        CMD_Printf("     + Data : ");
        for(j = 0;j<7;j++)
        {
            CMD_Printf("%02d ", week_profile.entry[i].data[j]);
        }
        CMD_Printf("\n\r");
    }

    CMD_Printf((uint8_t *)"8. Day Profile (Passive)\n\r");
    day_profile = R_ACT_CAL_Restore_DayProfile(is_Passive);
    CMD_Printf("     Num of entry : %d\n\r", day_profile.num);
    for(i = 0; i < day_profile.num; i++)
    {
        CMD_Printf("     Entry: %d\n\r",i);
        CMD_Printf("     ID : %02d\n\r", day_profile.entry[i].dayID);
        CMD_Printf("     +  Num of Action: %02d\n\r", day_profile.entry[i].numberOfAction);
        for(j = 0;j < day_profile.entry[i].numberOfAction;j++)
        {
            CMD_Printf("     +  Action [%02d]: %02d:%02d , %02d (HH:MM, ScriptID)\n\r", 
                j, 
                day_profile.entry[i].action[j].hour, 
                day_profile.entry[i].action[j].min, 
                day_profile.entry[i].action[j].scriptID);
        }
        CMD_Printf("\n\r");
    }
    
    CMD_Printf((uint8_t *)"9. Activate passive calendar time: ");
    R_ACT_CAL_Get_ActivationTime(&activation_time);

    CMD_Printf((uint8_t *)"%02d/%02d/%02d %02d:%02d:%02d %02d\n\r",
        activation_time.day,
        activation_time.month,
        activation_time.year,
        activation_time.hour,
        activation_time.min,
        activation_time.sec,
        activation_time.week
    );


    CMD_Printf("[END]\n\r");

}

void print_em_startup_diag(void)
{
    CMD_SendString((uint8_t *)"\n\rMeter startup diag:\n\r");
    
     CMD_Printf((uint8_t *)"EM Init Status:     %d\n\r", g_em_startup_diag.em_init_status);
     CMD_Printf((uint8_t *)"Config load status: %d\n\r", g_em_startup_diag.config_load_status);
     CMD_Printf((uint8_t *)"Energy load status: %d\n\r", g_em_startup_diag.energy_load_status);
     CMD_Printf((uint8_t *)"EM Start status:    %d\n\r", g_em_startup_diag.em_start_status);
}

/******************************************************************************
* Function Name : COMMAND_Init
* Interface     : void COMMAND_Init(void)
* Description   : Init the COMMAND application
* Arguments     : None
* Return Value  : None
******************************************************************************/
void COMMAND_Init(void)
{
    CMD_Init();
    CMD_RegisterSuggestion((void *)cmd_table, COMMAND_TABLE_LENGTH);
    CMD_SendString((uint8_t *)"\n\rDebug Command Initialized\n\r");
    
    print_em_startup_diag();
}

/***********************************************************************************************************************
* Function Name    : void COMMAND_PollingProcessing(void)
* Description      : COMMAND Polling Processing
* Arguments        : None
* Functions Called : None
* Return Value     : None
***********************************************************************************************************************/
void COMMAND_PollingProcessing(void)
{
    uint8_t i, is_found_cmd;
    uint8_t *pstr, *p_strarg;
    uint8_t cmdstr[64];

    /* Processing command line */
    if (CMD_IsCmdReceived())
    {
        /* Get command */
        pstr = CMD_Get();
        memset(cmdstr, 0, 64);

        /* Skip all ahead space */
        while (pstr[0] == ' ' && pstr[0] != 0)
        {
            pstr++;
        }
        
        /* Get command name */
        i = 0;
        while (pstr[0] != ' ' && pstr[0] != 0)
        {
            cmdstr[i++] = *pstr;
            pstr++;
        }
        
        /* Skip all ahead space on argument list */
        while (pstr[0] == ' ' && pstr[0] != 0)
        {
            pstr++;
        }
        p_strarg = pstr;

        /* is end of string */
        if (p_strarg[0] == 0)
        {
            p_strarg = NULL;    /* No parameter */
        }

        /* Find to invoke the command on the cmd_table */
        if (cmdstr[0] != 0)
        {
            is_found_cmd = 0;       /* Not found */
            for (i = 0; i < COMMAND_TABLE_LENGTH; i++)
            {
                /* is matched? */
                if (strcmp((const char *)cmdstr, (const char *)cmd_table[i].cmd_name) == 0)
                {
                    INVOKE_COMMAND(i, p_strarg);        /* Invoke to function */
                    is_found_cmd = 1;                   /* Found command */
                }
            }
            
            /* is NOT found command? */
            if (!is_found_cmd)
            {
                CMD_SendString((uint8_t *)"\n\rUnknown command: [");
                CMD_SendString(CMD_Get());
                CMD_SendString((uint8_t *)"]\n\rType ? for command list\n\r");
            }
        }

        CMD_AckCmdReceived();
    }
    #ifdef __CA78K0R__
    /* Math Error Exception Printout */
    if (g_matherr_type != 0)
    {
        CMD_Printf( (uint8_t *)"\n\rDEBUG: Math error exception [type: %i]\n\r",
                    g_matherr_type);

        CMD_AckCmdReceived();
        
        /* ACK */
        g_matherr_type = 0;
    }
    #endif
}


#endif /* __DEBUG */
