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
* Copyright (C) 2013, 2016 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_loadsurvey.c
* Version      : <Version>
* Device(s)    : <'RL78/I1C'>
* Tool-Chain   : <'CCRL'>
* H/W Platform : <'RL78/I1C Energy Meter Platform'>
* Description  : <Description of file>
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Standard */
#include "typedef.h"

/* CG Drivers */
#include "r_cg_macrodriver.h"
#include "r_cg_rtc.h"
#include "r_cg_wdt.h"

/* Meter SDKs */
#include "eeprom.h"
#include "storage.h"

/* Wrapper */
#include "wrp_app_ext.h"

/* Application */
#include "r_loadsurvey.h"
#include "inst_read.h"
#include "event.h"
#include "r_tariff.h"
#include "r_max_demand.h"
#include "r_meter_format.h"

#include "r_abnormal_operating.h"
#include "bl_serialflash.h"
/* Common */
#include <string.h>

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

//#ifndef STORAGE_EEPROM_BLOCKLOAD_PARTITION_ADDR
    //#define STORAGE_EEPROM_BLOCKLOAD_PARTITION_ADDR 10000
//#endif
//#ifndef STORAGE_EEPROM_DAILYLOAD_PARTITION_ADDR
    //#define STORAGE_EEPROM_DAILYLOAD_PARTITION_ADDR 15000
//#endif
//#ifndef STORAGE_EEPROM_BILLING_PARTITION_ADDR
    //#define STORAGE_EEPROM_BILLING_PARTITION_ADDR 17000
//#endif

#define BLOCKLOAD_BACKUP_DATA_REGION_ADDR   (STORAGE_EEPROM_BLOCKLOAD_PARTITION_ADDR)
#define BLOCKLOAD_PARAMS_BACKUP_SIZE        (100)
#define BLOCKLOAD_STORAGE_BASE_ADDR         (BLOCKLOAD_BACKUP_DATA_REGION_ADDR + BLOCKLOAD_PARAMS_BACKUP_SIZE)

#define BLOCKLOAD_MAX_ROW                   (36)
#define BLOCKLOAD_MAX_ENTRIES               ((uint32_t)BLOCKLOAD_MAX_ROW * 96)

#define DAILYLOAD_BACKUP_DATA_REGION_ADDR   (STORAGE_EEPROM_DAILYLOAD_PARTITION_ADDR)
#define DAILYLOAD_BACKUP_SIZE               (50)
#define DAILYLOAD_STORAGE_BASE_ADDR         (DAILYLOAD_BACKUP_DATA_REGION_ADDR + DAILYLOAD_BACKUP_SIZE)
#define DAILYLOAD_MAX_ROW                   (35)

#define BILLING_BACKUP_DATA_REGION_ADDR     (STORAGE_EEPROM_BILLING_PARTITION_ADDR)
#define BILLING_BACKUP_SIZE                 (50)
#define BILLING_STORAGE_BASE_ADDR           (BILLING_BACKUP_DATA_REGION_ADDR + DAILYLOAD_BACKUP_SIZE)
#define BILLING_MAX_ROW                     (12)

#define BLOCKLOAD_AVERAGE_CALCULATION       (1)

#ifndef SFL_DEVICE_PAGE_SIZE
#define SFL_DEVICE_PAGE_SIZE (256)
#endif

#define BLOCKLOAD_SERIAL_FLASH_PAGE_SIZE						(SFL_DEVICE_PAGE_SIZE) //256
#define BLOCKLOAD_SERIAL_FLASH_BLOCK_SIZE						((uint32_t)SFL_DEVICE_MINIMUM_BLOCK_SIZE * 2)//4096
#define BLOCKLOAD_NUMBER_OF_ENTRY_PER_PAGE						(8)
#define BLOCKLOAD_ENTRIES_TABLE_START_ADDR						(0x100000)
#define BLOCKLOAD_ENTRIES_TABLE_TOTAL_ENTRY						((uint32_t)BLOCKLOAD_MAX_ENTRIES)
#define BLOCKLOAD_ENTRIES_TABLE_SIZE							(((uint32_t)BLOCKLOAD_MAX_ROW) * (uint32_t)BLOCKLOAD_SERIAL_FLASH_BLOCK_SIZE )
/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

typedef struct st_table_config
{
    uint32_t TableTimeCaptureStartAddr;
    uint32_t TableStartAddr;
    uint32_t MaxEntries;
    uint32_t MaxRow;
    uint16_t LogSize;
    uint16_t CaptureTimeSize;
} st_table_config_t;


typedef struct tag_dailyload_table_config_t
{
    uint32_t TableStartAddr;
    uint32_t MaxEntries;
    uint16_t LogSize;
} dailyload_table_config_t;

typedef struct tag_billing_table_header_config_t
{
    uint32_t TableStartAddr;
    uint32_t MaxEntries;
    uint16_t LogSize;
} billing_table_config_t;

typedef struct st_blkload_rtc
{
    /* Total: 6 bytes */
    uint8_t Sec;        /* Second */
    uint8_t Min;        /* Minute */
    uint8_t Hour;       /* Hour */
    uint8_t Day;        /* Day */
    uint8_t Month;      /* Month */
    uint16_t Year;      /* Year */
} st_blkload_rtc_t;

typedef struct tag_blockload_table_header_t
{
    uint8_t                         IsRolledOver    :1;
    uint8_t                         IsBackWard      :1;
    uint8_t                         IsAbnormal      :1;
    uint16_t                        FirstRowIndex;
    uint16_t                        RowInUse;
    uint16_t                        ColumnInUse;
} blockload_table_header_t;


typedef struct tag_dailyload_table_header_t
{
    uint8_t                         IsRolledOver;
    uint16_t                        FirstEntryIndex;
    uint16_t                        EntryInUse;
} dailyload_table_header_t;


typedef struct tag_billing_table_header_t
{
    uint8_t                         IsRolledOver;
    uint16_t                        FirstEntryIndex;
    uint16_t                        EntryInUse;
} billing_table_header_t;

typedef struct tag_billing_backup_data
{
    float32_t acc_active;
    float32_t acc_apparent;
} billing_backup_data_t;

#if(defined( BLOCKLOAD_AVERAGE_CALCULATION ) && BLOCKLOAD_AVERAGE_CALCULATION == 1)
typedef struct tag_block_backup_data
{
    uint32_t  Counter;
    float32_t Current_R;
    float32_t Current_Y;
    float32_t Current_B;
    float32_t Voltage_R;
    float32_t Voltage_Y;
    float32_t Voltage_B;
    float32_t OldEnergykWhImport;
    float32_t OldEnergykVAhImport;
    float32_t OldEnergykWhExport;
    float32_t OldEnergykVAhExport;
} block_backup_data_t;
#endif /* BLOCKLOAD_AVERAGE_CALCULATION */

typedef uint32_t block_storage_type_t;

/* Memory map */

/* BLOCKLOAD */
#define BLOCKLOAD_BACKUP_DATA_ADDR          (BLOCKLOAD_BACKUP_DATA_REGION_ADDR)
#define BLOCKLOAD_BACKUP_DATA_SIZE          (sizeof(block_backup_data_t))

#define BLOCKLOAD_TABLE_HEADER_ADDR         (BLOCKLOAD_BACKUP_DATA_ADDR + BLOCKLOAD_BACKUP_DATA_SIZE)
#define BLOCKLOAD_TABLE_HEADER_SIZE         (sizeof(blockload_table_header_t))

#define BLOCKLOAD_PERIOD_ADDR               (BLOCKLOAD_TABLE_HEADER_ADDR + BLOCKLOAD_TABLE_HEADER_SIZE)
#define BLOCKLOAD_PERIOD_SIZE               (sizeof(uint32_t))

/* DAILYLOAD */
#define DAILYLOAD_TABLE_HEADER_ADDR         (DAILYLOAD_BACKUP_DATA_REGION_ADDR)
#define DAILYLOAD_TABLE_HEADER_SIZE         (sizeof(dailyload_table_header_t))

/* BILLING */
#define BILLING_BACKUP_DATA_ADDR            (BILLING_BACKUP_DATA_REGION_ADDR)
#define BILLING_BACKUP_DATA_SIZE            (sizeof(billing_table_header_t))

#define BILLING_TABLE_HEADER_ADDR           (BILLING_BACKUP_DATA_ADDR + BILLING_BACKUP_DATA_SIZE)
#define BILLING_TABLE_HEADER_SIZE           (sizeof(blockload_table_header_t))

#define BILLING_POWER_ON_DURATION_ADDR      (BILLING_TABLE_HEADER_ADDR + BILLING_TABLE_HEADER_SIZE)
#define BILLING_POWER_ON_DURATION_SIZE      (sizeof(uint32_t))

#define BILLING_COUNTER_ADDR                (BILLING_POWER_ON_DURATION_ADDR + BILLING_POWER_ON_DURATION_SIZE)
#define BILLING_COUNTER_SIZE                (sizeof(uint32_t))

#define METER_POWER_ON_DURATION_ADDR        (BILLING_COUNTER_ADDR + BILLING_COUNTER_SIZE)
#define METER_POWER_ON_DURATION_SIZE        (sizeof(uint32_t))

#define STORAGE_RESOLUTION                  (1000)

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/
uint32_t g_billing_counter = 0u;                          /* Billing counter */
uint32_t g_meter_power_off_duration = 0u;
uint32_t g_meter_power_on_duration = 0u;
uint32_t g_billing_power_on_duration = 0u;

static uint8_t g_meter_wakup_checked = FALSE;

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

/******************************************************
 * Private functions prototype
 *****************************************************/

static uint8_t IsBlockLoadPeriodEnd(void);
static uint8_t IsDailyLoadPeriodEnd(void);
static uint8_t IsBillingScheduleEnd(void);

static uint8_t R_LOADSURVEY_RecordDailyLoad(void);

static void ClearRow(uint16_t row_id);
static uint32_t GetCurrentRow(void);
static void AddNewRow(rtc_counter_value_t *p_rtc_value);
static void PrepareBufferRow(void);
static uint8_t ClearStorageRegion(uint32_t addr, uint16_t size);

static uint16_t GetNumOfEntriesPerRow(void);

static void GetBlockloadFromSnapshot(
    one_block_storage_t *p_blockload, 
    EM_INST_READ_PARAMS *p_snapshot
);

static void R_LOADSURVEY_CalculateAveragePF(
    float32_t *p_out_data,
    float32_t  acc_active,
    float32_t  acc_apparent
);

static void ExtractStorageDataToBlockload(
    r_block_load_t      *p_BlockLoad,
    r_loadsurvey_rtc_t  *p_capture_time,
    one_block_storage_t *p_storage_data
);

static void ToRTCDriverValue(rtc_counter_value_t *p_out, r_loadsurvey_rtc_t *p_in);
static int8_t CompareDateTime(rtc_counter_value_t *p_rtc_1, rtc_counter_value_t *p_rtc_2);

static void R_BILLING_OnBillGenerated(void);
static void R_LOADSURVEY_RecordBilling(void);

void R_LOADSURVEY_CheckBlockloadOnWakeup(void);
void R_LOADSURVEY_CheckBlockloadOnWakeup(void);
static uint8_t R_LOADSURVEY_RecordMissingDay(void);
static uint8_t R_LOADSURVEY_RecordMissingDay(void);

static void AccumulateBlockParameters(void);
static uint8_t R_BLOCKLOAD_TransferFlashBlockToEeprom(void);
static uint8_t R_BLOCKLOAD_TransferEepromToFlash(void);

static void check_and_fill_empty_entry_on_meterwakeup(void);

/******************************************************
 * Private variables
 *****************************************************/
static const st_table_config_t g_bl_table_header_config =
{
    /* TableTimeCaptureStartAddr   = */ BLOCKLOAD_STORAGE_BASE_ADDR,
	/* TableStartAddr   		   = */ (BLOCKLOAD_STORAGE_BASE_ADDR + (BLOCKLOAD_MAX_ROW + 1) * sizeof(r_loadsurvey_rtc_t)),
    /* MaxEntries                  = */ BLOCKLOAD_MAX_ENTRIES,
    /* MaxRow                      = */ (BLOCKLOAD_MAX_ROW + 1),
    /* LogSize                     = */ sizeof(one_block_storage_t),
    /* CaptureTimeSize             = */ sizeof(r_loadsurvey_rtc_t)
};

static const dailyload_table_config_t g_dl_table_header_config =
{
	/* TableStartAddr   		   = */ DAILYLOAD_STORAGE_BASE_ADDR,
    /* MaxEntries                  = */ DAILYLOAD_MAX_ROW,
    /* LogSize                     = */ sizeof(one_daily_log_storage)
};

static const billing_table_config_t g_billing_table_header_config =
{
	/* TableStartAddr   		   = */ BILLING_STORAGE_BASE_ADDR,
    /* MaxEntries                  = */ BILLING_MAX_ROW,
    /* LogSize                     = */ sizeof(one_billing_log_storage)
};

static blockload_table_header_t g_bl_table_header =
{
	/* IsRolledOver  = */       0,
    /* IsBackWard  = */         0,
    /* IsAbnormal  = */         0,
    /* FirstRowIndex = */       0,
    /* RowInUse      = */       0,
    /* ColumnInUse   = */       0
};

static dailyload_table_header_t g_dl_table_header =
{
	/* IsRolledOver     = */    0,
    /* FirstEntryIndex  = */    0,
    /* EntryInUse       = */    0
};

static billing_table_header_t g_billing_table_header =
{
	/* IsRolledOver     = */    0,
    /* FirstEntryIndex  = */    0,
    /* EntryInUse       = */    0
};


static rtc_counter_value_t g_last_capture_time;

uint32_t g_blockload_capture_period = BLOCKLOAD_CAPTURE_PERIOD_DEFAULT;

/* Max number of entry per day */
static const uint16_t g_number_entry_per_row =  (24*60) / R_BLOCKLOAD_CAPTURE_INTERVAL;   // (24h*60min / 15 mins) = 96

static block_backup_data_t g_block_backup_data;

static billing_backup_data_t g_billing_backup_data =
{
    0.0f,
    0.0f
};

const uint16_t g_blockload_capture_period_default		= BLOCKLOAD_CAPTURE_PERIOD_DEFAULT;

uint8_t g_is_season_changed = FALSE;

rtc_counter_value_t g_billing_date;

/******************************************************************************
* Function Name : R_BLOCKLOAD_Reset
* Interface     : uint8_t R_BLOCKLOAD_Reset(void)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_BLOCKLOAD_Reset(void)
{
    memset(&g_bl_table_header, 0, sizeof(g_bl_table_header));
	
    R_BLOCKLOAD_Format();

    memset(&g_last_capture_time, 0, sizeof(rtc_counter_value_t));
    
    g_block_backup_data.OldEnergykWhImport  = R_TARIFF_GetImportActiveEnergyTotal();
    g_block_backup_data.OldEnergykVAhImport = R_TARIFF_GetImportApparentEnergyTotal();
    g_block_backup_data.OldEnergykWhExport  = R_TARIFF_GetExportActiveEnergyTotal();
    g_block_backup_data.OldEnergykVAhExport = R_TARIFF_GetExportApparentEnergyTotal();

    g_block_backup_data.Counter = 0;
	g_block_backup_data.Current_R = 0;
    g_block_backup_data.Current_Y = 0;
    g_block_backup_data.Current_B = 0;
	
    g_block_backup_data.Voltage_R = 0;
    g_block_backup_data.Voltage_Y = 0;
    g_block_backup_data.Voltage_B = 0;

	R_LOADSURVEY_AccumulateCurrentBlock();
    
    return TRUE;
}

/******************************************************************************
* Function Name : R_DAILYLOAD_Reset
* Interface     : uint8_t R_DAILYLOAD_Reset(void)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DAILYLOAD_Reset(void)
{
    g_dl_table_header.EntryInUse = 0;
    g_dl_table_header.FirstEntryIndex = 0;
    g_dl_table_header.IsRolledOver = 0;

    return TRUE;
}

/******************************************************************************
* Function Name : R_BILLING_ManualCapture
* Interface     : uint8_t R_BILLING_ManualCapture(void)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_BILLING_ManualCapture(void)
{
    return TRUE; 
}

/******************************************************************************
* Function Name : R_BILLING_Capture
* Interface     : uint8_t R_BILLING_Capture(void)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_BILLING_Capture(void)
{
    return TRUE;
}

/******************************************************************************
* Function Name : R_BILLING_Reset
* Interface     : uint8_t R_BILLING_Reset(void)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_BILLING_Reset(void)
{
    g_billing_table_header.EntryInUse = 0;
    g_billing_table_header.FirstEntryIndex = 0;
    g_billing_table_header.IsRolledOver = 0;
    
    return TRUE;
}

/******************************************************************************
* Function Name : R_LOADSURVEY_Format
* Interface     : void R_LOADSURVEY_Format(void)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
uint8_t R_LOADSURVEY_Format(void)
{
    uint8_t format_result = STORAGE_OK;

    R_BLOCKLOAD_Format();
    R_DAILYLOAD_Format();
    format_result = R_BILLING_Format();

    return (format_result);
}

/******************************************************************************
* Function Name : R_LOADSURVEY_Backup
* Interface     : uint8_t R_LOADSURVEY_Backup(void)
* Description   :
* Arguments     :
* Return Value  : uint8_t: (0) is OK; else is ERROR
******************************************************************************/
uint8_t R_LOADSURVEY_Backup(void)
{
    EPR_Write(BLOCKLOAD_BACKUP_DATA_ADDR          , (uint8_t *)&g_block_backup_data              , sizeof(block_backup_data_t));
    EPR_Write(BLOCKLOAD_TABLE_HEADER_ADDR         , (uint8_t *)&g_bl_table_header                , sizeof(blockload_table_header_t));
    EPR_Write(BLOCKLOAD_PERIOD_ADDR               , (uint8_t *)&g_blockload_capture_period       , sizeof(uint16_t));

    EPR_Write(DAILYLOAD_TABLE_HEADER_ADDR         , (uint8_t *)&g_dl_table_header                , sizeof(dailyload_table_header_t));

    EPR_Write(BILLING_BACKUP_DATA_ADDR            , (uint8_t *)&g_billing_backup_data            , sizeof(billing_backup_data_t));
    EPR_Write(BILLING_TABLE_HEADER_ADDR           , (uint8_t *)&g_billing_table_header           , sizeof(billing_table_header_t));

    EPR_Write(METER_POWER_ON_DURATION_ADDR        , (uint8_t *)&g_meter_power_on_duration  , sizeof(uint32_t));
    EPR_Write(BILLING_POWER_ON_DURATION_ADDR      , (uint8_t *)&g_billing_power_on_duration, sizeof(uint32_t));

    R_BILLING_Backup();

    return STORAGE_OK;
}

