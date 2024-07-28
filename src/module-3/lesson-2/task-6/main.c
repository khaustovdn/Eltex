#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

#include "../../../utils/utils.h"

struct msgbuf {
    long mtype;
    char mtext[MAX_LEN];
};

int main(int argc, char *argv[])
{
  int msgid = msgget(IPC_PRIVATE, IPC_CREAT | 0666);
  pid_t pid = fork();

  switch (pid) {
    case -1:
      perror("fork");
      exit(EXIT_FAILURE);
    case 0: {
      struct msgbuf message;
      for (int i = 0; i < 4; i++) {
        message.mtype = 1;
        strncpy(message.mtext, (char*)&i, MAX_LEN);
        msgsnd(msgid, &message, sizeof(message.mtext), 0);
        sleep(1);
      }
      break;
    }
    default: {
      struct msgbuf result;
      for (int i = 0; i < 4; i++) {
        msgrcv(msgid, &result, sizeof(result.mtext), 1, 0);
        printf("%d\n", *(int*)result.mtext);
      }
      wait(NULL);
      break;
    }
  }
  
  msgctl(msgid, IPC_RMID, NULL);
  return EXIT_SUCCESS;
}
