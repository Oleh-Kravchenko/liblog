#include "liblog/loggers/color.h"
#include "liblog/loggers/file.h"
#include "liblog/log.h"

/*------------------------------------------------------------------------*/

int main(void)
{
	ll_logger_color();
	ll_logger_file();

	LL_DEBUG("debug");
	LL_INFO("info");
	LL_NOTICE("notice");
	LL_WARN("warning");
	LL_ERR("error");
	LL_CRIT("critical");
	LL_ALERT("alert");
	/* LL_EMERG("emergency"); */

#define _LIBLOG_NET_LEVEL _LL_LEVEL_DEBUG

	LL_PR(, _LL_LEVEL_DEBUG, "debug message");
	LL_PR_DEBUG(NET, "debug message by LL_PR_DEBUG()");

	ll_cleanup();

	return (0);
}
