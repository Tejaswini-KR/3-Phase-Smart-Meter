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
* File Name    : bl_image.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : 
* Description  : Image processing
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Drivers */
#include "bl_r_cg_macrodriver.h"
#include "bl_r_cg_sau.h"

/* Display module */
#include "bl_display.h"

/* Core functions */
#include "bl_header.h"

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/* Masking for reset flag in RESF registers */
#define TRAP                0x80
#define WDTRF               0x10
#define RPERF               0x04
#define IAWRF               0x02
#define LVIRF               0x01
/* Define the maximum number of false reset, 
 * After number of specified, the back up image in external memory will transferred back to ROM 
*/
#define BL_MAX_CONTINUOUS_FAULTY_RESET      (5)

/* Address of hash storage area in external memory
 * Place in the final block of memory
 * This act as a second lock in activating the image
*/
#define OLD_IMAGE_HASH_STORAGE_ADDR         (OLD_IMAGE_START_ADDRESS + DEVICE_FLASH_ROM_SIZE)
#define NEW_IMAGE_HASH_STORAGE_ADDR         (NEW_IMAGE_START_ADDRESS + DEVICE_FLASH_ROM_SIZE)

/* Buffer size for APIs open to user app, this will not be used for operation related to flash self programming library */
#define IMAGE_PROCESSING_BUFFER_SIZE        (128)

#if ((((USER_APP_NEAR_END_ADDRESS - USER_APP_NEAR_START_ADDRESS + 1) % IMAGE_PROCESSING_BUFFER_SIZE) != 0) ||\
     (((USER_APP_FAR_END_ADDRESS - USER_APP_FAR_START_ADDRESS + 1) % IMAGE_PROCESSING_BUFFER_SIZE) != 0) )
#error "Please select the hashing buffer size so user app length modulo the buffer size will be 0"
#endif

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
/* This variable is overlapped and will be erased in user app
 * Global is used instead of stack to reduced the total stack needed 
*/
uint8_t g_bl_image_read_ROM_buffer[DEVICE_FLASH_BLOCK_SIZE];

/***********************************************************************************************************************
* Function Name: void BL_IMAGE_EraseImageSerialFlash(uint8_t is_new)
* Description  : Erase the image area in serial flash
* Arguments    : uint8_t is_new: old or new partition
* Return Value : none
***********************************************************************************************************************/
void BL_IMAGE_EraseImageInSerialFlash(uint8_t is_new)
{
    uint32_t addr;
    uint16_t i; /* Use 16bit for compatibility from minimum and maximum block size type */
    
    /* Offset to address */
    if (is_new == IMAGE_OLD_PARTITION)
    {
        addr = OLD_IMAGE_START_ADDRESS;
    }
    else
    {
        addr = NEW_IMAGE_START_ADDRESS;
    }
    
    /* Erase all data in new image partition, including the status */
    for (i = 0; i < IMAGE_DATA_SIZE / SFL_DEVICE_MAXIMUM_BLOCK_SIZE; i++)
    {
        /* Erase on 64KB as device size is multiple of 64K, change to other block size if needed when device size changed */
        BL_SFL_DeviceErase64KB(addr);
        addr += SFL_DEVICE_MAXIMUM_BLOCK_SIZE;
        R_WDT_Restart();
    }
}

