#ifndef CONVERTER_H_
#define CONVERTER_H_

#include "../../../utils/utils.h"
#include <sys/types.h>

mode_t
converter_permissions_to_mode(const char* str_mode);

char*
converter_mode_to_bit(mode_t mode);

char*
converter_mode_to_letters(mode_t mode);

char*
converter_mode_to_octal(mode_t mode);

bool
converter_is_letters(const char* str_mode);

bool
converter_is_octal(const char* str_mode);

#endif // CONVERTER_H_
