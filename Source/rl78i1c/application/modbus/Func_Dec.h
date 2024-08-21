#include "r_cg_macrodriver.h"

void Modbus_Timer(void);
void R_UART1_RX_ON(void);
void Query_Validation(void);
void _MODBUS_READ_INPUTREGISTERS(void);
void Transfer_Modbus_Reg_Array(void);
void Modbus_Error_Response(uint8_t Error_Code, uint8_t Exception_Code);
unsigned  int  ModBus_getCRC16( unsigned char * String_Arry,unsigned char String_Length );
void Initial_Setup(void);