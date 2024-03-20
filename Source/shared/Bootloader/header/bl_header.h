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
* File Name    : bl_header.h
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : 
* Description  : 
***********************************************************************************************************************/
#ifndef __BL_HEADER_H
#define __BL_HEADER_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "typedef.h"
#include "compiler.h"

/* Standard library */
#include <stddef.h>

/* Core modules */
#include "bl_interrupt.h"
#include "bl_hashing.h"
#include "bl_image.h"
#include "bl_operation.h"

/* External storage */
#include "bl_serialflash.h"


/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef uint16_t bl_confirm_code_t;

typedef struct tagBLRequest
{
    bl_confirm_code_t recovery_mode;
    bl_confirm_code_t software_reset;
    bl_confirm_code_t activate_image;
    bl_confirm_code_t backup_image;
    bl_confirm_code_t restore_image;
    
} BL_REQUEST;

typedef struct tagBLProgress
{
    bl_confirm_code_t backingup_user_app_from_ROM;
    bl_confirm_code_t erasing_user_app_in_ROM;
    bl_confirm_code_t transferring_new_user_app_to_ROM;
    bl_confirm_code_t restoring_user_app_to_ROM;
    
} BL_PROGRESS;

typedef struct tagBLInformation
{
    uint8_t             reset_count;
    uint8_t             image_restore_count;
    BL_REQUEST          request;
    BL_PROGRESS         progress;
} BL_INFORMATION;

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/*
 * Device information
*/
#ifdef __CCRL__

#if   ( (defined __R5F10NPJIODEFINE_HEADER__) || (defined __R5F10NMJIODEFINE_HEADER__) )
    #define __RAM_ADDR_START                (0xBF00)
    #define DEVICE_FLASH_ROM_SIZE           (0x40000)
#elif ( (defined __R5F10NLGIODEFINE_HEADER__) || (defined __R5F10NMGIODEFINE_HEADER__) || (defined __R5F10NPGIODEFINE_HEADER__) )
    #define __RAM_ADDR_START                (0xDF00)
    #define DEVICE_FLASH_ROM_SIZE           (0x20000)
#elif ( (defined __R5F10NLEIODEFINE_HEADER__) || (defined __R5F10NMEIODEFINE_HEADER__) )
    #define __RAM_ADDR_START                (0xE700)
    #define DEVICE_FLASH_ROM_SIZE           (0x10000)
#elif ( (defined __R5F10NPLIODEFINE_HEADER__) )
    #define __RAM_ADDR_START                (0x7F00)
    #define DEVICE_FLASH_ROM_SIZE           (0x80000)
#endif

#endif /* __CCRL__ */ 

#ifdef __ICCRL78__

#if   ( (defined __IOR5F10NPJ_H__) || (defined __IOR5F10NMJ_H__) )
    #define __RAM_ADDR_START                (0xBF00)
    #define DEVICE_FLASH_ROM_SIZE           (0x40000)
#elif ( (defined __IOR5F10NLG_H__) || (defined __IOR5F10NMG_H__) || (defined __IOR5F10NPG_H__) )
    #define __RAM_ADDR_START                (0xDF00)
    #define DEVICE_FLASH_ROM_SIZE           (0x20000)
#elif ( (defined __IOR5F10NLE_H__) || (defined __IOR5F10NME_H__) )
    #define __RAM_ADDR_START                (0xE700)
    #define DEVICE_FLASH_ROM_SIZE           (0x10000)
#elif ( (defined __IOR5F10NPL_H__) )
    #define __RAM_ADDR_START                (0x7F00)
    #define DEVICE_FLASH_ROM_SIZE           (0x80000)
#endif

#endif//__ICCRL78__

#define DEVICE_FLASH_BLOCK_SIZE             (0x400)

/* 
 * User app range in memory
 * Rule to define these area:
 *  + Start_address     : multiple of DEVICE_FLASH_BLOCK_SIZE
 *  + End_address + 1   : multiple of DEVICE_FLASH_BLOCK_SIZE
 *  + Near End_address  :  < __RAM_ADDR_START
 *  + No area overlap with debug monitor area (check .map file for details) (this cannot auto check)
*/

#define USER_APP_NEAR_START_ADDRESS         (0x2000)

#ifdef __CCRL__

#if   ( (defined __R5F10NPJIODEFINE_HEADER__) || (defined __R5F10NMJIODEFINE_HEADER__) )
    #define USER_APP_NEAR_END_ADDRESS           (0xBBFF)

    #define USER_APP_FAR_START_ADDRESS          (0xBC00)
    #define USER_APP_FAR_END_ADDRESS            (0x3FBFF)
#elif ( (defined __R5F10NPLIODEFINE_HEADER__) )
    #define USER_APP_NEAR_END_ADDRESS           (0x7BFF)

    #define USER_APP_FAR_START_ADDRESS          (0x7C00)
    #define USER_APP_FAR_END_ADDRESS            (0x74BFF)
#endif

