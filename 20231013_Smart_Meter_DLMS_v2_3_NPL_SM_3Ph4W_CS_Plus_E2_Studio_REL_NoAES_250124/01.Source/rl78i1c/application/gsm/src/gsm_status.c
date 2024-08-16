#include "gsm_typedef.h"
#include "gsm_status.h"

#ifdef SIMULATION
static uint16_t g_relay_status = 1;
#else
#include "relay.h"
#endif

#ifdef SIMULATION
uint16_t get_relay_status()
{
    return g_relay_status;
}

void set_relay_status(uint16_t value)
{
    g_relay_status = value ? 1 : 0;
}

#else

uint16_t get_relay_status()
{
    return RELAY_GetStatus();
}

void set_relay_status(uint16_t value)
{
    uint8_t status = value ? 1 : 0;
    RELAY_SetStatus(status);
}

#endif