#undef __LOG_FUNC
#define __LOG_FUNC(...)

#include <log/log.h>

/*------------------------------------------------------------------------*/

static log_level_t log_level_current = __LOG_ERR;

/*------------------------------------------------------------------------*/

log_level_t log_get_level(void)
{
	return(log_level_current);
}

/*------------------------------------------------------------------------*/

log_level_t log_set_level(log_level_t level)
{
	log_level_t ret;

	ret = log_level_current;
	log_level_current = level;

	return(ret);
}
