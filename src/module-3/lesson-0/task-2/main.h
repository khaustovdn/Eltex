#ifndef MAIN_H_
#define MAIN_H_

#include "../../../utils/utils.h"

char**
parse_command(char* action_choice, int* arg_count);

int
main(int argc, char* argv[]);

char*
command_interpreter_menu();

#endif // MAIN_H_
