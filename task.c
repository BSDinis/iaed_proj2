/*
 *
 * task.c
 *
 * Baltasar Dinis 89416
 * IAED project
 *
 * defines the task datatype
 */

#include "task.h"

#define max(a, b) ((a > b) ? a : b)
#define min(a, b) ((a < b) ? a : b)

/* buffer for the description of a task (8000 chars as per specification) */
#define DESCRIPT_BUFFER 8000

/* size of error string: _error_ : 7 chars */
#define ERROR_BUFFER 7

/* buffer a ulong (ULONG_MAX = 4294967295 -> 10 chars) */
#define ULONG_BUFFER 10

/*-------------------------------*/
/* prototypes */
/*-------------------------------*/

static bool verify_quoted_str(char *str);

static task invalid_task();

/*-------------------------------*/
/*-------------------------------*/
/*-------------------------------*/


/* 
 * function: task_
 *
 * constructor for the task datatype
 *   id: task identifier, must be 32-bit positive integer
 *   descript: task description, enclosed in quotes
 *   dur: task duration, must be 32-bit positive integer
 *
 * returns: task
 *
 * if an error is detected in the input, return error in the
 * description string: the string is saved as "_error_" 
 * (without the quotes)
 *
 * if the description is enclosed by quotes, but the size is
 * exceeded, truncate at the end and add quotes
 */
task task_(unsigned long id, char *descript, unsigned long dur)
{
  task a;
  size_t src_len;

  /* verify input correctness
   * exits with error if the input is incorrect */
  if (!verify_quoted_str(descript)) {
    return invalid_task();
  }

  id(a) = id;
  dur(a) = dur;
  src_len = strlen(descript);
  descript(a) = (char *) malloc((src_len + 1) * sizeof(char));
  strncpy(descript(a), descript, src_len + 1);

  return a;
}


/*
 * function: verify_quoted_str
 *
 * verifies correctess of the input string
 *   str: string to be verified
 *
 * return: true if str is correct; false otherwise
 *
 * str is said to be incorrect if it isn't delimited by quotes
 *
 * if str is correct but has a size larger DESCRIPT_BUFFER,
 * it is truncated and a quote is added at the end (returning true)
 */
static bool verify_quoted_str(char *str)
{
  size_t len;

  if (str == NULL) return false;

  len = strlen(str);
  
  if (str[0] != '"' || str[len - 1] != '"') return false;

  if (len > DESCRIPT_BUFFER) {
    str[DESCRIPT_BUFFER - 1] = '"';
    str[DESCRIPT_BUFFER] = '\0';
  }

  return true;
}


/*
 * function: free_task
 *
 * return: invalid task
 */
static task invalid_task()
{
  task a;
  id(a) = dur(a) = 0;
  descript(a) = (char *) malloc((ERROR_BUFFER + 1) * sizeof(char));
  strncpy(descript(a), "_error_", ERROR_BUFFER + 1);
  return a;
}


/*
 * function: free_task
 *
 * destructor for the task datatype
 *   a: task
 *
 * frees task a
 */
void free_task(task a)
{
  free(descript(a));
}

/* 
 * function: valid_task
 * 
 * input: task
 * verifies if the task is valid
 */
bool valid_task(task a)
{
  return strcmp(descript(a), "_error_") == 0;
}


/*
 * function: change_task_description
 *
 * modifier for the task datatype
 *   t: ptr to a task
 *   new_desc: new description string
 *
 * returns: true if the change was successful;
 *   if it wasn't the description remains the same
 */
bool change_task_description(task *t, char *new_desc)
{
  size_t src_len;

  if (!verify_quoted_str(new_desc)) return false;

  src_len = strlen(new_desc);
  free(descript(*t));
  descript(*t) = (char *) malloc((src_len + 1) * sizeof(char));
  strncpy(descript(*t), new_desc, src_len + 1);

  return true;
}

/*
 * function: change_task_duration
 *
 * modifier for the task datatype
 *   t: ptr to a task
 *   new_dur: new task duration
 *
 * returns: true if the change was successful;
 *   if it wasn't the duration remains the same
 */
bool change_task_duration(task *t, unsigned long new_dur)
{
  dur(*t) = new_dur;
  return true;
}


/*
 * function: print_task
 *
 * external representation function for task datatype
 *   a: task
 *
 * return: str with external representation of a task
 *
 * representation: <id> <description> <durarion>
 */
char *print_task(task a)
{
  size_t len;
  char *str;

  /* note: 2 spaces between values */
  len = 2 * ULONG_BUFFER + strlen(descript(a)) + 2;
  str = malloc((len + 1) * sizeof(char));

  sprintf(str, "%lu %s %lu", id(a), descript(a), dur(a));
  return str;
}


/*
 * function: get_task
 *
 * input:
 *   str: a pointer to a string, containing 3 or more words
 *
 * return: task, obtained from the string
 *         invalid task, if the string is invalid
 *
 * the valid string format is:
 *   <id> <description> <duration> <optional args>
 *
 * the string is flushed to the beggining of <optional args>
 *
 */
task get_task(char **str)
{
  unsigned long id, dur;
  char *desc;
  char *token, *aux;

  /* parse the string */
  token = strtok(*str, " ");
  if (token == NULL || sscanf(token, "%lu", &id) != 1) 
    return invalid_task();

  /* find first and second occurences of '"' in string */
  token = strchr(*str, '"');
  aux = strchr(token + 1, '"');
  
  if (token == NULL || aux == NULL || strlen(aux) == 1) 
    return invalid_task();

  /* there has to be a space after the quote */
  if (!isspace(aux[1]))
    return invalid_task();

  aux[1] = '\0';
  desc = malloc((strlen(token) + 1) * sizeof(char));
  strcpy(desc, token);

  /* get the token to begin after the quote and the terminator */
  *str = aux + 2;
  token = strtok(*str, " ");
  if (token == NULL ||  sscanf(token, "%lu", &dur) != 1)
    return invalid_task();

  return task_(id, desc, dur);
}
