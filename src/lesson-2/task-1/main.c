#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "phonebook.h"

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
  while ((action_choice = phonebook_menu()) != 'q') {
    switch (action_choice) {
      case 'a':
        puts("Append contact action chosen");
        Contact contact;
        contact_construct(&contact);
        break;
      case 'e':
        puts("Edit contact info action chosen");
        break;
      case 'r':
        puts("Remove contact action chosen");
        break;
      case 'q':
        return EXIT_FAILURE;
      default:
        puts("Invalid choice of action");
    }
  }

  return EXIT_SUCCESS;
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
