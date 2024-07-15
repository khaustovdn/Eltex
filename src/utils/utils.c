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

int
input_number()
{
  char* action_choice = (char*)malloc(MAX_LEN * sizeof(char));
  if (action_choice == NULL) {
    fprintf(stderr, "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  int i = 0;
  int c;
  while ((c = fgetc(stdin)) != '\n' && i < MAX_LEN - 1) {
    action_choice[i] = c;
    i++;
  }
  action_choice[i] = '\0';
  if (i == MAX_LEN - 1 && c != '\n') {
    printf("Warning: Input exceeds the maximum length. It will be "
           "truncated.\n");
    while ((c = fgetc(stdin)) != '\n' && c != EOF)
      ;
  }

  int contact_id;
  if (sscanf(action_choice, "%d", &contact_id) != 1) {
    fprintf(stderr, "Error: Invalid input. Please enter a valid contact id.\n");
    free(action_choice);
    return -1;
  }

  free(action_choice);
  return contact_id;
}

