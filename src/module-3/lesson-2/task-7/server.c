#include <mqueue.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../utils/utils.h"

#define QUEUE_NAME "/prof"
#define MAX_MESSAGES 10

#define SERVER_QUIT_MESSAGE_PRIORITY 1
#define CLIENT_QUIT_MESSAGE_PRIORITY 2
#define SERVER_MESSAGE_PRIORITY 3
#define CLIENT_MESSAGE_PRIORITY 4

char*
server_menu()
{
  output_wrapped_title("Server Menu", 50, '-');

  fputs("Enter the number to send\n\tq. Quit\nInput: ",
        stdout);
  return input_string();
}

int
main(int argc, char* argv[])
{
  mqd_t qd_server, qd_client;
  long token_number = 1;

  struct mq_attr attr;

  attr.mq_flags = 0;
  attr.mq_maxmsg = MAX_MESSAGES;
  attr.mq_msgsize = MAX_LEN;
  attr.mq_curmsgs = 0;

  if ((qd_server = mq_open(QUEUE_NAME,
                           O_WRONLY | O_CREAT,
                           SERVER_MESSAGE_PRIORITY,
                           &attr)) == -1) {
    perror("mq_open");
    exit(1);
  }

  for (;;) {
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

    free(action_choice);
  }

  mq_unlink(QUEUE_NAME);
  return EXIT_SUCCESS;
}
