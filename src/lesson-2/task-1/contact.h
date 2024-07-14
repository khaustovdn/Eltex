#ifndef CONTACT_H_
#define CONTACT_H_

#define MAX_LEN 256

typedef struct
{
  char surname[MAX_LEN];
  char name[MAX_LEN];
  char patronymic[MAX_LEN];
} Initials;

typedef struct
{
  char mobile[MAX_LEN];
  char home[MAX_LEN];
  char work[MAX_LEN];
} PhoneNumber;

typedef struct
{
  char vkontakte[MAX_LEN];
  char youtube[MAX_LEN];
  char telegram[MAX_LEN];
} SocialNetwork;

typedef struct
{
  unsigned id;
  Initials initials;
  char job_title[MAX_LEN];
  char place_of_work[MAX_LEN];
  PhoneNumber phone_number;
  char email_address[MAX_LEN];
  SocialNetwork social_network;
} Contact;

void
contact_construct(Contact* contact);

const char*
contact_menu();

void
contact_fill_property(char* property,
                      const char* property_name);

#endif // CONTACT_H_
