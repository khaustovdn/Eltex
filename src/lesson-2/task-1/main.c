#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"

int
main(int argc, char* argv[])
{
  char action_choice;
  PhoneBook* phonebook = phonebook_constuct();
  while ((action_choice = phonebook_menu()) != 'q') {
    switch (action_choice) {
      case 'a':
        puts("Append contact action chosen");
        Contact* contact = contact_construct();
        phonebook_append(phonebook, contact);
        free(contact);
        break;
      case 'e': {
        fputs("Edit contact info action chosen\nInput contact id: ", stdout);
        InputResult contact_id;
        if ((contact_id = input_unsigned()).success == false)
          break;
        phonebook_edit(phonebook, *((unsigned *)contact_id.value));
        break;
      }
      case 'r': {
        fputs("Remove contact action chosen\nInput contact id: ", stdout);
        InputResult contact_id;
        if ((contact_id = input_unsigned()).success == false)
          break;
        phonebook_remove(phonebook, *((unsigned *)contact_id.value));
        break;
      }
      case 'p':
        puts("Print contact info action choosen");
        phonebook_print(*phonebook);
        break;
      default:
        puts("Invalid choice of action");
    }
  }

  free(phonebook->contacts);
  free(phonebook);

  return EXIT_SUCCESS;
}

char
phonebook_menu()
{
  char* wrapped_title = create_wrapped_title("PhoneBook Menu", 50, '-');
  output_wrapped_title(wrapped_title);

  fputs("Choose an action:\n\ta. Append "
        "contact\n\te. Edit contact info\n\tr. "
        "Remove contact\n\tp. Print\n\tq. Quit\nInput: ",
        stdout);
  return input_char();
}
