/*
 *
 * planner.c
 *
 * Baltasar Dinis 89416
 * IAED project
 *
 * defines the planner datatype
 */

#include "planner.h"

#define max(a, b) ((a > b) ? a : b)
#define min(a, b) ((a < b) ? a : b)

/*-------------------------------*/
/* prototypes */
/*-------------------------------*/

/* check if an id exists */
static bool id_exists(planner *p, unsigned long id);

/* check if the a list of ids all exist on the project */
static bool depends_exist(planner *p, unsigned long *ids, size_t *n_ids);

/* removes duplicates from a list os positive unsigned longs */
static void remove_duplicates(unsigned long *list, size_t *size);

/* removes all occurences of a sentinel */
static void remove_sentinels(unsigned long *list, size_t *size,
                             unsigned long sentinel);

/* removes duplicates in list of positive ulongs in O(n^2) */
static void naive_remove(unsigned long *list, size_t *size);

/* checks if a ulong is less than the other */
static int less_ulong(const void *a, const void *b);

/* checks if a ulong is greater than the other */
static int greater_ulong(const void *a, const void *b);

/* invalidate the critical path of the project */
static void invalidate_path(planner *p);

/* calcs the duration of the project */
static void calc_duration(planner *p);

/* updates the late_start of all the successors
 * turns on the freshness flag for the p_task */
static unsigned long calc_late_start(planner *p, p_task *t);

/*-------------------------------*/
/*-------------------------------*/
/*-------------------------------*/


/* 
 * function: planner_
 *
 * constructor for the planner datatype
 *
 * returns: ptr to planner
 */
planner *planner_()
{
  planner *a = (planner *) malloc(sizeof(planner));

  list(*a) = lnkd_list_();
  htable(*a) = hashtable_();
  proj_duration(*a) = 0;
  path_freshness(*a) = false;

  return a;
}

/*
 * function: free_planner_
 *
 * destructor for the planner datatype
 *   a: ptr to planner
 *
 * frees planner a
 * sets ptr to NULL
 */
void free_planner(planner *a)
{
  if (a != NULL) {
    free_hashtable(htable(*a));
    free_lnkd_list(list(*a));
    free(a);
    a = NULL;
  }
}

/* 
 * function: add_task
 *
 * modifier for planner datatype
 * insert a new task in the project
 *   p: ptr to planner
 *   id: id for task
 *   descript: description of the task
 *   dur: duration of the task
 *   ids: list of ids of dependencies
 *   n_ids: size of ids
 *
 * prints error messages if necessary
 */
void add_task(planner *p, 
    unsigned long id, char *descript, unsigned long dur, 
    unsigned long *ids, size_t n_ids)
{
  size_t i;
  l_node *node;
  p_task *pt;
  p_task **depends;

  if (p == NULL && descript == NULL && ids == NULL) {
    printf("error: planner.c: add_task: NULL pointers\n");
    return;
  }

  if (id_exists(p, id)) {
    printf("id already exists\n");
    return;
  }

  remove_duplicates(ids, &n_ids);
  if (!depends_exist(p, ids, &n_ids)) {
    printf("no such task\n");
    return;
  }

  depends = (p_task **) malloc(n_ids * sizeof(p_task *));
  for (i = 0; i < n_ids; i++) {
    node = search_hashtable(htable(*p), ids[i]);
    depends[i] = val(*node);
  }

  pt = p_task_(task_(id, descript, dur), depends, n_ids);

  add_at_end(list(*p), pt);
  node = prev(*tail(*(list(*p))));
  insert_hashtable(htable(*p), node);

  invalidate_path(p);

  free(depends);
}


/*
 * function: id_exists
 *
 * check if and id is on the project
 *   p: ptr to planner
 *   id 
 *
 * return: true if task exists
 */
static bool id_exists(planner *p, unsigned long id)
{
  l_node *node;
  node = search_hashtable(htable(*p), id);
  return node != NULL;
}


/*
 * function: remove_duplicates
 *
 * removes duplicates from a list os positive unsigned longs
 *   list: list of unsigned longs
 *   size: ptr to size of list
 *
 * performs optimization checks:
 *   check simultaneously if:
 *     the list is ordered 
 *     two items are equal (removing the last one in that case)
 *
 *   if the list is not ordered, copy it, sort it using qsort
 *   and check for duplicates
 *
 *   if they exist, run a naive n^2 to remove duplicates in original list
 */
