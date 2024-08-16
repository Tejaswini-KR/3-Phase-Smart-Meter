#include <stdio.h>
#include <stdarg.h>

#include "utils.h"
#include "event_log.h"

static LogLevel_t LogLevel = LOG_NONE;

void set_log_level(LogLevel_t log_level)
{
    if ( log_level >= LOG_NONE && log_level <= LOG_PRINT) {
        LogLevel = log_level;
    }
}

#ifdef SIMULATION

void log_info(const char *msg_fmt, ...)
{
	va_list args;
    if (LogLevel < LOG_INFO) {
        return;
    }
    printf("%08u: #INFO: ", get_tick_count());
    va_start(args, msg_fmt);
    vprintf(msg_fmt, args);
    va_end(args);
    printf("\n");
}

void log_warning(const char *msg_fmt, ...)
{
	va_list args;
    if (LogLevel < LOG_WARNING) {
        return;
    }
    printf("%08u: #WARN: ", get_tick_count());
    
    va_start(args, msg_fmt);
    vprintf(msg_fmt, args);
    va_end(args);
    printf("\n");
}

void log_error(const char *msg_fmt, ...)
{
	va_list args;
    if (LogLevel < LOG_ERROR) {
        return;
    }
    printf("%08u: #ERROR: ", get_tick_count());
    
    va_start(args, msg_fmt);
    vprintf(msg_fmt, args);
    va_end(args);
    printf("\n");
}

void log_debug(const char *msg_fmt, ...)
{
	va_list args;
    if (LogLevel < LOG_DEBUG) {
        return;
    }
    printf("%08u: #DEBUG: ", get_tick_count());
    
    va_start(args, msg_fmt);
    vprintf(msg_fmt, args);
    va_end(args);
    printf("\n");
}

void log_print(const char *msg_fmt, ...)
{
	va_list args;
    printf("%08u: ", get_tick_count());
    
    va_start(args, msg_fmt);
    vprintf(msg_fmt, args);
    va_end(args);
    printf("\n");
}
#endif
