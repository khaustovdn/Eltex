#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "contact.h"

void
contact_fill_property(char* property,
                      const char* property_name)
{
  char* last_token = (char*)malloc(MAX_LEN * sizeof(char));
  char* extracted_property_name =
    (char*)malloc(MAX_LEN * sizeof(char));
  if (last_token == NULL ||
      extracted_property_name == NULL) {
    fprintf(stderr, "Error: Memory allocation failed.\n");
    exit(1);
  }

  strcpy(last_token, property_name);
  char* token = strtok(last_token, ".");
  while (token != NULL) {
    strcpy(extracted_property_name, token);
    token = strtok(NULL, ".");
  }

  printf("Input %s: ", extracted_property_name);

  int i = 0;
  while ((property[i] = fgetc(stdin)) != '\n' &&
         i < MAX_LEN) {
    i++;
  }

  if (i == MAX_LEN && property[i - 1] != '\n') {
    printf("Warning: Input exceeds the maximum "
           "length. It will be truncated.\n");
    while (fgetc(stdin) != '\n')
      ;
  }

  property[i] = '\0';

  free(last_token);
  free(extracted_property_name);
}

#define CONTACT_FILL_PROPERTY(property)                    \
  contact_fill_property(property, #property)

void
contact_construct(Contact* contact)
{
  CONTACT_FILL_PROPERTY(contact->initials.surname);
  CONTACT_FILL_PROPERTY(contact->initials.name);
}
