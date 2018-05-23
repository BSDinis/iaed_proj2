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

/* a string will be a command => max len < 15  */
#define CMD_BUFFER 15

/* initial alloc size for list of ulongs */
#define INIT_ULONG_LIST 32

/* max size of an ulong */
#if ULONG_WIDTH == 32
#define ULONG_BUFFER 10
#else
#define ULONG_BUFFER 20
#endif

/* max len for quoted string */
#define QUOTED_MAX 8000

/*-------------------------------*/
/* prototypes */
/*-------------------------------*/

/*-------------------------------*/
/*-------------------------------*/
/*-------------------------------*/

/*
 * function: get_ulong
 *
 * gets an unsigned long from the stdinput
 *   u: pointer to an unsigned long, to be filled
 *
 * return: false on incorrect input
 *
 * the ulong has to start with a space
 * either ends with a space or a newline, putting either back
 * on the stream
 */
bool get_ulong(unsigned long *u)
{
  char ch;
  size_t i = 0;
  unsigned long old= 0;
  *u = 0;

  if ((ch = getc(stdin)) != ' ')
    return false;

  while (isdigit(ch = getc(stdin)) && i < ULONG_BUFFER) {
    *u *= 10;
    *u += (ch - '0');

    /* check for overflow */
    if (*u < old)
      return false;

    i++;
  }

  if (ch == ' ' || ch == '\n') {
    ungetc(ch, stdin);
    return *u > 0;
  }

  return false;
}


/*
 * function: get_ulong_list
 *
 * gets an unsigned long from the first token in str
 *   list: pointer to array of unsigned long's, to be filled
 *   n_elems: pointer to an size_t, number of elements in the list
 *
 * return: false on incorrect input
 */
bool get_ulong_list(unsigned long **list, size_t *n_elems)
{
  bool flag = true;
  unsigned long u = 0;
  unsigned long *ull = NULL;
  size_t allocd = INIT_ULONG_LIST;
  size_t size = 0;
  

  *list = NULL;
  *n_elems = 0;

  if (end_of_line()) 
    return true;

  ull = (unsigned long *) malloc(allocd * sizeof(unsigned long));

  while (!end_of_line() &&(flag == get_ulong(&u))) {
    if (size == allocd) {
      allocd *= 2;
      ull = (unsigned long *) realloc(ull, allocd * sizeof(unsigned long));
    }
    ull[size++] = u;
  }

  if (!flag) {
    free(ull);
    *list = NULL;
    return false;
  }

  /* free unnecessary space */
  *list = (unsigned long *) realloc(ull, size * sizeof(unsigned long));
  *n_elems = size;

  return true;
}


/*
 * function: get_quoted_str
 *
 * gets a string with the "<substr>" format
 *   str: pointer to string where the token is extracted to
 *
 * return: false on incorrect input or buffer exceededs QUOTED_MAX
 *
 * stream must begin with a single space
 */
bool get_quoted_str(char **str)
{
  /* allocated in stack: cheap */
  char buffer[QUOTED_MAX + 1];
  char ch;
  size_t str_size;

  if (!((ch = getc(stdin)) == ' ' && (ch = getc(stdin)) == '\"'))
    return false;
                
  str_size = 0;
  buffer[str_size++] = ch;
  while ((ch = getc(stdin)) != '\"' && ch != '\n' && str_size < QUOTED_MAX) 
    buffer[str_size++] = ch;

  if (ch != '\"') 
    return false;

  buffer[str_size++] = '\"';
  buffer[str_size] = '\0';

  *str = (char *) malloc((str_size + 1) * sizeof(char));

  strcpy(*str, buffer);
  return true;
}


/*
 * function: end_of_line
 *
 * checks if stdin reached EOL
 *
 * doesn't alter the position of the stream
 *
 * return: bool
 */
bool end_of_line()
{
  char ch = getc(stdin);
  if (ch == '\n' || ch == EOF) {
    ungetc(ch, stdin);
    return true;
  }

  ungetc(ch, stdin);
  return false;
}


/*
 * function: end_of_file
 *
 * checks if stdin reached EOF
 *
 * return: bool
 */
bool end_of_file()
{
  char ch = getc(stdin);
  if (ch == EOF) {
    ungetc(ch, stdin);
    return true;
  }

  ungetc(ch, stdin);
  return false;
}


/*
 * function: flush_line
 *
 * flushes line, getting the stream to either the char after '\n'
 * or leaving it at EOF
 */
void flush_line()
{
  char ch;
  while ((ch = getc(stdin)) != '\n' && ch != EOF);
}


/*
 * function: get_cmd
 *
 * get a command (different commands specified in cmd.h)
 *
 * cmd strings are:
 *   * "add"
 *   * "duration"
 *   * "depend"
 *   * "remove"
 *   * "path"
 *   * "exit"
 * 
 * return: cmd corresponding to a code for the commands listed
 *         or an INVALID command
 */
cmd get_cmd()
{
  /* allocd in stack: quick and cheap */
  char buffer[CMD_BUFFER];
  size_t i;
  char ch;

  i = 0;
  while (isalpha((ch = getc(stdin))) && i < CMD_BUFFER) {
    buffer[i++] = ch;
  }

  if (ch == ' ' || ch == '\n' || ch == EOF) {
    ungetc(ch, stdin);
  }
  else {
    return INVALID;
  }
  
  buffer[i] = '\0';

  if (strcmp(buffer, "add") == 0) 
    return ADD;
  else if (strcmp(buffer, "duration") == 0)
    return DUR;
  else if (strcmp(buffer, "depend") == 0)
    return DEP;
  else if (strcmp(buffer, "remove") == 0)
    return RM;
  else if (strcmp(buffer, "path") == 0)
    return PATH;
  else if (strcmp(buffer, "first") == 0)
    return FIRST;
  else if (strcmp(buffer, "second") == 0)
    return SECOND;
  else if (strcmp(buffer, "exit") == 0)
    return EXIT;


  return INVALID;
}
