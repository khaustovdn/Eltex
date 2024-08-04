#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../../../utils/utils.h"

#define PORT 8080

void
handle_error(const char* msg)
{
  perror(msg);
  exit(EXIT_FAILURE);
}

char*
client_menu()
{
  output_wrapped_title("Client Menu", 50, '-');
  fputs("Enter message to send\n\tq. Quit\nInput: ",
        stdout);
  return input_string();
}

void
initialize_client(int* sock_fd,
                  struct sockaddr_in* server_addr)
{
  *sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (*sock_fd == -1)
    handle_error("socket");
  else
    puts("Socket successfully created..");

  server_addr->sin_family = AF_INET;
  server_addr->sin_addr.s_addr =
    htonl(0x7f000001); // 127.0.0.1
  server_addr->sin_port = htons(PORT);

  if (connect(*sock_fd,
              (struct sockaddr*)server_addr,
              sizeof(*server_addr)) == -1)
    handle_error("connect");
  else
    puts("Connected to the server..");
}

void
register_client(int sock_fd, int client_id)
{
  char buffer[MAX_LEN];

  if (send(sock_fd, &client_id, sizeof(int), 0) == -1)
    handle_error("send");

  int n = recv(sock_fd, buffer, sizeof(buffer), 0);
  if (n == -1)
    handle_error("recv");

  int id;
  memcpy(&id, buffer, sizeof(int));

  if (id == 0) {
    puts("User with this id already exists");
    close(sock_fd);
    exit(EXIT_FAILURE);
  } else {
    puts("You have successfully registered");
  }
}

void
handle_message(int sock_fd, int client_id)
{
  char buffer[MAX_LEN];

  while (true) {
    char* message = client_menu();

    bzero(buffer, MAX_LEN);
    memcpy(buffer, &client_id, sizeof(int));
    strncpy(buffer + sizeof(int),
            message,
            MAX_LEN - sizeof(int) - 1);

    if (send(sock_fd,
             buffer,
             sizeof(int) + strlen(buffer + sizeof(int)),
             0) == -1) {
      handle_error("send");
    }

    bzero(buffer, MAX_LEN);

    output_wrapped_title("Output", 30, '-');

    int n = recv(sock_fd, buffer, sizeof(buffer), 0);
    if (n == -1) {
      handle_error("recv");
    } else if (n == 0) {
      printf("Server closed connection\n");
      close(sock_fd);
      return;
    }

    if (strcmp(message, "q") == 0) {
      if (n == sizeof(int)) {
        printf("Logging out...\n");
        free(message);
        close(sock_fd);
        break;
      }
    }

    free(message);

    int id;
    memcpy(&id, buffer, sizeof(int));
    printf("User %d: %s\n", id, buffer + sizeof(int));
  }
}

int
main(int argc, char* argv[])
{
  if (argc != 2) {
    puts("Usage: ./client <client_id>");
    exit(EXIT_FAILURE);
  }

  int client_id = atoi(argv[1]);
  if (client_id <= 0) {
    puts("Client ID should be a positive integer.");
    exit(EXIT_FAILURE);
  }

  int sock_fd;
  struct sockaddr_in server_addr, client_addr;

  initialize_client(&sock_fd, &server_addr);
  register_client(sock_fd, client_id);
  handle_message(sock_fd, client_id);

  close(sock_fd);
  return 0;
}
