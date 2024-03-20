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
* File Name    : r_drv_lcd_ext.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : CA78K0R
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : MCU LCD module driver APIs
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"       /* Macro driver definitions */
#include "r_drv_lcd_ext.h"          /* LCD Driver definitions */
#include "r_lcd_config.h"           /* LCD Config */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define LCD_MAX_SEGMENT			(22)
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
* Function Name: uint16_t LCD_GetRamSize(void);
* Description  : LCD Get Ram Size
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
uint16_t LCD_GetRamSize(void)
{
    return (uint16_t)LCD_RAM_SIZE;
}

/***********************************************************************************************************************
* Function Name: void LCD_RamClearAll(void);
* Description  : Clear all data on RAM area of LCD
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void LCD_RamClearAll(void)
{
    uint16_t i;
    uint8_t __far * lcdptr = (uint8_t __far *)LCD_RAM_START_ADDRESS;
    
    /* Switch off segment0 to 23 */
    for (i = 0; i < LCD_MAX_SEGMENT; i++)
    {
        *((uint8_t*)lcdptr + i) = 0x00;
    }
}

/***********************************************************************************************************************
* Function Name: void LCD_RamSetAll(void);
* Description  : Set all data on RAM area of LCD to 0xff
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void LCD_RamSetAll(void)
{
    uint16_t i;
    uint8_t __far * lcdptr = (uint8_t __far *)LCD_RAM_START_ADDRESS;

    /* Switch On segment0 to 23 */
    for (i = 0; i < LCD_MAX_SEGMENT; i++)
    {
        *((uint8_t*)lcdptr + i) = 0xFF;
    }
}

/***********************************************************************************************************************
* Function Name: uint8_t LCD_GetNumInfo(
*              :      uint8_t disp_value, 
*              :      uint8_t position,
*              :      LCD_NUM_INFO* num_info
*              : );
* Description  : Get LCD Number mapping infomations
* Arguments    : [disp_value] value need to be displayed
*              : [position]   displayed position on LCD screen
* Output       : [num_info]   address and display code for disp_value
* Return Value : LCD_WRONG_INPUT_ARGUMENT: input wrong argument
*              : LCD_INPUT_OK: input OK argument
***********************************************************************************************************************/
uint8_t LCD_GetNumInfo(uint8_t disp_value, uint8_t position, LCD_NUM_INFO* num_info)
{
    LCD_NUM_TYPE    type;
    uint8_t         value;
    
    /* Check NULL for input */
    if (num_info == NULL)
    {
        return LCD_WRONG_INPUT_ARGUMENT;
    }
    
    /* Check input range */
    if ((position > (LCD_NUM_DIGIT)) || 
        (position <= 0) ||
        (disp_value > (LCD_NUM_DIGIT_CHAR - 1)))
    {
        return LCD_WRONG_INPUT_ARGUMENT;
    }
    
    /* Get RAM address at displayed position */
    num_info->addr = g_LCD_NumMap[position - 1].addr;
    type = g_LCD_NumMap[position - 1].type;
    
    if (type == NUM_TYPE_A)
    {
        switch(position)
    	{
			case 1:
			case 2:
			case 3:value = g_LCD_NumType_SET1[disp_value].typeA;
				   break;
			case 4:
			case 5:
			case 6:	
	    	case 7:value = g_LCD_NumType_SET2[disp_value].typeA;
				   break;
			case 8:value = g_LCD_NumType_SET1[disp_value].typeA;
				   break;
		    case 9 :
			case 10:
			case 11:
			case 12:
			case 13: 
			case 14:value = g_LCD_NumType_SET3[disp_value].typeA;
					break;
    
    	}
    }
    else
    {
        value = 0;
    }
    
    /* Assign num information */
    num_info->value = value;
    
    return LCD_INPUT_OK;
}

/***********************************************************************************************************************
* Function Name: uint8_t LCD_GetSignInfo(uint8_t sign, LCD_SIGN_INFO* sign_info)
* Description  : Get LCD sign mapping infomations
* Arguments    : [sign] sign need to be displayed
* Output       : [sign_info] all information about displayed sign
* Return Value : LCD_WRONG_INPUT_ARGUMENT: input wrong argument
*              : LCD_INPUT_OK: input OK argument
***********************************************************************************************************************/
uint8_t LCD_GetSignInfo(uint8_t sign, LCD_SIGN_INFO* sign_info)
{
    if (sign_info == NULL)
    {
        return LCD_WRONG_INPUT_ARGUMENT;
    }
    
    if ((sign > (LCD_NUM_SIGN - 1)))
    {
        return LCD_WRONG_INPUT_ARGUMENT;
    }
    
    sign_info->addr = g_LCD_SignMap[sign].addr;
    sign_info->pos = g_LCD_SignMap[sign].pos;
    
    return LCD_INPUT_OK;
}


/***********************************************************************************************************************
* Function Name : LCD_WriteRAMDigitInfo
* Interface     : void LCD_WriteRAMDigitInfo(uint32_t ram_addr, uint8_t disp_value)
* Description   : Write RAM digit info into LCD RAM
* Arguments     : uint32_t ram_addr : LCD RAM Addr
*               : uint8_t disp_value: Value to write to LCD RAM
* Function Calls: None
* Return Value  : None
***********************************************************************************************************************/
void LCD_WriteRAMDigitInfo(uint32_t ram_addr, uint8_t disp_value)
{
    *((uint8_t __far *)ram_addr++) |= disp_value ;
}

/***********************************************************************************************************************
* Function Name : LCD_ClearRAMDigitInfo
* Interface     : void LCD_ClearRAMDigitInfo(uint32_t ram_addr, uint8_t disp_value)
* Description   : Clear digit info to LCD RAM
* Arguments     : uint32_t ram_addr : LCD RAM Addr
*               : uint8_t disp_value: Value to write to LCD RAM
* Function Calls: 
* Return Value  : None
***********************************************************************************************************************/
void LCD_ClearRAMDigitInfo(uint32_t ram_addr, uint8_t disp_value)
{
     *((uint8_t __far *)ram_addr++) &= disp_value ;
}

/***********************************************************************************************************************
* Function Name : LCD_WriteRAMSignInfo
* Interface     : void LCD_WriteRAMSignInfo(uint32_t ram_addr, uint8_t disp_value)
* Description   : Write RAM icon info into LCD RAM
* Arguments     : uint32_t ram_addr : LCD RAM Addr
*               : uint8_t disp_value: Value to write to LCD RAM
* Function Calls: 
* Return Value  : None
***********************************************************************************************************************/
void LCD_WriteRAMSignInfo(uint32_t ram_addr, uint8_t disp_value)
{
    *((uint8_t __far *)ram_addr) |= disp_value; 
}

/***********************************************************************************************************************
* Function Name : LCD_ClearRAMSignInfo
* Interface     : void LCD_ClearRAMSignInfo(uint32_t ram_addr, uint8_t disp_value)
* Description   : Clear icon info to LCD RAM
* Arguments     : uint32_t ram_addr : LCD RAM Addr
*               : uint8_t disp_value: Value to write to LCD RAM
* Function Calls: 
* Return Value  : None
***********************************************************************************************************************/
void LCD_ClearRAMSignInfo(uint32_t ram_addr, uint8_t disp_value)
{
    *((uint8_t __far *)ram_addr) &= disp_value;
}
