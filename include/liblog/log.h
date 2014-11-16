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

#ifndef __LIB_LOG_H
#define __LIB_LOG_H

#include <stdarg.h>
#include <stdlib.h>

/**
 * @def __LIBLOG_EXPORT
 *
 * Type of exported functions.
 */
#if defined _WIN32 || defined __CYGWIN__
#	ifdef __LIBLOG_EXPORTS
#		define __LIBLOG_EXPORT __declspec(dllexport)
#	else
#		define __LIBLOG_EXPORT __declspec(dllimport)
#	endif /* __LIBLOG_EXPORT */
#else
#	define __LIBLOG_EXPORT __attribute__ ((visibility("default")))
#endif


/**
 * @defgroup log Logging macros
 *
 * These macros allow you to quickly and easily add logging to your
 * program, they are backward compatible with syslog logging levels and
 * linux kernel.
 *
 * @{
 *
 * Logging configurations:
 * @li __LOG_LEVEL_COMPILE maximum level of logging, at compile time
 * @li __LOG_LEVEL_RUNTIME maximum level of logging, at run time
 * @li __LOG_NAMESPACE namespace of logging, by default ""
 *
 * Supported next type of logger:
 * @li stderr print messages into stderr
 * @li syslog print messages into syslog daemon
 *
 * Logging function prototype:
 * @code
 * void func(int level, const char* format, ...)
 * @endcode
 *
 * Usage example:
 * @li print to stderr
 * @code
 * #undef __LOG_NAMESPACE
 * #define __LOG_NAMESPACE "stderr"
 *	log_set_type(__LOG_NAMESPACE, log_stderr);
 *	_DEBUG("debug-level message");
 * @endcode
 * @li print to syslog
 * @code
 * #undef __LOG_NAMESPACE
 * #define __LOG_NAMESPACE "syslog"
 *	log_set_type(__LOG_NAMESPACE, log_syslog);
 *	_DEBUG("debug-level message");
 * @endcode
 * @li at program exit, should be called this function:
 * @code
 *	liblog_uninit();
 * @endcode
 */

/*------------------------------------------------------------------------*/

/** levels of logging */
#define __LOG_EMERG     0	/**< system is unusable */
#define __LOG_ALERT     1	/**< action must be taken immediately */
#define __LOG_CRIT      2	/**< critical conditions */
#define __LOG_ERR       3	/**< error conditions */
#define __LOG_WARNING   4	/**< warning conditions */
#define __LOG_NOTICE    5	/**< normal, but significant, condition */
#define __LOG_INFO      6	/**< informational message */
#define __LOG_DEBUG     7	/**< debug-level message */

/*------------------------------------------------------------------------*/

/** logging function type */
typedef void (*log_func_t)(int level, const char *format, va_list ap);

/*------------------------------------------------------------------------*/

/**
 * @def __LOG_LEVEL_COMPILE
 *
 * Maximum level of logging per compile time.
 */
#ifndef __LOG_LEVEL_COMPILE
#	ifdef NDEBUG
#		define __LOG_LEVEL_COMPILE __LOG_INFO
#	else /* NDEBUG */
#		define __LOG_LEVEL_COMPILE __LOG_DEBUG
#	endif /* NDEBUG */
#endif /* __LOG_LEVEL_COMPILE */

/*------------------------------------------------------------------------*/

/**
 * @def __LOG_LEVEL_RUNTIME
 *
 * Maximum level of logging at runtime.
 */
#ifndef __LOG_LEVEL_RUNTIME
#	define __LOG_LEVEL_RUNTIME __LOG_WARNING
#endif /* __LOG_LEVEL_RUNTIME */

/*------------------------------------------------------------------------*/

/**
 * @def __LOG_NAMESPACE
 *
 * Namespace for logging, can be specified per module.
 */
#ifndef __LOG_NAMESPACE
#	define __LOG_NAMESPACE NULL
#endif /* __LOG_NAMESPACE */

/*------------------------------------------------------------------------*/

/**
 * @brief initialize liblog library
 * @return 0, if successfull
 *
 * This function create namespace:
 * @li NULL default namespace for stderr output
 * @li "syslog" namespace for syslog output
 */
int liblog_init(void);

/**
 * @brief set new level of logging
 * @param [in] ns namespace of logging
 * @param [in] level new debugging level
 * @return old level of logging
 */
int liblog_level_set(const char *ns, int level);

/**
 * @brief get current level of logging
 * @param [in] ns namespace of logging
 * @return current level of logging
 */
int liblog_level_get(const char *ns);

/**
 * @brief set type of logger
 * @param [in] ns namespace of logging
 * @param [in] func new function for writing log
 * @return old function
 */
log_func_t liblog_type_set(const char *ns, log_func_t func);

