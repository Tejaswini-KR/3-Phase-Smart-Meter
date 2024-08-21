// UART
#define Receive_Packet_Size 	48 //excluding header 'AB'
#define BUFSIZE 		54
#define UART_1_SEC_TIME_OUT 	2000
#define UART_TX_COUNTER 	2000
#define Rx_BUFSIZE		128
#define MAXIMUM_CAL_RX_BUFFER   59
#define Tx_BUFSIZE		90
#define LOW 			0
#define HIGH 			1

/*********************MODBUS Definitions*********************************************/
#define Comm_Default   					0x93              // 10 01 0100        00-->NON   01-->EVN   10-->ODD
#define Comm_Enb_Dsb_Setting    			0x7F
#define Comm_Baud_Setting       			0xF8
#define Comm_Parity_Setting     			0xCF 
#define Comm_Rx_Parity_Error    			0x10
#define Maximum_Read_Register   			116
#define Maximum_Write_Register  			20
#define Maximum_Holding_Register 			116
#define MODBUS_MAX_INPUT_REG           		32
#define MODBUS_TX_BUFFER_SIZE				128

//#define Mb_Reg_Start     				101           // 30101 ,40101 start
#define Mb_Illegal_FUNC 				1
#define Mb_Illegal_ADRS 				2
#define Mb_Illegal_VAL   				3
#define Lockout_Clr_Adrs 				111
#define Master_ID 						250

/*      MODBUS FUNCTION CODES                                     */
#define MODBUS_READ_COILS               	0x01
#define MODBUS_READ_DISCRETEINPUTS      	0x02
#define MODBUS_READ_HOLDINGREGISTERS    	0x03
#define MODBUS_READ_INPUTREGISTERS      	0x04
#define MODBUS_WRITE_COIL               	0x05
#define MODBUS_WRITE_REGISTER           	0x06
#define MODBUS_WRITE_MULT_REG           	0x10
#define MODBUS_WRITE_MULT_COIL          	0x0F
#define EX_MODBUS_READ_COILS            	0x81
#define EX_MODBUS_READ_DISCRETEINPUTS   	0x82
#define EX_MODBUS_READ_INPUTREGISTERS   	0x84
#define EX_MODBUS_WRITE_COIL            	0x85
#define EX_MODBUS_WRITE_REGISTER        	0x86
#define REPORT_SLAVE_ID                 	0x11
#define TRUE                			1
#define FALSE               			0

#define RS485_DIR				P13_bit.no0		
//#define RS485_DIR				P4_bit.no2