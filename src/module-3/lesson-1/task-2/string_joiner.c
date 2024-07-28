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

  char* result = (char*)malloc(MAX_LEN * sizeof(char));
  if (result == NULL) {
    fprintf(stderr, "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 1; i < argc; i++) {
    strcat(result, argv[i]);
  }

  printf("Result: %s\n", result);

  return EXIT_SUCCESS;
}