/**
 * @brief get type of logger
 * @param [in] ns namespace of logging
 * @return function
 */
log_func_t liblog_type_get(const char *ns);

/**
 * @brief print message using current type of logger
 * @param [in] level debugging level
 * @param [in] ns namespace of logging (can be NULL)
 * @param [in] format format string
 */
void liblog_printf(int level, const char *ns, const char *format, ...);

/** cleanup namespaces */
void liblog_uninit(void);

/*------------------------------------------------------------------------*/

/**
 * @def __LINE_STR__
 *
 * Provide string interpretation of __LINE__ macro.
 */

#ifndef __LINE_STR__

#define __LINE_STR__STAGE1(line) #line
#define __LINE_STR__STAGE2(line) __LINE_STR__STAGE1(line)

#define __LINE_STR__ __LINE_STR__STAGE2(__LINE__)

#endif /* __LINE_STR__ */

/**
 * @def __DEBUG__
 *
 * Provide string interpretation of __FILE__ and __LINE__ macros to use
 * with log macros.
 */

#ifdef NDEBUG
#	define __DEBUG__(...) __VA_ARGS__
#else
#	define __DEBUG__(...) __FILE__ ":" __LINE_STR__ " " __VA_ARGS__
#endif /* NDEBUG */

/*------------------------------------------------------------------------*/

/**
 * @def _EMERG
 *
 * Print emergency message and abort program.
 */

#if __LOG_EMERG <= __LOG_LEVEL_COMPILE
#	define _EMERG(...)                                                     \
	do {                                                                   \
		liblog_printf(                                                     \
			__LOG_EMERG, __LOG_NAMESPACE,                                  \
			__DEBUG__(__VA_ARGS__)                                         \
		);                                                                 \
		abort();                                                           \
	} while(0)
#else
#	define _EMERG(...)
#endif

/*------------------------------------------------------------------------*/

/**
 * @def _ALERT
 *
 * Print alert message.
 */

#if __LOG_ALERT <= __LOG_LEVEL_COMPILE
#	define _ALERT(...)                                                     \
	liblog_printf(__LOG_ALERT, __LOG_NAMESPACE, __DEBUG__(__VA_ARGS__))
#else
#	define _ALERT(...)
#endif

/*------------------------------------------------------------------------*/

/**
 * @def _CRIT
 *
 * Print critical error message.
 */

#if __LOG_CRIT <= __LOG_LEVEL_COMPILE
#	define _CRIT(...)                                                      \
	liblog_printf(__LOG_CRIT, __LOG_NAMESPACE, __DEBUG__(__VA_ARGS__))
#else
#	define _CRIT(...)
#endif

/*------------------------------------------------------------------------*/

/**
 * @def _ERR
 *
 * Print error message.
 */

#if __LOG_ERR <= __LOG_LEVEL_COMPILE
#	define _ERR(...)                                                       \
	liblog_printf(__LOG_ERR, __LOG_NAMESPACE, __DEBUG__(__VA_ARGS__))
#else
#	define _ERR(...)
#endif

/*------------------------------------------------------------------------*/

/**
 * @def _WARNING
 *
 * Print warning message.
 */

#if __LOG_WARNING <= __LOG_LEVEL_COMPILE
#	define _WARNING(...)                                                   \
	liblog_printf(__LOG_WARNING, __LOG_NAMESPACE, __DEBUG__(__VA_ARGS__))
#else
#	define _WARNING(...)
#endif

/*------------------------------------------------------------------------*/

/**
 * @def _NOTICE
 *
 * Print notice message.
 */

#if __LOG_NOTICE <= __LOG_LEVEL_COMPILE
#	define _NOTICE(...)                                                    \
	liblog_printf(__LOG_NOTICE, __LOG_NAMESPACE, __DEBUG__(__VA_ARGS__))
#else
#	define _NOTICE(...)
#endif

/*------------------------------------------------------------------------*/

/**
 * @def _INFO
 *
 * Print informational message.
 */

#if __LOG_INFO <= __LOG_LEVEL_COMPILE
#	define _INFO(...)                                                      \
	liblog_printf(__LOG_INFO, __LOG_NAMESPACE, __DEBUG__(__VA_ARGS__))
#else
#	define _INFO(...)
#endif

/*------------------------------------------------------------------------*/

/**
 * @def _DEBUG
 *
 * Print debug message.
 */

#if __LOG_DEBUG <= __LOG_LEVEL_COMPILE
#	define _DEBUG(...)                                                     \
	liblog_printf(__LOG_DEBUG, __LOG_NAMESPACE, __DEBUG__(__VA_ARGS__))
#else
#	define _DEBUG(...)
#endif

/**
 * @}
 */

#endif /* __LIB_LOG_H */
