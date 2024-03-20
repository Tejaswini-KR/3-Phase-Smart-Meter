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
* File Name    : bl_recovery.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : 
* Description  : Recovery mode processing
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Drivers */
#include "bl_r_cg_macrodriver.h"
#include "bl_r_cg_crc.h"
#include "bl_r_cg_sau.h"
#include "bl_r_cg_tau.h"

/* Display module */
#include "bl_display.h"

/* Core functions */
#include "bl_header.h"

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum tagFirmwareState
{
    IDLE,
    FRAME_REQUEST_RECEIVED,
    FRAME_LENGTH_RECEIVED,
    FRAME_DATA_FULL,
    FRAME_DATA_READY,
    
} RECOVERY_UPDATE_STATE;

typedef enum tagFrameType
{
    FRAME_TYPE_EXIT,
    FRAME_TYPE_BLOCK_INFORMATION,
    FRAME_TYPE_BLOCK_TRANSFER,
} RECOVERY_FRAME_TYPE;

typedef enum tagErrorCode
{
    ERROR_CODE_UNKNOW_ERROR = 0x01,
    ERROR_CODE_UNKNOWN_FRAME_TYPE,
    ERROR_CODE_CHECKSUM_NOT_MATCHED,
    ERROR_CODE_WRONG_BLOCK_INDEX,
    ERROR_CODE_WRONG_DATA_LENGTH,
    ERROR_CODE_FLASH_WRITING_ERROR,
    
} RECOVERY_ERROR_CODE;

typedef enum tagAcknowledgeType
{
    ACK_CODE_NORMAL = 0x01,
    ACK_CODE_BLOCK_INFO,
    ACK_CODE_ERROR,
} RECOVERY_ACK_CODE;

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Driver API Mapping */
#define BL_RECOVERY_DriverUartInit()                {;}
#define BL_RECOVERY_DriverUartStart()               {R_UART2_Start();}
#define BL_RECOVERY_DriverUartSend(buffer, length)  {R_UART2_Send(buffer, length);}

#define BL_RECOVERY_DriverTimerInit()               {;}
#define BL_RECOVERY_DriverTimerStart()              {R_TAU0_Channel0_Start();}

#define BL_RECOVERY_BLOCK_SIZE                      (DEVICE_FLASH_BLOCK_SIZE)


/* Bootloader definition */
#define BL_RECOVERY_START_CODE                      (0x7E)  /* ASCII char: (~) */
#define BL_RECOVERY_END_CODE                        (0x23)  /* ASCII char: (#) */

#define BL_RECOVERY_ACK_TYPE_OK                     (0x00)
#define BL_RECOVERY_ACK_TYPE_ERROR_FRAME_INVALID    (0x10)
#define BL_RECOVERY_ACK_TYPE_ERROR_CRC              (0x11)
#define BL_RECOVERY_ACK_TYPE_ERROR_ADDR             (0x12)
#define BL_RECOVERY_ACK_TYPE_ERROR_SIZE             (0x13)
#define BL_RECOVERY_ACK_TYPE_ERROR_INTERNAL         (0x14)

#define BL_RECOVERY_FRAME_LENGTH_NUM_OF_BYTES       (0x02)
#define BL_RECOVERY_FRAME_TYPE_NUM_OF_BYTES         (0x01)
#define BL_RECOVERY_FRAME_CHECKSUM_NUM_OF_BYTES     (0x02)
#define BL_RECOVERY_FRAME_BLOCK_INDEX_NUM_OF_BYTES  (0x02)

/* Specify the timeout duration (in multiple of 0.5s) */
#define BL_RECOVERY_TIMEOUT_COUNT_IDLE_MODE         (60)
#define BL_RECOVERY_TIMEOUT_COUNT_DATA_MODE         (4)

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
uint8_t g_bl_recovery_data_buffer[BL_RECOVERY_BLOCK_SIZE + 32];
uint16_t g_bl_recovery_frame_length;
uint16_t g_bl_recovery_receive_count;
RECOVERY_ERROR_CODE g_bl_recovery_response_error_code;

uint8_t g_bl_recovery_is_key_press;
uint8_t g_bl_recovery_is_mode_timeout;
uint8_t g_bl_recovery_is_mode_finish;
uint8_t g_bl_recovery_is_processing;

uint8_t g_bl_recovery_is_sent;

RECOVERY_UPDATE_STATE g_bl_recovery_opr_state;
uint16_t g_bl_recovery_timeout_counter = 0;

