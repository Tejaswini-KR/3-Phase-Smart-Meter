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
* File Name    : cmd.h
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : CCRL
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : CMD Prompt MW Layer APIs
***********************************************************************************************************************/

#ifndef _CMD_PROMPT_H
#define _CMD_PROMPT_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "typedef.h"        /* GSCE Standard Typedef */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum tagCMDMode
{
    CMD_MODE_COMMAND = 0,   /* Command */
    CMD_MODE_RECEIVE_DATA   /* Binary receive data */
} CMD_MODE;

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define     CMD_USING_LAST_CMD              1       /* 1: USE, 0: UN-USE */
#define     CMD_USING_BUILT_IN_CMD          1       /* 1: USE, 0: UN-USE */
#define     CMD_USING_RECEIVE_ISR_INSIDE    0       /* 1: USE, 0: UN-USE */
#define     CMD_USING_SUGGESTION            1       /* 1: USE, 0: UN-USE */
#define     CMD_USING_HINT_WHEN_TYPING      0       /* 1: USE, 0: UN-USE */

#define     PRINT_COLOR_VT100_DEFAULT       0
#define     PRINT_COLOR_VT100_BLACK         30
#define     PRINT_COLOR_VT100_RED           31
#define     PRINT_COLOR_VT100_GREEN         32
#define     PRINT_COLOR_VT100_YELLOW        33
#define     PRINT_COLOR_VT100_BLUE          34
#define     PRINT_COLOR_VT100_MAGENTA       35
#define     PRINT_COLOR_VT100_CYAN          36

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/
/* Control */
void    CMD_Init(void);                                 /* CMD Init */
void    CMD_Start(void);                                /* Start Receive Cmd */
void    CMD_Stop(void);                                 /* Stop Receive Cmd */
uint8_t CMD_ChangeMode(CMD_MODE mode);              /* Change CMD Mode */
uint8_t CMD_GetReceivedByte(uint8_t* byte);         /* Get received byte */
uint8_t CMD_IsCmdReceived(void);                        /* Is CMD received ? */
void    CMD_AckCmdReceived(void);                       /* Ack CMD received */
uint8_t CMD_IsCtrlKeyReceived(void);                    /* Is CTRL+C key received ? */
void    CMD_AckCtrlKeyReceived(void);                   /* Ack CTRL+C received */
void    CMD_RegisterSuggestion(                     /* Register suggestion table */
    void *table,
    uint16_t table_length
);
/* Get Command */
uint8_t* CMD_Get(void);                                 /* Get the current CMD string */

/* Print out string */
void    CMD_SendString(uint8_t *str);               /* Send string to CMD Prompt */
void    CMD_SendStringA(uint8_t *str, uint8_t size);/* Send string to CMD Prompt (asynch) */
void    CMD_Printf(const void *format, ...);           /* CMD Prompt Printf */
void    CMD_PrintfWithColor(uint8_t color, const void *format, ...);

/* Callback */
void    CMD_SendEndCallback(void);
void    CMD_ReceiveEndCallback(
#if !(CMD_USING_RECEIVE_ISR_INSIDE)
    uint8_t receive_byte
#endif
);
void CMD_AckCmdReceivedNoHeader(void);

#endif /* _CMD_PROMPT_H */
