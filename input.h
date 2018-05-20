/*
 *
 * input.h
 *
 * Baltasar Dinis 89416
 * IAED project
 *
 * header file for input.c
 *
 * defines input functions, to parse commands
 *
 * all functions are booleans, returning fasle on incorrect input
 * all functions flush the input string to after the segment which was parsed
 */

#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "cmd.h"

/* get a positive unsigned long */
bool get_ulong(unsigned long *u);

/* get a list of positive unsigned longs:
 * returns the list and the number of elements */
bool get_ulong_list(unsigned long **list, size_t *n_elems);

/* get a string delimited by quotes */
bool get_quoted_str(char **str);

/* check if stream reached end of line maintaining it in that position */
bool end_of_line();

/* check if stdin reached EOF */
bool end_of_file();

/* flush a line of stdin */
void flush_line();

/* get a command */
cmd get_cmd();
#endif /* !INPUT_H */
