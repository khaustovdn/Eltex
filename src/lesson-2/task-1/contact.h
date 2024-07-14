#ifndef CONTACT_H_
#define CONTACT_H_

#define MAX_LEN 256

typedef struct
{
  char value[MAX_LEN];
  char name[MAX_LEN];
} Variable;

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
contact_construct(Contact* contact);

const char*
contact_menu();

void
contact_fill_property(Variable* property);

#endif // CONTACT_H_
