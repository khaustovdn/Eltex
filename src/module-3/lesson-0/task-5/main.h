#ifndef MAIN_H_
#define MAIN_H_

#include "unistd.h"

void
remove_spaces(char* str);

void
listener(int sig);

void
child_handler();

void
parent_handler(pid_t pid);

char*
file_editor_menu();

int
main(int argc, char* argv[]);

#endif // MAIN_H_
