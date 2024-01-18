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
* File Name    : bl_startup.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : 
* Description  : Bootloader program startup function
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "bl_r_cg_macrodriver.h"
#include "bl_r_cg_port.h"
#include "bl_r_cg_lcd.h"
#include "bl_r_cg_sau.h"
#include "bl_r_cg_tau.h"

/* Standard library */
#include <string.h>

/* Other modules */
#include "bl_header.h"
#include "bl_r_lcd_display.h"

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

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
* Function Name: uint8_t BL_Startup(void)
* Description  : Startup peripherals for bootloader
* Arguments    : None
* Return Value : peripheral startup result
***********************************************************************************************************************/
uint8_t BL_Startup(void)
{
    uint8_t status;
    
    g_bl_startup_status.hardware.flag_PORSR = PORSR;
    
    /* Check for power on reset */
    if (PORSR == 0)
    {
        /* Initialize the no init area for first time */
        memset(&g_bl_info, 0, sizeof(g_bl_info));
        
        /* Mark as power on reset */
        PORSR = 1;
    }
    
    /* Get the reset flag */
    g_bl_startup_status.hardware.flag_RESF = RESF;
    
    if (IS_ENOUGH_POWER_FOR_FLASH() == 1)
    {
        R_PORT_Create();

        /* Initialize LCD */
        //R_LCD_PowerOn();
        
        /* Initialize serial flash */
        status = BL_SFL_Init();
        
        /* Initialize recovery module (when serial flash is OK only) */
        if (status == SFL_OK)
        {
            BL_RECOVERY_Init();
        }
    }
    else
    {
        status = 0;
    }
    
    return status;
}

/***********************************************************************************************************************
* Function Name: uint8_t BL_StopPeripherals(void)
* Description  : Stop all started peripherals
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void BL_StopPeripherals(void)
{
    /* No stopping on CSI driver for serial flash, it's managed by bootloader */
    
    /* Stop overlapped drivers */
    R_UART2_Stop();
    R_TAU0_Channel0_Stop();
    
    /* Clear LCD display */
    //LCD_ClearAll();
    //R_LCD_PowerOff();
    
    FLASH_CPU_SWITCH_MIN_SPEED();
}