/******************************************************************************
* Function Name : R_LOADSURVEY_Restore
* Interface     : void R_LOADSURVEY_Restore(void)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_LOADSURVEY_Restore(void)
{
    EPR_Read(BLOCKLOAD_BACKUP_DATA_ADDR          , (uint8_t *)&g_block_backup_data        , sizeof(block_backup_data_t));
    EPR_Read(BLOCKLOAD_TABLE_HEADER_ADDR         , (uint8_t *)&g_bl_table_header          , sizeof(blockload_table_header_t));
    EPR_Read(BLOCKLOAD_PERIOD_ADDR               , (uint8_t *)&g_blockload_capture_period , sizeof(uint16_t                    ));

    EPR_Read(DAILYLOAD_TABLE_HEADER_ADDR         , (uint8_t *)&g_dl_table_header          , sizeof(dailyload_table_header_t));

    EPR_Read(BILLING_BACKUP_DATA_ADDR            , (uint8_t *)&g_billing_backup_data      , sizeof(billing_backup_data_t));
    EPR_Read(BILLING_TABLE_HEADER_ADDR           , (uint8_t *)&g_billing_table_header     , sizeof(billing_table_header_t));

    EPR_Read(METER_POWER_ON_DURATION_ADDR        , (uint8_t *)&g_meter_power_on_duration  , sizeof(uint32_t));
    EPR_Read(BILLING_POWER_ON_DURATION_ADDR      , (uint8_t *)&g_billing_power_on_duration, sizeof(uint32_t));

    /* Validate invalid restored data */
    if (g_blockload_capture_period == 0)
    {
        g_blockload_capture_period = BLOCKLOAD_CAPTURE_PERIOD_DEFAULT;
        EPR_Write(BLOCKLOAD_PERIOD_ADDR , (uint8_t *)&g_blockload_capture_period , sizeof(uint16_t));
    }

    R_BILLING_Restore();

    return 0;
}
/******************************************************************************
* Function Name : R_BLOCKLOAD_SPI_Format
* Interface     : void R_BLOCKLOAD_SPI_Format(void)
* Description   : Erase all 4KBs blocks on Serial Flash
* Return Value  : Success (TRUE) or failure (FALSE)
******************************************************************************/
uint8_t R_BLOCKLOAD_SPI_Format(void)
{
	uint8_t 				status;
	uint32_t 				addr;

	/* Clear entire entries table (0x80000 to 0x151FFF) */
	for (addr = 0u;
		 addr < (uint32_t)BLOCKLOAD_ENTRIES_TABLE_SIZE;
		 addr += (uint16_t)SFL_DEVICE_MINIMUM_BLOCK_SIZE)
	{
        
		status = BL_SFL_DeviceErase4KB(addr + BLOCKLOAD_ENTRIES_TABLE_START_ADDR);
		if (status != SFL_OK) 
		{
			return FALSE;
		}

		R_WDT_Restart();
	}
    
    if (status != 0x00) 
	{
		return FALSE;
	}

	return TRUE;
}


/******************************************************************************
* Function Name : R_BLOCKLOAD_SPI_ClearRow
* Interface     : void R_BLOCKLOAD_SPI_ClearRow(uint32_t row_index)
* Description   : Clear load survey table row
* Return Value  : Success (TRUE) or failure (FALSE)
******************************************************************************/
uint8_t R_BLOCKLOAD_SPI_ClearRow(uint32_t row_index)
{
    // Clear Data in SPI FLash
    uint32_t start_addr = BLOCKLOAD_ENTRIES_TABLE_START_ADDR;
    uint32_t size = 0u;
    uint32_t addr = 0u;
    uint8_t  status;

    size = BLOCKLOAD_SERIAL_FLASH_BLOCK_SIZE;
    start_addr = BLOCKLOAD_ENTRIES_TABLE_START_ADDR + row_index * BLOCKLOAD_SERIAL_FLASH_BLOCK_SIZE;

	/* Clear entire entries table (0x80000 to 0x151FFF) */
	for (addr = start_addr;
		 addr < (start_addr + size);
		 addr += SFL_DEVICE_MINIMUM_BLOCK_SIZE)
	{
		status = BL_SFL_DeviceErase4KB(addr);
		if (status != SFL_OK) 
		{
			return FALSE;
		}

		R_WDT_Restart();
	}

	if (status != 0x00) 
	{
		return FALSE;
	}

	return TRUE;
}
/******************************************************************************
* Function Name : R_BLOCKLOAD_Format
* Interface     : void R_BLOCKLOAD_Format(void)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_BLOCKLOAD_Format(void)
{   
    uint32_t    row_addr_eeprom = 0;
    uint32_t    row_size_eeprom = 0;
    uint32_t    row_addr = 0;
    uint32_t    row_size = 0;

    R_BLOCKLOAD_SPI_Format();

    // Clear Data in Epprom
	row_size_eeprom = g_number_entry_per_row * g_bl_table_header_config.LogSize;
	row_addr_eeprom = g_bl_table_header_config.TableStartAddr;

	ClearStorageRegion(row_addr_eeprom, row_size_eeprom);     // Prepare row, ~ 2 * 32 * 48 bytes = 3072 bytes

    // Clear date
	row_addr = g_bl_table_header_config.TableTimeCaptureStartAddr;
	row_size = g_bl_table_header_config.MaxRow * g_bl_table_header_config.CaptureTimeSize;
	ClearStorageRegion(row_addr, row_size);   

    EPR_Write(
        BLOCKLOAD_PERIOD_ADDR,                              // Addr
        (uint8_t *)&g_blockload_capture_period_default,     // Buff
        sizeof(uint16_t)                                    // Size
    );
    return 0;
}


/******************************************************************************
* Function Name : R_BLOCKLOAD_Backup
* Interface     : void R_BLOCKLOAD_Backup(void)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_BLOCKLOAD_Backup(void)
{
    /* TODO */
    return 0;
}


/******************************************************************************
* Function Name : R_BLOCKLOAD_Restore
* Interface     : void R_BLOCKLOAD_Restore(void)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_BLOCKLOAD_Restore(void)
{
    return 0;
}

/******************************************************************************
* Function Name : R_DAILYLOAD_Format
* Interface     : uint8_t R_DAILYLOAD_Format(void)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DAILYLOAD_Format(void)
{
    /* TODO */
    return 0;
}

/******************************************************************************
* Function Name : R_DAILYLOAD_Backup
* Interface     : uint8_t R_DAILYLOAD_Backup(void)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DAILYLOAD_Backup(void)
{
    /* TODO */
    return 0;
}

/******************************************************************************
* Function Name : R_DAILYLOAD_Restore
* Interface     : uint8_t R_DAILYLOAD_Restore(void)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DAILYLOAD_Restore(void)
{
    /* TODO */
    return 0;
}



/******************************************************************************
* Function Name : R_BILLING_Format
* Interface     : void R_BILLING_Format(void)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_BILLING_Format(void)
{
    g_billing_backup_data.acc_active = R_TARIFF_GetImportActiveEnergyTotal();
    g_billing_backup_data.acc_apparent = R_TARIFF_GetImportApparentEnergyTotal();

    return STORAGE_OK;
}


/******************************************************************************
* Function Name : R_BILLING_Backup
* Interface     : void R_BILLING_Backup(void)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_BILLING_Backup(void)
{
    /* TODO */
    
    /* Billing counter */

    // Billing counter is increase occasionally, just 1 or 2 times each month
    // So, Don't backup at critical time when power off
	/*
     *   EPR_Write(BILLING_COUNTER_ADDR, 
     *           (uint8_t *)&g_billing_counter,
     *           sizeof(uint32_t));
     */

    return 0;
}

/******************************************************************************
* Function Name : R_BILLING_Restore
* Interface     : void R_BILLING_Restore(void)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_BILLING_Restore(void)
{
    /* TODO */

    /* Billing counter */
	EPR_Read(BILLING_COUNTER_ADDR, 
                (uint8_t *)&g_billing_counter,
                sizeof(uint32_t));

    return 0;
}


static int8_t CompareDate(rtc_counter_value_t *p_rtc_1, rtc_counter_value_t *p_rtc_2);
/******************************************************************************
* Function Name : CompareDate
* Interface     : int8_t CompareDate(rtc_counter_value_t *p_rtc_1, rtc_counter_value_t *p_rtc_2)
* Description   :
* Arguments     :
* Return Value  : int8_t
******************************************************************************/
static int8_t CompareDate(rtc_counter_value_t *p_rtc_1, rtc_counter_value_t *p_rtc_2)
{   
	int8_t diff = 0;
    if (p_rtc_1->year == p_rtc_2->year &&
        p_rtc_1->month == p_rtc_2->month &&
        p_rtc_1->day == p_rtc_2->day
        )   
    {
        return 0;
    }
	
	diff = p_rtc_1->year - p_rtc_2->year;
    if (diff != 0)
    {
        return (diff);
    }

    diff = p_rtc_1->month - p_rtc_2->month;
    if (diff != 0)
    {
        return (diff);
    }
	
    diff = (p_rtc_1->day - p_rtc_2->day);
    if (diff != 0)
	{
        return (diff);
    }

    return (0);
}

/******************************************************************************
* Function Name : ToRTCDriverValue
* Interface     : void ToRTCDriverValue(rtc_counter_value_t *p_out, r_loadsurvey_rtc_t *p_in)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
static void ToRTCDriverValue(rtc_counter_value_t *p_out, r_loadsurvey_rtc_t *p_in)
{
    if (p_out != NULL && p_in != NULL)
    {
        p_out->sec   = p_in->sec;
        p_out->min   = p_in->min;
        p_out->hour  = p_in->hour;
        p_out->day   = p_in->day;
        p_out->week  = p_in->week;
        p_out->month = p_in->month;
        p_out->year  = p_in->year;
    }
}

/******************************************************************************
* Function Name : CompareDateTime
* Interface     : int8_t CompareDateTime(rtc_counter_value_t *p_rtc_1, rtc_counter_value_t *p_rtc_2)
* Description   :
* Arguments     :
* Return Value  : int8_t  (-1) Backward, (1) Forward
******************************************************************************/
static int8_t CompareDateTime(rtc_counter_value_t *p_rtc_1, rtc_counter_value_t *p_rtc_2)
{
    int16_t compare_result = CompareDate(p_rtc_1, p_rtc_2);
    uint32_t total_time1, total_time2;
    if (compare_result < 0)
    {
        return (-1);
    }
    else if (compare_result > 0)
    {
        return (1);
    }
    
    total_time1 = (p_rtc_1->hour*60+p_rtc_1->min)*60 + p_rtc_1->sec;
    total_time2 = (p_rtc_2->hour*60+p_rtc_2->min)*60 + p_rtc_2->sec;

    if (total_time1 == total_time2)
    {
        return (0);
    }
    else if (total_time1 > total_time2)
    {
        return (1);
    }

    return (-1);
}
/******************************************************************************
* Function Name : R_BLOCKLOAD_Get_EntryId_ByDateTime
* Interface     : uint8_t R_BLOCKLOAD_Get_EntryId_ByDateTime
* Description   : Find the first index of entry that have capture_date_time larger than request rtc
* Arguments     : rtc_counter_value_t *p_request_rtc_start : Requested RTC value for searching
*                 uint8_t divider: Block divider
*                 uint32_t *p_entry_id_out: Output of the searching
* Return Value  : uint8_t
*                 Return TRUE  (1) if found any entry that have date_time larger than request rtc value
*                 Return FALSE (0) if all entry in storage have capture_date_time smaller than request rtc value
******************************************************************************/
uint8_t R_BLOCKLOAD_Get_EntryId_ByDateTime(
    rtc_counter_value_t *p_request_rtc_start,
    uint8_t              divider,
    uint32_t            *p_entry_id_out)
{    
    uint16_t row_id;
    uint16_t row_id_rolled;
    uint16_t col_id;
    uint32_t row_addr;
    uint32_t entry_id;
    uint8_t found = FALSE;

    rtc_counter_value_t rtc_captured;
    /* Parameter checking */
    if (p_entry_id_out == NULL ||
        p_request_rtc_start == NULL ||
        divider == 0)
    {
        return FALSE;
    }
    
    for (row_id = 0; row_id < (g_bl_table_header.RowInUse+1); row_id++)
    {
        row_id_rolled = (row_id + g_bl_table_header.FirstRowIndex) % g_bl_table_header_config.MaxRow;

        /* Update new capture time */
        row_addr = g_bl_table_header_config.TableTimeCaptureStartAddr + row_id_rolled * g_bl_table_header_config.CaptureTimeSize;
        EPR_Read(row_addr, (uint8_t *)&rtc_captured, g_bl_table_header_config.CaptureTimeSize);
		
        if (CompareDate(&rtc_captured, p_request_rtc_start) == 0)
        {
            col_id = (p_request_rtc_start->hour * 60 + p_request_rtc_start->min) / R_BLOCKLOAD_CAPTURE_INTERVAL;
            if ((p_request_rtc_start->hour * 60 + p_request_rtc_start->min) % R_BLOCKLOAD_CAPTURE_INTERVAL != 0)
            {
                col_id++;
            }

            /* Last row may not have full entry */
            if (row_id == (g_bl_table_header.RowInUse+1))
            {
                if  ((col_id+1) > g_bl_table_header.ColumnInUse)
                {
                    found = FALSE;
                    break;
                }
            }

            found = TRUE;
            break;
        }
    }

    if (found == TRUE)
    {
        entry_id = row_id * g_number_entry_per_row + col_id;

        /* Apply divider */
        entry_id = entry_id / divider;

        /* Return the result */
        *p_entry_id_out = entry_id;

        return TRUE;
    }

    /* Not found? */
    return FALSE;
}
/******************************************************************************
* Function Name : R_BLOCKLOAD_Get_StartEntryId_FromDateTime
* Interface     : uint8_t R_BLOCKLOAD_Get_StartEntryId_FromDateTime
* Description   : Find the first index of entry that have capture_date_time larger than request rtc
* Arguments     : rtc_counter_value_t *p_request_rtc_start : Requested RTC value for searching
*                 uint8_t divider: Block divider
*                 uint32_t *p_entry_id_out: Output of the searching
* Return Value  : uint8_t
*                 Return TRUE  (1) if found any entry that have date_time larger than request rtc value
*                 Return FALSE (0) if all entry in storage have capture_date_time smaller than request rtc value
******************************************************************************/
uint8_t R_BLOCKLOAD_Get_StartEntryId_FromDateTime(
    rtc_counter_value_t *p_request_rtc_start,
    uint8_t              divider,
    uint32_t            *p_entry_id_out)
{    
    uint16_t row_id;
    uint16_t row_id_rolled;
    uint16_t col_id;
    uint32_t row_addr;
    uint32_t entry_id;
    uint8_t found = FALSE;

    rtc_counter_value_t rtc_captured;
    /* Parameter checking */
    if (p_entry_id_out == NULL ||
        p_request_rtc_start == NULL ||
        divider == 0)
    {
        return FALSE;
    }
    
    for (row_id = 0; row_id < (g_bl_table_header.RowInUse+1); row_id++)
    {
        row_id_rolled = (row_id + g_bl_table_header.FirstRowIndex) % g_bl_table_header_config.MaxRow;

        /* Update new capture time */
        row_addr = g_bl_table_header_config.TableTimeCaptureStartAddr + row_id_rolled * g_bl_table_header_config.CaptureTimeSize;
        EPR_Read(row_addr, (uint8_t *)&rtc_captured, g_bl_table_header_config.CaptureTimeSize);
		
        if (CompareDate(&rtc_captured, p_request_rtc_start) >= 0)
        {
            col_id = (p_request_rtc_start->hour * 60 + p_request_rtc_start->min) / R_BLOCKLOAD_CAPTURE_INTERVAL;
            if ((p_request_rtc_start->hour * 60 + p_request_rtc_start->min) % R_BLOCKLOAD_CAPTURE_INTERVAL != 0)
            {
                col_id++;
            }

            /* Last row may not have full entry */
            if (row_id == (g_bl_table_header.RowInUse+1))
            {
                if  ((col_id+1) > g_bl_table_header.ColumnInUse)
                {
                    found = FALSE;
                    break;
                }
            }

            found = TRUE;
            break;
        }
    }

    if (found == TRUE)
    {
        entry_id = row_id * g_number_entry_per_row + col_id;

        /* Apply divider */
        entry_id = entry_id / divider;

        /* Return the result */
        *p_entry_id_out = entry_id;

        return TRUE;
    }

    /* Not found? */
    return FALSE;
}

/******************************************************************************
* Function Name : R_BLOCKLOAD_Get_EndEntryId_FromDateTime
* Interface     : uint8_t R_BLOCKLOAD_Get_EndEntryId_FromDateTime
* Description   : Find the last index of entry that have capture_date_time smaller than request rtc
* Arguments     : rtc_counter_value_t *p_request_rtc_start : Requested RTC value for searching
*                 uint8_t divider: Block divider
*                 uint32_t *p_entry_id_out: Output of the searching
* Return Value  : uint8_t
*                 Return TRUE  (1) if found any entry that have date_time smaller than request rtc value
*                 Return FALSE (0) if all entry in storage have capture_date_time larger than request rtc value
******************************************************************************/
uint8_t R_BLOCKLOAD_Get_EndEntryId_FromDateTime(
    rtc_counter_value_t *p_request_rtc_start,
    uint8_t              divider,
    uint32_t            *p_entry_id_out)
{
    int32_t row_id;
    uint16_t row_id_rolled;
    uint16_t col_id;
    uint32_t row_addr;
    uint32_t entry_id;
    uint8_t found = FALSE;

    rtc_counter_value_t rtc_captured;

    /* Parameter checking */
    if (p_entry_id_out == NULL ||
        p_request_rtc_start == NULL ||
        divider == 0)
    {
        return FALSE;
    }
    
    for (row_id = g_bl_table_header.RowInUse - 1; row_id >= 0; row_id--)
    {
        row_id_rolled = (row_id + g_bl_table_header.FirstRowIndex) % g_bl_table_header_config.MaxRow;

        /* Update new capture time */
        row_addr = g_bl_table_header_config.TableTimeCaptureStartAddr + row_id_rolled * g_bl_table_header_config.CaptureTimeSize;
        EPR_Read(row_addr, (uint8_t *)&rtc_captured, g_bl_table_header_config.CaptureTimeSize);

        if (CompareDate(&rtc_captured, p_request_rtc_start) <= 0)
        {
            col_id = (p_request_rtc_start->hour * 60 + p_request_rtc_start->min) / R_BLOCKLOAD_CAPTURE_INTERVAL;
            
            if ((p_request_rtc_start->hour * 60 + p_request_rtc_start->min) % R_BLOCKLOAD_CAPTURE_INTERVAL != 0)
            {
                if (col_id > 0) col_id--;
            }

            /* Last row may not have full entry */
            if (row_id == g_bl_table_header.RowInUse)
            {
                if (col_id > g_bl_table_header.ColumnInUse)
                {
                    col_id = g_bl_table_header.ColumnInUse;
                    if (col_id > 0) col_id--;
                }
            }

            found = TRUE;
            break;
        }
    }

    if (found == TRUE)
    {
        entry_id = row_id * g_number_entry_per_row + col_id;

        /* Apply divider */
        entry_id = entry_id / divider;

        /* Return the result */
        *p_entry_id_out = entry_id;

        return TRUE;
    }

    /* Not found? */
    return FALSE;
}

/******************************************************************************
* Function Name : R_DAILYLOAD_Get_StartEntryId_FromDateTime
* Interface     : uint8_t R_DAILYLOAD_Get_StartEntryId_FromDateTime
* Description   : 
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DAILYLOAD_Get_StartEntryId_FromDateTime(
    rtc_counter_value_t *p_request_rtc_start,
    uint32_t            *p_entry_id_out)
{
    uint16_t i;

    uint16_t entry_id;
    uint16_t row_id_rolled;
    uint16_t col_id;
    uint32_t row_addr;

    uint8_t found = FALSE;

    rtc_counter_value_t capture_time_rtc_value;

    one_daily_log_storage entry_from_storage;

    rtc_counter_value_t rtc_captured;

    /* Parameter checking */
    if (p_entry_id_out == NULL ||
        p_request_rtc_start == NULL)
    {
        return FALSE;
    }
    
    for (entry_id = 0; entry_id < g_dl_table_header.EntryInUse; entry_id++)
    {
        row_id_rolled = (entry_id + g_dl_table_header.FirstEntryIndex) % g_dl_table_header_config.MaxEntries;

        /* Update new capture time */
        row_addr = g_dl_table_header_config.TableStartAddr + row_id_rolled * g_dl_table_header_config.LogSize;
        EPR_Read(row_addr, (uint8_t *)&entry_from_storage, g_dl_table_header_config.LogSize);

        ToRTCDriverValue(&capture_time_rtc_value, &entry_from_storage.CaptureTime);
        if (CompareDateTime(&capture_time_rtc_value, p_request_rtc_start) >= 0)
        {
            found = TRUE;
            break;
        }
    }

    if (found == TRUE)
    {
        /* Return the result */
        *p_entry_id_out = entry_id;

        return TRUE;
    }

    /* Not found? */
    return FALSE;
}

