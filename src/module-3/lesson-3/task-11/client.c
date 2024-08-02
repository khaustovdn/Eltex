#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mqueue.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/types.h>

#include <fcntl.h>
#include <time.h>
#include <unistd.h>

#define QUEUE_NAME "/base-queue"
#define MESSAGE_PRIORITY 1
#define MAX_MESSAGES 10
#define QUEUE_PERMISSIONS 0660

void
handle_error(const char* msg, int exit_code)
{
  perror(msg);
  exit(exit_code);
}

void
client_handler(mqd_t qd)
{
  sem_t *sem_rw, *sem_sd;
  for (int i = 0;
       i < 5 &&
       ((sem_rw = sem_open("/prof_rw", 0)) == SEM_FAILED ||
        (sem_sd = sem_open("/prof_sd", 0)) == SEM_FAILED);
       i++) {
    perror("sem_open");
    sleep(1);
  }

  int result;
  for (int i = 1;; i++) {
    if (sem_wait(sem_rw) == -1) {
      handle_error("sem_wait", EXIT_FAILURE);
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
      if (sem_post(sem_rw) == -1) {
        handle_error("semop (unlock)", EXIT_FAILURE);
      }

      break;
    }

    printf("%d - %d\n", i, result);
    usleep(50000);

    if (close(fd) == -1) {
      handle_error("close_file", EXIT_FAILURE);
    }

    if (sem_post(sem_rw) == -1) {
      handle_error("semop (unlock)", EXIT_FAILURE);
    }

    usleep(10000);
  }

  srand((unsigned)time(NULL));
  result = rand() % 100;
  printf("new number - %d\n", result);
  if (mq_send(qd,
              (const char*)&result,
              sizeof(result),
              MESSAGE_PRIORITY) == -1) {
    perror("mq_send");
  }

  if (mq_close(qd) == -1) {
    handle_error("mq_close", EXIT_FAILURE);
  }

  if (sem_post(sem_sd) == -1) {
    handle_error("semop (completed)", EXIT_FAILURE);
  }
}

int
main(int argc, char* argv[])
{
  mqd_t qd = mq_open(QUEUE_NAME, O_WRONLY);
  if (qd == (mqd_t)-1) {
    handle_error("mq_open", EXIT_FAILURE);
  }

  client_handler(qd);

  return EXIT_SUCCESS;
}
