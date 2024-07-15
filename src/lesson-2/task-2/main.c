#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "calculator.h"
#include "main.h"

int
main(int argc, char* argv[])
{
  char action_choice;
  while ((action_choice = calculator_menu()) != 'q') {
    double x, y, result;

    fputs("Input x: ", stdout);
    x = input_double();
    fputs("Input x: ", stdout);
    y = input_double();

    switch (action_choice) {
      case '+':
        result = add(x, y);
        break;
      case '-':
        result = subtract(x, y);
        break;
      case '*':
        result = multiply(x, y);
        break;
      case '/':
        result = divide(x, y);
        break;
      default:
        puts("Invalid choice of action");
    }

    printf("Result: %lf\n", result);
  }
  return EXIT_SUCCESS;
}

char
calculator_menu()
{
  char* wrapped_title = create_wrapped_title("Calcualtor Menu", 50, '-');
  output_wrapped_title(wrapped_title);

  fputs("Choose an action:\n\t+) Addition\n\t-) Subtraction\n\t"
        "*) Multiplication\n\t/) Division\n\tq) Quite\nInput: ",
        stdout);
  return input_char();
}
