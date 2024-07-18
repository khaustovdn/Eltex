#ifndef PERMISSIONS_H_
#define PERMISSIONS_H_

#include "../../utils/utils.h"
#include <sys/types.h>

typedef InputResult (*input_action)();

typedef char* (*output_action)(mode_t mode);

char*
permissions_input_menu();

void
permissions_input(mode_t* mode);

static InputResult
permissions_input_in_letters();

static InputResult
permissions_input_in_octal();

char*
permissions_output_menu();

void
permissions_output(mode_t* mode);

#endif // PERMISSIONS_H_
