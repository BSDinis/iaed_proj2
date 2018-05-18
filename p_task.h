/*
 *
 * p_task.h
 *
 * Baltasar Dinis 89416
 * IAED project
 *
 * header file for p_task.c
 *
 * defines the p_task datatype
 * 
 * a p_task (project task) is a task which is already conceptualized in a project
 *
 * this involves it having a list of dependencies and tasks that are dependent on it
 *
 * also, it can have an early start and a late start, which are defined as follow:
 *   early start: the earliest a task can start
 *   late start: the latest a task can start without delaying the project
 */

#ifndef P_TASK_H
#define P_TASK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "task.h"

/* p_task:
 *
 * t: task
 * early: early start
 * late: late start
 * valid_early: freshness flag for the early  start
 * valid_late: freshness flag for the late  start
 * depends: list of dependencies
 * successors: list of successors
 * n_depens: number of dependencies
 * n_succ: number of successors
 * n_allocd: size allocd for the successors list
 *
 * this is necessary because, although the number of dependencies is fixed
 * when the p_task is instanciated, the number of successors is mutable
 * (everytime a p_task 'a' lists another p_task 'b' as it's dependency,
 * 'b' adds 'a' to its list of successors)
 */
typedef struct _p_task{
  task *t;
  unsigned long early;
  unsigned long late;
  bool valid_early, valid_late;
  struct _p_task **depends, **successors;
  size_t n_depends, n_succ, n_allocd;
} p_task;

/* selectors */
#define task(a) ((a).t)
#define early(a) ((a).early)
#define late(a) ((a).late)
#define valid_early(a) ((a).valid_early)
#define valid_late(a) ((a).valid_late)
#define depends(a) ((a).depends)
#define successors(a) ((a).successors)
#define n_depends(a) ((a).n_depends)
#define n_succ(a) ((a).n_succ)
#define n_allocd(a) ((a).n_allocd)

/* constructor
 * returns a ptr to p_task with the parameters if they are correct
 * returns an invalid p_task otherwise
 *
 * calculates early_start (is a constant)
 * late start invalid
 * successors is allocated with an initial size
 */
p_task *p_task_(task *t, p_task **depends, size_t n_depends);

/* destructor */
void free_p_task(p_task *a);

/* careless destructor: frees without fixing dependencies
 * ONLY USE WHEN FREEING EVERTHING */
void careless_free_p_task(p_task *a);

/* tests */

/* checks if p_task is critical (early == late) */
bool critical_p_task(p_task *a);

/* check if p_task is terminal (no successors) */
bool terminal_p_task(p_task *a);

/* check if p_task is initial (no predecessors) */
bool initial_p_task(p_task *a);

/* modifiers */
/* adds a successor, updating lists */
bool add_successor(p_task *ptr, p_task *new_successor);

/* removes a dependency, updating lists */
bool remove_dependency(p_task *t, p_task *dependency);

/* removes a successor, updating lists */
bool remove_successor(p_task *t, p_task *successor);

/* change_early and change_late make the valid flags true */
bool change_early(p_task *t, unsigned long new_early);
bool change_late(p_task *t, unsigned long new_late);

/* invalidate early and late starts */
void invalidate_early(p_task *t);
void invalidate_late(p_task *t);

/* external representation */
char *print_p_task(p_task *a, bool flag);

#endif /* !P_TASK_H */
