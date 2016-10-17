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

#ifndef __LIBLOG_DEFINES_H
#define __LIBLOG_DEFINES_H

#include <stdlib.h>

/**
 * @defgroup liblog_macros Macros
 * @brief Macro definitions of liblog
 * @{
 */

/*------------------------------------------------------------------------*/

/**
 * @defgroup liblog_helper_macros Helper macros
 * @brief Helper macros for liblog, but can be also used in applications
 * @{
 */

/**
 * @def __stringify
 *
 * This macro do indirect stringification of input arguments,
 * mostly used with `__LINE__`.
 */
#ifndef __stringify
#	define __stringify_1(...) #__VA_ARGS__
#	define __stringify(...) __stringify_1(__VA_ARGS__)
#endif /* __stringify */

/**
 * @def _LL_LINE
 *
 * Provide string interpretation of "__LINE__" macro.
 */
#define _LL_LINE __stringify(__LINE__)

/**
 * @def _LL_ARGS
 *
 * This macro wrap variadic arguments with file name and line number of
 * caller, if current build configuration is Debug,
 *
 * Example:
 * @code
 * "main.c:5 " __VA_ARGS__
 * @endcode
 *
 * For other build configuration it will be:
 * @code
 * __VA_ARGS__
 * @endcode
 */
#ifdef NDEBUG
#	define _LL_ARGS(...) __VA_ARGS__
#else
#	define _LL_ARGS(...) __FILE__ ":" _LL_LINE " " __VA_ARGS__
#endif /* NDEBUG */

/** @} */

/*------------------------------------------------------------------------*/

/**
 * @defgroup liblog_level_macros Logging level
 * @brief Defines logging macros
 *
 * Please use them with logging macros.
 * @{
 */

#define _LL_LEVEL_EMERG		0	/**< System is unusable */
#define _LL_LEVEL_ALERT		1	/**< Action must be taken immediately */
#define _LL_LEVEL_CRIT		2	/**< Critical conditions */
#define _LL_LEVEL_ERR		3	/**< Error conditions */
#define _LL_LEVEL_WARN		4	/**< Warning conditions */
#define _LL_LEVEL_NOTICE	5	/**< Normal, but significant, condition */
#define _LL_LEVEL_INFO		6	/**< Informational message */
#define _LL_LEVEL_DEBUG		7	/**< Debug-level message */

/** @} */

/*------------------------------------------------------------------------*/

/**
 * @defgroup liblog_extended_macros Extended logging
 * @brief Logging macros to specified namespace
 *
 * Before use, you should define name space level by compiler flag,
 * for example:
 *
 * @li namespace 'NET':
 * @code
 * -D_LIBLOG_NET_LEVEL=7
 * @endcode
 *
 * @li namespace 'IO':
 * @code
 * -D_LIBLOG_IO_LEVEL=7
 * @endcode
 *
 * @{
 */

/**
 * @brief Core logging macro, which call logging routine
 * @param [in] NAMESPACE namespace of message
 * @param [in] LEVEL logging level of message
 *
 */
#define LL_PR(NAMESPACE, LEVEL, ...)                                      \
do {                                                                      \
	if (_LIBLOG_##NAMESPACE##_LEVEL >= LEVEL) {                       \
		ll_printf(#NAMESPACE, LEVEL, _LL_ARGS(__VA_ARGS__));      \
	}                                                                 \
} while (0)

/**
 * @brief Print emergency message to specific namespace and abort the program
 * @param [in] NAMESPACE namespace of message
 */
#define LL_PR_EMERG(NAMESPACE, ...)                                       \
do {                                                                      \
	LL_PR(NAMESPACE, _LL_LEVEL_EMERG, __VA_ARGS__);                   \
	abort();                                                          \
} while (0)

/**
 * @brief Print alert message to specific namespace
 * @param [in] NAMESPACE namespace of message
 */
#define LL_PR_ALERT(NAMESPACE, ...)                                       \
	LL_PR(NAMESPACE, _LL_LEVEL_ALERT, __VA_ARGS__)

/**
 * @brief Print critical message to specific namespace
 * @param [in] NAMESPACE namespace of message
 */
#define LL_PR_CRIT(NAMESPACE, ...)                                        \
	LL_PR(NAMESPACE, _LL_LEVEL_CRIT, __VA_ARGS__)

/**
 * @brief Print error message to specific namespace
 * @param [in] NAMESPACE namespace of message
 */
#define LL_PR_ERR(NAMESPACE, ...)                                         \
	LL_PR(NAMESPACE, _LL_LEVEL_ERR, __VA_ARGS__)

/**
 * @brief Print warning message to specific namespace
 * @param [in] NAMESPACE namespace of message
 */
#define LL_PR_WARN(NAMESPACE, ...)                                        \
	LL_PR(NAMESPACE, _LL_LEVEL_WARN, __VA_ARGS__)

/**
 * @brief Print notice to specific namespace
 * @param [in] NAMESPACE namespace of message
 */
#define LL_PR_NOTICE(NAMESPACE, ...)                                      \
	LL_PR(NAMESPACE, _LL_LEVEL_NOTICE, __VA_ARGS__)

/**
 * @brief Print informational message to specific namespace
 * @param [in] NAMESPACE namespace of message
 */
#define LL_PR_INFO(NAMESPACE, ...)                                        \
	LL_PR(NAMESPACE, _LL_LEVEL_INFO, __VA_ARGS__)

/**
 * @brief Print debug message to specific namespace
 * @param [in] NAMESPACE namespace of message
 */
#define LL_PR_DEBUG(NAMESPACE, ...)                                       \
	LL_PR(NAMESPACE, _LL_LEVEL_DEBUG, __VA_ARGS__)

/** @} */

/*------------------------------------------------------------------------*/

/**
 * @defgroup liblog_default_macros Default logging
 * @brief Logging macros to default namespace
 * @{
 */

/**
 * @def _LIBLOG__LEVEL
 *
 * Logging level of compile time, for default namespace
 */
#ifndef _LIBLOG__LEVEL
#	ifdef NDEBUG
#		define _LIBLOG__LEVEL _LL_LEVEL_NOTICE
#	else /* NDEBUG */
#		define _LIBLOG__LEVEL _LL_LEVEL_DEBUG
#	endif /* NDEBUG */
#endif /* __LIBLOG__LEVEL */

/** Print emergency message to default namespace and abort the program */
#define LL_EMERG(...) LL_PR_EMERG(, __VA_ARGS__)

/** Print alert message to default namespace */
#define LL_ALERT(...) LL_PR(, _LL_LEVEL_ALERT, __VA_ARGS__)

/** Print critical message to default namespace */
#define LL_CRIT(...) LL_PR(, _LL_LEVEL_CRIT, __VA_ARGS__)

/** Print error message to default namespace */
#define LL_ERR(...) LL_PR(, _LL_LEVEL_ERR, __VA_ARGS__)

/** Print warning message to default namespace */
#define LL_WARN(...) LL_PR(, _LL_LEVEL_WARN, __VA_ARGS__)

/** Print notice to default namespace */
#define LL_NOTICE(...) LL_PR(, _LL_LEVEL_NOTICE, __VA_ARGS__)

/** Print informational message to default namespace */
#define LL_INFO(...) LL_PR(, _LL_LEVEL_INFO, __VA_ARGS__)

/** Print debug message to default namespace */
#define LL_DEBUG(...) LL_PR(, _LL_LEVEL_DEBUG, __VA_ARGS__)

/** @} */

/** @} */

#endif /* __LIBLOG_DEFINES_H */
