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

int
input_number()
{
  char* result = input_string();
  int contact_id;
  if (sscanf(result, "%d", &contact_id) != 1) {
    fprintf(stderr, "Error: Invalid input. Please enter a valid contact id.\n");
    free(result);
    return -1;
  }

  free(result);
  return contact_id;
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
