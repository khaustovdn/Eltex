#ifndef MAIN_H_
#define MAIN_H_

#include <unistd.h>

void
remove_spaces(char* str);

void
handle_error(const char* msg, int exit_code);

void
update_file(int fd, const char* id, const char* new_value);

void
parent_handler(int pipefd[]);

void
child_handler(int pipefd[]);

char*
file_editor_menu();

int
main(int argc, char* argv[]);

#endif // MAIN_H_