static void remove_duplicates(unsigned long *list, size_t *size)
{
  size_t i;
  unsigned long *aux;
  int (*cmpfunc)(const void *, const void *b);
  bool employ_naive = false;

  /* sanity checks */
  if (list == NULL || *size <= 1)
    return;

  /* 0 is a sentinel */
  for (i = 0; i < *size - 1 && list[i] == list[i + 1]; list[i++] = 0);

  cmpfunc = (list[i] < list[i + 1]) ? less_ulong : greater_ulong;

  for (i++; i < *size - 1; i++) {
    if (list[i] == list[i + 1]) {
      list[i] = 0;
    }
    /* if the order is inverted, break */
    else if (cmpfunc(&list[i], &list[i + 1]) < 0) {
      i = *size;
    }
  }

  remove_sentinels(list, size, 0);
  aux = (unsigned long *) malloc(*size * sizeof(unsigned long));
  for (i = 0; i < *size; aux[i] = list[i], i++);

  qsort(aux, *size, sizeof(unsigned long), cmpfunc);
  for (i = 0; i < *size - 1 && !employ_naive; i++) {
    if (aux[i] == aux[i + 1]) {
      employ_naive = true;
    }
  }

  if (employ_naive) 
    naive_remove(list, size);

  return;
}


/*
 * function: less_ulong
 *
 * checks if a ulong is less than the other
 *   a: ptr to const void
 *   b: ptr to const void
 * 
 * returns: positive if a < b
 */
static int less_ulong(const void *a, const void *b)
{
  return ((long) *((unsigned long *)b) - (long) *((unsigned long *)a));
}

/*
 * function: greater_ulong
 *
 * checks if a ulong is greater than the other
 *   a: ptr to const void
 *   b: ptr to const void
 * 
 * returns: positive if a > b
 */
static int greater_ulong(const void *a, const void *b)
{
  return ((long) *((unsigned long *)a) - (long) *((unsigned long *)b));
}

/*
 * function: remove_sentinels
 *
 * removes all occurences of a sentinel
 *   list: list of unsigned longs
 *   size: ptr to list size
 *   sentinel: unsigned long, marks a position to be removed
 */
static void remove_sentinels(unsigned long *list, size_t *size,
                             unsigned long sentinel)
{
  size_t i, new_size;
  unsigned long *aux;

  if (list == NULL || size == NULL || *size <= 1)
    return;

  aux = (unsigned long *) malloc(*size * sizeof(unsigned long));
  for (i = new_size = 0; i < *size; i++) {
    if (list[i] != sentinel) {
      aux[new_size++] = list[i];
    }
  }

  for (i = 0; i < new_size; i++) 
    list[i] = aux[i];

  list = (unsigned long *) realloc(list, new_size * sizeof(unsigned long));
  *size = new_size;
  free(aux);
}

/*
 * function: naive_remove
 *
 * removes duplicates in list of positive ulongs in O(n^2)
 *   list: list of ulongs
 *   size: ptr to size of the list
 */
static void naive_remove(unsigned long *list, size_t *size)
{
  size_t i, j;

  if (list == NULL || size == NULL || *size <= 1)
    return;

  for (i = 0; i < *size; i++) {
    if (list[i] == 0) 
      continue;

    for (j = i + 1; j < *size; j++)  {
      if (list[j] == list[i]) {
        list[j] = 0;
      }
    }

  }

  remove_sentinels(list, size, 0);
  return;
}


/*
 * function: depends_exist
 *
 * check if the a list of ids all exist on the project
 *   p: ptr to planner
 *   id 
 *
 * return: true if all tasks exist
 */
static bool depends_exist(planner *p, unsigned long *ids, size_t *n_ids)
{
  l_node *node;
  size_t i;

  for (i = 0; i < *n_ids; i++) {
    if (ids[i] == 0) 
      continue;

    node = search_hashtable(htable(*p), ids[i]);
    if (node == NULL)
      return false;

  }

  return true;
}


/*
 * function: remove_task_id
 *
 * modifier for planner datatype
 * removes an item from project
 *   p: ptr to planner
 *   t: ptr to p_task
 *
 */
void remove_task_id(planner *p, unsigned long id)
{
  l_node *node;

  if (p == NULL)
    printf("error: planner.c: remove_task_id: NULL pointer\n");

  if (!id_exists(p, id)) {
    printf("no such task\n");
    return;
  }

  node = search_hashtable(htable(*p), id);
  if (!terminal_p_task(val(*node))) {
    printf("task with dependencies\n");
    return;
  }

  remove_hashtable(htable(*p), node);
  remove_l_node(node);
  invalidate_path(p);
  return;
}


/*
 * function: invalidate_path
 *
 * modifier for planner datatype
 * invalidate the critical path of the project
 *   p: ptr to planner
 *
 * since only terminal tasks are removed, the early start is always up to date
 * then to invalidate the path, we have to invalidate all the late starts and
 * turn off the path freshness flag
 */
