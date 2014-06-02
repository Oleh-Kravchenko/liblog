#include <stdio.h>
#include <stdarg.h>

#include <log/stderr.h>

void stderr_printf(log_level_t level, const char* format, ...)
{
	va_list ap;

	if(__LOG_LEVEL < level) {
		return;
	}

	fprintf(stderr, "<%d> ", level);

	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);

	fputc('\n', stderr);
}
