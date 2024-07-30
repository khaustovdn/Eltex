#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void
handle_error(const char* msg)
{
  perror(msg);
}

void
child_handler(int pipefd[])
{
  key_t key = ftok("/etc/fstab", 1);
  if (key == -1) {
    handle_error("ftok");
    return;
  }

  int semid = semget(key, 2, 0);
  if (semid == -1) {
    handle_error("semget");
    return;
  }

  struct sembuf lock_res = { 0, -1, 0 };
  struct sembuf rel_res = { 0, 1, 0 };
  struct sembuf push = { 1, -1, IPC_NOWAIT };
  struct sembuf pop = { 1, 1, IPC_NOWAIT };

  int result;
  for (int i = 1;; i++) {
    if (semop(semid, &lock_res, 1) == -1) {
      handle_error("semop (lock_res)");
      break;
    }
    if (semop(semid, &push, 2) == -1) {
      handle_error("semop (push)");
      break;
    }

    int fd = open("file.bin", O_RDONLY);
    if (fd == -1) {
      handle_error("open");
      semop(semid, &rel_res, 1);
      break;
    }

    if (lseek(fd, sizeof(int) * (i - 1), SEEK_SET) == -1) {
      handle_error("lseek");
      close(fd);
      semop(semid, &rel_res, 1);
      break;
    }

    ssize_t bytes_read = read(fd, &result, sizeof(result));
    if (bytes_read == -1) {
      handle_error("read");
      close(fd);
      semop(semid, &rel_res, 1);
      break;
    } else if (bytes_read == 0) {
      close(fd);
      semop(semid, &rel_res, 1);
      break;
    }

    printf("%d - %d\n", i, result);
    usleep(50000);

    close(fd);
    semop(semid, &rel_res, 1);
  }

  close(pipefd[0]);

  srand((unsigned)time(NULL));
  result = rand() % 100;
  if (write(pipefd[1], &result, sizeof(result)) == -1) {
    handle_error("write");
  }

  close(pipefd[1]);
}

int
main()
{
  int pipefd[2];
  if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  child_handler(pipefd);

  return EXIT_SUCCESS;
}
