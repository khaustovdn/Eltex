#ifndef UTILS_H_
#define UTILS_H_

#include <stdbool.h>

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
  void* property;
} CommandEntry;

Variable*
variable_construct(Variable* property, const char* name);

void
output_wrapped_title(const char* title, int width, char symbol);

bool
is_digit(char ch);

bool
is_unsigned(const char* str);

bool
is_integer(const char* str);

bool
is_double(const char* str);

InputResult
input_unsigned();

InputResult
input_integer();

InputResult
input_double();

char*
input_string();

#endif // UTILS_H_
