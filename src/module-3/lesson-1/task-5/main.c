#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../../../utils/utils.h"
#include "main.h"

void
remove_spaces(char* str)
{
  char* dst = str;
  while (*str) {
    if (*str != ' ') {
      *dst++ = *str;
    }
    str++;
  }
  *dst = '\0';
}

bool is_available = true;

void
listener(int sig)
{
  if (sig == SIGUSR1) {
    is_available = false;
  }
  if (sig == SIGUSR2) {
    is_available = true;
  }
}

void
child_handler()
{
  int fd = open("file.bin", O_RDONLY, 0777);
  if (fd == -1) {
    perror("open");
    exit(EXIT_FAILURE);
  }
  int result;
  for (int i = 1; read(fd, &result, sizeof(int)) > 0; i++) {
    for (; is_available == false;)
      pause();
    printf("%d - %d\n", i, result);
    usleep(50000);
  }
  close(fd);
}

void
parent_handler(pid_t pid)
{
  sleep(2);
  kill(pid, SIGUSR1);
  int fd = open("file.bin", O_CREAT | O_WRONLY, 0777);
  if (fd == -1) {
    perror("open");
    exit(EXIT_FAILURE);
  }

  char* action_choice;
  for (;;) {
    /* fill in the action selection field */
    action_choice = file_editor_menu();
    if (strncmp(action_choice, "q", MAX_LEN) == 0) {
      free(action_choice);
      break;
    }

    /* searching for an identifier and a new value */
    remove_spaces(action_choice);

    char* id = strtok(action_choice, "-");
    char* new_value = strtok(NULL, "-");

    if (is_unsigned(id) == false) {
      puts("Warning: ID is not a number");
      free(action_choice);
      continue;
    }
    if (is_integer(new_value) == false) {
      puts("Warning: value is not a number");
      free(action_choice);
      continue;
    }

    /* message sending */
    int result = atoi(new_value);
    lseek(fd, sizeof(int) * (atoi(id) - 1), SEEK_SET);
    write(fd, &result, sizeof(result));

    free(action_choice);
  }

  close(fd);
  kill(pid, SIGUSR2);
  wait(NULL);
}

char*
file_editor_menu()
{
  output_wrapped_title("File Editor Menu", 50, '-');

  fputs("Enter the identification number and the new value.\nIn this format "
        "(ID - new value)\nInput: ",
        stdout);
  return input_string();
}

int
main(int argc, char* argv[])
{
  signal(SIGUSR1, listener);
  signal(SIGUSR2, listener);

  pid_t pid = fork();
  switch (pid) {
    case -1:
      perror("fork");
      exit(EXIT_FAILURE);
    case 0: {
      child_handler();
      break;
    }
    default:
      parent_handler(pid);
      break;
  }

  return EXIT_SUCCESS;
}
