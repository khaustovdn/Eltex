#ifndef PERMISSIONS_INPUT_H_
#define PERMISSIONS_INPUT_H_

#include "../../utils/utils.h"
#include <sys/types.h>

typedef InputResult (*input_action)();

char*
permissions_input_menu();

void
permissions_input(mode_t* mode);

static InputResult
permissions_input_internal(char* prompt,
                        bool (*is_valid_input)(const char*),
                        mode_t (*convert_to_mode)(const char*));

static InputResult
permissions_input_file_name();

static InputResult
permissions_input_in_letters();

static InputResult
permissions_input_in_octal();

#endif // PERMISSIONS_INPUT_H_
