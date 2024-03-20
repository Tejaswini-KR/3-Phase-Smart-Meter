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
* File Name    : r_lcd_config.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : CA78K0R
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : Declare const array for LCD configuration
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_lcd_config.h"
#include "r_drv_lcd_ext.h"

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
/*
 * Data mapping:
 * This data must be changed when there is any difference on PIN
 * (COM and SEGMENT) connection setting between LCD and MCU
 */
const LCD_NUM_MAP g_LCD_NumMap[LCD_NUM_DIGIT] = 
{
    /* Pos   Address Number Type */
    {1,    LCD_RAM_START_ADDRESS+0,  NUM_TYPE_A},  // earilier it is seg25 now it is seg 31 - pos1
    {2,    LCD_RAM_START_ADDRESS+1,  NUM_TYPE_A},  // earilier it is seg24 now it is seg 32 - pos2
    {3,    LCD_RAM_START_ADDRESS+2,  NUM_TYPE_A},  // earilier it is seg23 now it is seg 33 - pos3
    {4,    LCD_RAM_START_ADDRESS+3,  NUM_TYPE_A},  // earilier it is seg22 now it is seg 31 - pos4
    {5,    LCD_RAM_START_ADDRESS+4,  NUM_TYPE_A},
    {6,    LCD_RAM_START_ADDRESS+5,  NUM_TYPE_A},
    {7,    LCD_RAM_START_ADDRESS+6,  NUM_TYPE_A},
    {8,    LCD_RAM_START_ADDRESS+7,  NUM_TYPE_A},
    {9,    LCD_RAM_START_ADDRESS+21,  NUM_TYPE_A},
    {10,   LCD_RAM_START_ADDRESS+20,  NUM_TYPE_A},
    {11,   LCD_RAM_START_ADDRESS+19,  NUM_TYPE_A},
    {12,   LCD_RAM_START_ADDRESS+18,  NUM_TYPE_A},
    {13,   LCD_RAM_START_ADDRESS+17,  NUM_TYPE_A},
    {14,   LCD_RAM_START_ADDRESS+16,  NUM_TYPE_A},
};

const LCD_NUM_TYPE_VALUE g_LCD_NumType_SET1[LCD_NUM_DIGIT_CHAR] =                                
{
{0x77},{0X24},{0X6B},{0X6D},{0X3C},{0X5D},{0X5F},{0X64},{0X7F},{0X7D},
// A	B	C	D	E     F	     G      H     I      J      K	L     M	      N      O     P       Q      R      S     T      U       V     W       X      Y     Z
{0x7E},{0x1F},{0x53},{0x2F},{0x5B},{0x5A},{0x00},{0x3E},{0x04},{0x00},{0x00},{0x13},{0x00},{0x0E},{0x0F},{0x7A},{0x00},{0x0A},{0x5D},{0x1B},{0x37},{0x00},{0x00},{0x00},{0x3D},{0x00},
{0x08},
}; 

const LCD_NUM_TYPE_VALUE g_LCD_NumType_SET2[LCD_NUM_DIGIT_CHAR] =                                
{
{0XEE},{0X48},{0XD6},{0XDA},{0X78},{0XBA},{0XBE},{0XC8},{0XFE},{0XFA},
// A	B	C	D	E     F	     G      H     I      J      K	L     M	      N      O     P       Q      R      S     T      U       V     W       X      Y     Z
{0xFC},{0x3E},{0xA6},{0x5E},{0xB6},{0xB4},{0x00},{0x7C},{0x08},{0x00},{0x00},{0x26},{0x00},{0x1C},{0x1E},{0xF4},{0x00},{0x14},{0xBA},{0x36},{0x6E},{0x00},{0x00},{0x00},{0x7C},{0x00},
{0x10},
};   

const LCD_NUM_TYPE_VALUE g_LCD_NumType_SET3[LCD_NUM_DIGIT_CHAR] =                                
{
{0X77},{0X12},{0X6B},{0X5B},{0X1E},{0X5D},{0X7C},{0X13},{0X7F},{0X5F},
// A	B	C	D	E     F	     G      H     I      J      K	L     M	      N      O     P       Q      R      S     T      U       V     W       X      Y     Z
{0x3F},{0x7C},{0x65},{0x7A},{0x6D},{0x2D},{0x00},{0x3E},{0x10},{0x00},{0x00},{0x64},{0x00},{0x38},{0x78},{0x2F},{0x00},{0x28},{0x5D},{0x6C},{0x76},{0x00},{0x00},{0x00},{0x5E},{0x00},
};                             

