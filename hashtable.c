/*
 *
 * hashtable.h
 *
 * Baltasar Dinis 89416
 * IAED project
 *
 * implements a hash table with a double hash
 *
 */

#include "hashtable.h"

#define max(a, b) ((a > b) ? a : b)
#define min(a, b) ((a < b) ? a : b)

/*-------------------------------*/
/* prototypes */
/*-------------------------------*/

/* fix hashtable alloc'ing more space */
static void fix_hashtable(hashtable *t);

/*-------------------------------*/
/*-------------------------------*/
/*-------------------------------*/

/* 
 * function: hashtable_
 *
 * constructor for the hashtable datatype
 *
 * return: ptr to hashtable
 */
hashtable *hashtable_()
{
  hashtable *t = (hashtable *) malloc(sizeof(hashtable));
  size_t i;

  size(*t) = INIT_HASH_SIZE;
  filled(*t) = 0;
  table(*t) = (item *) malloc(size(*t) * sizeof(item));

  for (i = 0; i < size(*t); table(*t)[i] = NULL_ITEM);

  return t;
}


/*
 * function: hash_1
 *
 * computes the first (main) hash
 *   t: ptr to hashtable
 *   k: key of an item
 *
 * returns: index
 */
size_t hash_1(hashtable *t, key_t k)
{
  return (k % size(*t));
}


/*
 * function: hash_2
 *
 * computes the second(ary) hash
 *   k: key_t
 *
 * returns: index
 */
size_t hash_2(key_t k)
{
  return 1 + (k % HASH_STEP);
}


/*
 * function: insert_hashtable
 *
 * inserts an element in hashtable
 *   t: ptr to hashtable
 *   k: item
 */
void insert_hashtable(hashtable *t, item i)
{
  size_t index;
  size_t step; 
  if (!eq_item(i, NULL_ITEM)) {
    index = hash_1(t, get_key(i));
    step = hash_2(get_key(i)); 
    while (!eq_item(table(*t)[index], NULL_ITEM))
      index = (index + step) % size(*t);

    table(*t)[index] = i;
    filled(*t)++;

    if (density(*t) > 0.5)
      fix_hashtable(t);
  }
}


/*
 * function: fix_hashtable(t)
 *
 * reallocs memory for hashtable when the density exceeds 50%
 *   t: ptr to hashtable
 */
static void fix_hashtable(hashtable *t)
{
  item *aux;
  size_t i;
  if (density(*t) > 0.5) {
    aux = (item *) malloc(size(*t) * sizeof(item));
    for (i = 0; i < size(*t); i++)
      aux[i] = table(*t)[i];

    size(*t) *= 2;
    free(table(*t));
    table(*t) = (item *) malloc(size(*t) * sizeof(item));
    for (i = 0; i < size(*t); table(*t)[i++] = NULL_ITEM);

    for (i = 0; i < (size(*t) / 2); i++) {
      if (!eq_item(aux[i], NULL_ITEM)) {
        insert_hashtable(t, aux[i]);
      }
    }
  }
}


/*
 * function: remove_hashtable
 *
 * removes an element from hashtable
 *   t: ptr to hashtable
 *   k: item
 */
void remove_hashtable(hashtable *t, item i)
{
  size_t index = hash_1(t, get_key(i));
  size_t step = hash_2(get_key(i));
  while (!eq_item(table(*t)[index], NULL_ITEM) 
      && !eq_item(table(*t)[index], i)) {
    index = (index + step) % size(*t);
  }

  if (!eq_item(table(*t)[index], NULL_ITEM)) {
    table(*t)[index] = SENTINEL;
    filled(*t)--;
  }
}


/*
 * function: search_hashtable
 *
 * search for an item with a given key
 *   t: ptr to hashtable
 *   key: key to search for
 *
 * return: item
 */
item search_item(hashtable *t, key_t k)
{
  size_t index = hash_1(t, k);
  size_t step = hash_2(k);
  while (!eq_item(table(*t)[index], NULL_ITEM) 
      && !eq_key(get_key(table(*t)[index]), k))
    index = (index + step) % size(*t);

  return table(*t)[index];
}
