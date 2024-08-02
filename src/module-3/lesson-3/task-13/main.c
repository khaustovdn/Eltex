#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include "../../../utils/utils.h"

volatile sig_atomic_t keep_running = 1;

void
sigint_handler(int sig)
{
  keep_running = 0;
}

void
handle_error(const char* msg)
{
  perror(msg);
  exit(EXIT_FAILURE);
}

void
parent_handler(sem_t* sem, int* shm_in, int* shm_out)
{
  int sets_count = 0;

  while (keep_running) {
    if (sem_wait(sem) == -1) {
      handle_error("sem_wait (parent)");
    }

    srand(time(NULL));
    int count = rand() % MAX_LEN + 1;
    printf("Parent: generating %d random numbers\n", count);
    for (int i = 0; i < count; i++) {
      shm_in[i] = rand() % 1000;
      printf("%d ", shm_in[i]);
    }
    printf("\n");
    shm_in[MAX_LEN] = count;

    if (sem_post(sem) == -1) {
      handle_error("sem_post (parent)");
    }

    usleep(10000);

    if (sem_wait(sem) == -1) {
      handle_error("sem_wait (parent)");
    }

    printf("Parent: Min = %d, Max = %d\n",
           shm_out[0],
           shm_out[1]);
    sets_count++;

    if (sem_post(sem) == -1) {
      handle_error("sem_post (parent)");
    }

    sleep(1);
  }

  printf("Parent: Processed %d sets\n", sets_count);
}

void
child_handler(sem_t* sem, int* shm_in, int* shm_out)
{
  while (keep_running) {
    if (sem_wait(sem) == -1) {
      handle_error("sem_wait (child)");
    }

    int count = shm_in[MAX_LEN];
    int min = shm_in[0];
    int max = shm_in[0];
    for (int i = 1; i < count; i++) {
      if (shm_in[i] < min) {
        min = shm_in[i];
      }
      if (shm_in[i] > max) {
        max = shm_in[i];
      }
    }

    shm_out[0] = min;
    shm_out[1] = max;

    if (sem_post(sem) == -1) {
      handle_error("sem_post (child)");
    }
  }
}

int
main(int argc, char* argv[])
{
  signal(SIGINT, sigint_handler);

  int shm_in_fd =
    shm_open("/shm_in", O_CREAT | O_RDWR, 0666);
  if (shm_in_fd == -1) {
    handle_error("shm_open /shm_in");
  }
  if (ftruncate(shm_in_fd, (MAX_LEN + 1) * sizeof(int)) ==
      -1) {
    handle_error("ftruncate /shm_in");
  }
  int* shm_in = mmap(NULL,
                     (MAX_LEN + 1) * sizeof(int),
                     PROT_READ | PROT_WRITE,
                     MAP_SHARED,
                     shm_in_fd,
                     0);
  if (shm_in == MAP_FAILED) {
    handle_error("mmap /shm_in");
  }

  int shm_out_fd =
    shm_open("/shm_out", O_CREAT | O_RDWR, 0666);
  if (shm_out_fd == -1) {
    handle_error("shm_open /shm_out");
  }
  if (ftruncate(shm_out_fd, 2 * sizeof(int)) == -1) {
    handle_error("ftruncate /shm_out");
  }
  int* shm_out = mmap(NULL,
                      2 * sizeof(int),
                      PROT_READ | PROT_WRITE,
                      MAP_SHARED,
                      shm_out_fd,
                      0);
  if (shm_out == MAP_FAILED) {
    handle_error("mmap /shm_out");
  }

  sem_t* sem = sem_open("/sem", O_CREAT, 0666, 1);
  if (sem == SEM_FAILED) {
    handle_error("sem_open /sem");
  }

  pid_t pid = fork();
  if (pid == -1) {
    handle_error("fork");
  }

  if (pid == 0) {
    child_handler(sem, shm_in, shm_out);
  } else {
    parent_handler(sem, shm_in, shm_out);
    wait(NULL);
  }

  munmap(shm_in, (MAX_LEN + 1) * sizeof(int));
  munmap(shm_out, 2 * sizeof(int));
  shm_unlink("/shm_in");
  shm_unlink("/shm_out");
  sem_close(sem);
  sem_unlink("/sem");

  return EXIT_SUCCESS;
}
