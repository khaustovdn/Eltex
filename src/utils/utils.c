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

void
output_wrapped_title(const char* title, int width, char symbol)
{
  if (width < strlen(title)) {
    fputs("Warning: Width is too small for the title", stdout);
    return;
  }
  size_t wrap_width = (width - strlen(title)) >> 1;

  char* result = (char*)malloc((width + 1) * sizeof(char));
  if (result == NULL) {
    fprintf(stderr,
            "Error: Unable to allocate memory "
            "for wrapped title.\n");
    exit(EXIT_FAILURE);
  }

  memset(result, symbol, width);
  result[width] = '\n';

  for (int i = 0; i < strlen(title); i++)
    result[i + wrap_width] = title[i];

  printf("\n%s\n", result);
  free(result);
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
input_unsigned()
{
  InputResult result;
  {
    result.value = malloc(sizeof(unsigned));
    result.success = false;
  }

  char* str = input_string();
  if (is_unsigned(str) == false) {
    puts("Error: Invalid input. Please enter a valid unsigned integer.");
    free(str);
    free(result.value);
    return result;
  }
  if (sscanf(str, "%u", (unsigned*)result.value) != 1) {
    fprintf(stderr,
            "Error: Invalid input. Please enter a valid unsigned integer.\n");
    free(str);
    free(result.value);
    return result;
  }

  free(str);
  result.success = true;
  return result;
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
