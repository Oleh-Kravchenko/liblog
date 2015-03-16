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

#include <assert.h>

#include "liblog/log.h"
#include "logger.h"
#include "namespace.h"

/*------------------------------------------------------------------------*/

int ll_printf(const char *name, enum ll_level level, const char *format, ...)
{
	assert(name);
	assert(format);

	struct ll_namespace *ns = ll_ns_lookup(name);

	/* out of memory? */
	if (!ns) {
		return (-1);
	}

	/* skip message, if it have low level? */
	if (level > ns->level) {
		return (0);
	}

	assert(ns->pr_cb);

	va_list ap;

	va_start(ap, format);
	int rc = ns->pr_cb(ns->priv, name, level, format, ap);
	va_end(ap);

	return (rc);
}

/*------------------------------------------------------------------------*/

enum ll_level ll_level_set(const char *name, enum ll_level level)
{
	assert(name);

	enum ll_level ret = LL_LEVEL_INVALID;
	struct ll_namespace *ns = ll_ns_lookup(name);

	/* out of memory? */
	if (!ns) {
		return (ret);
	}

	/* update logging level and return old value */
	ret = ns->level;
	ns->level = level;

	return (ret);
}

/*------------------------------------------------------------------------*/

void ll_cleanup(void)
{
	ll_logger_free();
	ll_ns_free();
}
