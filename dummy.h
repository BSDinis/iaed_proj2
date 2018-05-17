/*
 *
 * dummy.h
 *
 * Baltasar Dinis 89416
 * IAED project
 *
 * header file for dummy.c
 *
 * defines dummy functions to check the interaction with main
 *
 */

#ifndef DUMMY_H
#define DUMMY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void _add_task(unsigned long id, char *descript, unsigned long dur, 
    unsigned long *ids, size_t n_ids);

void _list_task_duration(unsigned long dur);

void _list_dependencies(unsigned long id);

void _remove_task_id(unsigned long id);

#endif /* !DUMMY_H */
