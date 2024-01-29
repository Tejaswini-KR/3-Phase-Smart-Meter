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
 * Copyright (C) 2013, 2016 Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * File Name    : r_dlms_calendar.c
 * Version      : 1.00
 * Device(s)    : RL78/I1C
 * Tool-Chain   : CCRL
 * H/W Platform : RL78/I1C Energy Meter Platform
 * Description  : 
 ************************************************************************************************************************
 * History      : DD.MM.YYYY Version Description
 ***********************************************************************************************************************/
// 10.12.2020 New create
/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
#include "r_dlms_calendar.h"
/***********************************************************************************************************************
 Macro definitions
 ***********************************************************************************************************************/


/***********************************************************************************************************************
 Typedef definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Imported global variables and functions (from other files)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global variables and functions (to be accessed by other files)
 ***********************************************************************************************************************/
/*
* DLMS OBIS data linkage
*/
/**********************************************************************************************************************
 * Function Name: R_CALENDAR_NameGet      
 * Description  : Function to get name of calendar
 * Arguments    : p_data_out -  pointer of calendar name,
 *                is_active - identify is active or not,
 *                p_data_length_out - pointer of length of calendar name.
 * Return Value : TRUE - get successfully, FALSE - get unsuccessfully.                   
 **********************************************************************************************************************/
uint8_t R_CALENDAR_NameGet(uint8_t * p_data_out, uint8_t is_active,  uint16_t * p_data_length_out)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}
/**********************************************************************************************************************
 * Function Name: R_CALENDAR_NameGet      
 * Description  : Function to set calendar name, this use to set for passive
 * Arguments    : p_data_in -  pointer of calendar name from client to set,
 *                p_data_length_in - pointer of length of calendar name from client
 * Return Value : TRUE - set successfully, FALSE - set unsuccessfully.                   
 **********************************************************************************************************************/
uint8_t R_CALENDAR_NameSet(uint8_t * p_data_in,  uint16_t * p_data_length_in)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}

/*
* Season profile
*/
/**********************************************************************************************************************
 * Function Name: R_CALENDAR_SeasonArrayLengthGet      
 * Description  : Function to get array length
 * Arguments    : p_data_out -  pointer to get length of season array,
 *                is_active - identify is active or not
 * Return Value : TRUE - get successfully, FALSE - get unsuccessfully.                   
 **********************************************************************************************************************/
uint8_t R_CALENDAR_SeasonArrayLengthGet(uint16_t * p_data_out, uint8_t is_active)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}

/**********************************************************************************************************************
 * Function Name: R_CALENDAR_SeasonProfileNameGet      
 * Description  : Function to get season profile name
 * Arguments    : p_data_out -  pointer of season name,
 *                is_active - identify is active or not,
 *                p_data_length_out - pointer of length of season name,
 *                array_index - index in array to get
 * Return Value : TRUE - get successfully, FALSE - get unsuccessfully.                  
 **********************************************************************************************************************/
uint8_t R_CALENDAR_SeasonProfileNameGet(uint8_t * p_data_out, 
	                                    uint8_t is_active,
                                        uint16_t * p_data_length_out, 
										uint16_t array_index)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}
/**********************************************************************************************************************
 * Function Name: R_CALENDAR_SeasonStartGet      
 * Description  : Function to get season start time
 * Arguments    : p_data_out -  pointer of season start(date_time_t),
 *                is_active - identify is active or not,
 *                array_index - index in array to get.
 * Return Value : TRUE - get successfully, FALSE - get unsuccessfully.                  
 **********************************************************************************************************************/
uint8_t R_CALENDAR_SeasonStartGet(uint8_t * p_data_out, uint8_t is_active, uint16_t array_index)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}

/**********************************************************************************************************************
 * Function Name: R_CALENDAR_SeasonWeekNameGet      
 * Description  : Function to get name of season of
 * Arguments    : p_data_out -  pointer of week name of season to get,
 *                is_active - identify is active or not,
 *                p_data_length_out - pointer of length of season name,
 *                array_index - index in array to get
 * Return Value : TRUE - get successfully, FALSE - get unsuccessfully.                  
 **********************************************************************************************************************/
uint8_t R_CALENDAR_SeasonWeekNameGet(uint8_t * p_data_out,
                                     uint8_t is_active,
									 uint16_t * p_data_length_out,
									 uint16_t array_index)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
} 
/**********************************************************************************************************************
 * Function Name: R_CALENDAR_SeasonArrayLengthSet      
 * Description  : Function to set season array length, this use to set for passive.
 * Arguments    : p_data_in -  pointer to length of season array from client to set.
 * Return Value : TRUE - set successfully, FALSE - set unsuccessfully.                   
 **********************************************************************************************************************/
