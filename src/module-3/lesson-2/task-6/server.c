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
server_menu()
{
  output_wrapped_title("Server Menu", 50, '-');

  fputs("Enter the number to send\n\tq. Quit\nInput: ", stdout);
  return input_string();
}

int
main(int argc, char* argv[])
{
  key_t key = ftok("prof", 1);
  int msgid = msgget(key, IPC_CREAT | 0666);

  struct msgbuf message;
  char* action_choice;

  for (;;) {
    /* receive */
    output_wrapped_title("Output", 30, '-');
    if (msgrcv(msgid,
               &message,
               sizeof(message.mtext),
               SERVER_QUIT_MESSAGE_PRIORITY,
               IPC_NOWAIT) != -1) {
      puts("The server has successfully shut down");
      break;
    }
    if (msgrcv(
          msgid, &message, sizeof(message.mtext), CLIENT_MESSAGE_PRIORITY, 0) ==
        -1) {
      perror("msgrcv");
      exit(EXIT_FAILURE);
    }
    printf("Server process received: %d\n", *(int*)message.mtext);

    /* send */
    action_choice = server_menu();
    if (strncmp(action_choice, "q", MAX_LEN) == 0) {
      message.mtype = CLIENT_QUIT_MESSAGE_PRIORITY;
      *(int*)message.mtext = 0;
    } else {
      if (is_integer(action_choice) == false) {
        puts("Warning: It is necessary to enter the number");
        free(action_choice);
        continue;
      }
      message.mtype = SERVER_MESSAGE_PRIORITY;
      *(int*)message.mtext = atoi(action_choice);
    }
    if (msgsnd(msgid, &message, sizeof(message.mtext), 0) == -1) {
      perror("msgsnd");
      free(action_choice);
      exit(EXIT_FAILURE);
    }

    free(action_choice);
  }

  msgctl(msgid, IPC_RMID, NULL);
  return EXIT_SUCCESS;
}
