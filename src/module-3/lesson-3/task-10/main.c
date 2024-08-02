#include <fcntl.h>
#include <semaphore.h>
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
parent_handler(int pipefd[])
{
  sem_t* sem = sem_open("/prof", O_CREAT, 0666, 1);
  if (sem == SEM_FAILED) {
    handle_error("sem_open", EXIT_FAILURE);
  }

  if (close(pipefd[1]) == -1) {
    handle_error("close", EXIT_FAILURE);
  }

  sleep(2);
  if (sem_wait(sem) == -1) {
    handle_error("sem_wait", EXIT_FAILURE);
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
  if (sem_post(sem) == -1) {
    handle_error("sem_post", EXIT_FAILURE);
  }

  wait(NULL);

  fd = open("file.bin", O_APPEND | O_WRONLY, 0666);
  if (fd == -1) {
    perror("open");
  } else {
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

    if (close(fd) == -1) {
      perror("close");
    }
  }

  if (close(pipefd[0]) == -1) {
    perror("close");
  }
  if (sem_close(sem) == -1) {
    perror("sem_close");
  }

  if (sem_unlink("/prof") == -1) {
    perror("sem_unlink");
  }
}

void
child_handler(int pipefd[])
{
  sem_t* sem;
  for (int i = 0;
       i < 5 && (sem = sem_open("/prof", 0)) == SEM_FAILED;
       i++) {
    perror("sem_open");
    sleep(1);
  }

  int result;
  for (int i = 1;; i++) {
    if (sem_wait(sem) == -1) {
      handle_error("sem_wait", EXIT_FAILURE);
    }

    int fd = open("file.bin", O_RDONLY);
    if (fd == -1) {
      handle_error("open", EXIT_FAILURE);
    }

    if (lseek(fd, sizeof(int) * (i - 1), SEEK_SET) == -1) {
      handle_error("lseek", EXIT_FAILURE);
    }
    ssize_t bytes_read = read(fd, &result, sizeof(result));
    if (bytes_read == -1) {
      handle_error("read", EXIT_FAILURE);
    } else if (bytes_read == 0) {
      if (close(fd) == -1) {
        handle_error("close", EXIT_FAILURE);
      }

      if (sem_post(sem) == -1) {
        handle_error("sem_post", EXIT_FAILURE);
      }
      break;
    }

    printf("%d - %d\n", i, result);
    usleep(50000);

    if (close(fd) == -1) {
      handle_error("close", EXIT_FAILURE);
    }

    if (sem_post(sem) == -1) {
      handle_error("sem_post", EXIT_FAILURE);
    }

    usleep(10000);
  }

  if (close(pipefd[0]) == -1) {
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

  sem_close(sem);
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
      parent_handler(pipefd);
      break;
  }

  return EXIT_SUCCESS;
}
