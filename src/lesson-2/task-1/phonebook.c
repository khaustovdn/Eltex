#include <stdbool.h>
#include <stdio.h>

#include "phonebook.h"

char
phonebook_menu()
{
  fputs("Choose an action:\n\ta. Append "
        "contact\n\te. Edit contact info\n\tr. "
        "Remove contact\n\tq. Quit\nInput: ",
        stdout);
  char action_choice = fgetc(stdin);
  while (fgetc(stdin) != '\n')
    ;
  return action_choice;
}
