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
#include "stderr.h"

/*------------------------------------------------------------------------*/

int ll_stderr_pr(void *priv, const char *name, enum ll_level level,
	const char *format, va_list args
) {
	unused(priv);

	assert(name);
	assert(format);

	int rc = -1;

	flockfile(stderr);

	do {
		if (fprintf(stderr, "%" PRIi64 ";%s;%s;",
			(int64_t)time(NULL), name, ll_level_str(level)) < 0) {
			break;
		}

		if (vfprintf(stderr, format, args) < 0) {
			break;
		}

		if (fputc('\n', stderr) < 0) {
			break;
		}

		rc = 0;
	} while (0);

	funlockfile(stderr);

	return (rc);
}
