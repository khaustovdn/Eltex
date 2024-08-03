#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

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
  struct sockaddr_in client_addr;
  char buffer[MAX_LEN];
  int opt = 1;

  int server_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (server_fd == -1)
    handle_error("socket");

  if (setsockopt(server_fd,
                 SOL_SOCKET,
                 SO_REUSEADDR | SO_REUSEPORT,
                 &opt,
                 sizeof(opt)) == -1)
    handle_error("setsockopt");

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(0x7f000001);
  server_addr.sin_port = htons(PORT);

  if (bind(server_fd,
           (struct sockaddr*)&server_addr,
           sizeof(server_addr)) == -1)
    handle_error("bind");

  socklen_t client_addrlen = sizeof(client_addr);
  for (;;) {
    int n = recvfrom(server_fd,
                     buffer,
                     MAX_LEN,
                     MSG_WAITALL,
                     (struct sockaddr*)&client_addr,
                     &client_addrlen);
    buffer[n] = '\0';
    printf("buffer: %s\n", buffer);
  }

  return EXIT_SUCCESS;
}
