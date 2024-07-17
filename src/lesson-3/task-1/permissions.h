#ifndef PERMISSIONS_H_
#define PERMISSIONS_H_

#include "../../utils/utils.h"

typedef void (*action)(const char* permissions);

char*
permissions_menu();

void
permissions_input(const char* permissions);

void
permissions_input_in_letter_format(const char* permissions);

void
permissions_input_in_numerical_format(const char* permissions);

#endif // PERMISSIONS_H_
