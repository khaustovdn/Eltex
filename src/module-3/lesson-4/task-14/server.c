#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../../../utils/utils.h"

#define PORT 8080
#define MAX_CONNECTIONS 1024

void
handle_error(const char* msg)
{
  perror(msg);
  exit(EXIT_FAILURE);
}

void
start_server()
{
  struct sockaddr_in server_addr, client_addr;
  int connections[MAX_CONNECTIONS] = { 0 };
  int connections_count = 0;
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
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(PORT);

  if (bind(server_fd,
           (struct sockaddr*)&server_addr,
           sizeof(server_addr)) == -1)
    handle_error("bind");

  socklen_t client_addrlen = sizeof(client_addr);
  while (true) {
    int n = recvfrom(server_fd,
                     buffer,
                     MAX_LEN,
                     MSG_WAITALL,
                     (struct sockaddr*)&client_addr,
                     &client_addrlen);
    if (n < 0)
      handle_error("recvfrom");

    int id = 0;
    memcpy(&id, buffer, sizeof(int));

    if (n == sizeof(int)) {
      bool user_exists = false;
      for (int i = 0; i < connections_count; i++) {
        if (id == connections[i]) {
          int response = 0;
          sendto(server_fd,
                 &response,
                 sizeof(response),
                 MSG_CONFIRM,
                 (struct sockaddr*)&client_addr,
                 client_addrlen);
          printf("User %d already exists\n", id);
          user_exists = true;
          break;
        }
      }
      if (!user_exists) {
        sendto(server_fd,
               &id,
               sizeof(id),
               MSG_CONFIRM,
               (struct sockaddr*)&client_addr,
               client_addrlen);
        connections[connections_count++] = id;
        printf("User %d has successfully registered\n", id);
      }
    } else {
      buffer[n] = '\0';
      printf(
        "User %d - client: %s\n", id, buffer + sizeof(int));
    }
  }
  close(server_fd);
}

int
main()
{
  start_server();
  return 0;
}