/******************************************************************************
* Function Name : R_DAILYLOAD_Get_EndEntryId_FromDateTime
* Interface     : uint8_t R_DAILYLOAD_Get_EndEntryId_FromDateTime
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DAILYLOAD_Get_EndEntryId_FromDateTime(
    rtc_counter_value_t *p_request_rtc_start,
    uint32_t            *p_entry_id_out)
{
    uint16_t i;

    int32_t entry_id;
    uint16_t row_id_rolled;
    uint16_t col_id;
    uint32_t row_addr;

    uint8_t found = FALSE;

    one_daily_log_storage entry_from_storage;

    rtc_counter_value_t rtc_captured;
    rtc_counter_value_t capture_time_rtc_value;

    /* Parameter checking */
    if (p_entry_id_out == NULL ||
        p_request_rtc_start == NULL)
    {
        return FALSE;
    }
    
    for (entry_id = g_dl_table_header.EntryInUse - 1; entry_id >= 0; entry_id--)
    {
        row_id_rolled = (entry_id + g_dl_table_header.FirstEntryIndex) % g_dl_table_header_config.MaxEntries;

        /* Update new capture time */
        row_addr = g_dl_table_header_config.TableStartAddr + row_id_rolled * g_dl_table_header_config.LogSize;
        EPR_Read(row_addr, (uint8_t *)&entry_from_storage, g_dl_table_header_config.LogSize);

        ToRTCDriverValue(&capture_time_rtc_value, &entry_from_storage.CaptureTime);
        if (CompareDateTime(&capture_time_rtc_value, p_request_rtc_start) <= 0)
        {
            found = TRUE;
            break;
        }
    }

    if (found == TRUE)
    {
        /* Return the result */
        *p_entry_id_out = entry_id;

        return TRUE;
    }

    /* Not found? */
    return FALSE;
}

/******************************************************************************
* Function Name : R_BILLING_Get_StartEntryId_FromDateTime
* Interface     : uint8_t R_BILLING_Get_StartEntryId_FromDateTime
* Description   : 
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_BILLING_Get_StartEntryId_FromDateTime(
    rtc_counter_value_t *p_request_rtc_start,
    uint32_t            *p_entry_id_out)
{
    uint16_t i;

    uint16_t entry_id;
    uint16_t row_id_rolled;
    uint16_t col_id;
    uint32_t row_addr;
    uint8_t found = FALSE;

    one_billing_log_storage entry_from_storage;

    rtc_counter_value_t rtc_captured;
    rtc_counter_value_t capture_time_rtc_value;

    /* Parameter checking */
    if (p_entry_id_out == NULL ||
        p_request_rtc_start == NULL)
    {
        return FALSE;
    }
    
    for (entry_id = 0; entry_id < g_billing_table_header.EntryInUse; entry_id++)
    {
        row_id_rolled = (entry_id + g_billing_table_header.FirstEntryIndex) % g_billing_table_header_config.MaxEntries;

        /* Update new capture time */
        row_addr = g_billing_table_header_config.TableStartAddr + row_id_rolled * g_billing_table_header_config.LogSize;
        EPR_Read(row_addr, (uint8_t *)&entry_from_storage, g_billing_table_header_config.LogSize);

        ToRTCDriverValue(&capture_time_rtc_value, &entry_from_storage.CaptureTime);
        if (CompareDateTime(&capture_time_rtc_value, p_request_rtc_start) >= 0)
        {
            found = TRUE;
            break;
        }
    }

    if (found == TRUE)
    {
        /* Return the result */
        *p_entry_id_out = entry_id;

        return TRUE;
    }

    /* Not found? */
    return FALSE;
}

/******************************************************************************
* Function Name : R_BILLING_Get_EndEntryId_FromDateTime
* Interface     : uint8_t R_BILLING_Get_EndEntryId_FromDateTime
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_BILLING_Get_EndEntryId_FromDateTime(
    rtc_counter_value_t *p_request_rtc_start,
    uint32_t            *p_entry_id_out)
{
    uint16_t i;

    int32_t entry_id;
    uint16_t row_id_rolled;
    uint16_t col_id;
    uint32_t row_addr;
    uint8_t found = FALSE;

    one_billing_log_storage entry_from_storage;

    rtc_counter_value_t rtc_captured;
    rtc_counter_value_t capture_time_rtc_value;

    /* Parameter checking */
    if (p_entry_id_out == NULL ||
        p_request_rtc_start == NULL)
    {
        return FALSE;
    }
    
    for (entry_id = g_billing_table_header.EntryInUse - 1; entry_id >= 0; entry_id--)
    {
        row_id_rolled = (entry_id + g_billing_table_header.FirstEntryIndex) % g_billing_table_header_config.MaxEntries;

        /* Update new capture time */
        row_addr = g_billing_table_header_config.TableStartAddr + row_id_rolled * g_billing_table_header_config.LogSize;
        EPR_Read(row_addr, (uint8_t *)&entry_from_storage, g_billing_table_header_config.LogSize);

        ToRTCDriverValue(&capture_time_rtc_value, &entry_from_storage.CaptureTime);
        if (CompareDateTime(&capture_time_rtc_value, p_request_rtc_start) <= 0)
        {
            found = TRUE;
            break;
        }
    }

    if (found == TRUE)
    {
        /* Return the result */
        *p_entry_id_out = entry_id;

        return TRUE;
    }

    /* Not found? */
    return FALSE;
}

/**********************************************************************************************************************
* Function Name: is_rolledover
* Description  :
* Arguments    : None
* Return Value : None
*********************************************************************************************************************/
static uint8_t is_rolledover(void)
{
    return g_bl_table_header.IsRolledOver;
}

/******************************************************************************
* Function Name : GetNumOfEntriesPerRow
* Interface     : uint16_t GetNumOfEntriesPerRow(void)
* Description   :
* Arguments     :
* Return Value  : uint16_t
******************************************************************************/
static uint16_t GetNumOfEntriesPerRow(void)
{
    return (24*60) / R_BLOCKLOAD_CAPTURE_INTERVAL;
}

/******************************************************************************
* Function Name : ClearStorageRegion
* Interface     : uint8_t ClearStorageRegion(uint32_t addr, uint16_t size)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
static uint8_t ClearStorageRegion(uint32_t addr, uint16_t size)
{
    uint32_t    eeprom_addr;
    uint32_t    last_addr;
    uint8_t     empty_page[EPR_DEVICE_PAGESIZE];

    uint16_t    item_index;

    /* Create empty_page */
    memset(empty_page, 0, sizeof(empty_page));

    eeprom_addr = addr;
    last_addr = addr + size;
    if (last_addr > EPR_DEVICE_SIZE)
    {
        last_addr = EPR_DEVICE_SIZE;
    }

    while (eeprom_addr < last_addr)
    {
        if ((last_addr - eeprom_addr) < EPR_DEVICE_PAGESIZE) {
            size = last_addr - eeprom_addr;
        }
        else {
            size = EPR_DEVICE_PAGESIZE;
        }

        if (EPR_Write(eeprom_addr, empty_page, size) != EPR_OK)
        {
            return FALSE;
        }

        eeprom_addr += size;

        R_WDT_Restart();
    }

    return TRUE;
}

/******************************************************************************
* Function Name : R_BLOCKLOAD_GetProfileEntry
* Interface     : uint8_t R_BLOCKLOAD_GetProfileEntry(uint32_t *p_OutData, uint8_t divider);
* Description   : Get profile entry
* Arguments     : uint32_t *p_OutData
*               : uint8_t divider
* Function Calls:
* Return Value  : TRUE (1) : Get success, FALSE (0): Get failed
******************************************************************************/
uint8_t R_BLOCKLOAD_GetProfileEntry(uint32_t *p_OutData, uint8_t divider)
{
	*p_OutData = ((g_bl_table_header_config.MaxEntries - g_number_entry_per_row) /divider);

	return TRUE;
}

/******************************************************************************
* Function Name : R_DAILYLOAD_GetProfileEntry
* Interface     : uint8_t R_DAILYLOAD_GetProfileEntry(uint32_t *p_OutData);
* Description   : Get profile entry
* Arguments     : uint32_t *p_OutData
* Function Calls:
* Return Value  : TRUE (1) : Get success, FALSE (0): Get failed
******************************************************************************/
uint8_t R_DAILYLOAD_GetProfileEntry(uint32_t *p_OutData)
{
	*p_OutData = g_dl_table_header_config.MaxEntries;

	return TRUE;
}

/******************************************************************************
* Function Name : R_BILLING_GetProfileEntry
* Interface     : uint8_t R_BILLING_GetProfileEntry(uint32_t *p_OutData);
* Description   : Get profile entry
* Arguments     : uint32_t *p_OutData
* Function Calls:
* Return Value  : TRUE (1) : Get success, FALSE (0): Get failed
******************************************************************************/
uint8_t R_BILLING_GetProfileEntry(uint32_t *p_OutData)
{
	*p_OutData = g_billing_table_header_config.MaxEntries;

	return TRUE;
}

/******************************************************************************
* Function Name : R_BLOCKLOAD_GetEntryInUse
* Interface     : uint8_t R_BLOCKLOAD_GetEntryInUse(uint32_t *p_OutData, uint32_t period);
* Description   : Get entry in use
* Arguments     : uint32_t *p_OutData
* Function Calls:
* Return Value  : TRUE (1) : Get success, FALSE (0): Get failed
******************************************************************************/
uint8_t R_BLOCKLOAD_GetEntryInUse(uint32_t *p_OutData, uint8_t divider)
{
    uint32_t entry_in_used = 0;
    uint32_t entry_per_day = g_number_entry_per_row;

    if (is_rolledover())
    {
        entry_in_used = g_bl_table_header_config.MaxEntries - g_number_entry_per_row;
    }
    else
    {
        if (g_bl_table_header.RowInUse == 0)
        {
           entry_in_used = g_bl_table_header.ColumnInUse;
        }
        else if (g_bl_table_header.RowInUse < (g_bl_table_header_config.MaxRow - 1))
        {
            entry_in_used = (g_bl_table_header.RowInUse) * entry_per_day + g_bl_table_header.ColumnInUse;
        }
    }

    entry_in_used = (uint16_t) (entry_in_used / (divider));

    *p_OutData = entry_in_used;

    return TRUE;
}   

/******************************************************************************
* Function Name : R_DAILYLOAD_GetEntryInUse
* Interface     : uint8_t R_DAILYLOAD_GetEntryInUse(uint32_t *p_OutData);
* Description   : Get entry in use
* Arguments     : uint32_t *p_OutData
* Function Calls:
* Return Value  : TRUE (1) : Get success, FALSE (0): Get failed
******************************************************************************/
uint8_t R_DAILYLOAD_GetEntryInUse(uint32_t *p_OutData)
{
    *p_OutData = (uint32_t)g_dl_table_header.EntryInUse;
    return TRUE;
}

/******************************************************************************
* Function Name : R_BILLING_GetEntryInUse
* Interface     : uint8_t R_BILLING_GetEntryInUse(uint32_t *p_OutData);
* Description   : Get entry in use
* Arguments     : uint32_t *p_OutData
* Function Calls:
* Return Value  : TRUE (1) : Get success, FALSE (0): Get failed
******************************************************************************/
uint8_t R_BILLING_GetEntryInUse(uint32_t *p_OutData)
{
    *p_OutData = (uint32_t)g_billing_table_header.EntryInUse;
    return TRUE;
}

/******************************************************************************
* Function Name : GetCellAddrInEepr
* Interface     : uint32_t GetCellAddrInEepr(uint32_t entry_index)
* Description   :
* Arguments     :
* Return Value  : uint32_t
******************************************************************************/
static uint32_t GetCellAddrInEepr(uint32_t entry_index)
{
	uint16_t num_entry_per_row = GetNumOfEntriesPerRow();
	uint16_t row;
	uint16_t col;
	uint32_t cell_addr;

	col = (uint16_t)entry_index % num_entry_per_row;

	cell_addr = g_bl_table_header_config.TableStartAddr + g_bl_table_header_config.LogSize * col;
	return cell_addr;
}
/******************************************************************************
* Function Name : GetCellAddrInFlash
* Interface     : uint32_t GetCellAddrInFlash(uint32_t entry_index)
* Description   :
* Arguments     :
* Return Value  : uint32_t
******************************************************************************/
static uint32_t GetCellAddrInFlash(uint32_t entry_index)
{
	uint16_t num_entry_per_row = GetNumOfEntriesPerRow();
	uint16_t row;
	uint16_t col;
	uint32_t cell_addr;

	uint32_t cell_index;

	row = (uint16_t)entry_index / num_entry_per_row;
	col = (uint16_t)entry_index % num_entry_per_row;

    {
        row += g_bl_table_header.FirstRowIndex;
    }

	cell_addr = BLOCKLOAD_ENTRIES_TABLE_START_ADDR + row * BLOCKLOAD_SERIAL_FLASH_BLOCK_SIZE;
    cell_addr += g_bl_table_header_config.LogSize * col;
	return cell_addr;
}
/******************************************************************************
* Function Name : GetCellAddr_ByPeriod
* Interface     : uint32_t GetCellAddr_ByPeriod(uint32_t entry_index, uint16_t period)
* Description   :
* Arguments     :
* Return Value  : uint32_t
******************************************************************************/
static uint32_t GetCellAddr_ByPeriod(uint32_t entry_index, uint16_t period)
{
	uint16_t num_entry_per_row = GetNumOfEntriesPerRow();
	uint16_t row;
	uint16_t col;
	uint32_t cell_addr;

	uint32_t cell_index;

	row = (uint16_t)entry_index / num_entry_per_row;
	col = (uint16_t)entry_index % num_entry_per_row;

    /* Rollover calculation */
    {
        row += g_bl_table_header.FirstRowIndex;
        if (g_bl_table_header.IsRolledOver == TRUE)
        {
            row++;
        }
        row %= g_bl_table_header_config.MaxRow;
    }

	cell_index = row * num_entry_per_row + col;

	cell_addr = g_bl_table_header_config.TableStartAddr + g_bl_table_header_config.LogSize * cell_index;
	return cell_addr;
}

/******************************************************************************
* Function Name : GetCurrentRow
* Description   : Get current row
* Arguments     :
* Return Value  : uint32_t
******************************************************************************/
static uint32_t GetCurrentRow(void)
{
	uint32_t row_index;

	row_index = g_bl_table_header.FirstRowIndex;
	if (g_bl_table_header.IsRolledOver == TRUE)
	{
		row_index++;
	}
	row_index += g_bl_table_header.RowInUse;
	row_index %= g_bl_table_header_config.MaxRow;

    return row_index;
}

/******************************************************************************
* Function Name : ClearRow
* Interface     : void ClearRow(uint16_t row_id)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
static void ClearRow(uint16_t row_id)
{
    uint32_t row_size;
    uint32_t row_addr = 0;

	uint32_t one_entry_size = g_bl_table_header_config.LogSize;
	uint32_t table_base_address = g_bl_table_header_config.TableStartAddr;

    row_size = g_number_entry_per_row * one_entry_size;
    row_addr = table_base_address + (row_id * row_size);

    /* Prepare next row */
    ClearStorageRegion(row_addr, row_size);     // Clear buffer row
}

/******************************************************************************
* Function Name : GetCurrentRow
* Interface     : uint32_t GetCurrentRow(void)
* Description   :
* Arguments     :
* Return Value  : uint32_t
******************************************************************************/
static uint32_t GetRowIdToWrite(void)
{
	uint32_t row_index;

	row_index = g_bl_table_header.FirstRowIndex;

	row_index += g_bl_table_header.RowInUse;
	row_index %= g_bl_table_header_config.MaxRow;

    return row_index;
}

/******************************************************************************
* Function Name : AddNewRow
* Interface     : void AddNewRow(void)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
static void AddNewRow(rtc_counter_value_t *p_rtc_value) //add new page
{
    uint32_t row_addr = 0;
    uint16_t current_row = 0;

    if ((g_bl_table_header.RowInUse) < (g_bl_table_header_config.MaxRow - 2))
    {
        g_bl_table_header.RowInUse++;
		g_bl_table_header.ColumnInUse = 0;
    }
    else
    {
		g_bl_table_header.FirstRowIndex++;
		g_bl_table_header.IsRolledOver = TRUE;
    	g_bl_table_header.FirstRowIndex %= g_bl_table_header_config.MaxRow;
    }
    PrepareBufferRow();

    /* Update new capture time */
    current_row = GetRowIdToWrite();   
    row_addr = g_bl_table_header_config.TableTimeCaptureStartAddr + current_row * g_bl_table_header_config.CaptureTimeSize;
    EPR_Write(row_addr, (uint8_t *)p_rtc_value, g_bl_table_header_config.CaptureTimeSize);
    memcpy(&g_last_capture_time, p_rtc_value, sizeof(rtc_counter_value_t));
}

/******************************************************************************
* Function Name : PrepareBufferRow
* Interface     : void PrepareBufferRow(void)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
static void PrepareBufferRow(void)
{
	uint32_t row_addr;
	uint32_t row_size;
    uint32_t row_size_eepr;
    uint32_t row_addr_spi = 0;
	uint16_t current_row;
    uint32_t table_log_base_addr;

    current_row = GetRowIdToWrite();
	current_row++;
	current_row %= g_bl_table_header_config.MaxRow;

    table_log_base_addr = g_bl_table_header_config.TableStartAddr;
    row_size_eepr = g_number_entry_per_row * g_bl_table_header_config.LogSize;

	// Clear date
	row_addr = g_bl_table_header_config.TableTimeCaptureStartAddr + current_row * g_bl_table_header_config.CaptureTimeSize;
	row_size = g_bl_table_header_config.CaptureTimeSize;
	ClearStorageRegion(row_addr, row_size); 

    //Clear Data in SPI FLash
    R_BLOCKLOAD_SPI_ClearRow(current_row);
}

static float32_t CalculateAvgCurrentFromOtherParams(float32_t v_avg, float32_t block_apparent, uint16_t time_counter);
/******************************************************************************
* Function Name : CalculateAvgCurrentFromOtherParams
* Interface     : float32_t CalculateAvgCurrentFromOtherParams(float32_t v_avg, float32_t block_apparent, uint16_t time_counter)
* Description   :
* Arguments     :
* Return Value  : float32_t
******************************************************************************/
static float32_t CalculateAvgCurrentFromOtherParams(float32_t v_avg, float32_t block_apparent, uint16_t time_counter)
{
    float32_t block_current_average = 0.0f;

    if (block_apparent == 0.0f || time_counter == 0 || v_avg == 0.0f)
    {
        block_current_average = 0.0f;
    }
    else
    {
        block_current_average = (float32_t)(block_apparent * 3600.0f * 1000.0f) / (v_avg * (float32_t)time_counter);
    }

    return block_current_average;
}

