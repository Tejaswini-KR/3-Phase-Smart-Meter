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
* File Name    : bl_flash.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : ROM Self Flash functions
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Drivers */
#include "bl_r_cg_macrodriver.h"
#include "bl_r_cg_sau.h"

/* Core functions */
#include "bl_header.h"
#include "fsl.h"

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define MAX_NUMBER_OF_WORDS_EACH_WRITE                  (64)
#define MAX_NUMBER_OF_BYTE_EACH_WRITE                   (MAX_NUMBER_OF_WORDS_EACH_WRITE * 4)

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
const FAR_PTR fsl_descriptor_t g_fsl_descriptor = 
{
    0x00,    /* Full speed */
    24,      /* 24 MHz */
    1,       /* Auto check */
};

/***********************************************************************************************************************
* Function Name: void BL_FLASH_EraseBlock(uint16_t block_no)
* Description  : Erase one block in FLASH
* Arguments    : uint16_t block_no: the block number (block size is 1024 bytes)
*              : CAUTIONS: this function do not check block number
* Return Value : uint8_t: erasing result
***********************************************************************************************************************/
uint8_t BL_FLASH_EraseBlock(uint16_t block_no)
{
    uint8_t result = 0;
    
    /* Disable interrupt when vector table in ROM */
    DI();
    
    /* Starting the FSL: Init --> Open --> PrepareFunctions*/
    FSL_Init(&g_fsl_descriptor);
    FSL_Open();
    FSL_PrepareFunctions();
    
    /* Erase the wanted block */
    if (FSL_Erase(block_no) != FSL_OK)
    {
        result = 1;
    }
    
    /* Close FSL operation */
    FSL_Close();
    
    /* Re-enable interrupt */
    EI();
    
    /* Erase finished, no error */
    return result;
}

/***********************************************************************************************************************
* Function Name: void BL_FLASH_WriteBlock(uint32_t addr, uint8_t * buffer)
* Description  : Write one block (1024 bytes) of data into FLASH
* Arguments    : uint32_t addr: write address
*              : uint8_t * buffer: data buffer. 
*              : CAUTIONS: this function do not check the addr and buffer
* Return Value : uint8_t: writing verification result
***********************************************************************************************************************/
uint8_t BL_FLASH_WriteBlock(uint32_t addr, uint8_t * buffer)
{
    uint8_t i;
    uint8_t result = 0;
    uint16_t block_no;
    fsl_write_t flash_write_info;
    
    /* Disable interrupt when vector table in ROM */
    DI();
    
    /* Starting the FSL: Init --> Open --> PrepareFunctions*/
    FSL_Init(&g_fsl_descriptor);
    FSL_Open();
    FSL_PrepareFunctions();
    
    /* Get the block information for checking */
    block_no = addr / DEVICE_FLASH_BLOCK_SIZE;
    
    /* Check if blank or not */
    if (FSL_BlankCheck(block_no) != FSL_OK)
    {
        result = 1;
    }
    
    /* Write data to flash */
    flash_write_info.fsl_word_count_u08 = MAX_NUMBER_OF_WORDS_EACH_WRITE;   /* Size: 64 word x 4bytes = 256 bytes */
    
    /* Write data into 1 block: 1024 bytes */
    for (i = 0; i < (DEVICE_FLASH_BLOCK_SIZE / MAX_NUMBER_OF_BYTE_EACH_WRITE); i++)
    {
        flash_write_info.fsl_data_buffer_p_u08 = buffer;
        flash_write_info.fsl_destination_address_u32 = addr;
        FSL_Write(&flash_write_info);
        
        buffer += MAX_NUMBER_OF_BYTE_EACH_WRITE;
        addr += MAX_NUMBER_OF_BYTE_EACH_WRITE;
    }
    
    /* Verify the writing proces */
    if (FSL_IVerify(block_no) != FSL_OK)
    {
        result = 1;
    }
    
    /* Close FSL operation */
    FSL_Close();
    
    /* Re-enable interrupt */
    EI();
    
    /* Write finished, no error */
    return result;
}
