#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

bool is_available = true;

void
listener(int sig)
{
  if (sig == SIGUSR1) {
    is_available = false;
  }
  if (sig == SIGUSR2) {
    is_available = true;
  }
}

int
main(int argc, char* argv[])
{
  signal(SIGUSR1, listener);
  signal(SIGUSR2, listener);

  pid_t pid = fork();
  switch (pid) {
    case -1:
      perror("fork");
      exit(EXIT_FAILURE);
    case 0: {
      int fd = open("file.bin", O_RDONLY, 0777);
      if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
      }
      int result;
      for (; read(fd, &result, sizeof(int)) > 0;) {
        for (; is_available == false;)
          pause();
        printf("%d\n", result);
        usleep(100000);
      }
      close(fd);
      break;
    }
    default:
      sleep(5);
      kill(pid, SIGUSR1);
      int fd = open("file.bin", O_CREAT | O_WRONLY, 0777);
      if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
      }
      int result = 12;
      if (write(fd, &result, sizeof(result)) == -1) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
      }
      close(fd);
      sleep(5);
      kill(pid, SIGUSR2);
      wait(NULL);
      break;
  }

  return EXIT_SUCCESS;
}
