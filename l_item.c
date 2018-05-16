/*
 *
 * l_item.c
 *
 * Baltasar Dinis 89416
 * IAED project
 *
 * defines l_item datatype
 *
 * to change the underlying datatype for the linked list implementation
 * done in "list.c", simply change the name in this file and rename another
 * file as "l_item.h"
 *
 */


#include "l_item.h"

/*
 * function: l_item
 *
 * gets a key from an l_item
 *   a: l_item
 *
 * return: key_t
 */
key_t l_key(l_item a)
{
  if (a != NULL) 
    return (id(*task(*a)));

  return 0;
}

/*
 * function: free_l_item
 *
 * frees an l_item
 *   a: l_item
 */
void free_l_item(l_item a)
{
  free_p_task(a);
}
