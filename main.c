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
#include "input.h"
#include "dummy.h"

/* TODO: get a hold of the correct val */
#define CMD_BUFFER 10000

/* maximum size of a quoted string */
#define MAX_QUOTED_STR 8000

/* 
 * number of possible command
 * also the number of implemented functionallities, 
 * represented by their wrapper functions
 */
#define N_CMDS 6

/*
 * define the command type, cmd
 */
typedef enum {ADD = 0, DUR, DEP, RM, PATH, EXIT, INVALID} cmd;

/*-------------------------------*/
/* prototypes */
/*-------------------------------*/

cmd get_cmd(char **cmd_str);

bool valid_command(cmd c);

void add(char *cmd_str);

void duration(char *cmd_str);

void depend(char *cmd_str);

void remove_task(char *cmd_str);

void path(char *cmd_str);

void exit_proj(char *cmd_str);

/*-------------------------------*/
/*-------------------------------*/
/*-------------------------------*/


int main(int argc, char *argv[])
{
  cmd command;
  char *cmd_str;
  char *orig;

  /* function array, with the implemented functionalities */
  void (*func[])(char *) = 
    {&add, &duration, &depend, &remove_task, &path, &exit_proj};

  do {
    if ((cmd_str = get_line()) == NULL) return 1;

    orig = cmd_str;
    command = get_cmd(&cmd_str);

    if (valid_command(command)) {
      func[command](cmd_str);
    }
    else {
      printf("illegal arguments\n");
    }

    free(orig);
  } while(command != EXIT);
    
  return 0;
}


/*
 * function: get_cmd
 *
 * gets a command from the first token of the string
 *   cmd_str_ptr: pointer to a string (cmd_str)
 *
 * return: cmd, with a specific command
 *   wrong input returns INVALID
 *
 * cmd_str is flushed to the next arg
 */
cmd get_cmd(char **cmd_str_ptr)
{
  cmd c;
  char *token;

  if (!get_str(cmd_str_ptr, &token)) {
    free(token);
    return INVALID;
  }
  else {
    if (strcmp(token, "add") == 0)
      c = ADD;
    else if (strcmp(token, "duration") == 0)
      c = DUR;
    else if (strcmp(token, "depend") == 0)
      c = DEP;
    else if (strcmp(token, "remove") == 0) 
      c = RM;
    else if (strcmp(token, "path") == 0)
      c = PATH;
    else if (strcmp(token, "exit") == 0) 
      c = EXIT;
    else 
      c = INVALID;
  }

  free(token);
  return c;
}


/*
 * function: valid_command
 *
 * checks if a command is valid
 *   c: command to be checked
 */
bool valid_command(cmd c)
{
  return c != INVALID;
}


/*
 * function: add
 *
 * adds a task to the project
 *   cmd_str: command string, only with the arguments
 *
 * parses the rest of the cmd string to call the add_task function TODO
 * correct input:
 *   add <id> <description> <dur> <ids>
 */
void add(char *cmd_str)
{
  size_t n_ids;
  unsigned long id, dur, *ids;
  char *description;

  if (!get_ulong(&cmd_str, &id)) {
    printf("illegal arguments\n");
    cmd_str[0] = '\0';
    return;
  }
  if (!get_quoted_str(&cmd_str, &description, MAX_QUOTED_STR)) {
    printf("illegal arguments\n");
    cmd_str[0] = '\0';
    return;
  }
  if (!get_ulong(&cmd_str, &dur)) {
    printf("illegal arguments\n");
    cmd_str[0] = '\0';
    free(description);
    return;
  }
  if (!get_ulong_list(&cmd_str, &ids, &n_ids)) {
    printf("illegal arguments\n");
    cmd_str[0] = '\0';
    free(description);
    return;
  }

  add_task(id, description, dur, ids, n_ids);
  free(description);
  free(ids);
}


/*
 * function: duration
 *
 * lists the tasks with a given (or longer) duration
 *   cmd_str: command string, only with the arguments
 *
 * parses the rest of the cmd string to call the list_task_duration function TODO
 */
void duration(char *cmd_str)
{
  unsigned long dur = 0;

  if (empty_str(cmd_str)) {
    list_task_duration(0);
  }
  else if (!get_ulong(&cmd_str, &dur) || !empty_str(cmd_str)) {
    printf("illegal arguments\n");
    return;
  }

  list_task_duration(dur);
}

/*
 * function: depend
 *
 * lists the dependencies of a task
 *   cmd_str: command string, only with the arguments
 *
 * parses the rest of the cmd string to call the list_dependencies function TODO
 */
void depend(char *cmd_str)
{
  unsigned long id;

  if (!get_ulong(&cmd_str, &id) || !empty_str(cmd_str)) {
    printf("illegal arguments\n");
    return;
  }

  list_dependencies(id);
}


/*
 * function: remove_task
 *
 * removes a task from the project
 *   cmd_str: command string, only with the arguments
 *
 * parses the rest of the cmd string to call the remove_task_id function TODO 
 */
void remove_task(char *cmd_str)
{
  unsigned long id;

  if (!get_ulong(&cmd_str, &id) || !empty_str(cmd_str)) {
    printf("illegal arguments\n");
    return;
  }

  remove_task_id(id);
}

/*
 * function: path
 *
 * lists the critical path of a project
 *   cmd_str: command string, only with the arguments
 *
 * parses the rest of the cmd string to call the proj_path function TODO
 */
void path(char *cmd_str)
{
  if (!empty_str(cmd_str)) {
    printf("illegal arguments\n");
  }

  printf("the path of the righteous man is beset on all sides by the inequities of the selfish and the tiranny of evil men\n");
}


/*
 * function: exit_proj
 *
 * packs everything up to quit the program
 *   cmd_str: command string, only with the arguments
 *
 * parses the rest of the cmd string to call the free_project function TODO
 */
void exit_proj(char *cmd_str)
{
  if (!empty_str(cmd_str)) {
    printf("illegal arguments\n");
  }

  printf("it would seem i should get back on my way\n");
}
