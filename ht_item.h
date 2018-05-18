/*
 *
 * ht_item.h
 *
 * Baltasar Dinis 89416
 * IAED project
 *
 * header file for ht_item.c
 *
 * defines ht_item datatype
 *
 */

#ifndef HT_ITEM_H
#define HT_ITEM_H

#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "l_item.h"

typedef l_node * ht_item;


/* get the key_t */
key_t ht_key(ht_item a);

#define eq_ht_item(a, b) ( eq_key(ht_key(a), ht_key(b)) )

/* frees an ht_item */
void free_ht_item(ht_item a);

#define NULL_HT_ITEM NULL
#define INVALID_HT_ITEM ((ht_item) ULONG_MAX)

#endif /* !HT_ITEM */
