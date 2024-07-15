#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"

int
main(int argc, char* argv[])
{
  char action_choice;
  while ((action_choice = calculator_menu()) != 'q') {
  }
  return EXIT_SUCCESS;
}

char
calculator_menu()
{
  char* wrapped_title = create_wrapped_title("Calcualtor Menu", 50, '-');
  output_wrapped_title(wrapped_title);

  fputs("Choose an action:\n\t+) Addition\n\t-) Subtraction\n\t"
        "*) Multiplication\n\t/) division\n\tq) Quite\nInput: ",
        stdout);
  return input_char();
}
