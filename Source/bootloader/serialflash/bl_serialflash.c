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
* File Name    : bl_serialflash.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : 
* Description  : SerialFlash MW Layer APIs
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Driver */
#include "bl_r_cg_macrodriver.h"        /* MD Macro Driver */

/* Code Standard */
#include "typedef.h"                    /* GSCE Standard Typedef */

/* General header */
#include "bl_header.h"

/* Wrapper */
#include "bl_wrp_mcu.h"
#include "bl_wrp_user_spi.h"            /* Wrapper/User SPI */

/* Application */
#include "bl_serialflash.h"             /* SerialFlash MW Layer */

#ifdef __CCRL__

#pragma section text SFLTx

#endif

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef union 
{
    uint8_t byte;
    struct
    {
        uint8_t write_in_progess    : 1;        /* If 1, the device still busy with internal writing */
        uint8_t write_enable_latch  : 1;        /* If 1, the device memory is write enabled (WREN issued) */
        uint8_t block_protection_0  : 1;        
        uint8_t block_protection_1  : 1;        
        uint8_t block_protection_2  : 1;        
        uint8_t block_protection_3  : 1;        
        uint8_t write_AAI_mode      : 1;        
        uint8_t write_protect_status: 1;        /* If 1, the device memory is write protected */
    } details;
    
} SFL_STATUS;

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Common serial communication line interface */ 
#define SFL_DEVICE_HOLD_DISABLE_STATEMENT   {;}                                     /* Command or interface to disable Hold */
#define SFL_DEVICE_HOLD_ENABLE_STATEMENT    {;}                                     /* Command or interface to enable Hold */
#define SFL_DEVICE_DESELECT_STATEMENT       {P5_bit.no0 = 1;}               	/* Command or interface to deselect device */
#define SFL_DEVICE_SELECT_STATEMENT         {P5_bit.no0 = 0;}                	/* Command or interface to select device */
#define SFL_DEVICE_WP_DISABLE_STATEMENT     {;}                                     /* Command or interface to disable WP device */
#define SFL_DEVICE_WP_ENABLE_STATEMENT      {;}                                     /* Command or interface to disable WP device */
#define SFL_DEVICE_READ_STATUS_PIN          (BIT_SELECT(P8, 4))                     /* Command or interface to read the status on MISO pin */

/*
 * Delay Specification for SerialFlash
 * If the SerialFlash is totally different, please consider to change these
 * below information.
 *
 * Normally, these information can be reused.
 */
#define SFL_1BYTE_TIMEOUT                   (40000.0f / SFL_BUS_SPEED)                                  /* 1 byte timeout (ms) for read/write */
#define SFL_SEND_ADDR_MAX_TIMEOUT           ((uint32_t)(SFL_1BYTE_TIMEOUT * 3))                         /* 2 byte addr + 1 offset */
#define SFL_READ_MAX_TIMEOUT                ((uint32_t)(SFL_1BYTE_TIMEOUT * (SFL_DEVICE_PHYSICAL_SIZE+1)))      /* Device size + 1 offset */
#define SFL_WRITE_MAX_TIMEOUT               ((uint32_t)(SFL_1BYTE_TIMEOUT * (SFL_DEVICE_PAGESIZE+1)))   /* Page bytes + 1 offset */

