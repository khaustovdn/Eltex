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
                SERVER_QUIT_MESSAGE_PRIORITY,
                IPC_NOWAIT) != -1 ||
         msgrcv(msgid,
                &message,
                sizeof(message.mtext),
                SERVER_MESSAGE_PRIORITY,
                IPC_NOWAIT) != -1) {
    if (message.mtype == SERVER_QUIT_MESSAGE_PRIORITY) {
      puts("The server has successfully shut down");
      msgctl(msgid, IPC_RMID, NULL);
      exit(EXIT_SUCCESS);
    } else if (message.mtype == SERVER_MESSAGE_PRIORITY) {
      printf("Server process received: %d\n",
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
    msgctl(msgid, IPC_RMID, NULL);
    exit(EXIT_FAILURE);
  }
}

int
main(int argc, char* argv[])
{
  key_t key = ftok("prof", 1);
  int msgid = msgget(key, IPC_CREAT | 0666);

  for (;;) {
    receive_messages(msgid);

    char* action_choice = server_menu();
    if (strncmp(action_choice, "q", MAX_LEN) == 0) {
      send_message(
        msgid, action_choice, CLIENT_QUIT_MESSAGE_PRIORITY);
      free(action_choice);
      puts("\nThe server has successfully shut down");
      break;
    }

    if (!is_integer(action_choice)) {
      puts("Warning: It is necessary to enter a number");
      free(action_choice);
      continue;
    }

    send_message(
      msgid, action_choice, CLIENT_MESSAGE_PRIORITY);
    free(action_choice);
  }

  msgctl(msgid, IPC_RMID, NULL);
  return EXIT_SUCCESS;
}
