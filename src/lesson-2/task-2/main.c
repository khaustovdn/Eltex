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

  char* action_choice;

  while (strncmp((action_choice = calculator_menu()), "q", MAX_LEN) != 0) {
    InputResult x, y;
    double result;
    
    int i = 0;
    for (; commands[i].name != NULL; i++)
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
    if (commands[i].name == NULL)
      puts("Invalid choice of action");
  }
  
  free(action_choice);
  return EXIT_SUCCESS;
}

char*
calculator_menu()
{
  output_wrapped_title("Calcualtor Menu", 50, '-');

  fputs("Choose an action:\n\t+) Addition\n\t-) Subtraction\n\t"
        "*) Multiplication\n\t/) Division\n\tq) Quite\nInput: ",
        stdout);
  return input_string();
}
