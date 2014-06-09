/**
 * @file
 * @author Oleh Kravchenko <oleg@kaa.org.ua>
 *
 * liblog -- Logging macros
 * Copyright (C) 2014  Oleh Kravchenko <oleg@kaa.org.ua>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __LIB_LOG_SYSLOG_H
#define __LIB_LOG_SYSLOG_H

#define __LOG_NAMESPACE_SYSLOG "syslog"

#undef __LOG_NAMESPACE
#define __LOG_NAMESPACE __LOG_NAMESPACE_SYSLOG

#include <liblog/log.h>

/**
 * @brief print log message into syslog
 * @param [in] level level of logging
 * @param [in] format format of message
 * @param [in] ap arguments list
 */
void log_syslog(log_level_t level, const char *format, va_list ap);

#endif /* __LIB_LOG_SYSLOG_H */
