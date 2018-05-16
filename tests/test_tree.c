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

  tree *t;
  t_node *node;

  char *str;
  char *aux = (char *) malloc(14 * sizeof(char));

  p_task **depends = malloc(LIST_SIZE * sizeof(p_task *));
  strcpy(aux, "\"dummy task\"");
  t = tree_();


  printf("initializing tree... ");
  for (i = 0; i < LIST_SIZE; i++) {
    p = p_task_(task_(i + 1, aux, i*2 + 1), depends, i);

    change_early(p, 2*i);
    change_late(p, i*i);
    depends[i] = p;

    insert_t_node(t, p);
  }

  printf("done\n\n");
  
  for (i = 0; i < LIST_SIZE; i++) {
    node = search_by_key(t, i);
    str = print_p_task(val(*node), (i % 4 == 0));
    if (i % 2 == 0) {
      printf("deleting node:\n%s\n...", str);
      printf("deleted node %lu\n", delete_t_node(t, node));
    }

    printf("task: %s\n", str);
    free(str);
  }

  free_tree(t);
  free(aux);
  free(depends);
  return 0;
}





