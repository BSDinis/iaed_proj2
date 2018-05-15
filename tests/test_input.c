/*
 *
 * Baltasar Dinis 89416
 * IAED Project
 *
 * test_input.c
 *
 *
 * Test program for input.h
 *
 * Performs the following checks:
 *   gets lines of the form:
 *   <str1> <ulong> <str2> <ulong_list>
 *   has to ouput each param correctly
 */


#include <stdio.h>
#include <stdlib.h>
#include "../input.h"

#define CMD_BUFFER 10000
#define STR_BUFFER 8000

int main()
{
  char *str = (char *) malloc((CMD_BUFFER + 1) * sizeof(char));
  char *orig = str;
  char *str1, *str2;
  unsigned long u, *list;
  size_t len;
  int i = 1;
  list = NULL;

  while (fgets(str, CMD_BUFFER, stdin) != NULL) {
    printf("::::TEST %i:::::\n", i);
    printf("%s", str);
    if (!get_str(&str, &str1)) {
      printf("error getting str1: continuing");
      goto cleanup1;
    }

    if (!get_ulong(&str, &u)) {
      printf("error getting ulong: continuing");
      goto cleanup1;
    }

    if (!get_quoted_str(&str, &str2, STR_BUFFER)) {
      printf("error getting str2: continuing");
      goto cleanup2;
    }

    if (!get_ulong_list(&str, &list, &len)) {
      printf("error getting ulong list: continuing");
      goto cleanup3;
    }

    printf("str1: %s\n", str1);
    printf("str2: %s\n", str2);
    printf("ulong: %lu\n", u);
    
cleanup3:
    free(list);
cleanup2:
    free(str2);
cleanup1:
    free(str1);
    printf("\n\n");
    i++;
  }

  free(orig);
  return 0;
}
