/*
 *
 * p_task.c
 *
 * Baltasar Dinis 89416
 * IAED project
 *
 * defines the p_task datatype
 */

#include "p_task.h"

#define max(a, b) ((a > b) ? a : b)
#define min(a, b) ((a < b) ? a : b)

/* initial size allocated for the list of successors */
#define INIT_SUCC_SIZE 32

/* buffer a ulong (ULONG_MAX = 4294967295 -> 10 chars) */
#define ULONG_BUFFER 10


/*-------------------------------*/
/* prototypes */
/*-------------------------------*/

static p_task invalid_p_task();

static char *print_early_late(p_task a, bool flag);

static char *print_depends(p_task a);

/*-------------------------------*/
/*-------------------------------*/
/*-------------------------------*/


/* 
 * function: p_task_
 *
 * constructor for the p_task datatype
 *   t: task
 *   depends: list of pointers to p_tasks
 *   n_depends: size of depends
 *
 * if the task is invalid, generate an invalid p_task (n_succ > n_allocd)
 *
 * returns: p_task
 */
p_task p_task_(task t, p_task **depends, size_t n_depends)
{
  p_task a;

  if (!valid_task(t)) 
    return invalid_p_task();

  task(a) = t;
  valid_early(a) = false;
  valid_late(a) = false;
  depends(a) = depends;
  n_depends(a) = (depends(a) == NULL) ? 0 : n_depends;
  n_allocd(a) = INIT_SUCC_SIZE;
  successors(a) = (p_task **) malloc(n_allocd(a) * sizeof(p_task *));
  n_succ(a) = 0;

  return a;
}

/*
 * function: free_p_task
 *
 * destructor for the p_task datatype
 *   a: p_task
 *
 * frees p_task a
 */
void free_p_task(p_task a)
{
  free_task(task(a));
  free(depends(a));
  free(successors(a));
}

/* 
 * function: valid_p_task
 *
 * verifier for the p_task datatype
 *   a: a p_task
 *
 * verifies if the p_task is valid
 */
bool valid_p_task(p_task a)
{
  return n_succ(a) <= n_allocd(a);
}


/* 
 * function: terminal_p_task
 *
 * test for the p_task datatype
 *   a: a p_task
 *
 * tests if the p_task is a terminal task (has no successors)
 */
bool terminal_p_task(p_task a)
{
  return n_succ(a) == 0;
}


/* 
 * function: initial_p_task
 *
 * test for the p_task datatype
 *   a: a p_task
 *
 * verifies if the p_task is valid
 */
bool initial_p_task(p_task a)
{
  return n_depends(a) == 0;
}


/* 
 * function: critical_p_task
 *
 * test for the p_task datatype
 *   a: a p_task
 *
 * tests if the p_task is a critial task
 */
bool critical_p_task(p_task a)
{
  return (valid_early(a) && valid_late(a) && early(a) == late(a));
}


/*
 * function: add_successor
 *
 * modifier for the p_task datatype
 * adds a successor to the p_task addressed by t
 *   t: ptr to a p_task
 *   new_successor: pointer to p_task, new successor
 *
 * doesn't perform any checks to whether that task is already listed as a 
 * successor or not
 *
 * may have to realloc the list of successors: grows exponentially by a
 * factor of 2
 *
 * return: false if any of the pointers is NULL
 */
bool add_successor(p_task *t, p_task *new_successor)
{
  if (t == NULL || new_successor == NULL) 
    return false;

  if (n_succ(*t) == n_allocd(*t)) {
    n_allocd(*t) *= 2;
    successors(*t) = 
      (p_task **) realloc(successors(*t), n_allocd(*t) * sizeof(p_task *));
  }

  successors(*t)[n_succ(*t)++] = new_successor;
  return true;
}


/*
 * function: remove_dependency
 *
 * modifier for the p_task datatype
 * removes a dependency from the p_task addressed by t
 *   t: ptr to a p_task
 *   depedency: pointer to p_task to be removed
 *
 * return: false if any of the pointers is NULL
 */
bool remove_dependency(p_task *t, p_task *dependency)
{
  size_t i, j;
  bool removed = false;

  if (t == NULL || dependency == NULL) 
    return false;

  for (i = 0, j = 0; i < n_depends(*t); i++) {
    if (depends(*t)[i] != dependency) {
      depends(*t)[j++] = depends(*t)[i];
    }
    else {
      removed = true;
    }
  }

  if (removed) 
    n_depends(*t)--;

  return true;
}