uint8_t R_CALENDAR_SeasonArrayLengthSet(uint16_t * p_data_in)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
} 
/**********************************************************************************************************************
 * Function Name: R_CALENDAR_SeasonProfileNameSet      
 * Description  : Function to set season profile name, this use to set for passive.
 * Arguments    : p_data_in -  pointer of season name from client to set,
 *                p_data_length_in - pointer of length of season name from client,
 *                array_index - index in array to set.
 * Return Value : TRUE - set successfully, FALSE - set unsuccessfully.                   
 **********************************************************************************************************************/
uint8_t R_CALENDAR_SeasonProfileNameSet(uint8_t * p_data_in,  uint16_t * p_data_length_in, uint16_t array_index)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
} 
/**********************************************************************************************************************
 * Function Name: R_CALENDAR_SeasonStartSet      
 * Description  : Function to set season start, this use to set for passive.
 * Arguments    : p_data_in -  pointer of season start(date_time_t) from client to set,
 *                array_index - index in array to set
 * Return Value : TRUE - set successfully, FALSE - set unsuccessfully.                   
 **********************************************************************************************************************/
uint8_t R_CALENDAR_SeasonStartSet(uint8_t * p_data_in, uint16_t array_index)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
} 
/**********************************************************************************************************************
 * Function Name: R_CALENDAR_SeasonWeekNameSet      
 * Description  : Function to set week name of season, this use to set for passive.
 * Arguments    : p_data_in -  pointer of week name of season from client to set,
 *                p_data_length_in - pointer of length of season name from client,
 *                array_index - index in array to set.
 * Return Value : TRUE - set successfully, FALSE - set unsuccessfully.                   
 **********************************************************************************************************************/
uint8_t R_CALENDAR_SeasonWeekNameSet(uint8_t * p_data_in,  uint16_t * p_data_length_in, uint16_t array_index)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}

/*
* Week profile
*/

/**********************************************************************************************************************
 * Function Name: R_CALENDAR_WeekArrayLengthGet      
 * Description  : Function to get array length of week profile array
 * Arguments    : p_data_out -  pointer to get length of array,
 *                is_active - identify is active or not,
 * Return Value : TRUE - get successfully, FALSE - get unsuccessfully.                 
 **********************************************************************************************************************/
uint8_t R_CALENDAR_WeekArrayLengthGet(uint16_t * p_data_out, uint8_t is_active)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
} 
/**********************************************************************************************************************
 * Function Name: R_CALENDAR_SeasonWeekNameGet      
 * Description  : Function to get name of week profile
 * Arguments    : p_data_out -  pointer of data to get,
 *                is_active - identify is active or not, 
 *                p_data_length_out - pointer of length of season name,
 *                array_index - index in array to get
 * Return Value : TRUE - get successfully, FALSE - get unsuccessfully.                  
 **********************************************************************************************************************/
uint8_t R_CALENDAR_WeekProfileNameGet(uint8_t * p_data_out, uint8_t is_active,  uint16_t * p_data_length_out, uint16_t array_index)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
} 
/**********************************************************************************************************************
 * Function Name: R_CALENDAR_SeasonWeekNameGet      
 * Description  : Function to get all data of week day
 * Arguments    : p_data_out -  pointer of data which contains all days as array[7],
 *                is_active - identify is active or not,
 *                array_index - index in array to get
 * Return Value : TRUE - get successfully, FALSE - get unsuccessfully.                  
 **********************************************************************************************************************/
uint8_t R_CALENDAR_WeekDataGet(uint8_t * p_data_out, uint8_t is_active, uint16_t array_index)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
} 
/**********************************************************************************************************************
 * Function Name: R_CALENDAR_WeekArrayLengthSet      
 * Description  : Function to set week profile array length, this use to set for passive.
 * Arguments    : p_data_in -  pointer to length of array from client to set.
 * Return Value : TRUE - set successfully, FALSE - set unsuccessfully.                   
 **********************************************************************************************************************/
uint8_t R_CALENDAR_WeekArrayLengthSet(uint16_t * p_data_in)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
} 
/**********************************************************************************************************************
 * Function Name: R_CALENDAR_WeekProfileNameSet      
 * Description  : Function to set week profile name, this use to set for passive.
 * Arguments    : p_data_out -  pointer of data from client to set,
 *                p_data_length_in - pointer of length of season name from client,
 *                array_index - index in array to set
 * Return Value : TRUE - set successfully, FALSE - set unsuccessfully.                   
 **********************************************************************************************************************/
