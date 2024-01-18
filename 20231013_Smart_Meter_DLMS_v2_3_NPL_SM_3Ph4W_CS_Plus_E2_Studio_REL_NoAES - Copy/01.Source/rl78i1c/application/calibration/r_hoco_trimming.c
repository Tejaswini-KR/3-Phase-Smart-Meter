/**********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2019 Renesas Electronics Corporation. All rights reserved.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * File Name    : r_calib.c
 * Version      : 1.0
 * Description  : Main calibration module
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : 01.04.2013 First release
 *         : 31.12.2019 Revised for new metrology
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "r_calib.h"            /* Calibration */
#include "r_calib_sampling.h"   /* Accumulation of calibration */
#include "r_hoco_trimming.h"
#include "wrp_em_wdt.h"
#include "wrp_em_mcu.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Local Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
Imported global variables and functions (from other files)
 *********************************************************************************************************************/
extern r_calib_system g_calib_system;
/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Private (static) variables and functions
 *********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name : R_CALIB_HocoTrimming
* Description   : Trimming the HOCO and calculate actual sampling frequency of DSAD
* Arguments     : None
* Return Value  : uint8_t
 *********************************************************************************************************************/
uint8_t R_CALIB_HocoTrimming(void)
{
    uint32_t fih_count;
    uint32_t fih_expected_count;
    float32_t fih_error_percentage;
    uint16_t fih_trimming_retry_count = 64;      /* Max 64 times for 6bit HIOTRM register */

    /* HOCO Trimming before fs calibration (measurement) */
    fih_expected_count = (g_calib_system.p_args->cpu_clock * 1000000) / 64; /* Counting period fixed to 64Hz as below FMC settings */
	/* Loop to measure HOCO clock and trim until within range of exceed max retry */
    while (fih_trimming_retry_count > 0)
    {
        /* Measure the HOCO using FMC */
        FMCEN = 1U;     /* enables input clock supply */
        FMS = 0U;       /* stops the frequency measurement circuit */
        FMCKS = 0x02;   /* Select fIH as count source */
        FMCTL = 0x01;   /* Fixed fsx/2^9 = 64Hz, 15.625ms */
    	FMS = 1U;       /* operates the frequency measurement circuit */
    	
        /* Wait until measurement done */
    	while (FMS == 1)
    	{
    		EM_WDT_Restart();
    	}
        /* Read measured fIH */
        fih_count = ((uint32_t)FMCRH<<16) | FMCRL;

        /* Turn off FMC */
    	FMCEN = 0;

        fih_error_percentage = (((float32_t)fih_count - (float32_t)fih_expected_count) / (float32_t)fih_expected_count) * 100.0f;

        if (fih_error_percentage < -R_CALIB_HOCO_TRIMMING_ERROR_THRESHOLD)
        {
            /* Slower than expected, speed up HOCO */
            HIOTRM++;
        }
        else if (fih_error_percentage > R_CALIB_HOCO_TRIMMING_ERROR_THRESHOLD)
        {
            /* Faster than expected, slow down HOCO */
            HIOTRM--;
        }
        else
        {
            /* Within range, keep this value of trimming and break */
			break;
        }
        
        /* Wait 15.625ms before next measurement for HOCO trimming takes effect */
        EM_MCU_Delay(15625);
		
		fih_trimming_retry_count--;
    }

    return R_CALIB_OK;
}

