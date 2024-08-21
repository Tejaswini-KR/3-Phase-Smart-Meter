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
* File Name    : r_cg_sau.c
* Version      : Code Generator for RL78/I1C V1.01.00.02 [15 May 2017]
* Device(s)    : R5F10NPJ
* Tool-Chain   : CCRL
* Description  : This file implements device driver for SAU module.
* Creation Date: 3/22/2019
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_sau.h"
/* Start user code for include. Do not edit comment generated here */
#include "Global_Var.h"
#include "User_Def.h"
#include "Func_Dec.h"
#include "relay.h"
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
volatile uint8_t * gp_uart0_tx_address;        /* uart0 transmit buffer address */
volatile uint16_t  g_uart0_tx_count;           /* uart0 transmit data number */
volatile uint8_t * gp_uart0_rx_address;        /* uart0 receive buffer address */
volatile uint16_t  g_uart0_rx_count;           /* uart0 receive data number */
volatile uint16_t  g_uart0_rx_length;          /* uart0 receive data length */
volatile uint8_t * gp_uart2_tx_address;        /* uart2 transmit buffer address */
volatile uint16_t  g_uart2_tx_count;           /* uart2 transmit data number */
volatile uint8_t * gp_uart2_rx_address;        /* uart2 receive buffer address */
volatile uint16_t  g_uart2_rx_count;           /* uart2 receive data number */
volatile uint16_t  g_uart2_rx_length;          /* uart2 receive data length */
volatile uint8_t * gp_csi30_rx_address;        /* csi30 receive buffer address */
volatile uint16_t  g_csi30_rx_length;          /* csi30 receive data length */
volatile uint16_t  g_csi30_rx_count;           /* csi30 receive data count */
volatile uint8_t * gp_csi30_tx_address;        /* csi30 send buffer address */
volatile uint16_t  g_csi30_send_length;        /* csi30 send data length */
volatile uint16_t  g_csi30_tx_count;           /* csi30 send data count */

volatile uint8_t * gp_uart1_tx_address;        /* uart1 transmit buffer address */
volatile uint16_t  g_uart1_tx_count;           /* uart1 transmit data number */
volatile uint8_t * gp_uart1_rx_address;        /* uart1 receive buffer address */
volatile uint16_t  g_uart1_rx_count;           /* uart1 receive data number */
volatile uint16_t  g_uart1_rx_length;          /* uart1 receive data length */

