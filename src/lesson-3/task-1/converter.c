#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "converter.h"

mode_t
convert_permissions_to_mode(const char* permissions)
{
  mode_t mode = 0;

  for (int i = 0; i < strlen(permissions); i += 3)
    mode = (mode << 3) |
           ((permissions[i] == 'r') << 2) |
           ((permissions[i + 1] == 'w') << 1) |
           (permissions[i + 2] == 'x');

  return mode;
}

char*
convert_mode_to_binary(mode_t mode)
{
  char* result = (char*)malloc(MAX_LEN * sizeof(char));

  if (result == NULL) {
    fprintf(stderr, "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < 9; ++i)
    result[i] = ((mode >> (8 - i)) & 1) ? '1' : '0';
  result[9] = '\0';

  return result;
}

char*
convert_mode_to_octal(mode_t mode)
{
  char* result = (char*)malloc(MAX_LEN * sizeof(char));

  if (result == NULL) {
    fprintf(stderr, "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  sprintf(result, "0%o\n", mode);

  return result;
}

char*
converter_from_letter_to_binary_format(const char* permissions)
{
  mode_t mode = convert_permissions_to_mode(permissions);
  return convert_mode_to_binary(mode);
}

char*
converter_from_letter_to_numerical_format(const char* permissions)
{
  mode_t mode = convert_permissions_to_mode(permissions);
  return convert_mode_to_octal(mode);
}
