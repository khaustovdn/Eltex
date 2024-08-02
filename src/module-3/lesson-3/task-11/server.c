#include "../../../utils/utils.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mqueue.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/types.h>

#include <fcntl.h>
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
update_file(int fd, const char* id, const char* new_value)
{
  if (lseek(fd, sizeof(int) * (atoi(id) - 1), SEEK_SET) ==
      -1) {
    handle_error("set_file_offset", EXIT_FAILURE);
  }

  int result = atoi(new_value);

  ssize_t bytes_written =
    write(fd, &result, sizeof(result));

  if (bytes_written == -1) {
    handle_error("write_file", EXIT_FAILURE);
  }
}

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
server_handler(mqd_t qd)
{
  sem_t* sem_rw = sem_open("/prof_rw", O_CREAT, 0666, 1);
  if (sem_rw == SEM_FAILED) {
    handle_error("sem_open", EXIT_FAILURE);
  }

  sem_t* sem_sd = sem_open("/prof_sd", O_CREAT, 0666, 0);
  if (sem_sd == SEM_FAILED) {
    handle_error("sem_open", EXIT_FAILURE);
  }

  sleep(2);
  if (sem_wait(sem_rw) == -1) {
    handle_error("sem_wait", EXIT_FAILURE);
  }

  int fd = open("file.bin", O_CREAT | O_WRONLY, 0666);
  if (fd == -1) {
    handle_error("open_file_write", EXIT_FAILURE);
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
    } else if (!is_unsigned(id) || atoi(id) == 0) {
      puts("Warning: ID is not a valid positive number");
    } else if (!is_integer(new_value)) {
      puts("Warning: Value is not a valid number");
    } else {
      update_file(fd, id, new_value);
    }

    free(action_choice);
  }

  if (close(fd) == -1) {
    handle_error("close_file", EXIT_FAILURE);
  }

  if (sem_post(sem_rw) == -1) {
    handle_error("semop (unlock)", EXIT_FAILURE);
  }

  for (int i = 0; i < 2; i++) {
    if (sem_wait(sem_sd) == -1) {
      handle_error("sem_wait", EXIT_FAILURE);
    }
  }

  fd = open("file.bin", O_APPEND | O_WRONLY, 0666);
  if (fd == -1) {
    perror("open_file_append");
  } else {
    for (;;) {
      unsigned int priority;
      int message;

      ssize_t bytes_read = mq_receive(
        qd, (char*)&message, sizeof(message), &priority);
      if (bytes_read == -1) {
        puts("files successfully read");
        break;

      } else if (bytes_read > 0) {
        printf("new number - %d\n", message);

        if (lseek(fd, 0, SEEK_END) == -1) {
          handle_error("set_file_offset_end", EXIT_FAILURE);
        }

        ssize_t bytes_written =
          write(fd, &message, sizeof(message));
        if (bytes_written == -1) {
          handle_error("write_file", EXIT_FAILURE);
        }
      }
    }

    if (close(fd) == -1) {
      perror("close_file");
    }
  }

  if (mq_close(qd) == -1) {
    perror("mq_close");
  }

  if (mq_unlink(QUEUE_NAME) == -1) {
    perror("mq_unlink");
  }

  if (sem_close(sem_rw) == -1) {
    perror("sem_close");
  }

  if (sem_close(sem_sd) == -1) {
    perror("sem_close");
  }
}

int
main(int argc, char* argv[])
{
  struct mq_attr queue_attr = { .mq_flags = 0,
                                .mq_maxmsg = MAX_MESSAGES,
                                .mq_msgsize = sizeof(int),
                                .mq_curmsgs = 0 };

  mqd_t qd = mq_open(QUEUE_NAME,
                     O_RDWR | O_CREAT | O_NONBLOCK,
                     QUEUE_PERMISSIONS,
                     &queue_attr);
  if (qd == (mqd_t)-1) {
    handle_error("mq_open", EXIT_FAILURE);
  }

  server_handler(qd);

  return EXIT_SUCCESS;
}