/* Start user code for global. Do not edit comment generated here */
volatile sau_std_baud_rate_t g_uart0_current_baud_rate;
volatile sau_std_baud_rate_t g_uart2_current_baud_rate;
volatile sau_std_baud_rate_t g_uart1_current_baud_rate;
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_SAU0_Create
* Description  : This function initializes the SAU0 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU0_Create(void)
{
    SAU0EN = 1U;    /* enables input clock supply */
    NOP();
    NOP();
    NOP();
    NOP();
    SPS0 = _0000_SAU_CK01_fCLK_0 | _0005_SAU_CK00_fCLK_5;
    /* Default baud rate for this platform */
    R_UART0_SetBaudRate(SAU_STD_BAUD_RATE_9600);
	R_UART1_SetBaudRate(SAU_STD_BAUD_RATE_9600);
    R_UART0_Create();
	R_UART1_Create();
}
/***********************************************************************************************************************
* Function Name: R_UART0_Create
* Description  : This function initializes the UART0 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UART0_Create(void)
{
    ST0 |= _0002_SAUm_CH1_STOP_TRG_ON | _0001_SAUm_CH0_STOP_TRG_ON;
    STMK0 = 1U;     /* disable INTST0 interrupt */
    STIF0 = 0U;     /* clear INTST0 interrupt flag */
    SRMK0 = 1U;     /* disable INTSR0 interrupt */
    SRIF0 = 0U;     /* clear INTSR0 interrupt flag */
    SREMK0 = 1U;    /* disable INTSRE0 interrupt */
    SREIF0 = 0U;    /* clear INTSRE0 interrupt flag */
    /* Set INTSR0 high priority */
    SRPR10 = 0U;
    SRPR00 = 0U;
    /* Set INTST0 low priority */
    STPR10 = 1U;
    STPR00 = 1U;
    SMR00 = _0020_SMR00_DEFAULT_VALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_CLOCK_MODE_CKS | 
            _0002_SAU_MODE_UART | _0000_SAU_TRANSFER_END;
    SCR00 = _0004_SCR00_DEFAULT_VALUE | _8000_SAU_TRANSMISSION | _0000_SAU_TIMING_1 | _0000_SAU_INTSRE_MASK | 
            _0000_SAU_PARITY_NONE | _0080_SAU_LSB | _0010_SAU_STOP_1 | _0003_SAU_LENGTH_8;
    SDR00 = _4C00_UART_DIVISOR;
    NFEN0 |= _01_SAU_RXD0_FILTER_ON;
    SIR01 = _0004_SAU_SIRMN_FECTMN | _0002_SAU_SIRMN_PECTMN | _0001_SAU_SIRMN_OVCTMN;
    SMR01 = _0020_SMR01_DEFAULT_VALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_CLOCK_MODE_CKS | 
            _0100_SAU_TRIGGER_RXD | _0000_SAU_EDGE_FALL | _0002_SAU_MODE_UART | _0000_SAU_TRANSFER_END;
    SCR01 = _0004_SCR01_DEFAULT_VALUE | _4000_SAU_RECEPTION | _0000_SAU_TIMING_1 | _0000_SAU_INTSRE_MASK | 
            _0000_SAU_PARITY_NONE | _0080_SAU_LSB | _0010_SAU_STOP_1 | _0003_SAU_LENGTH_8;
    SDR01 = _4C00_UART_DIVISOR;
    SO0 |= _0001_SAUm_CH0_DATA_OUTPUT_1;
    SOL0 &= (uint16_t)~_0001_SAUm_CHANNEL0_INVERTED;
    SOE0 |= _0001_SAUm_CH0_OUTPUT_ENABLE;
    /* Set RxD0 pin */
    PM0 |= 0x40U;
    /* Set TxD0 pin */
    P0 |= 0x80U;
    PM0 &= 0x7FU;
}
/***********************************************************************************************************************
* Function Name: R_UART0_Start
* Description  : This function starts the UART0 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UART0_Start(void)
{
    SO0 |= _0001_SAUm_CH0_DATA_OUTPUT_1;
    SOE0 |= _0001_SAUm_CH0_OUTPUT_ENABLE;
    SS0 |= _0002_SAUm_CH1_START_TRG_ON | _0001_SAUm_CH0_START_TRG_ON;
    STIF0 = 0U;     /* clear INTST0 interrupt flag */
    SRIF0 = 0U;     /* clear INTSR0 interrupt flag */
    STMK0 = 0U;     /* enable INTST0 interrupt */
    SRMK0 = 0U;     /* enable INTSR0 interrupt */
}
/***********************************************************************************************************************
* Function Name: R_UART0_Stop
* Description  : This function stops the UART0 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UART0_Stop(void)
{
    STMK0 = 1U;     /* disable INTST0 interrupt */
    SRMK0 = 1U;     /* disable INTSR0 interrupt */
    ST0 |= _0002_SAUm_CH1_STOP_TRG_ON | _0001_SAUm_CH0_STOP_TRG_ON;
    SOE0 &= (uint16_t)~_0001_SAUm_CH0_OUTPUT_ENABLE;
    STIF0 = 0U;     /* clear INTST0 interrupt flag */
    SRIF0 = 0U;     /* clear INTSR0 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_UART0_Start_Reception
* Description  : This function starts the UART0 Reception only.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UART0_Start_Reception(void)
{
    SS0 |= _0002_SAUm_CH1_START_TRG_ON;
    SRIF0 = 0U;     /* clear INTSR0 interrupt flag */
    SRMK0 = 0U;     /* enable INTSR0 interrupt */
}

