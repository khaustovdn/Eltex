#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "converter.h"
#include "main.h"

typedef char* (*action)(const char* permissions);

int
main(int argc, char* argv[])
{
  CommandEntry converter_commands[] = {
    { "clb", converter_from_letter_to_binary_format },
    { "cln", converter_from_letter_to_numerical_format },
    { NULL, NULL }
  };

  char* action_choice = (char*)malloc(MAX_LEN * sizeof(char));
  if (action_choice == NULL) {
    fprintf(stderr, "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  char* permissions = (char*)malloc(MAX_LEN * sizeof(char));
  if (permissions == NULL) {
    fprintf(stderr, "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }
  fputs("Input permissions: ", stdout);
  permissions = input_string();

  char* result = (char*)malloc(MAX_LEN * sizeof(char));
  if (result == NULL) {
    fprintf(stderr, "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  while (strcmp(strncpy(action_choice, permissions_menu(), MAX_LEN), "q") != 0) {
    int i = 0;
    for (; converter_commands[i].name != NULL; i++)
      if (strncmp(converter_commands[i].name, action_choice, MAX_LEN) == 0) {
        result = ((action)converter_commands[i].property)(permissions);
        break;
      }
    if (converter_commands[i].name == NULL)
      puts("Invalid choice of action");
  }

  puts(result);

  free(action_choice);
  free(permissions);
  free(result);

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
