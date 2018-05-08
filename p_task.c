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


/*-------------------------------*/
/* prototypes */
/*-------------------------------*/

static p_task invalid_p_task();

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
p_task p_task_(task t, p_task *depends, size_t n_depends)
{
  p_task a;

  if (invalid_task(t)) 
    return invalid_p_task();

  task(a) = t;
  valid_early(a) = false;
  valid_late(a) = false;
  depends(a) = depends;
  n_depends(a) = (depends(a) == NULL) ? 0 : n_depends;
  n_allocd(a) = INIT_SIZE;
  successors(a) = (p_task *) malloc(n_allocd(a) * sizeof(p_task));
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
 * input: p_task
 * verifies if the p_task is valid
 */
bool valid_p_task(p_task a)
{
  return n_succ(a) <= n_allocd(a);
}


/* 
 * function: critical_p_task
 * 
 * input: p_task
 * verifies if the p_task is critical (early == late)
 */
bool critical_p_task(p_task a)
{
  return (valid_early(a) && valid_late(a) && early(a) == late(a));
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
 *
 * return: str with external representation of a p_task
 *
 * representation: <id> <description> <duration>
 */
char *print_p_task(p_task a)
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


