#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "converter.h"
#include "permissions_output.h"

char*
permissions_output_menu()
{
  output_wrapped_title("Permissions Output Menu", 30, '-');

  fputs("Choose an input option:\n"
        "\tol. Output in Letter Format\n"
        "\too. Output in Octal Format\n"
        "\tob. Output in Bit Format\n"
        "\tq. Quit\n"
        "Input: ",
        stdout);
  return input_string();
}

void
permissions_output(mode_t* mode)
{
  CommandEntry commands[] = {
    { "ol", converter_mode_to_letters },
    { "oo", converter_mode_to_octal },
    { "ob", converter_mode_to_bit },
    { NULL, NULL }
  };

  char* action_choice;

  if (strncmp((action_choice = permissions_output_menu()),
              "q",
              MAX_LEN) == 0)
    return;

  int i = 0;
  for (; commands[i].name != NULL; i++)
    if (strncmp(action_choice, commands[i].name, MAX_LEN) ==
        0) {
      printf("\n%s", ((output_action)commands[i].property)(*mode));
      break;
    }
  if (commands[i].name == NULL)
    puts("Invalid choice of action");

  free(action_choice);
}
