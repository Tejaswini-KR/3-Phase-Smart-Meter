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
* File Name    : bl_hashing.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : 
* Description  : Hashing function for ROM code and external storage memory
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Driver */
#include "bl_r_cg_macrodriver.h"        /* MD Macro Driver */
#include "bl_r_cg_crc.h"

/* Core functions */
#include "bl_header.h"

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef uint8_t (*FUNC_Read)(uint32_t addr, uint8_t * buffer, uint16_t size);

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define HASHING_BUFFER_SIZE                 (128)

#define HASHING_AREA_ROM                    (0)
#define HASHING_AREA_SFL_USERAPP_OLD        (1)
#define HASHING_AREA_SFL_USERAPP_NEW        (2)
#define HASHING_AREA_SFL_NEW_IMAGE          (3)

#if ((((USER_APP_NEAR_END_ADDRESS - USER_APP_NEAR_START_ADDRESS + 1) % HASHING_BUFFER_SIZE) != 0) ||\
     (((USER_APP_FAR_END_ADDRESS - USER_APP_FAR_START_ADDRESS + 1) % HASHING_BUFFER_SIZE) != 0) )
#error "Please select the hashing buffer size so user app length modulo the buffer size will be 0"
#endif


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
* Function Name: void BL_HASHING_Init(void)
* Description  : Init the hashing module 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void BL_HASHING_Init(void)
{
    /* Reverse input --> according to CRC16-CCITT */
    R_CRC_Set(0xFFFF);
}

/***********************************************************************************************************************
* Function Name: void BL_HASHING_Calculate(uint8_t NEAR_PTR * buffer, uint16_t size)
* Description  : Push data to hashing processor
* Arguments    : uint8_t * buffer: near buffer containing data
*              : uint16_t size: buffer size
* Return Value : None
***********************************************************************************************************************/
void BL_HASHING_Calculate(uint8_t NEAR_PTR * buffer, uint16_t size)
{
    R_CRC_Calculate(buffer, size);
}

/***********************************************************************************************************************
* Function Name: void BL_HASHING_GetResult(bl_hashing_data * hdat)
* Description  : Get result from hashing processor
* Arguments    : bl_hashing_data * hdat: hashing data
* Return Value : None
***********************************************************************************************************************/
void BL_HASHING_GetResult(bl_hashing_data NEAR_PTR * hdat)
{
    uint16_t value;
    
    /* Reverse output --> according to CRC16-CCITT */
    value = R_CRC_GetResult() ^ 0xFFFF;
    
    /* Copy to output */
    BL_memcpy_nn((uint8_t *)hdat, (uint8_t *)&value, sizeof(bl_hashing_data));
}

/***********************************************************************************************************************
* Function Name: void BL_HASHING_Digest(bl_hashing_data * hdat, uint8_t area)
* Description  : Calculate hash for user app in different storage area
* Arguments    : bl_hashing_data * hdat: output pointer for hash data
*              : uint8_t area: area selection 
* Return Value : none
***********************************************************************************************************************/
static void BL_HASHING_Digest(bl_hashing_data * hdat, uint8_t area)
{
    /* Deprecated, proprietary image support embedded hash */
}

/* Public APIs for user app to access */
#ifdef __CCRL__
#pragma section text BLShareTx
#endif

/***********************************************************************************************************************
* Function Name: void BL_HASHING_DigestUserAppBackupSFL(bl_hashing_data *hdat)
* Description  : Calculate hash for current user app in Serial Flash (backup area) 
* Arguments    : bl_hashing_data * hdat: output pointer for hash data
* Return Value : none
***********************************************************************************************************************/
#ifdef __ICCRL78__
__root
#endif
void BL_HASHING_DigestUserAppBackupSFL(bl_hashing_data *hdat)
{
    BL_HASHING_Digest(hdat, HASHING_AREA_SFL_USERAPP_OLD);
}

/***********************************************************************************************************************
* Function Name: void BL_HASHING_DigestUserAppROM(bl_hashing_data *hdat)
* Description  : Calculate hash for current user app in ROM
* Arguments    : bl_hashing_data * hdat: output pointer for hash data
* Return Value : none
***********************************************************************************************************************/
#ifdef __ICCRL78__
__root
#endif
void BL_HASHING_DigestUserAppROM(bl_hashing_data *hdat)
{
    BL_HASHING_Digest(hdat, HASHING_AREA_ROM);
}

