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
* Copyright (C) 2015, 2017 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_port.c
* Version      : Code Generator for RL78/I1C V1.01.00.02 [15 May 2017]
* Device(s)    : R5F10NPJ
* Tool-Chain   : CCRL
* Description  : This file implements device driver for Port module.
* Creation Date: 3/22/2019
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_port.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

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
             _00_PFSEG36_PORT | _00_PFSEG34_PORT | _00_PFSEG33_PORT | _00_PFSEG32_PORT;
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
/* End user code. Do not edit comment generated here */
