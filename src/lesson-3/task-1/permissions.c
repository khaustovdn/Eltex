#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "converter.h"
#include "permissions.h"

char*
permissions_input_menu()
{
  output_wrapped_title("Permissions Input Menu", 30, '-');

  fputs("Choose an input variant:\n"
        "\til. Input in Letter Format\n"
        "\tio. Input in Octal Format\n"
        "\tq. Quit\n"
        "Input: ",
        stdout);
  return input_string();
}

void
permissions_input(mode_t* mode)
{
  CommandEntry commands[] = {
    { "il", permissions_input_in_letters },
    { "io", permissions_input_in_octal },
    { NULL, NULL }
  };

  char* action_choice;

  if (strncmp((action_choice = permissions_input_menu()),
              "q",
              MAX_LEN) == 0)
    return;

  int i = 0;
  for (; commands[i].name != NULL; i++)
    if (strncmp(action_choice, commands[i].name, MAX_LEN) ==
        0) {
      InputResult res_mode =
        ((input_action)commands[i].property)();
      if (res_mode.success == false) {
        puts("Warning: an attempt to enter permits was "
             "unsuccessful");
        break;
      }
      *mode = *(mode_t*)res_mode.value;
      break;
    }
  if (commands[i].name == NULL)
    puts("Invalid choice of action");

  free(action_choice);
}

static InputResult
permissions_input_in_letters()
{
  InputResult result;
  {
    result.value = malloc(sizeof(mode_t));
    if (result.value == NULL) {
      fprintf(stderr, "Error: Memory allocation failed.\n");
      exit(EXIT_FAILURE);
    }
    result.success = false;
  }

  fputs("Input permissions in letter format (rwxrwxrwx): ",
        stdout);

  char* str_mode = input_string();

  if (converter_is_letters(str_mode) == false) {
    free(str_mode);
    free(result.value);
    return result;
  }

  *(mode_t*)result.value =
    converter_permissions_to_mode(str_mode);
  result.success = true;

  free(str_mode);
  return result;
}

static InputResult
permissions_input_in_octal()
{
  InputResult result;
  {
    result.value = malloc(sizeof(mode_t));
    if (result.value == NULL) {
      fprintf(stderr, "Error: Memory allocation failed.\n");
      exit(EXIT_FAILURE);
    }
    result.success = false;
  }

  fputs("Input permissions in octal format (777): ",
        stdout);

  char* str_mode = input_string();

  if (is_unsigned(str_mode) == false) {
    free(str_mode);
    free(result.value);
    return result;
  }

  if (converter_is_octal(str_mode) == false) {
    free(str_mode);
    free(result.value);
    return result;
  }

  *(mode_t*)result.value = strtol(str_mode, NULL, 8);
  result.success = true;

  free(str_mode);
  return result;
}

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
