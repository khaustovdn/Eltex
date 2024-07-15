#ifndef UTILS_H_
#define UTILS_H_

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

Variable*
variable_construct(Variable* property, const char* name);

char*
create_wrapped_title(const char* title, int width, char symbol);

int
input_number();

#endif // UTILS_H_
