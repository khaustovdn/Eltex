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

  char* result = (char*)malloc(MAX_LEN * sizeof(char));
  if (result == NULL) {
    fprintf(stderr, "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  while (strncmp((action_choice = permissions_menu()), "q", MAX_LEN) != 0) {
    int i = 0;
    for (; converter_commands[i].name != NULL; i++) {
      if (strncmp(converter_commands[i].name, action_choice, MAX_LEN) == 0) {
        result = input_permissions_menu();
        if (result == NULL) {
          break;
        }
        result = ((action)converter_commands[i].property)(result);
        break;
      }
    }
    if (converter_commands[i].name == NULL) {
      puts("Invalid choice of action");
    }
  }

  puts(result);

  free(action_choice);
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

char* input_permissions_menu() {
  CommandEntry commands[] = {
    { "il", check_on_letter_format },
    { "in", check_on_numerical_format },
    { NULL, NULL }
  };

  char* result = malloc(MAX_LEN * sizeof(char));
  if (result == NULL) {
    fprintf(stderr, "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  printf("Input permissions: ");
  fgets(result, MAX_LEN, stdin);
  result[strcspn(result, "\n")] = 0; // Remove newline character

  printf("Choose an input option:\n"
         "\til. Input in Letter Format\n"
         "\tin. Input in Numeric Format\n"
         "\tInput: ");

  char* option = malloc(MAX_LEN * sizeof(char));
  if (option == NULL) {
    fprintf(stderr, "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  fgets(option, MAX_LEN, stdin);
  option[strcspn(option, "\n")] = 0;

  for (int i = 0; commands[i].name != NULL; i++) {
    if (strncmp(commands[i].name, option, MAX_LEN) == 0) {
      result = ((action)commands[i].property)(result);
      free(option);
      return result;
    }
  }

  puts("Invalid choice of action");
  free(option);
  return NULL;
}

char* check_on_letter_format(const char* permissions) {
  if (strlen(permissions) != 9) {
    puts("Error: invalid permissions string size");
    return NULL;
  }

  for (int i = 0; i < 9; i += 3) {
    if ((permissions[i] != 'r' && permissions[i] != '-') ||
        (permissions[i + 1] != 'w' && permissions[i + 1] != '-') ||
        (permissions[i + 2] != 'x' && permissions[i + 2] != '-')) {
      puts("Error: invalid permissions format");
      return NULL;
    }
  }

  return (char*)permissions; 
}

char* check_on_numerical_format(const char* permissions) {
  if (strlen(permissions) != 3) {
    puts("Error: invalid permissions string size");
    return NULL;
  }

  for (int i = 0; i < strlen(permissions); i++) {
    if (permissions[i] < '0' || permissions[i] > '7') {
      puts("Error: invalid permissions string format");
      return NULL;
    }
  }

  return convert_mode_to_letters(strtol(permissions, NULL, 8));
}
