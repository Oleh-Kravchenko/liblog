#include <log/stderr.h>

int main(void)
{
	_DEBUG("debug-level message");
	_INFO("informational message");
	_NOTICE("normal, but significant, condition");
	_WARNING("warning conditions");
	_ERR("error conditions");
	_CRIT("critical conditions");
	_ALERT("action must be taken immediately");
	_EMERG("system is unusable");

	return(0);
}
