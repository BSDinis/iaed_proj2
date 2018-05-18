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
#include <limits.h>

/* get arbitrary sized line */
char *get_line();

/* get a positive unsigned long */
bool get_ulong(char **str, unsigned long *u);

/* get a list of positive unsigned longs:
 * returns the list and the number of elements */
bool get_ulong_list(char **str, unsigned long **list, size_t *n_elems);

/* get a string, which only has a space after it */
bool get_str(char **str, char **out_str);

/* get a string delimited by quotes */
bool get_quoted_str(char **str, char **out_str, size_t max_len);

/* check if a string is empty */
bool empty_str(char *str);
#endif /* !INPUT_H */
