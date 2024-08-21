/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_wdt.h"
#include "r_cg_sau.h"
/* Start user code for include. Do not edit comment generated here */
#include "Global_Var.h"
#include "User_Def.h"
#include "Func_Dec.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"
#include "em_core.h"
#include "inst_read.h"
#include "r_tariff.h"
#include "r_max_demand.h"
#include "powermgmt.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt r_uart1_interrupt_send(vect=INTST1)
#pragma interrupt r_uart1_interrupt_receive(vect=INTSR1)

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint8_t * gp_uart1_tx_address;         /* uart1 send buffer address */
extern volatile uint16_t  g_uart1_tx_count;            /* uart1 send data number */
extern volatile uint8_t * gp_uart1_rx_address;         /* uart1 receive buffer address */
extern volatile uint16_t  g_uart1_rx_count;            /* uart1 receive data number */
extern volatile uint16_t  g_uart1_rx_length;           /* uart1 receive data length */
uint8_t array[];


/*******************************************************************************
 After Every Query received  validate Query
 1.Check CRC-----------------------------      Fails   ---> don't do any thing if Fails.
 2.Check Function code Supports----------      Fails   --->Error respose
 3.Call Individual Function
 ********************************************************************************/
void Query_Validation(void) // Function call will be at main loop after the complete frame receiving is over.
{
	uint16_t CRC_Value;
	CRC_Value = ModBus_getCRC16(Modbus_RX_Array, RX_Byte - 2);//--------------->Length of the Received Byte Array
	Lwc_Var.Lwc_Byte[1] = Modbus_RX_Array[--RX_Byte]; // hi word
	Lwc_Var.Lwc_Byte[0] = Modbus_RX_Array[--RX_Byte]; // lo word
	if (Lwc_Var.Lwc_Word[0] == CRC_Value)//752
	{
		Modbus_Bit_Fields.SI_Over=0;
		Silent_Interval = 10;//waited b/w querry and response
		
       		 Modbus_Timeout_Watch=0;
			
		while(!Modbus_Bit_Fields.SI_Over)
		//*********************** CRC Validation  Modbus CRC16 //57661
		switch (Modbus_RX_Array[1])
		{
			//*********************Function Code Validation
			case MODBUS_READ_HOLDINGREGISTERS	:
			case MODBUS_READ_INPUTREGISTERS		:	_MODBUS_READ_INPUTREGISTERS();		return;//Function code 04
			//case MODBUS_WRITE_MULT_REG		:	_MODBUS_WRITE_MULT_REG();			return;
			default					:	Modbus_Error_Response(0x84, 1);		return;
		}
	}
	else
	{
		//*************** Ignoring  the Received Data and restart the receive interrupt
		R_UART1_RX_ON();
	}
} 

