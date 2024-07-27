#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

int
main(int argc, char* argv[])
{
  pid_t pid = fork();
  switch (pid) {
    case -1:
      perror("Fork Failed");
      exit(EXIT_FAILURE);
    case 0: {
      int fd = open("file.bin", O_RDONLY, 0);
      if (fd == -1) {
        printf("Error: File cannot be opened for writing\n");
        exit(EXIT_FAILURE);
      }
      int result;
      for (; read(fd, &result, sizeof(int)) > 0;) {
        printf("%d\n", result);
      }
      close(fd);
      break;
    }
    default:
      wait(NULL);
      break;
  }

  return EXIT_SUCCESS;
}
