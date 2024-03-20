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
* File Name    : bl_operation.h
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : 
* Description  : APIs control operation of bootloader
***********************************************************************************************************************/

#ifndef __BL_OPERATION_H
#define __BL_OPERATION_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "typedef.h"        /* GSCE Standard Typedef */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct tagBootLoaderProperties
{
    struct tagUserAppArea
    {
        uint32_t start_addr_near;
        uint32_t end_addr_near;
        uint32_t start_addr_far;
        uint32_t end_addr_far;
    } user_app;
    
    struct tagExtMemoryInfo
    {
        uint32_t image_start_addr;
        uint32_t image_end_addr;
        uint32_t free_start_addr;
        uint32_t free_end_addr;
    } ext_mem;
    
} bl_properties;

typedef struct tagBootLoaderStartupStatus
{
    union tagImageUpdateStatus
    {
        uint16_t value;
        struct tagImageUpdateDetails
        {
            uint16_t new_update_info : 1;
            uint16_t update_sucess : 1;
            uint16_t update_failed_flash_writing_error : 1;
            uint16_t update_failed_new_image_not_work : 1;
            uint16_t verification_failed_address_out_of_range : 1;
            uint16_t verification_failed_hash_unmatched : 1;
            uint16_t reserved : 10;
            
        } details;
    } image_update;
    
    struct tagHardwareInfo
    {
        uint8_t flag_PORSR;
        uint8_t flag_RESF;
    } hardware;
    
} bl_startup_status;

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/
/* Get startup information provided by bootloader, details in bl_startup_status */
void BL_OPERATION_GetStartupStatus(bl_startup_status * p_status);
/* Get bootloader properties */
void BL_OPERATION_GetProperties(bl_properties * p_properties);

/* Call this to request recovery mode
 * After that when appropriate time, 
 * call BL_OPERATION_RequestUserReset and perform soft reset
 * Bootloader will jump into recovery mode after reboot
*/
void BL_OPERATION_RequestRecoveryMode(void);

/* Call this before performing any software reset 
 * Excluding BL_OPERATION_RequestImageActivation, it is auto reset
*/
void BL_OPERATION_RequestUserReset(void);

/* Call this API if user app don't want to do the backup by BL_IMAGE_BackupUserApp()
 * MUST ensure the current image in ROM is working normally for long time before calling this
 * The bootloader will do the backup after meter reset
*/
void BL_OPERATION_RequestImageBackup(void);

/* Call this after image has been download to designated area 
 * MUST ensure the download image is correct before calling this
 * The device reset immediately at the end of this API and start updating process
*/
void BL_OPERATION_RequestImageActivation(void);

/* Call this to let bootloader know the image is working correctly */
void BL_OPERATION_InformStartupOK(void);

/* Call this to let bootloader clear image updating status */
void BL_OPERATION_AcknowledgeImageUpdateStatus(void);

/* Call this to update driver (external memory) managed by bootloader */
void BL_OPERATION_UpdateOperatingClock(void);

#endif /* __BL_OPERATION_H */
