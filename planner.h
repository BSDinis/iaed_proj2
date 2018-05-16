/*
 *
 * planner.h
 *
 * Baltasar Dinis 89416
 * IAED project
 *
 * header file for planner.c
 *
 * defines the planner datatype
 *
 * the planner is the main data struct of the project planner
 * internally, it has:
 *   a linked_list, which saves history 
 *   a hashtable (with double hashing), saving ptrs to node on the linked_list
 *
 * with both of these structs, we can have:
 *   - lookup in ~ O(1)
 *   - insertion in ~ O(1)
 *   - deletion in ~ O(1)
 *   - transversing in O(n)
 *   - freeing in O(n)
 *
 * (~ O(1) because 
 * 
 */

#ifndef PLANNER_H
#define PLANNER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "list.h"
#include "hashtable.h"
#include "p_task.h"

typedef struct {
  list *l;
  hashtable *ht;
  unsigned long proj_duration;
  bool path_freshness;
} planner;

/* selectors */
#define list(a) ((a).l)
#define htable(a) ((a).htable)
#define proj_duration(a) ((a).proj_duration)
#define path_freshness(a) ((a).path_freshness)

/* constructor */
planner *planner_();

/* destructor */
void free_planner(planner *p);

/* insert modifier */
bool add_task(planner *p, p_task *t);

/* remove modifier */
bool remove_task(planner *p, unsigned long id);

/* print by duration */
void print_with_duration(planner *p, unsigned long dur);

/* print critical path */
void print_critical_path(planner *p);

/* print dependencies of a task */
void print_dependencies(planner *p, unsigned long id);

#endif /* !PLANNER_H */
