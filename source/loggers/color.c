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
#include "liblog/loggers/color.h"

/*------------------------------------------------------------------------*/

/**
 * @brief Write colored message to stderr
 * @copydetails ll_pr_cb_t
 */
static int color_pr(void *priv, const char *name, enum ll_level level,
	const char *format, va_list args) {
	unused(priv);

	assert(name);
	assert(format);

	int rc = -1;

	flockfile(stderr);

	do {
		if (fprintf(stderr, "%" PRIi64 ";%s;%d;",
			(int64_t)time(NULL), name, level) < 0) {
			break;
		}

		switch (level) {
			case LL_LEVEL_EMERG:
				if (fputs("\033[41;91;5m", stderr) < 0) {
					goto err;
				}

				break;

			case LL_LEVEL_ALERT:
				if (fputs("\033[41m", stderr) < 0) {
					goto err;
				}

				break;

			case LL_LEVEL_CRIT:
				if (fputs("\033[91m", stderr) < 0) {
					goto err;
				}

				break;

			case LL_LEVEL_ERR:
				if (fputs("\033[31m", stderr) < 0) {
					goto err;
				}

				break;

			case LL_LEVEL_WARN:
				if (fputs("\033[93m", stderr) < 0) {
					goto err;
				}

				break;

			case LL_LEVEL_NOTICE:
				if (fputs("\033[33m", stderr) < 0) {
					goto err;
				}

				break;

			case LL_LEVEL_INFO:
				break;

			case LL_LEVEL_DEBUG:
				if (fputs("\033[32m", stderr) < 0) {
					goto err;
				}

				break;

			default:
				break;
		}

		if (vfprintf(stderr, format, args) < 0) {
			break;
		}

		if (fputs("\033[0m\n", stderr) < 0) {
			break;
		}

		rc = 0;
	} while (0);

err:
	funlockfile(stderr);

	return (rc);
}

/*------------------------------------------------------------------------*/

int ll_logger_color(void)
{
	const struct ll_logger cbs = {
		.name = "color",
		.pr_cb = color_pr,
	};

	return (ll_logger_custom(&cbs));
}
