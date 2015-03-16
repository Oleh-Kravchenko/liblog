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
#include <inttypes.h>
#include <stdio.h>
#include <time.h>
#include <libtools/tools.h>

#include "liblog/log.h"
#include "liblog/loggers/file.h"

/*------------------------------------------------------------------------*/

/**
 * @brief Write message to file
 * @copydetails ll_open_cb_t
 */
static int file_open(const char *name, enum ll_level level, struct url *u,
	void **priv) {
	unused(name);
	unused(level);

	assert(u);

	if (u->username ||
		u->password ||
		u->hostname ||
		u->port ||
		!u->path ||
		u->query ||
		u->fragment) {
		return (-1);
	}

	if (!(*priv = fopen(u->path, "w"))) {
		return (-1);
	}

	return (0);
}

/*------------------------------------------------------------------------*/

/**
 * @brief Write message to file
 * @copydetails ll_pr_cb_t
 */
static int file_pr(void *priv, const char *name, enum ll_level level,
	const char *format, va_list args) {
	assert(priv);
	assert(name);
	assert(format);

	FILE *f = priv;
	int rc = -1;

	flockfile(f);

	do {
		if (fprintf(f, "%" PRIi64 ";%s;%d;",
			(int64_t)time(NULL), name, level) < 0) {
			break;
		}

		if (vfprintf(f, format, args) < 0) {
			break;
		}

		if (fputc('\n', f) < 0) {
			break;
		}

		rc = 0;
	} while (0);

	funlockfile(f);

	return (rc);
}

/*------------------------------------------------------------------------*/

/**
 * @brief Write message to file
 * @copydetails ll_close_cb_t
 */
static int file_close(void *priv)
{
	FILE *f = priv;

	if (f && fclose(f)) {
		return (-1);
	}

	return (0);
}

/*------------------------------------------------------------------------*/

int ll_logger_file(void)
{
	const struct ll_logger file_cb = {
		.name = "file",
		.open_cb = file_open,
		.pr_cb = file_pr,
		.close_cb = file_close,
	};

	return (ll_logger_custom(&file_cb));
}
