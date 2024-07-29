#include <errno.h>
#include <mqueue.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../utils/utils.h"

#define SERVER_QUEUE_NAME "/server"
#define CLIENT_QUEUE_NAME "/client"
#define SERVER_QUIT_QUEUE_NAME "/server-quit"
#define CLIENT_QUIT_QUEUE_NAME "/client-quit"
#define MAX_MESSAGES 10

#define SERVER_QUIT_MESSAGE_PRIORITY 1
#define CLIENT_QUIT_MESSAGE_PRIORITY 2
#define SERVER_MESSAGE_PRIORITY 3
#define CLIENT_MESSAGE_PRIORITY 4

#define QUEUE_PERMISSIONS 0660

unsigned int
receive_messages(mqd_t qd[])
{
  output_wrapped_title("Output", 30, '-');

  unsigned int priority;
  char message[MAX_LEN];

  while (mq_receive(qd[1], message, MAX_LEN, &priority) != -1) {
    puts("\nThe server has successfully shut down");
    return priority;
  }

  while (mq_receive(qd[0], message, MAX_LEN, &priority) != -1) {
    printf("Server process received: %s\n", message);
  }

  if (errno != EAGAIN) {
    perror("mq_receive");
  }

  return priority;
}

char*
server_menu()
{
  output_wrapped_title("Server Menu", 50, '-');

  fputs("Enter the number to send\n\tq. Quit\nInput: ", stdout);
  return input_string();
}

int
main(int argc, char* argv[])
{
  mqd_t qd_server[2];

  struct mq_attr queue_attr = { .mq_flags = 0,
                                .mq_maxmsg = MAX_MESSAGES,
                                .mq_msgsize = MAX_LEN,
                                .mq_curmsgs = 0 };

  qd_server[0] = mq_open(SERVER_QUEUE_NAME,
                         O_RDONLY | O_CREAT | O_NONBLOCK,
                         QUEUE_PERMISSIONS,
                         &queue_attr);
  qd_server[1] = mq_open(SERVER_QUIT_QUEUE_NAME,
                         O_RDONLY | O_CREAT | O_NONBLOCK,
                         QUEUE_PERMISSIONS,
                         &queue_attr);
  if (qd_server[0] == (mqd_t)-1) {
    perror("mq_open (server)");
    exit(EXIT_FAILURE);
  }
  if (qd_server[1] == (mqd_t)-1) {
    perror("mq_open (server quit)");
    exit(EXIT_FAILURE);
  }

  for (;;) {
    if (receive_messages(qd_server) ==
        SERVER_QUIT_MESSAGE_PRIORITY)
      break;

    char* action_choice = server_menu();

    mqd_t qd_client[2];
    qd_client[0] = mq_open(CLIENT_QUEUE_NAME, O_WRONLY);
    if (qd_client[0] == (mqd_t)-1) {
      perror("mq_open (client)");
      free(action_choice);
      break;
    }
    qd_client[1] = mq_open(CLIENT_QUIT_QUEUE_NAME, O_WRONLY);
    if (qd_client[1] == (mqd_t)-1) {
      perror("mq_open (client)");
      free(action_choice);
      break;
    }

    if (strncmp(action_choice, "q", MAX_LEN) == 0) {
      puts("\nThe server has successfully shut down");
      if (mq_send(qd_client[1],
                  action_choice,
                  MAX_LEN,
                  CLIENT_QUIT_MESSAGE_PRIORITY) == -1)
        perror("mq_send (to client)");
      mq_close(qd_client[0]);
      mq_close(qd_client[1]);
      free(action_choice);
      break;
    }

    if (!is_integer(action_choice)) {
      puts("Warning: It is necessary to enter a number");
      free(action_choice);
      continue;
    }

    if (mq_send(qd_client[0],
                action_choice,
                MAX_LEN,
                CLIENT_MESSAGE_PRIORITY) == -1) {
      perror("mq_send (to client)");
    }

    mq_close(qd_client[0]);
    mq_close(qd_client[1]);
    free(action_choice);
  }

  mq_close(qd_server[0]);
  mq_close(qd_server[1]);
  mq_unlink(SERVER_QUEUE_NAME);
  mq_unlink(CLIENT_QUEUE_NAME);

  return EXIT_SUCCESS;
}
