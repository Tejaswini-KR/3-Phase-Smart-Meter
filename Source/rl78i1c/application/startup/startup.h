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
* File Name    : startup.h
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : Start-up source File
***********************************************************************************************************************/

#ifndef _START_UP
#define _START_UP

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Status */
#define STARTUP_OK                  0       /* OK */
#define STARTUP_ERROR               1       /* Error */

/* Relationship between FLMODE and CPU clock:
 *  . 1-8MHz: LS mode, MODE0=0 (FLMODE register)
 *  . 1-24MHz: HS mode, MODE0=1 (FLMODE register)
 *  Changing: LS-->HS: 225 cycles
 *  Changing: HS-->LS: 30 cycles
*/

/* Worst case HS to LS */
#define FLASH_MODE_HS_TO_LS()       {\
                                        FLMWEN = 1U;\
                                        SET_BIT(FLMODE, 6, 0U);\
                                        FLMWEN = 0U;\
                                        MCU_Delay(30);\
                                    }

/* Worst case LS to HS */
#define FLASH_MODE_LS_TO_HS()       {\
                                        FLMWEN = 1U;\
                                        SET_BIT(FLMODE, 6, 1U);\
                                        FLMWEN = 0U;\
                                        MCU_Delay(50);\
                                    }

#define FLASH_MODE_IS_HS()          (BIT_SELECT(FLMODE, 6) == 1U)

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/
typedef struct st_em_startup_diag {
    uint8_t em_init_status;             /* EM_Init status */
    uint8_t config_load_status;         /* Config storage reload from dataflash status (other than 0 means error) */
    uint8_t energy_load_status;         /* Energy storage reload from EEPROM status (other than 0 means error) */
    uint8_t em_start_status;            /* EM_Start status */
} st_em_startup_diag_t;

/***********************************************************************************************************************
Variable Externs
******************************************************************************/
extern uint8_t g_reset_flag;
extern uint8_t g_softreset_flag;
extern st_em_startup_diag_t g_em_startup_diag;
/******************************************************************************
Functions Prototypes
***********************************************************************************************************************/
void start_peripheral_and_app(void);
void stop_peripheral(void);
void startup(void);

#endif /* _START_UP */

