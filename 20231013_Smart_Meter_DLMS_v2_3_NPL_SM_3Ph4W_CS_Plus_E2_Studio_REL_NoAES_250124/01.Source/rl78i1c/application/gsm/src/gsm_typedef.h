#ifndef __GSM_TYPE_DEFINITIONS_H__
#define __GSM_TYPE_DEFINITIONS_H__

#ifndef SIMULATION
#include "typedef.h"
#endif

#include <stdio.h>

#ifdef SIMULATION
typedef unsigned char       uint8_t;
typedef signed char         int8_t;

typedef unsigned short int  uint16_t;
typedef signed short int    int16_t;

typedef unsigned long int   uint32_t;
typedef signed long int     int32_t;

typedef float               float32_t;

#define __far
#endif

typedef uint16_t bool_t;

#ifndef TRUE
#define TRUE (1)
#endif
#ifndef FALSE
#define FALSE (0)
#endif

#endif