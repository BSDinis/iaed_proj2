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
  size_t i = 1;

  while (fgets(str, CMD_BUFFER, stdin) != NULL) {
    printf("::::TEST %lu:::::\n", i);
    printf("%s -> ", str);

    /*
    t = get_task(&str);
    printf("%s ", str);

    if (!valid_task(t)) {
      printf("illegal arguments\n");
      printf("\n\n");
      i++;
      free_task(t);
      continue;
    }

    aux = print_task(t);
    printf("orig: %s ||", aux);
    free(aux);

    change_task_duration(&t, id(t));
    change_task_description(&t, "\"i am a dummy description\"");

    aux = print_task(t);
    printf("changed: %s\n", aux);
    free(aux);

    if (valid_early(t) && valid_late(t)) 
      printf("%lu : %lu\n", early(t), late(t));

    change_early(&t, 2224);
    change_late(&t, 2224);

    if (valid_early(t) && valid_late(t)) 
      printf("%lu : %lu\n", early(t), late(t));

    printf("\n\n");
    i++;
    free_task(t);
    */
  }

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

  if (!get_quoted_str(&cmd_str, &description, MAX_QUOTED_STR)) {
    printf("illegal arguments\n");
    cmd_str[0] = '\0';
    return t;
  }
  if (!get_ulong(&cmd_str, &dur)) {
    printf("illegal arguments\n");
    cmd_str[0] = '\0';
    free(description);
    return t;
  }

  for (j = 0; j < i; depen[j] = &(list[j]), j++);

  t = p_task_(task_(i, description, dur), depen, i);
  free(description);
  free(depen);
  return t;
}
