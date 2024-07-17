#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "converter.h"
#include "permissions.h"

char*
permissions_menu()
{
  output_wrapped_title("Permissions Menu", 30, '-');

  fputs("Choose an input option:\n"
         "\til. Input in Letter Format\n"
         "\tin. Input in Numeric Format\n"
         "\tInput: ",
        stdout);
  return input_string();
}

void
permissions_input(const char* permissions) {
  CommandEntry commands[] = {
    { "il", permissions_input_in_letter_format },
    { "in", permissions_input_in_numerical_format },
    { NULL, NULL }
  };

  char* action_choice = malloc(MAX_LEN * sizeof(char));
  if (action_choice == NULL) {
    fprintf(stderr, "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  fputs("Input permissions: ", stdout);
  permissions = input_string();
  
  if (strncmp((action_choice = permissions_menu()), "q", MAX_LEN) == 0)
    return;

  int i = 0;
  for (; commands[i].name != NULL; i++)
    if (strncmp(action_choice, commands[i].name, MAX_LEN) == 0) {
      ((action)commands[i].property)(permissions);
      break;
    }
  if (commands[i].name == NULL)
    puts("Invalid choice of action");

  free(action_choice);
}

void permissions_input_in_letter_format(const char* permissions) {
  if (strlen(permissions) != 9) {
    puts("Error: invalid permissions string size");
    return;
  }

  for (int i = 0; i < 9; i += 3) {
    if ((permissions[i] != 'r' && permissions[i] != '-') ||
        (permissions[i + 1] != 'w' && permissions[i + 1] != '-') ||
        (permissions[i + 2] != 'x' && permissions[i + 2] != '-')) {
      puts("Error: invalid permissions format");
      return;
    }
  }
}

void permissions_input_in_numerical_format(const char* permissions) {
  if (strlen(permissions) != 3) {
    puts("Error: invalid permissions string size");
    return;
  }

  for (int i = 0; i < strlen(permissions); i++) {
    if (permissions[i] < '0' || permissions[i] > '7') {
      puts("Error: invalid permissions string format");
      return;
    }
  }

  permissions = convert_mode_to_letters(strtol(permissions, NULL, 8));
}
