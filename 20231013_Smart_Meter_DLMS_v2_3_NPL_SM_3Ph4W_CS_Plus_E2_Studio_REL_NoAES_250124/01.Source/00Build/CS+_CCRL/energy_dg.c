/******************************************************************************/
/* Copyright (C) 2023 Invendis Ltd. All rights reserved.  */
/****************************************************************************** 
* File Name    : energy_dg.c
* Version      : 1.00
* Device(s)    : None
* Tool-Chain   : CubeSuite+
* Description  : Energy Management Module
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 23.08.2023 
******************************************************************************/

#include "energy_dg.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define GRID_PRESENT 			P3_bit.no3
/******************************************************************************
Private global variables and functions
******************************************************************************/
static EnergySourceMode_t g_energy_source_mode = ENERGY_SOURCE_GRID_MODE;

EnergySourceMode_t EnergySourceGetMode(void)
{
    return g_energy_source_mode;
}

void EnergySourceSetMode(EnergySourceMode_t energy_source_mode)
{
    g_energy_source_mode = energy_source_mode;
}

EnergySourceMode_t EnergySourceDetect(void)
{
    if ( GRID_PRESENT ) {
		return ENERGY_SOURCE_GRID_MODE;
	}

	return ENERGY_SOURCE_DG_MODE;
}