/***********************************************************************************************************************
* Function Name: R_UART0_Stop_Reception
* Description  : This function stops the UART0 Reception only.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UART0_Stop_Reception(void)
{
    SRMK0 = 1U;     /* disable INTSR0 interrupt */
    ST0 |= _0002_SAUm_CH1_STOP_TRG_ON;
    SRIF0 = 0U;     /* clear INTSR0 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_UART0_Receive
* Description  : This function receives UART0 data.
* Arguments    : rx_buf -
*                    receive buffer pointer
*                rx_num -
*                    buffer size
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_UART0_Receive(uint8_t * const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;

    if (rx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        g_uart0_rx_count = 0U;
        g_uart0_rx_length = rx_num;
        gp_uart0_rx_address = rx_buf;
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: R_UART0_Send
* Description  : This function sends UART0 data.
* Arguments    : tx_buf -
*                    transfer buffer pointer
*                tx_num -
*                    buffer size
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_UART0_Send(uint8_t * const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        gp_uart0_tx_address = tx_buf;
        g_uart0_tx_count = tx_num;
        STMK0 = 1U;    /* disable INTST0 interrupt */
        TXD0 = *gp_uart0_tx_address;
        gp_uart0_tx_address++;
        g_uart0_tx_count--;
        STMK0 = 0U;    /* enable INTST0 interrupt */
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: R_SAU1_Create
* Description  : This function initializes the SAU1 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU1_Create(void)
{
    SAU1EN = 1U;    /* enables input clock supply */
    NOP();
    NOP();
    NOP();
    NOP();
    SPS1 = _0000_SAU_CK01_fCLK_0 | _0005_SAU_CK00_fCLK_5;
    /* Default baud rate for this platform */
    R_UART2_SetBaudRate(SAU_STD_BAUD_RATE_9600);
    R_UART2_Create();
    R_CSI30_Create();
}
/***********************************************************************************************************************
* Function Name: R_UART2_Create
* Description  : This function initializes the UART2 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UART2_Create(void)
{
    ST1 |= _0002_SAUm_CH1_STOP_TRG_ON | _0001_SAUm_CH0_STOP_TRG_ON;
    STMK2 = 1U;     /* disable INTST2 interrupt */
    STIF2 = 0U;     /* clear INTST2 interrupt flag */
    SRMK2 = 1U;     /* disable INTSR2 interrupt */
    SRIF2 = 0U;     /* clear INTSR2 interrupt flag */
    SREMK2 = 1U;    /* disable INTSRE2 interrupt */
    SREIF2 = 0U;    /* clear INTSRE2 interrupt flag */
    /* Set INTSR2 high priority */
    SRPR12 = 0U;
    SRPR02 = 0U;
    /* Set INTST2 low priority */
    STPR12 = 1U;
    STPR02 = 1U;
    SMR10 = _0020_SMR10_DEFAULT_VALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_CLOCK_MODE_CKS | 
            _0002_SAU_MODE_UART | _0000_SAU_TRANSFER_END;
    SCR10 = _0004_SCR10_DEFAULT_VALUE | _8000_SAU_TRANSMISSION | _0000_SAU_TIMING_1 | _0000_SAU_INTSRE_MASK | 
            _0000_SAU_PARITY_NONE | _0080_SAU_LSB | _0010_SAU_STOP_1 | _0003_SAU_LENGTH_8;
    SDR10 = _4C00_UART_DIVISOR;
    NFEN0 |= _10_SAU_RXD2_FILTER_ON;
    SIR11 = _0004_SAU_SIRMN_FECTMN | _0002_SAU_SIRMN_PECTMN | _0001_SAU_SIRMN_OVCTMN;
    SMR11 = _0020_SMR11_DEFAULT_VALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_CLOCK_MODE_CKS | 
            _0100_SAU_TRIGGER_RXD | _0000_SAU_EDGE_FALL | _0002_SAU_MODE_UART | _0000_SAU_TRANSFER_END;
    SCR11 = _0004_SCR11_DEFAULT_VALUE | _4000_SAU_RECEPTION | _0000_SAU_TIMING_1 | _0000_SAU_INTSRE_MASK | 
            _0000_SAU_PARITY_NONE | _0080_SAU_LSB | _0010_SAU_STOP_1 | _0003_SAU_LENGTH_8;
    SDR11 = _4C00_UART_DIVISOR;
    SO1 |= _0001_SAUm_CH0_DATA_OUTPUT_1;
    SOL1 &= (uint16_t)~_0001_SAUm_CHANNEL0_INVERTED;
    SOE1 |= _0001_SAUm_CH0_OUTPUT_ENABLE;
    /* Set RxD2 pin */
    PFSEG5 &= 0xDFU;
    PM5 |= 0x20U;
    /* Set TxD2 pin */
    PFSEG5 &= 0xBFU;
    P5 |= 0x40U;
    PM5 &= 0xBFU;
}
/***********************************************************************************************************************
* Function Name: R_UART2_Start
* Description  : This function starts the UART2 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UART2_Start(void)
{
    SO1 |= _0001_SAUm_CH0_DATA_OUTPUT_1;
    SOE1 |= _0001_SAUm_CH0_OUTPUT_ENABLE;
    SS1 |= _0002_SAUm_CH1_START_TRG_ON | _0001_SAUm_CH0_START_TRG_ON;
    STIF2 = 0U;     /* clear INTST2 interrupt flag */
    SRIF2 = 0U;     /* clear INTSR2 interrupt flag */
    STMK2 = 0U;     /* enable INTST2 interrupt */
    SRMK2 = 0U;     /* enable INTSR2 interrupt */
}
/***********************************************************************************************************************
* Function Name: R_UART2_Stop
* Description  : This function stops the UART2 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UART2_Stop(void)
{
    STMK2 = 1U;     /* disable INTST2 interrupt */
    SRMK2 = 1U;     /* disable INTSR2 interrupt */
    ST1 |= _0002_SAUm_CH1_STOP_TRG_ON | _0001_SAUm_CH0_STOP_TRG_ON;
    SOE1 &= (uint16_t)~_0001_SAUm_CH0_OUTPUT_ENABLE;
    STIF2 = 0U;     /* clear INTST2 interrupt flag */
    SRIF2 = 0U;     /* clear INTSR2 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_UART2_Start_Reception
* Description  : This function starts the UART2 Reception only.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UART2_Start_Reception(void)
{
    SS1 |= _0002_SAUm_CH1_START_TRG_ON;
    SRIF2 = 0U;     /* clear INTSR2 interrupt flag */
    SRMK2 = 0U;     /* enable INTSR2 interrupt */
}

