#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "converter.h"
#include "main.h"

int
main(int argc, char* argv[])
{
  CommandEntry converter_commands[] = { { "ipl", converter_to_letter_format },
                              { "ipn", converter_to_numerical_format },
                              { "ipb", converter_to_bit_format },
                              { NULL, NULL } };

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

  fputs("Choose an action:\n\tgfp. Get File Permissions\n\tipl. Input "
        "Permissions in Letter Format\n\tipn. Input Permissions in "
        "Numerical Format\n\tipb. Input Permissions in Bit "
        "Format\n\topl. Output Permissions in Letter Format\n\topn. "
        "Output Permissions in Numerical Format\n\topb. Output "
        "Permissions in Bit Format\n\tq.Quit\nInput: ",
        stdout);
  return input_string();
}
