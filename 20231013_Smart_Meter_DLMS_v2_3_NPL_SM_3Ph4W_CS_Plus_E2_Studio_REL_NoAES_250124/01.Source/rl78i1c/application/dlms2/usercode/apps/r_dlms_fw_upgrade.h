/***********************************************************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
************************************************************************************************************************
* File Name    : r_dlms_firware_upgrade
* Version      : 1.00
* Description  : Description
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
***********************************************************************************************************************/
// 2018-03-29 New create

#ifndef _R_DLMS_FIRMWARE_UPGRADE_H
#define _R_DLMS_FIRMWARE_UPGRADE_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* DLMS */
#include "typedef.h"

#include "r_dlms_config.h"
#include "bl_serialflash.h"
#include "bl_header.h"
/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
// Image transfer enable
#define R_DLMS_IMG_TRANSFER_ENABLE          (1)


/* For firmware upgrade */
#define HASHING_TYPE_CRC16_CCITT            (0)
#define HASHING_TYPE_CRC32_ETHERNET         (1)
//#define HASHING_TYPE_MD5                  (2)
#define HASHING_LENGTH                      (2)
#define HASHING_TYPE_SHA1                   (3)
#define HASHING_TYPE_SHA256                 (4)
#define HASHING_TYPE_SHA384                 (5)
#define HASHING_TYPE_SHA512                 (6)
           
#define DEVICE_ROM_SIZE                     (262144*2)
#define DEVICE_BLOCK_SIZE                   (1024)

#define IMAGE_ALLOCATED_SIZE                (DEVICE_FLASH_ROM_SIZE)
#define DEVICE_IMAGE_DOWNLOAD_START_ADDR    (EXT_MEM_IMAGE_START_ADDRESS)           
                                                               
#if (R_DLMS_IMG_TRANSFER_ENABLE)
#define IMAGE_BLOCK_TRANSFER_SIZE           (256)
#define IMAGE_TRANSFER_ENABLE        (1)
#else
#define IMAGE_BLOCK_TRANSFER_SIZE           (0)
#define IMAGE_TRANSFER_ENABLE        (0)
#endif//R_DLMS_IMG_TRANSFER_ENABLE

/* API mapping */
#define DEVICE_STORAGE_ERASE_SIZE           (SFL_DEVICE_MINIMUM_BLOCK_SIZE)
#define DEVICE_STORAGE_BLK_ERASE(addr)      BL_SFL_DeviceErase4KB(addr)


#if ((IMAGE_BLOCK_TRANSFER_SIZE & (IMAGE_BLOCK_TRANSFER_SIZE - 1)) != 0)
    #error  "Block transfer size need to be power of  2 for easy management with serial flash"
#endif



/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef union tag_dlms_fwu_self_check_t
{
    struct {
        uint8_t image_incomplete : 1;
        uint8_t num_of_region:1;
        uint8_t hash_type:1;
        uint8_t region_range_error:1;
        uint8_t region_range_invalid:1;
        uint8_t region_size_invalid:1;
        uint8_t img_size_not_match:1;
    } bit;
    uint8_t errors;
} dlms_fwu_self_check_t;

typedef enum tagUpdateStatus
{
    PASSED,
    FAILED_FLASH_ERROR,
    FAILED_IMAGE_CANNOT_START,
    FAILED_VERIFICATION_ADDRESS_OUT_RANGE,
    FAILED_VERIFICATION_HASH_UNMATCHED,
    FAILED_UNCLEAR_REASON,
    NO_UPDATE = 0xFF,
} bl_image_update_status;

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/
#if( R_DLMS_IMG_TRANSFER_ENABLE ) /* R_DLMS_IMG_TRANSFER_ENABLE */

/* Current implementation require the image download area to be 64kB alignment in serial flash for fast erasure */
#if ((DEVICE_IMAGE_DOWNLOAD_START_ADDR % SFL_DEVICE_MAXIMUM_BLOCK_SIZE) != 0)
    #error "Image download start address must be 64kB alignment "
#endif

/* Current implementation require serial flash erase size must larger than block transfer size */
#if (DEVICE_STORAGE_ERASE_SIZE < DEVICE_BLOCK_TRANSFER_SIZE)
    #error  "Serial flash storage size cannot be smaller than block transfer size"
#endif

uint8_t R_DLMS_FWU_GetImgTransferStatus(uint8_t * p_status);
uint8_t R_DLMS_FWU_GetImgBlockTransferStatus(uint8_t * p_status, uint16_t * p_len);
uint8_t R_DLMS_FWU_GetImgFirstNotTransfferedBlock(uint32_t * p_block_no);
uint8_t R_DLMS_FWU_GetImgSize(uint32_t * p_image_size);
uint8_t R_DLMS_FWU_GetImgId(uint8_t * p_id, uint16_t * p_len);
uint8_t R_DLMS_FWU_GetImgSignature(uint8_t * p_signature, uint16_t * p_len);
uint8_t R_DLMS_FWU_SetAssociatingStatus(uint8_t status);

uint8_t R_DLMS_FWU_ImageTransferInitiate(uint8_t * p_identifier, uint16_t length, uint32_t * p_image_size);
uint8_t R_DLMS_FWU_ImageBlockTransfer(uint32_t * p_block_number, uint8_t * p_block_data, uint16_t block_data_length);
uint8_t R_DLMS_FWU_ImageVerify(void);
//uint8_t R_DLMS_FWU_ImageActivate(void);

uint8_t R_DLMS_FWU_Init(void);
void R_DLMS_FWU_PollingProcess(void);

#else
#define R_DLMS_FWU_GetImgTransferStatus             {;}
#define R_DLMS_FWU_GetImgBlockTransferStatus        {;}
#define R_DLMS_FWU_GetImgFirstNotTransfferedBlock   {;}
#define R_DLMS_FWU_GetImgSize                       {;}
#define R_DLMS_FWU_GetImgId                         {;}
#define R_DLMS_FWU_GetImgSignature                  {;}
#define R_DLMS_FWU_SetAssociatingStatus             {;}

#define R_DLMS_FWU_ImageTransferInitiate(a, b, c)   (1)
#define R_DLMS_FWU_ImageBlockTransfer(a, b, c)      (1)
#define R_DLMS_FWU_ImageVerify()                    (1)


#define R_DLMS_FWU_Init()                            {;}
#define R_DLMS_FWU_PollingProcess()                   {;}

#endif /* R_DLMS_IMG_TRANSFER_ENABLE */

uint8_t R_DLMS_FWU_ImageActivate(void);

#endif /* _R_DLMS_FIRMWARE_UPGRADE_H */