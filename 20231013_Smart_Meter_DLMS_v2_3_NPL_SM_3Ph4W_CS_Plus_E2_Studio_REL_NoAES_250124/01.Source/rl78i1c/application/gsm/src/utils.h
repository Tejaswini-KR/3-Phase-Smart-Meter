#ifndef  __UTILS_H__
#define  __UTILS_H__

#include "gsm_typedef.h"

#define CONST_STR_AND_LEN(CMD)  CMD, (strlen(CMD))

#define SIZE_OF_ARRAY(array)    (sizeof(array) / sizeof(array[0])) 

typedef struct STRUCT_CMD_RESP
{
    const char * pCommandStr;
    const char * pResponseStr;
    char * pAltCommandStr;
} CommandResponse_t;

uint32_t get_tick_count(void);
uint32_t get_elapsed_time_in_s(uint32_t snapshot);
uint32_t get_elapsed_time_in_ms(uint32_t snapshot);

#ifdef SIMULATION
int msleep(long msec);
#endif

#endif