/***********************************************************************************************************************
* Function Name: R_UART2_Stop_Reception
* Description  : This function stops the UART2 Reception only.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UART2_Stop_Reception(void)
{
    SRMK2 = 1U;     /* disable INTSR2 interrupt */
    ST1 |= _0002_SAUm_CH1_STOP_TRG_ON;
    SRIF2 = 0U;     /* clear INTSR2 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_UART2_Receive
* Description  : This function receives UART2 data.
* Arguments    : rx_buf -
*                    receive buffer pointer
*                rx_num -
*                    buffer size
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_UART2_Receive(uint8_t * const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;

    if (rx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        g_uart2_rx_count = 0U;
        g_uart2_rx_length = rx_num;
        gp_uart2_rx_address = rx_buf;
    }

    return (status);
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
MD_STATUS R_UART2_Send(uint8_t * const tx_buf, uint16_t tx_num)
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

/***********************************************************************************************************************
* Function Name: R_CSI30_Create
* Description  : This function initializes the CSI30 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CSI30_Create(void)
{
    ST1 |= _0004_SAUm_CH2_STOP_TRG_ON;
    CSIMK30 = 1U;   /* disable INTCSI30 interrupt */
    CSIIF30 = 0U;   /* clear INTCSI30 interrupt flag */
    /* Set INTCSI30 low priority */
    CSIPR130 = 1U;
    CSIPR030 = 1U;
    SIR12 = _0002_SAU_SIRMN_PECTMN | _0001_SAU_SIRMN_OVCTMN;
    SMR12 = _0020_SMR12_DEFAULT_VALUE | _8000_SAU_CLOCK_SELECT_CK01 | _0000_SAU_CLOCK_MODE_CKS | 
            _0000_SAU_TRIGGER_SOFTWARE | _0000_SAU_MODE_CSI | _0000_SAU_TRANSFER_END;
    SCR12 = _0004_SCR12_DEFAULT_VALUE | _C000_SAU_RECEPTION_TRANSMISSION | _0000_SAU_TIMING_1 | 
            _0000_SAU_INTSRE_MASK | _0000_SAU_PARITY_NONE | _0000_SAU_MSB | _0000_SAU_STOP_NONE | 
            _0003_SAU_LENGTH_8;
    SDR12 = _0200_SAU1_CH2_BAUDRATE_DIVISOR;
    SO1 |= _0400_SAUm_CH2_CLOCK_OUTPUT_1;
    SO1 &= (uint16_t)~(_0004_SAUm_CH2_DATA_OUTPUT_1);
    SOE1 |= _0004_SAUm_CH2_OUTPUT_ENABLE;
    /* Set SI30 pin */
    PFSEG6 &= 0xFEU;
    PM8 |= 0x10U;
    /* Set SO30 pin */
    PFSEG6 &= 0xFDU;
    P8 |= 0x20U;
    PM8 &= 0xDFU;
    /* Set SCK30 pin */
    PFSEG5 &= 0x7FU;
    P5 |= 0x80U;
    PM5 &= 0x7FU;
}
/***********************************************************************************************************************
* Function Name: R_CSI30_Start
* Description  : This function starts the CSI30 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CSI30_Start(void)
{
    SO1 |= _0400_SAUm_CH2_CLOCK_OUTPUT_1;
    SO1 &= (uint16_t)~(_0004_SAUm_CH2_DATA_OUTPUT_1);
    SOE1 |= _0004_SAUm_CH2_OUTPUT_ENABLE;
    SS1 |= _0004_SAUm_CH2_START_TRG_ON;
    CSIIF30 = 0U;   /* clear INTCSI30 interrupt flag */
    CSIMK30 = 0U;   /* enable INTCSI30 interrupt */
}
/***********************************************************************************************************************
* Function Name: R_CSI30_Stop
* Description  : This function stops the CSI30 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CSI30_Stop(void)
{
    CSIMK30 = 1U;   /* disable INTCSI30 interrupt */
    ST1 |= _0004_SAUm_CH2_STOP_TRG_ON;
    SOE1 &= (uint16_t)~_0004_SAUm_CH2_OUTPUT_ENABLE;
    CSIIF30 = 0U;   /* clear INTCSI30 interrupt flag */
}
/***********************************************************************************************************************
* Function Name: R_CSI30_Send_Receive
* Description  : This function sends and receives CSI30 data.
* Arguments    : tx_buf -
*                    transfer buffer pointer
*                tx_num -
*                    buffer size
*                rx_buf -
*                    receive buffer pointer
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_CSI30_Send_Receive(uint8_t * const tx_buf, uint16_t tx_num, uint8_t * const rx_buf)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        g_csi30_tx_count = tx_num;        /* send data count */
        gp_csi30_tx_address = tx_buf;     /* send buffer pointer */
        gp_csi30_rx_address = rx_buf;     /* receive buffer pointer */
        CSIMK30 = 1U;                     /* disable INTCSI30 interrupt */

        if (0U != gp_csi30_tx_address)
        {
            SIO30 = *gp_csi30_tx_address;    /* started by writing data to SDR[7:0] */
            gp_csi30_tx_address++;
        }
        else
        {
            SIO30 = 0xFFU;
        }

        g_csi30_tx_count--;
        CSIMK30 = 0U;                     /* enable INTCSI30 interrupt */
    }

    return (status);

}
/* Start user code for adding. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_UART_CalculateSPS
* Description  : This function calculate the require SPS value to set from input baud rate
*              : Note, this function assume 2 things:
*              :    1. All channels are using  SCK00 (only 4 LSB)
*              :    2. The FRQSEL3 in user option byte is 0
*              : Limitation: 
*              :    1. Can only get from 300 - 38400bps
*              :    2. Support 3MHz - 24MHz only
* Arguments    : sau_std_baud_rate_t baud_rate - 
*                    input baud rate value
* Return Value : uint16_t: SPS value to set
***********************************************************************************************************************/
static uint16_t R_UART_CalculateSPS(sau_std_baud_rate_t baud_rate)
{
    uint16_t sps_value;

    switch (baud_rate)
    {
        case SAU_STD_BAUD_RATE_300:
        {
            sps_value = 0x000A;
        }
        break;
        case SAU_STD_BAUD_RATE_600:
        {
            sps_value = 0x0009;
        }
        break;
        case SAU_STD_BAUD_RATE_1200:
        {
            sps_value = 0x0008;
        }
        break;
        case SAU_STD_BAUD_RATE_2400:
        {
            sps_value = 0x0007;
        }
        break;
        case SAU_STD_BAUD_RATE_4800:
        {
            sps_value = 0x0006;
        }
        break;
        case SAU_STD_BAUD_RATE_9600:
        {
            sps_value = 0x0005;
        }
        break;
        case SAU_STD_BAUD_RATE_19200:
        {
            sps_value = 0x0004;
        }
        break;
        case SAU_STD_BAUD_RATE_38400:
        {
            sps_value = 0x0003;
        }
        break;
        /* 57600 and 115200 not supported for this API due to required changes on SDR also */
        case SAU_STD_BAUD_RATE_57600:
        case SAU_STD_BAUD_RATE_115200:
        default:	/* BAUD_RATE_300 */
        {
            sps_value = 0x000A;
        }
        break;
    }

    /* Offset with value of HOCODIV
     * If not in range of 3MHz-24MHz, clear it to zero
     * Minus and check for HOCODIV range later for safe access
    */
    sps_value -= HOCODIV;
    if (HOCODIV > 3)
    {
        sps_value = 0;
    }
    
    return sps_value;
}

