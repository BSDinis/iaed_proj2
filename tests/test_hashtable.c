/*
 *
 * Baltasar Dinis 89416
 * IAED Project
 *
 * test_hashtable.c
 *
 *
 * Test program for hashtable.h
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include "../task.h"
#include "../p_task.h"
#include "../list.h"
#include "../ht_item.h"
#include "../hashtable.h"

#define LIST_SIZE 10

int main()
{
  size_t i;
  p_task *p;
  task *t;

  lnkd_list *l;
  hashtable *ht;
  l_node *node;


  char *str;
  char *aux = (char *) malloc(14 * sizeof(char));

  p_task **depends = malloc(LIST_SIZE * sizeof(p_task *));
  strcpy(aux, "\"dummy task\"");
  l = lnkd_list_();
  ht = hashtable_();

  printf("initializing list... ");
  for (i = 0; i < LIST_SIZE; i++) {
    t = task_(i + 1, aux, i*2 + 1);
    p = p_task_(t, depends, i);

    change_early(p, 2*i);
    change_late(p, i*i);
    depends[i] = p;

    add_at_end(l, p);
    node = prev(*tail(*l));
    insert_hashtable(ht, node);
  }

  printf("done\n\n");

  for (i = 0; i < LIST_SIZE; i += 1) {
    node = search_hashtable(ht, i);
    if (node != NULL_HT_ITEM) {
      str = print_p_task(val(*node), true);
      printf("key %lu: node %p: %s\n", i, (void *) node, str);
      free(str);
    }
  }

  printf("done\n\n");
  for (i = 0; i < LIST_SIZE; i += 3) {
    node = search_hashtable(ht, i);
    if (node != NULL_HT_ITEM) {
      str = print_p_task(val(*node), true);
      printf("key %lu: node %p: %s\n", i, (void *) node, str);
      free(str);
    }
  }

  printf("\nremoving elements...");
  for (i = 2; i < LIST_SIZE; i += 3) {
    node = search_hashtable(ht, i);
    if (node != NULL_HT_ITEM) {
      remove_hashtable(ht, node);
      remove_l_node(node);
    }
  }
  printf("done\n\n");

  for (i = 0; i < LIST_SIZE; i++) {
    node = search_hashtable(ht, i);
    if (node != NULL_HT_ITEM) {
      str = print_p_task(val(*node), true);
      printf("key %lu: node %p: %s\n", i, (void *) node, str);
      free(str);
    }
  }

  free_lnkd_list(l);
  free_hashtable(ht);

  free(aux);
  free(depends);
  return 0;
}

