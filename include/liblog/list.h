/**
 * @file
 * @author Oleh Kravchenko <oleg@kaa.org.ua>
 *
 * log -- Logging macros
 * Copyright (C) 2013  Oleh Kravchenko <oleg@kaa.org.ua>
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

#ifndef __LIB_LOG_LIST_H
#define __LIB_LOG_LIST_H

#include <stddef.h>

typedef struct list_node {
	struct list_node *prev;

	struct list_node *next;
} list_node_t;

#define list_init_value(list) { .prev = list, .next = list, }

#define containerof(ptr, type, field)                                     \
	((type*)((size_t)(ptr) - offsetof(type, field)))

#define list_foreach(list, item, type, field)                             \
	for((item) = containerof((list)->next, type, field);                  \
		&(item)->field != (list);                                         \
		(item) = containerof((item)->field.next, type, field))

#define list_foreach_safe(list, item, temp, type, field)                  \
	for(item = containerof((list)->next, type, field),                    \
		temp = containerof((item)->field.next, type, field);              \
		&(item)->field != (list);                                         \
		item = temp, temp = containerof((temp)->field.next, type, field))

#define list_add_node(list, item)                                         \
	do {                                                                  \
		(item)->next = (list)->next;                                      \
		(item)->prev = (list);                                            \
		(list)->next->prev = (item);                                      \
		(list)->next = (item);                                            \
	} while(0);                                                           \

#define list_del_node(list)                                               \
	do {                                                                  \
		(list)->next->prev = (list)->prev;                                \
		(list)->prev->next = (list)->next;                                \
		(list)->prev = (list)->next = 0;                                  \
	} while(0);

#endif /* __LIB_LOG_LIST_H */
