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

#ifndef __LIBLOG_COLOR_H
#define __LIBLOG_COLOR_H

/**
 * @addtogroup liblog_loggers
 *
 * @{
 */

/**
 * @brief Register colored output stderr logger in liblog
 * @return on success, zero is returned
 * @retval -1 error occurred
 *
 * Accepted URI for this logger type is:
 * @li color:
 */
int ll_logger_color(void);

/** @} */

#endif /* __LIBLOG_COLOR_H */