uint8_t R_CALENDAR_WeekProfileNameSet(uint8_t * p_data_in, uint16_t * p_data_length_in, uint16_t array_index)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
} 
/**********************************************************************************************************************
 * Function Name: R_CALENDAR_WeekDataSet      
 * Description  : Function to set all week data(set for all day in week), this use to set for passive.
 * Arguments    : p_data_out -  pointer of data which contains all days as array[7] from client to set,
 *                array_index - index in array to set
 * Return Value : TRUE - set successfully, FALSE - set unsuccessfully.                   
 **********************************************************************************************************************/
uint8_t R_CALENDAR_WeekDataSet(uint8_t * p_data_in, uint16_t array_index)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
} 

/*
* Day profile
*/

/**********************************************************************************************************************
 * Function Name: R_CALENDAR_SeasonWeekNameGet      
 * Description  : Function to get day profile array length
 * Arguments    : p_data_out -  pointer to get length of array,
 *                is_active - identify is active or not.
 * Return Value : TRUE - get successfully, FALSE - get unsuccessfully.                 
 **********************************************************************************************************************/
uint8_t R_CALENDAR_DayArrayLengthGet(uint16_t * p_data_out, uint8_t is_active)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}
/**********************************************************************************************************************
 * Function Name: R_CALENDAR_DayIdGet      
 * Description  : Function to get day profile array length
 * Arguments    : p_data_out -  pointer of data to get,
 *                is_active - identify is active or not, 
 *                array_index - index in array to get
 * Return Value : TRUE - get successfully, FALSE - get unsuccessfully.                 
 **********************************************************************************************************************/
uint8_t R_CALENDAR_DayIdGet(uint8_t * p_data_out, uint8_t is_active, uint16_t array_index)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}
/**********************************************************************************************************************
 * Function Name: R_CALENDAR_DaySchduleArrayLengthGet      
 * Description  : Function to get day schedule array length.
 * Arguments    : p_data_out -  pointer of length of day schedule to get,
 *                is_active - identify is active or not,
 *                parent_array_index - index of day profile.
 * Return Value : TRUE - get successfully, FALSE - get unsuccessfully.                 
 **********************************************************************************************************************/
uint8_t R_CALENDAR_DaySchduleArrayLengthGet(uint16_t * p_data_out, uint8_t is_active, uint16_t parent_array_index)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}
/**********************************************************************************************************************
 * Function Name: R_CALENDAR_DayScheduleStartTimeGet      
 * Description  : Function to get start time of day schedule
 * Arguments    : p_data_out -  pointer of start time to get,
 *                is_active - identify is active or not,
 *                parent_array_index - index of day profile,
 *                schedule_array_index - index of schedule.
 * Return Value : TRUE - get successfully, FALSE - get unsuccessfully.                 
 **********************************************************************************************************************/
uint8_t R_CALENDAR_DayScheduleStartTimeGet(uint8_t * p_data_out,
                                           uint8_t is_active,
										   uint16_t parent_array_index,
										   uint16_t schedule_array_index)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}
/**********************************************************************************************************************
 * Function Name: R_CALENDAR_ShceduleScriptSelectorGet      
 * Description  : Function to get script selector of schedule
 * Arguments    : p_data_out -  pointer of start time to get,
 *                is_active - identify is active or not,
 *                parent_array_index - index of day profile,
 *                schedule_array_index - index of schedule.
 * Return Value : TRUE - get successfully, FALSE - get unsuccessfully.                 
 **********************************************************************************************************************/
uint8_t R_CALENDAR_ShceduleScriptSelectorGet(uint16_t * p_data_out,
                                             uint8_t is_active,
											 uint16_t parent_array_index,
											 uint16_t schedule_array_index)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}
/**********************************************************************************************************************
 * Function Name: R_CALENDAR_DayScheduleScriptLogicalNameGet      
 * Description  : Function to get script logical name of schedule
 * Arguments    : p_data_out -  pointer of script logical name to get,
 *                is_active - identify is active or not,
 *                parent_array_index - index of day profile,
 *                schedule_array_index - index of schedule.
 * Return Value : TRUE - get successfully, FALSE - get unsuccessfully.                 
 **********************************************************************************************************************/
uint8_t R_CALENDAR_DayScheduleScriptLogicalNameGet(uint8_t * p_data_out,
                                                   uint8_t is_active,
												   uint16_t parent_array_index,
												   uint16_t schedule_array_index)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}

/**********************************************************************************************************************
 * Function Name: R_CALENDAR_DayArrayLengthSet      
 * Description  : Function to set day profile array length, this use to set for passive.
 * Arguments    : p_data_in -  pointer of length of day array from to set. 
 * Return Value : TRUE - set successfully, FALSE - set unsuccessfully.                   
 **********************************************************************************************************************/
