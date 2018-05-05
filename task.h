/*
 *
 * task.h
 *
 * Baltasar Dinis 89416
 * IAED project
 *
 * header file for task.c
 *
 * defines the task datatype
 *
 * notes on the implementation:
 *   the task datatype doesn't have any information about its 
 *   dependencies or its sucessor tasks.
 *
 *   that information is implemented in the project datatype to 
 *   increase flexibility and enhance performance, since, this way, 
 *   tasks exist independent of each other and it is possible to
 *   assign the precedence between tasks
 *
 *   there is no task id modifier because it is unique, and that means
 *   giving the oportunity of altering it would be incorrect
 *
 */

#ifndef TASK_H
#define TASK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>

typedef struct {
  unsigned long id;
  char *desc;
  unsigned long dur;
  unsigned long early;
  unsigned long late;
  bool valid_early, valid_late;
} task;

/* selectors */
#define id(a) ((a).id)
#define descript(a) ((a).desc)
#define dur(a) ((a).dur)
#define early(a) ((a).early)
#define late(a) ((a).late)
#define valid_early(a) ((a).valid_early)
#define valid_late(a) ((a).valid_late)

/* constructor
 * returns a task with the parameters if they are correct
 * returns an invalid task otherwise
 */
task task_(unsigned long id, char *descript, unsigned long dur);

/* destructor */
void free_task(task a);

/* verifier */
bool valid_task(task a);

/* modifiers */

bool change_task_description(task *t, char *new_desc);
bool change_task_duration(task *t, unsigned long new_dur);

/* change_early and change_late make the valid flags true */
bool change_early(task *t, unsigned long new_early);
bool change_late(task *t, unsigned long new_late);
void invalidate_early(task *t);
void invalidate_late(task *t);

/* external representation */
char *print_task(task a);

/* get task from string */
task get_task(char **str);

#endif /* !TASK_H */