/***********************************************************************************************************************
* Function Name: void BL_IMAGE_RestoreUserApp(void)
* Description  : Restore the backed-up image in external memory to ROM
* Arguments    : None
* Return Value : uint8_t:
*              :    0: No error
*              :    2: flash erase failure
*              :    3: flash write failure
***********************************************************************************************************************/
static uint8_t BL_IMAGE_RestoreUserApp(void)
{
    /* Write from new area in serial flash to user app area in ROM */
    uint32_t addr;
    uint8_t status = 0;
    
    /* Indicate ongoing process */
    BL_OPERATION_SetConfirmCode(PROGRESS_RESTORING_BACKUP_USER_APP);
    
    /* Erase user app in ROM */
    if (BL_IMAGE_EraseUserAppInROM() == 1)
    {
        status = 2;
    }
    
    if (status == 0)
    {
        /* Read from SerialFlash */
        addr = USER_APP_NEAR_START_ADDRESS;
        while (addr < (USER_APP_NEAR_END_ADDRESS + 1))
        {
            BL_SFL_DeviceRead(addr, g_bl_image_read_ROM_buffer, DEVICE_FLASH_BLOCK_SIZE);
            /* Flash write block fixed at DEVICE_FLASH_BLOCK_SIZE bytes */
            /* No check for write condition, only backup image left for recover */
            if (BL_FLASH_WriteBlock(addr, g_bl_image_read_ROM_buffer) != 0)
            {
                status = 3;
                break;
            }
            addr += DEVICE_FLASH_BLOCK_SIZE;

            R_WDT_Restart();
        }

        addr = USER_APP_FAR_START_ADDRESS;
        while (addr < (USER_APP_FAR_END_ADDRESS + 1))
        {
            BL_SFL_DeviceRead(addr, g_bl_image_read_ROM_buffer, DEVICE_FLASH_BLOCK_SIZE);
            /* Flash write block fixed at DEVICE_FLASH_BLOCK_SIZE bytes */
            /* No check for write condition, only backup image left for recover */
            if (BL_FLASH_WriteBlock(addr, g_bl_image_read_ROM_buffer) != 0)
            {
                status = 3;
                break;
            }
            addr += DEVICE_FLASH_BLOCK_SIZE;

            R_WDT_Restart();
        }
    }
    
    /* Process finished */    
    BL_OPERATION_ClearConfirmCode(PROGRESS_RESTORING_BACKUP_USER_APP);

    return status;
}

/***********************************************************************************************************************
* Function Name: void BL_IMAGE_CheckUserApp(void)
* Description  : Check the user app in ROM for error and raise request if any
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void BL_IMAGE_CheckUserApp(void)
{
    /* Check entry address */
    if (*((uint16_t *)USER_APP_NEAR_START_ADDRESS) == 0xFFFF)
    {
        /* Invalid jump address, set reset count to max 
            * The flag and image update status will be raised by later process
        */
        g_bl_info.reset_count = BL_MAX_CONTINUOUS_FAULTY_RESET;
    }
    
    /* Check faulty reset */
    /* Check for reset flag */
    if (g_bl_startup_status.hardware.flag_RESF != 0x00 &&
        g_bl_startup_status.hardware.flag_RESF != LVIRF)
    {
        /* The reset is abnormal, check if it's because of userapp reset */
        if (BL_OPERATION_ReadConfirmCode(REQUEST_SOFTWARE_RESET) != 1)
        {
            /* Not user app software reset, caused by faulty program */
            if (g_bl_info.reset_count < BL_MAX_CONTINUOUS_FAULTY_RESET)
            {
                /* Try to reset the device again and increase the reset count */
                g_bl_info.reset_count++;
                
                /* Clear any image activation request, it may reset during update */
                BL_OPERATION_ClearConfirmCode(REQUEST_ACTIVATE_IMAGE);
            }
            else
            {
                /* Check whether restore process failed also */
                if (g_bl_info.image_restore_count < BL_MAX_IMAGE_RESTORE)
                {
                    g_bl_info.image_restore_count++;
                    
                    /* Maximum number of time for reset, raise event to restore image */
                    BL_OPERATION_SetConfirmCode(REQUEST_RESTORE_IMAGE); 
                }
                else
                {
                    /* Request recovery mode */
                    BL_OPERATION_SetConfirmCode(REQUEST_RECOVERY_MODE);
                }
                
                /* Let user app know the event */
                g_bl_startup_status.image_update.details.new_update_info = 1;
                g_bl_startup_status.image_update.details.update_sucess = 0;
                g_bl_startup_status.image_update.details.update_failed_new_image_not_work = 1;
            }
        }
        else
        {
            /* Clear the user app software reset and clear the faulty reset count */
            BL_OPERATION_ClearConfirmCode(REQUEST_SOFTWARE_RESET);
            g_bl_info.reset_count = 0;
        }
    }
    else
    {
        /* Reset the faulty reset count */
        g_bl_info.reset_count = 0;
    }
}

