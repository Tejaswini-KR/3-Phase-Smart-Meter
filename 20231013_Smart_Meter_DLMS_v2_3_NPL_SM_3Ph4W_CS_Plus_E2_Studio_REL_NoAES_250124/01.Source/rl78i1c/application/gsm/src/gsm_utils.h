#ifndef  __GSM_UTILS_H__
#define  __GSM_UTILS_H__

#include "gsm_typedef.h"
								   
bool_t is_error(void);

uint16_t gsm_state_handler_generic(bool_t isEntry, uint16_t initState, uint16_t endState,
                                   __far uint16_t *pChildState, const CommandResponse_t *arrCmdResp);
#endif
