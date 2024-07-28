#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>

#include "../../../utils/utils.h"

#define SERVER_QUIT_MESSAGE_PRIORITY 1
#define CLIENT_QUIT_MESSAGE_PRIORITY 2
#define SERVER_MESSAGE_PRIORITY 3
#define CLIENT_MESSAGE_PRIORITY 4

struct msgbuf
{
  long mtype;
  char mtext[MAX_LEN];
};

char*
client_menu()
{
  output_wrapped_title("Client Menu", 50, '-');

  fputs("Enter the number to send\n\tq. Quit\nInput: ",
        stdout);
  return input_string();
}

void
receive_messages(int msgid)
{
  output_wrapped_title("Output", 30, '-');
  struct msgbuf message;
  while (msgrcv(msgid,
                &message,
                sizeof(message.mtext),
                CLIENT_QUIT_MESSAGE_PRIORITY,
                IPC_NOWAIT) != -1 ||
         msgrcv(msgid,
                &message,
                sizeof(message.mtext),
                CLIENT_MESSAGE_PRIORITY,
                IPC_NOWAIT) != -1) {
    if (message.mtype == CLIENT_QUIT_MESSAGE_PRIORITY) {
      puts("The client has successfully shut down");
      exit(EXIT_SUCCESS);
    } else if (message.mtype == CLIENT_MESSAGE_PRIORITY) {
      printf("Client process received: %d\n",
             *(int*)message.mtext);
    }
  }
}

void
send_message(int msgid, const char* value, long priority)
{
  struct msgbuf message;
  message.mtype = priority;
  *(int*)message.mtext = atoi(value);

  if (msgsnd(msgid, &message, sizeof(message.mtext), 0) ==
      -1) {
    perror("msgsnd");
    exit(EXIT_FAILURE);
  }
}

int
main(int argc, char* argv[])
{
  key_t key = ftok("prof", 1);
  int msgid = msgget(key, 0);

  for (;;) {
    receive_messages(msgid);

    char* action_choice = client_menu();
    if (strncmp(action_choice, "q", MAX_LEN) == 0) {
      send_message(
        msgid, action_choice, SERVER_QUIT_MESSAGE_PRIORITY);
      free(action_choice);
      puts("\nThe client has successfully shut down");
      break;
    }

    if (!is_integer(action_choice)) {
      puts("Warning: It is necessary to enter a number");
      free(action_choice);
      continue;
    }

    send_message(
      msgid, action_choice, SERVER_MESSAGE_PRIORITY);
    free(action_choice);
  }

  return EXIT_SUCCESS;
}
