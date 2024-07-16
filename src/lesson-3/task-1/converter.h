#ifndef CONVERTER_H_
#define CONVERTER_H_

#include "../../utils/utils.h"

char*
converter_to_letter_format(const char* permissions);

char*
converter_to_numerical_format(const char* permissions);

char*
converter_to_bit_format(const char* permissions);

#endif // CONVERTER_H_
