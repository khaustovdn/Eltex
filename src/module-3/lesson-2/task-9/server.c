#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../../../utils/utils.h"

#if defined(__GNU_LIBRARY__) &&                            \
  !defined(_SEM_SEMUN_UNDEFINED)
/* union semun is defined by including <sys/sem.h> */
#else
/* according to X/OPEN we have to define it ourselves */
union semun
{
  int val;               /* value for SETVAL */
  struct semid_ds* buf;  /* buffer for IPC_STAT, IPC_SET */
  unsigned short* array; /* array for GETALL, SETALL */
                         /* Linux specific part: */
  struct seminfo* __buf; /* buffer for IPC_INFO */
};
#endif

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
handle_error(const char* msg)
{
  perror(msg);
}

void
update_file(int fd, const char* id, const char* new_value)
{
  int record_id = atoi(id);
  if (record_id <= 0) {
    fprintf(stderr, "Invalid ID: %s\n", id);
    return;
  }

  if (lseek(fd, sizeof(int) * (record_id - 1), SEEK_SET) ==
      -1) {
    handle_error("lseek");
    return;
  }

  int result = atoi(new_value);
  if (write(fd, &result, sizeof(result)) == -1) {
    handle_error("write");
  }
}

char*
file_editor_menu()
{
  output_wrapped_title("File Editor Menu", 50, '-');

  fputs("Enter the identification number and the new "
        "value.\nIn this format (ID - new value)\nInput: ",
        stdout);
  return input_string();
}

void
parent_handler(int pipefd[])
{
  key_t key = ftok("/etc/fstab", 1);
  if (key == -1) {
    handle_error("ftok");
    return;
  }

  int semid = semget(key, 2, 0666 | IPC_CREAT);
  if (semid == -1) {
    handle_error("semget");
    return;
  }

  struct sembuf lock_res = { 0, -1, 0 };
  struct sembuf rel_res = { 0, 1, 0 };
  union semun arg;
  arg.val = 1;
  if (semctl(semid, 0, SETVAL, arg) == -1) {
    handle_error("semctl (setval 0)");
    return;
  }
  arg.val = 2;
  if (semctl(semid, 1, SETVAL, arg) == -1) {
    handle_error("semctl (setval 1)");
    return;
  }

  close(pipefd[1]);

  sleep(2);
  if (semop(semid, &lock_res, 1) == -1) {
    handle_error("semop (lock_res)");
    return;
  }

  int fd = open("file.bin", O_CREAT | O_WRONLY, 0666);
  if (fd == -1) {
    handle_error("open");
    semop(semid, &rel_res, 1);
    return;
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
  semop(semid, &rel_res, 1);

  wait(NULL);

  fd = open("file.bin", O_APPEND | O_WRONLY, 0666);
  if (fd == -1) {
    handle_error("open");
    return;
  }

  int result;
  ssize_t bytes_read =
    read(pipefd[0], &result, sizeof(result));
  if (bytes_read == -1) {
    handle_error("read");
  } else if (bytes_read > 0) {
    printf("new number - %d\n", result);
    if (lseek(fd, 0, SEEK_END) == -1) {
      handle_error("lseek");
    } else if (write(fd, &result, sizeof(result)) == -1) {
      handle_error("write");
    }
  }

  close(pipefd[0]);
  close(fd);
}

int
main()
{
  int pipefd[2];
  if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  parent_handler(pipefd);

  return EXIT_SUCCESS;
}