static void invalidate_path(planner *p)
{
  l_node *node;

  if (p == NULL) {
    printf("error: planner.c: invalidate_path: NULL pointer\n");
    return;
  }
  
  if (!path_freshness(*p))
    return;

  node = go_next(head(*list(*p)));
  while (!is_tail(node)) {
    invalidate_late(val(*node));
    node = go_next(node);
  }

  path_freshness(*p) = false;
}


/*
 * function: print_by_duration 
 *
 * prints all tasks in project whose duration is greater than some lower bound
 *   p: ptr to planner
 *   dur: lower bound on duration
 *
 */
void print_with_duration(planner *p, unsigned long dur)
{
  l_node *node;
  char *str;

  if (p == NULL) {
    printf("error: planner.c: print_with_duration: NULL pointer\n");
    return;
  }

  node = go_next(head(*list(*p)));
  while (!is_tail(node)) {
    if (dur(*task(*val(*node))) >= dur) {
      str = print_p_task(val(*node), path_freshness(*p));
      printf("%s\n", str);
      free(str);
    }
    node = go_next(node);
  }
}


/*
 * function: print_dependencies 
 *
 * prints all tasks in project whose duration is greater than some lower bound
 *   p: ptr to planner
 *   dur: lower bound on duration
 *
 */
void print_dependencies(planner *p, unsigned long id)
{
  l_node *node;
  size_t i;

  if (p == NULL) {
    printf("error: planner.c: print_dependencies: NULL pointer\n");
    return;
  }

  if (!id_exists(p, id)) {
    printf("no such task\n");
    return;
  }

  node = search_hashtable(htable(*p), id);

  printf("%lu:", id(*task(*val(*node))));
  if (terminal_p_task(val(*node))) {
    printf(" no dependencies\n");
    return;
  }

  for (i = 0; i < n_succ(*val(*node)); i++) {
    printf(" %lu", id( *task(*(successors( *val(*node) )[i]) ) ));
  }

  printf("\n");
    
}


/*
 * function: print_critical_path
 *
 * calculates and prints the critical path of the project
 *   p: ptr to planner
 *
 * updates the critical_path, the duration and the freshness flag
 */
void print_critical_path(planner *p)
{
  l_node *node;
  char *str;

  if (p == NULL) {
    printf("error: planner.c: print_critical_path: NULL pointer\n");
    return;
  }

  calc_duration(p);
  path_freshness(*p) = true;

  node = go_next(head(*list(*p)));
  while (!is_tail(node)) {
    calc_late_start(p, val(*node));

    if (critical_p_task(val(*node))) {
      str = print_p_task(val(*node), path_freshness(*p));
      printf("%s\n", str);
      free(str);
    }

    node = go_next(node);
  }

  printf("project duration = %lu\n", proj_duration(*p));
}


/*
 * function: calc_duration
 *
 * calculates the duration of the project
 *   p: ptr to planner
 *
 * calcs the duration of the project
 */
static void calc_duration(planner *p)
{
  l_node *node;
  unsigned long tmp_dur;

  if (p == NULL) {
    printf("error: planner.c: calc_duration: NULL pointer\n");
    return;
  }
  else if (path_freshness(*p)) 
    return;

  tmp_dur = 0;

  node = go_next(head(*list(*p)));

  while (!is_tail(node)) {
    if (terminal_p_task(val(*node))) {
      tmp_dur = max(tmp_dur, early(*val(*node)) + dur(*task(*val(*node))));
    }

    node = go_next(node);
  }

  proj_duration(*p) = tmp_dur;
  return;
}


/*
 * function: calc_late_start
 *
 * calculates the late_start of a task
 *   p: ptr to planner
 *   t: ptr to p_task
 *
 * return: late_start of the task
 * updates the late_start of all the successors
 * turns on the freshness flag for the p_task
 */
static unsigned long calc_late_start(planner *p, p_task *t)
{
  size_t i;
  unsigned long min_late_successors, new_late, successor_late;
  min_late_successors = new_late = successor_late = 0;

  if (p == NULL || t == NULL) {
    printf("error: planner.c: print_critical_path: NULL pointers\n");
    return 0;
  }
  else if (valid_late(*t)) {
    return late(*t);
  }

  if (!path_freshness(*p)) {
    path_freshness(*p) = true;
    calc_duration(p);
  }

  if (terminal_p_task(t)) {
    new_late = proj_duration(*p) - dur(*task(*t));
    change_late(t, new_late);
    return late(*t);
  }

  min_late_successors = ULONG_MAX;
  for (i = 0; i < n_succ(*t); i++) {
    successor_late = calc_late_start(p, successors(*t)[i]);
    min_late_successors = min(min_late_successors, successor_late);
  }

  new_late = min_late_successors - dur(*task(*t));
  change_late(t, new_late);
  return late(*t);
}
