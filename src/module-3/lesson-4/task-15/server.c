#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#include "../../../utils/utils.h"

#define PORT 8080

typedef struct
{
  int id;
  int fd;
} Client;

void
handle_error(const char* msg)
{
  perror(msg);
  exit(EXIT_FAILURE);
}

void
initialize_server(int* sock_fd,
                  struct sockaddr_in* server_addr)
{
  *sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (*sock_fd == -1)
    handle_error("socket");
  else
    puts("Socket successfully created..");

  bzero(server_addr, sizeof(*server_addr));

  memset(server_addr, 0, sizeof(*server_addr));
  server_addr->sin_family = AF_INET;
  server_addr->sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr->sin_port = htons(PORT);

  if (bind(*sock_fd,
           (struct sockaddr*)server_addr,
           sizeof(*server_addr)) == -1)
    handle_error("bind");
  else
    puts("Socket successfully binded..");

  if ((listen(*sock_fd, 5)) == -1)
    handle_error("listen");
  else
    puts("Server listening..");
}

int
handle_message(Client client, char* buffer, int n)
{
  if (strncmp(buffer + sizeof(int), "q", n - sizeof(int)) ==
      0) {
    printf("Closed connection for user %d with fd %d\n",
           client.id,
           client.fd);
    bzero(buffer, MAX_LEN);
    if (send(client.fd, &client.id, sizeof(int), 0) == -1)
      handle_error("send");
    return -1;
  } else {
    printf(
      "User %d: %s\n", client.id, buffer + sizeof(int));
  }

  if (send(client.fd, buffer, n + 1, 0) == -1)
    handle_error("send");
  return 0;
}

void
handle_registration(int conn_fd,
                    Client* client,
                    char* buffer)
{
  memcpy(&client->id, buffer, sizeof(int));
  client->fd = conn_fd;

  if (send(
        client->fd, &client->id, sizeof(client->id), 0) ==
      -1)
    handle_error("send");

  printf("Client registered with fd: %d\n", conn_fd);
}

void
handle_client(int conn_fd)
{
  Client client;
  char buffer[MAX_LEN];

  for (;;) {
    memset(buffer, 0, MAX_LEN);
    int n = recv(conn_fd, buffer, sizeof(buffer), 0);
    if (n == -1) {
      close(conn_fd);
      return;
    }

    if (n == sizeof(int)) {
      handle_registration(conn_fd, &client, buffer);
    } else {
      if (handle_message(client, buffer, n) == -1) {
        close(client.fd);
        break;
      }
    }
  }
}

void
start_server()
{
  struct sockaddr_in server_addr;
  int sock_fd;

  initialize_server(&sock_fd, &server_addr);

  int conn_fd = accept(sock_fd, NULL, NULL);
  if (conn_fd == -1)
    handle_error("accept");

  printf("Server accepted a client...\n");
  handle_client(conn_fd);

  close(sock_fd);
  puts("The server has successfully shut down");
}

int
main()
{
  start_server();
  return 0;
}
