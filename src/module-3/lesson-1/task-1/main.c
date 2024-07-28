#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../../../utils/utils.h"

void
calculate_area(int start_index,
               int end_index,
               char* argv[],
               const char* process_type)
{
  for (int i = start_index; i < end_index; i++) {
    if (is_unsigned(argv[i]) == false) {
      printf("An invalid argument has been entered. The argument must be a "
             "positive number (%s).\n",
             process_type);
      continue;
    }
    int side_length = atoi(argv[i]);
    printf("%s calculates the area of square №%d: %d\n",
           process_type,
           i,
           side_length * side_length);
    usleep(50000);
  }
}

int
main(int argc, char* argv[])
{
  if (argc < 2) {
    puts("Invalid argument format. Enter the lengths of the sides of the "
         "squares.");
    exit(EXIT_FAILURE);
  }

  pid_t pid;

  switch (pid = fork()) {
    case -1:
      puts("Error: Failed to create a child process.");
      exit(EXIT_FAILURE);
    case 0:
      calculate_area(1, argc / 2, argv, "Child process");
      break;
    default:
      calculate_area(argc / 2, argc, argv, "Parent process");
      wait(NULL);
      break;
  }

  exit(EXIT_SUCCESS);
}
