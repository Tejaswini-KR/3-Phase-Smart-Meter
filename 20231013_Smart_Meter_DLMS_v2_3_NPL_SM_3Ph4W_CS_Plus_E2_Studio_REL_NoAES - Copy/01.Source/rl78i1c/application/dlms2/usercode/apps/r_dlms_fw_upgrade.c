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
* Copyright (C) 2013, 2016 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_dlms_fw_upgrade.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : CCRL
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : 
************************************************************************************************************************
* History      : 2018-03-12 New creation
***********************************************************************************************************************/
// 2018-03-29 New create
/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Drivers */
#include "r_cg_macrodriver.h"           /* Macro Driver Definitions */
#include "r_cg_crc.h"                   /* CG CRC Driver */

/* Standard library */
#include <string.h>

/* Wrapper */
#include "wrp_app_ext.h"

/* Bootloader */
#include "bl_hashing.h"
#include "bl_image.h"
#include "bl_serialflash.h"
#include "bl_operation.h"

/* Meter application */

/* DLMS */
#include "r_dlms_class18.h"

#include "r_dlms_app.h"
#include "r_dlms_storage.h"
#include "r_dlms_format.h"
#include "r_dlms_fw_upgrade.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define IS_MULTIPLE_OF_BLOCK_SIZE(x)                    ( ((x) % DEVICE_FLASH_BLOCK_SIZE) == 0 )
#define NUM_OF_IMAGE_BLOCK_IN_ONE_SFL_BLOCK             ((uint32_t)DEVICE_STORAGE_ERASE_SIZE / IMAGE_BLOCK_TRANSFER_SIZE)

/* Using for checking firmware upgrade code:
* Simulate following abnormal cases
* + A received, written block resent by client, OR
* + A block written failed (hash not matched when read back)
* The block number that mark as failed during simulation is chosen as below (index from 0)
* Please only enable this macro during debugging, not used for production code 
*/
#define SIMULATE_IMAGE_PACKET_RETRANSFER                FALSE
#define SIMULATE_IMAGE_PACKET_RETRANSFER_BLOCK_NUMBER   29

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct tag_dlms_fwu_flag_t
{
    uint8_t associating:1;
    uint8_t verified:1;
    uint8_t activate_start:1;
} dlms_fwu_flag_t;

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

dlms_fwu_flag_t g_Class18_fwu_flag;

#if (SIMULATE_IMAGE_PACKET_RETRANSFER == TRUE)
uint8_t g_class18_retransfer_simulate_done;
#endif

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

#if ( defined (R_DLMS_IMG_TRANSFER_ENABLE ) && R_DLMS_IMG_TRANSFER_ENABLE == 1)
/* Internal Get, Set */
static uint8_t R_DLMS_FWU_GetImgBlockTransferStatusLength(uint16_t * p_len);
static uint8_t R_DLMS_FWU_SetImgTransferStatus(uint8_t * p_status);
static uint8_t R_DLMS_FWU_SetImgSignature(uint16_t * p_signature);

/* Helper functions */
static uint8_t R_DLMS_FWU_ImageSelfCheck(void);
static void R_DLMS_FWU_CheckImageActivationStatus(void);

