#ifndef  __EVENT_LOG_H__
#define  __EVENT_LOG_H__

typedef enum {
    LOG_NONE = 0,
    LOG_ERROR,
    LOG_WARNING,
    LOG_INFO,
    LOG_DEBUG,
    LOG_PRINT
} LogLevel_t;

void set_log_level(LogLevel_t log_level);

void log_info(const char *msg_fmt, ...);
void log_warning(const char *msg_fmt, ...);
void log_error(const char *msg_fmt, ...);
void log_debug(const char *msg_fmt, ...);

void log_print(const char *msg_fmt, ...);

#endif