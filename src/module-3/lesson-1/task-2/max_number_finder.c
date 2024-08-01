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

  InputResult result;
  {
    result.value = (int*)malloc(sizeof(int));
    if (result.value == NULL) {
      fprintf(stderr, "Error: Memory allocation failed.\n");
      exit(EXIT_FAILURE);
    }
    result.success = false;
  }

  for (int i = 1; i < argc; i++) {
    if (is_integer(argv[i]) == false) {
      printf(
        "The \"%s\" argument numbered %d is not a number\n",
        argv[i],
        i);
      continue;
    }
    *(int*)result.value =
      (result.success == false ||
       *(int*)result.value < atoi(argv[i]))
        ? atoi(argv[i])
        : *(int*)result.value;
    result.success = true;
  }

  printf("Result: %d\n", *(int*)result.value);

  free(result.value);
  return EXIT_SUCCESS;
}
