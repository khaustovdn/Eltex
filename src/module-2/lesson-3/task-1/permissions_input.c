#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "converter.h"
#include "permissions_input.h"

char*
permissions_input_menu()
{
  output_wrapped_title("Permissions Input Menu", 30, '-');

  fputs("Choose an input variant:\n"
        "\tif. Input the File name\n"
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
    { "if", permissions_input_file_name },
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
permissions_input_internal(char* prompt,
                        bool (*is_valid_input)(const char*),
                        mode_t (*convert_to_mode)(const char*))
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

  fputs(prompt, stdout);

  char* str_mode = input_string();

  if (is_valid_input(str_mode) == false) {
    free(str_mode);
    free(result.value);
    return result;
  }

  *(mode_t*)result.value = convert_to_mode(str_mode);
  result.success = true;

  free(str_mode);
  return result;
}

static InputResult
permissions_input_file_name()
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

  fputs("Input the file name: ",
        stdout);

  char* file_name = input_string();
  
  FILE* file = fopen(file_name, "r");
  if (file == NULL) {
    puts("Error: File does not exist");
    free(file_name);
    free(result.value);
    return result;
  }

  struct stat file_stat;
  stat(file_name, &file_stat);

  *(mode_t*)result.value = file_stat.st_mode;
  result.success = true;

  free(file_name);
  fclose(file);
  return result;
}

static InputResult
permissions_input_in_letters()
{
  return permissions_input_internal(
    "Input permissions in letter format (rwxrwxrwx): ",
    converter_is_letters,
    converter_permissions_to_mode);
}

static InputResult
permissions_input_in_octal()
{
  return permissions_input_internal(
    "Input permissions in octal format (777): ",
    converter_is_octal,
    (mode_t (*)(const char*))strtol);
}
