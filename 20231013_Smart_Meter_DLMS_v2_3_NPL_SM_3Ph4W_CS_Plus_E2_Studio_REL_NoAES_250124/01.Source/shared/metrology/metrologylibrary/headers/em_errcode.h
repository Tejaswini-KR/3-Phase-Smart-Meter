/******************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : em_errcode.h
* Version      : 1.00
* Description  : EM Core Error Code Middleware Header file
******************************************************************************
* History : DD.MM.YYYY Version Description
******************************************************************************/

#ifndef _EM_ERROR_CODE_H
#define _EM_ERROR_CODE_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/

/******************************************************************************
Macro definitions
******************************************************************************/
/* Status Code */
#define EM_OK                                       (0x00)    /* OK */
/* 1 reserved: legacy status code (state copying)*/
#define EM_ACCUMULATING                             (0x01)
#define EM_CALIBRATING                              (0x02)

/* Error Code */
#define EM_ERROR                                    (0x80)
#define EM_ERROR_PARAMS                             (0x81)
#define EM_ERROR_NULL_PARAMS                        (0x82)
#define EM_ERROR_NOT_INITIALIZED                    (0x83)
#define EM_ERROR_NOT_RUNNING                        (0x84)
#define EM_ERROR_STILL_RUNNING                      (0x85)
/* EM_Start error code */
#define EM_ERROR_STARTUP_ADC                        (0x8D)
#define EM_ERROR_STARTUP_TIMER                      (0x8E)
#define EM_ERROR_STARTUP_RTC                        (0x8F)

/* EM_Init error code */
#define EM_ERROR_PLATFORM_PROPERTY_NULL             (0x90)
#define EM_ERROR_PLATFORM_PROPERTY_TARGET_FREQ      (0x91)
#define EM_ERROR_SW_PROPERTY_NULL                   (0x92)
#define EM_ERROR_SW_PROPERTY_ROUNDING               (0x93)
#define EM_ERROR_SW_PROPERTY_GAIN                   (0x94)
#define EM_ERROR_SW_PROPERTY_OPERATION              (0x95)
#define EM_ERROR_SW_PROPERTY_SAG_SWELL              (0x96)

/* EM_SetCalibInfo | EM_Init error code */
#define EM_ERROR_CALIB_NULL                         (0xA0)
#define EM_ERROR_CALIB_PARAMS_COMMON                (0xA1)
#define EM_ERROR_CALIB_PARAMS_LINE1                 (0xA2)
#define EM_ERROR_CALIB_PARAMS_LINE2                 (0xA3)
#define EM_ERROR_CALIB_PARAMS_LINE3                 (0xA4)
#define EM_ERROR_CALIB_PARAMS_NEUTRAL               (0xA5)


/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/

#endif /* _EM_ERROR_CODE_H */
