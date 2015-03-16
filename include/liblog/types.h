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

#ifndef __LIBLOG_TYPES_H
#define __LIBLOG_TYPES_H

#include <liblog/defines.h>
#include <stdarg.h>
#include <libtools/url.h>

/**
 * @defgroup liblog_types Types
 * @brief Defines types useful for interaction with liblog
 * @{
 */

/**
 * @brief Define logging level enumeration for strict type
 *
 * Please use it for logging functions.
 */
enum ll_level {
	/** Invalid value */
	LL_LEVEL_INVALID = -1,

	/** @copydoc _LL_LEVEL_EMERG */
	LL_LEVEL_EMERG = _LL_LEVEL_EMERG,

	/** @copydoc _LL_LEVEL_ALERT */
	LL_LEVEL_ALERT = _LL_LEVEL_ALERT,

	/** @copydoc _LL_LEVEL_CRIT */
	LL_LEVEL_CRIT = _LL_LEVEL_CRIT,

	/** @copydoc _LL_LEVEL_ERR */
	LL_LEVEL_ERR = _LL_LEVEL_ERR,

	/** @copydoc _LL_LEVEL_WARN */
	LL_LEVEL_WARN = _LL_LEVEL_WARN,

	/** @copydoc _LL_LEVEL_NOTICE */
	LL_LEVEL_NOTICE = _LL_LEVEL_NOTICE,

	/** @copydoc _LL_LEVEL_INFO */
	LL_LEVEL_INFO = _LL_LEVEL_INFO,

	/** @copydoc _LL_LEVEL_DEBUG */
	LL_LEVEL_DEBUG = _LL_LEVEL_DEBUG,
};

/**
 * @brief
 * @param [in] name namespace
 * @param [in] level logging level of namespace
 * @param [in] u
 * @param [in] priv
 * @return on success, zero is returned
 * @retval -1 error occurred
 */
typedef int (*ll_open_cb_t)(const char *name, enum ll_level level,
	struct url *u, void **priv
);

/**
 * @brief Routine callback for message logging
 * @param [in] priv pointer to private data of logger
 * @param [in] name namespace of message
 * @param [in] level logging level of message
 * @param [in] format format of message
 * @param [in] args list of arguments
 * @return on success, zero is returned
 * @retval -1 error occurred
 */
typedef int (*ll_pr_cb_t)(void *priv, const char *name,
	enum ll_level level, const char *format, va_list args
);

/**
 * @brief Routine callback to deallocate memory used by logger
 * @param [in] priv pointer to private data of logger (can be NULL)
 * @return on success, zero is returned
 * @retval -1 error occurred
 */
typedef int (*ll_close_cb_t)(void *priv);

/** Logger callback functions pointers */
struct ll_logger {
	/** name of logger */
	const char *name;

	/**
	 * @brief Pointer to logger open function
	 * @copydetails ll_open_cb_t
	 */
	const ll_open_cb_t open_cb;

	/**
	 * @brief Pointer to logger print function
	 * @copydetails ll_pr_cb_t
	 */
	const ll_pr_cb_t pr_cb;

	/**
	 * @brief Pointer to logger close function
	 * @copydetails ll_close_cb_t
	 */
	const ll_close_cb_t close_cb;
};

/** @} */

#endif /* __LIBLOG_TYPES_H */
