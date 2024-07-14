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
    exit(EXIT_FAILURE);
  }

  phonebook->contacts =
    (Contact*)malloc(MAX_CONTACTS * sizeof(Contact));
  if (phonebook->contacts == NULL) {
    free(phonebook);
    fprintf(
      stderr,
      "Error: Unable to allocate memory for contacts.\n");
    exit(EXIT_FAILURE);
  }

  phonebook->capacity = MAX_CONTACTS;
  phonebook->count = 0;

  return phonebook;
}

void
phonebook_append(PhoneBook* phonebook, Contact contact)
{
  if (phonebook->count < MAX_CONTACTS) {
    phonebook->contacts[phonebook->count] = contact;
    phonebook->count++;
  } else {
    puts("Warning: the phone book is full");
  }
}

void
phonebook_edit(PhoneBook* phonebook, Contact* contact)
{}

void
phonebook_remove(PhoneBook* phonebook, int id)
{}