/******************************************************************************
* Function Name : GetBlockloadFromSnapshot
* Interface     : void GetBlockloadFromSnapshot(parameter)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
static void GetBlockloadFromSnapshot(
    one_block_storage_t *p_blockload,                  // OUTPUT
    EM_INST_READ_PARAMS *p_snapshot)               // INPUT
{
    float32_t EnergykWhImport  = 0.0f;
    float32_t EnergykVAhImport = 0.0f;
    float32_t EnergykWhExport  = 0.0f;
    float32_t EnergykVAhExport = 0.0f;

    EnergykWhImport  = R_TARIFF_GetImportActiveEnergyTotal()   ;
    EnergykVAhImport = R_TARIFF_GetImportApparentEnergyTotal() ;
    EnergykWhExport  = R_TARIFF_GetExportActiveEnergyTotal()   ;
    EnergykVAhExport = R_TARIFF_GetExportApparentEnergyTotal() ;

    memset(p_blockload, 0, sizeof(one_block_storage_t));
    p_blockload->Header_code = 0x5A;
    p_blockload->EnergykWhImport  = (block_storage_type_t)((EnergykWhImport  - g_block_backup_data.OldEnergykWhImport)  * STORAGE_RESOLUTION);
    p_blockload->EnergykVAhImport = (block_storage_type_t)((EnergykVAhImport - g_block_backup_data.OldEnergykVAhImport) * STORAGE_RESOLUTION);
    p_blockload->EnergykWhExport  = (block_storage_type_t)((EnergykWhExport  - g_block_backup_data.OldEnergykWhExport)  * STORAGE_RESOLUTION);
    p_blockload->EnergykVAhExport = (block_storage_type_t)((EnergykVAhExport - g_block_backup_data.OldEnergykVAhExport) * STORAGE_RESOLUTION);

#if (defined( BLOCKLOAD_AVERAGE_CALCULATION ) && BLOCKLOAD_AVERAGE_CALCULATION == 1)
    p_blockload->Current_R      = (uint32_t)((g_block_backup_data.Current_R ) * STORAGE_RESOLUTION);
    p_blockload->Current_Y      = (uint32_t)((g_block_backup_data.Current_Y ) * STORAGE_RESOLUTION);
    p_blockload->Current_B      = (uint32_t)((g_block_backup_data.Current_B ) * STORAGE_RESOLUTION);
    p_blockload->Voltage_R      = (uint32_t)((g_block_backup_data.Voltage_R ) * STORAGE_RESOLUTION);
    p_blockload->Voltage_Y      = (uint32_t)((g_block_backup_data.Voltage_Y ) * STORAGE_RESOLUTION);
    p_blockload->Voltage_B      = (uint32_t)((g_block_backup_data.Voltage_B ) * STORAGE_RESOLUTION);
    p_blockload->NumberOfSample = g_block_backup_data.Counter;
#endif /* BLOCKLOAD_AVERAGE_CALCULATION */

    g_block_backup_data.OldEnergykWhImport  = R_TARIFF_GetImportActiveEnergyTotal();
    g_block_backup_data.OldEnergykVAhImport = R_TARIFF_GetImportApparentEnergyTotal();
    g_block_backup_data.OldEnergykWhExport  = R_TARIFF_GetExportActiveEnergyTotal();
    g_block_backup_data.OldEnergykVAhExport = R_TARIFF_GetExportApparentEnergyTotal();

    //g_block_backup_data.AccVrms = 0;
	g_block_backup_data.Current_R = 0;
    g_block_backup_data.Current_Y = 0;
    g_block_backup_data.Current_B = 0;

    g_block_backup_data.Voltage_R = 0;
    g_block_backup_data.Voltage_Y = 0;
    g_block_backup_data.Voltage_B = 0;
	
    g_block_backup_data.Counter = 0;
}

