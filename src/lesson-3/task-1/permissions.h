#ifndef PERMISSIONS_H_
#define PERMISSIONS_H_

#include "../../utils/utils.h"

typedef void (*action)(const char* permissions);

char*
permissions_input_menu();

void
permissions_input(const char* permissions);

static void
permissions_input_in_letter_format(const char* permissions);

static void
permissions_input_in_numeric_format(
  const char* permissions);

char*
permissions_output_menu();

void
permissions_output(const char* permissions);

static void
permissions_output_in_letter_format(const char* permissions);

static void
permissions_output_in_numeric_format(const char* permissions);

static void
permissions_output_in_bit_format(
  const char* permissions);

#endif // PERMISSIONS_H_
