#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "contact.h"
#include "main.h"
#include "phonebook.h"

PhoneBook*
phonebook_constuct()
{
  PhoneBook* phonebook =
    (PhoneBook*)malloc(sizeof(PhoneBook));
  if (phonebook == NULL) {
    fprintf(stderr,
            "Error: Unable to allocate memory "
            "for phonebook.\n");
    exit(EXIT_FAILURE);
  }

  phonebook->contacts = (Contact*)malloc(
    MAX_CONTACTS * sizeof(Contact));
  if (phonebook->contacts == NULL) {
    free(phonebook);
    fprintf(stderr,
            "Error: Unable to allocate memory "
            "for contacts.\n");
    exit(EXIT_FAILURE);
  }

  phonebook->capacity = MAX_CONTACTS;
  phonebook->count = 0;

  return phonebook;
}

void
phonebook_append(PhoneBook* phonebook,
                 Contact* contact)
{
  if (phonebook->count < MAX_CONTACTS) {
    contact->id = phonebook->count + 1;
    phonebook->contacts[phonebook->count] =
      *contact;
    phonebook->count++;
  } else {
    puts("Warning: the phone book is full");
  }
}

void
phonebook_edit(PhoneBook* phonebook, int id)
{}

void
phonebook_remove(PhoneBook* phonebook, int id)
{}

void
phonebook_print(PhoneBook phonebook)
{
  char* wrapped_title =
    create_wrapped_title("Contacts", 50, '-');
  if (wrapped_title == NULL) {
    fprintf(stderr,
            "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }
  puts(wrapped_title);
  free(wrapped_title);
  for (int i = 0; i < phonebook.count; i++)
    contact_print(phonebook.contacts[i]);
}
