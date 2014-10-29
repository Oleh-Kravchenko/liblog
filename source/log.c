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

#include <stdlib.h>
#include <string.h>

#include "liblog/stderr.h"
#include "liblog/syslog.h"

/*------------------------------------------------------------------------*/

static list_node_t log_namespaces = list_init_value(&log_namespaces);

/*------------------------------------------------------------------------*/

static log_namespace_t *log_namespace_get(const char *ns)
{
	log_namespace_t *ret;

	/* default namespace is "" */
	ns = ns ? ns : "";

	list_foreach (&log_namespaces, ret, log_namespace_t, node) {
		if (!strcmp(ns, ret->name)) {
			return (ret);
		}
	}

	if ((ret = malloc(sizeof(*ret)))) {
		strncpy(ret->name, ns, sizeof(ret->name) - 1);
		ret->name[sizeof(ret->name) - 1] = 0;

		ret->current = __LOG_LEVEL_RUNTIME;
		ret->log_func = log_stderr;

		list_add_node(&log_namespaces, &ret->node);
	}

	return (ret);
}

/*------------------------------------------------------------------------*/

__LIBLOG_EXPORT int liblog_init(void)
{
	liblog_type_set(__LOG_NAMESPACE_STDERR, log_stderr);
	liblog_type_set(__LOG_NAMESPACE_SYSLOG, log_syslog);

	return (0);
}

/*------------------------------------------------------------------------*/

__LIBLOG_EXPORT log_level_t liblog_level_set(const char *ns, log_level_t level)
{
	log_namespace_t *lns;

	if (!(lns = log_namespace_get(ns))) {
		return (__LOG_LEVEL_RUNTIME);
	}

	log_level_t ret;

	ret = lns->current; lns->current = level;

	return(ret);
}

/*------------------------------------------------------------------------*/

__LIBLOG_EXPORT log_level_t liblog_level_get(const char *ns)
{
	log_namespace_t *lns;

	if (!(lns = log_namespace_get(ns))) {
		return (__LOG_LEVEL_RUNTIME);
	}

	return (lns->current);
}

/*------------------------------------------------------------------------*/

__LIBLOG_EXPORT log_func_t liblog_type_set(const char *ns, log_func_t func)
{
	log_namespace_t *lns;

	if (!(lns = log_namespace_get(ns))) {
		return (log_stderr);
	}

	log_func_t ret;

	ret = lns->log_func; lns->log_func = func;

	return(ret);
}

/*------------------------------------------------------------------------*/

__LIBLOG_EXPORT log_func_t liblog_type_get(const char *ns)
{
	log_namespace_t *lns;

	if (!(lns = log_namespace_get(ns))) {
		return (log_stderr);
	}

	return (lns->log_func);
}

/*------------------------------------------------------------------------*/

__LIBLOG_EXPORT void liblog_printf(log_level_t level, const char *ns, const char *format, ...)
{
	log_namespace_t *lns;

	if (!(lns = log_namespace_get(ns))) {
		return;
	}

	if(level > lns->current) {
		return;
	}

	va_list ap;

	va_start(ap, format);
	lns->log_func(level, format, ap);
	va_end(ap);
}

/*------------------------------------------------------------------------*/

__LIBLOG_EXPORT void liblog_uninit(void)
{
	log_namespace_t *item, *tmp;

	/* destroy all namespaces */
	list_foreach_safe (&log_namespaces, item, tmp, log_namespace_t, node) {
		list_del_node(&item->node);
		free(item);
	}
}
