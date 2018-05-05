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

/* TODO: get a hold of the correct val */
#define CMD_BUFFER 10000

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
  char *cmd_str = (char *) malloc((CMD_BUFFER) * sizeof(char));
  char *orig = cmd_str;

  /* function array, with the implemented functionalities */
  void (*func[])(char *) = 
    {&add, &duration, &depend, &remove_task, &path, &exit_proj};

  do {
    fgets(cmd_str, CMD_BUFFER, stdin);
    command = get_cmd(&cmd_str);

    if (valid_command(command)) {
      func[command](cmd_str);
    }
    else {
      printf("illegal arguments\n");
    }
  } while(command != EXIT);
    
  free(orig);
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
  token = strtok(*cmd_str_ptr, " \n");

  if (token == NULL)  {
    c = INVALID;
  }
  else {
    *cmd_str_ptr += strlen(token) + 1;
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
 * parses the rest of the cmd string to call the add_task TODO:??? function
 */
void add(char *cmd_str)
{
  printf("added a dummy task\n");
}


/*
 * function: duration
 *
 * lists the tasks with a given (or longer) duration
 *   cmd_str: command string, only with the arguments
 *
 * parses the rest of the cmd string to call the task_duration TODO:??? function
 */
void duration(char *cmd_str)
{
  printf("you should really implement a duration function, dont ya think?\n");
}

/*
 * function: depend
 *
 * lists the dependencies of a task
 *   cmd_str: command string, only with the arguments
 *
 * parses the rest of the cmd string to call the list_dependencies TODO:??? function
 */
void depend(char *cmd_str)
{
  printf("tell me who you are, i'll tell you who you depend on\n");
}


/*
 * function: remove_task
 *
 * removes a task from the project
 *   cmd_str: command string, only with the arguments
 *
 * parses the rest of the cmd string to call the remove_task TODO:??? function
 */
void remove_task(char *cmd_str)
{
  printf("i had sth to tell you, but apparently someone removed that line\n");
}

/*
 * function: path
 *
 * lists the critical path of a project
 *   cmd_str: command string, only with the arguments
 *
 * parses the rest of the cmd string to call the proj_path: TODO:??? function
 */
void path(char *cmd_str)
{
  printf("the path of the righteous man is beset on all sides by the inequities of the selfish and the tiranny of evil men\n");
}


/*
 * function: exit_proj
 *
 * packs everything up to quit the program
 *   cmd_str: command string, only with the arguments
 *
 * parses the rest of the cmd string to call the free_project TODO:??? function
 */
void exit_proj(char *cmd_str)
{
  printf("it would seem i should get back on my way\n");
}
