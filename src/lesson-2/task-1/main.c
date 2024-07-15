#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

int
main(int argc, char* argv[])
{
  char* wrapped_title = create_wrapped_title("PhoneBook Application", 50, '-');
  if (wrapped_title == NULL) {
    fprintf(stderr, "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }
  puts(wrapped_title);
  free(wrapped_title);

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
        char* action_choice = (char*)malloc(MAX_LEN * sizeof(char));
        if (action_choice == NULL) {
          fprintf(stderr, "Error: Memory allocation failed.\n");
          exit(EXIT_FAILURE);
        }

        int i = 0;
        int c;
        while ((c = fgetc(stdin)) != '\n' && i < MAX_LEN - 1) {
          action_choice[i] = c;
          i++;
        }
        action_choice[i] = '\0';

        if (i == MAX_LEN - 1 && c != '\n') {
          printf("Warning: Input exceeds the maximum length. It will be "
                 "truncated.\n");
          while ((c = fgetc(stdin)) != '\n' && c != EOF)
            ;
        }

        int contact_id;
        if (sscanf(action_choice, "%d", &contact_id) != 1) {
          fprintf(stderr,
                  "Error: Invalid input. Please enter a valid contact id.\n");
          free(action_choice);
          break;
        }

        phonebook_edit(phonebook, contact_id);
        free(action_choice);
        break;
      }
      case 'r': {
        fputs("Remove contact action chosen\nInput contact id: ", stdout);
        char* action_choice = (char*)malloc(MAX_LEN * sizeof(char));
        if (action_choice == NULL) {
          fprintf(stderr, "Error: Memory allocation failed.\n");
          exit(EXIT_FAILURE);
        }

        int i = 0;
        int c;
        while ((c = fgetc(stdin)) != '\n' && i < MAX_LEN - 1) {
          action_choice[i] = c;
          i++;
        }
        action_choice[i] = '\0';

        if (i == MAX_LEN - 1 && c != '\n') {
          printf("Warning: Input exceeds the maximum length. It will be "
                 "truncated.\n");
          while ((c = fgetc(stdin)) != '\n' && c != EOF)
            ;
        }

        int contact_id;
        if (sscanf(action_choice, "%d", &contact_id) != 1) {
          fprintf(stderr,
                  "Error: Invalid input. Please enter a valid contact id.\n");
          free(action_choice);
          break;
        }

        phonebook_remove(phonebook, contact_id);
        free(action_choice);
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
  if (wrapped_title == NULL) {
    fprintf(stderr, "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }
  puts(wrapped_title);
  free(wrapped_title);

  fputs("Choose an action:\n\ta. Append "
        "contact\n\te. Edit contact info\n\tr. "
        "Remove contact\n\tp. Print\n\tq. Quit\nInput: ",
        stdout);
  char action_choice = fgetc(stdin);
  while (fgetc(stdin) != '\n')
    ;
  return action_choice;
}

char*
create_wrapped_title(const char* title, int width, char symbol)
{
  if (width < strlen(title)) {
    fputs("Error: Width is too small for the title", stdout);
    return NULL;
  }
  size_t wrap_width = (width - strlen(title)) >> 1;

  char* result = (char*)malloc((width + 1) * sizeof(char));
  if (result == NULL) {
    fputs("Error: Failed to allocate memory", stdout);
    return NULL;
  }

  memset(result, symbol, width);
  result[width] = '\n';

  for (int i = 0; i < strlen(title); i++)
    result[i + wrap_width] = title[i];

  puts("");

  return result;
}
