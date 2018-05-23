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
#define N_CMDS 8

/*-------------------------------*/
/* prototypes */
/*-------------------------------*/

void add(planner *project);

void duration(planner *project);

void depend(planner *project);

void remove_task(planner *project);

void path(planner *project);

void first(planner *project);

void second(planner *project);

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
    {&add, &duration, &depend, &remove_task, &path, &first, &second, &exit_proj};

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
    flush_line();
  } while(command != EXIT);
    
  return 0;
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
  if (ids != NULL) 
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
 * function: first
 *
 * prints the largest task_id of the project
 *   project: ptr to planner
 *
 * parses the rest of the cmd string to call the print_largest_id function
 */
void first(planner *project)
{
  if (!end_of_line()) {
    printf("illegal arguments\n");
  }

  print_largest_id(project);
}


/*
 * function: second
 *
 * prints the id of the task with more dependencies
 *   project: ptr to planner
 *
 * parses the rest of the cmd string to call the print_task_with_more_dependencies
 * dependencies
 */
void second(planner *project)
{
  if (!end_of_line()) {
    printf("illegal arguments\n");
  }

  print_task_with_more_dependencies(project);
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
