/**
 * @file
 * @author Oleh Kravchenko <oleg@kaa.org.ua>
 *
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

#ifndef __TOOLS_LIST_H
#define __TOOLS_LIST_H

#include <stddef.h>

/*------------------------------------------------------------------------*/

/** node of double-linked list */
struct list {
	/** pointer to previous node */
	struct list *prev;

	/** pointer to next node */
	struct list *next;
};

/*------------------------------------------------------------------------*/

/** should be used to static initialization */
#define list_initializer(list) { .prev = list, .next = list, }

/*------------------------------------------------------------------------*/

/** return pointer to struct of type, which hold field */
#define containerof(ptr, type, field)                                     \
	((type*)((size_t)(ptr) - offsetof(type, field)))

/*------------------------------------------------------------------------*/

/** iterate over all list nodes */
#define list_foreach(list, node, type, field)                             \
	for((node) = containerof((list)->next, type, field);                  \
		&(node)->field != (list);                                         \
		(node) = containerof((node)->field.next, type, field))

/*------------------------------------------------------------------------*/

/** iterate over all list nodes, also allow node deletion */
#define list_foreach_safe(list, node, temp, type, field)                  \
	for(node = containerof((list)->next, type, field),                    \
		temp = containerof((node)->field.next, type, field);              \
		&(node)->field != (list);                                         \
		node = temp, temp = containerof((temp)->field.next, type, field))

/*------------------------------------------------------------------------*/

/** add node to list */
#define list_add_node(list, node)                                         \
	do {                                                                  \
		(node)->next = (list)->next;                                      \
		(node)->prev = (list);                                            \
		(list)->next->prev = (node);                                      \
		(list)->next = (node);                                            \
	} while(0);                                                           \

/*------------------------------------------------------------------------*/

/** remove node from list */
#define list_del_node(node)                                               \
	do {                                                                  \
		(node)->next->prev = (node)->prev;                                \
		(node)->prev->next = (node)->next;                                \
		(node)->prev = (node)->next = 0;                                  \
	} while(0);

#endif /* __TOOLS_LIST_H */