/* Mapping all special sign of LCD to LCDRAM */
const LCD_SIGN_MAP g_LCD_SignMap[LCD_NUM_SIGN] = 
{
	/* Porting*/ 
    /* Number No.   Address   Bit No. */
    {S_DATE , LCD_RAM_START_ADDRESS + 0, 7},  /* 01 */
    {S_TIME , LCD_RAM_START_ADDRESS + 16, 7}, /* 02 */
    {S_EARTH, LCD_RAM_START_ADDRESS + 15, 2}, /* 03 */
    {S_REV  , LCD_RAM_START_ADDRESS + 15, 3}, /* 04 */
    {S_MN   , LCD_RAM_START_ADDRESS + 7, 7},  /* 05 */	//Not Changed
    {S_MAG  , LCD_RAM_START_ADDRESS + 9, 7},  /* 06 */
    {S_T9  , LCD_RAM_START_ADDRESS + 15, 4},  /* 05 */  //BATTERY
    {S_T8   , LCD_RAM_START_ADDRESS + 8 , 7}, /* 16 */ 	//z-inv
    {S_T7   , LCD_RAM_START_ADDRESS + 8 , 0}, /* 17 */  //h-invendis
//  {S_T6   , LCD_RAM_START_ADDRESS + 0 , 1}, /* 18 */  //Not Changed
    {S_T5   , LCD_RAM_START_ADDRESS + 8 , 1}, /* 19 */  //r-invendis
    {S_T4   , LCD_RAM_START_ADDRESS + 8, 2}, /* 20  */ 	//A-invendis
    {S_T3   , LCD_RAM_START_ADDRESS + 8 , 3}, /* 21 */  //V2-invendis
    {S_T2   , LCD_RAM_START_ADDRESS + 8 , 4}, /* 22 */  //V1-invendis
    {S_T1   , LCD_RAM_START_ADDRESS + 8 , 5}, /* 23 */  //k-invendis 	
    {S_D5   , LCD_RAM_START_ADDRESS + 4 , 0}, /* 25 */	//DEcimal point	
//  {S_D3   , LCD_RAM_START_ADDRESS + 15, 0}, /* 27 */	//Not Changed
//  {S_D2   , LCD_RAM_START_ADDRESS + 17, 0}, /* 28 */	//Not Changed
    {S_D1   , LCD_RAM_START_ADDRESS + 2 , 7}, /* 29 */	//col
    {S_MD   , LCD_RAM_START_ADDRESS + 10, 7}, /* 32 */

//    {C    , LCD_RAM_START_ADDRESS + 8 , 6}, /* 02 */
//    {BP   , LCD_RAM_START_ADDRESS + 11, 7}, /* 02 */
//    {T    , LCD_RAM_START_ADDRESS + 12, 7}, /* 02 */
//    {T2   , LCD_RAM_START_ADDRESS + 15, 0}, /* 02 */
//    {T3   , LCD_RAM_START_ADDRESS + 15, 1}, /* 02 */
//    {T6   , LCD_RAM_START_ADDRESS + 15, 4}, /* 02 */
//    {T7   , LCD_RAM_START_ADDRESS + 15, 5}, /* 02 */
//    {Q1   , LCD_RAM_START_ADDRESS + 15, 6}, //Quadrant1
//    {Q2   , LCD_RAM_START_ADDRESS + 15, 7}, //Quadrant2
//    {Q3   , LCD_RAM_START_ADDRESS + 13, 7}, //Quadrant3
//    {Q4   , LCD_RAM_START_ADDRESS + 14, 7}, //Quadrant4
      /* Porting*/
};

const LCD_DECIMAL_INFO g_DecInfo  = {6, S_D5};
const LCD_DECIMAL_INFO g_DecInfo1 = {6, S_D5};

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
