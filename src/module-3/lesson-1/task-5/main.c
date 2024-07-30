#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
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

void
handle_error(const char* msg, int exit_code)
{
  perror(msg);
  exit(exit_code);
}

volatile bool is_available = true;

void
listener(int sig)
{
  if (sig == SIGUSR1) {
    is_available = false;
  } else if (sig == SIGUSR2) {
    is_available = true;
  }
}

void
update_file(int fd, const char* id, const char* new_value)
{
  if (lseek(fd, sizeof(int) * (atoi(id) - 1), SEEK_SET) ==
      -1) {
    handle_error("lseek", EXIT_FAILURE);
  }

  int result = atoi(new_value);
  if (write(fd, &result, sizeof(result)) == -1) {
    handle_error("write", EXIT_FAILURE);
  }
}

void
parent_handler(pid_t pid, int pipefd[])
{
  if (close(pipefd[1]) == -1) {
    handle_error("close", EXIT_FAILURE);
  }

  sleep(2);
  if (kill(pid, SIGUSR1) == -1) {
    handle_error("kill", EXIT_FAILURE);
  }

  int fd = open("file.bin", O_CREAT | O_WRONLY, 0666);
  if (fd == -1) {
    handle_error("open", EXIT_FAILURE);
  }

  char* action_choice;
  while ((action_choice = file_editor_menu()) != NULL) {
    if (strncmp(action_choice, "q", MAX_LEN) == 0) {
      free(action_choice);
      break;
    }

    remove_spaces(action_choice);
    char* id = strtok(action_choice, "-");
    char* new_value = strtok(NULL, "-");

    if (id == NULL || new_value == NULL) {
      puts("Warning: Invalid input format");
    } else if (!is_unsigned(id)) {
      puts("Warning: ID is not a valid positive number");
    } else if (!is_integer(new_value)) {
      puts("Warning: Value is not a valid number");
    } else {
      update_file(fd, id, new_value);
    }

    free(action_choice);
  }

  close(fd);
  if (kill(pid, SIGUSR2) == -1) {
    handle_error("kill", EXIT_FAILURE);
  }

  wait(NULL);

  fd = open("file.bin", O_APPEND | O_WRONLY, 0666);
  if (fd == -1) {
    handle_error("open", EXIT_FAILURE);
  }

  int result;
  ssize_t bytes_read =
    read(pipefd[0], &result, sizeof(result));
  if (bytes_read == -1) {
    handle_error("read", EXIT_FAILURE);
  } else if (bytes_read > 0) {
    printf("new number - %d\n", result);
    if (lseek(fd, 0, SEEK_END) == -1) {
      handle_error("lseek", EXIT_FAILURE);
    }
    if (write(fd, &result, sizeof(result)) == -1) {
      handle_error("write", EXIT_FAILURE);
    }
  }

  close(pipefd[0]);
  close(fd);
}

void
child_handler(int pipefd[])
{
  int fd = open("file.bin", O_RDONLY);
  if (fd == -1) {
    handle_error("open", EXIT_FAILURE);
  }
  int result;
  for (int i = 1;; i++) {
    ssize_t bytes_read = read(fd, &result, sizeof(result));
    if (bytes_read == -1) {
      handle_error("read", EXIT_FAILURE);
    } else if (bytes_read == 0) {
      break;
    }

    while (!is_available) {
      close(fd);
      pause();
      int fd = open("file.bin", O_RDONLY);
      if (fd == -1) {
        handle_error("open", EXIT_FAILURE);
      }
      if (lseek(fd, sizeof(int) * i, SEEK_SET) == -1) {
        handle_error("lseek", EXIT_FAILURE);
      }
    }

    printf("%d - %d\n", i, result);
    usleep(50000);
  }

  if (close(fd) == -1 || close(pipefd[0]) == -1) {
    handle_error("close", EXIT_FAILURE);
  }

  srand((unsigned)time(NULL));
  result = rand() % 100;
  if (write(pipefd[1], &result, sizeof(result)) == -1) {
    handle_error("write", EXIT_FAILURE);
  }

  if (close(pipefd[1]) == -1) {
    handle_error("close", EXIT_FAILURE);
  }
}

char*
file_editor_menu()
{
  output_wrapped_title("File Editor Menu", 50, '-');

  fputs("Enter the identification number and the new "
        "value.\nIn this format "
        "(ID - new value)\nInput: ",
        stdout);
  return input_string();
}

int
main(int argc, char* argv[])
{
  signal(SIGUSR1, listener);
  signal(SIGUSR2, listener);

  int pipefd[2];
  if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  pid_t pid = fork();
  switch (pid) {
    case -1:
      perror("fork");
      exit(EXIT_FAILURE);
    case 0: {
      child_handler(pipefd);
      break;
    }
    default:
      parent_handler(pid, pipefd);
      break;
  }

  return EXIT_SUCCESS;
}
