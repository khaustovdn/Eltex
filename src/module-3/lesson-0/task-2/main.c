#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

int
main(int argc, char* argv[])
{
  CommandEntry commands[] = { { "summator", "summator" },
                              { "string-joiner", "string_joiner" },
                              { "max-number-finder", "max_number_finder" },
                              { "max-line-finder", "max_line_finder" },
                              { NULL, NULL } };

  char* action_choice;

  while (strncmp((action_choice = command_interpreter_menu()), "q", MAX_LEN) !=
         0) {
    int i = 0;
    for (; commands[i].name != NULL; i++) {
      char* name = strtok(action_choice, " ");
      if (strncmp(name, commands[i].name, MAX_LEN) == 0) {
        puts("Good");
        break;
      }
    }
    if (commands[i].name == NULL)
      puts("Invalid choice of action");
  }
  return EXIT_SUCCESS;
}

char*
command_interpreter_menu()
{
  output_wrapped_title("Command Interpreter Menu", 50, '-');

  fputs("Choose an command:\n\t- summator\n\t- string-joiner\n\t"
        "- max-number-finder\n\t- max-line-finder\n\tq. Quit\nInput: ",
        stdout);
  return input_string();
}
