/*
 *
 * dummy.c
 *
 * Baltasar Dinis 89416
 * IAED project
 *
 * defines dummy functions to test the interaction with the program
 *
 */


#include "dummy.h"


/*-------------------------------*/
/* prototypes */
/*-------------------------------*/

/*-------------------------------*/
/*-------------------------------*/
/*-------------------------------*/


void add_task(unsigned long id, char *descript, unsigned long dur, 
    unsigned long *ids, size_t n_ids, size_t allocd)
{
  size_t i;
  printf("inputs:\n");
  printf("id: %lu\n", id);
  printf("description: %s\n", descript);
  printf("dur: %lu\n", dur);

  printf("ids:");
  for (i = 0; i < n_ids; printf(" %lu", ids[i++]));
  printf("\nfilled %lu of the %lu allocd positions\n\n", n_ids, allocd);

  printf("added a dummy task\n");
}

void list_task_duration(unsigned long dur)
{
  printf("input: %lu\n", dur);
  printf("its taking a bit too long to implement this function, isn't it?\n");
}

void list_dependencies(unsigned long id)
{
  printf("input: %lu\n", id);
  printf("tell me who you are, i'll tell you who you depend on\n");
}

void remove_task_id(unsigned long id)
{
  printf("input: %lu\n", id);
  printf("i had sth to tell you, but apparently someone removed that line\n");
}

