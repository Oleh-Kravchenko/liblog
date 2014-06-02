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

#include <stdlib.h>

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
 * журналирования. Список переменных определяющие поведение макросов:
 * @li __LOG_LEVEL_COMPILE максимальный уровень журналирования определяемый во время компиляции.
 * @li __LOG_NAMESPACE простраство для журналирования событий
 * @li ___LOG_FUNC(level, ...) макрос выполняющий запись в журнал
 *
 * Прототип функции журналирования:
 * @code
 * void func(log_level_t level, const char* format, ...)
 * @endcode
 */

/*------------------------------------------------------------------------*/

/** уровни журналирования, в порядке убывания приоритета */
typedef enum log_level {
	__LOG_EMERG		= 0,  /**< system is unusable */
	__LOG_ALERT		= 1,  /**< action must be taken immediately */
	__LOG_CRIT		= 2,  /**< critical conditions */
	__LOG_ERR		= 3,  /**< error conditions */
	__LOG_WARNING 	= 4,  /**< warning conditions */
	__LOG_NOTICE	= 5,  /**< normal, but significant, condition */
	__LOG_INFO		= 6,  /**< informational message */
	__LOG_DEBUG		= 7,  /**< debug-level message */
} log_level_t;

/*------------------------------------------------------------------------*/

/**
 * @def __LOG_LEVEL_COMPILE
 *
 * Максимальный уровень журналирования определяемый во время компиляции.
 */
#ifndef __LOG_LEVEL_COMPILE
#	ifdef NDEBUG
#		define __LOG_LEVEL_COMPILE __LOG_WARNING
#	else /* NDEBUG */
#		define __LOG_LEVEL_COMPILE __LOG_DEBUG
#	endif /* NDEBUG */
#endif /* __LOG_LEVEL_COMPILE */

/*------------------------------------------------------------------------*/

/**
 * @def __LOG_NAMESPACE
 *
 * Простраство имен журналирования сообщений, может использоваться внутри модулей.
 */
#ifndef __LOG_NAMESPACE
#	define __LOG_NAMESPACE NULL
#endif /* __LOG_NAMESPACE */

/*------------------------------------------------------------------------*/

#ifndef __LOG_LEVEL
#define __LOG_LEVEL log_get_level()

/**
 * @brief set new level of logging
 * @param level new debugging level
 * @return old level of logging
 */
log_level_t log_set_level(log_level_t level);

/**
 * @brief get current level of logging
 * @return current level of logging
 */
log_level_t log_get_level();

#endif /* __LOG_LEVEL */

/**
 * @def __LOG_FUNC
 *
 * Функция выполняющая отладочного сообщения запись в журнал.
 */
#ifndef __LOG_FUNC
#	error __LOG_FUNC not defined
#endif /* __LOG_FUNC */

/*------------------------------------------------------------------------*/

/**
 * @def _EMERG
 *
 * Вывод сообщения о критической ошибке и завершения работы программы.
 */

#if __LOG_EMERG <= __LOG_LEVEL_COMPILE
#	define _EMERG(...)											\
do {															\
	__LOG_FUNC(__LOG_EMERG, __LOG_NAMESPACE, __VA_ARGS__);			\
	abort();													\
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
#	define _ALERT(...) __LOG_FUNC(__LOG_ALERT, __LOG_NAMESPACE, __VA_ARGS__)
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
#	define _CRIT(...) __LOG_FUNC(__LOG_CRIT, __LOG_NAMESPACE, __VA_ARGS__)
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
#	define _ERR(...) __LOG_FUNC(__LOG_ERR, __LOG_NAMESPACE, __VA_ARGS__)
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
#	define _WARNING(...) __LOG_FUNC(__LOG_WARNING, __LOG_NAMESPACE, __VA_ARGS__)
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
#	define _NOTICE(...) __LOG_FUNC(__LOG_NOTICE, __LOG_NAMESPACE, __VA_ARGS__)
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
#	define _INFO(...) __LOG_FUNC(__LOG_INFO, __LOG_NAMESPACE, __VA_ARGS__)
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
#	define _DEBUG(...) __LOG_FUNC(__LOG_DEBUG, __LOG_NAMESPACE, __VA_ARGS__)
#else
#	define _DEBUG(...)
#endif

/**
 * @}
 */

#endif /* __LIB_LOG_H */
