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
* File Name    : bl_operation.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : 
* Description  : APIs control operation of bootloader
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Drivers */
#include "bl_r_cg_macrodriver.h"
#include "bl_r_cg_cgc.h"
#include "bl_r_cg_sau.h"

/* Core functions */
#include "bl_header.h"

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/*
 * Define the custom confirmation code
 * This number currently chosen randomly
*/
#define BL_OPERATION_CONFIRMATION_CODE                (0xA579)

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/
/* Reserved RAM area for bootloader */
#ifdef __ICCRL78__
#pragma default_variable_attributes = @ "BLBss"
bl_startup_status g_bl_startup_status;
#endif

#ifdef __CCRL__
#pragma section bss BLBss
bl_startup_status g_bl_startup_status;
#endif

/* Non-initialized reserved RAM area for bootloader */
#ifdef __ICCRL78__
#pragma default_variable_attributes = @ "BLNoInit"
BL_INFORMATION g_bl_info;
#endif

#ifdef __CCRL__
#pragma section bss BLNoInit
BL_INFORMATION g_bl_info;
#endif

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: uint8_t BL_OPERATION_ReadConfirmCode(bl_code_index type)
* Description  : Read the confirm code on request and processing status in no init area
*              : Since value stored in no init area, 
*              : this function will temporarily disabled RAM parity interrupt before read
* Arguments    : bl_code_index type: code to query status
* Return Value : uint8_t: status of that code
*              :            0: no request or no processing
*              :            1: having request or on-going-processing
***********************************************************************************************************************/
uint8_t BL_OPERATION_ReadConfirmCode(bl_code_index type)
{
    uint8_t status;
    bl_confirm_code_t * p_code;
    
    /* The confirmation is placed in no init area, so RAM parity reset should also be disable first */
    RPERDIS = 1U;
    
    /* Point to the required code */
    p_code = (bl_confirm_code_t *)((uint16_t *)&g_bl_info + type);
    /* Get the status from code */
    status =  (*p_code == BL_OPERATION_CONFIRMATION_CODE ) ? 1 : 0;
        
    /* Clear the flag and enable RAM parity reset again */
    RPEF = 0; 
    RPERDIS = 0U;
    
    return status;
}

/***********************************************************************************************************************
* Function Name: void BL_OPERATION_ClearConfirmCode(bl_code_index type)
* Description  : Clear the confirm code on request and processing status in no init area
* Arguments    : bl_code_index type: code to clear
* Return Value : None
***********************************************************************************************************************/
void BL_OPERATION_ClearConfirmCode(bl_code_index type)
{
    bl_confirm_code_t * p_code;
    p_code = (bl_confirm_code_t *)((uint16_t *)&g_bl_info + type);
    *p_code = 0x0000;
}

/***********************************************************************************************************************
* Function Name: void BL_OPERATION_SetConfirmCode(bl_code_index type)
* Description  : Set the confirm code on request and processing status in no init area
* Arguments    : bl_code_index type: code to set
* Return Value : None
***********************************************************************************************************************/
void BL_OPERATION_SetConfirmCode(bl_code_index type)
{
    bl_confirm_code_t * p_code;
    p_code = (bl_confirm_code_t *)((uint16_t *)&g_bl_info + type);
    *p_code = BL_OPERATION_CONFIRMATION_CODE;
}

#ifdef __CCRL__

#pragma section text BLShareTx

#endif

/***********************************************************************************************************************
* Function Name: void BL_OPERATION_GetStartupStatus(bl_startup_status * p_status)
* Description  : Public APIs for user to get the startup status from bootloader
* Arguments    : bl_startup_status * p_status: pointer to the bootloader startup status structure
* Return Value : None
***********************************************************************************************************************/
#ifdef __ICCRL78__
__root
#endif
void BL_OPERATION_GetStartupStatus(bl_startup_status * p_status)
{
    /* Check input pointer */
    if (p_status == NULL)
    {
        return;
    }
    
    /* Get information */
    *p_status = g_bl_startup_status;
}

