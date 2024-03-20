#include "compiler.h"
#include "em_type.h"

#pragma section const EMCallback

/* wrp_em_timer.h */
void (FAR_PTR * const FAR_PTR EM_TIMER_Init_Address)(void);
void (FAR_PTR * const FAR_PTR EM_TIMER_Start_Address)(void);
void (FAR_PTR * const FAR_PTR EM_TIMER_Stop_Address)(void);

/* wrp_em_wdt.h */
void (FAR_PTR * const FAR_PTR EM_WDT_Init_Address)(void);
void (FAR_PTR * const FAR_PTR EM_WDT_Start_Address)(void);
void (FAR_PTR * const FAR_PTR EM_WDT_Stop_Address)(void);
void (FAR_PTR * const FAR_PTR EM_WDT_Restart_Address)(void);

/* wrp_em_mcu.h */
void (FAR_PTR * const FAR_PTR EM_MCU_Delay_Address)(uint16_t us);
void (FAR_PTR * const FAR_PTR EM_MCU_MultipleInterruptEnable_Address)(uint8_t enable);

/* wrp_em_adc.h */
void (FAR_PTR * const FAR_PTR EM_ADC_Init_Address)(void);
void (FAR_PTR * const FAR_PTR EM_ADC_Start_Address)(void);
void (FAR_PTR * const FAR_PTR EM_ADC_Stop_Address)(void);

void (FAR_PTR * const FAR_PTR EM_ADC_GainPhaseReset_Address)(EM_LINE line);
void (FAR_PTR * const FAR_PTR EM_ADC_GainPhaseIncrease_Address)(EM_LINE line);
void (FAR_PTR * const FAR_PTR EM_ADC_GainPhaseDecrease_Address)(EM_LINE line);
uint8_t (FAR_PTR * const FAR_PTR EM_ADC_GainPhaseGetLevel_Address)(EM_LINE line);

void (FAR_PTR * const FAR_PTR EM_ADC_SetPhaseCorrection_Address)(EM_LINE line, float32_t degree);
void (FAR_PTR * const FAR_PTR EM_ADC_SAMP_UpdateStep_Address)(float32_t fac);

/* wrp_em_pulse.h */
void (FAR_PTR * const FAR_PTR EM_PULSE_Init_Address)(void);
void (FAR_PTR * const FAR_PTR EM_PULSE_ACTIVE_On_Address)(void);
void (FAR_PTR * const FAR_PTR EM_PULSE_ACTIVE_Off_Address)(void);
void (FAR_PTR * const FAR_PTR EM_PULSE_REACTIVE_On_Address)(void);
void (FAR_PTR * const FAR_PTR EM_PULSE_REACTIVE_Off_Address)(void);
void (FAR_PTR * const FAR_PTR EM_PULSE_APPARENT_On_Address)(void);
void (FAR_PTR * const FAR_PTR EM_PULSE_APPARENT_Off_Address)(void);


/* wrp_em_sw_property.h */
EM_SW_PROPERTY FAR_PTR* (FAR_PTR * const FAR_PTR EM_SW_GetProperty_Address)(void);
