#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <libtools/list.h>
#include <libtools/string.h>
#include "namespace.h"

#include "logger.h"
#include "stderr.h"

/*------------------------------------------------------------------------*/

static struct list namespaces = list_initializer(&namespaces);

/*------------------------------------------------------------------------*/

/**
 * @brief Try to inherit logging settings from environment
 * @param [in] ns pointer to logging namespace
 * @return on success, zero is returned
 * @retval -1 error occurred
 */
static int ll_ns_env(struct ll_namespace *ns)
{
	assert(ns);
	assert(ns->name);

	const char *env;

	/* get settings from LIBLOG|LIBLOG_%s variable */
	if (*ns->name) {
		char *s;

		if (-1 == asprintf(&s, "LIBLOG_%s", ns->name)) {
			return (-1);
		}

		env = getenv(s);
		free(s);
	} else {
		env = getenv("LIBLOG");
	}

	if (!env) {
		/* nothing to inherit */
		return (-1);
	}

	/* logging level */
	ns->level = atoi(env);

	/* URI */
	const char *uri = strchr(env, ',');

	if (!uri) {
		/* only logging level was set by environment variable? */
		return (-1);
	}

	++ uri;
	struct url *u;

	if (!url_parse(uri, &u)) {
		return (-1);
	}

	/* try to initialize logger */
	int rc = ll_logger_open(u, ns);
	url_free(u);

	return (rc);
}

/*------------------------------------------------------------------------*/

/**
 * @brief Create new logging namespace
 * @param [in] name namespace
 * @return pointer to new namespace
 * @retval NULL error occurred
 */
static struct ll_namespace *liblog_ns_new(const char *name)
{
	assert(name);

	struct ll_namespace *ns = malloc(sizeof(*ns) + strlen(name) + 1);

	if (ns) {
		strcpy(ns->name, name);
		ns->level = _LIBLOG__LEVEL;

		/* try to inherit settings from environment */
		if (ll_ns_env(ns)) {
			/* failed, set default logger */
			ns->priv = NULL;
			ns->pr_cb = ll_stderr_pr;
			ns->close_cb = NULL;
		}
	}

	return (ns);
}

/*------------------------------------------------------------------------*/

struct ll_namespace *ll_ns_lookup(const char *name)
{
	assert(name);

	struct ll_namespace *i;

	/* look for namespace */
	list_foreach(&namespaces, i, struct ll_namespace, list) {
		if (!strcmp(i->name, name)) {
			return (i);
		}
	}

	/* create new one and add to the list */
	if ((i = liblog_ns_new(name))) {
		list_add_head(&namespaces, &i->list);
	}

	return (i);
}

/*------------------------------------------------------------------------*/

void ll_ns_free(void)
{
	struct ll_namespace *i, *tmp;

	list_foreach_safe(&namespaces, i, tmp, struct ll_namespace, list) {
		list_del_node(&i->list);

		if (i->close_cb) {
			i->close_cb(i->priv);
		}

		free(i);
	}
}
