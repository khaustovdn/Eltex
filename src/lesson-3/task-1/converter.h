#ifndef CONVERTER_H_
#define CONVERTER_H_

#include "../../utils/utils.h"
#include <sys/types.h>

char*
convert_mode_to_letters(mode_t mode);

char*
converter_from_letter_to_binary_format(
  const char* permissions);

char*
converter_from_letter_to_numerical_format(
  const char* permissions);

#endif // CONVERTER_H_
