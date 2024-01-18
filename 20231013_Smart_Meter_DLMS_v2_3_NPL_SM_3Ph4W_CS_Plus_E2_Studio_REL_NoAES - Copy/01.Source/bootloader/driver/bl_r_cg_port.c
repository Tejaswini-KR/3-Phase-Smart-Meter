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
* File Name    : bl_r_cg_port.c
* Version      : 
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* Description  : This file implements device driver for PORT module.
* Creation Date: 
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "bl_r_cg_macrodriver.h"
#include "bl_r_cg_port.h"
#include "bl_r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_PORT_Create
* Description  : This function initializes the Port I/O.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_PORT_Create(void)
{
    /*  3PH4W SMART METER POC---New by VN on Nov-02-2020
     *--------------------------------------------------------------------------------------------------------------------------------------------
     *              7               6               5               4               3               2               1               0
     *--------------------------------------------------------------------------------------------------------------------------------------------
     *  P0  MCU     TXD0            RXD0            PORT_O          TXD1            RXD1            PORT_O
     *      NAME    COMM_TXD0       COMM_RXD0       COMM_CTRL0      COMM_TXD1       COMM_RXD1       LED0
     *--------------------------------------------------------------------------------------------------------------------------------------------
     *  P1  MCU     SEG11           SEG10           SEG9            SEG8            SEG7            SEG6            SEG5            SEG4
     *      NAME    SEG11           SEG10           SEG9            SEG8            SEG7            SEG6            SEG5            SEG4
     *--------------------------------------------------------------------------------------------------------------------------------------------
     *  P2  MCU                                     ANI2            ANI1            ANI0            ANI5/EXLVD      NC              ANI3/AVREFP
     *      NAME                                    ADC2            ADC1            ADC0            EXLVD	        NC              ADCREFP
     *--------------------------------------------------------------------------------------------------------------------------------------------
     *  P3  MCU     PORT_O          PORT_O          PORT_O          PORT_O          PORT_O          PORT_O           PORT_O         PORT_O
     *      NAME    RLY_00          RLY_01          RLY_10          RLY_11          RLY_20          RLY_21           PWR_SWT        VDD_CTRL
     *--------------------------------------------------------------------------------------------------------------------------------------------
     *  P4  MCU                                                                     PORT_O          NC                              E1
     *      NAME                                                                    LED1            NC                              TOOL0*
     *--------------------------------------------------------------------------------------------------------------------------------------------
     *  P5  MCU     SCK30           TXD2            RXD2            PORT_O          PORT_O          NC              PORT_O          PORT_O
     *      NAME    SPI_CLK         IR_TXD          IR_RXD          FL_CE           VCC-3           NC              VCC-2           VCC-1
     *--------------------------------------------------------------------------------------------------------------------------------------------
     *  P6  MCU                                                                                     PORT_O          SDAA0           SCLA0
     *      NAME                                                                                    EPR_WP          SDA0            SCL0
     *--------------------------------------------------------------------------------------------------------------------------------------------
     *  P7  MCU     SEG23           SEG22           SEG21           SEG20           SEG19           SEG18           SEG17           SEG16
     *      NAME    SEG23           SEG22           SEG21           SEG20           SEG19           SEG18           SEG17           SEG16
     *--------------------------------------------------------------------------------------------------------------------------------------------
     *  P8  MCU                                     SO30            SI30            SEG15           SEG14           SEG13           SEG12
     *      NAME                                    SPI_OUT         SPI_IN          SEG15           SEG14           SEG13           SEG12
     *--------------------------------------------------------------------------------------------------------------------------------------------
     *  P9  MCU     SEG3            SEG2            SEG1            SEG0            COM3            COM2            COM1            COM0
     *      NAME    SEG3            SEG2            SEG1            SEG0            COM3            COM2            COM1            COM0
     *--------------------------------------------------------------------------------------------------------------------------------------------
     *  P12 MCU     CAPH            CAPL            INTP1             XT2           XT1             PORT_I          PORT_I
     *      NAME    CAPH            CAPL            HALL_SENS         XT2           XT1             RLY_S1          RLY_S0
     *--------------------------------------------------------------------------------------------------------------------------------------------
     *  P13 MCU     PORT_I                                                                                                          PORT_O
     *      NAME    RLY_S2                                                                                                          COMM_CTL
     *--------------------------------------------------------------------------------------------------------------------------------------------
     *  P15 MCU                                                                                     RTCIC2          RTCIC1          RTCIC0
     *      NAME                                                                                    SW1             CASE_SW         SW2
     *--------------------------------------------------------------------------------------------------------------------------------------------
    */

    /* Setting for not used segements Evaluation board */
    PFSEG0 = _08_PFCOM3_COM | _04_PFCOM2_COM | _02_PFCOM1_COM | _01_PFCOM0_COM;
    PFSEG1 = _80_PFSEG07_SEG | _40_PFSEG06_SEG | _20_PFSEG05_SEG | _10_PFSEG04_SEG | 
             _08_PFSEG03_SEG | _04_PFSEG02_SEG | _02_PFSEG01_SEG | _01_PFSEG00_SEG;
    PFSEG2 = _80_PFSEG15_SEG | _40_PFSEG14_SEG | _20_PFSEG13_SEG | _10_PFSEG12_SEG | 
             _08_PFSEG11_SEG | _04_PFSEG10_SEG | _02_PFSEG09_SEG | _01_PFSEG08_SEG;
    PFSEG3 = _80_PFSEG23_SEG | _40_PFSEG22_SEG | _20_PFSEG21_SEG | _10_PFSEG20_SEG | 
             _08_PFSEG19_SEG | _04_PFSEG18_SEG | _02_PFSEG17_SEG | _01_PFSEG16_SEG;
    PFSEG4 = _00_PFSEG31_PORT | _00_PFSEG30_PORT | _00_PFSEG29_PORT | _00_PFSEG28_PORT |
             _00_PFSEG27_PORT | _00_PFSEG26_PORT | _00_PFSEG25_PORT | _00_PFSEG24_PORT;
    PFSEG5 = _00_PFSEG39_PORT | _00_PFSEG38_PORT | _00_PFSEG37_PORT | _00_PFSEG37_PORT |
             _00_PFSEG36_PORT | _00_PFSEG34_PORT | _00_PFSEG33_PORT;//| _00_PFSEG32_PORT;
    PFSEG6 = _00_PFSEG41_PORT | _00_PFSEG40_PORT;
    
    ISCLCD =    _02_VL3_BUFFER_VALID;
    /* Set port value */
    P0 =    _00_Pn7_OUTPUT_0 | _40_Pn6_OUTPUT_1 | _00_Pn5_OUTPUT_0 | _10_Pn4_OUTPUT_1 |
            _08_Pn3_OUTPUT_1 | _04_Pn2_OUTPUT_1 | _02_Pn1_OUTPUT_1 | _01_Pn0_OUTPUT_1; //P0.2: FEA_LED0
			
	P2 = _00_Pn1_OUTPUT_0;
    
    P3 =    _00_Pn7_OUTPUT_0 | _00_Pn6_OUTPUT_0 | _00_Pn5_OUTPUT_0 | _00_Pn4_OUTPUT_0 |
            _00_Pn3_OUTPUT_0 | _00_Pn2_OUTPUT_0 | _00_Pn1_OUTPUT_0 | _00_Pn0_OUTPUT_0; //P3.0: VDD_CTRL; P3.1: POWER_SWITCH
    
    P4 =    _08_Pn3_OUTPUT_1 | _04_Pn2_OUTPUT_1 | _01_Pn0_OUTPUT_1 ; //P4.3: FEA_LED1
    
    P5 =    _00_Pn7_OUTPUT_0 | _40_Pn6_OUTPUT_1 | _20_Pn5_OUTPUT_1 | _00_Pn4_OUTPUT_0 |
            _08_Pn3_OUTPUT_1 | _00_Pn2_OUTPUT_0 | _00_Pn1_OUTPUT_0 | _00_Pn0_OUTPUT_0; //P5.3: VCC-3; P5.2: VCC-2; P5.1: VCC-1		

    P6 =    _04_Pn2_OUTPUT_1 | _00_Pn1_OUTPUT_0 | _00_Pn0_OUTPUT_0;
    
    P7 =    _00_Pn7_OUTPUT_0 | _00_Pn6_OUTPUT_0 | _00_Pn5_OUTPUT_0 | _00_Pn4_OUTPUT_0 |
            _00_Pn3_OUTPUT_0 | _00_Pn2_OUTPUT_0 | _00_Pn1_OUTPUT_0 | _00_Pn0_OUTPUT_0;
    
    P8 =    _00_Pn5_OUTPUT_0 | _00_Pn4_OUTPUT_0 | _00_Pn3_OUTPUT_0 | _00_Pn2_OUTPUT_0 |
            _00_Pn1_OUTPUT_0 | _00_Pn0_OUTPUT_0;
            
    P13 =   _80_Pn7_OUTPUT_1 | _01_Pn0_OUTPUT_1;

    P15 =   _04_Pn2_OUTPUT_1 | _02_Pn1_OUTPUT_1 | _01_Pn0_OUTPUT_1;

    /* Pull up */
    //PU7 = 0xFF;

    /* Set port input/output mode */
    PM0 =  _03_PM0_DEFAULT_VALUE | _00_PMn7_MODE_OUTPUT | _40_PMn6_MODE_INPUT | _00_PMn5_MODE_OUTPUT | 
          _00_PMn4_MODE_OUTPUT | _08_PMn3_MODE_INPUT | _00_PMn2_MODE_OUTPUT;
		  
    PM1 =   _00_PMn7_MODE_OUTPUT | _00_PMn6_MODE_OUTPUT | _00_PMn5_MODE_OUTPUT | _00_PMn4_MODE_OUTPUT |
            _00_PMn3_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _00_PMn0_MODE_OUTPUT;
		  
    PM2 =   _20_PMn5_MODE_INPUT | _10_PMn4_MODE_INPUT | _08_PMn3_MODE_INPUT | _04_PMn2_MODE_INPUT | 
            _00_PMn1_MODE_OUTPUT | _01_PMn0_MODE_INPUT;
	
    PM3 =   _00_PMn7_MODE_OUTPUT | _00_PMn6_MODE_OUTPUT| _00_PMn5_MODE_OUTPUT | _00_PMn4_MODE_OUTPUT |     
            _00_PMn3_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT| _00_PMn1_MODE_OUTPUT | _00_PMn0_MODE_OUTPUT;
    
    PM4 =   _00_PMn3_MODE_OUTPUT | _01_PMn0_MODE_INPUT;
    
    PM5 =   _00_PMn7_MODE_OUTPUT | _00_PMn6_MODE_OUTPUT | _20_PMn5_MODE_INPUT | _00_PMn4_MODE_OUTPUT |
            _08_PMn3_MODE_INPUT  | _00_PMn2_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _00_PMn0_MODE_OUTPUT;
    
    PM6 =   _00_PMn2_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _00_PMn0_MODE_OUTPUT;
    
    PM7 =   _00_PMn7_MODE_OUTPUT | _00_PMn6_MODE_OUTPUT | _00_PMn5_MODE_OUTPUT | _00_PMn4_MODE_OUTPUT |
            _00_PMn3_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _00_PMn0_MODE_OUTPUT;
    
    PM8 =   _00_PMn5_MODE_OUTPUT | _00_PMn4_MODE_OUTPUT | _00_PMn3_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT |
            _00_PMn1_MODE_OUTPUT | _00_PMn0_MODE_OUTPUT;
    
    PM9 =   _00_PMn7_MODE_OUTPUT | _00_PMn6_MODE_OUTPUT | _00_PMn5_MODE_OUTPUT | _00_PMn4_MODE_OUTPUT |
            _00_PMn3_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _00_PMn0_MODE_OUTPUT;

    PM15 =  _04_PMn2_MODE_INPUT | _02_PMn1_MODE_INPUT | _01_PMn0_MODE_INPUT; 
}

/* Start user code for adding. Do not edit comment generated here */
/***********************************************************************************************************************
* Function Name: R_PORT_StopCreate
* Description  : This function turn off unnesccesary port pin before stopping to conserve power
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_PORT_StopCreate(void)
{
    /*  Turn off un necessarcy port before sleeping 
    *   Only keep below items:
    *       1. EEPROM
    *       2. LCD
    *       3. SW1, CASE
    */

		
	P3 = _00_Pn2_OUTPUT_0;
	P5 = _00_Pn2_OUTPUT_0;
	
//    P0 = 0x00;
//    P1 = 0x00;
//    P2 = 0x00;
//    P3 = 0x00;
//    P4 = _01_Pn0_OUTPUT_1;
//    P5 = 0x00;
//    P6 = _04_Pn2_OUTPUT_1;
//    P7 = 0x00;
//    P8 = 0x00;
//    P13 = _01_Pn0_OUTPUT_1;
}
/* End user code. Do not edit comment generated here */
