#ifndef PERMISSIONS_OUTPUT_H_
#define PERMISSIONS_OUTPUT_H_

#include "../../utils/utils.h"
#include <sys/types.h>

typedef char* (*output_action)(mode_t mode);

char*
permissions_output_menu();

void
permissions_output(mode_t* mode);

#endif // PERMISSIONS_OUTPUT_H_
