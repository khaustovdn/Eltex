#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include "../../../utils/utils.h"

union semun
{
  int val;
  struct semid_ds* buf;
  unsigned short* array;
  struct seminfo* __buf;
};

volatile sig_atomic_t keep_running = 1;

void
sigint_handler(int sig)
{
  keep_running = 0;
}

void
handle_error(const char* msg, int exit_code)
{
  perror(msg);
  exit(exit_code);
}

void
parent_handler(int semid, int shmid_in, int shmid_out)
{
  struct sembuf lock_res = { 0, -1, 0 };
  struct sembuf rel_res = { 0, 1, 0 };

  int sets_count = 0;

  while (keep_running) {
    if (semop(semid, &lock_res, 1) == -1) {
      handle_error("semop (lock_res)", EXIT_FAILURE);
    }

    int* shm_in = shmat(shmid_in, NULL, 0);
    if (shm_in == (void*)-1) {
      handle_error("shmat (parent)", EXIT_FAILURE);
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

    shmdt(shm_in);

    if (semop(semid, &rel_res, 1) == -1) {
      handle_error("semop (rel_res)", EXIT_FAILURE);
    }

    usleep(10000);

    if (semop(semid, &lock_res, 1) == -1) {
      handle_error("semop (lock_res)", EXIT_FAILURE);
    }

    int* shm_out = shmat(shmid_out, NULL, 0);
    if (shm_out == (void*)-1) {
      handle_error("shmat (parent)", EXIT_FAILURE);
    }

    printf("Parent: Min = %d, Max = %d\n",
           shm_out[0],
           shm_out[1]);
    sets_count++;

    shmdt(shm_out);

    if (semop(semid, &rel_res, 1) == -1) {
      handle_error("semop (rel_res)", EXIT_FAILURE);
    }

    sleep(1);
  }

  printf("Parent: Processed %d sets\n", sets_count);
}

void
child_handler(int semid, int shmid_in, int shmid_out)
{
  struct sembuf lock_res = { 0, -1, 0 };
  struct sembuf rel_res = { 0, 1, 0 };

  while (keep_running) {
    if (semop(semid, &lock_res, 1) == -1) {
      handle_error("semop (lock_res)", EXIT_FAILURE);
    }

    int* shm_in = shmat(shmid_in, NULL, 0);
    if (shm_in == (void*)-1) {
      handle_error("shmat (child)", EXIT_FAILURE);
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
    shmdt(shm_in);

    if (semop(semid, &rel_res, 1) == -1) {
      handle_error("semop (rel_res)", EXIT_FAILURE);
    }

    if (semop(semid, &lock_res, 1) == -1) {
      handle_error("semop (lock_res)", EXIT_FAILURE);
    }

    int* shm_out = shmat(shmid_out, NULL, 0);
    if (shm_out == (void*)-1) {
      handle_error("shmat (child)", EXIT_FAILURE);
    }

    shm_out[0] = min;
    shm_out[1] = max;

    shmdt(shm_out);

    if (semop(semid, &rel_res, 1) == -1) {
      handle_error("semop (rel_res)", EXIT_FAILURE);
    }
  }
}

int
main(int argc, char* argv[])
{
  signal(SIGINT, sigint_handler);

  key_t shm_in_key = ftok("prof_in_shm", 1);
  key_t shm_out_key = ftok("prof_out_shm", 1);
  key_t sem_key = ftok("prof_sem", 1);

  int shmid_in = shmget(shm_in_key,
                        (MAX_LEN + 1) * sizeof(int),
                        IPC_CREAT | 0666);
  if (shmid_in == -1) {
    handle_error("shmget (in)", EXIT_FAILURE);
  }

  int shmid_out =
    shmget(shm_out_key, 2 * sizeof(int), IPC_CREAT | 0666);
  if (shmid_out == -1) {
    handle_error("shmget (out)", EXIT_FAILURE);
  }

  int semid = semget(sem_key, 1, IPC_CREAT | 0666);
  if (semid == -1) {
    handle_error("semget", EXIT_FAILURE);
  }

  union semun arg = { .val = 1 };
  if (semctl(semid, 0, SETVAL, arg) == -1) {
    handle_error("semctl", EXIT_FAILURE);
  }

  pid_t pid = fork();
  if (pid == -1) {
    handle_error("fork", EXIT_FAILURE);
  }

  if (pid == 0) {
    child_handler(semid, shmid_in, shmid_out);
  } else {
    parent_handler(semid, shmid_in, shmid_out);
    wait(NULL);
  }

  shmctl(shmid_in, IPC_RMID, NULL);
  shmctl(shmid_out, IPC_RMID, NULL);
  semctl(semid, 0, IPC_RMID);

  return EXIT_SUCCESS;
}
