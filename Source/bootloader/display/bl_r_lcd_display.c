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
* File Name    : bl_r_lcd_display.h
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : 
* Description  : LCD Segment Data display APIs
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "bl_r_cg_macrodriver.h"       /* macro driver definitions */
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
* Function Name: void LCD_DisplayAll(void)
* Description  : Display all digit on LCD screen
* Arguments    : none
* Output       : none
* Return Value : none
***********************************************************************************************************************/
void LCD_DisplayAll(void)
{
    LCD_RamSetAll();
}

/***********************************************************************************************************************
* Function Name: void LCD_ClearAll(void)
* Description  : Clear all digit on LCD screen
* Arguments    : none
* Output       : none
* Return Value : none
***********************************************************************************************************************/
void LCD_ClearAll(void)
{
    LCD_RamClearAll();
}

/***********************************************************************************************************************
* Function Name: uint8_t uint8_t LCD_DisplayDigit(uint8_t position, uint8_t value)
* Description  : Diplay [value] at [position] on LCD screen
* Arguments    : [value] value need to be display
*              : [position] the position of digit on LCD screen
* Output       : none
* Return Value : LCD_WRONG_INPUT_ARGUMENT: input wrong argument
*              : LCD_INPUT_OK: input OK argument
***********************************************************************************************************************/
uint8_t LCD_DisplayDigit(uint8_t position, uint8_t value)
{
    uint16_t lcdptr;
    uint8_t disp_value, data_status;
    LCD_NUM_INFO num_info;
    
    /* check for range of input argument */
    if ((position > (LCD_NUM_DIGIT)) || 
        (value > (LCD_NUM_DIGIT_CHAR - 1)))
    {
        return LCD_WRONG_INPUT_ARGUMENT;
    }
    
    //LCD_ClearDigit(position);
    
    /* Get display number information */
    data_status = LCD_GetNumInfo(value, position, &num_info);
    if (data_status == LCD_WRONG_INPUT_ARGUMENT)
    {
        return LCD_WRONG_INPUT_ARGUMENT;
    }
    
    lcdptr = num_info.addr;
    if (lcdptr == 0)
    {
        return LCD_WRONG_INPUT_ARGUMENT;
    }
        
    /* Turn on all related-segment of this digit */
    disp_value = num_info.value;
    LCD_WriteRAMDigitInfo(lcdptr, disp_value);
    
    return LCD_INPUT_OK;
}