/***********************************************************************************************************************
* Function Name: void BL_OPERATION_GetProperties(bl_properties * p_properties)
* Description  : Public APIs for user to get the properties on this version of bootloader
* Arguments    : bl_properties * p_properties: pointer to the bootloader properties structure
* Return Value : None
***********************************************************************************************************************/
#ifdef __ICCRL78__
__root
#endif
void BL_OPERATION_GetProperties(bl_properties * p_properties)
{
    /* Check input pointer */
    if (p_properties == NULL)
    {
        return;
    }
    
    /* Fill the information */
    p_properties->user_app.start_addr_near = USER_APP_NEAR_START_ADDRESS;
    p_properties->user_app.end_addr_near = USER_APP_NEAR_END_ADDRESS;
    p_properties->user_app.start_addr_far = USER_APP_FAR_START_ADDRESS;
    p_properties->user_app.end_addr_far = USER_APP_FAR_END_ADDRESS;
    
    p_properties->ext_mem.image_start_addr = EXT_MEM_IMAGE_START_ADDRESS;
    p_properties->ext_mem.image_end_addr = EXT_MEM_IMAGE_END_ADDRESS;
    p_properties->ext_mem.free_start_addr = EXT_MEM_FREE_START_ADDRESS;
    p_properties->ext_mem.free_end_addr = EXT_MEM_FREE_END_ADDRESS;
}

/***********************************************************************************************************************
* Function Name: void BL_OPERATION_RequestRecoveryMode(void)
* Description  : Public APIs for user to request RECOVERY MODE enter after reset
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#ifdef __ICCRL78__
__root
#endif
void BL_OPERATION_RequestRecoveryMode(void)
{
    BL_OPERATION_SetConfirmCode(REQUEST_RECOVERY_MODE);
}

/***********************************************************************************************************************
* Function Name: void BL_OPERATION_RequestUserReset(void)
* Description  : Public APIs for user to inform an intentional reset from user
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#ifdef __ICCRL78__
__root
#endif
void BL_OPERATION_RequestUserReset(void)
{
    /* UserApp call to inform device software reset */
    BL_OPERATION_SetConfirmCode(REQUEST_SOFTWARE_RESET);
}

/***********************************************************************************************************************
* Function Name: void BL_OPERATION_RequestImageActivation(void)
* Description  : Public APIs for user to request image activation
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#ifdef __ICCRL78__
__root
#endif
void BL_OPERATION_RequestImageActivation(void)
{
    /* Inform to activate image and normal soft reset */
    BL_OPERATION_SetConfirmCode(REQUEST_ACTIVATE_IMAGE);
    BL_OPERATION_SetConfirmCode(REQUEST_SOFTWARE_RESET);
        
    /* Reset immediately */
    DEVICE_RESTART_INSTRUCTION();
}

/***********************************************************************************************************************
* Function Name: void BL_OPERATION_RequestImageBackup(void)
* Description  : Public APIs for user to request image backup
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#ifdef __ICCRL78__
__root
#endif
void BL_OPERATION_RequestImageBackup(void)
{
    /* Inform to backup image (do it after reset) */
    BL_OPERATION_SetConfirmCode(REQUEST_BACKUP_IMAGE);
}

/***********************************************************************************************************************
* Function Name: void BL_OPERATION_InformStartupOK(void)
* Description  : Public APIs for user to inform a normal startup is finished to clear the staus inside bootloader
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#ifdef __ICCRL78__
__root
#endif
void BL_OPERATION_InformStartupOK(void)
{
    g_bl_info.reset_count = 0;
    g_bl_info.image_restore_count = 0;
    
    BL_OPERATION_ClearConfirmCode(REQUEST_RECOVERY_MODE);
    BL_OPERATION_ClearConfirmCode(REQUEST_SOFTWARE_RESET);
    BL_OPERATION_ClearConfirmCode(REQUEST_ACTIVATE_IMAGE);
    BL_OPERATION_ClearConfirmCode(REQUEST_BACKUP_IMAGE);
    BL_OPERATION_ClearConfirmCode(REQUEST_RESTORE_IMAGE);
}

/***********************************************************************************************************************
* Function Name: void BL_OPERATION_AcknowledgeImageUpdateStatus(void)
* Description  : Public APIs for user to acknowledge the image update status on bootloader, clear all status
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#ifdef __ICCRL78__
__root
#endif
void BL_OPERATION_AcknowledgeImageUpdateStatus(void)
{
    g_bl_startup_status.image_update.value = 0;
}

/***********************************************************************************************************************
* Function Name: void BL_OPERATION_UpdateOperatingClock(void)
* Description  : Public APIs for user to inform bootloader to update bootloader managed drivers 
*              : MUST call this when CPU clock changes
*              : This API currently support HOCO clock (from 6MHz -- 24MHz) only
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#ifdef __ICCRL78__
__root
#endif
void BL_OPERATION_UpdateOperatingClock(void)
{
    /* Support HOCO clock only */
    BL_R_CGC_UpdateCPUClock();
}