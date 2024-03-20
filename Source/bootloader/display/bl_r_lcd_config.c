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
* File Name    : bl_r_lcd_config.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : 
* Description  : Declare const array for LCD configuration
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "compiler.h"
#include "bl_r_lcd_config.h"
#include "bl_r_drv_lcd_ext.h"

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
const FAR_PTR LCD_NUM_MAP g_LCD_NumMap[LCD_NUM_DIGIT] = 
{
    /* Pos   Address Number Type */
    {1,    LCD_RAM_START_ADDRESS + 21 ,  NUM_TYPE_A},
    {2,    LCD_RAM_START_ADDRESS + 19 ,  NUM_TYPE_A},
    {3,    LCD_RAM_START_ADDRESS + 17 ,  NUM_TYPE_A},
    {4,    LCD_RAM_START_ADDRESS + 15 ,  NUM_TYPE_A},
    {5,    LCD_RAM_START_ADDRESS + 13 ,  NUM_TYPE_A},
    {6,    LCD_RAM_START_ADDRESS + 9,    NUM_TYPE_A},
    {7,    LCD_RAM_START_ADDRESS + 7,    NUM_TYPE_A},
//    {8,    LCD_RAM_START_ADDRESS + 5,    NUM_TYPE_A},
//    {9,    LCD_RAM_START_ADDRESS + 3,    NUM_TYPE_A},
};

const FAR_PTR LCD_NUM_TYPE_VALUE g_LCD_NumType[LCD_NUM_DIGIT_CHAR] =
{
	/*porting*/
	{0xBE},//1011 1110//    { 0xD7 }    , /* '0' - 0* 1101 0111 /  
	//{0x06},//0000 0110//    { 0x06 }    , /* '1' - 1* 0000 0110 /
	//{0x7C},//0111 1100//    { 0xE3 }    , /* '2' - 2* 1110 0011 /
	//{0x5E},//0101 1110//    { 0xA7 }    , /* '3' - 3* 1010 0111 /
	//{0xC6},//1100 0110//    { 0x36 }    , /* '4' - 4* 0011 0110 /
	{0xDA},//1101 1010//    { 0xB5 }    , /* '5' - 5* 1011 0101 /
	//{0xFA},//1111 1010//    { 0xF5 }    , /* '6' - 6* 1111 0101 /
	//{0x0E},//0000 1110//    { 0x07 }    , /* '7' - 7* 0000 0111 /
	//{0xFE},//1111 1110//    { 0xF7 }    , /* '8' - 8* 1111 0111 /
	//{0xDE},//1101 1110//    { 0xB7 }    , /* '9' - 9* 1011 0111 /
	{0xEE},//1110 1110//    { 0x77 }    , /* 'A' - 10* 0111 0111 /
	{0xF2},//1111 0010//    { 0xF4 }    , /* 'b' - 11* 1111 0100 /
	{0xB8},//1011 1000//    { 0xD1 }    , /* 'C' - 12* 1101 0001 /
	{0x76},//0111 0110//    { 0xE6 }    , /* 'd' - 13* 1110 0110 /
	{0xF8},//1111 1000//    { 0xF1 }    , /* 'E' - 14* 1111 0001 /
	//{0xE8},//1110 1000//    { 0x71 }    , /* 'F' - 15* 0111 0001 /
	//{0x40},//0100 0000//    { 0x20 }    , /* '-' - 16* 0010 0000 /
	{0xEC},//1110 1100//    { 0x73 }    , /* 'P' - 17* 0111 0011 /
	//{0xB0},//1011 0000//    { 0xD0 }    , /* 'L' - 18* 1101 0000 /
	//{0xAE},//1010 1110//    { 0x57 }    , /* 'N' - 19* 0101 0111 /
	//{0x01},//0000 0001//    { 0x08 }    , /* na - 20* 0000 1000 /
	{0xB6},//1011 0110//    { 0xD6 }    , /* 'U' - 21* 1101 0110 /
    { 0xF0 }    , /* 't' - 22*/
    { 0x60 }    , /* 'r' - 23*/
	/*porting*/
};                              


const FAR_PTR LCD_DECIMAL_INFO g_DecInfo  = {6, S_D5};
const FAR_PTR LCD_DECIMAL_INFO g_DecInfo1 = {5, S_D4};

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
