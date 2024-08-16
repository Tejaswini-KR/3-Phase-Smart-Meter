#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include <string.h>
#include "uart.h"
#include "r_cg_rtc.h"
#include "em_display.h" 

#ifndef SIMULATION
//#include "energy_internal.h"
#else
#include <stdlib.h>
#endif

unsigned char esc_char[] = "\r\x1a"; 
void Wait_ms(unsigned int Required_Delay);

#define Protocol_Identifier			"$BX"
#define Protocol_Version			1.1
#define Number_of_Fields			50
#define	Dev_Iden					10001
#define Record_Type					1
#define Meter_SlaveID				10001

typedef enum {
	GSM_DATA_START = 0,
	
	//GSM_DATA_DATE_TIME,
	//GSM_DATA_DUMMY_FILL,
	GSM_DATA_VOLTAGE,
	GSM_DATA_PHASE_CURRENT,
	GSM_DATA_NEUTRAL_CURRENT,
//	GSM_DATA_PHASE_POWERFACTOR,
//	GSM_DATA_NEUTRAL_POWERFACTOR,
//	GSM_DATA_FREQUENCY,
	
//	GSM_DATA_INST_ACTIVEPOWER_PHASE,
//	GSM_DATA_INST_REACTIVEPOWER_PHASE,
//	GSM_DATA_INST_FUNDAMENTAL_ACTIVEPOWER_PHASE,
//	GSM_DATA_INST_APARENTPOWER_PHASE,
//	GSM_DATA_INST_ACTIVEPOWER_NEUTRAL,
//	GSM_DATA_INST_REACTIVEPOWER_NEUTRAL,
//	GSM_DATA_INST_FUNDAMENTAL_ACTIVEPOWER_NEUTRAL,
//	GSM_DATA_INST_APPARENTPOWER_NEUTRAL,
	
//	GSM_DATA_IMPORT_ACTIVE_ENERGY,
//	GSM_DATA_IMPORT_CAPCITIVEREACTIVE_ENERGY,
//	GSM_DATA_IMPORT_INDUCTIVEREACTIVE_ENERGY,
//	GSM_DATA_IMPORT_APPARENT_ENERGY,
//	GSM_DATA_EXPORT_ACTIVE_ENERGY,
//	GSM_DATA_EXPORT_CAPCITIVEREACTIVE_ENERGY,
//	GSM_DATA_EXPORT_INDUCTIVEREACTIVE_ENERGY,
//	GSM_DATA_EXPORT_APPARENT_ENERGY,
	
//	GSM_DATA_IMPORT_ACTIVE_ENERGY_TARIFF,
//	GSM_DATA_IMPORT_CAPCITIVEREACTIVE_ENERGY_TARIFF,
//	GSM_DATA_IMPORT_INDUCTIVEREACTIVE_ENERGY_TARIFF,
//	GSM_DATA_IMPORT_APPARENT_ENERGY_TARIFF,
//	GSM_DATA_EXPORT_ACTIVE_ENERGY_TARIFF,
//	GSM_DATA_EXPORT_CAPCITIVEREACTIVE_ENERGY_TARIFF,
//	GSM_DATA_EXPORT_INDUCTIVEREACTIVE_ENERGY_TARIFF,
//	GSM_DATA_EXPORT_APPARENT_ENERGY_TARIFF,
	
//	GSM_DATA_ACTIVE_MAXDEMAND,
//	GSM_DATA_CAPACITIVEREACTIVE_MAXDEMAND,
//	GSM_DATA_INDUCTIVEREACTIVE_MAXDEMAND,
//	GSM_DATA_APPARENT_MAXDEMAND,
	
//	GSM_DATA_RELAY_STATUS,
	
	GSM_DATA_END
	
} GsmDataItems_t;

typedef enum {
	GSM_DATA_NONE = 0,
	GSM_DATA_FLOAT,
	GSM_DATA_STR
} GsmDataItemType_t;

#define GSM_DATA_FOOTER_LEN		10
//#define GSM_DATA_SEND_AT_ONCE	1

