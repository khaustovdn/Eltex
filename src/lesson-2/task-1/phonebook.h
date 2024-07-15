#ifndef PHONEBOOK_H_
#define PHONEBOOK_H_

#include "contact.h"
#define MAX_CONTACTS 16

typedef struct
{
  Contact* contacts;
  int capacity;
  int count;
} PhoneBook;

PhoneBook*
phonebook_constuct();

void
phonebook_append(PhoneBook* phonebook, Contact* contact);

static int
phonebook_search(PhoneBook phonebook, int id);

void
phonebook_edit(PhoneBook* phonebook, int id);

void
phonebook_remove(PhoneBook* phonebook, int id);

void
phonebook_print(PhoneBook phonebook);

#endif // PHONEBOOK_H_