/***********************************************************************************************************************
Macro definitions use private variables or related to
***********************************************************************************************************************/
#define IS_RECOVERY_MODE_HARDWARE_REQUESTED(status)     {status = 0;}
#define IS_RECOVERY_MODE_SOFTWARE_REQUESTED(status)     {\
                                                            status |= BL_OPERATION_ReadConfirmCode(REQUEST_RECOVERY_MODE);\
                                                        }


/***********************************************************************************************************************
* Function Name: void BL_RECOVERY_Init(void)
* Description  : Init the Recovery module
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void BL_RECOVERY_Init(void)
{
    BL_RECOVERY_DriverUartInit();
    BL_RECOVERY_DriverUartStart();
    
    BL_RECOVERY_DriverTimerInit();
    BL_RECOVERY_DriverTimerStart();
    
    g_bl_recovery_opr_state = IDLE;
}

/***********************************************************************************************************************
* Function Name: void BL_RECOVERY_SendFrameAck(RECOVERY_ACK_CODE ack_type)
* Description  : Send the ack information to PC
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void BL_RECOVERY_SendFrameAck(RECOVERY_ACK_CODE ack_type)
{
    uint8_t data[3];
    uint8_t size;
    
    data[0] = ack_type;
    
    switch (ack_type)
    {
        case ACK_CODE_NORMAL:
            size = 1;
            break;
        case ACK_CODE_BLOCK_INFO:
            data[1] = (uint8_t)(BL_RECOVERY_BLOCK_SIZE & 0x00FF);
            data[2] = (uint8_t)((BL_RECOVERY_BLOCK_SIZE >> 8) & 0x00FF);
            size = 3;
            break;
        case ACK_CODE_ERROR:
            data[1] = g_bl_recovery_response_error_code;
            size = 2;
            break;
        default:
            size = 0;
            break;
    }
    
    /* Send acknowledgement */
    if (size != 0)
    {
        g_bl_recovery_is_sent = 0;
        BL_RECOVERY_DriverUartSend(data, size);
        
        while (g_bl_recovery_is_sent == 0);
        R_WDT_Restart();
    }
}

