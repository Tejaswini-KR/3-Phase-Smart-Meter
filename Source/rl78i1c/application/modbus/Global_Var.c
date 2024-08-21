#include "r_cg_macrodriver.h"
#include "User_Def.h"

unsigned int 	Modbus_Power_ON_Reset=0,Modbus_Timeout_Watch=0,Power_ON_Reset=0;
unsigned char   Modbus_RX_Array[128];	// define required size in header file
unsigned char   UARTTxEmpty = 1,UART_Rx_Count=0,UART_Tx_Count;
unsigned char   Transmit_buffer[150]; // define required size in header file
unsigned char   Modbus_Input_Reg_Array[MODBUS_MAX_INPUT_REG]; 
unsigned char   *UART_Tx_Pointer; // pointer for int based transmission
unsigned char   Master_Watch_Dog;
unsigned char   Uart_RXD_TOV; 
unsigned int    Delay_2_Min_Count=0;
unsigned char   TX_Byte=0, TX_Data_Count=0,RX_Byte=0,Silent_Interval,Char_Frame_Delay, Shift_Out_Delay;
unsigned char   Modbus_State=0;
unsigned char Uart_Monitor_Counter=60;
unsigned char Modbus_State;

union
  { 
    struct
  	{
  		float	MODBUS_DATA_VOLTAGE_Phase_R;
		float	MODBUS_DATA_VOLTAGE_Phase_Y;
		float	MODBUS_DATA_VOLTAGE_Phase_B;
		
  		float	MODBUS_DATA_PHASE_CURRENT_Phase_R;	
		float	MODBUS_DATA_PHASE_CURRENT_Phase_Y;
		float	MODBUS_DATA_PHASE_CURRENT_Phase_B;	
  		float	MODBUS_DATA_NEUTRAL_CURRENT;
		
		float 	MODBUS_DATA_PHASE_POWERFACTOR_R;
		float 	MODBUS_DATA_PHASE_POWERFACTOR_Y;
		float 	MODBUS_DATA_PHASE_POWERFACTOR_B;
		
		float	MODBUS_DATA_FREQUENCY;
	
		float	MODBUS_DATA_INST_ACTIVEPOWER_PHASE_R;
		float	MODBUS_DATA_INST_ACTIVEPOWER_PHASE_Y;
		float	MODBUS_DATA_INST_ACTIVEPOWER_PHASE_B;
		
		float	MODBUS_DATA_INST_REACTIVEPOWER_PHASE_R;
		float	MODBUS_DATA_INST_REACTIVEPOWER_PHASE_Y;
		float	MODBUS_DATA_INST_REACTIVEPOWER_PHASE_B;
		
		float	MODBUS_DATA_INST_FUNDAMENTAL_ACTIVEPOWER_PHASE_R;
		float	MODBUS_DATA_INST_FUNDAMENTAL_ACTIVEPOWER_PHASE_Y;
		float	MODBUS_DATA_INST_FUNDAMENTAL_ACTIVEPOWER_PHASE_B;
		
		float	MODBUS_DATA_INST_APARENTPOWER_PHASE_R;
		float	MODBUS_DATA_INST_APARENTPOWER_PHASE_Y;
		float	MODBUS_DATA_INST_APARENTPOWER_PHASE_B;
	
		float	MODBUS_DATA_IMPORT_ACTIVE_ENERGY;
		float	MODBUS_DATA_IMPORT_CAPCITIVEREACTIVE_ENERGY;
		float	MODBUS_DATA_IMPORT_INDUCTIVEREACTIVE_ENERGY;
		float	MODBUS_DATA_IMPORT_APPARENT_ENERGY;
		float	MODBUS_DATA_EXPORT_ACTIVE_ENERGY;
		float	MODBUS_DATA_EXPORT_CAPCITIVEREACTIVE_ENERGY;
		float	MODBUS_DATA_EXPORT_INDUCTIVEREACTIVE_ENERGY;
		float	MODBUS_DATA_EXPORT_APPARENT_ENERGY;
	
		float	MODBUS_DATA_ACTIVE_MAXDEMAND;
		float	MODBUS_DATA_CAPACITIVEREACTIVE_MAXDEMAND;
		float	MODBUS_DATA_INDUCTIVEREACTIVE_MAXDEMAND;
		float	MODBUS_DATA_APPARENT_MAXDEMAND;	        		             		
		
  	}Modbus_Structure;
	
 }Modbus_Union;
 
 struct
{		
	unsigned char 	Meter_Id;      		
	unsigned char 	CTL_Flags;			
	unsigned char 	Tmr_On_Delay;		
	unsigned char 	Tmr_Off_Delay;		
	unsigned char 	MD_Interval;		
	unsigned char	MD_Par;				
        unsigned char   Spare;	           
        unsigned long   Serial_Number; 		    
        unsigned int    Manufacturing_Date; 	
        unsigned int    Modbus_Watchdog_Timer; 	
        unsigned int    Baud_Rate;	           
        unsigned char   Parity;	            
        unsigned char   Spare2;	         
        unsigned long   Dummy[12];  		
	unsigned int    Mtr_Const_CRC16;
	
}Mtr_Set_Const;


struct UART_Bit_Register 
{
  	unsigned int Transmition_Ready                            : 1;
  	unsigned int Received_Enable                              : 1;
  	unsigned int Modbus_ID_Received                           : 1; 
  	unsigned int Modbus_ID_Validation                         : 1;
  	unsigned int SI_Over                                      : 1;
  	unsigned int Valid_Frame                                  : 1;    
  	unsigned int Valid_Frame_complete                         : 1;
  	unsigned int Modbus_Tx_Completed                          : 1;
  	unsigned int Modbus_Holding_Reg_Add_Validation_Pass       : 1;
  	unsigned int Modbus_Holding_Reg_Byte_Validation_Pass      : 1;
  	unsigned int Modbus_Holding_Reg_Add_Byte_Validation_Pass  : 1;
  	unsigned int Modbus_Holding_Reg_Flash_Write_Pass          : 1;
  	unsigned int Modbus_uart_Idle			          : 1;
	unsigned int Modbus_Send_Complete			  : 1;
	unsigned int Modbus_Rec_Complete			  : 1;
	
}Modbus_Bit_Fields;

union
  {
    unsigned long int Lwc_Long;
    unsigned short int Lwc_Word[2];
    // Lwc_Word[0] is LSW
    unsigned char Lwc_Byte[4];
    // Lwc_Byte[0] is LSB
  } Lwc_Var;