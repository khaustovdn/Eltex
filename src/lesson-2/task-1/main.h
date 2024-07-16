#ifndef MAIN_H_
#define MAIN_H_

#include "contact.h"
#include "phonebook.h"

static Contact* phonebook_contacts;

int
main(int argc, char* argv[]);

char*
phonebook_menu();

void
append_contact(PhoneBook* phonebook);

void
edit_contact(PhoneBook* phonebook);

void
remove_contact(PhoneBook* phonebook);

void
print_contacts(PhoneBook* phonebook);

#endif // MAIN_H_
