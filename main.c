/*
 *
 * main.c
 *
 * Baltasar Dinis 89416
 * IAED project
 *
 * main file
 *
 * defines the interaction for the program
 *
 * dependencies:
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "task.h"
#include "p_task.h"
#include "input.h"
#include "planner.h"
#include "cmd.h"

/* 
 * number of possible command
 * also the number of implemented functionallities, 
 * represented by their wrapper functions
 */
#define N_CMDS 6

/*-------------------------------*/
/* prototypes */
/*-------------------------------*/

void add(planner *project);

void duration(planner *project);

void depend(planner *project);

void remove_task(planner *project);

void path(planner *project);

void exit_proj(planner *project);

/*-------------------------------*/
/*-------------------------------*/
/*-------------------------------*/


int main(int argc, char *argv[])
{
  cmd command;

  planner *project;

  /* function array, with the implemented functionalities */
  void (*func[])(planner *) = 
    {&add, &duration, &depend, &remove_task, &path, &exit_proj};

  project = planner_();

  do {
    if (end_of_file())
      return 1;

    command = get_cmd();

    if (valid_command(command)) {
      func[command](project);
    }
    else {
      printf("illegal arguments\n");
    }

    /* move stream to next line */
    fgetc(stdin);
  } while(command != EXIT);
    
  return 0;
}


/*
 * function: get_cmd
 *
 * gets a command from a string
 *   cmd_str: string 
 *
 * return: cmd, with a specific command
 *   wrong input returns INVALID
 *
 */
cmd get_cmd()
{
  cmd c;
  char *cmd_str = NULL;

  if (!get_str(&cmd_str))
    return INVALID;

  if (strcmp(cmd_str, "add") == 0)
    c = ADD;
  else if (strcmp(cmd_str, "duration") == 0)
    c = DUR;
  else if (strcmp(cmd_str, "depend") == 0)
    c = DEP;
  else if (strcmp(cmd_str, "remove") == 0) 
    c = RM;
  else if (strcmp(cmd_str, "path") == 0)
    c = PATH;
  else if (strcmp(cmd_str, "exit") == 0) 
    c = EXIT;
  else 
    c = INVALID;

  free(cmd_str);
  return c;
}


/*
 * function: add
 *
 * adds a task to the project
 *   cmd_str: command string, only with the arguments
 *
 * parses the rest of the cmd string to call the add_task function 
 * correct input:
 *   add <id> <description> <dur> <ids>
 */
void add(planner *project)
{
  size_t n_ids;
  unsigned long id, dur, *ids;
  char *description;

  if (!get_ulong(&id)) {
    printf("illegal arguments\n");
    return;
  }
  if (!get_quoted_str(&description)) {
    printf("illegal arguments\n");
    return;
  }
  if (!get_ulong(&dur)) {
    printf("illegal arguments\n");
    free(description);
    return;
  }
  if (!get_ulong_list(&ids, &n_ids)) {
    printf("illegal arguments\n");
    free(description);
    return;
  }

  add_task(project, id, description, dur, ids, n_ids);
  free(description);
  free(ids);
}


/*
 * function: duration
 *
 * lists the tasks with a given (or longer) duration
 *   cmd_str: command string, only with the arguments
 *
 * parses the rest of the cmd string to call the list_task_duration function 
 */
void duration(planner *project)
{
  unsigned long dur = 0;

  if (end_of_line()) {
    print_with_duration(project, 0);
  }
  else if (!get_ulong(&dur) || !end_of_line()) {
    printf("illegal arguments\n");
    return;
  }
  else {
    print_with_duration(project, dur);
  }
}

/*
 * function: depend
 *
 * lists the dependencies of a task
 *   cmd_str: command string, only with the arguments
 *
 * parses the rest of the cmd string to call the list_dependencies function 
 */
void depend(planner *project)
{
  unsigned long id = 0;

  if (!get_ulong(&id) || !end_of_line()) {
    printf("illegal arguments\n");
    return;
  }

  print_dependencies(project, id);
}


/*
 * function: remove_task
 *
 * removes a task from the project
 *   cmd_str: command string, only with the arguments
 *
 * parses the rest of the cmd string to call the remove_task_id function 
 */
void remove_task(planner *project)
{
  unsigned long id;

  if (!get_ulong(&id) || !end_of_line()) {
    printf("illegal arguments\n");
    return;
  }

  remove_task_id(project, id);
}

/*
 * function: path
 *
 * lists the critical path of a project
 *   cmd_str: command string, only with the arguments
 *
 * parses the rest of the cmd string to call the proj_path function
 */
void path(planner *project)
{
  if (!end_of_line()) {
    printf("illegal arguments\n");
  }

  print_critical_path(project);
}


/*
 * function: exit_proj
 *
 * packs everything up to quit the program
 *   cmd_str: command string, only with the arguments
 *
 * parses the rest of the cmd string to call the free_project function
 */
void exit_proj(planner *project)
{
  if (!end_of_line()) {
    printf("illegal arguments\n");
  }

  free_planner(project);
}