/***********************************************************************************************************************
* Function Name: uint8_t BL_IMAGE_EraseUserAppInROM(void)
* Description  : Erase the user app in ROM
* Arguments    : None
* Return Value : uint8_t: result
*              :    0: no error
*              :    1: erase failure
***********************************************************************************************************************/
uint8_t BL_IMAGE_EraseUserAppInROM(void)
{
    uint16_t flash_blk_count;
    uint16_t flash_blk_count_end;
    
    /* Indicate ongoing process */
    BL_OPERATION_SetConfirmCode(PROGRESS_ERASING_USER_APP);
    
    /* Erase User app area */
    flash_blk_count = USER_APP_NEAR_START_ADDRESS / DEVICE_FLASH_BLOCK_SIZE;
    flash_blk_count_end = (USER_APP_NEAR_END_ADDRESS + 1) / DEVICE_FLASH_BLOCK_SIZE;
    
    for (; flash_blk_count < flash_blk_count_end; flash_blk_count++)
    {
        if (BL_FLASH_EraseBlock(flash_blk_count) != 0)
        {
            return 1;
        }
        R_WDT_Restart();
    }
    
    flash_blk_count = USER_APP_FAR_START_ADDRESS / DEVICE_FLASH_BLOCK_SIZE;
    flash_blk_count_end = (USER_APP_FAR_END_ADDRESS + 1) / DEVICE_FLASH_BLOCK_SIZE;
    
    for (; flash_blk_count < flash_blk_count_end; flash_blk_count++)
    {
        if (BL_FLASH_EraseBlock(flash_blk_count) != 0)
        {
            return 1;
        }
        R_WDT_Restart();
    }
    
    /* Process finished */    
    BL_OPERATION_ClearConfirmCode(PROGRESS_ERASING_USER_APP);

    return 0;
}

