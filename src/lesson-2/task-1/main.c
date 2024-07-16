#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

typedef double (*action)(PhoneBook*);

int
main(int argc, char* argv[])
{
  CommandEntry commands[] = { { "a", append_contact },
                              { "e", edit_contact },
                              { "r", remove_contact },
                              { "p", print_contacts },
                              { NULL, NULL } };

  char* action_choice = (char*)malloc(MAX_LEN * sizeof(char));
  if (action_choice == NULL) {
    fprintf(stderr, "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  PhoneBook* phonebook = phonebook_constuct();
  while (strncmp((action_choice = phonebook_menu()), "q", MAX_LEN) != 0) {
    int i = 0;
    for (; commands[i].name != NULL; i++)
      if (strncmp(action_choice, commands[i].name, MAX_LEN) == 0) {
        ((action)commands[i].property)(phonebook);
        break;
      }
    if (commands[i].name == NULL)
      puts("Invalid choice of action");
  }

  free(action_choice);
  free(phonebook->contacts);
  free(phonebook);

  return EXIT_SUCCESS;
}

char*
phonebook_menu()
{
  output_wrapped_title("PhoneBook Menu", 50, '-');

  fputs("Choose an action:\n\ta. Append "
        "contact\n\te. Edit contact info\n\tr. "
        "Remove contact\n\tp. Print\n\tq. Quit\nInput: ",
        stdout);
  return input_string();
}

void
append_contact(PhoneBook* phonebook)
{
  puts("Append contact action chosen");
  Contact* contact = contact_construct();
  phonebook_append(phonebook, contact);
  free(contact);
}

void
edit_contact(PhoneBook* phonebook)
{
  fputs("Edit contact info action chosen\nInput contact id: ", stdout);
  InputResult contact_id;
  if ((contact_id = input_unsigned()).success == false)
    return;
  phonebook_edit(phonebook, *((unsigned*)contact_id.value));
}

void
remove_contact(PhoneBook* phonebook)
{
  fputs("Remove contact action chosen\nInput contact id: ", stdout);
  InputResult contact_id;
  if ((contact_id = input_unsigned()).success == false)
    return;
  phonebook_remove(phonebook, *((unsigned*)contact_id.value));
}

void
print_contacts(PhoneBook* phonebook)
{
  puts("Print contact info action choosen");
  phonebook_print(*phonebook);
}