#endif /* __CCRL__ */ 

#ifdef __ICCRL78__

#if   ( (defined __IOR5F10NPJ_H__) || (defined __IOR5F10NMJ_H__) )
    #define USER_APP_NEAR_END_ADDRESS           (0xBBFF)

    #define USER_APP_FAR_START_ADDRESS          (0xBC00)
    #define USER_APP_FAR_END_ADDRESS            (0x3FBFF)
#elif ( (defined __IOR5F10NPL_H__) )
    #define USER_APP_NEAR_END_ADDRESS           (0x7BFF)

    #define USER_APP_FAR_START_ADDRESS          (0x7C00)
    #define USER_APP_FAR_END_ADDRESS            (0x74BFF)
#endif

#endif//__ICCRL78__

/* User app range definition checking -- Do not edit this part */

#if ((USER_APP_NEAR_START_ADDRESS % DEVICE_FLASH_BLOCK_SIZE != 0) || (USER_APP_FAR_START_ADDRESS % DEVICE_FLASH_BLOCK_SIZE != 0))
  #error "Start address must be multiple of device flash block size"
#endif

#if (((USER_APP_NEAR_END_ADDRESS+1) % DEVICE_FLASH_BLOCK_SIZE != 0) || ((USER_APP_FAR_END_ADDRESS+1) % DEVICE_FLASH_BLOCK_SIZE != 0))
    #error "End address + 1 must be multiple of device flash block size"
#endif

#if (USER_APP_NEAR_END_ADDRESS >= __RAM_ADDR_START)
    #error "User app near end address must be within mirror area"
#endif

/* 
 * Serial flash usage
*/
/* Image properties information */

/* Extra information for paritioning the old and new firmware position */
#define IMAGE_OLD_PARTITION                 (0)
#define IMAGE_NEW_PARTITION                 (1)

#define OLD_IMAGE_START_ADDRESS             (0)

#ifdef __CCRL__

#if   ( (defined __R5F10NPJIODEFINE_HEADER__) || (defined __R5F10NMJIODEFINE_HEADER__) )
    #define NEW_IMAGE_START_ADDRESS             (0x40000)
#elif ( (defined __R5F10NPLIODEFINE_HEADER__) )
    #define NEW_IMAGE_START_ADDRESS             (0x080000)
#endif

#endif /* __CCRL__ */ 

#ifdef __ICCRL78__

#if   ( (defined __IOR5F10NPJ_H__) || (defined __IOR5F10NMJ_H__) )
    #define NEW_IMAGE_START_ADDRESS             (0x40000)
#elif ( (defined __IOR5F10NPL_H__) )
    #define NEW_IMAGE_START_ADDRESS             (0x080000)
#endif

#endif//__ICCRL78__

#define IMAGE_DATA_SIZE                     (NEW_IMAGE_START_ADDRESS)

#define EXT_MEM_IMAGE_START_ADDRESS         (NEW_IMAGE_START_ADDRESS)
#define EXT_MEM_IMAGE_END_ADDRESS           (NEW_IMAGE_START_ADDRESS + DEVICE_FLASH_ROM_SIZE - 1)
#define EXT_MEM_FREE_START_ADDRESS          (NEW_IMAGE_START_ADDRESS + DEVICE_FLASH_ROM_SIZE)
#define EXT_MEM_FREE_END_ADDRESS            (SFL_DEVICE_PHYSICAL_SIZE - 1)

/*
 * Image operation configuration
*/
#define BL_MAX_IMAGE_RESTORE                (1)

/* TransferUserApp operation type */
#define BL_TRANSFER_USER_APP_TYPE_VERIFY_ONLY                       (1)
#define BL_TRANSFER_USER_APP_TYPE_VERIFY_AND_FLASH                  (2)

/* Result code of TransferUserApp */
#define BL_TRANSFER_USER_APP_RESULT_OK                              (0)
#define BL_TRANSFER_USER_APP_RESULT_ERROR_HASH_UNMATCHED            (1)
#define BL_TRANSFER_USER_APP_RESULT_ERROR_FLASH_ERASE_FAILURE       (2)
#define BL_TRANSFER_USER_APP_RESULT_ERROR_FLASH_WRITE_FAILURE       (3)
#define BL_TRANSFER_USER_APP_RESULT_ERROR_ADDRESS_OUT_RANGE         (4)
#define BL_TRANSFER_USER_APP_RESULT_ERROR_INVALID_ARGUMENT          (5)

/*
 * Function-like helper macro
*/
#define DEVICE_RESTART_INSTRUCTION()        {WDTE = 0x00;}
#define R_WDT_Restart()                     {WDTE = 0xACU;}

#if 0
#define FLASH_CPU_SWITCH_MAX_SPEED()        {\
                                                BL_R_CGC_OperateAtClock24M();\
                                                FLMWEN = 1U;\
                                                SET_BIT(FLMODE, 6, 1U);\
                                                FLMWEN = 0U;\
                                                MCU_Delay(50);\
                                            }
