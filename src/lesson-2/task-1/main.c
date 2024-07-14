#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "phonebook.h"

static Contact* phonebook_contacts;

char
phonebook_menu();

char*
create_wrapped_title(const char* title,
                     int width,
                     char symbol);

int
main(int argc, char* argv[])
{
  char* wrapped_title =
    create_wrapped_title("Contacts", 30, '-');
  if (wrapped_title == NULL) {
    return EXIT_FAILURE;
  }
  puts(wrapped_title);
  free(wrapped_title);

  char action_choice;
  PhoneBook* phonebook = phonebook_constuct();
  while ((action_choice = phonebook_menu()) != 'q') {
    switch (action_choice) {
      case 'a':
        puts("Append contact action chosen");
        Contact contact;
        contact_construct(&contact);
        phonebook_append(phonebook, contact);
        break;
      case 'e':
        puts("Edit contact info action chosen");
        break;
      case 'r':
        puts("Remove contact action chosen");
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
  fputs("Choose an action:\n\ta. Append "
        "contact\n\te. Edit contact info\n\tr. "
        "Remove contact\n\tq. Quit\nInput: ",
        stdout);
  char action_choice = fgetc(stdin);
  while (fgetc(stdin) != '\n')
    ;
  return action_choice;
}

char*
create_wrapped_title(const char* title,
                     int width,
                     char symbol)
{
  if (width < strlen(title)) {
    fputs("Error: Width is too small for the title",
          stdout);
    return NULL;
  }
  size_t wrap_width = (width - strlen(title)) >> 1;

  char* result = (char*)malloc((width + 1) * sizeof(char));
  if (result == NULL) {
    fputs("Error: Failed to allocate memory", stdout);
    return NULL;
  }

  memset(result, symbol, width);
  result[width] = '\0';

  for (int i = 0; i < strlen(title); i++)
    result[i + wrap_width] = title[i];

  return result;
}
