/*
 *
 * item.c
 *
 * Baltasar Dinis 89416
 * IAED project
 *
 * defines item datatype
 *
 * to change the underlying datatype for the linked list implementation
 * done in "list.c", simply change the name in this file and rename another
 * file as "item.h"
 *
 */


#include "item.h"

/*
 * function: get_key
 *   a: item
 *
 * return: items' key
 */
unsigned long get_key(item a)
{
  return id(*task(*a));
}

/*
 * function: free_item
 *
 * frees an item
 *   a: item
 */
void free_item(item a)
{
  free_p_task(a);
  free(a);
}
