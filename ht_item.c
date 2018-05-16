/*
 *
 * ht_item.c
 *
 * Baltasar Dinis 89416
 * IAED project
 *
 * defines ht_item datatype
 *
 */


#include "ht_item.h"


/*
 * function: ht_key
 *
 * gets the key of a ht_item
 *   a: ht_item
 */
key_t ht_key(ht_item a)
{
  if (a != NULL_HT_ITEM) 
    return (l_key(val(*a)));

  return 0;
}

/*
 * function: free_ht_item
 *
 * frees an ht_item
 *   a: ht_item
 */
void free_ht_item(ht_item a)
{
  free_l_node(a);
}