/***********************************************************************************************************************
* Function Name: void BL_IMAGE_Processing(void)
* Description  : Check user app and process image update, backup or restore request
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void BL_IMAGE_Processing(void)
{
    uint8_t status = BL_TRANSFER_USER_APP_RESULT_OK;

    /* Check user app operability */
    BL_IMAGE_CheckUserApp();
    
    /* Is there any image backup request */
    if (BL_OPERATION_ReadConfirmCode(REQUEST_BACKUP_IMAGE) == 1)
    {
         /* Change to max CPU speed to reduce processing time */
        FLASH_CPU_SWITCH_MAX_SPEED();

        /* Inform to user on LCD */
        BL_LCD_DisplayBackingUp();
        
        /* Indicate ongoing process */
        BL_OPERATION_SetConfirmCode(PROGRESS_BACKINGUP_USER_APP);
        
        /* Restore the good image from serial flash */
        BL_IMAGE_BackupUserApp();
    
        /* Process finished */    
        BL_OPERATION_ClearConfirmCode(PROGRESS_BACKINGUP_USER_APP);
        
        /* Request finished */
        BL_OPERATION_ClearConfirmCode(REQUEST_BACKUP_IMAGE);

        FLASH_CPU_SWITCH_MIN_SPEED();
    }
    
    /* Is there any image activate request */
    if (BL_OPERATION_ReadConfirmCode(REQUEST_ACTIVATE_IMAGE) ==  1)
    {
         /* Change to max CPU speed to reduce processing time */
        FLASH_CPU_SWITCH_MAX_SPEED();
        
        /* Inform to user on LCD */
        BL_LCD_DisplayUpdating();

        /* Erase all previous image status count */
        g_bl_info.reset_count = 0;
        g_bl_info.image_restore_count = 0;

        /* Reset notification value, always mark there's update for activate request */
        g_bl_startup_status.image_update.value = 0;
        g_bl_startup_status.image_update.details.new_update_info = 1;
        
        /* Start transfer new image from SFL to ROM
         * Transfer including SFL image header check, SFL hash check and flash to ROM
        */
        /* Verify first */
        status = BL_IMAGE_TransferUserAppToROM(BL_TRANSFER_USER_APP_TYPE_VERIFY_ONLY);

        if (status == 0)
        {
            /* Start writing new image into user flash area */
            status = BL_IMAGE_TransferUserAppToROM(BL_TRANSFER_USER_APP_TYPE_VERIFY_AND_FLASH);
            
            /* Now checking updating result */
            if (status == BL_TRANSFER_USER_APP_RESULT_OK)
            {
                /* Let user app know the event */
                g_bl_startup_status.image_update.details.update_sucess = 1;
            }
            else
            {
                /* Updating failed, Let user app know the event */
                g_bl_startup_status.image_update.details.update_sucess = 0;

                if (status == BL_TRANSFER_USER_APP_RESULT_ERROR_FLASH_ERASE_FAILURE ||
                    status == BL_TRANSFER_USER_APP_RESULT_ERROR_FLASH_WRITE_FAILURE)
                {
                    /* Restore the good image from serial flash */
                    BL_OPERATION_SetConfirmCode(REQUEST_RESTORE_IMAGE);
                
                    g_bl_startup_status.image_update.details.update_failed_flash_writing_error = 1;
                }
                else
                {
                    /* Should not reach this condition */
                }
            }
        }
        else
        {
            /* Verification only failed, Let user app know the event */
            g_bl_startup_status.image_update.details.update_sucess = 0;

            if (status == BL_TRANSFER_USER_APP_RESULT_ERROR_HASH_UNMATCHED)
            {
                g_bl_startup_status.image_update.details.verification_failed_hash_unmatched = 1;
            }
            else if (status == BL_TRANSFER_USER_APP_RESULT_ERROR_ADDRESS_OUT_RANGE)
            {
                g_bl_startup_status.image_update.details.verification_failed_address_out_of_range = 1;
            }
            else
            {
                /* Should not reach this condition */
            }
        }
        
        BL_OPERATION_ClearConfirmCode(REQUEST_ACTIVATE_IMAGE);

        FLASH_CPU_SWITCH_MIN_SPEED();
    }
    
    /* Is there any image restore request */
    if (BL_OPERATION_ReadConfirmCode(REQUEST_RESTORE_IMAGE) == 1)
    {
         /* Change to max CPU speed to reduce processing time */
        FLASH_CPU_SWITCH_MAX_SPEED();
        
        /* Inform to user on LCD */
        BL_LCD_DisplayRestoring();
        
        /* Restore the good image from serial flash */
        status = BL_IMAGE_RestoreUserApp();
        if (status != 0)
        {
            // status == 2 //erase failure
            // status == 3 //write failure
            /* Request recovery mode */
            BL_OPERATION_SetConfirmCode(REQUEST_RECOVERY_MODE);
        }
        else
        {
            g_bl_info.reset_count = 0;
            g_bl_info.image_restore_count = 0;
        }
        
        /* Request finished */
        BL_OPERATION_ClearConfirmCode(REQUEST_RESTORE_IMAGE);

        FLASH_CPU_SWITCH_MIN_SPEED();
    }
}

#ifdef __CCRL__

#pragma section text BLShareTx

#endif

/***********************************************************************************************************************
* Function Name: uint8_t BL_IMAGE_EraseImageData(void)
* Description  : For user app to erase all information (image data + status block)
* Arguments    : None
* Return Value : uint8_t: erase result
***********************************************************************************************************************/
#ifdef __ICCRL78__
__root
#endif
uint8_t BL_IMAGE_EraseImageData(void)
{
    BL_IMAGE_EraseImageInSerialFlash(IMAGE_NEW_PARTITION);
    
    /* Erase success */
    return BL_IMAGE_OK;
}

