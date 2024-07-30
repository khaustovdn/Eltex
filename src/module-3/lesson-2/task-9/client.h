#ifndef CLIENT_H_
#define CLIENT_H_

#include <unistd.h>

void
handle_error(const char* msg, int exit_code);

void
child_handler(int pipefd[]);

int
main(int argc, char* argv[]);

#endif // CLIENT_H_
