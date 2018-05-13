/*
 *
 * dummy.h
 *
 * Baltasar Dinis 89416
 * IAED project
 *
 * header file for l_item.c
 *
 * defines l_item (list item) datatype
 *
 * to change the underlying datatype for the linked list implementation
 * done in "list.c", simply change the name in this file and rename another
 * file as "l_item.h"
 *
 */

#ifndef L_ITEM_H
#define L_ITEM_H

#include <stdio.h>
#include <stdlib.h>

#include "p_task.h"

typedef p_task l_item;

unsigned long get_key(l_item l);

void free_l_item(l_item l);

#endif /* !L_ITEM_H */
