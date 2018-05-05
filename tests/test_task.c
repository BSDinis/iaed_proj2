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
#include "../task.h"

#define CMD_BUFFER 10000

int main()
{
  char *str = (char *) malloc((CMD_BUFFER + 1) * sizeof(char));
  task t;
  size_t i = 1;

  while (fgets(str, CMD_BUFFER, stdin) != NULL) {
    printf("::::TEST %lu:::::\n", i);
    printf("%s -> ", str);
    t = get_task(&str);
    printf("%s ", str);

    if (!valid_task(t)) {
      printf("illegal arguments\n");
      printf("\n\n");
      i++;
      continue;
    }

    printf("orig: %s ||", print_task(t));
    change_task_duration(&t, id(t));
    change_task_description(&t, "\"i am a dummy description\"");
    printf("changed: %s\n", print_task(t));

    if (valid_early(t) && valid_late(t)) 
      printf("%lu : %lu\n", early(t), late(t));

    change_early(&t, 2224);
    change_late(&t, 2224);

    if (valid_early(t) && valid_late(t)) 
      printf("%lu : %lu\n", early(t), late(t));

    printf("\n\n");
    i++;
  }

  return 0;
}
