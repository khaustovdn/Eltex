#ifndef MAIN_H_
#define MAIN_H_

#include "contact.h"
#include "phonebook.h"

static Contact* phonebook_contacts;

int
main(int argc, char* argv[]);

char
phonebook_menu();

char*
create_wrapped_title(const char* title,
                     int width,
                     char symbol);

#endif // MAIN_H_
