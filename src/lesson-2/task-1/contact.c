#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "contact.h"
#include "main.h"

Variable*
variable_construct(Variable* property,
                   const char* name)
{
  strncpy(property->name, name, MAX_LEN - 1);
  property->name[MAX_LEN - 1] = '\0';
  return property;
}

void
contact_fill_property(Variable* property)
{
  printf("Input %s: ", property->name);

  int i = 0;
  while ((property->value[i] = fgetc(stdin)) !=
           '\n' &&
         i < MAX_LEN) {
    i++;
  }

  if (i == MAX_LEN &&
      property->value[i - 1] != '\n') {
    printf("Warning: Input exceeds the maximum "
           "length. It will be truncated.\n");
    while (fgetc(stdin) != '\n')
      ;
  }

  property->value[i] = '\0';
}

#define DECLARE_VARIABLE(member_name)            \
  variable_construct(&member_name, #member_name)

void
contact_fill_required_properties(Contact* contact)
{
  contact->id = 0;
  contact_fill_property(
    DECLARE_VARIABLE(contact->initials.surname));
  contact_fill_property(
    DECLARE_VARIABLE(contact->initials.name));
}

void
contact_fill_optional_properties(Contact* contact)
{
  char* action_choice =
    (char*)malloc(MAX_LEN * sizeof(char));
  if (action_choice == NULL) {
    fprintf(stderr,
            "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  CommandEntry commands[] = {
    { "ip",
      DECLARE_VARIABLE(
        contact->initials.patronymic) },
    { "jt",
      DECLARE_VARIABLE(contact->job_title) },
    { "pow",
      DECLARE_VARIABLE(contact->place_of_work) },
    { "mpn",
      DECLARE_VARIABLE(
        contact->phone_number.mobile) },
    { "hpn",
      DECLARE_VARIABLE(
        contact->phone_number.home) },
    { "wpn",
      DECLARE_VARIABLE(
        contact->phone_number.work) },
    { "ea",
      DECLARE_VARIABLE(contact->email_address) },
    { "vksn",
      DECLARE_VARIABLE(
        contact->social_network.vkontakte) },
    { "ytsn",
      DECLARE_VARIABLE(
        contact->social_network.youtube) },
    { "tgsn",
      DECLARE_VARIABLE(
        contact->social_network.telegram) },
    { NULL, NULL }
  };
  for (int i = 0; commands[i].name != NULL; i++) {
    strncpy(
      commands[i].property->value, "\0", MAX_LEN);
  }

  while (strcmp(strncpy(action_choice,
                        contact_menu(),
                        MAX_LEN),
                "q") != 0) {
    int i = 0;
    while (commands[i].name != NULL) {
      if (strcmp(action_choice,
                 commands[i].name) == 0) {
        contact_fill_property(
          commands[i].property);
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

Contact*
contact_construct()
{
  Contact* contact =
    (Contact*)malloc(sizeof(Contact));
  if (contact == NULL) {
    fprintf(stderr,
            "Error: Unable to allocate memory "
            "for phonebook.\n");
    exit(EXIT_FAILURE);
  }

  contact_fill_required_properties(contact);
  contact_fill_optional_properties(contact);
  return contact;
}

const char*
contact_menu()
{
  char* wrapped_title =
    create_wrapped_title("Main Menu", 50, '-');
  if (wrapped_title == NULL) {
    fprintf(stderr,
            "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }
  puts(wrapped_title);
  free(wrapped_title);

  fputs(
    "Do you want to set it up:\n\tip. "
    "Patronymic\n\t"
    "jt. Job Title\n\tpow. Place of Work\n\t"
    "mpn. Mobile Phone Number\n\thpn Home Phone "
    "Number\n\twpn. Work Phone Number\n\tea. "
    "E-Mail "
    "Address\n\tvksn. VK Social Network\n\tytsn. "
    "YouTube Social Network\n\ttgsn. Telegram "
    "Social Network\n\tq. Quit\nInput: ",
    stdout);
  char* action_choice =
    (char*)malloc(MAX_LEN * sizeof(char));
  if (action_choice == NULL) {
    fprintf(stderr,
            "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  int i = 0;
  while ((action_choice[i] = fgetc(stdin)) !=
           '\n' &&
         i < MAX_LEN) {
    i++;
  }

  if (i == MAX_LEN &&
      action_choice[i - 1] != '\n') {
    printf("Warning: Input exceeds the maximum "
           "length. It will be truncated.\n");
    while (fgetc(stdin) != '\n')
      ;
  }

  action_choice[i] = '\0';

  return action_choice;
}

void
contact_print(Contact contact)
{
  Variable* properties[] = {
    &contact.initials.surname,
    &contact.initials.name,
    &contact.initials.patronymic,
    &contact.job_title,
    &contact.place_of_work,
    &contact.phone_number.mobile,
    &contact.phone_number.home,
    &contact.phone_number.work,
    &contact.email_address,
    &contact.social_network.vkontakte,
    &contact.social_network.youtube,
    &contact.social_network.telegram,
    NULL
  };

  char* wrapped_title =
    create_wrapped_title("Item", 30, '-');
  if (wrapped_title == NULL) {
    fprintf(stderr,
            "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }
  puts(wrapped_title);
  free(wrapped_title);

  printf("id: %d\n", contact.id);
  for (int i = 0; properties[i] != NULL; i++) {
    if (strcmp(properties[i]->value, "\0") != 0) {
      printf("%s: %s\n",
             properties[i]->name,
             properties[i]->value);
    }
  }
}