/***********************************************************************************************************************
* Function Name: R_UART0_CheckOperating
* Description  : This function check the operating status of UART0
* Arguments    : None
* Return Value : 0: not operating
*              : 1: operating
***********************************************************************************************************************/
uint8_t R_UART0_CheckOperating(void)
{
    if (((~_0001_SAUm_CH0_OUTPUT_ENABLE) | SOE0) == 0xffff)
    {
        return 1;	//UART is operating
    }
    return 0;	//UART is not operating
}

/***********************************************************************************************************************
* Function Name: R_UART0_SetBaudRate
* Description  : This function configure the UART0 baudrate only
*              : NOTE: Use this function when this peripheral is stop only
* Arguments    : sau_std_baud_rate_t new_baud_rate -
*                    New baud rate
* Return Value : None
***********************************************************************************************************************/
void R_UART0_SetBaudRate(sau_std_baud_rate_t new_baud_rate)
{
    uint16_t sps_value;
    /* Clear old setting */
    SPS0 &= (~_000F_SAU_CK00_fCLK_15);
    
    sps_value = R_UART_CalculateSPS(new_baud_rate);
    
    /* Store the current baud rate */
    g_uart0_current_baud_rate = new_baud_rate;

    /* UART0 using CK00 --> keep value, no need to shift */
    SPS0 |= sps_value;
}

