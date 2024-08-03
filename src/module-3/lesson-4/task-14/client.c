#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../../../utils/utils.h"

#define PORT 8080
#define LISTEN_BACKLOG 50

void
handle_error(const char* msg)
{
  perror(msg);
  exit(EXIT_FAILURE);
}

int
main(int argc, char* argv[])
{
  struct sockaddr_in server_addr;
  char buffer[MAX_LEN];
  int opt = 1;

  int client_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (client_fd == -1)
    handle_error("socket");

  if (setsockopt(client_fd,
                 SOL_SOCKET,
                 SO_REUSEADDR | SO_REUSEPORT,
                 &opt,
                 sizeof(opt)) == -1)
    handle_error("setsockopt");

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(0x7f000001);
  server_addr.sin_port = htons(PORT);

  socklen_t server_addrlen = sizeof(server_addr);
  for (;;) {
    strncpy(buffer, "Hello, server\0", MAX_LEN);
    sendto(client_fd,
           buffer,
           MAX_LEN,
           MSG_CONFIRM,
           (struct sockaddr*)&server_addr,
           server_addrlen);
    sleep(1);
  }

  return EXIT_SUCCESS;
}
