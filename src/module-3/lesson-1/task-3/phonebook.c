#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "phonebook.h"

PhoneBook*
phonebook_constuct()
{
  PhoneBook* phonebook = (PhoneBook*)malloc(sizeof(PhoneBook));
  if (phonebook == NULL) {
    fprintf(stderr,
            "Error: Unable to allocate memory "
            "for phonebook.\n");
    exit(EXIT_FAILURE);
  }

  phonebook->contacts = (Contact*)malloc(MAX_CONTACTS * sizeof(Contact));
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
phonebook_append(PhoneBook* phonebook, Contact* contact)
{
  if (phonebook->count < MAX_CONTACTS) {
    int i = 0;
    while (i < phonebook->capacity) {
      if (phonebook_search(*phonebook, i + 1) == -1)
        break;
      i++;
    }

    contact->id = i + 1;
    phonebook->contacts[phonebook->count] = *contact;
    phonebook->count++;
  } else {
    puts("Warning: the phone book is full");
  }
}

static int
phonebook_search(PhoneBook phonebook, unsigned id)
{
  for (int i = 0; i < phonebook.count; i++) {
    if (phonebook.contacts[i].id == id) {
      return i;
    }
  }
  return -1;
}

void
phonebook_edit(PhoneBook* phonebook, unsigned id)
{
  int index = phonebook_search(*phonebook, id);
  if (index != -1)
    contact_fill_optional_properties(&phonebook->contacts[index]);
  else
    printf("Contact with ID %d not found.\n", id);
}

void
phonebook_remove(PhoneBook* phonebook, unsigned id)
{
  int index = phonebook_search(*phonebook, id);
  if (index != -1) {
    for (int i = index; i < phonebook->count - 1; i++) {
      phonebook->contacts[i] = phonebook->contacts[i + 1];
    }
    phonebook->count--;
  } else {
    printf("Contact with ID %d not found.\n", id);
  }
}

void
phonebook_print(PhoneBook phonebook)
{
  for (int i = 0; i < phonebook.count; i++)
    contact_print(phonebook.contacts[i]);
}

void
phonebook_save(PhoneBook phonebook)
{
  int fd = open("file.bin", O_CREAT | O_TRUNC | O_WRONLY, 0777);
  if (fd == -1) {
    printf("Error: File cannot be opened for writing\n");
    return;
  }
  for (int i = 0; i < phonebook.count; i++)
    if (write(fd, &phonebook.contacts[i], sizeof(phonebook.contacts[i])) == -1) {
      printf("Error: Writing to file\n");
      break;
    }
  close(fd);
}

void
phonebook_read(PhoneBook* phonebook)
{
  int fd;
  if ((fd = open("file.bin", O_RDONLY, 0)) == -1) {
    printf("Warning: File does not exist\n");
    return;
  }
  Contact contact;
  for (; read(fd, &contact, sizeof(contact)) > 0; )
    phonebook_append(phonebook, &contact);
  close(fd);
}
