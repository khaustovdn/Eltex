#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "permissions.h"

typedef void (*action)(mode_t*);

int
main(int argc, char* argv[])
{
  CommandEntry permissions_commands[] = {
    { "ip", permissions_input },
    { "op", permissions_output },
    { NULL, NULL }
  };

  char* action_choice =
    (char*)malloc(MAX_LEN * sizeof(char));
  if (action_choice == NULL) {
    fprintf(stderr, "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  mode_t mode = 0;
  while (
    strncmp((action_choice = permissions_manager_menu()),
            "q",
            MAX_LEN) != 0) {
    int i = 0;
    for (; permissions_commands[i].name != NULL; i++) {
      if (strncmp(permissions_commands[i].name,
                  action_choice,
                  MAX_LEN) == 0) {
        ((action)permissions_commands[i].property)(
          &mode);
        break;
      }
    }
    if (permissions_commands[i].name == NULL) {
      puts("Invalid choice of action");
    }
  }

  free(action_choice);

  return EXIT_SUCCESS;
}

char*
permissions_manager_menu()
{
  output_wrapped_title("Permission Manager Menu", 50, '-');

  fputs("Choose an action:\n\tip. Input Permissions\n\t"
        "op. Output Permissions\n\tq.Quit\nInput: ",
        stdout);
  return input_string();
}