/* 
 * Instruction definition
*/
#define SPI_SERIALFLASH_INSTRUCTION_WREN            (0x06)  /* 0000 0110 Write Enable               */
#define SPI_SERIALFLASH_INSTRUCTION_WRDI            (0x04)  /* 0000 0100 Write Disable              */
#define SPI_SERIALFLASH_INSTRUCTION_RDSR            (0x05)  /* 0000 0101 Read Status Register       */
#define SPI_SERIALFLASH_INSTRUCTION_EWSR            (0x50)  /* 0000 0101 Enable Write Status Register       */
#define SPI_SERIALFLASH_INSTRUCTION_WRSR            (0x01)  /* 0000 0001 Write Status Register      */
#define SPI_SERIALFLASH_INSTRUCTION_READ            (0x03)  /* 0000 0011 Read from Memory Array     */
#define SPI_SERIALFLASH_INSTRUCTION_WRITE           (0x02)  /* 0000 0010 Write byte to Memory Array */
#define SPI_SERIALFLASH_INSTRUCTION_WRITE_AAI       (0xAD)  /* 1010 1101 Write word to Memory Array */
#define SPI_SERIALFLASH_INSTRUCTION_BLK4K_ERASE     (0x20)  /* 0010 0000 Erase block 4k             */
#define SPI_SERIALFLASH_INSTRUCTION_BLK64K_ERASE    (0xD8)  /* 1101 1000 Erase block 64k             */
#define SPI_SERIALFLASH_INSTRUCTION_CHIP_ERASE      (0xC7)  /* 1100 0111 Erase whole chip           */
#define SPI_SERIALFLASH_INSTRUCTION_EBSY            (0x70)  /* 0111 0000 Enable SO ouput RY/BY# status during AAI */
#define SPI_SERIALFLASH_INSTRUCTION_DBSY            (0x80)  /* 1000 0000 Disable SO ouput RY/BY# status during AAI */

#define SERIALFLASH_CHECK_AAI_USING_HARDWARE        (1)

/* Do not edit here */
#define SERIALFLASH_HARDWARE_READY                  (1)
#define SERIALFLASH_HARDWARE_BUSY                   (0)

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
#ifdef __CCRL__

#pragma section bss BLBss
#pragma section data BLData

#endif

static uint8_t g_is_send_end    = 0;
static uint8_t g_is_receive_end = 0;

static uint8_t SFL_WaitForBus(uint16_t bytes);
static uint8_t SFL_WaitForWrite(uint32_t time_us);
static uint8_t SFL_DeviceWriteEnable(void);
static uint8_t SFL_DeviceWriteDisable(void);
static uint8_t SFL_DevicePinBusyStatusEnable(void);
static uint8_t SFL_DevicePinBusyStatusDisable(void);
static uint8_t SFL_DeviceReadStatusRegister(SFL_STATUS * status_reg);
static uint8_t SFL_DeviceWriteStatusRegister(SFL_STATUS status_reg);
static uint8_t SFL_DeviceByteProgramming(uint32_t addr, uint8_t byte);
static uint8_t SFL_DeviceAAIWordProgramming(uint32_t addr, uint8_t * buf, uint32_t size);

/***********************************************************************************************************************
* Function Name: void SFL_ClearFlagWaitBus(void)
* Description  : Clear flag and wait for bus transfer
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void SFL_ClearFlagWaitBus(void)
{
    /* Clear flag to wait bus ack */
    g_is_receive_end = 0;
    g_is_send_end = 0;
}

/***********************************************************************************************************************
* Function Name: static uint8_t SFL_WaitForBus(uint16_t bytes)
* Description  : Wait for bus to finish transfer
* Arguments    : uint16_t bytes: number of transfer byte
* Return Value : uint8_t: Execution status
*              :    SFL_OK                  Normal end
*              :    SFL_ERROR_NO_RESPOND    Expected size and address are not suitable
***********************************************************************************************************************/
static uint8_t SFL_WaitForBus(uint16_t bytes)
{
    uint32_t timeout;
    
    /* Formula: (for SPI bus)
    * 1byte require 8 transfer clock
    * timeout (us) = (8 * 1,000,000/SFL_BUS_SPEED) * bytes
    * Instead calculate per length, this timeout pre-calculate for worst time waiting
    * This is to save ROM size for division function
    */
    timeout = (uint32_t)( ((8 * 1000000) / SFL_BUS_SPEED)*65535 );
    
    while (g_is_send_end == 0 || g_is_receive_end == 0)
    {
        MCU_Delay(1);
        
        timeout--;
        if (timeout == 0)
        {
            return SFL_ERROR_NO_RESPOND;
        }
    }
    
    return SFL_OK;
}

