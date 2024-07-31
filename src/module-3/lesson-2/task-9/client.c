#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

#include <fcntl.h>
#include <time.h>
#include <unistd.h>

void
handle_error(const char* msg, int exit_code)
{
  perror(msg);
  exit(exit_code);
}

void
client_handler(int fifofd)
{
  key_t key = ftok("/etc/vimrc", '.');
  int semid = semget(key, 2, 0);

  struct sembuf lock = { 0, -1, 0 };
  struct sembuf unlock = { 0, 1, 0 };
  struct sembuf completed = { 1, 1, 0 };

  int result;
  for (int i = 1;; i++) {
    if (semop(semid, &lock, 1) == -1) {
      handle_error("semop (lock)", EXIT_FAILURE);
    }

    int fd = open("file.bin", O_RDONLY);
    if (fd == -1) {
      handle_error("open_file_read", EXIT_FAILURE);
    }

    if (lseek(fd, sizeof(int) * (i - 1), SEEK_SET) == -1) {
      handle_error("set_file_offset", EXIT_FAILURE);
    }

    ssize_t bytes_read = read(fd, &result, sizeof(result));
    if (bytes_read == -1) {
      handle_error("read_file", EXIT_FAILURE);
    } else if (bytes_read == 0) {
      if (close(fd) == -1) {
        handle_error("close_file", EXIT_FAILURE);
      }
      if (semop(semid, &unlock, 1) == -1) {
        handle_error("semop (unlock)", EXIT_FAILURE);
      }

      break;
    }

    printf("%d - %d\n", i, result);
    usleep(50000);

    if (close(fd) == -1) {
      handle_error("close_file", EXIT_FAILURE);
    }

    if (semop(semid, &unlock, 1) == -1) {
      handle_error("semop (unlock)", EXIT_FAILURE);
    }
  }

  srand((unsigned)time(NULL));
  result = rand() % 100;
  printf("new number - %d\n", result);
  if (write(fifofd, &result, sizeof(result)) == -1) {
    handle_error("write", EXIT_FAILURE);
  }

  if (close(fifofd) == -1) {
    handle_error("close", EXIT_FAILURE);
  }

  if (semop(semid, &completed, 1) == -1) {
    handle_error("semop (completed)", EXIT_FAILURE);
  }
}

int
main(int argc, char* argv[])
{
  int fifofd = open("/tmp/fifo", O_WRONLY, 0666);
  if (fifofd == -1) {
    handle_error("fifo", EXIT_FAILURE);
  }

  client_handler(fifofd);

  return EXIT_SUCCESS;
}
