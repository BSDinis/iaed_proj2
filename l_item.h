/*
 *
 * l_item.h
 *
 * Baltasar Dinis 89416
 * IAED project
 *
 * header file for l_item.c
 *
 * defines l_item datatype
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
#include "key_t.h"

typedef p_task* l_item;

#define NULL_L_ITEM NULL
#define INVALID_L_ITEM ((l_item) ULONG_MAX)

key_t l_key(l_item a); 

void free_l_item(l_item a);

#endif /* !L_ITEM_H */
