/*
 *
 * hashtable.h
 *
 * Baltasar Dinis 89416
 * IAED project
 *
 * header file for hashtable.c
 *
 * implements a hash table with a double hash
 *
 */

#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>

#include "ht_item.h"

/* initial size for hash table: arbitrary prime */
#define INIT_HASH_SIZE 131

/* prime for second hash function must be different than INIT_HASH_SIZE */
#define HASH_STEP 7

/* define the sentinel, 
 * placed when a previous value was removed from the table */
#define SENTINEL (INVALID_HT_ITEM)

/* define hashtable */
typedef struct  {
  ht_item *table;
  size_t size, filled;
} hashtable;

/* selectors: added trivial computation for density */
#define table(a) ((a).table)
#define size(a) ((a).size)
#define filled(a) ((a).filled)
#define density(a) ( ((double) filled(a)) / ((double) size(a)) )

/* initialize hash table */
hashtable *hashtable_();

/* hash functions */
size_t hash_1(hashtable *t, key_t k);
size_t hash_2(key_t k);

/* insert ht_item */
void insert_hashtable(hashtable *t, ht_item k);

/* remove ht_item */
void remove_hashtable(hashtable *t, ht_item k);

/* search for ht_item */
ht_item search_hashtable(hashtable *t, key_t k);

/* free a hashtable (but not its elements!) */
void free_hashtable(hashtable *ht);

#endif /* !HASH_H */
