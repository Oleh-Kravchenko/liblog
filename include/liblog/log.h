/**
 * @file
 * @author Oleh Kravchenko <oleg@kaa.org.ua>
 *
 * log -- Logging macros
 * Copyright (C) 2013  Oleh Kravchenko <oleg@kaa.org.ua>
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

#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>

#include <liblog/list.h>

/**
 * @defgroup log Logging macros
 *
 * Эти макросы позволяют легко и быстро добавить журналирование в вашу
 * программу, они обратно совместимы с уровнями журналирования syslog и
 * linux kernel.
 *
 * @{
 *
 * Для удобного использования определены макросы влияющие на поведение
 * журналирования:
 * @li __LOG_LEVEL_COMPILE максимальный уровень журналирования определяемый во время компиляции
 * @li __LOG_LEVEL_RUNTIME максимальный уровень журналирования по-умолчанию во время работы программы
 * @li __LOG_NAMESPACE простраство для журналирования событий, по-умолчанию ""
 *
 * На данный момент поддерживается два вида журналирования:
 * @li stderr вывод отладочных сообщений в stderr
 * @li syslog отправка отладочных сообщений в syslog демон
 *
 * Прототип функции журналирования:
 * @code
 * void func(log_level_t level, const char* format, ...)
 * @endcode
 *
 * Пример использования:
 * @li Печать в stderr
 * @code
 * #undef __LOG_NAMESPACE
 * #define __LOG_NAMESPACE "stderr"
 *	log_set_type(__LOG_NAMESPACE, log_stderr);
 *	_DEBUG("debug-level message");
 * @endcode
 * @li syslog
 * @code
 * #undef __LOG_NAMESPACE
 * #define __LOG_NAMESPACE "syslog"
 *	log_set_type(__LOG_NAMESPACE, log_syslog);
 *	_DEBUG("debug-level message");
 * @endcode
 * @li по завершении работы программы следует вызвать:
 * @code
 *	log_gc();
 * @endcode
 */

/*------------------------------------------------------------------------*/

/** уровни журналирования, в порядке убывания приоритета */
typedef enum log_level {
	__LOG_EMERG     = 0,  /**< system is unusable */
	__LOG_ALERT     = 1,  /**< action must be taken immediately */
	__LOG_CRIT      = 2,  /**< critical conditions */
	__LOG_ERR       = 3,  /**< error conditions */
	__LOG_WARNING   = 4,  /**< warning conditions */
	__LOG_NOTICE    = 5,  /**< normal, but significant, condition */
	__LOG_INFO      = 6,  /**< informational message */
	__LOG_DEBUG     = 7,  /**< debug-level message */
} log_level_t;

/*------------------------------------------------------------------------*/

/** logging function type */
typedef void (*log_func_t)(log_level_t, const char *, va_list);

/** type of namespace logging */
typedef struct log_namespace {
	/** list pointer */
	list_node_t node;

	/** logger function */
	log_func_t log_func;

	/** current logging level */
	log_level_t current;

	/** namespace of logging */
	char name[PATH_MAX];
} log_namespace_t;

/*------------------------------------------------------------------------*/

/**
 * @def __LOG_LEVEL_COMPILE
 *
 * Максимальный уровень журналирования определяемый во время компиляции.
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
 * Максимальный уровень журналирования во время работы программы.
 */
#ifndef __LOG_LEVEL_RUNTIME
#	ifdef NDEBUG
#		define __LOG_LEVEL_RUNTIME __LOG_NOTICE
#	else /* NDEBUG */
#		define __LOG_LEVEL_RUNTIME __LOG_INFO
#	endif /* NDEBUG */
#endif /* __LOG_LEVEL_RUNTIME */

/*------------------------------------------------------------------------*/

/**
 * @def __LOG_NAMESPACE
 *
 * Простраство имен журналирования сообщений, может использоваться внутри модулей.
 */
#ifndef __LOG_NAMESPACE
#	define __LOG_NAMESPACE ""
#endif /* __LOG_NAMESPACE */

/*------------------------------------------------------------------------*/

/**
 * @brief set new level of logging
 * @param [in] ns namespace of logging
 * @param [in] level new debugging level
 * @return old level of logging
 */
