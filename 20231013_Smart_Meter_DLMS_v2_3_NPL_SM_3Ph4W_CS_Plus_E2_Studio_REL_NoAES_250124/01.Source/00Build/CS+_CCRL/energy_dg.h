/******************************************************************************/
/* Copyright (C) 2023 Invendis Ltd. All rights reserved.  */
/****************************************************************************** 
* File Name    : energy_dg.h
* Version      : 1.00
* Description  : Energy Management Module
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 23.08.2023 
******************************************************************************/

#ifndef _ENERGY_DG_H
#define _ENERGY_DG_H

#include "typedef.h"
//#include "energy_constraint.h"
//#include "energy_type.h"
#include "iodefine.h"

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef enum tagEnergySourceMode
{
    ENERGY_SOURCE_GRID_MODE = 1U,
    ENERGY_SOURCE_DG_MODE
} EnergySourceMode_t;

EnergySourceMode_t EnergySourceDetect(void);
EnergySourceMode_t EnergySourceGetMode(void);
void EnergySourceSetMode(EnergySourceMode_t energy_source_mode);

#endif