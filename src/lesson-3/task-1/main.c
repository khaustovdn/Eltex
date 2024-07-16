#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

int
main(int argc, char* argv[])
{
  char* action_choice = (char*)malloc(MAX_LEN * sizeof(char));
  if (action_choice == NULL) {
    fprintf(stderr, "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  char* permissions = (char*)malloc(MAX_LEN * sizeof(char));

  while (strcmp(strncpy(action_choice, permissions_menu(), MAX_LEN), "q") != 0) {
  }

  free(action_choice);
  free(permissions);

  return EXIT_SUCCESS;
}

char*
permissions_menu()
{
  output_wrapped_title("Permission Manager Menu", 50, '-');

  fputs("Choose an action:\n\tif. Input File Name\n\tipl. Input "
        "Permits in Letter Format\n\tipn. Input Permissions in "
        "Numerical Format\n\tipb. Input Permissions in Bit "
        "Format\n\topl. Output Permits in Letter Format\n\topn. "
        "Output Permissions in Numerical Format\n\topb. Output "
        "Permissions in Bit Format\n\tq.Quit\nInput: ",
        stdout);
  return input_string();
}