log_level_t log_set(const char *ns, log_level_t level);

/**
 * @brief get current level of logging
 * @param [in] ns namespace of logging
 * @return current level of logging
 */
log_level_t log_get(const char *ns);

/**
 * @brief set type of logger
 * @param [in] ns namespace of logging
 * @param [in] func new function for writing log
 * @return old function
 */
log_func_t log_set_type(const char *ns, log_func_t func);

/**
 * @brief get type of logger
 * @param [in] ns namespace of logging
 * @return function
 */
log_func_t log_get_type(const char *ns);

/**
 * @brief print message using current type of logger
 * @param [in] level debugging level
 * @param [in] ns namespace of logging (can be NULL)
 * @param [in] format format string
 */
void log_printf(log_level_t level, const char *ns, const char *format, ...);

/** cleanup namespaces */
void log_gc(void);

/*------------------------------------------------------------------------*/

/**
 * @def _EMERG
 *
 * Вывод сообщения о критической ошибке и завершения работы программы.
 */

#if __LOG_EMERG <= __LOG_LEVEL_COMPILE
#	define _EMERG(...)                                                    \
	do {                                                                  \
		log_printf(__LOG_EMERG, __LOG_NAMESPACE, __VA_ARGS__);            \
		abort();                                                          \
	} while(0)
#else
#	define _EMERG(...)
#endif

/*------------------------------------------------------------------------*/

/**
 * @def _ALERT
 *
 * Вывод сообщения о критической ошибке.
 */

#if __LOG_ALERT <= __LOG_LEVEL_COMPILE
#	define _ALERT(...) log_printf(__LOG_ALERT, __LOG_NAMESPACE, __VA_ARGS__)
#else
#	define _ALERT(...)
#endif

/*------------------------------------------------------------------------*/

/**
 * @def _CRIT
 *
 * Вывод сообщения о серьезной ошибке.
 */

#if __LOG_CRIT <= __LOG_LEVEL_COMPILE
#	define _CRIT(...) log_printf(__LOG_CRIT, __LOG_NAMESPACE, __VA_ARGS__)
#else
#	define _CRIT(...)
#endif

/*------------------------------------------------------------------------*/

/**
 * @def _ERR
 *
 * Вывод сообщения об ошибке.
 */

#if __LOG_ERR <= __LOG_LEVEL_COMPILE
#	define _ERR(...) log_printf(__LOG_ERR, __LOG_NAMESPACE, __VA_ARGS__)
#else
#	define _ERR(...)
#endif

/*------------------------------------------------------------------------*/

/**
 * @def _WARNING
 *
 * Вывод предупреждения.
 */

#if __LOG_WARNING <= __LOG_LEVEL_COMPILE
#	define _WARNING(...) log_printf(__LOG_WARNING, __LOG_NAMESPACE, __VA_ARGS__)
#else
#	define _WARNING(...)
#endif

/*------------------------------------------------------------------------*/

/**
 * @def _NOTICE
 *
 * Вывод уведомления.
 */

#if __LOG_NOTICE <= __LOG_LEVEL_COMPILE
#	define _NOTICE(...) log_printf(__LOG_NOTICE, __LOG_NAMESPACE, __VA_ARGS__)
#else
#	define _NOTICE(...)
#endif

/*------------------------------------------------------------------------*/

/**
 * @def _INFO
 *
 * Вывод информационного сообщения.
 */

#if __LOG_INFO <= __LOG_LEVEL_COMPILE
#	define _INFO(...) log_printf(__LOG_INFO, __LOG_NAMESPACE, __VA_ARGS__)
#else
#	define _INFO(...)
#endif

/*------------------------------------------------------------------------*/

/**
 * @def _DEBUG
 *
 * Вывод отладочной информации.
 */

#if __LOG_DEBUG <= __LOG_LEVEL_COMPILE
#	define _DEBUG(...) log_printf(__LOG_DEBUG, __LOG_NAMESPACE, __VA_ARGS__)
#else
#	define _DEBUG(...)
#endif

/**
 * @}
 */

#endif /* __LIB_LOG_H */