/***********************************************************************************************************************
* Function Name: R_UART0_OnHocoChanged
* Description  : This function configure the UART0 SPS register in case HOCODIV registered changed
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UART0_OnHocoChanged(void)
{
    /* Update the SPS based on the last baud rate setting */
    R_UART0_SetBaudRate(g_uart0_current_baud_rate);
}

/***********************************************************************************************************************
* Function Name: R_UART0_SetConfig
* Description  : This function configure the UART0 (except baudrate).
*              : NOTE: Use this function when this peripheral is stop only
* Arguments    : sau_std_length_t datalen -
*                    Byte data length configuration
*                sau_std_parity_t parity -
*                    Parity configuration
*                sau_std_stopbits_t stopbits -
*                    Stopbits configuration
* Return Value : None
***********************************************************************************************************************/
void R_UART0_SetConfig(sau_std_length_t datalen, sau_std_parity_t parity, sau_std_stopbits_t stopbits)
{
    SCR00 = _8000_SAU_TRANSMISSION | _0000_SAU_INTSRE_MASK | _0080_SAU_LSB | (datalen | parity | stopbits);
    SCR01 = _4000_SAU_RECEPTION | _0000_SAU_INTSRE_MASK | _0080_SAU_LSB | (datalen | parity | stopbits);
}

/***********************************************************************************************************************
* Function Name: R_UART2_CheckOperating
* Description  : This function check the operating status of UART2
* Arguments    : None
* Return Value : 0: not operating
*              : 1: operating
***********************************************************************************************************************/
uint8_t R_UART2_CheckOperating(void)
{
    if (((~_0001_SAUm_CH0_OUTPUT_ENABLE) | SOE1) == 0xffff)
    {
        return 1;	//UART is operating
    }
    return 0;	//UART is not operating
}

/***********************************************************************************************************************
* Function Name: R_UART2_SetBaudRate
* Description  : This function configure the UART2 baudrate only
*              : NOTE: Use this function when this peripheral is stop only
* Arguments    : sau_std_baud_rate_t new_baud_rate -
*                    New baud rate
* Return Value : None
***********************************************************************************************************************/
void R_UART2_SetBaudRate(sau_std_baud_rate_t new_baud_rate)
{
    uint16_t sps_value;
    /* Clear old setting */
    SPS1 &= (~_000F_SAU_CK00_fCLK_15);
    
    sps_value = R_UART_CalculateSPS(new_baud_rate);

    /* Store the current baud rate */
    g_uart2_current_baud_rate = new_baud_rate;
    
    /* UART2 using CK00 --> keep value, no need to shift */
    SPS1 |= sps_value;
}

/***********************************************************************************************************************
* Function Name: R_UART2_OnHocoChanged
* Description  : This function configure the UART2 SPS register in case HOCODIV registered changed
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UART2_OnHocoChanged(void)
{
    /* Update the SPS based on the last baud rate setting */
    R_UART2_SetBaudRate(g_uart2_current_baud_rate);
}

