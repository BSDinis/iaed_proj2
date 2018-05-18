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
  size_t i = 0;

  size(*t) = INIT_HASH_SIZE;
  filled(*t) = 0;
  table(*t) = (ht_item *) malloc(size(*t) * sizeof(ht_item));

  for (i = 0; i < size(*t); i++) {
    table(*t)[i] = NULL_HT_ITEM;
  }

  return t;
}


/*
 * function: hash_1
 *
 * computes the first (main) hash
 *   t: ptr to hashtable
 *   k: key of an ht_item
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
 *   k: ht_item
 */
void insert_hashtable(hashtable *t, ht_item i)
{
  size_t index;
  size_t step; 
  if (!eq_ht_item(i, NULL_HT_ITEM)) {
    index = hash_1(t, ht_key(i));
    step = hash_2(ht_key(i)); 
    while (!eq_ht_item(table(*t)[index], NULL_HT_ITEM))
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
  ht_item *aux;
  size_t aux_size;
  size_t i;
  if (density(*t) > 0.5) {

    aux = (ht_item *) malloc(size(*t) * sizeof(ht_item));
    for (i = aux_size = 0; i < size(*t); i++) {
      if (table(*t)[i] != SENTINEL && table(*t)[i] != NULL) {
        aux[aux_size++] = table(*t)[i];
      }
    }

    size(*t) *= 2;
    free(table(*t));
    table(*t) = (ht_item *) malloc(size(*t) * sizeof(ht_item));
    for (i = 0; i < size(*t); table(*t)[i++] = NULL_HT_ITEM);

    for (i = 0; i < aux_size; i++) {
      insert_hashtable(t, aux[i]);
    }

    free(aux);
  }
}


/*
 * function: remove_hashtable
 *
 * removes an element from hashtable
 *   t: ptr to hashtable
 *   k: ht_item
 */
void remove_hashtable(hashtable *t, ht_item i)
{
  size_t index = hash_1(t, ht_key(i));
  size_t step = hash_2(ht_key(i));
  while (!eq_ht_item(table(*t)[index], NULL_HT_ITEM) 
      && !eq_ht_item(table(*t)[index], i)) {
    index = (index + step) % size(*t);
  }

  if (!eq_ht_item(table(*t)[index], NULL_HT_ITEM)) {
    table(*t)[index] = SENTINEL;
    filled(*t)--;
  }
}


/*
 * function: search_hashtable
 *
 * search for an ht_item with a given key
 *   t: ptr to hashtable
 *   key: key to search for
 *
 * return: ht_item
 */
ht_item search_hashtable(hashtable *t, key_t k)
{
  size_t index = hash_1(t, k);
  size_t step = hash_2(k);

  while (table(*t)[index] == SENTINEL || 
      (!eq_ht_item(table(*t)[index], NULL_HT_ITEM)
       && !eq_key(ht_key(table(*t)[index]), k)) ) {

    index = (index + step) % size(*t);
  }

  return table(*t)[index];
}


/*
 * function: free_hashtable
 *
 * destructor for the hashtable datatype
 *   ht: ptr to hashtable
 *
 * note: since in this application, the elements in the table will be 
 * freed by another module, and freeing all elements in the hashtable is 
 * relatively heavy (O(hashtable.size)), this function does not free the 
 * elements
 */
void free_hashtable(hashtable *ht)
{
  if (ht != NULL) {
    if (table(*ht) != NULL) 
      free(table(*ht));

    free(ht);
    ht = NULL;
  }
}

      
