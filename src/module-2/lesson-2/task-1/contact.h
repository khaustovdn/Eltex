#ifndef CONTACT_H_
#define CONTACT_H_

#include "../../../utils/utils.h"

typedef struct
{
  Variable surname;
  Variable name;
  Variable patronymic;
} Initials;

typedef struct
{
  Variable mobile;
  Variable home;
  Variable work;
} PhoneNumber;

typedef struct
{
  Variable vkontakte;
  Variable youtube;
  Variable telegram;
} SocialNetwork;

typedef struct
{
  unsigned id;
  Initials initials;
  Variable job_title;
  Variable place_of_work;
  PhoneNumber phone_number;
  Variable email_address;
  SocialNetwork social_network;
} Contact;

void
contact_fill_property(Variable* property);

void
contact_fill_required_properties(Contact* contact);

void
contact_fill_optional_properties(Contact* contact);

char*
contact_menu();

Contact*
contact_construct();

void
contact_print(Contact contact);

#endif // CONTACT_H_
