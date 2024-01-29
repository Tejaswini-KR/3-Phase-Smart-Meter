/***********************************************************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
************************************************************************************************************************
* File Name    : r_dlms_calendar
* Version      : 1.00
* Description  : Description
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
***********************************************************************************************************************/
// 10.12.2020 New create

#ifndef _R_DLMS_CALENDAR_H
#define _R_DLMS_CALENDAR_H

/**********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_cg_macrodriver.h" 

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define CALENDAR_MAX_NUMBER_SEASON_PROFILE_SUPPORT                               (4)
#define CALENDAR_MAX_NUMBER_WEEK_PROFILE_SUPPORT                                 (4)
#define CALENDAR_MAX_NUMBER_DAY_PROFILE_SUPPORT                                  (4)
#define CALENDAR_MAX_NUMBER_DAY_ACTION_SUPPORT                                   (4)
/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/
uint8_t R_CALENDAR_NameGet(uint8_t * p_data_out, uint8_t is_active,  uint16_t * p_data_length_out);
uint8_t R_CALENDAR_NameSet(uint8_t * p_data_in,  uint16_t * p_data_length_in);
uint8_t R_CALENDAR_SeasonArrayLengthGet(uint16_t * p_data_out, uint8_t is_active);
uint8_t R_CALENDAR_SeasonProfileNameGet(uint8_t * p_data_out, 
	                                    uint8_t is_active,
                                        uint16_t * p_data_length_out, 
										uint16_t array_index);
uint8_t R_CALENDAR_SeasonStartGet(uint8_t * p_data_out, uint8_t is_active, uint16_t array_index);		
uint8_t R_CALENDAR_SeasonWeekNameGet(uint8_t * p_data_out,
                                     uint8_t is_active,
									 uint16_t * p_data_length_out,
									 uint16_t array_index);
uint8_t R_CALENDAR_SeasonArrayLengthSet(uint16_t * p_data_in);
uint8_t R_CALENDAR_SeasonProfileNameSet(uint8_t * p_data_in,  uint16_t * p_data_length_in, uint16_t array_index);
uint8_t R_CALENDAR_SeasonStartSet(uint8_t * p_data_in, uint16_t array_index);
uint8_t R_CALENDAR_SeasonWeekNameSet(uint8_t * p_data_in,  uint16_t * p_data_length_in, uint16_t array_index);
uint8_t R_CALENDAR_WeekArrayLengthGet(uint16_t * p_data_out, uint8_t is_active);
uint8_t R_CALENDAR_WeekProfileNameGet(uint8_t * p_data_out, uint8_t is_active,  uint16_t * p_data_length_out, uint16_t array_index);
uint8_t R_CALENDAR_WeekDataGet(uint8_t * p_data_out, uint8_t is_active, uint16_t array_index);
uint8_t R_CALENDAR_WeekArrayLengthSet(uint16_t * p_data_in);
uint8_t R_CALENDAR_WeekProfileNameSet(uint8_t * p_data_in, uint16_t * p_data_length_in, uint16_t array_index);
uint8_t R_CALENDAR_WeekDataSet(uint8_t * p_data_in, uint16_t array_index);
uint8_t R_CALENDAR_DayArrayLengthGet(uint16_t * p_data_out, uint8_t is_active);
uint8_t R_CALENDAR_DayIdGet(uint8_t * p_data_out, uint8_t is_active, uint16_t array_index);
uint8_t R_CALENDAR_DaySchduleArrayLengthGet(uint16_t * p_data_out, uint8_t is_active, uint16_t parent_array_index);
uint8_t R_CALENDAR_DayScheduleStartTimeGet(uint8_t * p_data_out,
                                           uint8_t is_active,
										   uint16_t parent_array_index,
										   uint16_t schedule_array_index);
uint8_t R_CALENDAR_ShceduleScriptSelectorGet(uint16_t * p_data_out,
                                             uint8_t is_active,
											 uint16_t parent_array_index,
											 uint16_t schedule_array_index);
uint8_t R_CALENDAR_DayScheduleScriptLogicalNameGet(uint8_t * p_data_out,
                                                   uint8_t is_active,
												   uint16_t parent_array_index,
												   uint16_t schedule_array_index);
uint8_t R_CALENDAR_DayArrayLengthSet(uint16_t * p_data_in);
uint8_t R_CALENDAR_DayIdSet(uint8_t * p_data_in,  uint16_t array_index);
uint8_t R_CALENDAR_DayScheduleArrayLengthSet(uint16_t * p_data_in, uint16_t parent_array_index);
uint8_t R_CALENDAR_DayScheduleStartTimeSet(uint8_t * p_data_in, uint16_t parent_array_index, uint16_t schedule_array_index);
uint8_t R_CALENDAR_DayScheduleScriptSelectorSet(uint16_t * p_data_in, uint16_t parent_array_index, uint16_t schedule_array_index);
uint8_t R_CALENDAR_DayScheduleScriptLogicalNameSet(uint8_t * p_data_in,
                                                   uint16_t parent_array_index,
												   uint16_t schedule_array_index);
uint8_t R_CALENDAR_ActivePassiveTimeGet(uint8_t * p_data_out);
uint8_t R_CALENDAR_ActivePassiveTimeSet(uint8_t * p_data_in);		
uint8_t R_CALENDAR_ActivePassiveAction(void);									   
#endif /* _R_DLMS_CALENDAR_H */