/***********************************************************************************************************************
* Function Name: R_UART2_SetConfig
* Description  : This function configure the UART2 (except baudrate).
*              : NOTE: Use this function when this peripheral is stop only
* Arguments    : sau_std_length_t datalen -
*                    Byte data length configuration
*                sau_std_parity_t parity -
*                    Parity configuration
*                sau_std_stopbits_t stopbits -
*                    Stopbits configuration
* Return Value : None
***********************************************************************************************************************/
void R_UART2_SetConfig(sau_std_length_t datalen, sau_std_parity_t parity, sau_std_stopbits_t stopbits)
{
    SCR10 = _8000_SAU_TRANSMISSION | _0000_SAU_INTSRE_MASK | _0080_SAU_LSB | (datalen | parity | stopbits);
    SCR11 = _4000_SAU_RECEPTION | _0000_SAU_INTSRE_MASK | _0080_SAU_LSB | (datalen | parity | stopbits);
}

/***********************************************************************************************************************
* Function Name: R_UART1_Create
* Description  : This function initializes the UART1 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UART1_Create(void)
{
    ST0 |= _0008_SAUm_CH3_STOP_TRG_ON | _0004_SAUm_CH2_STOP_TRG_ON;
    STMK1 = 1U;     /* disable INTST1 interrupt */
    STIF1 = 0U;     /* clear INTST1 interrupt flag */
    SRMK1 = 1U;     /* disable INTSR1 interrupt */
    SRIF1 = 0U;     /* clear INTSR1 interrupt flag */
    SREMK1 = 1U;    /* disable INTSRE1 interrupt */
    SREIF1 = 0U;    /* clear INTSRE1 interrupt flag */
    /* Set INTSR1 low priority */
    SRPR11 = 1U;
    SRPR01 = 1U;
    /* Set INTST1 low priority */
    STPR11 = 1U;
    STPR01 = 1U;
    SMR02 = _0020_SMR02_DEFAULT_VALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_CLOCK_MODE_CKS | 
            _0002_SAU_MODE_UART | _0000_SAU_TRANSFER_END;
    SCR02 = _0004_SCR02_DEFAULT_VALUE | _8000_SAU_TRANSMISSION | _0000_SAU_TIMING_1 | _0000_SAU_INTSRE_MASK | 
            _0000_SAU_PARITY_NONE | _0080_SAU_LSB | _0010_SAU_STOP_1 | _0003_SAU_LENGTH_8;
    SDR02 = _4C00_UART_DIVISOR;
    NFEN0 |= _04_SAU_RXD1_FILTER_ON;
    SIR03 = _0004_SAU_SIRMN_FECTMN | _0002_SAU_SIRMN_PECTMN | _0001_SAU_SIRMN_OVCTMN;
    SMR03 = _0020_SMR03_DEFAULT_VALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_CLOCK_MODE_CKS | 
            _0100_SAU_TRIGGER_RXD | _0000_SAU_EDGE_FALL | _0002_SAU_MODE_UART | _0000_SAU_TRANSFER_END;
    SCR03 = _0004_SCR03_DEFAULT_VALUE | _4000_SAU_RECEPTION | _0000_SAU_TIMING_1 | _0000_SAU_INTSRE_MASK | 
            _0000_SAU_PARITY_NONE | _0080_SAU_LSB | _0010_SAU_STOP_1 | _0003_SAU_LENGTH_8;
    SDR03 = _4C00_UART_DIVISOR;
    SO0 |= _0004_SAUm_CH2_DATA_OUTPUT_1;
    SOL0 &= (uint16_t)~_0004_SAUm_CHANNEL2_INVERTED;
    SOE0 |= _0004_SAUm_CH2_OUTPUT_ENABLE;
    /* Set RxD1 pin */
    PM0 |= 0x08U;
    /* Set TxD1 pin */
    P0 |= 0x10U;
    PM0 &= 0xEFU;
}
/***********************************************************************************************************************
* Function Name: R_UART1_Start
* Description  : This function starts the UART1 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UART1_Start(void)
{
    SO0 |= _0004_SAUm_CH2_DATA_OUTPUT_1;
    SOE0 |= _0004_SAUm_CH2_OUTPUT_ENABLE;
    SS0 |= _0008_SAUm_CH3_START_TRG_ON | _0004_SAUm_CH2_START_TRG_ON;
    STIF1 = 0U;     /* clear INTST1 interrupt flag */
    SRIF1 = 0U;     /* clear INTSR1 interrupt flag */
    STMK1 = 0U;     /* enable INTST1 interrupt */
    SRMK1 = 0U;     /* enable INTSR1 interrupt */
}
/***********************************************************************************************************************
* Function Name: R_UART1_Stop
* Description  : This function stops the UART1 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UART1_Stop(void)
{
    STMK1 = 1U;     /* disable INTST1 interrupt */
    SRMK1 = 1U;     /* disable INTSR1 interrupt */
    ST0 |= _0008_SAUm_CH3_STOP_TRG_ON | _0004_SAUm_CH2_STOP_TRG_ON;
    SOE0 &= (uint16_t)~_0004_SAUm_CH2_OUTPUT_ENABLE;
    STIF1 = 0U;     /* clear INTST1 interrupt flag */
    SRIF1 = 0U;     /* clear INTSR1 interrupt flag */
}
/***********************************************************************************************************************
* Function Name: R_UART1_Receive
* Description  : This function receives UART1 data.
* Arguments    : rx_buf -
*                    receive buffer pointer
*                rx_num -
*                    buffer size
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_UART1_Receive(uint8_t * const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;

    if (rx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        g_uart1_rx_count = 0U;
        g_uart1_rx_length = rx_num;
        gp_uart1_rx_address = rx_buf;
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: R_UART1_Send
* Description  : This function sends UART1 data.
* Arguments    : tx_buf -
*                    transfer buffer pointer
*                tx_num -
*                    buffer size
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_UART1_Send(uint8_t * const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        gp_uart1_tx_address = tx_buf;
        g_uart1_tx_count = tx_num;
        STMK1 = 1U;    /* disable INTST1 interrupt */
        TXD1 = *gp_uart1_tx_address;
        gp_uart1_tx_address++;
        g_uart1_tx_count--;
        STMK1 = 0U;    /* enable INTST1 interrupt */
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: R_UART1_SetBaudRate
* Description  : This function configure the UART0 baudrate only
*              : NOTE: Use this function when this peripheral is stop only
* Arguments    : sau_std_baud_rate_t new_baud_rate -
*                    New baud rate
* Return Value : None
***********************************************************************************************************************/
void R_UART1_SetBaudRate(sau_std_baud_rate_t new_baud_rate)
{
    uint16_t sps_value;
    /* Clear old setting */
    SPS0 &= (~_000F_SAU_CK00_fCLK_15);
    
    sps_value = R_UART_CalculateSPS(new_baud_rate);
    
    /* Store the current baud rate */
    g_uart1_current_baud_rate = new_baud_rate;

    /* UART0 using CK00 --> keep value, no need to shift */
    SPS0 |= sps_value;
}

