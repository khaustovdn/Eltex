#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calculator.h"
#include "main.h"

typedef double (*operation)(double, double);

int
main(int argc, char* argv[])
{
  CommandEntry commands[] = { { "+", add },
                              { "-", subtract },
                              { "*", multiply },
                              { "/", divide },
                              { NULL, NULL } };

  char* action_choice = (char*)malloc(MAX_LEN * sizeof(char));
  if (action_choice == NULL) {
    fprintf(stderr, "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  while (strncmp((action_choice = calculator_menu()), "q", MAX_LEN) != 0) {
    InputResult x, y;
    double result;
    
    int i = 0;
    while (commands[i].name != NULL) {
      if (strncmp(commands[i].name, action_choice, MAX_LEN) == 0) {
        fputs("Input x: ", stdout);
        if ((x = input_double()).success == false)
          continue;
        fputs("Input y: ", stdout);
        if ((y = input_double()).success == false)
          continue;

        result = ((operation)commands[i].property)((*(double*)x.value),
                                                   (*(double*)y.value));

        printf("Result: %lf\n", result);
        break;
      }
      i++;
    }
    if (commands[i].name == NULL)
      puts("Invalid choice of action");
  }

  return EXIT_SUCCESS;
}

char*
calculator_menu()
{
  char* wrapped_title = create_wrapped_title("Calcualtor Menu", 50, '-');
  output_wrapped_title(wrapped_title);

  fputs("Choose an action:\n\t+) Addition\n\t-) Subtraction\n\t"
        "*) Multiplication\n\t/) Division\n\tq) Quite\nInput: ",
        stdout);
  return input_string();
}
