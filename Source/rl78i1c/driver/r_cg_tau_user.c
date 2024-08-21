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
* File Name    : r_cg_tau_user.c
* Version      : Code Generator for RL78/I1C V1.01.00.02 [15 May 2017]
* Device(s)    : R5F10NPJ
* Tool-Chain   : CCRL
* Description  : This file implements device driver for TAU module.
* Creation Date: 3/22/2019
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_tau.h"
#include "r_cg_sau.h"
/* Start user code for include. Do not edit comment generated here */
#include "em_core.h"
#include "r_calib.h"
#ifdef _DLMS
#include "r_dlms_physical_wrapper.h"
#include "r_dlms_timeout_wrapper.h"
#include "r_dlms_udp_wrapper_interface.h"
#include "r_dlms_tcp_wrapper_interface.h"
#endif
#include "wrp_app_ext.h"
#include "Global_Var.h"
#include "User_Def.h"
#include "Func_Dec.h"
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
* Function Name: r_tau0_channel0_interrupt
* Description  : This function INTTM00 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
NEAR_FUNC void r_tau0_channel0_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    EI();
    
    #ifdef _DLMS
    /* DLMS Physical Timeout Count */
    R_DLMS_HdlcTimeoutMilisecondTimerCallback();
    R_DLMS_UdpTimeoutMilisecondTimerCallback();
	R_DLMS_TcpTimeoutMilisecondTimerCallback();
	R_UDP_WRP_ReceiverTimeoutMilisecond();
	R_TCP_WRP_ReceiverTimeoutMilisecond();
    R_PHY_DeviceTimeOutCount();
    #endif /* _DLMS */
    WRP_EXT_HwDelayMillisecondTimerCallback();
	
	Modbus_Timer();
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_tau0_channel1_interrupt
* Description  : This function INTTM01 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
NEAR_FUNC void r_tau0_channel1_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_tau0_channel2_interrupt
* Description  : This function INTTM02 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
NEAR_FUNC void r_tau0_channel2_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    EI();
    
    if (R_CALIB_IsInCalibMode() == 0)
    {
        EM_TIMER_InterruptCallback();
    }
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
void Modbus_Timer(void)
 {
    //**************************************Modbus*******************************************
if(Silent_Interval) // avoid below in bus idle state
 { if(!--Silent_Interval)
   { 
     Modbus_Bit_Fields.SI_Over=1; // mark end of Silent Interval
     if(Modbus_State==1) // if in query rx
	{
	  // frame is completed and stop receiving the data , set the complete FLAG start transmitting the data
	   Modbus_Bit_Fields.Valid_Frame_complete=1; 
	   R_UART1_Stop();
	} 
   if(Modbus_Bit_Fields.Modbus_Tx_Completed)	//Change over to Reception mode if tX complete
     { 		
   		Modbus_Bit_Fields.Modbus_Tx_Completed=0; 
		RS485_DIR=0;
     	R_UART1_RX_ON();
		Modbus_State=0;
     }
    Silent_Interval=Char_Frame_Delay;
    Modbus_State=0;       //  ID is not matching ignore frame and Initialize for the next frame
   }
 }   
}
/* End user code. Do not edit comment generated here */
