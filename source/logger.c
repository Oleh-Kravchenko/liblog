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
#include <string.h>

#include "logger.h"

/*------------------------------------------------------------------------*/

/** item of loggers list */
struct logger {
	/** list node */
	struct list list;

	/** @copydoc ll_open_cb_t */
	ll_open_cb_t open_cb;

	/** @copydoc ll_pr_cb_t */
	ll_pr_cb_t pr_cb;

	/** @copydoc ll_close_cb_t */
	ll_close_cb_t close_cb;

	/** logger name */
	char name[];
};

/*------------------------------------------------------------------------*/

/** pointer to loggers list */
static struct list loggers = list_initializer(&loggers);

/*------------------------------------------------------------------------*/

int ll_logger_custom(const struct ll_logger *l)
{
	assert(l);
	assert(l->name);
	assert(l->pr_cb);
	assert(!l->open_cb == !l->close_cb);

	struct logger *i;

	/* check, if already registered? */
	list_foreach(&loggers, i, struct logger, list) {
		if (!strcasecmp(i->name, l->name)) {
			return (-1);
		}
	}

	/* register new logger */
	if (!(i = malloc(sizeof(*i) + strlen(l->name) + 1))) {
		return (-1);
	}

	i->open_cb = l->open_cb;
	i->pr_cb = l->pr_cb;
	i->close_cb = l->close_cb;
	strcpy(i->name, l->name);

	list_add_head(&loggers, &i->list);

	return (0);
}

/*------------------------------------------------------------------------*/

int ll_logger_open(struct url *u, struct ll_namespace *ns)
{
	assert(u);
	assert(ns);

	struct logger *i;

	list_foreach(&loggers, i, struct logger, list) {
		if (!strcasecmp(i->name, u->scheme)) {
			ns->pr_cb = i->pr_cb;
			ns->close_cb = i->close_cb;

			if (!i->open_cb) {
				return (0);
			}

			return (i->open_cb(ns->name, ns->level, u, &ns->priv));
		}
	}

	return (-1);
}

/*------------------------------------------------------------------------*/

void ll_logger_free(void)
{
	struct logger *i, *tmp;

	list_foreach_safe(&loggers, i, tmp, struct logger, list) {
		list_del_node(&i->list);

		free(i);
	}
}