/******************************************************************************
* Function Name : GetDailyloadFromSnapshot
* Interface     : void GetDailyloadFromSnapshot()
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
static void GetDailyloadFromSnapshot(one_daily_log_storage *p_data, s_capture_em_data_t *p_snapshot)
{
    memset(p_data, 0, sizeof(one_daily_log_storage));
    p_data->CaptureTime.sec 	= gp_inst_LastDataPop->capture_time.sec;
    p_data->CaptureTime.min 	= gp_inst_LastDataPop->capture_time.min;
    p_data->CaptureTime.hour 	= gp_inst_LastDataPop->capture_time.hour;
    p_data->CaptureTime.day 	= gp_inst_LastDataPop->capture_time.day;
    p_data->CaptureTime.week 	= gp_inst_LastDataPop->capture_time.week;
    p_data->CaptureTime.month 	= gp_inst_LastDataPop->capture_time.month;
    p_data->CaptureTime.year 	= gp_inst_LastDataPop->capture_time.year;

	p_data->EnergykWhImport  = (uint32_t)((R_TARIFF_GetImportActiveEnergyTotal()   ) * STORAGE_RESOLUTION);
    p_data->EnergykVAhImport = (uint32_t)((R_TARIFF_GetImportApparentEnergyTotal() ) * STORAGE_RESOLUTION);
    p_data->EnergykWhExport  = (uint32_t)((R_TARIFF_GetExportActiveEnergyTotal()   ) * STORAGE_RESOLUTION);
    p_data->EnergykVAhExport = (uint32_t)((R_TARIFF_GetExportApparentEnergyTotal() ) * STORAGE_RESOLUTION);


}

/******************************************************************************
* Function Name : GetBillingloadFromSnapshot
* Interface     : void GetBillingloadFromSnapshot()
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
static void GetBillingloadFromSnapshot(one_billing_log_storage *p_data)
{
    static one_billing_log_storage previous_block_counters;
    float32_t f32_value;
    rtc_counter_value_t e_datetime_value;

    /* Get from inst snapshot */
    memcpy(&p_data->CaptureTime, &g_billing_date, sizeof(rtc_counter_value_t));

    p_data->AveragePowerFactor = (uint16_t)(R_LOADSURVEY_GetCurrentAveragePF() * STORAGE_RESOLUTION);

    p_data->CumulativeEnergykWh = (uint32_t)(R_TARIFF_GetImportActiveEnergyTotal() * STORAGE_RESOLUTION);
    p_data->CumulativeEnergykVAh = (uint32_t)(R_TARIFF_GetImportApparentEnergyTotal() * STORAGE_RESOLUTION);

    p_data->CumulativeEnergykWh_Export = (uint32_t)(R_TARIFF_GetExportActiveEnergyTotal() * STORAGE_RESOLUTION);
    p_data->CumulativeEnergykVAh_Export = (uint32_t)(R_TARIFF_GetExportApparentEnergyTotal() * STORAGE_RESOLUTION);

    /* Get value from tariff */
    R_TARIFF_GetImportActiveEnergyTariff(0, &f32_value);
    p_data->CumulativeEnergykWh_TZ1 = (uint32_t)(f32_value * STORAGE_RESOLUTION);
    R_TARIFF_GetImportActiveEnergyTariff(1, &f32_value);
    p_data->CumulativeEnergykWh_TZ2 = (uint32_t)(f32_value * STORAGE_RESOLUTION);
    R_TARIFF_GetImportActiveEnergyTariff(2, &f32_value);
    p_data->CumulativeEnergykWh_TZ3 = (uint32_t)(f32_value * STORAGE_RESOLUTION);
    R_TARIFF_GetImportActiveEnergyTariff(3, &f32_value);
    p_data->CumulativeEnergykWh_TZ4 = (uint32_t)(f32_value * STORAGE_RESOLUTION);
    R_TARIFF_GetImportActiveEnergyTariff(4, &f32_value);
    p_data->CumulativeEnergykWh_TZ5 = (uint32_t)(f32_value * STORAGE_RESOLUTION);
    R_TARIFF_GetImportActiveEnergyTariff(5, &f32_value);
    p_data->CumulativeEnergykWh_TZ6 = (uint32_t)(f32_value * STORAGE_RESOLUTION);
    R_TARIFF_GetImportActiveEnergyTariff(6, &f32_value);
    p_data->CumulativeEnergykWh_TZ7 = (uint32_t)(f32_value * STORAGE_RESOLUTION);
    R_TARIFF_GetImportActiveEnergyTariff(7, &f32_value);
    p_data->CumulativeEnergykWh_TZ8 = (uint32_t)(f32_value * STORAGE_RESOLUTION);

    R_TARIFF_GetImportApparentEnergyTariff(0, &f32_value);
    p_data->CumulativeEnergykVAh_TZ1 = (uint32_t)(f32_value * STORAGE_RESOLUTION);
    R_TARIFF_GetImportApparentEnergyTariff(1, &f32_value);
    p_data->CumulativeEnergykVAh_TZ2 = (uint32_t)(f32_value * STORAGE_RESOLUTION);
    R_TARIFF_GetImportApparentEnergyTariff(2, &f32_value);
    p_data->CumulativeEnergykVAh_TZ3 = (uint32_t)(f32_value * STORAGE_RESOLUTION);
    R_TARIFF_GetImportApparentEnergyTariff(3, &f32_value);
    p_data->CumulativeEnergykVAh_TZ4 = (uint32_t)(f32_value * STORAGE_RESOLUTION);
    R_TARIFF_GetImportApparentEnergyTariff(4, &f32_value);
    p_data->CumulativeEnergykVAh_TZ5 = (uint32_t)(f32_value * STORAGE_RESOLUTION);
    R_TARIFF_GetImportApparentEnergyTariff(5, &f32_value);
    p_data->CumulativeEnergykVAh_TZ6 = (uint32_t)(f32_value * STORAGE_RESOLUTION);
    R_TARIFF_GetImportApparentEnergyTariff(6, &f32_value);
    p_data->CumulativeEnergykVAh_TZ7 = (uint32_t)(f32_value * STORAGE_RESOLUTION);
    R_TARIFF_GetImportApparentEnergyTariff(7, &f32_value);
    p_data->CumulativeEnergykVAh_TZ8 = (uint32_t)(f32_value * STORAGE_RESOLUTION);

    /* Get from MDM application */
    p_data->MDkW = (uint32_t)(R_MDM_GetActiveMaxDemand() * STORAGE_RESOLUTION);
    R_MDM_GetActiveMaxDemandCapturedTime(&e_datetime_value);                                 
    memcpy(&p_data->MDkWDateTime, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetActiveMaxDemandTz(0, &f32_value);
    p_data->MDkW_TZ1 = (uint32_t)(f32_value * STORAGE_RESOLUTION);                
    R_MDM_GetMaxDemandActiveCapturedTimeTz(0, &e_datetime_value);                             
    memcpy(&p_data->MDkWDateTime_TZ1, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetActiveMaxDemandTz(1, &f32_value);
    p_data->MDkW_TZ2 = (uint32_t)(f32_value * STORAGE_RESOLUTION);                
    R_MDM_GetMaxDemandActiveCapturedTimeTz(1, &e_datetime_value);                             
    memcpy(&p_data->MDkWDateTime_TZ2, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetActiveMaxDemandTz(2, &f32_value);
    p_data->MDkW_TZ3 = (uint32_t)(f32_value * STORAGE_RESOLUTION);                
    R_MDM_GetMaxDemandActiveCapturedTimeTz(2, &e_datetime_value);                             
    memcpy(&p_data->MDkWDateTime_TZ3, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetActiveMaxDemandTz(3, &f32_value);
    p_data->MDkW_TZ4 = (uint32_t)(f32_value * STORAGE_RESOLUTION);                
    R_MDM_GetMaxDemandActiveCapturedTimeTz(3, &e_datetime_value);                             
    memcpy(&p_data->MDkWDateTime_TZ4, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetActiveMaxDemandTz(4, &f32_value);
    p_data->MDkW_TZ5 = (uint32_t)(f32_value * STORAGE_RESOLUTION);                
    R_MDM_GetMaxDemandActiveCapturedTimeTz(4, &e_datetime_value);                             
    memcpy(&p_data->MDkWDateTime_TZ5, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetActiveMaxDemandTz(5, &f32_value);
    p_data->MDkW_TZ6 = (uint32_t)(f32_value * STORAGE_RESOLUTION);                
    R_MDM_GetMaxDemandActiveCapturedTimeTz(5, &e_datetime_value);                             
    memcpy(&p_data->MDkWDateTime_TZ6, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetActiveMaxDemandTz(6, &f32_value);
    p_data->MDkW_TZ7 = (uint32_t)(f32_value * STORAGE_RESOLUTION);                
    R_MDM_GetMaxDemandActiveCapturedTimeTz(6, &e_datetime_value);                             
    memcpy(&p_data->MDkWDateTime_TZ7, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetActiveMaxDemandTz(7, &f32_value);
    p_data->MDkW_TZ8 = (uint32_t)(f32_value * STORAGE_RESOLUTION);                
    R_MDM_GetMaxDemandActiveCapturedTimeTz(7, &e_datetime_value);                             
    memcpy(&p_data->MDkWDateTime_TZ8, &e_datetime_value, sizeof(e_datetime_value));
    
    p_data->MDkVA = (uint32_t)(R_MDM_GetApparentMaxDemand() * STORAGE_RESOLUTION);
    R_MDM_GetApparentMaxDemandCapturedTime(&e_datetime_value);                                 
    memcpy(&p_data->MDkVADateTime, &e_datetime_value, sizeof(e_datetime_value));    
    R_MDM_GetApparentMaxDemandTz(0, &f32_value);
    p_data->MDkVA_TZ1 = (uint32_t)(f32_value * STORAGE_RESOLUTION);              
    R_MDM_GetMaxDemandApparentCapturedTimeTz(0, &e_datetime_value);                             
    memcpy(&p_data->MDkVADateTime_TZ1, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetApparentMaxDemandTz(1, &f32_value);
    p_data->MDkVA_TZ2 = (uint32_t)(f32_value * STORAGE_RESOLUTION);              
    R_MDM_GetMaxDemandApparentCapturedTimeTz(1, &e_datetime_value);                             
    memcpy(&p_data->MDkVADateTime_TZ2, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetApparentMaxDemandTz(2, &f32_value);
    p_data->MDkVA_TZ3 = (uint32_t)(f32_value * STORAGE_RESOLUTION);              
    R_MDM_GetMaxDemandApparentCapturedTimeTz(2, &e_datetime_value);                             
    memcpy(&p_data->MDkVADateTime_TZ3, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetApparentMaxDemandTz(3, &f32_value);
    p_data->MDkVA_TZ4 = (uint32_t)(f32_value * STORAGE_RESOLUTION);              
    R_MDM_GetMaxDemandApparentCapturedTimeTz(3, &e_datetime_value);                             
    memcpy(&p_data->MDkVADateTime_TZ4, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetApparentMaxDemandTz(4, &f32_value);
    p_data->MDkVA_TZ5 = (uint32_t)(f32_value * STORAGE_RESOLUTION);              
    R_MDM_GetMaxDemandApparentCapturedTimeTz(4, &e_datetime_value);                             
    memcpy(&p_data->MDkVADateTime_TZ5, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetApparentMaxDemandTz(5, &f32_value);
    p_data->MDkVA_TZ6 = (uint32_t)(f32_value * STORAGE_RESOLUTION);              
    R_MDM_GetMaxDemandApparentCapturedTimeTz(5, &e_datetime_value);                             
    memcpy(&p_data->MDkVADateTime_TZ6, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetApparentMaxDemandTz(6, &f32_value);
    p_data->MDkVA_TZ7 = (uint32_t)(f32_value * STORAGE_RESOLUTION);              
    R_MDM_GetMaxDemandApparentCapturedTimeTz(6, &e_datetime_value);                             
    memcpy(&p_data->MDkVADateTime_TZ7, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetApparentMaxDemandTz(7, &f32_value);
    p_data->MDkVA_TZ8 = (uint32_t)(f32_value * STORAGE_RESOLUTION);              
    R_MDM_GetMaxDemandApparentCapturedTimeTz(7, &e_datetime_value);                             
    memcpy(&p_data->MDkVADateTime_TZ8, &e_datetime_value, sizeof(e_datetime_value));

    /* Get total power on duration */
    p_data->PowerONduration = g_billing_power_on_duration;

    /* Quadrant energy */
    p_data->CumulativeEnergykVArh_QI = (uint32_t)(R_TARIFF_GetImportInductiveReactiveEnergyTotal() * STORAGE_RESOLUTION);
    p_data->CumulativeEnergykVArh_QII = (uint32_t)(R_TARIFF_GetExportCapacitiveReactiveEnergyTotal() * STORAGE_RESOLUTION);
    p_data->CumulativeEnergykVArh_QIII = (uint32_t)(R_TARIFF_GetExportInductiveReactiveEnergyTotal() * STORAGE_RESOLUTION);
    p_data->CumulativeEnergykVArh_QIV = (uint32_t)(R_TARIFF_GetImportCapacitiveReactiveEnergyTotal() * STORAGE_RESOLUTION);

    /* Clear billing data after get */
    g_billing_power_on_duration = 0;

}

/******************************************************************************
* Function Name : ExtractStorageDataToBlockload
* Interface     : void ExtractStorageDataToBlockload(r_block_load_t *p_BlockLoad, one_block_storage_t *p_storage_data)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
static void ExtractStorageDataToBlockload(
    r_block_load_t      *p_BlockLoad,
    r_loadsurvey_rtc_t  *p_capture_time,
    one_block_storage_t *p_storage_data
)
{
    float32_t block_apparent_energy;

    p_BlockLoad->CaptureTime = *p_capture_time;

    p_BlockLoad->EnergykWhImport  = ((float32_t)p_storage_data->EnergykWhImport  / STORAGE_RESOLUTION);
    p_BlockLoad->EnergykVAhImport = ((float32_t)p_storage_data->EnergykVAhImport / STORAGE_RESOLUTION);
    p_BlockLoad->EnergykWhExport  = ((float32_t)p_storage_data->EnergykWhExport  / STORAGE_RESOLUTION);
    p_BlockLoad->EnergykVAhExport = ((float32_t)p_storage_data->EnergykVAhExport / STORAGE_RESOLUTION);

    if (p_storage_data->NumberOfSample != 0)
    {
	    p_BlockLoad->Current_R  =  (float32_t)p_storage_data->Current_R / (p_storage_data->NumberOfSample * STORAGE_RESOLUTION);
	    p_BlockLoad->Current_Y  =  (float32_t)p_storage_data->Current_Y / (p_storage_data->NumberOfSample * STORAGE_RESOLUTION);
	    p_BlockLoad->Current_B  =  (float32_t)p_storage_data->Current_B / (p_storage_data->NumberOfSample * STORAGE_RESOLUTION);

	    p_BlockLoad->Voltage_R   =  (float32_t)p_storage_data->Voltage_R / (p_storage_data->NumberOfSample * STORAGE_RESOLUTION);
	    p_BlockLoad->Voltage_Y   =  (float32_t)p_storage_data->Voltage_Y / (p_storage_data->NumberOfSample * STORAGE_RESOLUTION);
	    p_BlockLoad->Voltage_B   =  (float32_t)p_storage_data->Voltage_B / (p_storage_data->NumberOfSample * STORAGE_RESOLUTION);
    }
    else
    {
        p_BlockLoad->Current_R = 0.0f;
		p_BlockLoad->Current_Y = 0.0f;
		p_BlockLoad->Current_B = 0.0f;
		
		p_BlockLoad->Voltage_R = 0.0f;
		p_BlockLoad->Voltage_Y = 0.0f;
		p_BlockLoad->Voltage_B = 0.0f;
    }

#if 1       // Import only mode
    block_apparent_energy = p_BlockLoad->EnergykVAhImport;
    #else       // ImportExport mode
    block_apparent_energy = p_BlockLoad->EnergykVAhImport + p_BlockLoad->EnergykVAhExport;
    #endif      
    //p_BlockLoad->AverageCurrent = CalculateAvgCurrentFromOtherParams(
    //                                p_BlockLoad->AverageVoltage,
    //                                block_apparent_energy,
    //                                p_storage_data->NumberOfSample
    //                            );
//
}

/******************************************************************************
* Function Name : ExtractStorageDataToDailyLoad
* Interface     : void ExtractStorageDataToDailyLoad(r_daily_load_t *p_BlockLoad, r_loadsurvey_rtc_t *p_capture_time, one_daily_log_storage *p_storage_data)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
static void ExtractStorageDataToDailyLoad(
    r_daily_load_t *p_out_data, 
    r_loadsurvey_rtc_t *p_capture_time, 
    one_daily_log_storage *p_storage_data
)
{
    p_out_data->CaptureTime = p_storage_data->CaptureTime;
    p_out_data->EnergykWhImport  = (float32_t)p_storage_data->EnergykWhImport  / STORAGE_RESOLUTION;
    p_out_data->EnergykVAhImport = (float32_t)p_storage_data->EnergykVAhImport  / STORAGE_RESOLUTION;
    p_out_data->EnergykWhExport  = (float32_t)p_storage_data->EnergykWhExport  / STORAGE_RESOLUTION;
    p_out_data->EnergykVAhExport = (float32_t)p_storage_data->EnergykVAhExport  / STORAGE_RESOLUTION;
}

/******************************************************************************
* Function Name : ExtractStorageDataToBilling
* Interface     : void ExtractStorageDataToBilling(r_billing_t *p_out_data, r_loadsurvey_rtc_t *p_capture_time, one_billing_log_storage *p_storage_data)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
static void ExtractStorageDataToBilling(
    r_billing_t *p_out_data, 
    r_loadsurvey_rtc_t *p_capture_time, 
    one_billing_log_storage *p_storage_data
)
{
    p_out_data->CaptureTime = p_storage_data->CaptureTime;
    p_out_data->AveragePowerFactor = (float32_t)(p_storage_data->AveragePowerFactor / 100.0f);
    p_out_data->CumulativeEnergykWh = (float32_t)p_storage_data->CumulativeEnergykWh / STORAGE_RESOLUTION;
    p_out_data->CumulativeEnergykWh_TZ1 = (float32_t)p_storage_data->CumulativeEnergykWh_TZ1 / STORAGE_RESOLUTION;
    p_out_data->CumulativeEnergykWh_TZ2 = (float32_t)p_storage_data->CumulativeEnergykWh_TZ2 / STORAGE_RESOLUTION;
    p_out_data->CumulativeEnergykWh_TZ3 = (float32_t)p_storage_data->CumulativeEnergykWh_TZ3 / STORAGE_RESOLUTION;
    p_out_data->CumulativeEnergykWh_TZ4 = (float32_t)p_storage_data->CumulativeEnergykWh_TZ4 / STORAGE_RESOLUTION;
    p_out_data->CumulativeEnergykWh_TZ5 = (float32_t)p_storage_data->CumulativeEnergykWh_TZ5 / STORAGE_RESOLUTION;
    p_out_data->CumulativeEnergykWh_TZ6 = (float32_t)p_storage_data->CumulativeEnergykWh_TZ6 / STORAGE_RESOLUTION;
    p_out_data->CumulativeEnergykWh_TZ7 = (float32_t)p_storage_data->CumulativeEnergykWh_TZ7 / STORAGE_RESOLUTION;
    p_out_data->CumulativeEnergykWh_TZ8 = (float32_t)p_storage_data->CumulativeEnergykWh_TZ8 / STORAGE_RESOLUTION;
    p_out_data->CumulativeEnergykVAh = (float32_t)p_storage_data->CumulativeEnergykVAh / STORAGE_RESOLUTION;
    p_out_data->CumulativeEnergykVAh_TZ1 = (float32_t)p_storage_data->CumulativeEnergykVAh_TZ1 / STORAGE_RESOLUTION;
    p_out_data->CumulativeEnergykVAh_TZ2 = (float32_t)p_storage_data->CumulativeEnergykVAh_TZ2 / STORAGE_RESOLUTION;
    p_out_data->CumulativeEnergykVAh_TZ3 = (float32_t)p_storage_data->CumulativeEnergykVAh_TZ3 / STORAGE_RESOLUTION;
    p_out_data->CumulativeEnergykVAh_TZ4 = (float32_t)p_storage_data->CumulativeEnergykVAh_TZ4 / STORAGE_RESOLUTION;
    p_out_data->CumulativeEnergykVAh_TZ5 = (float32_t)p_storage_data->CumulativeEnergykVAh_TZ5 / STORAGE_RESOLUTION;
    p_out_data->CumulativeEnergykVAh_TZ6 = (float32_t)p_storage_data->CumulativeEnergykVAh_TZ6 / STORAGE_RESOLUTION;
    p_out_data->CumulativeEnergykVAh_TZ7 = (float32_t)p_storage_data->CumulativeEnergykVAh_TZ7 / STORAGE_RESOLUTION;
    p_out_data->CumulativeEnergykVAh_TZ8 = (float32_t)p_storage_data->CumulativeEnergykVAh_TZ8 / STORAGE_RESOLUTION;
    p_out_data->MDkW                        = (float32_t)p_storage_data->MDkW / STORAGE_RESOLUTION;
    p_out_data->MDkW_TZ1                    = (float32_t)p_storage_data->MDkW_TZ1 / STORAGE_RESOLUTION;
    p_out_data->MDkW_TZ2                    = (float32_t)p_storage_data->MDkW_TZ2 / STORAGE_RESOLUTION;
    p_out_data->MDkW_TZ3                    = (float32_t)p_storage_data->MDkW_TZ3 / STORAGE_RESOLUTION;
    p_out_data->MDkW_TZ4                    = (float32_t)p_storage_data->MDkW_TZ4 / STORAGE_RESOLUTION;
    p_out_data->MDkW_TZ5                    = (float32_t)p_storage_data->MDkW_TZ5 / STORAGE_RESOLUTION;
    p_out_data->MDkW_TZ6                    = (float32_t)p_storage_data->MDkW_TZ6 / STORAGE_RESOLUTION;
    p_out_data->MDkW_TZ7                    = (float32_t)p_storage_data->MDkW_TZ7 / STORAGE_RESOLUTION;
    p_out_data->MDkW_TZ8                    = (float32_t)p_storage_data->MDkW_TZ8 / STORAGE_RESOLUTION;

    p_out_data->MDkWDateTime                = p_storage_data->MDkWDateTime;
    p_out_data->MDkWDateTime_TZ1            = p_storage_data->MDkWDateTime_TZ1;
    p_out_data->MDkWDateTime_TZ2            = p_storage_data->MDkWDateTime_TZ2;
    p_out_data->MDkWDateTime_TZ3            = p_storage_data->MDkWDateTime_TZ3;
    p_out_data->MDkWDateTime_TZ4            = p_storage_data->MDkWDateTime_TZ4;
    p_out_data->MDkWDateTime_TZ5            = p_storage_data->MDkWDateTime_TZ5;
    p_out_data->MDkWDateTime_TZ6            = p_storage_data->MDkWDateTime_TZ6;
    p_out_data->MDkWDateTime_TZ7            = p_storage_data->MDkWDateTime_TZ7;
    p_out_data->MDkWDateTime_TZ8            = p_storage_data->MDkWDateTime_TZ8;

    p_out_data->MDkVA                       = (float32_t)p_storage_data->MDkVA / STORAGE_RESOLUTION;
    p_out_data->MDkVA_TZ1                   = (float32_t)p_storage_data->MDkVA_TZ1 / STORAGE_RESOLUTION;
    p_out_data->MDkVA_TZ2                   = (float32_t)p_storage_data->MDkVA_TZ2 / STORAGE_RESOLUTION;
    p_out_data->MDkVA_TZ3                   = (float32_t)p_storage_data->MDkVA_TZ3 / STORAGE_RESOLUTION;
    p_out_data->MDkVA_TZ4                   = (float32_t)p_storage_data->MDkVA_TZ4 / STORAGE_RESOLUTION;
    p_out_data->MDkVA_TZ5                   = (float32_t)p_storage_data->MDkVA_TZ5 / STORAGE_RESOLUTION;
    p_out_data->MDkVA_TZ6                   = (float32_t)p_storage_data->MDkVA_TZ6 / STORAGE_RESOLUTION;
    p_out_data->MDkVA_TZ7                   = (float32_t)p_storage_data->MDkVA_TZ7 / STORAGE_RESOLUTION;
    p_out_data->MDkVA_TZ8                   = (float32_t)p_storage_data->MDkVA_TZ8 / STORAGE_RESOLUTION;

    p_out_data->MDkVADateTime               = p_storage_data->MDkVADateTime;
    p_out_data->MDkVADateTime_TZ1           = p_storage_data->MDkVADateTime_TZ1;
    p_out_data->MDkVADateTime_TZ2           = p_storage_data->MDkVADateTime_TZ2;
    p_out_data->MDkVADateTime_TZ3           = p_storage_data->MDkVADateTime_TZ3;
    p_out_data->MDkVADateTime_TZ4           = p_storage_data->MDkVADateTime_TZ4;
    p_out_data->MDkVADateTime_TZ5           = p_storage_data->MDkVADateTime_TZ5;
    p_out_data->MDkVADateTime_TZ6           = p_storage_data->MDkVADateTime_TZ6;
    p_out_data->MDkVADateTime_TZ7           = p_storage_data->MDkVADateTime_TZ7;
    p_out_data->MDkVADateTime_TZ8           = p_storage_data->MDkVADateTime_TZ8;

    p_out_data->PowerONduration             = p_storage_data->PowerONduration;

    p_out_data->CumulativeEnergykWh_Export  = (float32_t)p_storage_data->CumulativeEnergykWh_Export / STORAGE_RESOLUTION;
    p_out_data->CumulativeEnergykVAh_Export = (float32_t)p_storage_data->CumulativeEnergykVAh_Export / STORAGE_RESOLUTION;
    p_out_data->CumulativeEnergykVArh_QI    = (float32_t)p_storage_data->CumulativeEnergykVArh_QI / STORAGE_RESOLUTION;
    p_out_data->CumulativeEnergykVArh_QII   = (float32_t)p_storage_data->CumulativeEnergykVArh_QII / STORAGE_RESOLUTION;
    p_out_data->CumulativeEnergykVArh_QIII  = (float32_t)p_storage_data->CumulativeEnergykVArh_QIII / STORAGE_RESOLUTION;
    p_out_data->CumulativeEnergykVArh_QIV   = (float32_t)p_storage_data->CumulativeEnergykVArh_QIV / STORAGE_RESOLUTION;
}



/******************************************************************************
* Function Name : R_BLOCKLOAD_GetEntryByIndex
* Interface     : void R_BLOCKLOAD_GetEntryByIndex(uint32_t entry_index, uint8_t multiplier, r_block_load_t *p_OutData);
* Description   : Collect the data from SPI Flash
* Arguments     : uint32_t entry_index
*               : uint8_t multiplier
*               : r_block_load_t *p_OutData
* Function Calls:
* Return Value  : TRUE (1) : Get success, FALSE (0): Get failed
******************************************************************************/
uint8_t R_BLOCKLOAD_GetEntryByIndex(uint32_t entry_index, uint8_t multiplier, r_block_load_t *p_OutData)
{
    uint32_t ReadAddr = 0;

    uint32_t table_capture_time_base_addr = g_bl_table_header_config.TableTimeCaptureStartAddr;
    uint32_t row_addr = 0;
    uint16_t row_id;
    uint32_t entry_index_subslot;
    uint16_t i;
    uint32_t sample_counter = 0;
    float32_t voltageR_accumulate = 0;
    float32_t voltageY_accumulate = 0;
    float32_t voltageB_accumulate = 0;
    float32_t currentR_accumulate = 0;
    float32_t currentY_accumulate = 0;
    float32_t currentB_accumulate = 0;
    uint32_t real_index;
    uint32_t column_index;
    uint16_t row_in_use;
	
	uint32_t phy_entry_index = 0;

    one_block_storage_t blockload_entry_from_storage;
    one_block_storage_t blockload_entry_from_storage_total;
    r_loadsurvey_rtc_t capture_time;

    float32_t EnergykWhImport   = 0.0f;  
    float32_t EnergykVAhImport  = 0.0f;
    float32_t EnergykWhExport   = 0.0f;
    float32_t EnergykVAhExport  = 0.0f;

    /* Error check */
    if (p_OutData == 0 || multiplier == 0)
    {
        return FALSE;
    }

    /* Init */
    memset(&blockload_entry_from_storage, 0, sizeof(one_block_storage_t));
    memset(&blockload_entry_from_storage_total, 0, sizeof(one_block_storage_t));
    memset(p_OutData, 0, sizeof(r_block_load_t));
    memset(&capture_time, 0, sizeof(r_loadsurvey_rtc_t));
    
	phy_entry_index = entry_index * multiplier;
    if(is_rolledover())
    {
		phy_entry_index += g_bl_table_header.ColumnInUse;
    }

    row_in_use = GetRowIdToWrite();
    /* Get time */
    row_id = (phy_entry_index) / g_number_entry_per_row;
    row_id += g_bl_table_header.FirstRowIndex;
    row_id %= g_bl_table_header_config.MaxRow;
    row_addr = table_capture_time_base_addr + row_id * g_bl_table_header_config.CaptureTimeSize;
    EPR_Read(row_addr, (uint8_t *)&capture_time, g_bl_table_header_config.CaptureTimeSize);

    for(i = 0; i < multiplier; i++)
    {   
        entry_index_subslot = (phy_entry_index) + i;
        if ( row_id == row_in_use)
        {
            if (g_bl_table_header.IsAbnormal == TRUE )  /* Abnormal case */
            {
                /* Get log data from Eepr*/
                ReadAddr = GetCellAddrInEepr(entry_index_subslot);
                if (EPR_Read(ReadAddr, (uint8_t *)(void *)&blockload_entry_from_storage, g_bl_table_header_config.LogSize) != EPR_OK)
                {
                return FALSE;
                }
            }
            else  /* Normal case*/
            {
                /* Get log data from Flash*/
                ReadAddr = GetCellAddrInFlash(entry_index_subslot);
                if (BL_SFL_DeviceRead(ReadAddr, (uint8_t *)(void *)&blockload_entry_from_storage, g_bl_table_header_config.LogSize) != SFL_OK)
                {
                    return FALSE;
                }
        
            }
        }
        else
        {
            /* Get log data from Flash*/
            ReadAddr = GetCellAddrInFlash(entry_index_subslot);
            if (BL_SFL_DeviceRead(ReadAddr, (uint8_t *)(void *)&blockload_entry_from_storage, g_bl_table_header_config.LogSize) != SFL_OK)
            {
                return FALSE;
            }
        
        }
        if (blockload_entry_from_storage.Header_code != 0x5A)
        {
            memset(&blockload_entry_from_storage, 0, g_bl_table_header_config.LogSize);
        }
        else
        {
            __nop();
        }

        blockload_entry_from_storage_total.NumberOfSample += blockload_entry_from_storage.NumberOfSample;

        currentR_accumulate += blockload_entry_from_storage.Current_R;
        currentY_accumulate += blockload_entry_from_storage.Current_Y;
        currentB_accumulate += blockload_entry_from_storage.Current_B;

        voltageR_accumulate += blockload_entry_from_storage.Voltage_R;
        voltageY_accumulate += blockload_entry_from_storage.Voltage_Y;
        voltageB_accumulate += blockload_entry_from_storage.Voltage_B;

        blockload_entry_from_storage_total.EnergykWhImport  += blockload_entry_from_storage.EnergykWhImport;
        blockload_entry_from_storage_total.EnergykVAhImport += blockload_entry_from_storage.EnergykVAhImport;
        blockload_entry_from_storage_total.EnergykWhExport  += blockload_entry_from_storage.EnergykWhExport;
        blockload_entry_from_storage_total.EnergykVAhExport += blockload_entry_from_storage.EnergykVAhExport;

    }

    blockload_entry_from_storage_total.Current_R = (currentR_accumulate );
    blockload_entry_from_storage_total.Current_Y = (currentY_accumulate );
    blockload_entry_from_storage_total.Current_B = (currentB_accumulate );

    blockload_entry_from_storage_total.Voltage_R = (voltageR_accumulate );
    blockload_entry_from_storage_total.Voltage_Y = (voltageY_accumulate );
    blockload_entry_from_storage_total.Voltage_B = (voltageB_accumulate );

    real_index = phy_entry_index;
    column_index = real_index % g_number_entry_per_row;

    column_index = column_index * R_BLOCKLOAD_CAPTURE_INTERVAL;
    capture_time.sec = 0;
    capture_time.min = (uint8_t)(column_index % 60);
    capture_time.hour = (uint8_t)(column_index / 60);

    /* Convert from storage (compact data type) to display type */
    ExtractStorageDataToBlockload(p_OutData, &capture_time, &blockload_entry_from_storage_total);

    return TRUE;
}

/******************************************************************************
* Function Name : R_LOADSURVEY_RecordBlockLoad_InEEPROM
* Interface     : void R_LOADSURVEY_RecordBlockLoad_InEEPROM(
*               :    r_loadsurvey_rtc_t           *p_capture_time,
*               :    EM_INST_READ_PARAMS           *p_inst_values,
*               : );
* Description   : This function will add data of p_log into EEPROM buffer.
*               : The entries_in_used and write_pos will be increased
*               : Rollover happend when entries_in_used > max_entries
* Arguments     :
*               : p_log                   : Buffer that contain data of entry
*               : log_size                : Size of p_log data
*               : p_storage_table_map     : Address of EEPROM
*               :             It shall include Address of
*               :                     [buffer_info]
*               :                     [Data table]
* Function Calls:
* Return Value  : TRUE (0)     : Result success
*               : Other       (!=0) : The logging has (an) error(s).
******************************************************************************/
static uint8_t R_LOADSURVEY_RecordBlockLoad_InEEPROM(void)
{
	uint32_t one_entry_size = g_bl_table_header_config.LogSize;
    uint32_t table_capture_time_base_addr = g_bl_table_header_config.TableTimeCaptureStartAddr;
    uint32_t table_log_base_addr = g_bl_table_header_config.TableStartAddr;

    rtc_counter_value_t capture_time;
    EM_INST_READ_PARAMS inst_values;
	// Calculate row index
	uint32_t row_addr = 0;
    uint32_t row_addr_spi = 0;
	uint32_t row_index = 0;

	uint16_t column_index = 0;
	uint32_t cell_addr = 0;
    
	uint32_t row_size_eepr;

    one_block_storage_t blockload_value;
    one_block_storage_t blockload_value_stored;
    
	/*
	*  Capture time:
    *                [T1] [T2] [T3]       [Tn]
    *
    *  Blockload table cell indexing (NOT ROLLEDOVER YET)
	*
	*                | Col   | Col 1  | Col 2  | Col 3  |  ...  | Col 47
	*        --------+-------|--------|--------|--------|-------|---------
	*        Row 0   | 0     |  1     |  2     |  3     |  ...  |  47
	*        Row 1   | 48    |  49    |  50    |  51    |  ...  |  95
	*        Row 2   | 96    |  97    |  98    |  99    |  ...  |  143
	*        Row 3   | 144   |  145   |  146   |  147   |  ...  |  191
	*        Row 4   | 192   |  193   |  194   |  195   |  ...  |  239
	*                | ...   |  ...   |  ...   |  ...   |  ...  |  ...
	*        Row 34  | 1632  |  1633  | 1634   |  1635  |  ...  |  1679
	*        Row 35  | ----  |  ----  | ----   |  ----  |  ...  |  ----      (Buffer row)
	*/

	/* Pre-calculation */
	row_size_eepr = g_number_entry_per_row * one_entry_size;
    row_index = GetRowIdToWrite();
    memset(&blockload_value_stored, 0, sizeof(one_block_storage_t));
    memcpy(&capture_time, &gp_inst_LastDataPop->capture_time, sizeof(rtc_counter_value_t));

	if (capture_time.year == 0u ||
		capture_time.month == 0u ||
		capture_time.day == 0u ||
		g_last_capture_time.year ==0 ||
		g_last_capture_time.month == 0||
		g_last_capture_time.day == 0)
	{
        // Clear Data in Epprom
        ClearStorageRegion(table_log_base_addr, row_size_eepr);     // Prepare row, ~ 2 * 32 * 48 bytes = 3072 bytes

        R_BLOCKLOAD_SPI_ClearRow(row_index);
        
        /* Update new capture time */
        row_addr = table_capture_time_base_addr + row_index * g_bl_table_header_config.CaptureTimeSize;
        EPR_Write(row_addr, (uint8_t *)&capture_time, g_bl_table_header_config.CaptureTimeSize);
		g_last_capture_time = capture_time;
	}
    else if(g_bl_table_header.IsBackWard == TRUE)
    {
        R_BLOCKLOAD_TransferFlashBlockToEeprom();
        PrepareBufferRow();
        g_bl_table_header.IsBackWard = FALSE;
    }
	else if (capture_time.year    != g_last_capture_time.year ||
		     capture_time.month   != g_last_capture_time.month ||
		     capture_time.day     != g_last_capture_time.day)
	{   
        R_BLOCKLOAD_TransferEepromToFlash();    
        AddNewRow(&capture_time);
        g_bl_table_header.IsAbnormal = FALSE;
	}

	/* Write current block */
	{
		column_index = (uint16_t)(capture_time.hour * 60 + capture_time.min) / (R_BLOCKLOAD_CAPTURE_INTERVAL);
		cell_addr = table_log_base_addr +  column_index * one_entry_size;
	}

    /* Accumulate to current slot */
    EPR_Read(cell_addr, (uint8_t*)&blockload_value_stored, g_bl_table_header_config.LogSize);
    if (blockload_value_stored.Header_code != 0x5A)
    {
        memset(&blockload_value_stored, 0, g_bl_table_header_config.LogSize);
    }
    {   
        GetBlockloadFromSnapshot(&blockload_value, &gp_inst_LastDataPop->value);

        blockload_value.EnergykWhImport += blockload_value_stored.EnergykWhImport;
        blockload_value.EnergykVAhImport += blockload_value_stored.EnergykVAhImport;
        blockload_value.EnergykWhExport += blockload_value_stored.EnergykWhExport;
        blockload_value.EnergykVAhExport += blockload_value_stored.EnergykVAhExport;
        
        blockload_value.NumberOfSample += blockload_value_stored.NumberOfSample;
        blockload_value.Current_R += blockload_value_stored.Current_R;
        blockload_value.Current_Y += blockload_value_stored.Current_Y;
        blockload_value.Current_B += blockload_value_stored.Current_B;

        blockload_value.Voltage_R += blockload_value_stored.Voltage_R;
        blockload_value.Voltage_Y += blockload_value_stored.Voltage_Y;
        blockload_value.Voltage_B += blockload_value_stored.Voltage_B;
    }

	/* Write accumulated value to EEPROM */
	EPR_Write(cell_addr, (uint8_t*)&blockload_value, g_bl_table_header_config.LogSize);
	{
		g_bl_table_header.ColumnInUse = column_index + 1;
	}

	return TRUE;
}

/******************************************************************************
* Function Name : R_LOADSURVEY_RecordBlockLoad_InFlash
* Interface     : void R_LOADSURVEY_RecordBlockLoad_InFlash(
*               :    r_loadsurvey_rtc_t           *p_capture_time,
*               :    EM_INST_READ_PARAMS           *p_inst_values,
*               : );
* Description   : This function will add data of p_log into EEPROM buffer.
*               : The entries_in_used and write_pos will be increased
*               : Rollover happend when entries_in_used > max_entries
* Arguments     :
*               : p_log                   : Buffer that contain data of entry
*               : log_size                : Size of p_log data
*               : p_storage_table_map     : Address of EEPROM
*               :             It shall include Address of
*               :                     [buffer_info]
*               :                     [Data table]
* Function Calls:
* Return Value  : TRUE (0)     : Result success
*               : Other       (!=0) : The logging has (an) error(s).
******************************************************************************/
static uint8_t R_LOADSURVEY_RecordBlockLoad_InFlash(void)
{
	uint32_t one_entry_size = g_bl_table_header_config.LogSize;
    uint32_t table_capture_time_base_addr = g_bl_table_header_config.TableTimeCaptureStartAddr;
    uint32_t table_log_base_addr = g_bl_table_header_config.TableStartAddr;

    rtc_counter_value_t capture_time;
    EM_INST_READ_PARAMS inst_values;
	// Calculate row index
	uint32_t row_addr = 0;
    uint32_t row_addr_spi = 0;
	uint32_t row_index = 0;

	uint16_t column_index = 0;
	uint32_t cell_addr = 0;
    
	uint32_t row_size_eepr;

    one_block_storage_t blockload_value;
    one_block_storage_t blockload_value_stored;
    
	/*
	*  Capture time:
    *                [T1] [T2] [T3]       [Tn]
    *
    *  Blockload table cell indexing (NOT ROLLEDOVER YET)
	*
	*                | Col   | Col 1  | Col 2  | Col 3  |  ...  | Col 47
	*        --------+-------|--------|--------|--------|-------|---------
	*        Row 0   | 0     |  1     |  2     |  3     |  ...  |  47
	*        Row 1   | 48    |  49    |  50    |  51    |  ...  |  95
	*        Row 2   | 96    |  97    |  98    |  99    |  ...  |  143
	*        Row 3   | 144   |  145   |  146   |  147   |  ...  |  191
	*        Row 4   | 192   |  193   |  194   |  195   |  ...  |  239
	*                | ...   |  ...   |  ...   |  ...   |  ...  |  ...
	*        Row 34  | 1632  |  1633  | 1634   |  1635  |  ...  |  1679
	*        Row 35  | ----  |  ----  | ----   |  ----  |  ...  |  ----      (Buffer row)
	*/

	/* Pre-calculation */
	row_size_eepr = g_number_entry_per_row * one_entry_size;
    row_index = GetRowIdToWrite();
    memset(&blockload_value_stored, 0, sizeof(one_block_storage_t));
    memcpy(&capture_time, &gp_inst_LastDataPop->capture_time, sizeof(rtc_counter_value_t));

	if (capture_time.year == 0u ||
		capture_time.month == 0u ||
		capture_time.day == 0u ||
		g_last_capture_time.year ==0 ||
		g_last_capture_time.month == 0||
		g_last_capture_time.day == 0)
	{
        // Clear Data in Epprom
        ClearStorageRegion(table_log_base_addr, row_size_eepr);     // Prepare row, ~ 2 * 32 * 48 bytes = 3072 bytes

        R_BLOCKLOAD_SPI_ClearRow(row_index);

        /* Update new capture time */
        row_addr = table_capture_time_base_addr + row_index * g_bl_table_header_config.CaptureTimeSize;
        EPR_Write(row_addr, (uint8_t *)&capture_time, g_bl_table_header_config.CaptureTimeSize);
		g_last_capture_time = capture_time;
	}
	else if (capture_time.year    != g_last_capture_time.year ||
		     capture_time.month   != g_last_capture_time.month ||
		     capture_time.day     != g_last_capture_time.day)
	{       
        AddNewRow(&capture_time);
        row_index = GetRowIdToWrite();
	}

	/* Write current block */
	{
		column_index = (uint16_t)(capture_time.hour * 60 + capture_time.min) / (R_BLOCKLOAD_CAPTURE_INTERVAL);
		cell_addr = BLOCKLOAD_ENTRIES_TABLE_START_ADDR + row_index * BLOCKLOAD_SERIAL_FLASH_BLOCK_SIZE +  column_index * one_entry_size;
	}

    /* Accumulate to current slot */
    {
        GetBlockloadFromSnapshot(&blockload_value, &gp_inst_LastDataPop->value);
    }

	/* Write accumulated value to SPI Flash */
	BL_SFL_DeviceWrite(cell_addr, (uint8_t*)&blockload_value, g_bl_table_header_config.LogSize);
	{
		g_bl_table_header.ColumnInUse = column_index + 1;
	}

	return TRUE;
}
/******************************************************************************
* Function Name : R_DAILYLOAD_GetEntryByIndex
* Interface     : uint8_t R_DAILYLOAD_GetEntryByIndex(uint32_t entry_index, r_daily_load_t *p_OutData);
* Description   : Collect the data from EEPROM
* Arguments     : uint32_t entry_index
* Function Calls:
* Return Value  : TRUE (1) : Get success, FALSE (0): Get failed
******************************************************************************/
uint8_t R_DAILYLOAD_GetEntryByIndex(uint32_t entry_index, r_daily_load_t *p_OutData)
{
    uint32_t ReadAddr;
    uint32_t ReadIndex;

    one_daily_log_storage entry_from_storage;
    r_loadsurvey_rtc_t capture_time;

    /* Error check */
    if (p_OutData == 0)
    {
        return FALSE;
    }

    if (entry_index > g_dl_table_header.EntryInUse)
    {
        return FALSE;
    }

    /* Init */
    memset(&entry_from_storage, 0, g_dl_table_header_config.LogSize);
    memset(p_OutData, 0, sizeof(r_daily_load_t));

    /* Get log data */
    ReadIndex = (entry_index + g_dl_table_header.FirstEntryIndex) % g_dl_table_header_config.MaxEntries;

    ReadAddr =  g_dl_table_header_config.TableStartAddr;
    ReadAddr += ReadIndex * g_dl_table_header_config.LogSize;
    if (EPR_Read(ReadAddr, (uint8_t *)(void *)&entry_from_storage, g_dl_table_header_config.LogSize) != EPR_OK)
    {
        return FALSE;
    }

    /* Convert from storage (compact data type) to display type */
    ExtractStorageDataToDailyLoad(p_OutData, &capture_time, &entry_from_storage);

    return TRUE;
}

/******************************************************************************
* Function Name : R_LOADSURVEY_RecordDailyLoad
* Interface     : void R_LOADSURVEY_RecordDailyLoad(void)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
static uint8_t R_LOADSURVEY_RecordDailyLoad(void)
{
    /*Daily load recording */
    uint32_t write_addr;
    uint32_t entry_index;
    one_daily_log_storage daily_load;

    entry_index = (g_dl_table_header.FirstEntryIndex + g_dl_table_header.EntryInUse) % g_dl_table_header_config.MaxEntries;

    write_addr = g_dl_table_header_config.TableStartAddr;
    write_addr += g_dl_table_header_config.LogSize * entry_index;

    GetDailyloadFromSnapshot(&daily_load, gp_inst_LastDataPop);

    EPR_Write(write_addr, (uint8_t*)(void *)&daily_load, g_dl_table_header_config.LogSize);

    if (g_dl_table_header.EntryInUse < g_dl_table_header_config.MaxEntries)
    {
        g_dl_table_header.EntryInUse++;
    }
    else
    {
        g_dl_table_header.FirstEntryIndex++;
        g_dl_table_header.FirstEntryIndex %= g_dl_table_header_config.MaxEntries;
    }

    return TRUE;
}

uint8_t R_BILLING_Get_CurrentCycleBillingParameters(r_billing_t *p_OutData);
/******************************************************************************
* Function Name : R_BILLING_Get_CurrentCycleBillingParameters
* Interface     : uint8_t R_BILLING_Get_CurrentCycleBillingParameters(parameter)
* Description   :
* Arguments     :
* Return Value  : TRUE (1) : Get success, FALSE (0): Get failed
******************************************************************************/
uint8_t R_BILLING_Get_CurrentCycleBillingParameters(r_billing_t *p_OutData)
{
    float32_t f32_value;
    rtc_counter_value_t e_datetime_value;

    /* Error check */
    if (p_OutData == 0)
    {
        return FALSE;
    }

    /* Get from inst snapshot */
    memcpy(&p_OutData->CaptureTime, &gp_inst_LastDataPop->capture_time, sizeof(rtc_counter_value_t));

    p_OutData->AveragePowerFactor = (R_LOADSURVEY_GetCurrentAveragePF());

    p_OutData->CumulativeEnergykWh = (R_TARIFF_GetImportActiveEnergyTotal());
    p_OutData->CumulativeEnergykVAh = (R_TARIFF_GetImportApparentEnergyTotal());

    p_OutData->CumulativeEnergykWh_Export = (R_TARIFF_GetExportActiveEnergyTotal());
    p_OutData->CumulativeEnergykVAh_Export = (R_TARIFF_GetExportApparentEnergyTotal());

    /* Get value from tariff */
    R_TARIFF_GetImportActiveEnergyTariff(0, &f32_value);
    p_OutData->CumulativeEnergykWh_TZ1 = (f32_value);
    R_TARIFF_GetImportActiveEnergyTariff(1, &f32_value);
    p_OutData->CumulativeEnergykWh_TZ2 = (f32_value);
    R_TARIFF_GetImportActiveEnergyTariff(2, &f32_value);
    p_OutData->CumulativeEnergykWh_TZ3 = (f32_value);
    R_TARIFF_GetImportActiveEnergyTariff(3, &f32_value);
    p_OutData->CumulativeEnergykWh_TZ4 = (f32_value);
    R_TARIFF_GetImportActiveEnergyTariff(4, &f32_value);
    p_OutData->CumulativeEnergykWh_TZ5 = (f32_value);
    R_TARIFF_GetImportActiveEnergyTariff(5, &f32_value);
    p_OutData->CumulativeEnergykWh_TZ6 = (f32_value);
    R_TARIFF_GetImportActiveEnergyTariff(6, &f32_value);
    p_OutData->CumulativeEnergykWh_TZ7 = (f32_value);
    R_TARIFF_GetImportActiveEnergyTariff(7, &f32_value);
    p_OutData->CumulativeEnergykWh_TZ8 = (f32_value);

    R_TARIFF_GetImportApparentEnergyTariff(0, &f32_value);
    p_OutData->CumulativeEnergykVAh_TZ1 = (f32_value);
    R_TARIFF_GetImportApparentEnergyTariff(1, &f32_value);
    p_OutData->CumulativeEnergykVAh_TZ2 = (f32_value);
    R_TARIFF_GetImportApparentEnergyTariff(2, &f32_value);
    p_OutData->CumulativeEnergykVAh_TZ3 = (f32_value);
    R_TARIFF_GetImportApparentEnergyTariff(3, &f32_value);
    p_OutData->CumulativeEnergykVAh_TZ4 = (f32_value);
    R_TARIFF_GetImportApparentEnergyTariff(4, &f32_value);
    p_OutData->CumulativeEnergykVAh_TZ5 = (f32_value);
    R_TARIFF_GetImportApparentEnergyTariff(5, &f32_value);
    p_OutData->CumulativeEnergykVAh_TZ6 = (f32_value);
    R_TARIFF_GetImportApparentEnergyTariff(6, &f32_value);
    p_OutData->CumulativeEnergykVAh_TZ7 = (f32_value);
    R_TARIFF_GetImportApparentEnergyTariff(7, &f32_value);
    p_OutData->CumulativeEnergykVAh_TZ8 = (f32_value);

    /* Get from MDM application */
    p_OutData->MDkW = (R_MDM_GetActiveMaxDemand());
    R_MDM_GetActiveMaxDemandCapturedTime(&e_datetime_value);                                 
    memcpy(&p_OutData->MDkWDateTime, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetActiveMaxDemandTz(0, &f32_value);
    p_OutData->MDkW_TZ1 = (f32_value);                
    R_MDM_GetMaxDemandActiveCapturedTimeTz(0, &e_datetime_value);                             
    memcpy(&p_OutData->MDkWDateTime_TZ1, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetActiveMaxDemandTz(1, &f32_value);
    p_OutData->MDkW_TZ2 = (f32_value);                
    R_MDM_GetMaxDemandActiveCapturedTimeTz(1, &e_datetime_value);                             
    memcpy(&p_OutData->MDkWDateTime_TZ2, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetActiveMaxDemandTz(2, &f32_value);
    p_OutData->MDkW_TZ3 = (f32_value);                
    R_MDM_GetMaxDemandActiveCapturedTimeTz(2, &e_datetime_value);                             
    memcpy(&p_OutData->MDkWDateTime_TZ3, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetActiveMaxDemandTz(3, &f32_value);
    p_OutData->MDkW_TZ4 = (f32_value);                
    R_MDM_GetMaxDemandActiveCapturedTimeTz(3, &e_datetime_value);                             
    memcpy(&p_OutData->MDkWDateTime_TZ4, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetActiveMaxDemandTz(4, &f32_value);
    p_OutData->MDkW_TZ5 = (f32_value);                
    R_MDM_GetMaxDemandActiveCapturedTimeTz(4, &e_datetime_value);                             
    memcpy(&p_OutData->MDkWDateTime_TZ5, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetActiveMaxDemandTz(5, &f32_value);
    p_OutData->MDkW_TZ6 = (f32_value);                
    R_MDM_GetMaxDemandActiveCapturedTimeTz(5, &e_datetime_value);                             
    memcpy(&p_OutData->MDkWDateTime_TZ6, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetActiveMaxDemandTz(6, &f32_value);
    p_OutData->MDkW_TZ7 = (f32_value);                
    R_MDM_GetMaxDemandActiveCapturedTimeTz(6, &e_datetime_value);                             
    memcpy(&p_OutData->MDkWDateTime_TZ7, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetActiveMaxDemandTz(7, &f32_value);
    p_OutData->MDkW_TZ8 = (f32_value );                
    R_MDM_GetMaxDemandActiveCapturedTimeTz(7, &e_datetime_value);                             
    memcpy(&p_OutData->MDkWDateTime_TZ8, &e_datetime_value, sizeof(e_datetime_value));

    p_OutData->MDkVA = (R_MDM_GetApparentMaxDemand());
    R_MDM_GetApparentMaxDemandCapturedTime(&e_datetime_value);                                 
    memcpy(&p_OutData->MDkVADateTime, &e_datetime_value, sizeof(e_datetime_value));    
    R_MDM_GetApparentMaxDemandTz(0, &f32_value);
    p_OutData->MDkVA_TZ1 = (f32_value);              
    R_MDM_GetMaxDemandApparentCapturedTimeTz(0, &e_datetime_value);                             
    memcpy(&p_OutData->MDkVADateTime_TZ1, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetApparentMaxDemandTz(1, &f32_value);
    p_OutData->MDkVA_TZ2 = (f32_value);              
    R_MDM_GetMaxDemandApparentCapturedTimeTz(1, &e_datetime_value);                             
    memcpy(&p_OutData->MDkVADateTime_TZ2, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetApparentMaxDemandTz(2, &f32_value);
    p_OutData->MDkVA_TZ3 = (f32_value);              
    R_MDM_GetMaxDemandApparentCapturedTimeTz(2, &e_datetime_value);                             
    memcpy(&p_OutData->MDkVADateTime_TZ3, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetApparentMaxDemandTz(3, &f32_value);
    p_OutData->MDkVA_TZ4 = (f32_value);              
    R_MDM_GetMaxDemandApparentCapturedTimeTz(3, &e_datetime_value);                             
    memcpy(&p_OutData->MDkVADateTime_TZ4, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetApparentMaxDemandTz(4, &f32_value);
    p_OutData->MDkVA_TZ5 = (f32_value);              
    R_MDM_GetMaxDemandApparentCapturedTimeTz(4, &e_datetime_value);                             
    memcpy(&p_OutData->MDkVADateTime_TZ5, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetApparentMaxDemandTz(5, &f32_value);
    p_OutData->MDkVA_TZ6 = (f32_value);              
    R_MDM_GetMaxDemandApparentCapturedTimeTz(5, &e_datetime_value);                             
    memcpy(&p_OutData->MDkVADateTime_TZ6, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetApparentMaxDemandTz(6, &f32_value);
    p_OutData->MDkVA_TZ7 = (f32_value);              
    R_MDM_GetMaxDemandApparentCapturedTimeTz(6, &e_datetime_value);                             
    memcpy(&p_OutData->MDkVADateTime_TZ7, &e_datetime_value, sizeof(e_datetime_value));
    R_MDM_GetApparentMaxDemandTz(7, &f32_value);
    p_OutData->MDkVA_TZ8 = (f32_value);              
    R_MDM_GetMaxDemandApparentCapturedTimeTz(7, &e_datetime_value);                             
    memcpy(&p_OutData->MDkVADateTime_TZ8, &e_datetime_value, sizeof(e_datetime_value));

    /* Get total power on duration */
    p_OutData->PowerONduration = g_billing_power_on_duration;

    /* Quadrant energy */
    p_OutData->CumulativeEnergykVArh_QI = (R_TARIFF_GetImportInductiveReactiveEnergyTotal());
    p_OutData->CumulativeEnergykVArh_QII = (R_TARIFF_GetExportCapacitiveReactiveEnergyTotal());
    p_OutData->CumulativeEnergykVArh_QIII = (R_TARIFF_GetExportInductiveReactiveEnergyTotal());
    p_OutData->CumulativeEnergykVArh_QIV = (R_TARIFF_GetImportCapacitiveReactiveEnergyTotal());

    return TRUE;
}

/******************************************************************************
* Function Name : R_BILLING_GetEntryByIndex
* Interface     : uint8_t R_BILLING_GetEntryByIndex(uint32_t entry_index, r_billing_t *p_OutData)
* Description   : Collect the data from EEPROM
* Arguments     : uint32_t entry_index
* Function Calls:
* Return Value  : TRUE (1) : Get success, FALSE (0): Get failed
******************************************************************************/
uint8_t R_BILLING_GetEntryByIndex(uint32_t entry_index, r_billing_t *p_OutData)
{
    uint32_t ReadAddr;
    uint32_t ReadIndex;

    one_billing_log_storage billing_entry_from_storage;
    r_loadsurvey_rtc_t capture_time;

    /* Error check */
    if (p_OutData == 0)
    {
        return FALSE;
    }

    if (entry_index > g_billing_table_header.EntryInUse)
    {
        return FALSE;
    }

    /* Init */
    memset(&billing_entry_from_storage, 0, g_billing_table_header_config.LogSize);
    memset(p_OutData, 0, sizeof(r_billing_t));

    /* Get log data */
    ReadIndex = (entry_index + g_billing_table_header.FirstEntryIndex) %g_billing_table_header_config.MaxEntries;

    ReadAddr = g_billing_table_header_config.TableStartAddr;
    ReadAddr += ReadIndex * g_billing_table_header_config.LogSize;
    if (EPR_Read(ReadAddr, (uint8_t *)(void *)&billing_entry_from_storage, g_billing_table_header_config.LogSize) != EPR_OK)
    {
        return FALSE;
    }

    /* Convert from storage (compact data type) to display type */
    ExtractStorageDataToBilling(p_OutData, &capture_time, &billing_entry_from_storage);

    return TRUE;
}

/******************************************************************************
* Function Name : R_BILLING_OnBillGenerated
* Interface     : void R_BILLING_OnBillGenerated(void)
* Description   : This function will be called after bill generated to do clear job
*                 as reset md counter.
* Arguments     :
* Return Value  : void
******************************************************************************/
static void R_BILLING_OnBillGenerated(void)
{
    /* Update counter */
    g_billing_backup_data.acc_active 	= R_TARIFF_GetImportActiveEnergyTotal();
    g_billing_backup_data.acc_apparent 	= R_TARIFF_GetImportApparentEnergyTotal();

    /* Increase billing counter each time generate bill */
    g_billing_counter++;
    EPR_Write(BILLING_COUNTER_ADDR,                 // billing counter is not regularly happend every day
                (uint8_t *)&g_billing_counter,      // can do backup immediatelly 
                sizeof(uint32_t));

    /* Report to event that billing counter is increase */
    g_event_flag.bits.bill_counter = TRUE;

    /* Reset Max demand counter */
    R_MDM_Reset();

}

static void R_LOADSURVEY_RecordBilling(void);
/******************************************************************************
* Function Name : R_LOADSURVEY_RecordBilling
* Interface     : void R_LOADSURVEY_RecordBilling()
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
static void R_LOADSURVEY_RecordBilling(void)
{
    /* Daily load recording */
    uint32_t write_addr;
    uint32_t entry_index;
    one_billing_log_storage billing;

    entry_index = (g_billing_table_header.FirstEntryIndex + g_billing_table_header.EntryInUse) % g_billing_table_header_config.MaxEntries;

    write_addr = g_billing_table_header_config.TableStartAddr;
    write_addr += g_billing_table_header_config.LogSize * entry_index;

    GetBillingloadFromSnapshot(&billing);

    EPR_Write(write_addr, (uint8_t*)(void *)&billing, g_billing_table_header_config.LogSize);

    if (g_billing_table_header.EntryInUse < g_billing_table_header_config.MaxEntries)
    {
        g_billing_table_header.EntryInUse++;
    }
    else
    {
        g_billing_table_header.FirstEntryIndex++;
        g_billing_table_header.FirstEntryIndex %= g_billing_table_header_config.MaxEntries;
    }

    R_BILLING_OnBillGenerated();

    return;
}

/******************************************************************************
* Function Name : R_BILLING_GetLastActiveEnergyImport
* Interface     : uint8_t R_BILLING_GetLastActiveEnergyImport(float32_t *p_cumulative_energy)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_BILLING_GetLastActiveEnergyImport(float32_t *p_cumulative_energy)
{
    r_billing_t biling;
    
    if (g_billing_table_header.EntryInUse == 0)
    {
        *p_cumulative_energy = R_TARIFF_GetImportActiveEnergyTotal();
    }
    else
    {
        R_BILLING_GetEntryByIndex((g_billing_table_header.EntryInUse - 1), &biling);
        *p_cumulative_energy = R_TARIFF_GetImportActiveEnergyTotal() - biling.CumulativeEnergykWh;
    }

    return TRUE;
}


/******************************************************************************
* Function Name : IsBlockLoadPeriodEnd
* Interface     : uint8_t IsBlockLoadPeriodEnd(void)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
static uint8_t IsBlockLoadPeriodEnd(void)
{
    return g_event_request_flag.is_blockload_request;
}

/******************************************************************************
* Function Name : IsDailyLoadPeriodEnd
* Interface     : uint8_t IsDailyLoadPeriodEnd(void)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
static uint8_t IsDailyLoadPeriodEnd(void)
{
    return g_event_request_flag.is_dailyload_request;
}

/******************************************************************************
* Function Name : IsBillingScheduleEnd
* Interface     : uint8_t IsBillingScheduleEnd(void)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
static uint8_t IsBillingScheduleEnd(void)
{
    return g_event_request_flag.is_billing_request;
}

/******************************************************************************
* Function Name : R_BLOCKLOAD_SetProfileCapturePeriod
* Interface     : uint8_t R_BLOCKLOAD_SetProfileCapturePeriod(uint16_t period)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_BLOCKLOAD_SetProfileCapturePeriod(uint16_t period)
{
    g_blockload_capture_period = period;

    return TRUE;
}


/******************************************************************************
* Function Name : R_BLOCKLOAD_GetProfileCapturePeriod
* Interface     : uint8_t R_BLOCKLOAD_GetProfileCapturePeriod(uint16_t *p_period)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_BLOCKLOAD_GetProfileCapturePeriod(uint16_t *p_period)
{
    if (p_period == NULL)
    {
        return FALSE;
    }
    
    if (g_blockload_capture_period == 0)
    {
        g_blockload_capture_period = BLOCKLOAD_CAPTURE_PERIOD_DEFAULT;
    }
    *p_period = g_blockload_capture_period;

    return TRUE;
}

/******************************************************************************
* Function Name : R_BLOCKLOAD_GetAverageCurrent
* Interface     : void R_BLOCKLOAD_GetAverageCurrent(float32_t *p_out_data)
* Description   : Get instantaneous value of Average Current of current block
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_BLOCKLOAD_GetAverageCurrent(float32_t *p_out_data)
{
    //TO DO
    float32_t apparent_counter = 0.0f;
    float32_t voltage_avg = 0.0f;

    float32_t block_kVAh_import;
    float32_t block_kVAh_export;
    
    uint16_t total_sample_per_sec;

    if (p_out_data == NULL)
    {
        return;
    }

    block_kVAh_import =  R_TARIFF_GetImportApparentEnergyTotal() - g_block_backup_data.OldEnergykVAhImport;
    block_kVAh_export =  R_TARIFF_GetExportApparentEnergyTotal() - g_block_backup_data.OldEnergykVAhExport;

    apparent_counter = block_kVAh_import + block_kVAh_export;

    R_BLOCKLOAD_GetAverageVoltage(&voltage_avg);
    
    total_sample_per_sec = g_block_backup_data.Counter;

    *p_out_data  =  CalculateAvgCurrentFromOtherParams(
                        voltage_avg,
                        apparent_counter,
                        total_sample_per_sec
                    );
}

/******************************************************************************
* Function Name : R_BLOCKLOAD_GetAverageVoltage
* Interface     : void R_BLOCKLOAD_GetAverageVoltage(float32_t *p_out_data)
* Description   : Get instantaneous value of Average Voltage of current block
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_BLOCKLOAD_GetAverageVoltage(float32_t *p_out_data)
{
    //TODO
    //*p_out_data = (g_block_backup_data.AccVrms/g_block_backup_data.Counter);
}

/******************************************************************************
* Function Name : AccumulateBlockParameters
* Interface     : void AccumulateBlockParameters(void)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
static void AccumulateBlockParameters(void)
{
    if (gp_inst_DataPop != NULL)
    {
    	if (gp_inst_DataPop->value.vrms[LINE_PHASE_R] >= VRMS_AVERAGE_THRESHOLD||
            gp_inst_DataPop->value.vrms[LINE_PHASE_Y] >= VRMS_AVERAGE_THRESHOLD||
            gp_inst_DataPop->value.vrms[LINE_PHASE_B] >= VRMS_AVERAGE_THRESHOLD)
        {
        	g_block_backup_data.Voltage_R += gp_inst_DataPop->value.vrms[LINE_PHASE_R];
        	g_block_backup_data.Voltage_Y += gp_inst_DataPop->value.vrms[LINE_PHASE_Y];
        	g_block_backup_data.Voltage_B += gp_inst_DataPop->value.vrms[LINE_PHASE_B];
            
            g_block_backup_data.Current_R += gp_inst_DataPop->value.irms[LINE_PHASE_R];
        	g_block_backup_data.Current_Y += gp_inst_DataPop->value.irms[LINE_PHASE_Y];
        	g_block_backup_data.Current_B += gp_inst_DataPop->value.irms[LINE_PHASE_B];
        	g_block_backup_data.Counter++;

        	g_billing_power_on_duration++;
    	}
    }
}

/******************************************************************************
* Function Name : R_LOADSURVEY_GetCurrentAveragePF
* Interface     : float32_t R_LOADSURVEY_GetCurrentAveragePF(void)
* Description   :
* Arguments     :
* Return Value  : float32_t
******************************************************************************/
float32_t R_LOADSURVEY_GetCurrentAveragePF(void)
{
    float32_t average_pf = 0.0f;

    float32_t acc_active    = g_billing_backup_data.acc_active;
    float32_t acc_apparent  = g_billing_backup_data.acc_apparent;

    acc_active = R_TARIFF_GetImportActiveEnergyTotal();
    acc_apparent = R_TARIFF_GetImportApparentEnergyTotal();
    
    acc_active -= g_billing_backup_data.acc_active;
    acc_apparent -= g_billing_backup_data.acc_apparent;

    R_LOADSURVEY_CalculateAveragePF(
        &average_pf,
        acc_active,
        acc_apparent
    );

    return average_pf;
}

/******************************************************************************
* Function Name : R_LOADSURVEY_CalculateAveragePF
* Interface     : void R_LOADSURVEY_CalculateAveragePF(
*                           float32_t *p_out_data, 
*                           float32_t acc_active, 
*                           float32_t acc_apparent)
* Description   : Calculate average PF from Accumulate active energy and Apparent energy
* Arguments     : float32_t acc_active, float32_t acc_apparent
* Return Value  : void
******************************************************************************/
static void R_LOADSURVEY_CalculateAveragePF(
    float32_t *p_out_data,                          /* Output */
    float32_t acc_active,                           /* Input */
    float32_t acc_apparent                          /* Input */
)
{
    float32_t result;

    /* Range check before calculating Average PF */
    if (acc_apparent == 0.0f)
    {
        /* Apparent is zero, division will resulted in Inf, make it 0 */
        result = 0.0f;
    }
    else
    {
        /* Calculate PF:
        *                Average Active Power        Acc Active Energy / Acc Time
        * Average PF = ------------------------ =  --------------------------------
        *               Average Apparent Power      Acc Apparent Energy / Acc Time
        *
        * The acc time is same for both, so it cancelled out
        *
        */
        result = WRP_EXT_Absf(acc_active / acc_apparent);
    }

    /* Limit the range of PF value */
    if (result > 1.0f)
    {
        result = 1.0f;
    }

    *p_out_data = result;

    return;

}

/******************************************************************************
* Function Name : R_BLOCKLOAD_AddSampleOfStandbyMode
* Interface     : void R_BLOCKLOAD_AddSampleOfStandbyMode(
*               :     float32_t v_rms, float32_t i_rms
*               : );
* Description   : Accumulate fixed value of voltage during NM
* Arguments     : V_RMS : Fixed value of voltage during NM
* Function call : This function should be called in neutral missing mode
* Return Value  : void
******************************************************************************/
void R_BLOCKLOAD_AddSampleOfStandbyMode(float32_t v_rms)
{
	//TODO
    if (v_rms >= VRMS_AVERAGE_THRESHOLD)
    {
        //g_block_backup_data.AccVrms += v_rms;
        g_block_backup_data.Counter++;
    }
    else
    {
        /* Ignore sample when Ac lost */
    }
}


/******************************************************************************
* Function Name: void R_LOADSURVEY_PollingProcessing(void)
* Description  : Process blockload
* Arguments    : None
* Return Value : None
******************************************************************************/
void R_LOADSURVEY_PollingProcessing(void)
{	
    AccumulateBlockParameters();
    
    /* Accumulate Power on duration for each minute */
    if (g_event_request_flag.min_interval)
    {
        g_meter_power_on_duration++;
        g_billing_power_on_duration++;

        g_event_request_flag.min_interval = FALSE;
    }
    if (IsBlockLoadPeriodEnd() == TRUE)
    {   
        if( g_bl_table_header.IsAbnormal == TRUE)
        {
            R_LOADSURVEY_RecordBlockLoad_InEEPROM();
        }
        else 
        {
            R_LOADSURVEY_RecordBlockLoad_InFlash();
        }
        g_event_request_flag.is_blockload_request = FALSE;
    }

    if (IsDailyLoadPeriodEnd() == TRUE)
    {
        R_LOADSURVEY_RecordDailyLoad();
        g_event_request_flag.is_dailyload_request = FALSE;
    }

    if (IsBillingScheduleEnd() == TRUE)
    {
        g_billing_date = gp_inst_LastDataPop->capture_time;
        R_LOADSURVEY_RecordBilling();
        g_event_request_flag.is_billing_request = FALSE;
    }

    if (gp_inst_DataPop != 0 && g_meter_wakup_checked == FALSE)
    {
        check_and_fill_empty_entry_on_meterwakeup();
    }
}

/******************************************************************************
* Function Name : loadsurvey_error_check
* Interface     : void loadsurvey_error_check(void)
* Description   : For each 1s, do check the intergity of load survey data
* Arguments     :
* Return Value  : void
******************************************************************************/
static void check_and_fill_empty_entry_on_meterwakeup(void)
{
    uint8_t min;
    uint8_t hour;
    uint16_t timestamp;
    uint16_t timestamp_index;
    if (g_bl_table_header.ColumnInUse == 0 &&
        g_bl_table_header.RowInUse == 0 &&
        g_bl_table_header.FirstRowIndex == 0 &&
        g_meter_wakup_checked == FALSE)
    {
        g_block_backup_data.OldEnergykWhImport  = R_TARIFF_GetImportActiveEnergyTotal();
        g_block_backup_data.OldEnergykVAhImport = R_TARIFF_GetImportApparentEnergyTotal();
        g_block_backup_data.OldEnergykWhExport  = R_TARIFF_GetExportActiveEnergyTotal();
        g_block_backup_data.OldEnergykVAhExport = R_TARIFF_GetExportApparentEnergyTotal();
    
        hour = gp_inst_LastDataPop->capture_time.hour;
        min = gp_inst_LastDataPop->capture_time.min;

        timestamp = hour * 60 + min;
        timestamp_index = (uint16_t)(timestamp / R_BLOCKLOAD_CAPTURE_INTERVAL);
        if (timestamp_index > 1)
        {
            R_LOADSURVEY_AccumulateCurrentBlock();
        }
        
        g_meter_wakup_checked = TRUE;
    }
}

/******************************************************************************
* Function Name : R_LOADSURVEY_AccumulateCurrentBlock
* Interface     : void R_LOADSURVEY_AccumulateCurrentBlock(void)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_LOADSURVEY_AccumulateCurrentBlock(void)
{
    uint32_t one_entry_size = g_bl_table_header_config.LogSize;
    uint32_t table_capture_time_base_addr = g_bl_table_header_config.TableTimeCaptureStartAddr;
    uint32_t table_log_base_addr = g_bl_table_header_config.TableStartAddr;

    rtc_counter_value_t capture_time;
    //EM_INST_READ_PARAMS inst_values;

	// Calculate row index
	uint32_t row_addr = 0;
    uint32_t row_addr_spi = 0;
	uint32_t row_id = 0;
    
	uint16_t column_index = 0;
	uint32_t cell_addr = 0;

	uint32_t row_size_eepr;

    one_block_storage_t blockload_value;
    one_block_storage_t blockload_value_stored;

	/*
	*  Capture time:
    *                [T1] [T2] [T3]       [Tn]
    *
    *  Blockload table cell indexing (NOT ROLLEDOVER YET)
	*
	*                | Col   | Col 1  | Col 2  | Col 3  |  ...  | Col 47
	*        --------+-------|--------|--------|--------|-------|---------
	*        Row 0   | 0     |  1     |  2     |  3     |  ...  |  47
	*        Row 1   | 48    |  49    |  50    |  51    |  ...  |  95
	*        Row 2   | 96    |  97    |  98    |  99    |  ...  |  143
	*        Row 3   | 144   |  145   |  146   |  147   |  ...  |  191
	*        Row 4   | 192   |  193   |  194   |  195   |  ...  |  239
	*                | ...   |  ...   |  ...   |  ...   |  ...  |  ...
	*        Row 34  | 1632  |  1633  | 1634   |  1635  |  ...  |  1679
	*        Row 35  | ----  |  ----  | ----   |  ----  |  ...  |  ----      (Buffer row)
	*/

	/* Pre-calculation */
	row_size_eepr = g_number_entry_per_row * one_entry_size;
    memset(&blockload_value_stored, 0, sizeof(one_block_storage_t));
	if (g_event_request_flag.is_blockload_request == TRUE)
	{
    	memcpy(&capture_time, &gp_inst_LastDataPop->capture_time, sizeof(rtc_counter_value_t));
	}
	else
	{
		memcpy(&capture_time, &g_meter_wakekup_data.rtc_old, sizeof(rtc_counter_value_t));
	}
	
    row_id = GetRowIdToWrite();

	if (capture_time.year == 0u ||
		capture_time.month == 0u ||
		capture_time.day == 0u ||
		g_last_capture_time.year ==0 ||
		g_last_capture_time.month == 0||
		g_last_capture_time.day == 0)
	{
        // Clear Data in Epprom
        ClearStorageRegion(table_log_base_addr, row_size_eepr);     // Prepare row, ~ 2 * 20 * 48 bytes = 1920 bytes
        
        R_BLOCKLOAD_SPI_ClearRow(row_id);
        
        memcpy(&capture_time, &gp_inst_LastDataPop->capture_time, sizeof(rtc_counter_value_t));

        /* Update new capture time */
        row_addr = table_capture_time_base_addr + row_id * g_bl_table_header_config.CaptureTimeSize;
        EPR_Write(row_addr, (uint8_t *)&capture_time, g_bl_table_header_config.CaptureTimeSize);
		g_last_capture_time = capture_time;
        
        column_index = (uint16_t)(capture_time.hour * 60 + capture_time.min) / (R_BLOCKLOAD_CAPTURE_INTERVAL);
        g_bl_table_header.ColumnInUse = column_index;
	}
	else if (capture_time.year    != g_last_capture_time.year ||
		     capture_time.month   != g_last_capture_time.month ||
		     capture_time.day     != g_last_capture_time.day)
	{   
        if(g_bl_table_header.IsAbnormal == TRUE)
        {
            R_BLOCKLOAD_TransferEepromToFlash();    
            g_bl_table_header.IsAbnormal = FALSE;
        }
        AddNewRow(&capture_time);
	}

	/* Write current block */
	{
		column_index = (uint16_t)(capture_time.hour * 60 + capture_time.min) / (R_BLOCKLOAD_CAPTURE_INTERVAL);
        g_bl_table_header.ColumnInUse = column_index;	
	}
    /* Accumulate to current slot */
    GetBlockloadFromSnapshot(&blockload_value, &gp_inst_LastDataPop->value);

    if ( g_bl_table_header.IsAbnormal == TRUE)  /* Abnormal case */
    {
        cell_addr = table_log_base_addr + column_index * one_entry_size;
        EPR_Read(cell_addr, (uint8_t*)&blockload_value_stored, g_bl_table_header_config.LogSize);
        if (blockload_value_stored.Header_code != 0x5A)
        {
            memset(&blockload_value_stored, 0, g_bl_table_header_config.LogSize);
        }
        blockload_value.EnergykWhImport += blockload_value_stored.EnergykWhImport;
        blockload_value.EnergykVAhImport += blockload_value_stored.EnergykVAhImport;
        blockload_value.EnergykWhExport += blockload_value_stored.EnergykWhExport;
        blockload_value.EnergykVAhExport += blockload_value_stored.EnergykVAhExport;

        blockload_value.NumberOfSample += blockload_value_stored.NumberOfSample;

	    blockload_value.Current_R += blockload_value_stored.Current_R;
	    blockload_value.Current_Y += blockload_value_stored.Current_Y;
	    blockload_value.Current_B += blockload_value_stored.Current_B;

        blockload_value.Voltage_R += blockload_value_stored.Voltage_R;
	    blockload_value.Voltage_Y += blockload_value_stored.Voltage_Y;
	    blockload_value.Voltage_B += blockload_value_stored.Voltage_B;

	    /* Write accumulated value to EEPROM */
	    EPR_Write(cell_addr, (uint8_t*)&blockload_value, g_bl_table_header_config.LogSize);
    }
    else
    {   
        cell_addr = BLOCKLOAD_ENTRIES_TABLE_START_ADDR + row_id * BLOCKLOAD_SERIAL_FLASH_BLOCK_SIZE + column_index * one_entry_size;
        BL_SFL_DeviceWrite(cell_addr, (uint8_t*)&blockload_value, g_bl_table_header_config.LogSize);
    }
    return;
}


/******************************************************************************
* Function Name : R_LOADSURVEY_Recover
* Interface     : void R_LOADSURVEY_Recover(void)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_LOADSURVEY_Recover(void)
{
    R_BLOCKLOAD_Recover();
    R_DAILYLOAD_Recover();
    R_BILLING_Recover();
}


/******************************************************************************
* Function Name : R_LOADSURVEY_RecordMissingDay
* Interface     : uint8_t R_LOADSURVEY_RecordMissingDay(void)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
static uint8_t R_LOADSURVEY_RecordMissingDay(void)
{
    /*Daily load recording */
    uint32_t write_addr;
    uint32_t entry_index;
    one_daily_log_storage daily_load;

    entry_index = (g_dl_table_header.FirstEntryIndex + g_dl_table_header.EntryInUse) % g_dl_table_header_config.MaxEntries;

    write_addr = g_dl_table_header_config.TableStartAddr;
    write_addr += g_dl_table_header_config.LogSize * entry_index;

    GetDailyloadFromSnapshot(&daily_load, &g_meter_wakekup_data.snapshot_old);

    daily_load.CaptureTime.sec = 0;
    daily_load.CaptureTime.min = 0;
    daily_load.CaptureTime.hour = 24;
    daily_load.CaptureTime.day = g_meter_wakekup_data.rtc_old.day;
    daily_load.CaptureTime.month = g_meter_wakekup_data.rtc_old.month;
    daily_load.CaptureTime.year = (uint8_t)g_meter_wakekup_data.rtc_old.year;

    EPR_Write(write_addr, (uint8_t*)(void *)&daily_load, g_dl_table_header_config.LogSize);

    if (g_dl_table_header.EntryInUse < g_dl_table_header_config.MaxEntries)
    {
        g_dl_table_header.EntryInUse++;
    }
    else
    {
        g_dl_table_header.FirstEntryIndex++;
        g_dl_table_header.FirstEntryIndex %= g_dl_table_header_config.MaxEntries;
    }

    return TRUE;
}


/******************************************************************************
* Function Name : R_BLOCKLOAD_TransferFlashBlockToEeprom(void)
* Interface     : static uint8_t R_BLOCKLOAD_TransferFlashBlockToEeprom(void)
*               :
*               : 
* Description   : Transfer 4KBs abnormal block to entries table
* Arguments     :
* Return Value  : Success (TRUE) or failure (FALSE)
******************************************************************************/
static uint8_t R_BLOCKLOAD_TransferFlashBlockToEeprom(void)
{
	uint32_t    row_addr = 0;
    uint16_t    row_id = 0;
	uint16_t	size = 0;
	uint8_t 	status = FALSE;
	uint8_t		page_buffer[BLOCKLOAD_SERIAL_FLASH_PAGE_SIZE];
	//uint8_t		page_check_buffer[BLOCKLOAD_SERIAL_FLASH_PAGE_SIZE];

    row_id = GetRowIdToWrite();
	row_addr = BLOCKLOAD_ENTRIES_TABLE_START_ADDR + row_id * BLOCKLOAD_SERIAL_FLASH_BLOCK_SIZE;

    /* Copy flash to eeprom */
    for (size = 0;
		 size < (12 * BLOCKLOAD_SERIAL_FLASH_PAGE_SIZE);
		 size += BLOCKLOAD_SERIAL_FLASH_PAGE_SIZE)
	{
		status = BL_SFL_DeviceRead(row_addr + size, (uint8_t*)(void *)page_buffer, BLOCKLOAD_SERIAL_FLASH_PAGE_SIZE);
		if (status != 0x00) {
			return FALSE;
		}
		status = EPR_Write(g_bl_table_header_config.TableStartAddr + size, (uint8_t*)(void *)page_buffer, BLOCKLOAD_SERIAL_FLASH_PAGE_SIZE);
		if (status != 0x00) {
			return FALSE;
		}
		//status = EPR_Read(g_bl_table_header_config.TableStartAddr + size, (uint8_t*)(void *)&page_check_buffer, BLOCKLOAD_SERIAL_FLASH_PAGE_SIZE);
		//if (status != 0x00) {
		//	return FALSE;
		//}

		R_WDT_Restart();
	}

	return TRUE;
}
/******************************************************************************
* Function Name : R_BLOCKLOAD_TransferEepromToFlash(void)
* Interface     : static uint8_t R_BLOCKLOAD_TransferEepromToFlash(void)
*               :
*               : 
* Description   : Transfer block data on eeprom to Flash memory 
* Arguments     :
* Return Value  : Success (TRUE) or failure (FALSE)
******************************************************************************/
static uint8_t R_BLOCKLOAD_TransferEepromToFlash(void)
{
	uint32_t    row_addr_flash = 0;
    uint32_t    row_addr_eeprom = 0;
    uint32_t    row_size_eeprom = 0;
    uint16_t    row_id = 0;
	uint16_t	size = 0;
	uint8_t 	status = FALSE;
	uint8_t		page_buffer[BLOCKLOAD_SERIAL_FLASH_PAGE_SIZE];
	//uint8_t		page_check_buffer[BLOCKLOAD_SERIAL_FLASH_PAGE_SIZE];

    row_id = GetRowIdToWrite();
	row_addr_flash = BLOCKLOAD_ENTRIES_TABLE_START_ADDR + row_id * BLOCKLOAD_SERIAL_FLASH_BLOCK_SIZE;

    R_BLOCKLOAD_SPI_ClearRow(row_id);

    /* Copy eeprom to Flash */
    for (size = 0;
		 size < (12 * BLOCKLOAD_SERIAL_FLASH_PAGE_SIZE);
		 size += BLOCKLOAD_SERIAL_FLASH_PAGE_SIZE)
	{
		status = EPR_Read(g_bl_table_header_config.TableStartAddr + size, (uint8_t*)(void *)page_buffer, BLOCKLOAD_SERIAL_FLASH_PAGE_SIZE);
		if (status != 0x00) {
			return FALSE;
		}
		status = BL_SFL_DeviceWrite(row_addr_flash + size, (uint8_t*)(void *)page_buffer, BLOCKLOAD_SERIAL_FLASH_PAGE_SIZE);
		if (status != 0x00) {
			return FALSE;
		}
		
		//status = BL_SFL_DeviceRead(row_addr_flash + size, (uint8_t*)(void *)&page_check_buffer, BLOCKLOAD_SERIAL_FLASH_PAGE_SIZE);
		//if (status != 0x00) {
		//	return FALSE;
		//}

		R_WDT_Restart();
	}

    // Clear Data in Epprom
	row_size_eeprom = g_number_entry_per_row * g_bl_table_header_config.LogSize;
	row_addr_eeprom = g_bl_table_header_config.TableStartAddr;

	ClearStorageRegion(row_addr_eeprom, row_size_eeprom);     // Prepare row, ~ 2 * 32 * 48 bytes = 3072 bytes

	return TRUE;
}
/******************************************************************************
* Function Name : R_BLOCKLOAD_Recover
* Interface     : void R_BLOCKLOAD_Recover(void)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_BLOCKLOAD_Recover(void)
{
    uint32_t row_addr = 0;
    uint32_t entry_id;
    uint32_t current_column;

    if (g_meter_wakekup_data.status == 0)
    {
        current_column = (uint16_t)((g_meter_wakekup_data.rtc_new.hour * 60 +   \
                                                   g_meter_wakekup_data.rtc_new.min)           \
                                                   / (R_BLOCKLOAD_CAPTURE_INTERVAL));

        if (current_column < g_bl_table_header.ColumnInUse)
        {
            /* RTC revert! */
            R_BLOCKLOAD_Reset();
        }
        else
        {
		    /* Update blockload index only */
	        if(g_bl_table_header.IsAbnormal == FALSE)
	        {
	            g_bl_table_header.IsBackWard = TRUE;
	            g_bl_table_header.IsAbnormal = TRUE;
	        }
            /* Update blockload index only */
            g_bl_table_header.ColumnInUse = current_column;
        }                                            
    }
    else if (g_meter_wakekup_data.status < 0)   /* RTC Set Forward More than 1 day */
    {
        if(g_bl_table_header.IsAbnormal == TRUE)
        {
            R_BLOCKLOAD_TransferEepromToFlash(); 
            g_bl_table_header.IsAbnormal = FALSE;
        }
        /* Day is changes */
        AddNewRow(&g_meter_wakekup_data.rtc_new);
		
        g_bl_table_header.ColumnInUse = (uint16_t)((g_meter_wakekup_data.rtc_new.hour * 60 +    \
                                                   g_meter_wakekup_data.rtc_new.min)            \
                                                   / (R_BLOCKLOAD_CAPTURE_INTERVAL));
    }
    else    /* RTC Set Backward */
    {
        if (g_is_season_changed == TRUE)
        {
            if (R_BLOCKLOAD_Get_EntryId_ByDateTime(&g_meter_wakekup_data.rtc_new, 1, &entry_id) == TRUE)
            {
                g_bl_table_header.RowInUse = entry_id / g_number_entry_per_row;
                g_bl_table_header.ColumnInUse = entry_id % g_number_entry_per_row;
                g_bl_table_header.IsRolledOver = FALSE;
			    g_last_capture_time = g_meter_wakekup_data.rtc_new;
			
                g_bl_table_header.IsBackWard = TRUE;
            }
            else
            {
                R_BLOCKLOAD_Reset();
            }
        }
        else
        {
            R_BLOCKLOAD_Reset();
            R_DAILYLOAD_Reset();
        }
    }
}

/******************************************************************************
* Function Name : R_DAILYLOAD_Recover
* Interface     : void R_DAILYLOAD_Recover(void)
* Description   : Generate missed daily load survey log due to meter sleep
* Arguments     : None
* Return Value  : void
******************************************************************************/
void R_DAILYLOAD_Recover(void)
{
    uint32_t entry_id;

    if (g_meter_wakekup_data.status < 0)    /* RTC Set Forward */
    {
        /* Previous day is not recorded due to meter sleep */
        R_LOADSURVEY_RecordMissingDay();
    }
    else if (g_meter_wakekup_data.status > 0) /* RTC Set Backward */
    {
        if (R_DAILYLOAD_Get_StartEntryId_FromDateTime(&g_meter_wakekup_data.rtc_new, &entry_id) == TRUE)
        {
            g_dl_table_header.EntryInUse = entry_id;
        }
    }
    else
    {
        /* Normal. Do nothing. */
    }
}

/******************************************************************************
* Function Name : R_DLMS_BillingController_ShiftToNextBillingDate
* Interface     : void R_DLMS_BillingController_ShiftToNextBillingDate(
*               :     R_DLMS_RTC_T *p_billing_date
*               : );
* Description   : This function will shift current billing date to the next
* Arguments     : None
* Return Value  : Current Billing Date
******************************************************************************/
void IncreaseOneMonth(rtc_counter_value_t *p_rtc_value)
{
	p_rtc_value->month++;
	if (p_rtc_value->month > 12)
	{
		p_rtc_value->month = 1;
		p_rtc_value->year++;
	}
}


/******************************************************************************
* Function Name : R_BILLING_Recover
* Interface     : void R_BILLING_Recover(void)
* Description   : Generate missed bills due to meter sleep over billing period
* Arguments     : None
* Return Value  : void
******************************************************************************/
void R_BILLING_Recover(void)
{
    uint32_t entry_id;
    int8_t status_compare;
    int8_t status_compare1;

    rtc_counter_value_t old_date_time;
    rtc_counter_value_t new_date_time;

    uint8_t date_schedule[4];
    uint8_t time_schedule[3];

    uint8_t is_checked_date = FALSE;

    if (g_meter_wakekup_data.status > 0)        /* RTC Set Backward */
    {
        if (R_BILLING_Get_StartEntryId_FromDateTime(&g_meter_wakekup_data.rtc_new, &entry_id) == TRUE)
        {
            g_billing_table_header.EntryInUse = entry_id;
        }
    }
    else        /* RTC Set Forward */
    {
        do
        {
            if (is_checked_date == FALSE)
            {
            	memcpy(&old_date_time, &g_meter_wakekup_data.rtc_old, sizeof(rtc_counter_value_t));

            	R_SCHEDULER_ExecutionDateGet(date_schedule, SCHEDULER_ID_BILLING, 0);
            	old_date_time.day = date_schedule[3];
            	R_SCHEDULER_ExecutionTimeGet(time_schedule, SCHEDULER_ID_BILLING, 0);
            	old_date_time.hour = time_schedule[0];
            	old_date_time.min = time_schedule[1];
            	old_date_time.sec = time_schedule[2];

          
                status_compare1 = CompareDateTime(&g_meter_wakekup_data.rtc_old, &old_date_time);   
                status_compare = CompareDateTime(&old_date_time, &g_meter_wakekup_data.rtc_new);
                is_checked_date = TRUE;
            }
            else
            {
                /* Shift to next billing date */
                IncreaseOneMonth(&old_date_time);
                status_compare1 = (-1);
                status_compare = CompareDateTime(&old_date_time, &g_meter_wakekup_data.rtc_new);
            }

            /* 
             * Generate for all billing date that:
             *      (1) RTC OLD < BillingDate < RTC NEW
             *      (2) Biling date satify scheduler form
             */
            if (status_compare <= 0 && status_compare1 < 0)
            {
                memcpy(&g_billing_date, &old_date_time, sizeof(rtc_counter_value_t));
                R_LOADSURVEY_RecordBilling();
            }

            R_WDT_Restart();

        } while (status_compare <= 0);
    }
}


/******************************************************************************
* Function Name : R_LoadSurvey_FindNextDay
* Interface     : void R_LoadSurvey_FindNextDay(void)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_LoadSurvey_FindNextDay(r_loadsurvey_rtc_t  *p_capture_time)
{
    /*! The number day of month */
    const int nDayOfMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    uint16_t ndays;
    uint16_t year;
    {
        year = p_capture_time->year + 2000;

        /*=======================================================================*/
        ndays = nDayOfMonth[p_capture_time->month-1];
        if (p_capture_time->month==2)
        {
            if ( ( ((year)%100==0) && ((year)%400==0) ) ||
                (  (year)%4==0 ) )
            {
                ndays = 29;
            }
        }

        p_capture_time->day += 1;
        p_capture_time->week += 1;
        if (p_capture_time->week > 7)
        {
            p_capture_time->week = 1;
        }

        if ( p_capture_time->day > ndays )
        {
            p_capture_time->day = 1;
            p_capture_time->month++;
        }
        if ( p_capture_time->month > 12 )
        {
            p_capture_time->month = 1;
            p_capture_time->year++;
            if (year > 99)
            {
                year = 0;
            }
        }
    }
}
