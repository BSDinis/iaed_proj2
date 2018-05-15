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
 *
 *   Outputing:
 *     checks the print function
 *
 *   Destructor:
 *     frees the task
 */


#include <stdio.h>
#include <stdlib.h>
#include "../task.h"
#include "../input.h"

#define CMD_BUFFER 10000

int main()
{
  char *aux;
  char *descript = malloc(100 * sizeof(char));
  task *t;
  size_t i;

  for (i = 0; i < 10; printf("\n\n"), i++) {
    printf("::::TEST %lu:::::\n", i + 1);
    if (i != 0)
      sprintf(descript, "\"task %lu is a bitch\"", i);
    else
      sprintf(descript, "i'm a boss ass bitch");

    t = task_(i, descript, i*i);

    if (!valid_task(t)) {
      printf("illegal arguments\n");
      continue;
    }

    aux = print_task(t);
    printf("orig: %s ||", aux);
    free(aux);

    change_task_duration(t, id(*t) + 1);
    change_task_description(t, "\"i am a dummy description\"");

    aux = print_task(t);
    printf("changed: %s\n", aux);
    free(aux);

    free_task(t);
    free(t);
  }

  free(descript);
  return 0;
}
