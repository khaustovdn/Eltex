#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "permissions.h"
#include "main.h"

int
main(int argc, char* argv[])
{
  CommandEntry permissions_commands[] = {
    { "fp", NULL },
    { "ip", permissions_input },
    { "op",  },
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

  while (strncmp((action_choice = permissions_manager_menu()), "q", MAX_LEN) != 0) {
    int i = 0;
    for (; permissions_commands[i].name != NULL; i++) {
      if (strncmp(permissions_commands[i].name, action_choice, MAX_LEN) == 0) {
        ((action)permissions_commands[i].property)(permissions);
        break;
      }
    }
    if (permissions_commands[i].name == NULL) {
      puts("Invalid choice of action");
    }
  }

  free(action_choice);
  free(permissions);

  return EXIT_SUCCESS;
}

char*
permissions_manager_menu()
{
  output_wrapped_title("Permission Manager Menu", 50, '-');

  fputs("Choose an action:\n\tfp. Get File "
        "Permissions\n\tip. Input Permissions\n\t"
        "op. Output Permissions\n\tq.Quit\nInput: ",
        stdout);
  return input_string();
}