/*
 * function: change_early
 *
 * modifier for the p_task datatype
 *   t: ptr to a p_task
 *   new_early: new early start
 *
 * turns the validation flag to true
 * returns true on a successful change
 */
bool change_early(p_task *t, unsigned long new_early)
{
  early(*t) = new_early;
  valid_early(*t) = true;
  return true;
}


/*
 * function: change_late
 *
 * modifier for the p_task datatype
 *   t: ptr to a p_task
 *   new_late: new late start
 *
 * turns the validation flag to true
 * returns true on a successful change
 */
bool change_late(p_task *t, unsigned long new_late)
{
  late(*t) = new_late;
  valid_late(*t) = true;
  return true;
}


/*
 * function: invalidate_early
 *
 * modifier for the p_task datatype
 *   t: ptr to a p_task
 *
 * turns the validation flag to false
 */
void invalidate_early(p_task *t)
{
  valid_early(*t) = false;
}


/*
 * function: invalidate_late
 *
 * modifier for the p_task datatype
 *   t: ptr to a p_task
 *
 * turns the validation flag to false
 */
void invalidate_late(p_task *t)
{
  valid_late(*t) = false;
}


/*
 * function: print_p_task
 *
 * external representation function for p_task datatype
 *   a: p_task
 *   path_freshness: although the p_task may have its early and late starts
 *     valid, the project may have an invalid type, which overwrites the
 *     validity of the starts
 *
 * return: str with external representation of a p_task
 *
 * representation: <task> [<early> <late>] <ids>
 */
char *print_p_task(p_task a, bool path_freshness)
{
  char *str, *task_str, *early_late_str, *ids;
  size_t len;
  bool early_late = path_freshness && valid_early(a) && valid_late(a);

  task_str = print_task(task(a));
  early_late_str = print_early_late(a, early_late);
  ids = print_depends(a);


  len = strlen(task_str) + 1 + strlen(early_late_str) + strlen(ids);
  str = (char *) malloc((len + 1) * sizeof(char));
  sprintf(str, "%s %s%s", task_str, early_late_str, ids);
  free(task_str);
  free(early_late_str);
  free(ids);
  return str;
}
    

/*
 * function: print_early_late
 *
 * prints the early_late component of the p_task represenation
 *   a: a p_task
 *   flag: bolean flag, that indicates wheter the early and late starts should
 *     be printed
 *
 * return:
 *   string with the format "[<early> <late>] " if the flag is true
 */
static char *print_early_late(p_task a, bool flag)
{
  size_t len;
  char *str;

  if (!flag) {
    str = (char *) malloc(1 * sizeof(char));
    str[0] = '\0';
    return str;
  }

  /* 2 ulongs + 2 spaces + 2 brackets */
  len = 2 * ULONG_BUFFER + 4;
  str = (char *) malloc ((len + 1) * sizeof(char));
  if (critical_p_task(a)) {
    sprintf(str, "[%lu CRITICAL] ", early(a));
  }
  else {
    sprintf(str, "[%lu %lu] ", early(a), late(a));
  }

  return str;
}
  

/*
 * function: print_depens
 *
 * prints the ids of the dependencies of a p_task
 *   a: a p_task
 *
 * return:
 *   string with the format "<id>*" 
 */
static char *print_depends(p_task a)
{
  char *str;
  char *aux;
  size_t len, i;

  /* n_depends ids and a space after
   * exception: last one, which has the terminator */
  len = n_depends(a) * (ULONG_BUFFER + 1);

  str = (char *) malloc(len * sizeof(char)); 
  aux = (char *) malloc((ULONG_BUFFER + 2) * sizeof(char));

  for (i = 0, strcpy(str, ""); i < n_depends(a); i++) {
    sprintf(aux, "%lu ", id( task( *(depends(a)[i])) ));
    strcat(str, aux);
  }

  free(aux);
  return str;
}

/*
 * function: invalid_p_task
 *
 * return: invalid p_task 
 * (a p_task whose number of successors is larger than the size allocd for the 
 * successors list)
 */
static p_task invalid_p_task()
{
  p_task a;
  n_succ(a) = 1;
  n_allocd(a) = 0;
  return a;
}

