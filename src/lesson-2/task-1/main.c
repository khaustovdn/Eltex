#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 128

char *get_chars (int n, char symblol);

int
main (int argc, char *argv[])
{
  printf ("%sContacts%s", get_chars (12, '-'), get_chars(12, '-'));
  return EXIT_SUCCESS;
}

char *
get_chars (int n, char symbol)
{
  char *result = (char *)malloc (n * sizeof (char));
  for (int i = 0; i < n; i++) {
    *(result + i) = symbol;
  }
  return result;
}
