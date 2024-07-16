#ifndef MAIN_H_
#define MAIN_H_

#include "../../utils/utils.h"

int
main(int args, char *argv[]);

char*
permissions_menu();

char*
input_permissions_menu();

char*
check_on_letter_format(const char* permissions);

char*
check_on_numerical_format(const char* permissions);

#endif // MAIN_H_
