#ifndef __CALLBACK_H
#define __CALLBACK_H

#include "typedef.h"
#include "compiler.h"

extern void                                         (FAR_PTR * const FAR_PTR EM_TIMER_Init_Address)(void);
extern void                                         (FAR_PTR * const FAR_PTR EM_TIMER_Start_Address)(void);
extern void                                         (FAR_PTR * const FAR_PTR EM_TIMER_Stop_Address)(void);

extern void                                         (FAR_PTR * const FAR_PTR EM_WDT_Init_Address)(void);
extern void                                         (FAR_PTR * const FAR_PTR EM_WDT_Start_Address)(void);
extern void                                         (FAR_PTR * const FAR_PTR EM_WDT_Stop_Address)(void);
extern void                                         (FAR_PTR * const FAR_PTR EM_WDT_Restart_Address)(void);

extern void                                         (FAR_PTR * const FAR_PTR EM_MCU_Delay_Address)(uint16_t us);
extern void                                         (FAR_PTR * const FAR_PTR EM_MCU_MultipleInterruptEnable_Address)(uint8_t enable);

extern void                                         (FAR_PTR * const FAR_PTR EM_ADC_Init_Address)(void);
extern void                                         (FAR_PTR * const FAR_PTR EM_ADC_Start_Address)(void);
extern void                                         (FAR_PTR * const FAR_PTR EM_ADC_Stop_Address)(void);

extern void                                         (FAR_PTR * const FAR_PTR EM_ADC_GainPhaseReset_Address)(EM_LINE line);
extern void                                         (FAR_PTR * const FAR_PTR EM_ADC_GainPhaseIncrease_Address)(EM_LINE line);
extern void                                         (FAR_PTR * const FAR_PTR EM_ADC_GainPhaseDecrease_Address)(EM_LINE line);
extern uint8_t                                      (FAR_PTR * const FAR_PTR EM_ADC_GainPhaseGetLevel_Address)(EM_LINE line);

extern void                                         (FAR_PTR * const FAR_PTR EM_ADC_SetPhaseCorrection_Address)(EM_LINE line, float32_t degree);
extern void                                         (FAR_PTR * const FAR_PTR EM_ADC_SAMP_UpdateStep_Address)(float32_t fac);

extern void                                         (FAR_PTR * const FAR_PTR EM_PULSE_Init_Address)(void);
extern void                                         (FAR_PTR * const FAR_PTR EM_PULSE_ACTIVE_On_Address)(void);
extern void                                         (FAR_PTR * const FAR_PTR EM_PULSE_ACTIVE_Off_Address)(void);
extern void                                         (FAR_PTR * const FAR_PTR EM_PULSE_REACTIVE_On_Address)(void);
extern void                                         (FAR_PTR * const FAR_PTR EM_PULSE_REACTIVE_Off_Address)(void);
extern void                                         (FAR_PTR * const FAR_PTR EM_PULSE_APPARENT_On_Address)(void);
extern void                                         (FAR_PTR * const FAR_PTR EM_PULSE_APPARENT_Off_Address)(void);

extern EM_SW_PROPERTY FAR_PTR *                    (FAR_PTR * const FAR_PTR EM_SW_GetProperty_Address)(void);

#endif /* __CALLBACK_H */