/**
 * @file
 *
 * Copyright (C) 2016  Oleh Kravchenko <oleg@kaa.org.ua>
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

#ifndef __LIBLOG_LOG_H
#define __LIBLOG_LOG_H

#include <liblog/types.h>

/**
 * @defgroup liblog_functions Functions
 * @brief Defines functions for liblog configuration and message logging
 * @{
 */

/**
 * @brief Log message according to format
 * @param [in] name namespace of message
 * @param [in] level logging level of message
 * @param [in] format format string of message
 * @return on success, zero is returned
 * @retval -1 error occurred
 */
int ll_printf(const char *name, enum ll_level level, const char *format, ...);

/**
 * @brief Setup logging namespace
 * @param [in] name namespace name
 * @param [in] level logging level of namespace
 * @param [in] uri logger parameters in URI format
 * @return on success, zero is returned
 * @retval -1 error occurred
 */
int ll_setup(const char *name, enum ll_level level, const char *uri);

/**
 * @brief Set logging level for specified namespace
 * @param [in] name namespace
 * @param [in] level new logging level
 * @return old logging level
 * @retval LL_LEVEL_INVALID error occurred
 */
enum ll_level ll_level_set(const char *name, enum ll_level level);

/**
 * @brief Return string representation of logging level
 * @param [in] level logging level
 * @return string representation of logging level
 * @retval "" invalid logging level was specified
 */
const char *ll_level_str(enum ll_level level);

/** Clean all memory used by liblog */
void ll_cleanup(void);

/** @} */

/**
 * @defgroup liblog_loggers Loggers
 * @ingroup liblog_functions
 * @brief Defines functions for additional loggers initialization
 * @{
 */

/**
 * @brief Register custom  logger in liblog
 * @param [in] logger callbacks info of logger
 * @return on success, zero is returned
 * @retval -1 error occurred
 */
int ll_logger_custom(const struct ll_logger *logger);

/** @} */

#endif /* __LIBLOG_LOG_H */
