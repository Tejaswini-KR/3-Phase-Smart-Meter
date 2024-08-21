#include "r_cg_macrodriver.h"
#include "User_Def.h"

extern unsigned int 	Modbus_Power_ON_Reset,Modbus_Timeout_Watch,Power_ON_Reset;
extern unsigned char   Modbus_RX_Array[];	// define required size in header file
extern unsigned char   UARTTxEmpty,UART_Rx_Count,UART_Tx_Count;
extern unsigned char   Transmit_buffer[]; // define required size in header file
extern unsigned char   Modbus_Input_Reg_Array[]; 
extern unsigned char   *UART_Tx_Pointer; // pointer for int based transmission
extern unsigned char   Master_Watch_Dog;
extern unsigned char   Uart_RXD_TOV; 
extern unsigned int    Delay_2_Min_Count;
extern unsigned char   TX_Byte, TX_Data_Count,RX_Byte,Silent_Interval,Char_Frame_Delay, Shift_Out_Delay;
extern unsigned char   Modbus_State;
extern unsigned char Uart_Monitor_Counter;
extern unsigned char Modbus_State;

extern union
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
 
 extern struct
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


extern struct UART_Bit_Register 
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

extern union
  {
    unsigned long int Lwc_Long;
    unsigned short int Lwc_Word[2];
    // Lwc_Word[0] is LSW
    unsigned char Lwc_Byte[4];
    // Lwc_Byte[0] is LSB
  } Lwc_Var;