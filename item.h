/*
 *
 * dummy.h
 *
 * Baltasar Dinis 89416
 * IAED project
 *
 * header file for item.c
 *
 * defines item datatype
 *
 * to change the underlying datatype for the linked list implementation
 * done in "list.c", simply change the name in this file and rename another
 * file as "item.h"
 *
 */

#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <stdlib.h>

#include "p_task.h"

typedef p_task * item;

typedef unsigned long key_t;
#define less_key(a, b) (a < b)
#define eq_key(a, b) (a == b)

key_t get_key(item a);

void free_item(item a);

#endif /* !ITEM_H */