/******************************************************************************
* Function Name : R_DLMS_FWU_GetImgBlockTransferStatusLength
* Interface     : uint8_t R_DLMS_FWU_GetImgBlockTransferStatusLength(
*               :     uint16_t * p_len
*               : );
* Description   : Get image block transfer status length from EEPROM
* Arguments     : uint16_t * p_len: pointer to length value
* Function Calls: None
* Return Value  : uint8_t: RLT_SUCCESS if no error
******************************************************************************/
static uint8_t R_DLMS_FWU_GetImgBlockTransferStatusLength(uint16_t * p_len)
{
    DLMS_STORAGE info = { STORAGE_EEPROM_DLMS_IMG_BITSTRING_LENGTH_ADDR, STORAGE_EEPROM_DLMS_IMG_BITSTRING_LENGTH_SIZE };

    // Read image size from eeprom
    R_DLMS_EEPROM_Read(info, (uint8_t *)p_len);

    /* If length is out of range, consider storage not initialized, reset length to 0 */
    if( (*p_len) > (IMAGE_ALLOCATED_SIZE / IMAGE_BLOCK_TRANSFER_SIZE) )
    {
        *p_len = 0;
        R_DLMS_EEPROM_Write(info, (uint8_t *)p_len);
    }

    // Return image size
    return RLT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_FWU_SetImgTransferStatus
* Interface     : uint8_t R_DLMS_FWU_SetImgTransferStatus(
*               :     uint8_t * p_status
*               : );
* Description   : Set image transfer status to EEPROM
* Arguments     : uint8_t * p_status: pointer to image transfer status
* Function Calls: None
* Return Value  : uint8_t: RLT_SUCCESS if no error
******************************************************************************/
static uint8_t R_DLMS_FWU_SetImgTransferStatus(uint8_t * p_status)
{
    DLMS_STORAGE info = { STORAGE_EEPROM_DLMS_IMG_STATUS_ADDR, STORAGE_EEPROM_DLMS_IMG_STATUS_SIZE };

    // Read image size from eeprom
    R_DLMS_EEPROM_Write(info, (uint8_t *)p_status);

    // Return image size
    return RLT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_FWU_SetImgSignature
* Interface     : uint8_t R_DLMS_FWU_SetImgTransferStatus(
*               :     uint16_t signature
*               : );
* Description   : Set image signature to EEPROM
* Arguments     : uint16_t signature: using 16bit value to save code size
* Function Calls: None
* Return Value  : uint8_t: RLT_SUCCESS if no error
******************************************************************************/
static uint8_t R_DLMS_FWU_SetImgSignature(uint16_t * p_signature)
{
    DLMS_STORAGE info = { STORAGE_EEPROM_DLMS_IMG_SIGNATURE_ADDR, STORAGE_EEPROM_DLMS_IMG_SIGNATURE_SIZE };

    // Read image size from eeprom
    R_DLMS_EEPROM_Write(info, (uint8_t *)p_signature);

    // Return image size
    return RLT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_FWU_ImageSelfCheck
* Interface     : uint8_t R_DLMS_FWU_ImageSelfCheck(void)
* Description   : Self check the downloaded Renesas proprietary image through meta data content
*               : This not included the integrity checking (verification), need to call it separately
* Arguments     : None
* Function Calls: None
* Return Value  : 0 is Pass, Other is FAIL
******************************************************************************/
static uint8_t R_DLMS_FWU_ImageSelfCheck(void)
{
    /* Check the content of image (using embedded metadata area) */
    uint32_t region_start_addr;
    uint32_t region_end_addr;
    uint32_t accumulated_size;
    uint32_t image_size;
    bl_properties properties;
    uint8_t i, hash_type, number_of_region;
    dlms_fwu_self_check_t error_flg;
    uint16_t embedded_hash_value;
    uint16_t num_of_blocks;
    uint32_t first_not_transferred_block;

    /* 1. Check image transfer completeness */
    /* Get number of calculated transfer blocks */
    R_DLMS_FWU_GetImgBlockTransferStatusLength(&num_of_blocks);
    R_DLMS_FWU_GetImgFirstNotTransfferedBlock(&first_not_transferred_block);

    /* First not transfer block must equal calculated blocks to be considered as complete */
    if (first_not_transferred_block != num_of_blocks)
    {
        error_flg.bit.image_incomplete = 1;
        return error_flg.errors;
    }
    
    /* Assign the image size information */
    R_DLMS_FWU_GetImgSize(&image_size);

    BL_OPERATION_GetProperties(&properties);

    /* Assign the number of region information */
    BL_SFL_DeviceRead(
        DEVICE_IMAGE_DOWNLOAD_START_ADDR,
        &number_of_region,
        sizeof(number_of_region)
    );

    BL_SFL_DeviceRead(
        DEVICE_IMAGE_DOWNLOAD_START_ADDR + 1 + (number_of_region * 8),
        &hash_type,
        sizeof(hash_type)
    );

    /* 2. Do checking on image meta data */

    /* Image size, number of region and hash type must be read before calling this function */
    if (number_of_region == 0)
    {
        /* Number of region cannot be 0 */
        error_flg.bit.num_of_region = 1;
        return error_flg.errors;
    }
    else if (hash_type != HASHING_TYPE_CRC16_CCITT)
    {
        /* Hashing type must be 16bit CCITT for this platform */
        error_flg.bit.hash_type = 1;
        return error_flg.errors;
    }
    else
    {
        accumulated_size = (number_of_region * 8) + 2;

        for (i = 0; i < number_of_region; i++)
        {
            /* Start address of 1st region (uint32_t type), right after number of region information */
            BL_SFL_DeviceRead(DEVICE_IMAGE_DOWNLOAD_START_ADDR + 1 + (i * 8),
                (uint8_t *)&region_start_addr,
                sizeof(uint32_t)
            );

            /* End address of 1st region (uint32_t type), right after 1st region start address */
            BL_SFL_DeviceRead(DEVICE_IMAGE_DOWNLOAD_START_ADDR + 1 + (i * 8) + sizeof(uint32_t),
                (uint8_t *)&region_end_addr,
                sizeof(uint32_t)
            );

            if (region_end_addr <= region_start_addr)
            {
                /* Region information wrong --> Reset the image translation */
                error_flg.bit.region_range_error = 1;
                return error_flg.errors;
            }

            if (((region_start_addr < properties.ext_mem.image_start_addr) && (region_start_addr > properties.ext_mem.image_end_addr)) ||
                ((region_end_addr   < properties.ext_mem.image_start_addr) && (region_end_addr   > properties.ext_mem.image_end_addr)))
            {
                /* Region out of allowable range: */
                error_flg.bit.region_range_invalid = 1;
                return error_flg.errors;
            }

            if ((IS_MULTIPLE_OF_BLOCK_SIZE(region_start_addr) != 1) ||
                (IS_MULTIPLE_OF_BLOCK_SIZE((region_end_addr + 1)) != 1))
            {
                /* The address must be power of 2 */
                error_flg.bit.region_size_invalid = 1;
                return error_flg.errors;
            }

            accumulated_size += (region_end_addr - region_start_addr) + 1;
        }

        accumulated_size += HASHING_LENGTH;

        if (accumulated_size != image_size)
        {
            /* Accumulated length must equal the downloaded image size */
            error_flg.bit.img_size_not_match = 1;
            return error_flg.errors;
        }
    }

    /* Work around to get image signature by fetching directly from embedded hash */
    BL_SFL_DeviceRead(
        DEVICE_IMAGE_DOWNLOAD_START_ADDR + image_size - HASHING_LENGTH,
        (uint8_t *)&embedded_hash_value,
        sizeof(embedded_hash_value)
    );
    R_DLMS_FWU_SetImgSignature(&embedded_hash_value);

    return 0; /* OK */
}

/******************************************************************************
* Function Name : R_DLMS_FWU_CheckImageActivationStatus
* Interface     : void R_DLMS_FWU_CheckImageActivationStatus(void)
* Description   : Read bootloader information to check if there's any update activity
* Arguments     : None
* Function Calls: TBD
* Return Value  : None
******************************************************************************/
static void R_DLMS_FWU_CheckImageActivationStatus(void)
{
    bl_startup_status       bl_status;
    bl_image_update_status  report_status;
	img_transfer_status_t	image_transfer_status;
	
    BL_OPERATION_GetStartupStatus(&bl_status);

    /* Fill the image update result */
    if (bl_status.image_update.details.new_update_info == 1)
    {
        if (bl_status.image_update.details.update_sucess == 1)
        {
            image_transfer_status = IMG_ACTIVATE_SUCCESSFUL;
            report_status = PASSED;
        }
        else if (bl_status.image_update.details.update_failed_flash_writing_error == 1)
        {
            image_transfer_status = IMG_ACTIVATE_FAILED;
            report_status = FAILED_FLASH_ERROR;
        }
        else if (bl_status.image_update.details.update_failed_new_image_not_work == 1)
        {
            image_transfer_status = IMG_ACTIVATE_FAILED;
            report_status = FAILED_IMAGE_CANNOT_START;
        }
        else if (bl_status.image_update.details.verification_failed_address_out_of_range == 1)
        {
            image_transfer_status = IMG_ACTIVATE_FAILED;
            report_status = FAILED_VERIFICATION_ADDRESS_OUT_RANGE;
        }
        else if (bl_status.image_update.details.verification_failed_hash_unmatched == 1)
        {
            image_transfer_status = IMG_ACTIVATE_FAILED;
            report_status = FAILED_VERIFICATION_HASH_UNMATCHED;
        }
        else
        {
            /* Abnormal condition, should not appear */
            image_transfer_status = IMG_ACTIVATE_FAILED;
            report_status = FAILED_UNCLEAR_REASON;
        }
    }
    else
    {
        report_status = NO_UPDATE;
    }

    if (report_status != NO_UPDATE)
    {
        R_DLMS_FWU_SetImgTransferStatus((uint8_t *)&image_transfer_status);
        BL_OPERATION_AcknowledgeImageUpdateStatus();
    }
}

/******************************************************************************
* Function Name : R_DLMS_FWU_CheckImageTransferStatus
* Interface     : void R_DLMS_FWU_CheckImageTransferStatus(void)
* Description   : Check stored image transfer status
* Arguments     : None
* Function Calls: TBD
* Return Value  : None
******************************************************************************/
static void R_DLMS_FWU_CheckImageTransferStatus(void)
{
    img_transfer_status_t image_transfer_status;

    R_DLMS_FWU_GetImgTransferStatus((uint8_t *)&image_transfer_status);

    /* Check invalid transfer status */
    if (image_transfer_status > IMG_ACTIVATE_FAILED)
    {
        /* Invalid transfer status, reset and save to EEPROM */
        image_transfer_status = IMG_TRANS_NOT_INITIATED;
        R_DLMS_FWU_SetImgTransferStatus((uint8_t *)&image_transfer_status);
    }

    /* If verify initiated return from previous step */
    if (image_transfer_status == IMG_VERIFY_INITIATED)
    {
        image_transfer_status = IMG_TRANS_INITIATED;
        R_DLMS_FWU_SetImgTransferStatus((uint8_t *)&image_transfer_status);
    }
}

/******************************************************************************
* Function Name : R_DLMS_FWU_GetImgTransferStatus
* Interface     : uint8_t R_DLMS_FWU_GetImgTransferStatus(
*               :   uint8_t * p_status
*               : );
* Description   : Get image transfer status from EEPROM
* Arguments     : uint8_t * p_status: pointer to status value
* Function Calls: TBD
* Return Value  : uint8_t: RLT_SUCCESS if no error or RLT_ERR_NULL
******************************************************************************/
uint8_t R_DLMS_FWU_GetImgTransferStatus(uint8_t * p_status)
{
    DLMS_STORAGE info = { STORAGE_EEPROM_DLMS_IMG_STATUS_ADDR, STORAGE_EEPROM_DLMS_IMG_STATUS_SIZE };

    ASSERT_TRUE_RET_VAL(
        p_status == NULL,
        RLT_ERR_NULL
    );

    // Read image size from eeprom
    R_DLMS_EEPROM_Read(info, (uint8_t *)p_status);

    // Return image size
    return RLT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_FWU_GetImgBlockTransferStatus
* Interface     : uint8_t R_DLMS_FWU_GetImgBlockTransferStatus(
*               :   uint8_t * p_status, uint16_t * p_len
*               : );
* Description   : Get image block transfer status from EEPROM
* Arguments     : uint8_t * p_status: pointer to block transfer status value
*               : uint16_t * p_len: pointer to number of blocks value
* Function Calls: TBD
* Return Value  : uint8_t: RLT_SUCCESS if no error or RLT_ERR_NULL
******************************************************************************/
uint8_t R_DLMS_FWU_GetImgBlockTransferStatus(uint8_t * p_status, uint16_t * p_len)
{
    DLMS_STORAGE info;
    uint16_t length;
    img_transfer_status_t status;

    ASSERT_TRUE_RET_VAL(
        p_status == NULL || p_len == NULL,
        RLT_ERR_NULL
    );

    /* Check the image transfer status: not read EEPROM data unless initiated */
    R_DLMS_FWU_GetImgTransferStatus((uint8_t *)&status);

    if (status == IMG_TRANS_NOT_INITIATED)
    {
        *p_status = 0;
        *p_len = 0;
        return RLT_SUCCESS;
    }

    R_DLMS_FWU_GetImgBlockTransferStatusLength(&length);
    
    /* The length get from this API is the bit length, not byte length */
    *p_len = length;
    
    /* Convert into bit length to byte length for reading the bitstring buffer from EEPROM */
    info.address = STORAGE_EEPROM_DLMS_IMG_BITSTRING_ADDR;
    info.length = (length + 7) / 8;

    // Read image size from eeprom
    R_DLMS_EEPROM_Read(info, (uint8_t *)p_status);

    // Return image size
    return RLT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_FWU_GetImgFirstNotTransfferedBlock
* Interface     : uint8_t R_DLMS_FWU_GetImgFirstNotTransfferedBlock(
*               :   uint32_t * p_block_no
*               : );
* Description   : Get image first not transferred block from EEPROM
* Arguments     : uint16_t * p_block_no: pointer to first not transfferd block value
* Function Calls: TBD
* Return Value  : uint8_t: RLT_SUCCESS if no error or RLT_ERR_NULL
******************************************************************************/
uint8_t R_DLMS_FWU_GetImgFirstNotTransfferedBlock(uint32_t * p_block_no)
{
    uint16_t len_u16, i, j;
    uint32_t blockNumber;
    uint8_t b;
    img_transfer_status_t status;
    DLMS_STORAGE info;

    ASSERT_TRUE_RET_VAL(
        p_block_no == NULL,
        RLT_ERR_NULL
    );

    /* Check the image transfer status: not read EEPROM data unless initiated */
    R_DLMS_FWU_GetImgTransferStatus((uint8_t *)&status);

    if (status == IMG_TRANS_NOT_INITIATED)
    {
        *p_block_no = 0;
        return RLT_SUCCESS;
    }

    R_DLMS_FWU_GetImgBlockTransferStatusLength(&len_u16);

    /* Convert into bit length to byte length for reading the bitstring buffer from EEPROM */
    len_u16 = (len_u16 + 7) / 8;
    blockNumber = 0;

    /* Prepare storage information of bitstring with read length fixed to 1 */
    info.address = STORAGE_EEPROM_DLMS_IMG_BITSTRING_ADDR;
    info.length = 1;

    /* Find first 0 in the bit-string */
    for (i = 0; i < len_u16; i++)
    {
        /* Read bitstring from eeprom */
        R_DLMS_EEPROM_Read(info, (uint8_t *)&b);

        /* Scan for 1's bit and count block number until there's 0 bit or reaching len_u16 */
        for (j = 0; j <= 7; j++)
        {
            /* Scan from MSB, each 1 bit count as 1 block number */
            if ((b & (1 << (7 - j))) != 0x00)
            {
                /* Bit 1: count as 1 block number */
                blockNumber += 1;
            }
            else
            {
                /* Bit 0: keep blockNumber, stop counting */
                break;
            }
        }
        
        /* Point to next status bit string byte */
        info.address += 1;

        /* Feed WDT while loop has eeprom operation */
        R_WDT_Restart();
    }

    *p_block_no = blockNumber;

    // Return image size
    return RLT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_FWU_GetImgSize
* Interface     : uint8_t R_DLMS_FWU_GetImgSize(
*               :   uint32_t * p_image_size
*               : );
* Description   : Get image size from EEPROM
* Arguments     : uint32_t * p_image_size: pointer to image size value
* Function Calls: TBD
* Return Value  : uint8_t: RLT_SUCCESS if no error or RLT_ERR_NULL
******************************************************************************/
uint8_t R_DLMS_FWU_GetImgSize(uint32_t * p_image_size)
{
    DLMS_STORAGE info = { STORAGE_EEPROM_DLMS_IMG_SIZE_ADDR, STORAGE_EEPROM_DLMS_IMG_SIZE_SIZE };
    img_transfer_status_t status;

    /* Check the image transfer status: signature not return before initiated */
    R_DLMS_FWU_GetImgTransferStatus((uint8_t *)&status);

    if (status == IMG_TRANS_NOT_INITIATED)
    {
        *p_image_size = 0;
        return RLT_SUCCESS;
    }

    ASSERT_TRUE_RET_VAL(
        p_image_size == NULL,
        RLT_ERR_NULL
    );

    // Read image size from eeprom
    R_DLMS_EEPROM_Read(info, (uint8_t *)p_image_size);

    // Return image size
    return RLT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_FWU_GetImgId
* Interface     : uint8_t R_DLMS_FWU_GetImgId(
*               :   uint8_t * p_id, uint16_t * p_len
*               : );
* Description   : Get image size from EEPROM
* Arguments     : uint32_t * p_image_size: pointer to image size value
* Function Calls: TBD
* Return Value  : uint8_t: RLT_SUCCESS if no error or RLT_ERR_NULL
******************************************************************************/
uint8_t R_DLMS_FWU_GetImgId(uint8_t * p_id, uint16_t * p_len)
{
    DLMS_STORAGE info;
    img_transfer_status_t status;

    ASSERT_TRUE_RET_VAL(
        p_id == NULL || p_len == NULL,
        RLT_ERR_NULL
    );

    /* Check the image transfer status: signature not return before initiated */
    R_DLMS_FWU_GetImgTransferStatus((uint8_t *)&status);

    if (status == IMG_TRANS_NOT_INITIATED)
    {
        *p_id = 0;
        *p_len = 0;
        return RLT_SUCCESS;
    }

    /* Get length of image identification */
    info.address = STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_LENGTH_ADDR;
    info.length = STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_LENGTH_SIZE;
    R_DLMS_EEPROM_Read(info, (uint8_t *)p_len);

    /* If length out of range, consider memory not initialize */
    if (*p_len > STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_SIZE)
    {
        *p_len = STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_SIZE;
        memset(p_id, 0, STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_SIZE);
    }
    else
    {
        /* Get image identification */
        info.address = STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_ADDR;
        info.length = *p_len;
        R_DLMS_EEPROM_Read(info, (uint8_t *)p_id);
    }

    // Return image size
    return RLT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_FWU_GetImgSignature
* Interface     : uint8_t R_DLMS_FWU_GetImgSignature(
*               :   uint8_t * p_signature, uint16_t * p_len
*               : );
* Description   : Get image signature from EEPROM (CRC checking of image)
* Arguments     : uint8_t * p_signature: pointer to signature value
*               : uint16_t * p_len: pointer to signature length value
* Function Calls: TBD
* Return Value  : uint8_t: RLT_SUCCESS if no error or RLT_ERR_NULL
******************************************************************************/
uint8_t R_DLMS_FWU_GetImgSignature(uint8_t * p_signature, uint16_t * p_len)
{
    DLMS_STORAGE info;
    img_transfer_status_t status;

    ASSERT_TRUE_RET_VAL(
        p_signature == NULL || p_len == NULL,
        RLT_ERR_NULL
    );

    /* Check the image transfer status: signature not return before verified */
    R_DLMS_FWU_GetImgTransferStatus((uint8_t *)&status);

    /* Note: assume that the status enum follow sequence as in Blue book */
    if (status < IMG_VERIFY_SUCCESSFUL)
    {
        *p_signature = 0;
        *p_len = 0;
        return RLT_SUCCESS;
    }

    /* Fixed signature length */
    *p_len = HASHING_LENGTH;

    /* Get image identification */
    info.address = STORAGE_EEPROM_DLMS_IMG_SIGNATURE_ADDR;
    info.length = HASHING_LENGTH;
    R_DLMS_EEPROM_Read(info, (uint8_t *)p_signature);

    // Return image size
    return RLT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_FWU_SetAssociatingStatus
* Interface     : uint8_t R_DLMS_FWU_SetAssociatingStatus(
*               :   uint8_t status
*               : );
* Description   : Set DLMS associating status to do async image checking
* Arguments     : uint8_t status: associating status (1: associating)
* Function Calls: TBD
* Return Value  : uint8_t: RLT_SUCCESS if no error
******************************************************************************/
uint8_t R_DLMS_FWU_SetAssociatingStatus(uint8_t status)
{
    g_Class18_fwu_flag.associating = status;
    
    return RLT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_FWU_ImageTransferInitiate
* Interface     : uint8_t R_DLMS_FWU_ImageTransferInitiate(
*               :   uint8_t * p_identifier, uint16_t identifier_length, uint32_t image_size
*               : );
* Description   : Initiate the image transfer process
* Arguments     : uint8_t * p_identifier: pointer to image identifier buffer
*               : uint16_t identifier_length: length of the image identifier
*               : uint32_t * p_image_size: pointer to size of the image sent later
* Function Calls: TBD
* Return Value  : uint8_t: RLT_SUCCESS if no error or RLT_ERR_NULL, RLT_ERR_INVALID_PARAMETER , RLT_ERR_OPERATION_CORRUPTED
******************************************************************************/
uint8_t R_DLMS_FWU_ImageTransferInitiate(uint8_t * p_identifier, uint16_t identifier_length, uint32_t * p_image_size)
{
    uint8_t pageBuff[32];
    /* Fill information: device_size and block_size */
    img_transfer_status_t image_transfer_status;
    uint8_t block_transfer_status;
    uint16_t block_transfer_status_len, block_transfer_status_len_byte, writtenLengthByte;
    uint32_t image_size;
    DLMS_STORAGE info;
    
    /* Check input parameters */
    ASSERT_TRUE_RET_VAL(
        p_identifier == NULL || p_image_size == NULL,
        RLT_ERR_NULL
    );

    image_size = *p_image_size;

    ASSERT_TRUE_RET_VAL(
        identifier_length == 0 || image_size == 0,
        RLT_ERR_INVALID_PARAMETER
    );

    /* Set image transfer status to not initiated */
    image_transfer_status = IMG_TRANS_NOT_INITIATED;
    R_DLMS_FWU_SetImgTransferStatus((uint8_t *)&image_transfer_status);

    /*----- Validate parameter ------------------------------------------ */
    /* Check if set identifier length is larger than EEPROM allocation 
    * This is currently consider not important, so just truncate it
    */
    if (identifier_length > STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_SIZE)
    {
        identifier_length = STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_SIZE;
    }
    
    /* Image sent from client should be within allocated size
    */
    if (image_size > (uint32_t)IMAGE_ALLOCATED_SIZE)
    {
        return RLT_ERR_INVALID_PARAMETER;
    }

    /* ----- Update attribute--------------------------------------------*/
    /* Save indentification to memory */
    info.address = STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_LENGTH_ADDR;
    info.length = STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_LENGTH_SIZE;
    R_DLMS_EEPROM_Write(info, (uint8_t *)&identifier_length);

    info.address = STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_ADDR;
    info.length = identifier_length;
    R_DLMS_EEPROM_Write(info, p_identifier);

    /* Save image size to memory */
    info.address = STORAGE_EEPROM_DLMS_IMG_SIZE_ADDR;
    info.length = STORAGE_EEPROM_DLMS_IMG_SIZE_SIZE;
    R_DLMS_EEPROM_Write(info, (uint8_t *)&image_size);

    /* ---- Initiate function -----------------------------------------------*/
    block_transfer_status_len = (image_size + (IMAGE_BLOCK_TRANSFER_SIZE - 1)) / IMAGE_BLOCK_TRANSFER_SIZE;
    info.address = STORAGE_EEPROM_DLMS_IMG_BITSTRING_LENGTH_ADDR;
    info.length = STORAGE_EEPROM_DLMS_IMG_BITSTRING_LENGTH_SIZE;
    R_DLMS_EEPROM_Write(info, (uint8_t *)&block_transfer_status_len);

    R_DLMS_FWU_SetImgSignature(0);
    
    /* Init image block transfer status */
    memset(pageBuff, 0, sizeof(pageBuff));
    block_transfer_status_len_byte = (block_transfer_status_len + 7) / 8;
    info.address = STORAGE_EEPROM_DLMS_IMG_BITSTRING_ADDR;
    writtenLengthByte = 0;
    while (writtenLengthByte < block_transfer_status_len_byte)
    {
        /* Using pageBuff to reduce stack size, pageBuff size check with EEPROM write cycle time */
        if ((block_transfer_status_len_byte - writtenLengthByte) < sizeof(pageBuff))
        {
            info.length = block_transfer_status_len_byte - writtenLengthByte;
        }
        else
        {
            info.length = sizeof(pageBuff);
        }

        R_DLMS_EEPROM_Write(info, pageBuff);

        info.address += info.length;
        writtenLengthByte += info.length;

        /* Feed WDT while loop has eeprom operation */
        R_WDT_Restart();
    }

    
    /* Call bootloader API to clear storage memory */
    if (BL_IMAGE_EraseImageData() != BL_IMAGE_OK)
    {
        return RLT_ERR_OPERATION_CORRUPTED;
    }

    /* ----- Update attribute -------------------------------------------*/
    /* Set image transfer status to initiated */
    image_transfer_status = IMG_TRANS_INITIATED;
    R_DLMS_FWU_SetImgTransferStatus((uint8_t *)&image_transfer_status);

    /* ----- Clear image translation service flag ----------------------*/
    g_Class18_fwu_flag.activate_start = 0;
    g_Class18_fwu_flag.verified = 0;

#if (SIMULATE_IMAGE_PACKET_RETRANSFER == TRUE)
    g_class18_retransfer_simulate_done = 0;
#endif

    // Return image size
    return RLT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_FWU_ImageBlockTransfer
* Interface     : uint8_t R_DLMS_FWU_ImageBlockTransfer(
*               :   uint32_t block_number, uint8_t * p_block_data, uint16_t block_data_length
*               : );
* Description   : Transfer image block data into storage memory
* Arguments     : uint32_t * p_block_number: pointer to block number (index 0)
*               : uint8_t * p_block_data: pointer to buffer of block data
*               : uint16_t block_data_length: length of the block data
* Function Calls: TBD
* Return Value  : uint8_t: RLT_SUCCESS if no error or RLT_ERR_NULL, RLT_ERR , RLT_ERR_OPERATION_CORRUPTED
******************************************************************************/
uint8_t R_DLMS_FWU_ImageBlockTransfer(uint32_t * p_block_number, uint8_t * p_block_data, uint16_t block_data_length)
{
    uint8_t block_transfer_status;
    uint32_t block_status_epr_address;
    uint16_t read_write_length;

    uint8_t status;
    img_transfer_status_t image_transfer_status;
    uint32_t addr, block_number;
    DLMS_STORAGE info;
    uint16_t sfl_block_number;
    uint16_t received_data_crc, read_back_crc, backup_crc;

    /* Check input parameters */
    ASSERT_TRUE_RET_VAL(
        p_block_data == NULL || p_block_number == NULL,
        RLT_ERR_NULL
    );

    ASSERT_TRUE_RET_VAL(
        block_data_length == 0 || block_data_length > IMAGE_BLOCK_TRANSFER_SIZE,
        RLT_ERR_INVALID_PARAMETER
    );

    block_number = *p_block_number;

    /* Check image transfer status */
    R_DLMS_FWU_GetImgTransferStatus((uint8_t *)&image_transfer_status);

    /* Only receive block transfer if transfer initiated */
    ASSERT_TRUE_RET_VAL(
        image_transfer_status != IMG_TRANS_INITIATED,
        RLT_ERR
    );

    /* Read the block transfer status bit string based on this block number */
    block_status_epr_address = (uint32_t)STORAGE_EEPROM_DLMS_IMG_BITSTRING_ADDR + (block_number / 8);
    info.address = block_status_epr_address;
    info.length = 1;
    R_DLMS_EEPROM_Read(info, &block_transfer_status);

    /* If this block already written, proceed to erase step below */
    if (((0x80 >> (block_number % 8)) & block_transfer_status) != 0)
    {
        status = 1;
    }
    else
    {
        addr = block_number * IMAGE_BLOCK_TRANSFER_SIZE;
        /* Writing block data into external storage */
        status = BL_SFL_DeviceWrite(addr + DEVICE_IMAGE_DOWNLOAD_START_ADDR, p_block_data, block_data_length);

        /* Backup CRCD */
        backup_crc = R_CRC_GetResult();

        /* Calculate received data crc */
        R_CRC_Clear();
        R_CRC_Calculate(p_block_data, block_data_length);
        received_data_crc = R_CRC_GetResult();

        /* Utilize input block data as read back buffer to avoid heap + stack overflow */
        BL_SFL_DeviceRead(addr + DEVICE_IMAGE_DOWNLOAD_START_ADDR, p_block_data, block_data_length);

        /* Calculate received data crc */
        R_CRC_Clear();
        R_CRC_Calculate(p_block_data, block_data_length);
        read_back_crc = R_CRC_GetResult();

        /* Restore CRCD */
        R_CRC_Set(backup_crc);

#if (SIMULATE_IMAGE_PACKET_RETRANSFER == TRUE)
        /* Simulate condition that a block retransferred or write failed:
        * Update the block number then mark status as 1 to clear the related block
        */
        if ((block_number == SIMULATE_IMAGE_PACKET_RETRANSFER_BLOCK_NUMBER) && (g_class18_retransfer_simulate_done == 0)) {
            g_class18_retransfer_simulate_done = 1;
            received_data_crc = 0;
        }
#endif
        /* Confirm written packet in serial flash same as received packet */
        if (received_data_crc == read_back_crc) {
            status = 0;
            /* Mark the block as processed and store to EEPROM */
            block_transfer_status |= (0x80 >> (block_number % 8));
            /* Check status of EEPROM_Write function */
            status = R_DLMS_EEPROM_Write(info, &block_transfer_status);
        }
        else {
            status = 1;
        }

    }

    /* If either:
     * This block writing failed or
     * Client want to resend a block that already has data
     * Then erase this block and update the bitstring
    */
    if (status != 0)
    {
        #if(defined(R_DLMS_APPS_MALLOC_USING) && (R_DLMS_APPS_MALLOC_USING == FALSE))
        uint8_t bit_status_clear_buffer[NUM_OF_IMAGE_BLOCK_IN_ONE_SFL_BLOCK / 8];
        #endif
        uint8_t * p_bit_status_clear_buffer;

        sfl_block_number = block_number / NUM_OF_IMAGE_BLOCK_IN_ONE_SFL_BLOCK;

        /* Erase in serial flash */
        DEVICE_STORAGE_BLK_ERASE(DEVICE_IMAGE_DOWNLOAD_START_ADDR + (sfl_block_number * (uint32_t)DEVICE_STORAGE_ERASE_SIZE));

        /* Update block transfer status bit string */
        block_status_epr_address = (uint32_t)STORAGE_EEPROM_DLMS_IMG_BITSTRING_ADDR + 
                       (sfl_block_number * (NUM_OF_IMAGE_BLOCK_IN_ONE_SFL_BLOCK / 8));
        read_write_length  = (uint16_t)(NUM_OF_IMAGE_BLOCK_IN_ONE_SFL_BLOCK / 8);
        #if(defined(R_DLMS_APPS_MALLOC_USING) && (R_DLMS_APPS_MALLOC_USING == TRUE))
        /* Open buffer for bit status clear buffer */
        p_bit_status_clear_buffer = (uint8_t *)WRP_EXT_Heap_Malloc(read_write_length);
        #else
        p_bit_status_clear_buffer = bit_status_clear_buffer;
        #endif
        if (p_bit_status_clear_buffer != NULL) {
            /* Clear all status bit to zero */
            info.address = block_status_epr_address;
            info.length = read_write_length;
            memset(p_bit_status_clear_buffer, 0, read_write_length);
            R_DLMS_EEPROM_Write(info, p_bit_status_clear_buffer);

        #if(defined(R_DLMS_APPS_MALLOC_USING) && (R_DLMS_APPS_MALLOC_USING == TRUE))
            WRP_EXT_Heap_Free(p_bit_status_clear_buffer);
        #endif
        }
        else {
            /* Image transfer process stop due to memory allocation failed */
            return RLT_ERR_NOT_ENOUGH_MEM;
        }
    }

    // Return image size
    return RLT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_FWU_ImageVerify
* Interface     : uint8_t R_DLMS_FWU_ImageVerify(void);
* Description   : Verify image in storage memory in 2 steps:
*               :   1. Self verify the image format (synchronous)
*               :   2. Checking image integrity by hashing the image (asynchronous)
*               : If the image format is correct, it will start the asynchrnous operation
*               : Each PollingProcessing call, it will process chunk of data
*               : After hashing complete, it will update the image transfer status again (verify failed or succeeded)
* Arguments     : None
* Function Calls: TBD
* Return Value  : uint8_t: RLT_SUCCESS if no error or RLT_ERR, RLT_OTHER 
******************************************************************************/
uint8_t R_DLMS_FWU_ImageVerify(void)
{
    img_transfer_status_t image_transfer_status;
    dlms_app_return_error_code_t result;
    
    /* Check image transfer status */
    R_DLMS_FWU_GetImgTransferStatus((uint8_t *)&image_transfer_status);

    /* Only verify if transfer initiated */
    ASSERT_TRUE_RET_VAL(
        image_transfer_status != IMG_TRANS_INITIATED,
        RLT_ERR
    );

    /* Set transfer status to verify initiated */
    image_transfer_status = IMG_VERIFY_INITIATED;
    R_DLMS_FWU_SetImgTransferStatus((uint8_t *)&image_transfer_status);

    /* Do self check image format */
    if (R_DLMS_FWU_ImageSelfCheck() != 0)
    {
        image_transfer_status = IMG_VERIFY_FAILED;
        result = RLT_OTHER;
    }
    else
    {
        /* Image self check done, consider image valid */
        image_transfer_status = IMG_VERIFY_SUCCESSFUL;
        result = RLT_SUCCESS;

        g_Class18_fwu_flag.verified = 1;
    }

    /* Update the status */
    R_DLMS_FWU_SetImgTransferStatus((uint8_t *)&image_transfer_status);

    // Return image size
    return result;
}

/******************************************************************************
* Function Name : R_DLMS_FWU_ImageActivate
* Interface     : uint8_t R_DLMS_FWU_ImageActivate(void);
* Description   : Activate image in storage memory
*               : If image not verify yet, it will start as implicit operation
*               : and will activate once the asynchronous verification finished
* Arguments     : None
* Function Calls: TBD
* Return Value  : uint8_t: RLT_SUCCESS if no error or RLT_ERR_OPERATION_IN_PROGRESS, RLT_OTHER
******************************************************************************/
uint8_t R_DLMS_FWU_ImageActivate(void)
{
    img_transfer_status_t image_transfer_status;
    dlms_app_return_error_code_t result;

    /* Check image transfer status */
    R_DLMS_FWU_GetImgTransferStatus((uint8_t *)&image_transfer_status);

    /* Activating, reply as operation in progress */
    ASSERT_TRUE_RET_VAL(
        image_transfer_status == IMG_ACTIVATE_INITIATED,
        RLT_ERR_OPERATION_IN_PROGRESS
    );

    /* Only activate if verify successfully (explicit activation) or image transfer initiated (implicit activation) */
    ASSERT_TRUE_RET_VAL(
        image_transfer_status != IMG_VERIFY_SUCCESSFUL && image_transfer_status != IMG_TRANS_INITIATED,
        RLT_ERR
    );

    /* Check current image transfer status */
    if (image_transfer_status == IMG_VERIFY_SUCCESSFUL)
    {
        /* If image verification done explicitly before, let client know meter will activate immediately */
        image_transfer_status = IMG_ACTIVATE_INITIATED;
        g_Class18_fwu_flag.verified = 1;
        g_Class18_fwu_flag.activate_start = 1;
        result = RLT_SUCCESS;

        R_DLMS_FWU_SetImgTransferStatus((uint8_t *)&image_transfer_status);
    }
    else if ((image_transfer_status == IMG_TRANS_INITIATED))
    {
        /* If image verification is not done or , do it implicitly on image activation process */

        /* Do self check image format */
        if (R_DLMS_FWU_ImageSelfCheck() != 0)
        {
            image_transfer_status = IMG_ACTIVATE_FAILED;
            result = RLT_OTHER;
        }
        else
        {
            image_transfer_status = IMG_ACTIVATE_INITIATED;
            g_Class18_fwu_flag.verified = 1;
            g_Class18_fwu_flag.activate_start = 1;
            result = RLT_SUCCESS;
        }

        R_DLMS_FWU_SetImgTransferStatus((uint8_t *)&image_transfer_status);
    }
    else
    {
        /* For other case, consider it's not correct step, action failed */
        result = RLT_OTHER;
    }

    // Return image size
    return result;
}
static void Check_Serialflash(void)
{
    uint8_t status;
    uint32_t address = 524288;
    uint8_t buff_write[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};
    uint8_t buff_read[10];
    status = BL_SFL_DeviceErase4KB(address);
    status = BL_SFL_DeviceWrite(address, buff_write, 10);
    status = BL_SFL_DeviceRead(address, buff_read, 10);
    __nop();
}
/******************************************************************************
* Function Name : R_DLMS_FWU_Init
* Interface     : uint8_t R_DLMS_FWU_Init(void);
* Description   : Initialize DLMS FWU Application
*               :  . Checking image activation status from bootloader
* Arguments     : None
* Function Calls: TBD
* Return Value  : uint8_t: RLT_SUCCESS if no error
******************************************************************************/
uint8_t R_DLMS_FWU_Init(void)
{
    BL_SFL_Init();
    R_DLMS_FWU_CheckImageActivationStatus();
    R_DLMS_FWU_CheckImageTransferStatus();
    //Check_Serialflash();

    return RLT_SUCCESS;   // Default is OK
}

/******************************************************************************
* Function Name : R_DLMS_FWU_PollingProcess
* Interface     : void R_DLMS_FWU_PollingProcess(void);
* Description   : Polling processing for DLMS FWU Application
*               :  1. Do request activate image to bootloader if:
*               :       image verified (implicitly or explicitly) and 
*               :       image activated and
*               :       no current active associating on DLMS
* Arguments     : None
* Function Calls: TBD
* Return Value  : None
******************************************************************************/
void R_DLMS_FWU_PollingProcess(void)
{
    if (g_Class18_fwu_flag.activate_start == 1)
    {
        /* DLMS must be idle and image verification completed before */
        if (g_Class18_fwu_flag.verified == 1 &&
            g_Class18_fwu_flag.associating == 0)
        {
            /* Restart now immediately after this function call (no need to reset image activate flag) */
            BL_OPERATION_RequestImageActivation();
        }
    }
}
#else
uint8_t R_DLMS_FWU_ImageActivate(void)
{
    return 0;
}
#endif /* R_DLMS_IMG_TRANSFER_ENABLE */
