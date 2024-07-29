#include <errno.h>
#include <mqueue.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../../../utils/utils.h"

#define SERVER_QUEUE_NAME "/server"
#define CLIENT_QUEUE_NAME "/client"
#define MAX_MESSAGES 10

#define SERVER_QUIT_MESSAGE_PRIORITY 1
#define CLIENT_QUIT_MESSAGE_PRIORITY 2
#define SERVER_MESSAGE_PRIORITY 3
#define CLIENT_MESSAGE_PRIORITY 4

#define QUEUE_PERMISSIONS 0660

void
receive_messages(mqd_t qd)
{
  output_wrapped_title("Output", 30, '-');

  unsigned int priority;
  char message[MAX_LEN];

  while (mq_receive(qd, message, MAX_LEN, &priority) != -1) {
    printf("Client process received: %s\n", message);
  }

  if (errno != EAGAIN) {
    perror("mq_receive");
  }
}

char*
client_menu()
{
  output_wrapped_title("Client Menu", 50, '-');

  fputs("Enter the number to send\n\tq. Quit\nInput: ", stdout);
  return input_string();
}

int
main(int argc, char* argv[])
{
  mqd_t qd_client;

  struct mq_attr queue_attr = { .mq_flags = 0,
                                .mq_maxmsg = MAX_MESSAGES,
                                .mq_msgsize = MAX_LEN,
                                .mq_curmsgs = 0 };

  qd_client = mq_open(CLIENT_QUEUE_NAME,
                      O_RDONLY | O_CREAT | O_NONBLOCK,
                      QUEUE_PERMISSIONS,
                      &queue_attr);
  if (qd_client == (mqd_t)-1) {
    perror("mq_open (client)");
    exit(EXIT_FAILURE);
  }

  for (;;) {
    receive_messages(qd_client);

    char* action_choice = client_menu();
    if (!action_choice) {
      fprintf(stderr, "Failed to read input\n");
      continue;
    }

    mqd_t qd_server = mq_open(SERVER_QUEUE_NAME, O_WRONLY);
    if (qd_server == (mqd_t)-1) {
      perror("mq_open (server)");
      free(action_choice);
      break;
    }

    if (strncmp(action_choice, "q", MAX_LEN) == 0) {
      puts("\nThe client has successfully shut down");
      if (mq_send(qd_server,
                  action_choice,
                  MAX_LEN,
                  SERVER_QUIT_MESSAGE_PRIORITY) == -1) {
        perror("mq_send (to server quit)");
      }
      mq_close(qd_server);
      free(action_choice);
      break;
    }

    if (!is_integer(action_choice)) {
      puts("Warning: It is necessary to enter a number");
      free(action_choice);
      continue;
    }

    if (mq_send(qd_server,
                action_choice,
                MAX_LEN,
                SERVER_MESSAGE_PRIORITY) == -1) {
      perror("mq_send (to server)");
    }

    mq_close(qd_server);
    free(action_choice);
  }

  mq_close(qd_client);

  return EXIT_SUCCESS;
}