/***************************************************************************
MODBUS_READ_INPUTREGISTERS
Request
          Function code               1 Byte      0x04
          Starting Address            2 Bytes     0x0000 to 0xFFFF
          Quantity of Input Registers 2 Bytes     0x0001 to 0x007D
Response
          Function code               1 Byte      0x04
          Byte count                  1 Byte      2 x N*
          Input Registers             N* x 2 Bytes
*N = Quantity of Input Registers
Error
        Error code                    1 Byte      0x84
        Exception code                1 Byte      01 or 02 or 03 or 04
*****************************************************************************/ 
void _MODBUS_READ_INPUTREGISTERS(void)
{
 unsigned char i;
 unsigned int Starting_Address,Byte_Counts;
 //************************ Read Starting Address 
  Lwc_Var.Lwc_Byte[1]=Modbus_RX_Array[2]; // hi word
  Lwc_Var.Lwc_Byte[0]=Modbus_RX_Array[3]; // lo word
  Starting_Address= Lwc_Var.Lwc_Word[0];
  //************************Read the byte count 
  Lwc_Var.Lwc_Byte[1]=Modbus_RX_Array[4]; // hi word
  Lwc_Var.Lwc_Byte[0]=Modbus_RX_Array[5]; // lo word
  Byte_Counts= Lwc_Var.Lwc_Word[0];
  //*************************Validate Address
  if(Starting_Address <=Maximum_Read_Register)  //address 0000 to FFFF 36
  { //*************************Validate Bytes_Counts
    if((Byte_Counts+Starting_Address) <= Maximum_Read_Register )
    { 
	Transmit_buffer[0]=Modbus_RX_Array[0];        // Meter_ID
    Transmit_buffer[1]=Modbus_RX_Array[1];            //Function Code 04 
    Transmit_buffer[2]=Byte_Counts*2;   //Byte Counts=  2* N
    /******** Loading Current Readings  ***********/
    Transfer_Modbus_Reg_Array();
    for(i=3;i<=(Byte_Counts*2)+3;i++)
    Transmit_buffer[i]=Transmit_buffer[i+Starting_Address*2];
/******** Loading Current Readings ***********/
	Lwc_Var.Lwc_Word[0] = ModBus_getCRC16(Transmit_buffer,Transmit_buffer[2] + 3);//--------------->Length of the Received Byte Arry
	Transmit_buffer[--i] = Lwc_Var.Lwc_Byte[0];// hi word
	Transmit_buffer[++i] = Lwc_Var.Lwc_Byte[1]; // lo word
	TX_Data_Count = Transmit_buffer[2] + 5;
	TX_Byte = 0;
	RS485_DIR=1; 
	while(Modbus_Bit_Fields.Modbus_Tx_Completed); // if last resp sent then go 
	R_UART1_Start();
	R_UART1_Send(Transmit_buffer,TX_Data_Count);  
    }
    else
    Modbus_Error_Response(0x84,3);
  }
  else
    Modbus_Error_Response(0x84,2); 
}

/****************************************************************************
 Error
 Error code          1 Byte    0x90 or 0x84 or 0x91
 Exception code      1 Byte    01 or 02 or 03 or 04

 *****************************************************************************/ 
void Modbus_Error_Response(uint8_t Error_Code, uint8_t Exception_Code)
{
	//Tranmitting error code;
	Transmit_buffer[0] = Modbus_RX_Array[0]; // Meter_ID
	Transmit_buffer[1] = Error_Code; // Error Code
	Transmit_buffer[2] = Exception_Code; // Exception Code
	Lwc_Var.Lwc_Word[0] = ModBus_getCRC16(Transmit_buffer, 5);//------->Length of the Received Byte Arry-2
	Transmit_buffer[3] = Lwc_Var.Lwc_Byte[0];// hi word
	Transmit_buffer[4] = Lwc_Var.Lwc_Byte[1]; // lo word
	TX_Data_Count = 5;  
	RS485_DIR=1;
	R_UART1_Start();
	R_UART1_Send(Transmit_buffer,TX_Data_Count); 
} 

