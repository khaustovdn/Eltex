#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

#include "main.h"

char**
parse_command(char* action_choice, int* arg_count)
{
  char* token = strtok(action_choice, " ");
  if (token == NULL)
    return NULL;

  char** prog_argv =
    (char**)malloc(MAX_LEN * sizeof(char*));
  if (prog_argv == NULL) {
    perror("Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  *arg_count = 0;

  while (token != NULL) {
    if (*arg_count >= MAX_LEN - 1) {
      perror("Too many arguments\n");
      break;
    }

    prog_argv[*arg_count] =
      (char*)malloc((strlen(token) + 1) * sizeof(char));
    if (prog_argv[*arg_count] == NULL) {
      perror("Error: Memory allocation failed.\n");
      for (int i = 0; i < *arg_count; i++) {
        free(prog_argv[i]);
      }
      free(prog_argv);
      exit(EXIT_FAILURE);
    }

    strcpy(prog_argv[*arg_count], token);
    (*arg_count)++;
    token = strtok(NULL, " ");
  }

  prog_argv[*arg_count] = NULL;

  return prog_argv;
}

int
main(int argc, char* argv[])
{
  char* action_choice;

  for (;;) {
    action_choice = command_interpreter_menu();

    if (strncmp(action_choice, "q", MAX_LEN) == 0) {
      free(action_choice);
      break;
    }

    int arg_count;
    char** prog_argv =
      parse_command(action_choice, &arg_count);

    if (prog_argv == NULL) {
      puts("Invalid command format.");
      free(action_choice);
      continue;
    }

    int pid = fork();
    switch (pid) {
      case -1:
        puts("Fork");
        break;
      case 0:
        if (execv(prog_argv[0], prog_argv) == -1) {
          puts("Invalid choice of action");
          exit(EXIT_FAILURE);
        }
        break;
      default:
        wait(NULL);
        break;
    }

    for (int i = 0; i < arg_count; i++) {
      free(prog_argv[i]);
    }
    free(prog_argv);
    free(action_choice);
  }

  return EXIT_SUCCESS;
}

char*
command_interpreter_menu()
{
  output_wrapped_title("Command Interpreter Menu", 50, '-');

  fputs("Choose an command:\n\t- summator\n\t- "
        "string-joiner\n\t"
        "- max-number-finder\n\t- max-line-finder\n\tq. "
        "Quit\nInput: ",
        stdout);
  return input_string();
}
