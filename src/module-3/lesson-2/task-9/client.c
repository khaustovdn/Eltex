#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <time.h>

#include "client.h"

void
handle_error(const char* msg, int exit_code)
{
  perror(msg);
  exit(exit_code);
}

void
child_handler(int pipefd[])
{
  key_t key = ftok("/etc/fstab", 1);
  int semid = semget(key, 2, 0);

  struct sembuf lock_res = { 0, -1, 0 };
  struct sembuf rel_res = { 0, 1, 0 };
  struct sembuf push = { 1, -1, IPC_NOWAIT };
  struct sembuf pop = { 1, 1, IPC_NOWAIT };

  int result;
  for (int i = 1;; i++) {
    if (semop(semid, &lock_res, 1) == -1) {
      handle_error("semget (lock_res)", EXIT_FAILURE);
    }
    if (semop(semid, &push, 2) == -1) {
      handle_error("semget (lock_res)", EXIT_FAILURE);
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

      if (semop(semid, &rel_res, 1) == -1) {
        handle_error("semget (rel_res)", EXIT_FAILURE);
      }
      break;
    }

    printf("%d - %d\n", i, result);
    usleep(50000);

    if (close(fd) == -1) {
      handle_error("close", EXIT_FAILURE);
    }

    if (semop(semid, &rel_res, 1) == -1) {
      handle_error("semget (rel_res)", EXIT_FAILURE);
    }
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
}

int
main(int argc, char* argv[])
{
  int pipefd[2];
  if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  child_handler(pipefd);

  return EXIT_SUCCESS;
}