uint8_t Gsm_PrepareData(char cmdBuffer[], uint16_t cmd_buffer_len)
{
    uint8_t current_tariff;
    uint8_t return_status;

    uint16_t data_len = 0;
	
    uint16_t cmd_buf_index = 0;
	uint16_t loop_index = 0;
	uint16_t loop_item = 0;
	
	uint32_t item_value_int = 0;
    float item_value_float = 0.0;

	GsmDataItemType_t item_type = GSM_DATA_FLOAT;
	
	uint8_t relay_status = 1;
	TIME_DATA_INFO              	disp_data;
	rtc_calendarcounter_value_t 	rtc_data;
	
    cmd_buf_index = sprintf(&cmdBuffer[cmd_buf_index], "$BX,1.1,41,10005,");
    cmdBuffer[cmd_buf_index] = 0;
	
#ifndef GSM_DATA_SEND_AT_ONCE
    SendData(cmdBuffer, cmd_buf_index, FALSE);
	cmd_buf_index = 0;
#endif

	for (loop_index = GSM_DATA_START + 1; loop_index < GSM_DATA_END; loop_index ++)
	{
#ifndef SIMULATION
        switch (loop_index)
        {				
			
//		case GSM_DATA_DATE_TIME:
//			item_type = GSM_DATA_STR;
//			R_RTC_Get_CalendarCounterValue(&rtc_data);
//			data_len = sprintf(&cmdBuffer[cmd_buf_index], "%02x%02x%02x%02x%02x%02x,", 
//						rtc_data.rdaycnt, rtc_data.rmoncnt, rtc_data.ryrcnt,
//						rtc_data.rhrcnt, rtc_data.rmincnt, rtc_data.rseccnt);
//			break;
			
//		case GSM_DATA_DUMMY_FILL:
//			item_type = GSM_DATA_STR;
//			data_len = sprintf(&cmdBuffer[cmd_buf_index], "0,1,2,10005,");
//			break;
			
			case GSM_DATA_VOLTAGE:
				item_type = GSM_DATA_FLOAT;
            	item_value_float = EM_GetVoltageRMS();
				break;
			
			case GSM_DATA_PHASE_CURRENT:
				item_type = GSM_DATA_FLOAT;
            	item_value_float = EM_GetCurrentRMS(EM_LINE_PHASE);
				break;
			
			case GSM_DATA_NEUTRAL_CURRENT:
			    item_type = GSM_DATA_FLOAT;
            item_value_float = EM_GetCurrentRMS(EM_LINE_NEUTRAL);
				break; 
			
//			case GSM_DATA_PHASE_POWERFACTOR:
//				item_type = GSM_DATA_FLOAT;
//            item_value_float = EM_GetPowerFactor(EM_LINE_PHASE);
//				break; 
			
//			case GSM_DATA_NEUTRAL_POWERFACTOR:
//				item_type = GSM_DATA_FLOAT;
//            item_value_float = EM_GetPowerFactor(EM_LINE_NEUTRAL);
//			break; 
			
//			case GSM_DATA_FREQUENCY:
//				item_type = GSM_DATA_FLOAT;
//            item_value_float = EM_GetLineFrequency();
//			break;
			
//			case GSM_DATA_INST_ACTIVEPOWER_PHASE:
//				item_type = GSM_DATA_FLOAT;
//            item_value_float = EM_GetActivePower(EM_LINE_PHASE);
//			break;
			
//			case GSM_DATA_INST_REACTIVEPOWER_PHASE:
//				item_type = GSM_DATA_FLOAT;
//            item_value_float = EM_GetReactivePower(EM_LINE_PHASE);
//			break;
			
//			case GSM_DATA_INST_FUNDAMENTAL_ACTIVEPOWER_PHASE:
//				item_type = GSM_DATA_FLOAT;
//            item_value_float = EM_GetFundamentalActivePower(EM_LINE_PHASE);
//			break;
			
//			case GSM_DATA_INST_APARENTPOWER_PHASE:
//				item_type = GSM_DATA_FLOAT;
//            item_value_float = EM_GetApparentPower(EM_LINE_PHASE);
//			break;
			
//			case GSM_DATA_INST_ACTIVEPOWER_NEUTRAL:
//				item_type = GSM_DATA_FLOAT;
//            item_value_float = EM_GetActivePower(EM_LINE_NEUTRAL);
//			break;
			
//			case GSM_DATA_INST_REACTIVEPOWER_NEUTRAL:
//				item_type = GSM_DATA_FLOAT;
//            item_value_float = EM_GetReactivePower(EM_LINE_NEUTRAL);
//			break;
			
//			case GSM_DATA_INST_FUNDAMENTAL_ACTIVEPOWER_NEUTRAL:
//				item_type = GSM_DATA_FLOAT;
//            item_value_float = EM_GetFundamentalActivePower(EM_LINE_NEUTRAL);
//			break;
			
//			case GSM_DATA_INST_APPARENTPOWER_NEUTRAL:
//				item_type = GSM_DATA_FLOAT;
//            item_value_float = EM_GetApparentPower(EM_LINE_NEUTRAL);
//			break;
			
//			case GSM_DATA_IMPORT_ACTIVE_ENERGY:
//				item_type = GSM_DATA_FLOAT;
//            item_value_float = ENERGY_GetImportActiveEnergyTotal();
//			break;
			
//			case GSM_DATA_IMPORT_CAPCITIVEREACTIVE_ENERGY:
//				item_type = GSM_DATA_FLOAT;
//            item_value_float = ENERGY_GetImportCapacitiveReactiveEnergyTotal();
//			break;
			
//			case GSM_DATA_IMPORT_INDUCTIVEREACTIVE_ENERGY:
//				item_type = GSM_DATA_FLOAT;
//            item_value_float = ENERGY_GetImportInductiveReactiveEnergyTotal();
//			break;
			
//			case GSM_DATA_IMPORT_APPARENT_ENERGY:
//				item_type = GSM_DATA_FLOAT;
//            item_value_float = ENERGY_GetImportApparentEnergyTotal();
//			break;
			
//			case GSM_DATA_EXPORT_ACTIVE_ENERGY:
//				item_type = GSM_DATA_FLOAT;
//            item_value_float = ENERGY_GetExportActiveEnergyTotal();
//			break;
			
//			case GSM_DATA_EXPORT_CAPCITIVEREACTIVE_ENERGY:
//				item_type = GSM_DATA_FLOAT;
//            item_value_float = ENERGY_GetExportCapacitiveReactiveEnergyTotal();
//			break;
			
//			case GSM_DATA_EXPORT_INDUCTIVEREACTIVE_ENERGY:
//				item_type = GSM_DATA_FLOAT;
//            item_value_float = ENERGY_GetExportInductiveReactiveEnergyTotal();
//			break;
			
//			case GSM_DATA_EXPORT_APPARENT_ENERGY:
//				item_type = GSM_DATA_FLOAT;
//            item_value_float = ENERGY_GetExportApparentEnergyTotal();
//			break;
			
//			case GSM_DATA_IMPORT_ACTIVE_ENERGY_TARIFF:
//					item_type = GSM_DATA_FLOAT;
//				    /* Get the current active active tariff */
//    				current_tariff = ENERGY_TARIFF_GetCurrentTariff();

//    				/* Get active energy at active tariff */
//            return_status = ENERGY_GetImportActiveEnergyTariff(current_tariff, &item_value_float);
//    				if (return_status != EM_OK)
//    				{
//                item_value_float = 0.0;
//    				}
//			break;
			
//			case GSM_DATA_IMPORT_CAPCITIVEREACTIVE_ENERGY_TARIFF:
//					item_type = GSM_DATA_FLOAT;
//				/* Get the current active active tariff */
//    				current_tariff = ENERGY_TARIFF_GetCurrentTariff();

//    				/* Get active energy at active tariff */
//            return_status = ENERGY_GetImportCapacitiveReactiveEnergyTariff(current_tariff, &item_value_float);
//    				if (return_status != EM_OK)
//    				{
//                item_value_float = 0.0;
//    				} 
//			break;
			
//			case GSM_DATA_IMPORT_INDUCTIVEREACTIVE_ENERGY_TARIFF:
//					item_type = GSM_DATA_FLOAT;
//				/* Get the current active active tariff */
//    				current_tariff = ENERGY_TARIFF_GetCurrentTariff();

//    				/* Get active energy at active tariff */
//            return_status = ENERGY_GetImportInductiveReactiveEnergyTariff(current_tariff, &item_value_float);
//    				if (return_status != EM_OK)
//    				{
//                item_value_float = 0.0;
//    				} 
//			break;
			
//			case GSM_DATA_IMPORT_APPARENT_ENERGY_TARIFF:
//					item_type = GSM_DATA_FLOAT;
//				/* Get the current active active tariff */
//    				current_tariff = ENERGY_TARIFF_GetCurrentTariff();

//    				/* Get active energy at active tariff */
//            return_status = ENERGY_GetImportApparentEnergyTariff(current_tariff, &item_value_float);
//    				if (return_status != EM_OK)
//    				{
//                item_value_float = 0.0;
//    				} 
//			break;
			
//			case GSM_DATA_EXPORT_ACTIVE_ENERGY_TARIFF:
//					item_type = GSM_DATA_FLOAT;
//				/* Get the current active active tariff */
//    				current_tariff = ENERGY_TARIFF_GetCurrentTariff();

//    				/* Get active energy at active tariff */
//            return_status = ENERGY_GetExportActiveEnergyTariff(current_tariff, &item_value_float);
//    				if (return_status != EM_OK)
//    				{
//                item_value_float = 0.0;
//    				} 
//			break;
			
//			case GSM_DATA_EXPORT_CAPCITIVEREACTIVE_ENERGY_TARIFF:
//					item_type = GSM_DATA_FLOAT;
//				/* Get the current active active tariff */
//    				current_tariff = ENERGY_TARIFF_GetCurrentTariff();

//    				/* Get active energy at active tariff */
//            return_status = ENERGY_GetExportCapacitiveReactiveEnergyTariff(current_tariff, &item_value_float);
//    				if (return_status != EM_OK)
//    				{
//                item_value_float = 0.0;
//    				}
//			break;
			
//			case GSM_DATA_EXPORT_INDUCTIVEREACTIVE_ENERGY_TARIFF:
//					item_type = GSM_DATA_FLOAT;
//				/* Get the current active active tariff */
//    				current_tariff = ENERGY_TARIFF_GetCurrentTariff();

//    				/* Get active energy at active tariff */
//            return_status = ENERGY_GetExportInductiveReactiveEnergyTariff(current_tariff, &item_value_float);
//    				if (return_status != EM_OK)
//    				{
//                item_value_float = 0.0;
//    				} 
//			break;
			
//			case GSM_DATA_EXPORT_APPARENT_ENERGY_TARIFF:
//					item_type = GSM_DATA_FLOAT;
//				/* Get the current active active tariff */
//    				current_tariff = ENERGY_TARIFF_GetCurrentTariff();

//    				/* Get active energy at active tariff */
//            return_status = ENERGY_GetExportApparentEnergyTariff(current_tariff, &item_value_float);
//    				if (return_status != EM_OK)
//    				{
//                item_value_float = 0.0;
//    				} 
//			break;
			
//			case GSM_DATA_ACTIVE_MAXDEMAND:
//				item_type = GSM_DATA_FLOAT;
//            item_value_float = ENERGY_GetActiveMaxDemand();
//			break;
			
//			case GSM_DATA_CAPACITIVEREACTIVE_MAXDEMAND:
//				item_type = GSM_DATA_FLOAT;
//            item_value_float = ENERGY_GetCapacitiveReactiveMaxDemand();
//			break;
			
//			case GSM_DATA_INDUCTIVEREACTIVE_MAXDEMAND:
//				item_type = GSM_DATA_FLOAT;
//            item_value_float = ENERGY_GetInductiveReactiveMaxDemand();
//			break;
			
//			case GSM_DATA_APPARENT_MAXDEMAND:
//				item_type = GSM_DATA_FLOAT;
//            item_value_float = ENERGY_GetApparentMaxDemand();
//			break;
		}
#else
        item_value_float = rand() / 100.0;
#endif
		
       	switch(item_type)
		{
		case GSM_DATA_FLOAT:
			data_len = sprintf(&cmdBuffer[cmd_buf_index], "%.2f,", item_value_float);
			break;
		case GSM_DATA_STR:
		    // do nothing
			break;
		}

		cmd_buf_index += data_len;
		cmdBuffer[cmd_buf_index] = 0;

#ifndef GSM_DATA_SEND_AT_ONCE
		if ( item_type != GSM_DATA_NONE ) {
			SendData(cmdBuffer, cmd_buf_index, FALSE);
		}
		cmd_buf_index = 0;
#endif
    }
	
    data_len = sprintf(&cmdBuffer[cmd_buf_index], "%u\r\x1a", relay_status);
	cmd_buf_index += data_len;
    cmdBuffer[cmd_buf_index] = 0;
    SendData(cmdBuffer, cmd_buf_index, FALSE);
	

    return data_len;
}