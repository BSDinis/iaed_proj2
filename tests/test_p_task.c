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
#include "../input.h"

#define CMD_BUFFER 10000
#define MAX_QUOTED_STR 8000
#define LIST_SIZE 10

p_task get_p_task(char *cmd_str, int i, p_task list[LIST_SIZE]);

int main()
{
  char *str = (char *) malloc((CMD_BUFFER + 1) * sizeof(char));
  char *orig = str;
  char *aux; 
  p_task list[LIST_SIZE];
  size_t i = 0;

  while (fgets(str, CMD_BUFFER, stdin) != NULL) {
    printf("::::TEST %lu:::::\n", i + 1);
    printf("%s\n", str);

    list[i] = get_p_task(str, i, list);

    if (!valid_p_task(list[i])) {
      printf("illegal arguments\n");
      printf("\n\n");
      i++;
      return 1;
      continue;
    }

    aux = print_p_task(list[i], false);
    printf("without path: %s \n", aux);
    free(aux);

    if (valid_early(list[i]) && valid_late(list[i])) 
      printf("%lu : %lu\n", early(list[i]), late(list[i]));

    change_early(&list[i], 2 * i);
    change_late(&list[i], i * i);

    aux = print_p_task(list[i], true);
    printf("with path: %s \n", aux);
    free(aux);

    printf("\n\n");
    i++;
  }

  for(i = 0; i < LIST_SIZE; free_p_task(list[i++]));
  free(orig);
  return 0;
}


p_task get_p_task(char *cmd_str, int i, p_task list[LIST_SIZE])
{
  unsigned long dur;
  int j;  
  char *description;
  p_task t; 
  p_task **depen = (p_task **) malloc(i * sizeof(p_task *));

  get_quoted_str(&cmd_str, &description, MAX_QUOTED_STR);
  get_ulong(&cmd_str, &dur);
  for (j = 0; j < i; depen[j] = &(list[j]), j++);

  t = p_task_(task_(i, description, dur), depen, i);
  free(description);

  description = print_task(task(t));
  printf("task: %s\n", description);
  free(description);

  free(depen);
  return t;
}