#define FLASH_CPU_SWITCH_MIN_SPEED()        {\
                                                BL_R_CGC_OperateAtClock6M();\
                                                FLMWEN = 1U;\
                                                SET_BIT(FLMODE, 6, 0U);\
                                                FLMWEN = 0U;\
                                                MCU_Delay(50);\
                                            }
#else
#define FLASH_CPU_SWITCH_MAX_SPEED()        {;}
#define FLASH_CPU_SWITCH_MIN_SPEED()        {;}
#endif

#define IS_ENOUGH_POWER_FOR_FLASH()         (LVDVDDF == 0)

/***********************************************************************************************************************
Typedef definitions (required defined macro)
***********************************************************************************************************************/

/* 
 * Internal macro (used for this typedef below only)
*/

/* Helper macro to get the position in information structure of confirmation code and used as index */
#define BL_GET_OFFSET_REQUEST_CODE(element)     (\
                                                    (   offsetof(BL_INFORMATION, request) + \
                                                        offsetof(BL_REQUEST, element) \
                                                    ) / \
                                                    sizeof(bl_confirm_code_t)\
                                                )
                                                
#define BL_GET_OFFSET_PROGRESS_CODE(element)    (\
                                                    (   offsetof(BL_INFORMATION, progress) + \
                                                        offsetof(BL_PROGRESS, element) \
                                                    ) / \
                                                    sizeof(bl_confirm_code_t)\
                                                )
typedef enum tagCodeIndex
{
    REQUEST_RECOVERY_MODE               = BL_GET_OFFSET_REQUEST_CODE(recovery_mode),
    REQUEST_SOFTWARE_RESET              = BL_GET_OFFSET_REQUEST_CODE(software_reset),
    REQUEST_ACTIVATE_IMAGE              = BL_GET_OFFSET_REQUEST_CODE(activate_image),
    REQUEST_BACKUP_IMAGE                = BL_GET_OFFSET_REQUEST_CODE(backup_image),
    REQUEST_RESTORE_IMAGE               = BL_GET_OFFSET_REQUEST_CODE(restore_image),
    
    PROGRESS_BACKINGUP_USER_APP         = BL_GET_OFFSET_PROGRESS_CODE(backingup_user_app_from_ROM),
    PROGRESS_ERASING_USER_APP           = BL_GET_OFFSET_PROGRESS_CODE(erasing_user_app_in_ROM),
    PROGRESS_TRANSFERING_NEW_USER_APP   = BL_GET_OFFSET_PROGRESS_CODE(transferring_new_user_app_to_ROM),
    PROGRESS_RESTORING_BACKUP_USER_APP  = BL_GET_OFFSET_PROGRESS_CODE(restoring_user_app_to_ROM),
    
} bl_code_index;

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/
extern INT_HANDLER RAM_ISR_Table[NUMBER_OF_ISR];
extern BL_INFORMATION g_bl_info;
extern bl_startup_status g_bl_startup_status;
extern uint8_t g_bl_image_read_ROM_buffer[];

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/
/* OPERATION function */
uint8_t BL_OPERATION_ReadConfirmCode(bl_code_index type);
void BL_OPERATION_ClearConfirmCode(bl_code_index type);
void BL_OPERATION_SetConfirmCode(bl_code_index type);

/* Custom memcmp and memcpy */
int16_t BL_memcmp_nn(const void NEAR_PTR * s1, const void NEAR_PTR * s2, uint16_t size);
void BL_memcpy_nf(void NEAR_PTR * dest, const void FAR_PTR * src, uint16_t size);
void BL_memcpy_nn(void NEAR_PTR * dest, const void NEAR_PTR * src, uint16_t size);

/* RECOVERY module */
void BL_RECOVERY_Init(void);
void BL_RECOVERY_Processing(void);

void BL_RECOVERY_UartSendEndCallBack(void);
void BL_RECOVERY_UartReceivedEndCallBack(uint8_t receive_data);
void BL_RECOVERY_TimerEndCallBack(void);

/* FLASH operation */
uint8_t BL_FLASH_WriteBlock(uint32_t addr, uint8_t * buffer);
uint8_t BL_FLASH_EraseBlock(uint16_t block_no);

/* IMAGE processing */
uint8_t BL_IMAGE_EraseUserAppInROM(void);
void BL_IMAGE_Processing(void);
uint8_t BL_IMAGE_TransferUserAppToROM(uint8_t type);
void BL_IMAGE_EraseImageInSerialFlash(uint8_t is_new);

/* HASHING module */
void BL_HASHING_Init(void);
void BL_HASHING_Calculate(uint8_t NEAR_PTR * buffer, uint16_t size);
void BL_HASHING_GetResult(bl_hashing_data NEAR_PTR * hdat);

/* Callbacks for SPI Serial Flash: CSI send/receive */
void SFL_SendEndCallback(void);
void SFL_ReceiveEndCallback(void);

#endif /* __BL_HEADER_H */