/***********************************************************************************************************************
* Function Name: void BL_RECOVERY_PollingProcessing()
* Description  : Polling processing in recovery mode
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void BL_RECOVERY_PollingProcessing(void)
{
    switch (g_bl_recovery_opr_state)
    {
        case IDLE:
        case FRAME_REQUEST_RECEIVED:
        case FRAME_LENGTH_RECEIVED:
        case FRAME_DATA_FULL:
            /* Do nothing */
            break;
        case FRAME_DATA_READY:
        {
            uint16_t frame_embedded_crc;
            uint16_t frame_calculated_crc;
            uint16_t block_no;
            RECOVERY_FRAME_TYPE frame_type;
            uint16_t frame_length;
            uint16_t data_length;
            RECOVERY_ACK_CODE ack_type;
            uint8_t * p_data;
            
            /* Get information from frame */
            *((uint8_t *)&frame_length + 0) = g_bl_recovery_data_buffer[0];
            *((uint8_t *)&frame_length + 1) = g_bl_recovery_data_buffer[1];
            data_length = frame_length - 3;
            
            frame_type = (RECOVERY_FRAME_TYPE)g_bl_recovery_data_buffer[2];
            
            *((uint8_t *)&frame_embedded_crc + 0) = g_bl_recovery_data_buffer[frame_length+BL_RECOVERY_FRAME_CHECKSUM_NUM_OF_BYTES-2];
            *((uint8_t *)&frame_embedded_crc + 1) = g_bl_recovery_data_buffer[frame_length+BL_RECOVERY_FRAME_CHECKSUM_NUM_OF_BYTES-1];
            
            /* Check the frame CRC16 */
            R_CRC_Set(0xFFFF);
            R_CRC_Calculate(g_bl_recovery_data_buffer, frame_length +
                                                       BL_RECOVERY_FRAME_LENGTH_NUM_OF_BYTES - 
                                                       BL_RECOVERY_FRAME_CHECKSUM_NUM_OF_BYTES);
            frame_calculated_crc = R_CRC_GetResult() ^ 0xFFFF;
            
            if (frame_embedded_crc != frame_calculated_crc)
            {
                /* Discard frame, no action */
                ack_type = ACK_CODE_ERROR;
                g_bl_recovery_response_error_code = ERROR_CODE_CHECKSUM_NOT_MATCHED;
            }
            else
            {
                /* Frame CRC ok, now check what frame type */
                if (frame_type == FRAME_TYPE_EXIT)
                {
                    /* Raise signal to exit recovery mode */
                    g_bl_recovery_is_mode_finish = 1;
                    ack_type = ACK_CODE_NORMAL;
                }
                else if (frame_type == FRAME_TYPE_BLOCK_INFORMATION)
                {
                    ack_type = ACK_CODE_BLOCK_INFO;
                }
                else if (frame_type == FRAME_TYPE_BLOCK_TRANSFER)
                {
                    /* Get block_no: 2 bytes */
                    *((uint8_t *)&block_no + 0) = g_bl_recovery_data_buffer[3];
                    *((uint8_t *)&block_no + 1) = g_bl_recovery_data_buffer[4];
                    
                    /* Is valid block number? */
                    if (block_no < ( USER_APP_NEAR_START_ADDRESS / DEVICE_FLASH_BLOCK_SIZE) ||
                        block_no > ((DEVICE_FLASH_ROM_SIZE) / DEVICE_FLASH_BLOCK_SIZE) - 1)
                    {
                        /* Discard frame, no action */
                        ack_type = ACK_CODE_ERROR;
                        g_bl_recovery_response_error_code = ERROR_CODE_WRONG_BLOCK_INDEX;
                    }
                    /* Check for data length */
                    else if ((data_length - BL_RECOVERY_FRAME_BLOCK_INDEX_NUM_OF_BYTES) != BL_RECOVERY_BLOCK_SIZE)
                    {
                        /* Discard frame, no action */
                        ack_type = ACK_CODE_ERROR;
                        g_bl_recovery_response_error_code = ERROR_CODE_WRONG_DATA_LENGTH;
                    }
                    else
                    {
                        uint8_t flash_result = 0;
                        /* Frame ok, write the block data to flash */
                        p_data = &g_bl_recovery_data_buffer[5];
                        
                        flash_result = BL_FLASH_EraseBlock(block_no);
                        flash_result |= BL_FLASH_WriteBlock((uint32_t)block_no * BL_RECOVERY_BLOCK_SIZE, p_data);
                        
                        if (flash_result != 0)
                        {
                            /* Discard frame */
                            ack_type = ACK_CODE_ERROR;
                            g_bl_recovery_response_error_code = ERROR_CODE_FLASH_WRITING_ERROR;
                        }
                        else
                        {
                            ack_type = ACK_CODE_NORMAL;
                        }
                    }
                }
                else
                {
                    /* Discard frame, no action */
                    ack_type = ACK_CODE_ERROR;
                    g_bl_recovery_response_error_code = ERROR_CODE_UNKNOWN_FRAME_TYPE;
                }
            }
            
            /* Send acknowledgement to PC */
            BL_RECOVERY_SendFrameAck(ack_type);
            
            /* Reset operation state */
            g_bl_recovery_opr_state = IDLE;
            
            break;
        }
        /* No processing in case other state */
        default:
            break;
    }
}

/******************************************************************************
* Function Name: void BL_RECOVERY_UartSendEndCallBack(void)
* Description  : Assign this to UART driver send end interrupt
* Arguments    : None
* Return Value : None
******************************************************************************/
void BL_RECOVERY_UartSendEndCallBack(void)
{
    g_bl_recovery_is_sent = 1;
}

