#ifdef SIMULATION
#include <time.h>
#include <errno.h>
#endif

#include <stdio.h>
#include "gsm_typedef.h"

#define TICK_COUNT_MAX		2000000000

#define TICKS_PER_SECOND	1000

static int32_t g_TickCount = 0;
// 1999999900
void tick_count_callback(void)
{
	g_TickCount++;
	if (g_TickCount > TICK_COUNT_MAX) 
	{
		g_TickCount = 0;
	}
}

uint32_t get_tick_count(void) 
{
#ifdef SIMULATION
   	return((uint32_t)clock());
#else
	return (uint32_t)g_TickCount;
#endif
}

uint32_t get_diff_count(uint32_t snapshot)
{
	int32_t diff = 0;
	
	diff = get_tick_count() - snapshot;
	if (diff < 0) 
	{
		diff += TICK_COUNT_MAX;
	}
	
	return diff;
}

uint32_t get_elapsed_time_in_s(uint32_t snapshot) 
{
   	return(get_diff_count(snapshot) / TICKS_PER_SECOND);
}

uint32_t get_elapsed_time_in_ms(uint32_t snapshot) 
{
	return(get_diff_count(snapshot));
} 

#ifdef SIMULATION
/* msleep(): Sleep for the requested number of milliseconds. */
int msleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}
#endif