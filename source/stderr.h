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

#ifndef __LIBLOG_STDERR_H
#define __LIBLOG_STDERR_H

#include "liblog/types.h"

/**
 * @brief Print message to stderr
 * @copydetails ll_pr_cb_t
 */
int ll_stderr_pr(void *priv, const char *name, enum ll_level level,
	const char *format, va_list args
);

#endif /* __LIBLOG_STDERR_H */
