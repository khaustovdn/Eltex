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
  void* value;
  bool success;
} InputResult;

typedef struct
{
  const char* name;
  Variable* property;
} CommandEntry;

Variable*
variable_construct(Variable* property, const char* name);

char*
create_wrapped_title(const char* title, int width, char symbol);

void
output_wrapped_title(char* wrapped_title);

bool
is_digit(char ch);

bool
is_unsigned(const char* str);

bool
is_integer(const char* str);

bool
is_double(const char* str);

InputResult
input_integer();

InputResult
input_double();

char*
input_string();

char
input_char();

#endif // UTILS_H_