uint8_t R_CALENDAR_DayArrayLengthSet(uint16_t * p_data_in)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}
/**********************************************************************************************************************
 * Function Name: R_CALENDAR_DayIdSet      
 * Description  : Function to set day ID, this use to set for passive.
 * Arguments    : p_data_in -  pointer of data from client to set,
 *                array_index - index in array to set. 
 * Return Value : TRUE - set successfully, FALSE - set unsuccessfully.                   
 **********************************************************************************************************************/ 
uint8_t R_CALENDAR_DayIdSet(uint8_t * p_data_in,  uint16_t array_index) 
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}
/**********************************************************************************************************************
 * Function Name: R_CALENDAR_DayScheduleArrayLengthSet      
 * Description  : Function to set schedule array length, this use to set for passive.
 * Arguments    : p_data_in -  pointer of length of day schedule from client to set,
 *                parent_array_index - index of day profile.
 * Return Value : TRUE - set successfully, FALSE - set unsuccessfully.                   
 **********************************************************************************************************************/ 
uint8_t R_CALENDAR_DayScheduleArrayLengthSet(uint16_t * p_data_in, uint16_t parent_array_index)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}
/**********************************************************************************************************************
 * Function Name: R_CALENDAR_DayScheduleStartTimeSet      
 * Description  : Function to set schedule start time, this use to set for passive.
 * Arguments    : p_data_in -  pointer of start time from client to set,
 *                parent_array_index - index of day profile,
 *                schedule_array_index - index of schedule.
 * Return Value : TRUE - set successfully, FALSE - set unsuccessfully.                   
 **********************************************************************************************************************/ 
uint8_t R_CALENDAR_DayScheduleStartTimeSet(uint8_t * p_data_in, uint16_t parent_array_index, uint16_t schedule_array_index) 
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}
/**********************************************************************************************************************
 * Function Name: R_CALENDAR_DayShceduleScriptSelectorSet      
 * Description  : Function to set script selector, this use to set for passive.
 * Arguments    : p_data_in -  pointer of script selector from client to set,
 *                parent_array_index - index of day profile,
 *                schedule_array_index - index of schedule.
 * Return Value : TRUE - set successfully, FALSE - set unsuccessfully.                   
 **********************************************************************************************************************/ 
uint8_t R_CALENDAR_DayScheduleScriptSelectorSet(uint16_t * p_data_in, uint16_t parent_array_index, uint16_t schedule_array_index)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}
/**********************************************************************************************************************
 * Function Name: R_CALENDAR_DayScheduleScriptLogicalNameSet      
 * Description  : Function to set schedule scription logical name, this use to set for passive.
 * Arguments    : p_data_out -  pointer of script logical name from client to set,
 *                parent_array_index - index of day profile,
 *                schedule_array_index - index of schedule.
 * Return Value : TRUE - set successfully, FALSE - set unsuccessfully.                   
 **********************************************************************************************************************/ 
uint8_t R_CALENDAR_DayScheduleScriptLogicalNameSet(uint8_t * p_data_in,
                                                   uint16_t parent_array_index,
												   uint16_t schedule_array_index)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}

/*
* Active passive calendar
*/
/**********************************************************************************************************************
 * Function Name: R_CALENDAR_ActivePassiveTimeGet      
 * Description  : Function to get active passive calendar time.
 * Arguments    :  p_data_out -  pointer of passive active time(date_time_t). 
 * Return Value : TRUE - get successfully, FALSE - get unsuccessfully.                   
 **********************************************************************************************************************/ 
uint8_t R_CALENDAR_ActivePassiveTimeGet(uint8_t * p_data_out)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}
/**********************************************************************************************************************
 * Function Name: R_CALENDAR_ActivePassiveTimeSet      
 * Description  : Function to set active passive calendar time.
 * Arguments    : p_data_in -  pointer of passive active time(date_time_t) from client to set.
 * Return Value : TRUE - set successfully, FALSE - set unsuccessfully.                   
 **********************************************************************************************************************/ 
uint8_t R_CALENDAR_ActivePassiveTimeSet(uint8_t * p_data_in)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}

/*
* Active passive action
*/
/**********************************************************************************************************************
 * Function Name: R_CALENDAR_ActivePassiveAction      
 * Description  : Function to copy data from passive to active
 * Arguments    : void
 * Return Value : TRUE - action successfully, FALSE - action unsuccessfully.                   
 **********************************************************************************************************************/ 
uint8_t R_CALENDAR_ActivePassiveAction(void)
{
	/* TODO - Implement code for data linkage */
	return FALSE;
}
/***********************************************************************************************************************
 Private global variables and functions
 ***********************************************************************************************************************/
