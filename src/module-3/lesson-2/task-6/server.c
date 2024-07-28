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

int
main(int argc, char* argv[])
{
  key_t key = ftok("prof", 1);
  int msgid = msgget(key, IPC_CREAT | 0666);
  
  struct msgbuf message;
  for (int i = 0; i < 4; i++) {
    /* receive */
    if (msgrcv(msgid, &message, sizeof(message.mtext), 1, 0) == -1) {
      perror("msgrcv");
      exit(EXIT_FAILURE);
    }
    printf("Server process received: %d\n", *(int*)message.mtext);
    /* pause */
    sleep(1);
    /* send */
    srand(time(NULL));
    message.mtype = 1;
    *(int*)message.mtext = rand() % 100;
    if (msgsnd(msgid, &message, sizeof(message.mtext), 0) == -1) {
      perror("msgrcv");
      exit(EXIT_FAILURE);
    }
    printf("Server process send: %d\n", *(int*)message.mtext);
    /* pause */
    sleep(1);
  }

  msgctl(msgid, IPC_RMID, NULL);
  return EXIT_SUCCESS;
}
