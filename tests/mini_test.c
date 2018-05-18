#include <stdio.h>
#include <stdlib.h>
#include "../input.h"

int main()
{
  char *str, *orig;
  char *aux = NULL;
  size_t i = 1;


  while ((orig = str = get_line()) != NULL) {
    while (!empty_str(str)) {
      if (get_str(&str, &aux)) {
        printf("%lu: %s\n", i, aux);
        free(aux);
        aux = NULL;
      }
      else {
        printf("\n%lu: invalid arguments\n\n", i);
        str = NULL;
      }
      i++;
    }

    free(orig);
  }

  return 0;
}

