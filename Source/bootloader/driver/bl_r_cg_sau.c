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
* File Name    : bl_r_cg_sau.c
* Version      : 
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* Description  : This file implements device driver for SAU module.
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
#include "bl_r_cg_sau.h"
/* Start user code for include. Do not edit comment generated here */
#include "bl_header.h"
/* End user code. Do not edit comment generated here */
#include "bl_r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
#ifdef __CCRL__

#pragma section bss BLBss
#pragma section data BLData

#endif

volatile uint8_t  *gp_Csi30RxAddress;   /* csi00 receive buffer address */
volatile uint16_t g_Csi30RxLen;         /* csi00 receive data length */
volatile uint16_t g_Csi30RxCnt;         /* csi00 receive data count */
volatile uint8_t  *gp_Csi30TxAddress;   /* csi00 send buffer address */
volatile uint16_t g_Csi30TxLen;         /* csi00 send data length */
volatile uint16_t g_Csi30TxCnt;         /* csi00 send data count */

volatile uint8_t * gp_uart2_tx_address;        /* uart2 transmit buffer address */
volatile uint16_t  g_uart2_tx_count;           /* uart2 transmit data number */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**  This function initializes the SAU0 module.
**
**  Parameters:
**  None
**
**  Returns:
**  None
**
**-----------------------------------------------------------------------------
*/
void R_SAU1_Create(void)
{
    SAU1EN = 1U;    /* supply SAU0 clock */
    NOP();
    NOP();
    NOP();
    NOP();
    SPS1 = _0004_SAU_CK00_FCLK_4 | _0000_SAU_CK01_FCLK_0;   /* UART2: 9600, CSI30: highest speed */
    R_UART2_Create();
    R_CSI30_Create();
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**  This function initializes the CSI00 module.
**
**  Parameters:
**  None
**
**  Returns:
**  None
**
**-----------------------------------------------------------------------------
*/
void R_CSI30_Create(void)
{
    ST0 |= _0004_SAU_CH2_STOP_TRG_ON;    /* disable CSI30 */
    CSIMK30 = 1U;    /* disable INTCSI30 interrupt */
    CSIIF30 = 0U;    /* clear INTCSI30 interrupt flag */
    /* Set INTCSI30 low priority */
    CSIPR130 = 1U;
    CSIPR030 = 1U;
    SIR12 = _0004_SAU_SIRMN_FECTMN | _0002_SAU_SIRMN_PECTMN | _0001_SAU_SIRMN_OVCTMN;    /* clear error flag */
    SMR12 = _0020_SAU_SMRMN_INITIALVALUE | _8000_SAU_CLOCK_SELECT_CK01 | _0000_SAU_CLOCK_MODE_CKS |
            _0000_SAU_TRIGGER_SOFTWARE | _0000_SAU_MODE_CSI | _0000_SAU_TRANSFER_END;
    SCR12 = _C000_SAU_RECEPTION_TRANSMISSION | _0000_SAU_TIMING_1 | _0000_SAU_MSB | _0007_SAU_LENGTH_8;
    SDR12 = _0400_CSI30_DIVISOR;
    SO1 |= _0400_SAU_CH2_CLOCK_OUTPUT_1;    /* CSI30 clock initial level */
    SO1 &= ~_0004_SAU_CH2_DATA_OUTPUT_1;    /* CSI30 SO initial level */
    SOE1 |= _0004_SAU_CH2_OUTPUT_ENABLE;    /* enable CSI30 output */
    ///* Set SCK30 pin */
    //PFSEG4 &= 0x7FU;
    //P5 |= 0x80U;
    //PM5 &= 0x7FU;
    ///* Set SI30 pin */
    //PFSEG5 &= 0xFEU;
    //PM8 |= 0x10U;
    ///* Set SO30 pin */
    //PFSEG5 &= 0xFDU;
    //P8 |= 0x20U;
    //PM8 &= 0xDFU;
}

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**  This function starts the CSI30 module operation.
**
**  Parameters:
**  None
**
**  Returns:
**  None
**
**-----------------------------------------------------------------------------
*/
void R_CSI30_Start(void)
{
    CSIIF30 = 0U;   /* clear INTCSI30 interrupt flag */
    CSIMK30 = 0U;   /* enable INTCSI30 */
    SO1 |= _0400_SAU_CH2_CLOCK_OUTPUT_1;    /* CSI30 clock initial level */
    SO1 &= ~_0004_SAU_CH2_DATA_OUTPUT_1;    /* CSI30 SO initial level */
    SOE1 |= _0004_SAU_CH2_OUTPUT_ENABLE;    /* enable CSI30 output */
    SS1 |= _0004_SAU_CH2_START_TRG_ON;  /* enable CSI30 */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**  This function stops the CSI30 module operation.
**
**  Parameters:
**  None
**
**  Returns:
**  None
**
**-----------------------------------------------------------------------------
*/
void R_CSI30_Stop(void)
{
    ST1 |= _0004_SAU_CH2_STOP_TRG_ON;   /* disable CSI30 */
    SOE1 &= ~_0004_SAU_CH2_OUTPUT_ENABLE;   /* disable CSI30 output */
    CSIMK30 = 1U;   /* disable INTCSI30 interrupt */
    CSIIF30 = 0U;   /* clear INTCSI30 interrupt flag */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**  This function sends and receives CSI00 data.
**
**  Parameters:
**  txbuf: transfer buffer pointer
**  txnum: buffer size
**  rxbuf: receive buffer pointer
**
**  Returns:
**  MD_OK
**  MD_ARGERROR
**
**-----------------------------------------------------------------------------
*/
MD_STATUS R_CSI30_Send_Receive(uint8_t *txbuf, uint16_t txnum, uint8_t *rxbuf)
{
    MD_STATUS status = MD_OK;

    if (txnum < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        g_Csi30TxCnt = txnum;   /* send data count */
        gp_Csi30TxAddress = txbuf;  /* send buffer pointer */
        gp_Csi30RxAddress = rxbuf;  /* receive buffer pointer */
        CSIMK30 = 1U;   /* disable INTCSI30 interrupt */
        SIO30 = *gp_Csi30TxAddress; /* started by writing data to SDR[7:0] */
        gp_Csi30TxAddress++;
        g_Csi30TxCnt--;
        CSIMK30 = 0U;   /* enable INTCSI30 interrupt */
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: R_UART2_Create
* Description  : This function initializes the UART2 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UART2_Create(void)
{
    ST1 |= _0002_SAU_CH1_STOP_TRG_ON | _0001_SAU_CH0_STOP_TRG_ON;    /* disable UART2 receive and transmit */
    STMK2 = 1U;    /* disable INTST2 interrupt */
    STIF2 = 0U;    /* clear INTST2 interrupt flag */
    SRMK2 = 1U;    /* disable INTSR2 interrupt */
    SRIF2 = 0U;    /* clear INTSR2 interrupt flag */
    SREMK2 = 1U;   /* disable INTSRE2 interrupt */
    SREIF2 = 0U;   /* clear INTSRE2 interrupt flag */
    /* Set INTST2 low priority */
    STPR12 = 1U;
    STPR02 = 1U;
    /* Set INTSR2 low priority */
    SRPR12 = 0U;
    SRPR02 = 0U;
    SMR10 = _0020_SAU_SMRMN_INITIALVALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_TRIGGER_SOFTWARE | 
            _0002_SAU_MODE_UART | _0000_SAU_TRANSFER_END;
    SCR10 = _8000_SAU_TRANSMISSION | _0000_SAU_INTSRE_MASK | _0000_SAU_PARITY_NONE | _0080_SAU_LSB | 
            _0010_SAU_STOP_1 | _0007_SAU_LENGTH_8;
    SDR10 = _9A00_UART2_TRANSMIT_DIVISOR;
    NFEN0 |= _10_SAU_RXD2_FILTER_ON;
    SIR11 = _0004_SAU_SIRMN_FECTMN | _0002_SAU_SIRMN_PECTMN | _0001_SAU_SIRMN_OVCTMN;    /* clear error flag */
    SMR11 = _0020_SAU_SMRMN_INITIALVALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0100_SAU_TRIGGER_RXD | _0000_SAU_EDGE_FALL | 
            _0002_SAU_MODE_UART | _0000_SAU_TRANSFER_END;
    SCR11 = _4000_SAU_RECEPTION | _0000_SAU_INTSRE_MASK | _0000_SAU_PARITY_NONE | _0080_SAU_LSB | _0010_SAU_STOP_1 | 
            _0007_SAU_LENGTH_8;
    SDR11 = _9A00_UART2_RECEIVE_DIVISOR;
    SO1 |= _0001_SAU_CH0_DATA_OUTPUT_1;
    SOL1 |= _0000_SAU_CHANNEL0_NORMAL;    /* output level normal */
    SOE1 |= _0001_SAU_CH0_OUTPUT_ENABLE;    /* enable UART2 output */
    ///* Set RxD2 pin */
    //PM5 |= 0x20U;
    ///* Set TxD2 pin */
    //P5 |= 0x40U;
    //PM5 &= 0xBFU;
}
/***********************************************************************************************************************
* Function Name: R_UART2_Start
* Description  : This function starts the UART2 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UART2_Start(void)
{
    SO1 |= _0001_SAU_CH0_DATA_OUTPUT_1;    /* output level normal */
    SOE1 |= _0001_SAU_CH0_OUTPUT_ENABLE;    /* enable UART2 output */
    SS1 |= _0002_SAU_CH1_START_TRG_ON | _0001_SAU_CH0_START_TRG_ON;    /* enable UART2 receive and transmit */
    STIF2 = 0U;    /* clear INTST2 interrupt flag */
    SRIF2 = 0U;    /* clear INTSR2 interrupt flag */
    SRMK2 = 0U;    /* enable INTSR2 interrupt */
    STMK2 = 0U;    /* enable INTST2 interrupt */
}
/***********************************************************************************************************************
* Function Name: R_UART2_Stop
* Description  : This function stops the UART2 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UART2_Stop(void)
{
    STMK2 = 1U;    /* disable INTST2 interrupt */
    SRMK2 = 1U;    /* disable INTSR2 interrupt */
    ST1 |= _0002_SAU_CH1_STOP_TRG_ON | _0001_SAU_CH0_STOP_TRG_ON;    /* disable UART2 receive and transmit */
    SOE1 &= ~_0001_SAU_CH0_OUTPUT_ENABLE;    /* disable UART2 output */
    STIF2 = 0U;    /* clear INTST2 interrupt flag */
    SRIF2 = 0U;    /* clear INTSR2 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_UART2_Send
* Description  : This function sends UART2 data.
* Arguments    : tx_buf -
*                    transfer buffer pointer
*                tx_num -
*                    buffer size
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_UART2_Send(uint8_t * tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        gp_uart2_tx_address = tx_buf;
        g_uart2_tx_count = tx_num;
        STMK2 = 1U;    /* disable INTST2 interrupt */
        TXD2 = *gp_uart2_tx_address;
        gp_uart2_tx_address++;
        g_uart2_tx_count--;
        STMK2 = 0U;    /* enable INTST2 interrupt */
    }

    return (status);
}



/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