/***********************************************************************************************************************
* Function Name: uint8_t BL_IMAGE_Erase(uint32_t addr)
* Description  : For user app to erase a block (depend on external memory block size) 
*              : in the area which stored the new image
* Arguments    : uint32_t addr: block which contain this address will be erased
* Return Value : uint8_t: erase result
***********************************************************************************************************************/
#ifdef __ICCRL78__
__root
#endif
uint8_t BL_IMAGE_Erase(uint32_t addr)
{
    /* Check for erasing range: only allow in image area only */
    if (addr > (EXT_MEM_IMAGE_END_ADDRESS - NEW_IMAGE_START_ADDRESS) )
    {
        return BL_IMAGE_ERROR_PARAMS;
    }
    
    if (BL_SFL_DeviceErase4KB(addr + NEW_IMAGE_START_ADDRESS) != SFL_OK)
    {
        return BL_IMAGE_ERROR_EXECUTION;
    }
    
    /* Erase success */
    return BL_IMAGE_OK;
}

/***********************************************************************************************************************
* Function Name: uint8_t BL_IMAGE_Write(uint32_t addr, uint8_t * buffer, uint16_t size)
* Description  : For user app to write data into new image storage area
* Arguments    : uint32_t addr: write address (according to actual ROM address)
*              : uint8_t * buffer: write buffer
*              : uint16_t size: buffer size
* Return Value : uint8_t: write result
***********************************************************************************************************************/
#ifdef __ICCRL78__
__root
#endif
uint8_t BL_IMAGE_Write(uint32_t addr, uint8_t * buffer, uint16_t size)
{
    /* Check input argument */
    if (buffer == NULL)
    {
        return BL_IMAGE_ERROR_PARAMS;
    }
    
    /* Check for writing range: only allow in image area only */
    if ( (size == 0) ||
         (addr + size) > (EXT_MEM_IMAGE_END_ADDRESS - NEW_IMAGE_START_ADDRESS + 1))
    {
        return BL_IMAGE_ERROR_PARAMS;
    }
    
    if (BL_SFL_DeviceWrite(addr + NEW_IMAGE_START_ADDRESS, buffer, size) != SFL_OK)
    {
        return BL_IMAGE_ERROR_EXECUTION;
    }
    
    /* Write success */
    return BL_IMAGE_OK;
}

/***********************************************************************************************************************
* Function Name: uint8_t BL_IMAGE_BackupUserAppROM(void)
* Description  : Backup user app from ROM to SerialFlash
* Arguments    : None
* Return Value : none
***********************************************************************************************************************/
#ifdef __ICCRL78__
__root
#endif
uint8_t BL_IMAGE_BackupUserApp(void)
{
    uint8_t status = 0;
    uint32_t addr;
    /* This function open for user app, so it need to use stack */
    uint8_t buffer[IMAGE_PROCESSING_BUFFER_SIZE];
    
    /* First erase whole image in serial flash */
    BL_IMAGE_EraseImageInSerialFlash(IMAGE_OLD_PARTITION);
    
    addr = USER_APP_NEAR_START_ADDRESS;
    while (addr < (USER_APP_NEAR_END_ADDRESS + 1))
    {
        BL_memcpy_nn(buffer, (const uint8_t NEAR_PTR *)(uint16_t)addr, IMAGE_PROCESSING_BUFFER_SIZE);
        status |= BL_SFL_DeviceWrite(addr, buffer, IMAGE_PROCESSING_BUFFER_SIZE);
        addr += IMAGE_PROCESSING_BUFFER_SIZE;
        
        R_WDT_Restart();
    }
    
    addr = USER_APP_FAR_START_ADDRESS;
    while (addr < (USER_APP_FAR_END_ADDRESS + 1))
    {
        BL_memcpy_nf(buffer, (const uint8_t FAR_PTR *)addr, IMAGE_PROCESSING_BUFFER_SIZE);
        status |= BL_SFL_DeviceWrite(addr, buffer, IMAGE_PROCESSING_BUFFER_SIZE);
        addr += IMAGE_PROCESSING_BUFFER_SIZE;
        
        R_WDT_Restart();
    }
    
    return status;
}