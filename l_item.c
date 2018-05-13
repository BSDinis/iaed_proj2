/*
 *
 * l_item.c
 *
 * Baltasar Dinis 89416
 * IAED project
 *
 * defines l_item (list item) datatype
 *
 * to change the underlying datatype for the linked list implementation
 * done in "list.c", simply change the name in this file and rename another
 * file as "l_item.h"
 *
 */


#include "l_item.h"


unsigned long get_key(l_item l)
{
  return id(task(l));
}

void free_l_item(l_item l)
{
  free_p_task(l);
}
