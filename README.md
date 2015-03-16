# liblog

## Synopsis

C implementation of the logging library.

Available features:

- CMake support;
- Compile and run-time logging levels;
- Multi-level logging compatible with syslog;
- Support logger types (file, stderr, ..);
- Support namespaces with own logging level and logger type.

## Code Example

Configuring logging over environment:

~~~~{.sh}
export LIBLOG=7,file:/tmp/my.log
~~~~

Easy usage:

~~~~{.c}
#include <liblog/loggers/file.h>
#include <liblog/log.h>

int main(void)
{
	ll_logger_file();

	LL_DEBUG("debug");
	LL_INFO("info");
	LL_NOTICE("notice");
	LL_WARN("warning");
	LL_ERR("error");
	LL_CRIT("critical");
	LL_ALERT("alert");

#if 0
	LL_EMERG("emergency"); /* also abort program by abort() */
#endif

	ll_cleanup();

	return 0;
}
~~~~

## Installation

### Compilation from sources

~~~~{.sh}
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=/usr/local ..
make install
~~~~

## API Reference

### CMake

~~~~{.cmake}
FIND_PACKAGE(liblog REQUIRED)

# use dinamic linking
TARGET_LINK_LIBRARIES(YOUR_APP liblog)

# or static if want
TARGET_LINK_LIBRARIES(YOUR_APP liblog_static)
~~~~

### Environment

When liblog first time logging a message,
it lookup for environment variable in this format:

~~~~{.sh}
LIBLOG[_NAMESPACE]=<LEVEL>[,<URI>]
~~~~

It's allow you to configure logging of your program,
without any configuration files, etc.

To avoid this behaviour, please use ll_setup().

### C

Configuring namespaces:

~~~~{.c}
ll_setup("", LL_LEVEL_INFO, ""); /* to stderr */
ll_setup("MY", LL_LEVEL_WARN, "file:/var/log/liblog.log");
~~~~

Extended logging, using separate namespaces:

~~~~{.c}
/* don't forget to define logging level for your namespace */
#define _LIBLOG_MY_LEVEL _LL_LEVEL_DEBUG

LL_PR_DEBUG(MY, "debug message from MY namespace");
~~~~

Restart logging (useful for logrotate):

~~~~{.c}
ll_flush("MY"); /* flush MY namespace */
ll_flush_all(); /* flush all namespace */
~~~~

Change run-time logging level:

~~~~{.c}
ll_level_set("", LL_LEVEL_WARN);
ll_level_set("MY", LL_LEVEL_DEBUG); /* print everything, from MY */
~~~~

Adding custom logger:

~~~~{.c}
ll_logger_custom({
	.name = "mylog", /* your logger name */
	.open_cb = NULL,
	.pr_cb = NULL,
	.flush_cb = NULL,
	.close_cb = NULL,
});
~~~~

### Doxygen

Library is well documented in Doxygen style.
To generate documentation, please run in build directory:

~~~~{.sh}
make doc
~~~~

And open html/index.html file.

## Contributors

- Maksym Kosharniy <kmvvmk@gmail.com>
- Oleh Kravchenko <oleg@kaa.org.ua>

## License

Copyright (C) 2016  Oleh Kravchenko <oleg@kaa.org.ua>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
