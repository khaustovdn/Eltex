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
  int conn_fd;
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

  *server_fd = socket(AF_INET, SOCK_STREAM, 0);
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

  if ((listen(*server_fd, 5)) == -1)
    handle_error("listen");
  else
    puts("Server listening..");
}

void
handle_registration(int server_fd,
                    Client* clients,
                    int* client_count,
                    char* buffer)
{
  int id;
  memcpy(&id, buffer, sizeof(int));
  printf("Attempting to register user with ID: %d\n", id);

  for (int i = 0; i < *client_count; i++) {
    if (id == clients[i].id) {
      int response = 0;
      memcpy(buffer, &response, sizeof(int));
      if (send(server_fd, buffer, MAX_LEN, 0) == -1)
        handle_error("send");
      printf("User %d: already exists\n", id);
      return;
    }
  }

  printf("New connection accepted. Connection FD: %d\n",
         server_fd);
  if (*client_count < MAX_CONNECTIONS) {
    clients[*client_count].id = id;
    clients[*client_count].conn_fd = server_fd;
    (*client_count)++;

    printf("Client count updated. Current number of "
           "clients: %d\n",
           *client_count);
  } else {
    printf("Max clients reached. Connection rejected.\n");
    close(server_fd);
  }

  memcpy(buffer, &id, sizeof(int));
  if (send(server_fd, buffer, MAX_LEN, 0) == -1)
    handle_error("send");

  strncpy(buffer + sizeof(int),
          "logged into the chat",
          MAX_LEN - sizeof(int) - 1);
  buffer[MAX_LEN - 1] = '\0';

  printf("User %d: has successfully registered. Notifying "
         "other clients...\n",
         id);
  for (int i = 0; i < *client_count; i++) {
    if (clients[i].id != id) {
      if (send(clients[i].conn_fd, buffer, MAX_LEN, 0) ==
          -1)
        handle_error("send");
      printf("Sent message to User %d: %s\n",
             clients[i].id,
             buffer + sizeof(int));
    }
  }
}

void
handle_message(Client* clients,
               int* client_count,
               char* buffer,
               int sender_id)
{
  printf("Received message from User %d: %s\n",
         sender_id,
         buffer + sizeof(int));

  // Forward message to all other clients
  for (int i = 0; i < *client_count; i++) {
    if (clients[i].id != sender_id) {
      send(clients[i].conn_fd, buffer, MAX_LEN, 0);
    }
  }
}

void
start_server()
{
  struct sockaddr_in server_addr, client_addr;
  Client clients[MAX_CONNECTIONS];
  int client_count = 0;
  fd_set readfds;
  char buffer[MAX_LEN];
  int server_fd;

  // Create socket
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    handle_error("socket");
  }

  // Prepare the sockaddr_in structure
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(8080);

  // Bind
  if (bind(server_fd,
           (struct sockaddr*)&server_addr,
           sizeof(server_addr)) < 0) {
    handle_error("bind");
  }

  // Listen
  listen(server_fd, 3);

  socklen_t client_addrlen = sizeof(client_addr);

  while (1) {
    FD_ZERO(&readfds);
    FD_SET(server_fd, &readfds);
    int max_sd = server_fd;

    // Add client sockets to set
    for (int i = 0; i < client_count; i++) {
      FD_SET(clients[i].conn_fd, &readfds);
      if (clients[i].conn_fd > max_sd) {
        max_sd = clients[i].conn_fd;
      }
    }

    // Wait for activity on one of the sockets
    if (select(max_sd + 1, &readfds, NULL, NULL, NULL) <
        0) {
      handle_error("select error");
    }

    // Check if there is a new connection
    if (FD_ISSET(server_fd, &readfds)) {
      int conn_fd = accept(server_fd,
                           (struct sockaddr*)&client_addr,
                           &client_addrlen);
      if (conn_fd < 0) {
        handle_error("accept");
      }
      recv(conn_fd,
           buffer,
           MAX_LEN,
           0); // Receive ID from the new client
      handle_registration(
        conn_fd, clients, &client_count, buffer);
    }

    // Check for messages from existing clients
    for (int i = 0; i < client_count; i++) {
      if (FD_ISSET(clients[i].conn_fd, &readfds)) {
        int n =
          recv(clients[i].conn_fd, buffer, MAX_LEN, 0);
        if (n <= 0) { // Client disconnected or error
          close(clients[i].conn_fd);
          clients[i] =
            clients[--client_count]; // Remove client
          printf("Client disconnected. Current number of "
                 "clients: %d\n",
                 client_count);
        } else {
          handle_message(
            clients, &client_count, buffer, clients[i].id);
        }
      }
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
