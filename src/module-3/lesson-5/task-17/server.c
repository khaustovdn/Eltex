#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../../../utils/utils.h"

#define PORT 8080
#define MAX_CONNECTIONS 1024

typedef struct
{
  int id;
  struct sockaddr_in addr;
  socklen_t addrlen;
} Client;

void
handle_error(const char* msg)
{
  perror(msg);
  exit(EXIT_FAILURE);
}

void
initialize_server(int* server_fd,
                  struct sockaddr_in* server_addr)
{
  int opt = 1;

  *server_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (*server_fd == -1)
    handle_error("socket");

  if (setsockopt(*server_fd,
                 SOL_SOCKET,
                 SO_REUSEADDR | SO_REUSEPORT,
                 &opt,
                 sizeof(opt)) == -1)
    handle_error("setsockopt");

  server_addr->sin_family = AF_INET;
  server_addr->sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr->sin_port = htons(PORT);

  if (bind(*server_fd,
           (struct sockaddr*)server_addr,
           sizeof(*server_addr)) == -1)
    handle_error("bind");
}

void
handle_registration(int server_fd,
                    Client* clients,
                    int* client_count,
                    char* buffer,
                    struct sockaddr_in* client_addr,
                    socklen_t client_addrlen)
{
  int id;
  memcpy(&id, buffer, sizeof(int));

  for (int i = 0; i < *client_count; i++) {
    if (id == clients[i].id) {
      int response = 0;
      memcpy(buffer, &response, sizeof(int));
      if (sendto(server_fd,
                 buffer,
                 MAX_LEN,
                 MSG_CONFIRM,
                 (struct sockaddr*)client_addr,
                 client_addrlen) == -1)
        handle_error("sendto");
      printf("User %d: already exists\n", id);
      return;
    }
  }

  clients[*client_count].id = id;
  clients[*client_count].addr = *client_addr;
  clients[*client_count].addrlen = client_addrlen;
  (*client_count)++;

  memcpy(buffer, &id, sizeof(int));
  if (sendto(server_fd,
             buffer,
             MAX_LEN,
             MSG_CONFIRM,
             (struct sockaddr*)client_addr,
             client_addrlen) == -1)
    handle_error("sendto");

  strncpy(buffer + sizeof(int),
          "logged into the chat",
          MAX_LEN - sizeof(int) - 1);
  buffer[MAX_LEN - 1] = '\0';

  for (int i = 0; i < *client_count; i++) {
    if (clients[i].id != id) {
      if (sendto(server_fd,
                 buffer,
                 MAX_LEN,
                 MSG_CONFIRM,
                 (struct sockaddr*)&clients[i].addr,
                 clients[i].addrlen) == -1)
        handle_error("sendto");
    }
  }

  printf("User %d: has successfully registered\n", id);
}

void
handle_message(int server_fd,
               Client* clients,
               int* client_count,
               char* buffer,
               struct sockaddr_in* client_addr,
               socklen_t client_addrlen,
               int* active_client)
{
  int id;
  memcpy(&id, buffer, sizeof(int));

  if (strncmp(buffer + sizeof(int),
              "q",
              MAX_LEN - sizeof(int) - 1) == 0) {
    for (int i = 0; i < *client_count - 1; i++) {
      if (clients[i].id == id) {
        clients[i] = clients[i + 1];
      }
    }
    (*client_count)--;

    strncpy(buffer + sizeof(int),
            "logged out of the chat",
            MAX_LEN - sizeof(int) - 1);
    buffer[MAX_LEN - 1] = '\0';
    printf("User %d: logged out of the chat\n", id);
  } else {
    buffer[MAX_LEN - 1] = '\0';
    printf("User %d: %s\n", id, buffer + sizeof(int));
  }

  for (int i = 0; i < *client_count; i++) {
    if (clients[i].id != id) {
      if (sendto(server_fd,
                 buffer,
                 MAX_LEN,
                 MSG_CONFIRM,
                 (struct sockaddr*)&clients[i].addr,
                 clients[i].addrlen) == -1)
        handle_error("sendto");
    }
  }

  *active_client =
    (id == clients[0].id) ? clients[1].id : clients[0].id;
}

void
start_server()
{
  struct sockaddr_in server_addr, client_addr;
  Client clients[MAX_CONNECTIONS] = { 0 };
  int client_count = 0;
  char buffer[MAX_LEN];
  int server_fd;
  int active_client = -1;

  initialize_server(&server_fd, &server_addr);

  socklen_t client_addrlen = sizeof(client_addr);
  while (true) {
    int n = recvfrom(server_fd,
                     buffer,
                     MAX_LEN,
                     MSG_WAITALL,
                     (struct sockaddr*)&client_addr,
                     &client_addrlen);
    if (n == -1)
      handle_error("recvfrom");

    int id;
    memcpy(&id, buffer, sizeof(int));

    if (*(buffer + sizeof(int)) == '\0') {
      handle_registration(server_fd,
                          clients,
                          &client_count,
                          buffer,
                          &client_addr,
                          client_addrlen);
      if (client_count == 1) {
        active_client = id;
      }
    } else {
      if (id != active_client) {
        continue;
      }
      handle_message(server_fd,
                     clients,
                     &client_count,
                     buffer,
                     &client_addr,
                     client_addrlen,
                     &active_client);
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
