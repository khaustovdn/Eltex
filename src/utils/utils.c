#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

Variable*
variable_construct(Variable* property, const char* name)
{
  strncpy(property->name, name, MAX_LEN - 1);
  property->name[MAX_LEN - 1] = '\0';
  return property;
}

char*
create_wrapped_title(const char* title, int width, char symbol)
{
  if (width < strlen(title)) {
    fputs("Error: Width is too small for the title", stdout);
    return NULL;
  }
  size_t wrap_width = (width - strlen(title)) >> 1;

  char* result = (char*)malloc((width + 1) * sizeof(char));
  if (result == NULL) {
    fputs("Error: Failed to allocate memory", stdout);
    return NULL;
  }

  memset(result, symbol, width);
  result[width] = '\n';

  for (int i = 0; i < strlen(title); i++)
    result[i + wrap_width] = title[i];

  puts("");

  return result;
}

void
output_wrapped_title(char* wrapped_title)
{
  if (wrapped_title == NULL) {
    fprintf(stderr, "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }
  puts(wrapped_title);
  free(wrapped_title);
}

bool
is_digit(char ch)
{
  return (ch >= '0' && ch <= '9');
}

bool
is_unsigned(const char* str)
{
  int i = 0;
  while (str[i] != '\0' && i < MAX_LEN) {
    if (!is_digit(str[i])) {
      return false;
    }
    i++;
  }
  return true;
}

bool
is_integer(const char* str)
{
  if (*str == '-') {
    char* substr = (char*)malloc(MAX_LEN * sizeof(char));
    if (substr == NULL) {
      fprintf(stderr, "Error: Memory allocation failed.\n");
      exit(EXIT_FAILURE);
    }

    strncpy(substr, str + 1, MAX_LEN);
    return is_unsigned(substr);
  }
  return is_unsigned(str);
}

bool
is_double(const char* str)
{
  char* temp = strdup(str);
  char* token = strtok(temp, ".");
  if (token == NULL) {
    return false;
  }
  if (!is_integer(token)) {
    return false;
  }
  token = strtok(NULL, ".");
  if (token != NULL && !is_unsigned(token)) {
    return false;
  }
  return true;
}

InputResult
input_integer()
{
  InputResult result;
  {
    result.value = malloc(sizeof(int));
    result.success = false;
  }

  char* str = input_string();
  if (is_integer(str) == false) {
    puts("Error: Invalid input. Please enter a valid integer.");
    free(str);
    free(result.value);
    return result;
  }
  if (sscanf(str, "%d", (int*)result.value) != 1) {
    fprintf(stderr, "Error: Invalid input. Please enter a valid integer.\n");
    free(str);
    free(result.value);
    return result;
  }

  free(str);
  result.success = true;
  return result;
}

InputResult
input_double()
{
  InputResult result;
  {
    result.value = malloc(sizeof(double));
    result.success = false;
  }

  char* str = input_string();
  if (is_double(str) == false) {
    puts("Error: Invalid input. Please enter a valid double.");
    free(str);
    free(result.value);
    return result;
  }
  if (sscanf(str, "%lf", (double*)result.value) != 1) {
    fprintf(stderr, "Error: Invalid input. Please enter a valid double.\n");
    free(str);
    free(result.value);
    return result;
  }

  free(str);
  result.success = true;
  return result;
}

char*
input_string()
{
  char* result = (char*)malloc(MAX_LEN * sizeof(char));
  if (result == NULL) {
    fprintf(stderr, "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  int i = 0;
  int c;
  while ((c = fgetc(stdin)) != '\n' && i < MAX_LEN - 1) {
    result[i] = c;
    i++;
  }
  result[i] = '\0';
  if (i == MAX_LEN - 1 && c != '\n') {
    printf("Warning: Input exceeds the maximum length. It will be "
           "truncated.\n");
    while ((c = fgetc(stdin)) != '\n' && c != EOF)
      ;
  }
  return result;
}

char
input_char()
{
  char result = fgetc(stdin);
  int i = 0;
  while (fgetc(stdin) != '\n')
    i++;
  if (i > 0) {
    puts("Warning: Input exceeds the maximum length.");
    return '\0';
  }
  return result;
}
