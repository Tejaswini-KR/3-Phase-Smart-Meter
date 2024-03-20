/******************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : compiler.h
* Version      : 1.00
* Description  : Compiler specific declaration for IAR compiler
******************************************************************************
* History : DD.MM.YYYY Version Description
******************************************************************************/

#ifndef _COMPILER_H
#define _COMPILER_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/

/* MCU IO & Register Define */
#include "ior5f10npl.h"
#include "ior5f10npl_ext.h"
#include "intrinsics.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/* Bit accessors */
#define SET_BIT(reg, bit_no, bit_value)                 (reg##_bit.no##bit_no = bit_value)
#define BIT_SELECT(reg, bit_no)                         (reg##_bit.no##bit_no)

/* Standard functions*/
#define DI          __disable_interrupt
#define EI          __enable_interrupt
#define HALT        __halt
#define NOP         __no_operation
#define STOP        __stop
#define __nop       __no_operation

/* Near far definition */
#define NEAR_PTR    __near
#define FAR_PTR     __far    
#define NEAR_FUNC   __near_func
#define FAR_FUNC    __far_func
#define VECTOR_INDEX(vector_id)                            (vector_id##_vect)

/* Interuppt specifier */
#define __INTERRUPT  __interrupt

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/

#endif /* _COMPILER_H */
