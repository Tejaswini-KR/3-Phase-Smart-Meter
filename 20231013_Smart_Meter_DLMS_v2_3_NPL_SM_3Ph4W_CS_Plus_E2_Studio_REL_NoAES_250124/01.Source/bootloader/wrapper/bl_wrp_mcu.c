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
* File Name    : bl_wrp_mcu.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : 
* Description  : Specified MCU APIs
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "compiler.h"
#include "bl_wrp_mcu.h"                /* MCU Wrapper Layer definitions */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/*
 * fCPU test statement
 *
 * write (0) if MCU not support,
 * else, please write down the code that indicate speed of MCU is running
 */
#define IS_MCU_RUN_AT_24MHZ     (HOCODIV == 0x00)
#define IS_MCU_RUN_AT_06MHZ     (HOCODIV == 0x02)

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
* Function Name: void MCU_Delay(uint16_t us)
* Note         : THIS FUNCTION STRICTLY DEPEND ON THE MCU
*              : BELOW IMPLEMENTATION IS USED FOR RL78I1B ONLY
*              : WHEN CHANGE TO OTHER MCU, PLEASE RE-IMPLEMENT THIS FUNCTION
* Description  : MCU Delay
* Arguments    : uint16_t us: Expected delay time, in micro second, us must > 0
* Return Value : None
***********************************************************************************************************************/
void MCU_Delay(uint16_t us)
{
    if (IS_MCU_RUN_AT_24MHZ)
    {
        #if 1
        
        /* Compensate -1us for:
         *  - Copy param to AX (input params)
         *  - CALL _MCU_Delay 
         *  - Begin & End function
         * See "ASM Code Summary Table" for more detail
         */
        if (us < 1)
        {
            return;
        }
        us--;
        
        /* NOP compensated for t2 */
        NOP();
        
        /* Implementation */
        while (us)  /* Each loop must elapse 1us */
        {
            /* Put ASM code (NOP instruction here) */
            /* 16 NOP Compensated t3 */
            NOP();  /* 01 */
            NOP();  /* 02 */
            NOP();  /* 03 */
            NOP();  /* 04 */
            NOP();  /* 05 */
            NOP();  /* 06 */
            NOP();  /* 07 */
            NOP();  /* 08 */
            NOP();  /* 09 */
            NOP();  /* 10 */
            NOP();  /* 11 */
            NOP();  /* 12 */
            NOP();  /* 13 */
            NOP();  /* 14 */
            NOP();  /* 15 */
            NOP();  /* 16 */
            
            us--;   /* count down number of us */
        }

        /*
         *-----------------------------------------------------------------------------------------------
         *| ASM Code Summary Table                                                                      |
         *| . Setting of RL78I1B                                                                        |
         *|   fCPU = 24MHz                                                                              |
         *|   -->  1Clock = 0.0416666666666667us, 1us = 24 clock                                        |
         *| . Requirement                                                                               |
         *|   > t1 + t2 + t4 = 1us (24 clocks)                                                          |
         *|   > t3           = 1us (24 clocks)                                                          |
         *| . Actual                                                                                    |
         *|   > t1 + t4 = 19 clock                                                                      |
         *|   > t2 = 5 clock compensated                                                                |
         *|   > t1 + t2 + t4 = 24 * 41.66 = 1us (Passed)                                                |
         *|   > t3           = 8clock + 16clock compensated = 24 * 41.66 = 1us (Passed)                 |
         *-----------------------------------------------------------------------------------------------
         *| ASM Code                                        | Description          | Summary (by time)  |
         *-----------------------------------------------------------------------------------------------
         * _MCU_Delay:                                      |                      |                    |
         *                                                  |                      |                    |
         *                                                  |                      |                    |
         * # <<Begin Function>>                             |                      | <<Begin Function>> |
         * # MOVW Input Parameter to AX                     | 1clock            t1 | t1: 6 clocks       |
         * # CALL _MCU_Delay                                | 3clocks           t1 |                    |
         * #                                                |                      |                    |
         * #   Backup Register                              |                      |                    |
         * #   Variable Stack Allocation                    |                      |                    |
         *                                                  |                      |                    |
         *    c7          PUSH            HL                | 1clock            t1 |                    |
         *    16          MOVW            HL,AX             | 1clock            t1 |                    |
         *                                                  |                      |                    |
         * # <<Function Body>>                              |                      | <<Function Body>>  |
         * # <<Compensate>>                                 |                      | <<Compensate>>     |
         *    b7          DECW            HL                | 1clock            t2 | t2: 5 clock        |
         *    f6          CLRW            AX                | 1clock            t2 |                    |
         *    47          CMPW            AX,HL             | 1clock            t2 |                    |
         *    61f8        SKNZ                              | 1clock            t2 |                    |
         *    00          NOP                               | 1clock            t2 |                    |        
         *                                                  |                      |                    |
         * # while (us)                                     |                      | << 1 Whill Loop>>  |
         * # {                                              |                      | t3: 24 clocks      |
         *    f6          CLRW            AX                | 1clock         t3 t4 |                    |
         *    47          CMPW            AX,HL             | 1clock         t3 t4 |                    |
         *    xxxx        BZ              $[End Function]   | 2clocks (NM)   t3    |                    |
         *                                                  | 4clocks ( M)      t4 |                    |
         * # NOP(); 16 NOP                                  |                      |                    |
         *    00          NOP x 16                          | 16clock        t3    |                    |
         *                                                  |                      |                    |
         * #us--;                                           |                      |                    |
         *    b7          DECW            HL                | 1clock         t3    |                    |
         *                                                  |                      |                    |
         * # }                                              |                      |                    |
         *    xxxx        BR              $[# while (us)]   | 3clocks        t3    |                    |
         *                                                  |                      |                    |
         * # <<End Function>>                               |                      | <<End Function>>   |
         *    c6          POP             HL                | 1clock            t4 | t4: 13 clocks      |
         *    d7          RET                               | 6clocks           t4 |                    |
         *                                                  |                      |                    |
         *-----------------------------------------------------------------------------------------------
         */
         
        #endif
    }
    else if (IS_MCU_RUN_AT_06MHZ)
    {
        #if 1
        
        /* Compensate -4us for:
         *  - Copy param to AX (input params)
         *  - CALL _MCU_Delay 
         *  - Begin & End function
         * See "ASM Code Summary Table" for more detail
         */
        if (us <= 4)
        {
            us = 1;
        }
        else
        {
            us = us / 2;
        }
        us--;
        
        /* 1 NOP Compensated t2 */
        NOP();  
        
        /* Implementation */
        while (us)  /* Each loop must elapse 2us */
        {
            /* Put ASM code (NOP instruction here) */
            /* 4 NOP Compensated t3 */
            NOP();  /*  01  */
            NOP();  /*  02  */
            NOP();  /*  03  */
            NOP();  /*  04  */
            
            us--;   /* count down number of us */
        }
        
        /*  
         *-----------------------------------------------------------------------------------------------   
         *| ASM Code Summary Table                                                                      |   
         *| . Setting of RL78I1B                                                                        |   
         *|   fCPU = 6MHz                                                                               |   
         *|   -->  1Clock = (1/6)us ~ 0.1666667us --> 1us = 6clock                                      |   
         *| . Requirement                                                                               |   
         *|   > t1 + t2 + t4 = 4us (24 clocks)                                                          |   
         *|   > t3           = 2us (12 clocks)                                                          |   
         *| . Actual                                                                                    |   
         *|   > t1 + t4      = 19clock                                                                  |   
         *|   > t2 = 24-19   = 5clock compensated                                                       |   
         *|   > t3           = 8clock + 4clock compensated = 12 / 6 = 2us (Passed)                     |    
         *-----------------------------------------------------------------------------------------------   
         *| ASM Code                                        | Description          | Summary (by time)  |   
         *-----------------------------------------------------------------------------------------------   
         * _MCU_Delay:                                      |                      |                    |   
         *                                                  |                      |                    |   
         *                                                  |                      |                    |   
         * # <<Begin Function>>                             |                      | <<Begin Function>> |   
         * # MOVW Input Parameter to AX                     | 1clock            t1 | t1: 6 clocks       |   
         * # CALL _MCU_Delay                                | 3clocks           t1 |                    |   
         * #                                                |                      |                    |   
         * #   Backup Register                              |                      |                    |   
         * #   Variable Stack Allocation                    |                      |                    |   
         *                                                  |                      |                    |   
         *    c7          PUSH            HL                | 1clock            t1 |                    |   
         *    16          MOVW            HL,AX             | 1clock            t1 |                    |   
         *                                                  |                      |                    |   
         * # <<Function Body>>                              |                      | <<Function Body>>  |   
         * # <<Compensate>>                                 |                      | <<Compensate>>     |   
         *    17          MOVW            AX,HL             | 1clock            t2 | t2: 5 clocks       |   
         *    312e        SHRW            AX,2H             | 1clock            t2 |                    |   
         *    16          MOVW            HL,AX             | 1clock            t2 |                    |   
         *    b7          DECW            HL                | 1clock            t2 |                    |   
         *    00          NOP                               | 1clock            t2 |                    |   
         *                                                  |                      |                    |   
         * # while (us)                                     |                      | << 1 Whill Loop>>  |   
         * # {                                              |                      | t3: 12 clocks      |   
         *    f6          CLRW            AX                | 1clock         t3 t4 |                    |   
         *    47          CMPW            AX,HL             | 1clock         t3 t4 |                    |   
         *    xxxx        BZ              $[End Function]   | 2clocks (NM)   t3    |                    |   
         *                                                  | 4clocks ( M)      t4 |                    |   
         * # NOP(); 16 NOP                                  |                      |                    |   
         *    00          NOP x 4                           | 4clock         t3    |                    |   
         *                                                  |                      |                    |   
         * #us--;                                           |                      |                    |   
         *    b7          DECW            HL                | 1clock         t3    |                    |   
         *                                                  |                      |                    |   
         * # }                                              |                      |                    |   
         *    xxxx        BR              $[# while (us)]   | 3clocks        t3    |                    |   
         *                                                  |                      |                    |   
         * # <<End Function>>                               |                      | <<End Function>>   |   
         *    c6          POP             HL                | 1clock            t4 | t4: 13 clocks      |   
         *    d7          RET                               | 6clocks           t4 |                    |   
         *                                                  |                      |                    |   
         *-----------------------------------------------------------------------------------------------}  
         */
         
        #endif
    }
}
