/*
 *
 * task.c
 *
 * Baltasar Dinis 89416
 * IAED project
 *
 * defines input functions, to parse commands
 */

#include "input.h"

#define INIT_ALLOC 4

/*-------------------------------*/
/* prototypes */
/*-------------------------------*/

/*-------------------------------*/
/*-------------------------------*/
/*-------------------------------*/

/*
 * function: get_ulong
 *
 * gets an unsigned long from the first token in str
 *   str: pointer to a string
 *   u: pointer to an unsigned long, to be filled
 *
 * return: false on incorrect input
 */
bool get_ulong(char **str, unsigned long *u)
{
  char *token;
  token = strtok(*str, " \n");

  if (token == NULL || token[0] == '-' || sscanf(token, "%lu", u) != 1)  {
    return false;
  }

  *str += strlen(token) + 1;
  return true;
}

/*
 * function: get_ulong_list
 *
 * gets an unsigned long from the first token in str
 *   str: pointer to a string
 *   u: pointer to an unsigned long, to be filled
 *
 * return: false on incorrect input
 */
bool get_ulong_list(char **str, unsigned long **list, size_t *n_elems, size_t *n_allocd)
{
  *n_elems = 0;
  *n_allocd = INIT_ALLOC;
  *list = (unsigned long *) malloc((*n_allocd) * sizeof(unsigned long));

  while (*str != NULL) {
    if (!get_ulong(str, &(*list[(*n_elems)++]))) {
      free(*list);
      return false;
    }
    else if (*n_elems == *n_allocd) {
      *n_allocd *= 2;
      *list = (unsigned long *) realloc(*list, (*n_allocd) * sizeof(unsigned long));
    }
  }

  return true;
}

/*
 * function: get_str
 *
 * gets a string delimited by whitespace
 *   str: pointer to string where the token is extracted
 *   out_str: pointer to string, to be filled
 *
 * return: false on incorrect input
 */
bool get_str(char **str, char **out_str)
{
  char *token;

  token = strtok(*str, " \n");
  
  if (token == NULL) return false;

  *out_str = malloc((strlen(token) + 1) * sizeof(char));
  strcpy(*out_str, token);

  *str += strlen(token) + 2;
  return true;
}


/*
 * function: get_quoted_str
 *
 * gets a string with the "<substr>" format
 *   str: pointer to string where the token is extracted
 *   out_str: pointer to string, to be filled
 *
 * return: false on incorrect input
 */
bool get_quoted_str(char **str, char **out_str)
{
  char *token, *aux;

  /* find first and second occurences of '"' in string */
  token = strchr(*str, '\"');
  aux = strchr(token + 1, '\"');
  
  if (token == NULL || aux == NULL ||
      strlen(aux) == 1 || !isspace(aux[1])) {
    return false;
  }

  aux[1] = '\0';

  *out_str = malloc((strlen(token) + 1) * sizeof(char));
  strcpy(*out_str, token);

  /* flush the string to after the quote and the terminator */
  *str = aux + 2;
  return true;
}

