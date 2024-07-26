#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    result.value = (char*)malloc(MAX_LEN * sizeof(char));
    if (result.value == NULL) {
      fprintf(stderr, "Error: Memory allocation failed.\n");
      exit(EXIT_FAILURE);
    }
    result.success = false;
  }

  for (int i = 1; i < argc; i++) {
    strncpy(result.value,
            (result.success == false || strlen(result.value) < strlen(argv[i]))
              ? argv[i]
              : result.value,
            MAX_LEN);
    result.success = true;
  }

  printf("Result: %s. Count: %lu\n", (char*)result.value, strlen(result.value));

  return EXIT_SUCCESS;
}
