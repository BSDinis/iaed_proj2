/*
 *
 * Baltasar Dinis 89416
 * IAED Project
 *
 * test_task.c
 *
 *
 * Test program for task.h
 *
 * Performs the following checks:
 *   Input:
 *     gets a series of tasks
 *     make sure it is validated properly
 *
 *   Modifiers:
 *     changes the duration to match the id
 *     change the description
 *     gives early and late a value
 *     checks if they are valid first
 *
 *   Outputing:
 *     checks the print function
 *
 *   Destructor:
 *     frees the task
 */


#include <stdio.h>
#include <stdlib.h>
#include "../p_task.h"
#include "../task.h"

#define LIST_SIZE 10

int main()
{
  p_task list[LIST_SIZE];
  char *str;
  size_t i;
  task t[LIST_SIZE];
  char *aux = (char *) malloc(14 * sizeof(char));
  p_task **depends = malloc(LIST_SIZE * sizeof(p_task *));
  strcpy(aux, "\"dummy task\"");

  for (i = 0; i < LIST_SIZE; i++) {
    t[i] = task_(i + 1, aux, i*2 + 1);
    list[i] = p_task_(t[i], depends, i);
    change_early(&(list[i]), 2*i);
    change_late(&(list[i]), i*i);
    depends[i] = &(list[i]);
    str = print_p_task(list[i], false);
    printf("p_task %lu: %s\n", i + 1, str);
    free(str);
  }


  printf("\n\n");
  for (i = 0; i < LIST_SIZE; i++) {
    str = print_p_task(list[i], true);
    printf("p_task %lu: %s\n", i + 1, str);
    free(str);
  }

  for (i = 0; i < LIST_SIZE; i++) {
    free_p_task(list[i]);
  }


  free(aux);
  free(depends);
  return 0;
}

