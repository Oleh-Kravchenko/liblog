/**
 * @file
 * @author Oleh Kravchenko <oleg@kaa.org.ua>
 */

#ifndef __DEBUG_SYSLOG_H
#define __DEBUG_SYSLOG_H

#undef __LOG_FUNC
#define __LOG_FUNC(level, ...) syslog_printf(level, __VA_ARGS__)

#include <log/log.h>

/**
 * @brief print message into syslog
 * @param level level of logging for this message
 * @param format format of produced message
 */
__attribute__((nonnull(2), format(printf, 2, 3)))
void syslog_printf(log_level_t level, const char* format, ...);

#endif /* __DEBUG_SYSLOG_H */
