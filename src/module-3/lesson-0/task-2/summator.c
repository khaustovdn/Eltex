#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../../utils/utils.h"

int
main(int argc, char* argv[])
{
  if (argc < 3) {
    puts("Error: Incorrect number of arguments");
    exit(EXIT_FAILURE);
  }

  int sum = 0;
  for (int i = 1; i < argc; i++) {
    if (is_integer(argv[i]) == false) {
      printf("The %s argument numbered %d is not a number\n", argv[i], i);
      continue;
    }
    sum += atoi(argv[i]);
  }

  printf("Result: %d\n", sum);

  return EXIT_SUCCESS;
}