/***********************************************************************************************************************
* Function Name: static uint8_t SFL_WaitForWrite(uint32_t time_us)
* Description  : Wait for internal write process in serial flash until either
*              :    . write_in_progess become 0 (read from device status register)
*              :    . or timeout
* Arguments    : uint32_t: time in us
* Return Value : uint8_t: Execution status
*              :    SFL_OK                  Normal end
*              :    SFL_ERROR_NO_RESPOND    Expected size and address are not suitable
***********************************************************************************************************************/
static uint8_t SFL_WaitForWrite(uint32_t time_us)
{
    uint32_t timeout, i;
    SFL_STATUS status;
    
    timeout = time_us / 10;
    
    for (i=0; i< timeout; i++)
    {
        /* Delay between status polling */
        MCU_Delay(10);
        
        /* If device idle, break wait loop */
        SFL_DeviceReadStatusRegister(&status);
        if (status.details.write_in_progess == 0)
        {
            return SFL_OK;
        }
        
        R_WDT_Restart();
    }
    
    return SFL_ERROR_NO_RESPOND;
}

/***********************************************************************************************************************
* Function Name: static uint8_t SFL_DeviceWriteEnable(void)
* Description  : Enable device write latch
* Arguments    : None
* Return Value : uint8_t: Execution status
*              :    SFL_OK                  Normal end
*              :    SFL_ERROR_NO_RESPOND    Expected size and address are not suitable
***********************************************************************************************************************/
static uint8_t SFL_DeviceWriteEnable(void)
{
    uint8_t local_buf[1];
    
    SFL_ClearFlagWaitBus();
    
    local_buf[0] = SPI_SERIALFLASH_INSTRUCTION_WREN;
    SFL_DEVICE_SELECT_STATEMENT;
    WRP_SPI_SendReceive(local_buf, 1, local_buf);
    if (SFL_WaitForBus(1) != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
    SFL_DEVICE_DESELECT_STATEMENT;
    
    return SFL_OK;
}

/***********************************************************************************************************************
* Function Name: static uint8_t SFL_DeviceWriteDisable(void)
* Description  : Disable device write latch
* Arguments    : None
* Return Value : uint8_t: Execution status
*              :    SFL_OK                  Normal end
*              :    SFL_ERROR_NO_RESPOND    Expected size and address are not suitable
***********************************************************************************************************************/
static uint8_t SFL_DeviceWriteDisable(void)
{
    uint8_t local_buf[1];
    
    SFL_ClearFlagWaitBus();
    
    local_buf[0] = SPI_SERIALFLASH_INSTRUCTION_WRDI;
    SFL_DEVICE_SELECT_STATEMENT;
    WRP_SPI_SendReceive(local_buf, 1, local_buf);
    if (SFL_WaitForBus(1) != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
    SFL_DEVICE_DESELECT_STATEMENT;
    
    return SFL_OK;
}

/***********************************************************************************************************************
* Function Name: static uint8_t SFL_DevicePinBusyStatusEnable(void)
* Description  : Enable busy status output on device SO pin
* Arguments    : None
* Return Value : uint8_t: Execution status
*              :    SFL_OK                  Normal end
*              :    SFL_ERROR_NO_RESPOND    Expected size and address are not suitable
***********************************************************************************************************************/
static uint8_t SFL_DevicePinBusyStatusEnable(void)
{
    uint8_t local_buf[1];
    
    SFL_ClearFlagWaitBus();
    local_buf[0] = SPI_SERIALFLASH_INSTRUCTION_EBSY;
    
    SFL_DEVICE_SELECT_STATEMENT;
    WRP_SPI_SendReceive(local_buf, 1, local_buf);
    if (SFL_WaitForBus(1) != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
    /* Set CS high to deselect device */
    SFL_DEVICE_DESELECT_STATEMENT;
    
    return SFL_OK;
}

/***********************************************************************************************************************
* Function Name: static uint8_t SFL_DevicePinBusyStatusDisable(void)
* Description  : Disable busy status output on device SO pin
* Arguments    : None
* Return Value : uint8_t: Execution status
*              :    SFL_OK                  Normal end
*              :    SFL_ERROR_NO_RESPOND    Expected size and address are not suitable
***********************************************************************************************************************/
static uint8_t SFL_DevicePinBusyStatusDisable(void)
{
    uint8_t local_buf[1];
    
    SFL_ClearFlagWaitBus();
    local_buf[0] = SPI_SERIALFLASH_INSTRUCTION_DBSY;
    
    SFL_DEVICE_SELECT_STATEMENT;
    WRP_SPI_SendReceive(local_buf, 1, local_buf);
    if (SFL_WaitForBus(1) != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
    /* Set CS high to deselect device */
    SFL_DEVICE_DESELECT_STATEMENT;
    
    return SFL_OK;
}

/***********************************************************************************************************************
* Function Name: static uint8_t SFL_DeviceReadStatusRegister(SFL_STATUS * status_reg)
* Description  : SerialFlash Read device status register
* Arguments    : Read back status store in global register
* Return Value : uint8_t: Execution status
*              :    SFL_OK                  Normal end
*              :    SFL_ERROR_NO_RESPOND    Expected size and address are not suitable
***********************************************************************************************************************/
static uint8_t SFL_DeviceReadStatusRegister(SFL_STATUS * status_reg)
{
    uint8_t local_buf[2];
    
    SFL_ClearFlagWaitBus();
    
    local_buf[0] = SPI_SERIALFLASH_INSTRUCTION_RDSR;
    local_buf[1] = 0x00;
    SFL_DEVICE_SELECT_STATEMENT;
    WRP_SPI_SendReceive(local_buf, 2, local_buf);
    if (SFL_WaitForBus(2) != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
    SFL_DEVICE_DESELECT_STATEMENT;
    
    status_reg->byte = local_buf[1];
    
    return SFL_OK;
}

/***********************************************************************************************************************
* Function Name: static uint8_t SFL_DeviceWriteStatusRegister(uint8_t status_reg)
* Description  : SerialFlash Write device status register
* Arguments    : uint8_t value
* Return Value : uint8_t: Execution status
*              :    SFL_OK                  Normal end
*              :    SFL_ERROR_NO_RESPOND    Expected size and address are not suitable
***********************************************************************************************************************/
static uint8_t SFL_DeviceWriteStatusRegister(SFL_STATUS status_reg)
{
    uint8_t local_buf[2];
    
    /* Enable write to status register */
    SFL_ClearFlagWaitBus();
    
    local_buf[0] = SPI_SERIALFLASH_INSTRUCTION_EWSR;
    SFL_DEVICE_SELECT_STATEMENT;
    WRP_SPI_SendReceive(local_buf, 1, local_buf);
    if (SFL_WaitForBus(1) != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
    SFL_DEVICE_DESELECT_STATEMENT;
    
    /* Write to status register */
    SFL_ClearFlagWaitBus();
    
    local_buf[0] = SPI_SERIALFLASH_INSTRUCTION_WRSR;
    local_buf[1] = status_reg.byte;
    SFL_DEVICE_SELECT_STATEMENT;
    WRP_SPI_SendReceive(local_buf, 2, local_buf);
    if (SFL_WaitForBus(2) != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
    SFL_DEVICE_DESELECT_STATEMENT;
    
    /* Wait for internal operation */
    if (SFL_WaitForWrite(SFL_DEVICE_WRITE_STATUS_TIME) != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
    
    return SFL_OK;
}

/******************************************************************************
* Function Name: static uint8_t SFL_DeviceByteProgramming(uint32_t addr, uint8_t byte)
* Description  : Programming single byte
* Arguments    : addr: Local address in SerialFlash
*              : byte : Byte to program
* Return Value : uint8_t: Execution status
*              :    SFL_OK                  Normal end
*              :    SFL_ERROR_NO_RESPOND    Expected size and address are not suitable
******************************************************************************/
static uint8_t SFL_DeviceByteProgramming(uint32_t addr, uint8_t byte)
{
    uint8_t local_buf[5];
    
    /* Write Enable */
    if (SFL_DeviceWriteEnable() != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
    
    /* Write a byte */
    SFL_ClearFlagWaitBus();
    
    local_buf[0] = SPI_SERIALFLASH_INSTRUCTION_WRITE;
    local_buf[1] = (uint8_t)(addr >> 16);
    local_buf[2] = (uint8_t)(addr >> 8);
    local_buf[3] = (uint8_t)(addr);
    local_buf[4] = byte;
    
    SFL_DEVICE_SELECT_STATEMENT;
    WRP_SPI_SendReceive(local_buf, 5, local_buf);
    if (SFL_WaitForBus(5) != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
    SFL_DEVICE_DESELECT_STATEMENT;
    
    /* Wait for internal operation */
    if (SFL_WaitForWrite(SFL_DEVICE_BYTE_PROGRAM_TIME) != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
    
    return SFL_OK;
}

/******************************************************************************
* Function Name: static uint8_t SFL_DeviceAAIWordProgramming(uint32_t addr, uint8_t * buf, uint32_t size)
* Description  : Programming using AAI word programming instruction
* Arguments    : addr: Local address in SerialFlash
*              : buf : Buffer to store the result
*              : size: Expected size want to read
* Return Value : uint8_t: Execution status
*              :    SFL_OK                  Normal end
*              :    SFL_ERROR_NO_RESPOND    Expected size and address are not suitable
******************************************************************************/
static uint8_t SFL_DeviceAAIWordProgramming(uint32_t addr, uint8_t * buf, uint32_t size)
{
    uint8_t local_buf[6];
    uint8_t first_aai = 1;
    uint8_t send_size;
    uint32_t delay_count;
        
    /* Odd address */
    if (((uint8_t)(*((uint8_t *)&addr)) % 2) != 0)
    {
        /* Send first byte */
        if (SFL_DeviceByteProgramming(addr, *buf) != SFL_OK)
        {
            return SFL_ERROR_NO_RESPOND;
        }
        
        /* Next data */
        addr++;
        buf++;
        size--;
    }
    
    #if (SERIALFLASH_CHECK_AAI_USING_HARDWARE == 1)
    /* Enable SO as busy indication */
    if (SFL_DevicePinBusyStatusEnable() != SFL_OK)
    {
        return SFL_ERROR;
    }
    #endif /* SERIALFLASH_CHECK_AAI_USING_HARDWARE */
    
    /* Write enable */
    SFL_DeviceWriteEnable();
    
    /* 
     * Write AAI sequence 
    */
    while(size > 1)
    {
        local_buf[0] = SPI_SERIALFLASH_INSTRUCTION_WRITE_AAI;
        
        /* Prepare buffer */
        SFL_ClearFlagWaitBus();
        if (first_aai)
        {
            local_buf[1] = (uint8_t)(addr >> 16);
            local_buf[2] = (uint8_t)(addr >> 8);
            local_buf[3] = (uint8_t)(addr);
            local_buf[4] = *(buf);
            local_buf[5] = *(buf + 1);
            send_size = 6;
            first_aai = 0;
        }
        else
        {
            local_buf[1] = *(buf);
            local_buf[2] = *(buf + 1);
            send_size = 3;
        }
        
        SFL_DEVICE_SELECT_STATEMENT;
        WRP_SPI_SendReceive(local_buf, send_size, local_buf);
        if (SFL_WaitForBus(send_size) != SFL_OK)
        {
            return SFL_ERROR_NO_RESPOND;
        }
        /* Set CS high to deselect device */
        SFL_DEVICE_DESELECT_STATEMENT;
    
        /* Next data */
        addr += 2;
        buf += 2;
        size -= 2;
        
        #if (SERIALFLASH_CHECK_AAI_USING_HARDWARE == 1)
        SFL_DEVICE_SELECT_STATEMENT;
        /* Check using hardware */
        delay_count = 0;
        while(SFL_DEVICE_READ_STATUS_PIN != SERIALFLASH_HARDWARE_READY)
        {
            R_WDT_Restart();
            /* Checking timeout */
            MCU_Delay(1);
            delay_count++;
            if ((delay_count >= 1000000) || (IS_ENOUGH_POWER_FOR_FLASH() == 0))
            {
                return SFL_ERROR_NO_RESPOND;
            }
        }
        SFL_DEVICE_DESELECT_STATEMENT;
        
        #else
        /* Software Polling for busy bit */
        /* Wait for internal operation */
        if (SFL_WaitForWrite(SFL_DEVICE_BYTE_PROGRAM_TIME) != SFL_OK)
        {
            return SFL_ERROR_NO_RESPOND;
        }
        #endif /* SERIALFLASH_CHECK_AAI_USING_HARDWARE */
    }
    
    /* Disable to stop AAI sequence */
    if (SFL_DeviceWriteDisable() != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
        
    #if (SERIALFLASH_CHECK_AAI_USING_HARDWARE == 1)
    /* Disable SO as busy indication */
    if (SFL_DevicePinBusyStatusDisable() != SFL_OK)
    {
        return SFL_ERROR;
    }
        
    #ifdef __DEBUG
    {
        SFL_STATUS status;
            
        if (SFL_DeviceReadStatusRegister(&status) != SFL_OK)
        {
            return SFL_ERROR;                
        }
    }
    #endif /* __DEBUG */
        
    #endif /* SERIALFLASH_CHECK_AAI_USING_HARDWARE */
    
    /* Still remaining 1 byte */
    if (size == 1)
    {
        /* Send final byte */
        if (SFL_DeviceByteProgramming(addr, *buf) != SFL_OK)
        {
            return SFL_ERROR_NO_RESPOND;
        }
    }
    
    return SFL_OK;
}

/***********************************************************************************************************************
* Function Name: uint8_t BL_SFL_Init(void)
* Description  : SerialFlash Initialization
* Arguments    : WRP_SPI_Init()
* Return Value : uint8_t, execution status
***********************************************************************************************************************/
#ifdef __ICCRL78__
__root
#endif
uint8_t BL_SFL_Init(void)
{
    SFL_STATUS status;
    
    /* Init SerialFlash device interface mapping */
    WRP_SPI_Init();
    WRP_SPI_Start();
    
    SFL_DEVICE_HOLD_DISABLE_STATEMENT;
    SFL_DEVICE_WP_DISABLE_STATEMENT;
    SFL_DEVICE_DESELECT_STATEMENT;  /* Deselect device as write protected */
    
    /* Terminate any previous AAI operation by WRDI followed by DBSY */
    if (SFL_DeviceWriteDisable() != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
    
    /* Enable the write to check if it set properly */
    if (SFL_DeviceWriteEnable() != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
    
    /* Check if device write enable latch on */
    if (SFL_DeviceReadStatusRegister(&status) != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
    if (status.details.write_enable_latch != 1)
    {
        return SFL_ERROR;
    }
    
    #if (SERIALFLASH_CHECK_AAI_USING_HARDWARE == 1)
    /* Disable SO as busy indication */
    if (SFL_DevicePinBusyStatusDisable() != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
    #endif /* SERIALFLASH_CHECK_AAI_USING_HARDWARE */
        
    /* Disable all block protection */
    status.byte = 0x00;
    if (SFL_DeviceWriteStatusRegister(status) != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
    
    if (SFL_DeviceReadStatusRegister(&status) != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
    
    /* Check device status: */
    if (status.details.write_in_progess != 0 ||
        status.details.write_protect_status != 0 )
    {
        return SFL_ERROR;
    }
    
    return SFL_OK;
}

/***********************************************************************************************************************
* Function Name: uint8_t BL_SFL_Stop(void)
* Description  : SerialFlash stop
* Arguments    : 
* Return Value : uint8_t, execution status
***********************************************************************************************************************/
uint8_t BL_SFL_Stop(void)
{
    WRP_SPI_Stop();
    return SFL_OK;
}

/******************************************************************************
* Function Name: static uint8_t BL_SFL_DeviceErase4KB(uint32_t addr)
* Description  : Erase memory in block 4K
* Arguments    : uint32_t addr: the address of block to be erase
* Return Value : uint8_t: Execution status
*              :    SFL_OK                  Normal end
*              :    SFL_ERROR_NO_RESPOND    Expected size and address are not suitable
******************************************************************************/
uint8_t BL_SFL_DeviceErase4KB(uint32_t addr)
{
    uint8_t local_buf[4];
    
    /* Check input argument */
    if (addr > (SFL_DEVICE_PHYSICAL_SIZE - 1))
    {
        return SFL_ERROR_SIZE;
    }

    /* Write Enable */
    if (SFL_DeviceWriteEnable() != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
        
    /* Erase block */
    SFL_ClearFlagWaitBus();
    
    local_buf[0] = SPI_SERIALFLASH_INSTRUCTION_BLK4K_ERASE;
    local_buf[1] = (uint8_t)(addr >> 16);
    local_buf[2] = (uint8_t)(addr >> 8);
    local_buf[3] = (uint8_t)(addr);
    
    SFL_DEVICE_SELECT_STATEMENT;
    WRP_SPI_SendReceive(local_buf, 4, local_buf);
    if (SFL_WaitForBus(4) != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
    SFL_DEVICE_DESELECT_STATEMENT;
    
    /* Wait for internal operation */
    if (SFL_WaitForWrite(SFL_MAX_MINIMUM_BLOCK_ERASE_TIME) != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
    
    return SFL_OK;
}

/******************************************************************************
* Function Name: static uint8_t BL_SFL_DeviceErase64KB(uint32_t addr)
* Description  : Erase memory in block 64K
* Arguments    : uint32_t addr: the address of block to be erase
* Return Value : uint8_t: Execution status
*              :    SFL_OK                  Normal end
*              :    SFL_ERROR_NO_RESPOND    Expected size and address are not suitable
******************************************************************************/
uint8_t BL_SFL_DeviceErase64KB(uint32_t addr)
{
    uint8_t local_buf[4];
    
    /* Check input argument */
    if (addr > (SFL_DEVICE_PHYSICAL_SIZE - 1))
    {
        return SFL_ERROR_SIZE;
    }

    /* Write Enable */
    if (SFL_DeviceWriteEnable() != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
        
    /* Erase block */
    SFL_ClearFlagWaitBus();
    
    local_buf[0] = SPI_SERIALFLASH_INSTRUCTION_BLK64K_ERASE;
    local_buf[1] = (uint8_t)(addr >> 16);
    local_buf[2] = (uint8_t)(addr >> 8);
    local_buf[3] = (uint8_t)(addr);
    
    SFL_DEVICE_SELECT_STATEMENT;
    WRP_SPI_SendReceive(local_buf, 4, local_buf);
    if (SFL_WaitForBus(4) != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
    SFL_DEVICE_DESELECT_STATEMENT;
    
    /* Wait for internal operation */
    if (SFL_WaitForWrite(SFL_MAX_MINIMUM_BLOCK_ERASE_TIME) != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
    
    return SFL_OK;
}

/******************************************************************************
* Function Name: static uint8_t BL_SFL_DeviceEraseAll(void)
* Description  : Erase whole serial flash device (to 0xFF)
* Arguments    : None
* Return Value : uint8_t: Execution status
*              :    SFL_OK                  Normal end
*              :    SFL_ERROR_NO_RESPOND    Expected size and address are not suitable
******************************************************************************/
uint8_t BL_SFL_DeviceEraseAll(void)
{
    uint8_t local_buf[1];
    
    /* Write Enable */
    if (SFL_DeviceWriteEnable() != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
    
    /* Erase whole chip */
    SFL_ClearFlagWaitBus();
    
    local_buf[0] = SPI_SERIALFLASH_INSTRUCTION_CHIP_ERASE;
    SFL_DEVICE_SELECT_STATEMENT;
    WRP_SPI_SendReceive(local_buf, 1, local_buf);
    if (SFL_WaitForBus(1) != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
    SFL_DEVICE_DESELECT_STATEMENT;
    
    /* Wait for internal operation */
    if (SFL_WaitForWrite(SFL_MAX_CHIP_ERASE_TIME) != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
    
    return SFL_OK;
}

/******************************************************************************
* Function Name: uint8_t BL_SFL_DeviceWriteProtectAll(void)
* Description  : Protect whole memory: disable write and erase operation
* Arguments    : None
* Return Value : uint8_t: Execution status
******************************************************************************/
uint8_t BL_SFL_DeviceWriteProtectAll(void)
{
    SFL_STATUS status;
    
    status.details.block_protection_0 = 1;
    status.details.block_protection_1 = 1;
    status.details.block_protection_2 = 1;
    status.details.block_protection_3 = 1;
    
    return (SFL_DeviceWriteStatusRegister(status));
}

/******************************************************************************
* Function Name: uint8_t BL_SFL_DeviceWriteUnProtectAll(void)
* Description  : Un Protect whole memory: allow write and erase operation 
* Arguments    : None
* Return Value : uint8_t: Execution status
******************************************************************************/
uint8_t BL_SFL_DeviceWriteUnProtectAll(void)
{
    SFL_STATUS status;
    
    status.byte = 0x00;
    
    return (SFL_DeviceWriteStatusRegister(status));
}

/******************************************************************************
* Function Name: uint8_t BL_SFL_DeviceRead(uint32_t addr, uint8_t *buf, uint16_t size)
* Description  : Read to buffer
* Arguments    : addr: Local address in SerialFlash
*              : buf : Buffer to store the result
*              : size: Expected size want to read
* Return Value : uint8_t: Execution status
*              :    SFL_OK                  Normal end
*              :    SFL_ERROR_NO_RESPOND    Expected size and address are not suitable
******************************************************************************/
uint8_t BL_SFL_DeviceRead(uint32_t addr, uint8_t *buf, uint16_t size)
{
    uint8_t local_buf[4];
    
    /* Check input argument */
    if (buf == NULL)
    {
        return SFL_ERROR;
    }

    /* Check for input addr, size */
    if ((size == 0) ||
        (addr + size) > (SFL_DEVICE_PHYSICAL_SIZE))
    {
        return SFL_ERROR_SIZE;
    }

    /* Write a byte */
    SFL_ClearFlagWaitBus();
    
    local_buf[0] = SPI_SERIALFLASH_INSTRUCTION_READ;
    local_buf[1] = (uint8_t)(addr >> 16);
    local_buf[2] = (uint8_t)(addr >> 8);
    local_buf[3] = (uint8_t)(addr);
    
    SFL_DEVICE_SELECT_STATEMENT;
    WRP_SPI_SendReceive(local_buf, 4, local_buf);
    if (SFL_WaitForBus(4) != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
    
    SFL_ClearFlagWaitBus();
    WRP_SPI_SendReceive(buf, size, buf);
    if (SFL_WaitForBus(size) != SFL_OK)
    {
        return SFL_ERROR_NO_RESPOND;
    }
    SFL_DEVICE_DESELECT_STATEMENT;
    
    return SFL_OK;
}

/******************************************************************************
* Function Name: uint8_t BL_SFL_DeviceWrite(uint32_t addr, uint8_t *buf, uint16_t size)
* Description  : Write from buffer to serial flash
* Arguments    : addr: Local address in SerialFlash
*              : buf : Buffer to write
*              : size: Expected size want to read
* Return Value : uint8_t: Execution status
******************************************************************************/
uint8_t BL_SFL_DeviceWrite(uint32_t addr, uint8_t *buf, uint16_t size)
{
    /* Check input argument */
    if (buf == NULL)
    {
        return SFL_ERROR;
    }

    /* Check for input addr, size */
    if ((size == 0) ||
        (addr + size) > (SFL_DEVICE_PHYSICAL_SIZE))
    {
        return SFL_ERROR_SIZE;
    }

    return (SFL_DeviceAAIWordProgramming(addr, buf, size));
}

/* 
 * Area to ignore symnbol output to user application 
*/
#ifdef __CCRL__
#pragma section
#endif

/***********************************************************************************************************************
* Function Name: void SFL_SendEndCallback(void)
* Description  : SerialFlash Send End Callback
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void SFL_SendEndCallback(void)
{
    g_is_send_end = 1;  
}

/***********************************************************************************************************************
* Function Name: void SFL_ReceiveEndCallback(void)
* Description  : SerialFlash Receive End Callback
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void SFL_ReceiveEndCallback(void)
{
    g_is_receive_end = 1;
}
