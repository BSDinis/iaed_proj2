/*
 *
 * Baltasar Dinis 89416
 * IAED Project
 *
 * test_tree.c
 *
 *
 * Test program for tree.h
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include "../task.h"
#include "../p_task.h"
#include "../tree.h"

#define LIST_SIZE 10

int main()
{
  size_t i;
  p_task *p;
  task *t;

  tree *t;
  t_node *node;

  char *str;
  char *aux = (char *) malloc(14 * sizeof(char));

  p_task **depends = malloc(LIST_SIZE * sizeof(p_task *));
  strcpy(aux, "\"dummy task\"");
  t = tree_();


  printf("initializing tree... ");
  for (i = 0; i < LIST_SIZE; i++) {
    t = task_(i + 1, aux, i*2 + 1);
    p = p_task_(t, depends, i);

    change_early(p, 2*i);
    change_late(p, i*i);
    depends[i] = p;

    insert
  }

  printf("done\n\n");

  node = go_next(head(*l));
  while (!is_tail(node)) {
    str = print_p_task(val(*node), true);
    printf("node %p: %s\n", (void *) node, str);
    free(str);
    node = go_next(node);
  }


  free_lnkd_list(l);

  free(aux);
  free(depends);
  return 0;
}

