#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "converter.h"

mode_t
convert_permissions_to_mode(const char* str_mode)
{
  if (strlen(str_mode) != 9) {
    fprintf(stderr, "Error: Invalid permission format.\n");
    exit(EXIT_FAILURE);
  }

  mode_t mode = 0;

  for (int i = 0; i < strlen(str_mode); i += 3)
    mode = (mode << 3) | ((str_mode[i] == 'r') << 2) |
           ((str_mode[i + 1] == 'w') << 1) |
           (str_mode[i + 2] == 'x');

  return mode;
}

char*
convert_mode_to_bit(mode_t mode)
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
convert_mode_to_letters(mode_t mode)
{
  char* result = malloc(MAX_LEN * sizeof(char));
  if (result == NULL) {
    fprintf(stderr, "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < 9; ++i) {
    if ((mode >> (8 - i)) & 1) {
      result[i] =
        (i % 3 == 0) ? 'r' : (i % 3 == 1) ? 'w' : 'x';
    } else {
      result[i] = '-';
    }
  }
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
convert_from_letter_to_bit_format(const char* str_mode)
{
  if (strlen(str_mode) != 9) {
    fprintf(stderr, "Error: Invalid permission format.\n");
    exit(EXIT_FAILURE);
  }

  mode_t mode = convert_permissions_to_mode(str_mode);
  return convert_mode_to_bit(mode);
}

char*
convert_from_letter_to_octal_format(const char* str_mode)
{
  if (strlen(str_mode) != 9) {
    fprintf(stderr, "Error: Invalid permission format.\n");
    exit(EXIT_FAILURE);
  }

  mode_t mode = convert_permissions_to_mode(str_mode);
  return convert_mode_to_octal(mode);
}
