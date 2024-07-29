#include <mqueue.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../utils/utils.h"

#define SERVER_QUEUE_NAME "/server"
#define SERVER_QUIT_QUEUE_NAME "/server-quit"
#define MAX_MESSAGES 10

#define SERVER_QUIT_MESSAGE_PRIORITY 1
#define CLIENT_QUIT_MESSAGE_PRIORITY 2
#define SERVER_MESSAGE_PRIORITY 3
#define CLIENT_MESSAGE_PRIORITY 4

void
receive_messages(mqd_t qd[])
{
  output_wrapped_title("Output", 30, '-');

  unsigned int priority;
  char message[MAX_LEN];

  while (mq_receive(qd[0], message, MAX_LEN, &priority) != -1) {
    printf("Server process received: %s\n", message);
  }
}

void
send_message(mqd_t qd[],
             const char* value,
             unsigned int priority)
{
  if (mq_send(qd[0], value, MAX_LEN, priority) == -1) {
    perror("mq_send");
    mq_close(qd[0]);
    mq_close(qd[1]);
    mq_unlink(SERVER_QUEUE_NAME);
    exit(EXIT_FAILURE);
  }
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

  struct mq_attr queue_attr;

  queue_attr.mq_flags = 0;
  queue_attr.mq_maxmsg = MAX_MESSAGES;
  queue_attr.mq_msgsize = MAX_LEN;
  queue_attr.mq_curmsgs = 0;

  mq_unlink(SERVER_QUEUE_NAME);
  if ((qd_server[0] =
         mq_open(SERVER_QUEUE_NAME,
                 O_RDWR | O_CREAT | O_NONBLOCK | 0666,
                 SERVER_MESSAGE_PRIORITY,
                 &queue_attr)) == -1) {
    perror("mq_open (server)");
    exit(1);
  }

  for (;;) {
    receive_messages(qd_server);

    char* action_choice = server_menu();
    if (strncmp(action_choice, "q", MAX_LEN) == 0) {
      puts("\nThe server has successfully shut down");
      free(action_choice);
      break;
    }

    if (!is_integer(action_choice)) {
      puts("Warning: It is necessary to enter a number");
      free(action_choice);
      continue;
    }

    send_message(
      qd_server, action_choice, SERVER_MESSAGE_PRIORITY);

    free(action_choice);
  }

  mq_close(qd_server[0]);
  mq_close(qd_server[1]);
  mq_unlink(SERVER_QUEUE_NAME);
  return EXIT_SUCCESS;
}