/******************************************************************************
* Function Name: void BL_RECOVERY_UartReceivedEndCallBack(void)
* Description  : Assign this to UART driver receive end interrupt
* Arguments    : None
* Return Value : None
******************************************************************************/
void BL_RECOVERY_UartReceivedEndCallBack(uint8_t receive_data)
{
    switch (g_bl_recovery_opr_state)
    {
        case IDLE:
            if (receive_data == BL_RECOVERY_START_CODE)
            {
                g_bl_recovery_receive_count = 0;
                g_bl_recovery_opr_state = FRAME_REQUEST_RECEIVED;
            }
            break;
        case FRAME_REQUEST_RECEIVED:
            /* Get the frame length information */
            g_bl_recovery_data_buffer[g_bl_recovery_receive_count] = receive_data;
            g_bl_recovery_receive_count++;
            
            if (g_bl_recovery_receive_count >= 2)
            {
                *((uint8_t *)&g_bl_recovery_frame_length) = g_bl_recovery_data_buffer[0];
                *(((uint8_t *)&g_bl_recovery_frame_length) + 1) = g_bl_recovery_data_buffer[1];
                g_bl_recovery_receive_count = 0;
                g_bl_recovery_opr_state = FRAME_LENGTH_RECEIVED;
            }
            
            break;
            
        case FRAME_LENGTH_RECEIVED:
            if (g_bl_recovery_receive_count < g_bl_recovery_frame_length)
            {
                g_bl_recovery_data_buffer[g_bl_recovery_receive_count + 2] = receive_data;
                g_bl_recovery_receive_count++;
                
                if (g_bl_recovery_receive_count >= g_bl_recovery_frame_length)
                {
                    g_bl_recovery_opr_state = FRAME_DATA_FULL;
                    g_bl_recovery_receive_count = 0;
                }
            }
            break;
            
        case FRAME_DATA_FULL:
            /* Perform quick checking */
            if (receive_data != BL_RECOVERY_END_CODE)
            {
                /* Discard frame */
                g_bl_recovery_opr_state = IDLE;
            }
            else
            {
                g_bl_recovery_opr_state = FRAME_DATA_READY;
                g_bl_recovery_timeout_counter = 0;
            }
            break;
        default:
            g_bl_recovery_opr_state = IDLE;
            break;
    }
}

/******************************************************************************
* Function Name: void BL_RECOVERY_TimerEndCallBack(void)
* Description  : Assign this to 500ms timer driver count end interrupt
* Arguments    : None
* Return Value : None
******************************************************************************/
void BL_RECOVERY_TimerEndCallBack(void)
{
    if (g_bl_recovery_is_processing)
    {
        g_bl_recovery_timeout_counter++;
        
        /* Check for communication timeout and recovery mode timeout */
        if (g_bl_recovery_opr_state == IDLE)
        {
            /* Raise signal to exit recovery mode */
            if (g_bl_recovery_timeout_counter >= BL_RECOVERY_TIMEOUT_COUNT_IDLE_MODE)
            {
                g_bl_recovery_is_mode_timeout = 1;
                g_bl_recovery_timeout_counter = 0;
            }
        }
        else
        {
            /* Reset the data frame */
            if (g_bl_recovery_timeout_counter >= BL_RECOVERY_TIMEOUT_COUNT_DATA_MODE)
            {
                g_bl_recovery_frame_length = 0;
                g_bl_recovery_receive_count = 0;
                g_bl_recovery_opr_state = IDLE;
                /* No reset the time out, let it continue counting */
            }
        }
    }
}

/***********************************************************************************************************************
* Function Name: void BL_RECOVERY_Processing()
* Description  : Check for condition to enter recovery mode and process in recovery mode 
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void BL_RECOVERY_Processing(void)
{
    uint8_t is_requested = 0;
    
    /* Check for condition of recovery mode */
    /* Is button press? */
    IS_RECOVERY_MODE_HARDWARE_REQUESTED(is_requested);
    /* Is special variable set? */
    IS_RECOVERY_MODE_SOFTWARE_REQUESTED(is_requested);
    
    if (is_requested)
    {
         /* Change to max CPU speed to reduce processing time */
        FLASH_CPU_SWITCH_MAX_SPEED();

        /* Inform to user on LCD */
        BL_LCD_DisplayRecoveryMode();
        
        /* Inform the timer to start counting */
        g_bl_recovery_is_processing = 1;
        
        while (g_bl_recovery_is_processing)
        {
            BL_RECOVERY_PollingProcessing();
            
            /* Check for recovery mode exit condition */
            /* Exit by keypress or timeout or receive command to exit */
            if (g_bl_recovery_is_key_press == 1 ||
                g_bl_recovery_is_mode_timeout == 1 ||
                g_bl_recovery_is_mode_finish == 1)
            {
                /* Consider the image burn by recovery is correct
                 * Inform internally the startup is ok
                */
                if (g_bl_recovery_is_mode_finish == 1)
                {
                    BL_OPERATION_InformStartupOK();
                }
                g_bl_recovery_is_processing = 0;
            }
            R_WDT_Restart();
        }


        FLASH_CPU_SWITCH_MIN_SPEED();
    }

    /* Acknowledge complete recovery mode */
    BL_OPERATION_ClearConfirmCode(REQUEST_RECOVERY_MODE);
}