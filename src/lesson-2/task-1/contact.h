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
  const char* name;
  Variable* property;
} CommandEntry;

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

Variable*
variable_construct(Variable* property, const char* name);

void
contact_fill_property(Variable* property);

void
contact_fill_required_properties(Contact* contact);

void
contact_fill_optional_properties(Contact* contact);

Contact*
contact_construct();

const char*
contact_menu();

void
contact_print(Contact contact);

#endif // CONTACT_H_
