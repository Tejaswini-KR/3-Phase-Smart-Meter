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
* File Name    : bl_serialflash.h
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : CA78K0R
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : SerialFlash MW Layer APIs
***********************************************************************************************************************/

#ifndef __BL_SERIALFLASH_H
#define __BL_SERIALFLASH_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "typedef.h"        /* GSCE Standard Typedef */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/*
 * Device Information
 * Re-map these below information when change SerialFlash device or SPI bus
 * Current device: SST25VF016B
 */
#define SFL_BUS_SPEED                       1000000             /* SPI Bus speed (Hz) */
#define SFL_DEVICE_START_ADDR               0x00000             /* SerialFlash device start address */
#define SFL_DEVICE_PHYSICAL_SIZE            0x200000            /* SerialFlash device size (total bytes) */
#define SFL_DEVICE_MINIMUM_BLOCK_SIZE       (0x1000)            /* SerialFlash minimum erase size (bytes)   */
#define SFL_DEVICE_MAXIMUM_BLOCK_SIZE       (0x10000)           /* SerialFlash minimum erase size (bytes)   */
#define SFL_DEVICE_BLOCK_ADDR_MASK          (0xFFFFF000)        /* Mask of address: relate to block size (refer to datasheet) */
#define SFL_DEVICE_BYTE_PROGRAM_TIME        (10)                /* Time to program one byte : (us)          */
#define SFL_DEVICE_WRITE_STATUS_TIME        (15)                /* Time to write to status register : (us)  */
#define SFL_MAX_MINIMUM_BLOCK_ERASE_TIME    (25000)             /* Time to erase minimum size : (us)        */
#define SFL_MAX_CHIP_ERASE_TIME             (50000)             /* Time to erase whole chip : (us)          */

/* SerialFlash Return Code */
#define SFL_OK                              0           /* Normal end */
#define SFL_ERROR                           1           /* Error in SerialFlash */
#define SFL_ERROR_NO_RESPOND                2           /* Device does not respond */
#define SFL_ERROR_SIZE                      3           /* Expected size and address are not suitable */
#define SFL_NOT_FORMATTED                   4           /* DataFlash not formatted */

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/
/* API control operation of SFL SPI driver: do not call these if not using for power management */
uint8_t BL_SFL_Init(void);                                                 /* SerialFlash Init */
uint8_t BL_SFL_Stop(void);                                                 /* SerialFlash Stop */

/* API for SFL operation: erase, read, write 
 * Note:
 * . For erase function: input the address belong to the block to erase
 * . For write function: ensure the data is erase before writting, provided API not check this
*/
uint8_t BL_SFL_DeviceErase4KB(uint32_t addr);                              /* SerialFlash Erase Block 4K */
uint8_t BL_SFL_DeviceErase64KB(uint32_t addr);                             /* SerialFlash Erase Block 64K */
uint8_t BL_SFL_DeviceEraseAll(void);                                       /* SerialFlash Erase whole chip */
uint8_t BL_SFL_DeviceWriteProtectAll(void);                                /* SerialFlash Protect Write to memory */
uint8_t BL_SFL_DeviceWriteUnProtectAll(void);                              /* SerialFlash UnProtect Write to memory */
uint8_t BL_SFL_DeviceRead(uint32_t addr, uint8_t *buf, uint16_t size);     /* SerialFlash Read memory */
uint8_t BL_SFL_DeviceWrite(uint32_t addr, uint8_t *buf, uint16_t size);    /* SerialFlash Write to memory (write area must be blank before) */

#endif /* __BL_SERIALFLASH_H */
