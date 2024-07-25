#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "permissions_input.h"
#include "permissions_editor.h"
#include "permissions_output.h"

typedef void (*action)(mode_t*);

int
main(int argc, char* argv[])
{
  CommandEntry permissions_commands[] = {
    { "ip", permissions_input },
    { "er", permissions_editor },
    { "op", permissions_output },
    { NULL, NULL }
  };

  char* action_choice;

  mode_t mode = 0;
  for (;;) {
    action_choice = permissions_manager_menu();
    if (strncmp(action_choice,
            "q",
            MAX_LEN) == 0) {
      free(action_choice);
      break;
    }

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

    free(action_choice);
  }

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
