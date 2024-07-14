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
    exit(EXIT_FAILURE);
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

typedef struct
{
  const char* name;
  char* property;
} CommandEntry;

void
contact_construct(Contact* contact)
{
  contact->id = 0;
  CONTACT_FILL_PROPERTY(contact->initials.surname);
  CONTACT_FILL_PROPERTY(contact->initials.name);

  char* action_choice =
    (char*)malloc(MAX_LEN * sizeof(char));
  if (action_choice == NULL) {
    fprintf(stderr, "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  CommandEntry commands[] = {
    { "ip", contact->initials.patronymic },
    { "jt", contact->job_title },
    { "pow", contact->place_of_work },
    { "mpn", contact->phone_number.mobile },
    { "hpn", contact->phone_number.home },
    { "wpn", contact->phone_number.work },
    { "ea", contact->email_address },
    { "vksn", contact->social_network.vkontakte },
    { "ytsn", contact->social_network.youtube },
    { "tgsn", contact->social_network.telegram },
    { NULL, NULL }
  };

  while (
    strcmp(strncpy(action_choice, contact_menu(), MAX_LEN),
           "q") != 0) {
    int i = 0;
    while (commands[i].name != NULL) {
      if (strcmp(action_choice, commands[i].name) == 0) {
        CONTACT_FILL_PROPERTY(commands[i].property);
        break;
      }
      i++;
    }

    if (commands[i].name == NULL) {
      puts("Invalid choice of action");
    }
  }

  free(action_choice);
}

const char*
contact_menu()
{
  fputs("Do you want to set it up:\n\tip. Patronymic\n\t"
        "jt. Job Title\n\tpow. Place of Work\n\t"
        "mpn. Mobile Phone Number\n\thpn Home Phone "
        "Number\n\twpn. Work Phone Number\n\tea. E-Mail "
        "Address\n\tvksn. VK Social Network\n\tytsn. "
        "YouTube Social Network\n\ttgsn. Telegram "
        "Social Network\n\tq. Quit\nInput: ",
        stdout);
  char* action_choice =
    (char*)malloc(MAX_LEN * sizeof(char));
  if (action_choice == NULL) {
    fprintf(stderr, "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  int i = 0;
  while ((action_choice[i] = fgetc(stdin)) != '\n' &&
         i < MAX_LEN) {
    i++;
  }

  if (i == MAX_LEN && action_choice[i - 1] != '\n') {
    printf("Warning: Input exceeds the maximum "
           "length. It will be truncated.\n");
    while (fgetc(stdin) != '\n')
      ;
  }

  action_choice[i] = '\0';

  return action_choice;
}
