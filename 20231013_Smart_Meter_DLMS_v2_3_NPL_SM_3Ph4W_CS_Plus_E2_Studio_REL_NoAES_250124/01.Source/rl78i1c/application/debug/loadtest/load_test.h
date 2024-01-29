#ifndef __LOAD_TEST_H
#define __LOAD_TEST_H

#include "r_cg_cgc.h"
#include "platform.h"

/* DSAD */
#ifdef METER_ENABLE_MEASURE_CPU_LOAD
/* Import from  r_cg_adc_user.c for measuring DSAD functions */
extern uint16_t g_timer0_dsad_counter;

extern uint16_t g_timer0_dsad_maxcounter;
extern uint16_t g_timer0_dsad_mincounter;

extern uint16_t g_dsad_count;
extern uint16_t g_dsad_max_count;
extern uint32_t g_timer0_dsad_sum_counter;

extern uint16_t g_timer0_emtimer_counter;

extern uint16_t g_timer0_emtimer_maxcounter;

extern uint16_t g_emtimer_count;
extern const uint16_t g_emtimer_max_count;

extern uint16_t g_timer0_diff;
#endif

/* TIMER */
void LOADTEST_TAU_DRV_Init(void);
void LOADTEST_TAU_DRV_DeInit(void);

/* CGC */
uint16_t LOADTEST_CGC_DRV_GetClock(void);

void LOADTEST_TAU_DRV_SetCKM0Divider(uint16_t divider);
uint16_t LOADTEST_TAU_DRV_GetCKM0Divider(uint8_t is_raw);

#define LOADTEST_TAU_Init()                         LOADTEST_TAU_DRV_Init()
#define LOADTEST_TAU_DeInit()                       LOADTEST_TAU_DRV_DeInit()
#define LOADTEST_TAU_SetCKM0Divider(divider)        LOADTEST_TAU_DRV_SetCKM0Divider(divider)
#define LOADTEST_TAU_GetCKM0Divider(is_raw)         LOADTEST_TAU_DRV_GetCKM0Divider(is_raw)
#define LOADTEST_CGC_GetClock()                     LOADTEST_CGC_DRV_GetClock()
#define LOADTEST_TAU_Start()                        (TS0 = 0x01)
#define LOADTEST_TAU_Stop()                         (TT0 = 0x01)
#define LOADTEST_TAU_Diff()                         (0xFFFF - TCR00)

#endif /* __LOAD_TEST_H */