/***********************************************************************************************************************
* Function Name: R_UART0_OnHocoChanged
* Description  : This function configure the UART0 SPS register in case HOCODIV registered changed
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UART1_OnHocoChanged(void)
{
    /* Update the SPS based on the last baud rate setting */
    R_UART1_SetBaudRate(g_uart1_current_baud_rate);
}

/***********************************************************************************************************************
* Function Name: R_UART0_SetConfig
* Description  : This function configure the UART0 (except baudrate).
*              : NOTE: Use this function when this peripheral is stop only
* Arguments    : sau_std_length_t datalen -
*                    Byte data length configuration
*                sau_std_parity_t parity -
*                    Parity configuration
*                sau_std_stopbits_t stopbits -
*                    Stopbits configuration
* Return Value : None
***********************************************************************************************************************/
void R_UART1_SetConfig(sau_std_length_t datalen, sau_std_parity_t parity, sau_std_stopbits_t stopbits)
{
    SCR00 = _8000_SAU_TRANSMISSION | _0000_SAU_INTSRE_MASK | _0080_SAU_LSB | (datalen | parity | stopbits);
    SCR01 = _4000_SAU_RECEPTION | _0000_SAU_INTSRE_MASK | _0080_SAU_LSB | (datalen | parity | stopbits);
}

/***********************************************************************************************************************
* Function Name: r_uart2_callback_sendend
* Description  : This function is a callback function when UART2 finishes transmission.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_uart1_callback_sendend(void)
{
	Modbus_Bit_Fields.Modbus_Tx_Completed = 1;
	Silent_Interval = Char_Frame_Delay;
  
}

void R_UART1_RX_ON(void)
{
    RS485_DIR = 0;
    Char_Frame_Delay = 0x04;
    Silent_Interval = 4;   
    Modbus_State = 0; //  ID is not matching ignore frame and Initialize for the next frame 
    R_UART1_Start();
}

/* End user code. Do not edit comment generated here */
