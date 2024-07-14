#ifndef PHONEBOOK_H_
#define PHONEBOOK_H_

#include "contact.h"
#define N 16

typedef struct
{
  Contact* contacts;
  int capacity;
  int count;
} PhoneBook;

PhoneBook*
phonebook_constuct();

void
phonebook_append(PhoneBook* phonebook, Contact contact);

void
phonebook_edit(PhoneBook* phonebook, Contact* contact);

void
phonebook_remove(PhoneBook* phonebook, int id);

#endif // PHONEBOOK_H_
