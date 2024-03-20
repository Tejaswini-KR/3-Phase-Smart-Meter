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
* File Name    : bl_main.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : 
* Description  : Bootloader Main processing
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Startup module */
#include "bl_startup.h"

/* Core functions */
#include "bl_header.h"

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef void (* func_ptr)(void);

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: void bl_main()
* Description  : Main processing
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void bl_main(void)
{
    volatile func_ptr func_jump;
    
    /* Make sure serial flash is running */
    if (BL_Startup() == BL_STARTUP_OK)
    {
        DEVICE_RESTART_INSTRUCTION();
    }
    
    /* Check for bootloader operation status */
    if (BL_OPERATION_ReadConfirmCode(REQUEST_ACTIVATE_IMAGE) ||
        BL_OPERATION_ReadConfirmCode(REQUEST_BACKUP_IMAGE) ||
        (g_bl_info.image_restore_count >= BL_MAX_IMAGE_RESTORE))
    {
        if (IS_ENOUGH_POWER_FOR_FLASH() != 1)
        {
            /* Cannot jump into user app to take care of power management (activating or restoring image)
             * And also cannot execute the firmware update process
            */
            /* Sleep and wait until enough power */
            PER0 = 0x00U;
            PER1 = 0x00U;
            PER2 = 0x00U;
            BL_StopPeripherals();
            NOP();
            NOP();
            NOP();
            STOP();
            NOP();
            NOP();
            NOP();
        }
        else
        {
            /* Continue for other processing */
        }
    }
    
    /* Recovery and Image processing when VDD enough only */
    if (IS_ENOUGH_POWER_FOR_FLASH() == 1)
    {
        /* Check for new firmware and updating */
        //BL_IMAGE_Processing();
        
        /* Check for recovery mode */
        //BL_RECOVERY_Processing();
    }
    
    /* Stop all peripherals used in bootloader */
    BL_StopPeripherals();
    
    /* Locate and jump to user application */
    func_jump = (func_ptr)USER_APP_NEAR_START_ADDRESS;
    
    if (*((uint16_t *)func_jump) != 0xFFFF)
    {
        /* Call to user application */
        func_jump();
    }
    else
    {
        /* Imporant, not allow jump into broken image */
        DEVICE_RESTART_INSTRUCTION();
    }
}
