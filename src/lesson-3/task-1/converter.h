#ifndef CONVERTER_H_
#define CONVERTER_H_

#include "../../utils/utils.h"
#include <sys/types.h>

mode_t
convert_permissions_to_mode(const char* str_mode);

char*
convert_mode_to_bit(mode_t mode);

char*
convert_mode_to_letters(mode_t mode);

char*
convert_mode_to_octal(mode_t mode);

char*
convert_from_letter_to_bit_format(const char* mode);

char*
convert_from_letter_to_octal_format(const char* mode);

#endif // CONVERTER_H_