void Transfer_Modbus_Reg_Array(void)
{
	unsigned char i = 0;
        //unsigned long K=(unsigned long)Modbus_Union.Modbus_Structure.Voltage;
        union 
          {
          	float Modbus_Union_Pointer;
          	unsigned char Modbus_Union[4];
          }Temp_Union; 

          /*union 
          {
          	unsigned long Modbus_Union_Pointer;
          	unsigned char Modbus_Union[4];
          } Long_Temp_Union;
          
          union 
          {
          unsigned long Modbus_Union_Pointer;
          unsigned char Modbus_Union[2];
          }Int_Temp_Union;*/

           
	float *Modbus_Union_Pointer;
	//unsigned long *Modbus_Union_Pointer_Long;
	//unsigned int *Modbus_Union_Pointer_int;
	
	Modbus_Union.Modbus_Structure.MODBUS_DATA_VOLTAGE_Phase_R = g_inst_read_params.vrms[LINE_PHASE_R];
	Modbus_Union.Modbus_Structure.MODBUS_DATA_VOLTAGE_Phase_Y = g_inst_read_params.vrms[LINE_PHASE_Y];
	Modbus_Union.Modbus_Structure.MODBUS_DATA_VOLTAGE_Phase_B = g_inst_read_params.vrms[LINE_PHASE_B];
	
	Modbus_Union.Modbus_Structure.MODBUS_DATA_PHASE_CURRENT_Phase_R = g_inst_read_params.irms[LINE_PHASE_R]; 
	Modbus_Union.Modbus_Structure.MODBUS_DATA_PHASE_CURRENT_Phase_Y = g_inst_read_params.irms[LINE_PHASE_Y]; 
	Modbus_Union.Modbus_Structure.MODBUS_DATA_PHASE_CURRENT_Phase_B = g_inst_read_params.irms[LINE_PHASE_B]; 
	Modbus_Union.Modbus_Structure.MODBUS_DATA_NEUTRAL_CURRENT = g_inst_read_params.irms[LINE_NEUTRAL]; 
	
	Modbus_Union.Modbus_Structure.MODBUS_DATA_PHASE_POWERFACTOR_R = g_inst_read_params.power_factor[LINE_PHASE_R];
	Modbus_Union.Modbus_Structure.MODBUS_DATA_PHASE_POWERFACTOR_Y = g_inst_read_params.power_factor[LINE_PHASE_Y];
	Modbus_Union.Modbus_Structure.MODBUS_DATA_PHASE_POWERFACTOR_B = g_inst_read_params.power_factor[LINE_PHASE_B];

	Modbus_Union.Modbus_Structure.MODBUS_DATA_FREQUENCY = g_inst_read_params.freq[LINE_TOTAL];
	
	Modbus_Union.Modbus_Structure.MODBUS_DATA_INST_ACTIVEPOWER_PHASE_R = g_inst_read_params.active_power[LINE_PHASE_R];
	Modbus_Union.Modbus_Structure.MODBUS_DATA_INST_ACTIVEPOWER_PHASE_Y = g_inst_read_params.active_power[LINE_PHASE_Y];
	Modbus_Union.Modbus_Structure.MODBUS_DATA_INST_ACTIVEPOWER_PHASE_B = g_inst_read_params.active_power[LINE_PHASE_B];
	
	Modbus_Union.Modbus_Structure.MODBUS_DATA_INST_REACTIVEPOWER_PHASE_R = g_inst_read_params.reactive_power[LINE_PHASE_R];
	Modbus_Union.Modbus_Structure.MODBUS_DATA_INST_REACTIVEPOWER_PHASE_Y = g_inst_read_params.reactive_power[LINE_PHASE_Y];
	Modbus_Union.Modbus_Structure.MODBUS_DATA_INST_REACTIVEPOWER_PHASE_B = g_inst_read_params.reactive_power[LINE_PHASE_B];
	
	Modbus_Union.Modbus_Structure.MODBUS_DATA_INST_FUNDAMENTAL_ACTIVEPOWER_PHASE_R = g_inst_read_params.fundamental_power[LINE_PHASE_R];
	Modbus_Union.Modbus_Structure.MODBUS_DATA_INST_FUNDAMENTAL_ACTIVEPOWER_PHASE_Y = g_inst_read_params.fundamental_power[LINE_PHASE_Y];
	Modbus_Union.Modbus_Structure.MODBUS_DATA_INST_FUNDAMENTAL_ACTIVEPOWER_PHASE_B = g_inst_read_params.fundamental_power[LINE_PHASE_B];
	
	Modbus_Union.Modbus_Structure.MODBUS_DATA_INST_APARENTPOWER_PHASE_R = g_inst_read_params.apparent_power[LINE_PHASE_R];
	Modbus_Union.Modbus_Structure.MODBUS_DATA_INST_APARENTPOWER_PHASE_Y = g_inst_read_params.apparent_power[LINE_PHASE_Y];
	Modbus_Union.Modbus_Structure.MODBUS_DATA_INST_APARENTPOWER_PHASE_B = g_inst_read_params.apparent_power[LINE_PHASE_B];
	
	Modbus_Union.Modbus_Structure.MODBUS_DATA_IMPORT_ACTIVE_ENERGY =  R_TARIFF_GetImportActiveEnergyTotal();
	Modbus_Union.Modbus_Structure.MODBUS_DATA_IMPORT_CAPCITIVEREACTIVE_ENERGY = R_TARIFF_GetImportCapacitiveReactiveEnergyTotal();
	Modbus_Union.Modbus_Structure.MODBUS_DATA_IMPORT_INDUCTIVEREACTIVE_ENERGY = R_TARIFF_GetImportInductiveReactiveEnergyTotal();
	Modbus_Union.Modbus_Structure.MODBUS_DATA_IMPORT_APPARENT_ENERGY = R_TARIFF_GetImportApparentEnergyTotal();
	Modbus_Union.Modbus_Structure.MODBUS_DATA_EXPORT_ACTIVE_ENERGY = R_TARIFF_GetExportActiveEnergyTotal();
	Modbus_Union.Modbus_Structure.MODBUS_DATA_EXPORT_CAPCITIVEREACTIVE_ENERGY = R_TARIFF_GetExportCapacitiveReactiveEnergyTotal();
	Modbus_Union.Modbus_Structure.MODBUS_DATA_EXPORT_INDUCTIVEREACTIVE_ENERGY = R_TARIFF_GetExportInductiveReactiveEnergyTotal();
	Modbus_Union.Modbus_Structure.MODBUS_DATA_EXPORT_APPARENT_ENERGY =  R_TARIFF_GetExportApparentEnergyTotal();
	
	Modbus_Union.Modbus_Structure.MODBUS_DATA_ACTIVE_MAXDEMAND = R_MDM_GetActiveMaxDemand();
	Modbus_Union.Modbus_Structure.MODBUS_DATA_CAPACITIVEREACTIVE_MAXDEMAND = R_MDM_GetCapacitiveReactiveMaxDemand();
	Modbus_Union.Modbus_Structure.MODBUS_DATA_INDUCTIVEREACTIVE_MAXDEMAND = R_MDM_GetInductiveReactiveMaxDemand();
	Modbus_Union.Modbus_Structure.MODBUS_DATA_APPARENT_MAXDEMAND = R_MDM_GetApparentMaxDemand();
   
    	Modbus_Union_Pointer = &Modbus_Union.Modbus_Structure.MODBUS_DATA_VOLTAGE_Phase_R;

	    for (i = 3; i < 140;)
		{
			Temp_Union.Modbus_Union_Pointer = *Modbus_Union_Pointer;
			Transmit_buffer[i++]            = Temp_Union.Modbus_Union[3];
			Transmit_buffer[i++]            = Temp_Union.Modbus_Union[2];
			Transmit_buffer[i++]            = Temp_Union.Modbus_Union[1];
			Transmit_buffer[i++]            = Temp_Union.Modbus_Union[0];
			Modbus_Union_Pointer++;
		} 

    return;
}  

/* Start user code for adding. Do not edit comment generated here */
unsigned  int  ModBus_getCRC16( unsigned char * String_Arry,unsigned char String_Length )
{
unsigned short crc,thisbyte,shift;
unsigned char lastbit, j,highbyte, lowbyte;

crc=0xffff;

  for (j=0; j<String_Length; j++)
    {
    thisbyte= *String_Arry++;
    crc = crc^thisbyte;
    for (shift=1; shift<=8; shift++)
      {
          lastbit = (unsigned char)crc & 1;
          crc = (crc >> 1) & 0x7fff;
          if (lastbit==1)
          {
          crc = crc^0xA001 ;
          }
       }
     }
    highbyte=(unsigned char) ((crc>>8)&0xff);
    lowbyte=(unsigned char) (crc&0xff);
    Lwc_Var.Lwc_Byte[1]=highbyte;
    Lwc_Var.Lwc_Byte[0]=lowbyte;
    return   Lwc_Var.Lwc_Word[0]; //( (crc & 0xFF) * 256 ) + (crc>>8);
}

/* End user code. Do not edit comment generated here */
