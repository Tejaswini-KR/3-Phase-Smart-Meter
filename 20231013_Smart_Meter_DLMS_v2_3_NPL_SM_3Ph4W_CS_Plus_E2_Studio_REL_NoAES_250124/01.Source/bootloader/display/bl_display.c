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
* File Name    : bl_display.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : 
* Description  : LCD Display for bootloader
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Drivers */
#include "bl_r_cg_macrodriver.h"
#include "bl_r_cg_lcd.h"

/* Display functions */
#include "bl_display.h"
#include "bl_r_lcd_display.h"

/* Other modules */
#include "bl_header.h"

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
* Function Name: void BL_LCD_DisplayBackingUp(void)
* Description  : Display on LCD information: bootloader backing up
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void BL_LCD_DisplayBackingUp(void)
{
    LCD_ClearAll();
    
    LCD_DisplayDigit(1, LCD_CHAR_B);
    LCD_DisplayDigit(2, LCD_CHAR_A);
    LCD_DisplayDigit(3, LCD_CHAR_C);
    
    LCD_DisplayDigit(6, LCD_CHAR_U);
    LCD_DisplayDigit(7, LCD_CHAR_P);
}

/***********************************************************************************************************************
* Function Name: void BL_LCD_DisplayRestoring(void)
* Description  : Display on LCD information: bootloader restoring image
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void BL_LCD_DisplayRestoring(void)
{
    LCD_ClearAll();
    
    LCD_DisplayDigit(1, LCD_CHAR_R);
    LCD_DisplayDigit(2, LCD_CHAR_E);
    LCD_DisplayDigit(3, LCD_NUMB_5);
    LCD_DisplayDigit(4, LCD_CHAR_T);
    LCD_DisplayDigit(5, LCD_NUMB_0);
    LCD_DisplayDigit(6, LCD_CHAR_R);
    LCD_DisplayDigit(7, LCD_CHAR_E);
}

/***********************************************************************************************************************
* Function Name: void BL_LCD_DisplayUpdating(void)
* Description  : Display on LCD information: bootloader updating with new image
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void BL_LCD_DisplayUpdating(void)
{
    LCD_ClearAll();
    
    LCD_DisplayDigit(1, LCD_CHAR_U);
    LCD_DisplayDigit(2, LCD_CHAR_P);
    LCD_DisplayDigit(3, LCD_CHAR_D);
    LCD_DisplayDigit(4, LCD_CHAR_A);
    LCD_DisplayDigit(5, LCD_CHAR_T);
    LCD_DisplayDigit(6, LCD_CHAR_E);
}

/***********************************************************************************************************************
* Function Name: void BL_LCD_DisplayRecoveryMode(void)
* Description  : Display on LCD information: bootloader in recovery mode
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void BL_LCD_DisplayRecoveryMode(void)
{
    LCD_ClearAll();
    
    LCD_DisplayDigit(1, LCD_CHAR_R);
    LCD_DisplayDigit(2, LCD_CHAR_E);
    LCD_DisplayDigit(3, LCD_CHAR_C);
    LCD_DisplayDigit(4, LCD_NUMB_0);
    LCD_DisplayDigit(5, LCD_CHAR_U);
    LCD_DisplayDigit(6, LCD_CHAR_E);
    LCD_DisplayDigit(7, LCD_CHAR_R);
}
