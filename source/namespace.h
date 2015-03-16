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

#ifndef __LIBLOG_NAMESPACE_H
#define __LIBLOG_NAMESPACE_H

#include <liblog/types.h>
#include <libtools/list.h>

/** Namespace structure */
struct ll_namespace {
	/** list node */
	struct list list;

	/** pointer to private data of logger used in this namespace */
	void *priv;

	/** @copydoc ll_pr_cb_t */
	ll_pr_cb_t pr_cb;

	/** @copydoc ll_close_cb_t */
	ll_close_cb_t close_cb;

	/** current logging level for this namespace */
	enum ll_level level;

	/** name of namespace */
	char name[];
};

/**
 * @brief Return pointer to liblog namespace
 * @param [in] ns namespace
 * @return pointer to liblog namespace @sa liblog_ns
 * @retval NULL error occurred
 */
struct ll_namespace *ll_ns_lookup(const char *ns);

/** Cleanup all namespaces */
void ll_ns_free(void);

#endif /* __LIBLOG_NAMESPACE_H */
