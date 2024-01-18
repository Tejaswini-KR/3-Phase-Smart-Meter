#include "typedef.h"
#include "compiler.h"
#include "em_type.h"

#include "wrp_em_timer.h"
#include "wrp_em_wdt.h"
#include "wrp_em_mcu.h"

#include "wrp_em_adc.h"
#include "wrp_em_pulse.h"
#include "wrp_em_sw_property.h"

typedef void (FAR_PTR *FUNC_PTR)(void);

#pragma section const EMCallback

FAR_PTR const FUNC_PTR function_table[] = 
{
    /* wrp_em_timer.h */
    (FUNC_PTR) EM_TIMER_Init,
    (FUNC_PTR) EM_TIMER_Start,
    (FUNC_PTR) EM_TIMER_Stop,

    /* wrp_em_wdt.h */
    (FUNC_PTR) EM_WDT_Init,
    (FUNC_PTR) EM_WDT_Start,
    (FUNC_PTR) EM_WDT_Stop,
    (FUNC_PTR) EM_WDT_Restart,

    /* wrp_em_mcu.h */
    (FUNC_PTR) EM_MCU_Delay,
    (FUNC_PTR) EM_MCU_MultipleInterruptEnable,

    /* wrp_em_adc.h */
    (FUNC_PTR) EM_ADC_Init,
    (FUNC_PTR) EM_ADC_Start,
    (FUNC_PTR) EM_ADC_Stop,

    (FUNC_PTR) EM_ADC_GainPhaseReset,
    (FUNC_PTR) EM_ADC_GainPhaseIncrease,
    (FUNC_PTR) EM_ADC_GainPhaseDecrease,
    (FUNC_PTR) EM_ADC_GainPhaseGetLevel,

    (FUNC_PTR) EM_ADC_SetPhaseCorrection,
    (FUNC_PTR) EM_ADC_SAMP_UpdateStep,

    /* wrp_em_pulse.h */
    (FUNC_PTR)EM_PULSE_Init,
 	(FUNC_PTR)EM_PULSE_ACTIVE_On,
 	(FUNC_PTR)EM_PULSE_ACTIVE_Off,
 	(FUNC_PTR)EM_PULSE_REACTIVE_On,
 	(FUNC_PTR)EM_PULSE_REACTIVE_Off,
	(FUNC_PTR)EM_PULSE_APPARENT_On,
 	(FUNC_PTR)EM_PULSE_APPARENT_Off,

    /* wrp_em_sw_property.h */
    (FUNC_PTR) EM_SW_GetProperty
    
};
