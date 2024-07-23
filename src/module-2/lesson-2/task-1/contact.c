#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "contact.h"

void
contact_fill_property(Variable* property)
{
  printf("Input %s: ", property->name);
  strncpy(property->value, input_string(), MAX_LEN);
}

#define DECLARE_VARIABLE(member_name)                                          \
  variable_construct(&member_name, #member_name)

void
contact_fill_required_properties(Contact* contact)
{
  contact->id = 0;
  contact_fill_property(DECLARE_VARIABLE(contact->initials.surname));
  contact_fill_property(DECLARE_VARIABLE(contact->initials.name));
}

void
contact_fill_optional_properties(Contact* contact)
{
  CommandEntry commands[] = {
    { "ip", DECLARE_VARIABLE(contact->initials.patronymic) },
    { "jt", DECLARE_VARIABLE(contact->job_title) },
    { "pow", DECLARE_VARIABLE(contact->place_of_work) },
    { "mpn", DECLARE_VARIABLE(contact->phone_number.mobile) },
    { "hpn", DECLARE_VARIABLE(contact->phone_number.home) },
    { "wpn", DECLARE_VARIABLE(contact->phone_number.work) },
    { "ea", DECLARE_VARIABLE(contact->email_address) },
    { "vksn", DECLARE_VARIABLE(contact->social_network.vkontakte) },
    { "ytsn", DECLARE_VARIABLE(contact->social_network.youtube) },
    { "tgsn", DECLARE_VARIABLE(contact->social_network.telegram) },
    { NULL, NULL }
  };

  char* action_choice;

  while (strncmp((action_choice = contact_menu()), "q", MAX_LEN) != 0) {
    int i = 0;
    for (;commands[i].name != NULL; i++)
      if (strncmp(action_choice, commands[i].name, MAX_LEN) == 0) {
        contact_fill_property(commands[i].property);
        break;
      }
    if (commands[i].name == NULL)
      puts("Invalid choice of action");
  }

  free(action_choice);
}

char*
contact_menu()
{
  output_wrapped_title("Contact Menu", 50, '-');

  fputs("Do you want to set it up:\n\tip. Patronymic\n\t"
        "jt. Job Title\n\tpow. Place of Work\n\t"
        "mpn. Mobile Phone Number\n\thpn Home Phone "
        "Number\n\twpn. Work Phone Number\n\tea. "
        "E-Mail Address\n\tvksn. VK Social Network\n\tytsn. "
        "YouTube Social Network\n\ttgsn. Telegram "
        "Social Network\n\tq. Quit\nInput: ",
        stdout);

  return input_string();
}

Contact*
contact_construct()
{
  Contact* contact = (Contact*)malloc(sizeof(Contact));
  if (contact == NULL) {
    fprintf(stderr,
            "Error: Unable to allocate memory "
            "for phonebook.\n");
    exit(EXIT_FAILURE);
  }

  memset(contact, 0, sizeof(Contact));
  contact_fill_required_properties(contact);
  contact_fill_optional_properties(contact);
  return contact;
}

void
contact_print(Contact contact)
{
  Variable* properties[] = { &contact.initials.surname,
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
                             NULL };

  output_wrapped_title("Item", 30, '-');

  printf("id: %d\n", contact.id);
  for (int i = 0; properties[i] != NULL; i++) {
    if (strcmp(properties[i]->value, "\0") != 0) {
      printf("%s: %s\n", properties[i]->name, properties[i]->value);
    }
  }
}
