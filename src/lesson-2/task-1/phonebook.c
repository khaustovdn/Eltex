#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "contact.h"
#include "phonebook.h"

PhoneBook*
phonebook_constuct()
{
  PhoneBook* phonebook =
    (PhoneBook*)malloc(sizeof(PhoneBook));
  if (phonebook == NULL) {
    fprintf(
      stderr,
      "Error: Unable to allocate memory for phonebook.\n");
    exit(1);
  }

  phonebook->contacts =
    (Contact*)malloc(N * sizeof(Contact));
  if (phonebook->contacts == NULL) {
    free(phonebook);
    fprintf(
      stderr,
      "Error: Unable to allocate memory for contacts.\n");
    exit(1);
  }

  phonebook->capacity = N;
  phonebook->count = 0;

  return phonebook;
}

void
phonebook_append(PhoneBook* phonebook, Contact contact)
{
  for (int i = 0; i < N; i++)
    if (phonebook->contacts[i].initials.name[0] == '\0') {
      contact.id = i + 1;
      phonebook->contacts[i] = contact;
      break;
    }
}
