#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

int
main(int argc, char *argv[])
{
  char* permissions = (char*)malloc(MAX_LEN * sizeof(char));
  char* action_choice = (char*)malloc(MAX_LEN * sizeof(char));
  if (action_choice == NULL) {
    fprintf(stderr, "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  while (strcmp(strncpy(action_choice, permission_manager_menu(), MAX_LEN), "q") != 0) {
  }

  free(action_choice);
  free(permissions);
  return EXIT_SUCCESS;
}

char*
permission_manager_menu()
{
  char* wrapped_title = create_wrapped_title("Permission Manager Menu", 50, '-');
  output_wrapped_title(wrapped_title);

  fputs("Choose an action:\n\tif. Input File Name\n\tipl. "
        "Input Permits in Letter Format\n\tipn. Input "
        "Permissions in Numerical Format\n\tipb. Input "
        "Permissions in Bit Format\n\topl. Output Permits in "
        "Letter Format\n\topn. Output Permissions in Numerical "
        "Format\n\topb. Output Permissions in Bit Format\nInput: ",
        stdout);
  return input_string();
}
