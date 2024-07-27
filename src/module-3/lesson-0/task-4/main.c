#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>

#include "../../../utils/utils.h"

int
main(int argc, char* argv[])
{
  if (argc != 2) {
    puts("Error: Incorrect number of arguments");
    exit(EXIT_FAILURE);
  }

  if (is_unsigned(argv[argc - 1]) == false) {
    puts("Error: Argument is not a number");
    exit(EXIT_FAILURE);
  }

  int count = atoi(argv[argc - 1]);

  int pipefd[2];
  if (pipe(pipefd) == -1) {
    perror("Pipe Failed");
    return EXIT_FAILURE;
  }

  pid_t pid = fork();
  switch (pid) {
    case -1:
      perror("Fork Failed");
      exit(EXIT_FAILURE);
    case 0:
      close(pipefd[0]);
      srand(time(NULL));
      for (int i = 0; i < count; i++) {
        int result = rand() % 100;
        write(pipefd[1], &result, sizeof(int));
      }
      close(pipefd[1]);
      break;
    default:
      close(pipefd[1]);
      int fd = open("file.bin", O_CREAT | O_TRUNC | O_WRONLY, 0777);
      if (fd == -1) {
        printf("Error: File cannot be opened for writing\n");
        exit(EXIT_FAILURE);
      }
      int result;
      for (; read(pipefd[0], &result, sizeof(int)) > 0;) {
        printf("%d\n", result);
        write(fd, &result, sizeof(int));
      }
      close(pipefd[0]);
      close(fd);
      wait(NULL);
      break;
  }

  return EXIT_SUCCESS;
}
