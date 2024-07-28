#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include "../../../utils/utils.h"

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

int
main(int argc, char* argv[])
{
  key_t key = ftok("prof", 1);
  int msgid = msgget(key, IPC_CREAT | 0666);

  struct msgbuf message;
  char* action_choice;

  for (;;) {
    action_choice = client_menu();
    if (strncmp(action_choice,
                "q",
                MAX_LEN) == 0) {
      break;
    }

    /* receive */
    output_wrapped_title("Output", 30, '-');
    if (msgrcv(msgid, &message, sizeof(message.mtext), 1, 0) == -1) {
      perror("msgrcv");
      exit(EXIT_FAILURE);
    }
    printf("Client process received: %d\n", *(int*)message.mtext);
    /* pause */
    sleep(1);

    /* send */
    if (is_integer(action_choice) == false) {
      puts("Warning: It is necessary to enter the number");
      free(action_choice);
      continue;
    }    srand(time(NULL));
    message.mtype = 1;
    *(int*)message.mtext = atoi(action_choice);
    if (msgsnd(msgid, &message, sizeof(message.mtext), 0) == -1) {
      perror("msgsnd");
      exit(EXIT_FAILURE);
    }
    /* pause */
    sleep(1);

    free(action_choice);
  }

  msgctl(msgid, IPC_RMID, NULL);
  free(action_choice);
  return EXIT_SUCCESS;
}
