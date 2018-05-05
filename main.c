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

/*-------------------------------*/
/*-------------------------------*/
/*-------------------------------*/


int main(int argc, char *argv[])
{
  cmd command;
  char *cmd_str = (char *) malloc((CMD_BUFFER) * sizeof(char));

  /* function array, with the implemented functionalities */
  void (*func[])(char *) = 
    {&add, &duration, &depend, &remove, &path, &exit};

  do {
    fgets(cmd_str, CMD_BUFFER, stdin);
    command = get_cmd(&cmd_str);

    if (valid_command(command)) {
      func[cmd](cmd_str);
    }
    else {
      printf("illegal arguments\n");
    }
  } while(cmd != EXIT);
    
  return 0;
}


