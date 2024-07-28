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

  fputs("Enter the number to send\n\tq. Quit\nInput: ", stdout);
  return input_string();
}

int
main(int argc, char* argv[])
{
  key_t key = ftok("prof", 1);
  int msgid = msgget(key, 0);

  struct msgbuf message;
  char* action_choice;

  for (;;) {
    /* send */
    action_choice = client_menu();
    if (strncmp(action_choice, "q", MAX_LEN) == 0) {
      message.mtype = SERVER_QUIT_MESSAGE_PRIORITY;
      *(int*)message.mtext = 0;
    } else {
      if (is_integer(action_choice) == false) {
        puts("Warning: It is necessary to enter the number");
        free(action_choice);
        continue;
      }
      message.mtype = CLIENT_MESSAGE_PRIORITY;
      *(int*)message.mtext = atoi(action_choice);
    }
    if (msgsnd(msgid, &message, sizeof(message.mtext), 0) == -1) {
      perror("msgsnd");
      free(action_choice);
      exit(EXIT_FAILURE);
    }

    /* receive */
    output_wrapped_title("Output", 30, '-');
    if (msgrcv(msgid,
               &message,
               sizeof(message.mtext),
               CLIENT_QUIT_MESSAGE_PRIORITY,
               IPC_NOWAIT) != -1) {
      puts("The client has successfully shut down");
      free(action_choice);
      break;
    }
    if (msgrcv(
          msgid, &message, sizeof(message.mtext), SERVER_MESSAGE_PRIORITY, 0) ==
        -1) {
      perror("msgrcv");
      free(action_choice);
      exit(EXIT_FAILURE);
    }
    printf("Client process received: %d\n", *(int*)message.mtext);

    free(action_choice);
  }

  return EXIT_SUCCESS;
}
