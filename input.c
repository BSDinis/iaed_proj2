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
#define INIT_BUFF 1024

/*-------------------------------*/
/* prototypes */
/*-------------------------------*/

/* verifies if a string is a representation of a ulong */
static bool is_ulong(char *str);

/* verifies if a char is black (' ' or '\t') */
static bool isblank(char c);

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
  char *token = NULL;

  if (!get_str(str, &token)) {
    free(token);
    return false;
  }

  if (!is_ulong(token) || sscanf(token, "%lu", u) < 1) {
    free(token);
    return false;
  }

  free(token);

  if (*u == 0)
    return false;

  return true;
}


/*
 * function: is_ulong
 *
 * verifies if a string can be fully converted to an ulong
 *   str: string to be verified
 *
 * returns: true if the string only has digits
 */
static bool is_ulong(char *str)
{
  int i = 0;
  while (str[i] != '\0' && isdigit(str[i++]));

  return str[i] == 0;
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
bool get_ulong_list(char **str, unsigned long **list, size_t *n_elems)
{
  unsigned long u;
  size_t n_allocd = INIT_ALLOC;
  *n_elems = 0;
  *list = (unsigned long *) malloc(n_allocd * sizeof(unsigned long));

  while (!empty_str(*str)) {
    if (!get_ulong(str, &u)) {
      free(*list);
      return false;          
    }
    else {
      (*list)[(*n_elems)++] = u;
      if (*n_elems == n_allocd) {
        n_allocd *= 2;
        *list = (unsigned long *) realloc(*list, (n_allocd) * sizeof(unsigned long));
      }
    }
  }

  /* frees unnecessary memory */
  *list = (unsigned long *) realloc(*list, (*n_elems) * sizeof(unsigned long));
  return true;
}

/* 
 * function: get_line
 *
 * reads a line from stdin
 * allocates memory exponentially to accomodate growing input
 * includes the newline character
 *
 * return: string,
 *         NULL on EOF
 */
char *get_line()
{
  size_t allocd, len;
  char *line;
  char ch;

  allocd = INIT_BUFF;
  len = 0;
  line = (char *) malloc(allocd * sizeof(char));

  while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
    line[len++] = ch;
    if (len == allocd) {
      allocd *= 2;
      line = (char *) realloc(line, allocd * sizeof(char));
    }
  }

  if (ch == EOF) {
    free(line);
    return NULL;
  }

  line[len++] = ' ';
  line[len++] = '\n';
  line[len++] = '\0';
  line = (char *) realloc(line, len * sizeof(char));
  return line;
}


/*
 * function: get_str
 *
 * gets a string delimited by a single whitespace 
 *   str: pointer to string where the token is extracted
 *   out_str: pointer to string, to be filled
 *
 * return: false on incorrect input
 */
bool get_str(char **str, char **out_str)
{
  char *token;

  token = strchr(*str, ' ');
  
  if (token == NULL) 
    return false;

  if (strlen(token) == 1 || token[0] != ' ' || isblank(token[1]))
    return false;

  token[0] = '\0';

  *out_str = malloc((strlen(*str) + 1) * sizeof(char));
  strcpy(*out_str, *str);

  token[0] = ' ';

  *str = token + 1;
  return true;
}


/*
 * function: get_quoted_str
 *
 * gets a string with the "<substr>" format
 *   str: pointer to string where the token is extracted
 *   out_str: pointer to string, to be filled
 *   max_len: maximum size of the string, excluding the terminator
 *
 * return: false on incorrect input or max_len exceeded
 */
bool get_quoted_str(char **str, char **out_str, size_t max_len)
{
  char *tok1, *tok2;

  /* find first and second occurences of '"' in string */
  tok1 = strchr(*str, '\"');
  tok2 = strchr(tok1 + 1, '\"');
  
  if (tok1 == NULL || tok2 == NULL || strlen(tok2) == 1
      || !isblank(tok2[1]) || isblank(tok2[2])) {
    return false;
  }

  tok2[1] = '\0';

  /* check for size restriciton */
  if (strlen(tok1) > max_len) 
    return false;

  *out_str = malloc((strlen(tok1) + 1) * sizeof(char));
  strcpy(*out_str, tok1);

  /* flush the string to after the quote and the space */
  *str = tok2 + 2;
  return true;
}


/*
 * function: empty_str
 *
 * checks if a string is empty
 *   str: string to be checked
 *
 * return: true on empty str
 *
 * a str is empty if it is " \n" or "\n" or " "
 */
bool empty_str(char *str)
{
  return (str == NULL
          ||strcmp(str, " \n") == 0 
          || strcmp(str, "\n") == 0 
          || strcmp(str, " ") == 0);
}

/*
 * function: isblank
 *
 * check if a character is blank (either space or tab)
 *   c: char
 * 
 * return: bool
 */
static bool isblank(char c)
{
  return c == ' ' || c == '\t';
}

