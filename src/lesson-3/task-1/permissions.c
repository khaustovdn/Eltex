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
    { "il", permissions_input_in_letter_format },
    { "io", permissions_input_in_octal_format },
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
permissions_input_in_letter_format()
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

  if (strlen(str_mode) != 9) {
    puts("Error: invalid permissions string size");
    free(str_mode);
    free(result.value);
    return result;
  }

  for (int i = 0; i < 9; i += 3) {
    if ((str_mode[i] != 'r' && str_mode[i] != '-') ||
        (str_mode[i + 1] != 'w' &&
         str_mode[i + 1] != '-') ||
        (str_mode[i + 2] != 'x' &&
         str_mode[i + 2] != '-')) {
      puts("Error: invalid permissions format");
      free(str_mode);
      free(result.value);
      return result;
    }
  }

  *(mode_t*)result.value =
    convert_permissions_to_mode(str_mode);
  result.success = true;

  free(str_mode);
  return result;
}

static InputResult
permissions_input_in_octal_format()
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

  InputResult str_mode;
  if ((str_mode = input_unsigned()).success == false) {
    free(str_mode.value);
    free(result.value);
    return result;
  }

  if (strlen(str_mode.value) != 3) {
    puts("Error: invalid permissions string size");
    free(str_mode.value);
    free(result.value);
    return result;
  }

  for (int i = 0; i < strlen(str_mode.value); i++) {
    if (((char*)str_mode.value)[i] < '0' ||
        ((char*)str_mode.value)[i] > '7') {
      puts("Error: invalid permissions string format");
      free(str_mode.value);
      free(result.value);
      return result;
    }
  }

  *(mode_t*)result.value = strtol(str_mode.value, NULL, 8);
  result.success = true;

  free(str_mode.value);
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
    { "ol", permissions_output_in_letter_format },
    { "oo", permissions_output_in_octal_format },
    { "ob", permissions_output_in_bit_format },
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
      ((output_action)commands[i].property)(*mode);
      break;
    }
  if (commands[i].name == NULL)
    puts("Invalid choice of action");

  free(action_choice);
}

static void
permissions_output_in_letter_format(mode_t mode)
{
  printf("%s\n", convert_mode_to_letters(mode));
}

static void
permissions_output_in_octal_format(mode_t mode)
{
  printf("%s\n", convert_mode_to_octal(mode));
}

static void
permissions_output_in_bit_format(mode_t mode)
{
  printf("%s\n", convert_mode_to_bit(mode));
}
