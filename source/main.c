/**
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

#include <liblog/stderr.h>
#include <liblog/syslog.h>

int main(void)
{
	liblog_init();

	/* log to stderr */
#undef __LOG_NAMESPACE
#define __LOG_NAMESPACE "stderr"
	liblog_type_set(__LOG_NAMESPACE, log_stderr);
	_DEBUG("debug-level message");
	_INFO("informational message");
	_NOTICE("normal, but significant, condition");
	_WARNING("warning conditions");
	_ERR("error conditions");
	_CRIT("critical conditions");
	_ALERT("action must be taken immediately");

	/* log to syslog */
#undef __LOG_NAMESPACE
#define __LOG_NAMESPACE "syslog"
	liblog_type_set(__LOG_NAMESPACE, log_syslog);
	liblog_level_set(__LOG_NAMESPACE, __LOG_DEBUG);
	_DEBUG("debug-level message");
	_INFO("informational message");
	_NOTICE("normal, but significant, condition");
	_WARNING("warning conditions");
	_ERR("error conditions");
	_CRIT("critical conditions");
	_ALERT("action must be taken immediately");

	liblog_uninit();

	return(0);
}
