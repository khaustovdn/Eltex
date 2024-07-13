#ifndef CONTACT_H_
#define CONTACT_H_

typedef struct
{
  char *surname;
  char *name;
  char *patronymic;
} Initials;

typedef struct
{
  char *mobile;
  char *home;
  char *work;
} PhoneNumber;

typedef struct
{
  char *vkontakte;
  char *google;
  char *telegram;
} SocialNetworks;

typedef struct
{
  Initials initials;
  char *job_title;
  char *place_of_work;
  PhoneNumber phone_number;
  char *email_address;
  SocialNetworks social_networks;
} Contact;

#endif // CONTACT_H_
