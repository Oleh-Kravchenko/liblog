#include <stdarg.h>
#include <syslog.h>

#include <log/syslog.h>

void syslog_printf(log_level_t level, const char *ns, const char* format, ...)
{
	va_list ap;

	if(__LOG_LEVEL < level) {
		return;
	}

	va_start(ap, format);
	vsyslog(level, format, ap);
	va_end(ap);
}
