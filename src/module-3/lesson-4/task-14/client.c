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
initialize_client(int* client_fd,
                  struct sockaddr_in* server_addr)
{
  int opt = 1;

  *client_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (*client_fd == -1)
    handle_error("socket");

  if (setsockopt(*client_fd,
                 SOL_SOCKET,
                 SO_REUSEADDR | SO_REUSEPORT,
                 &opt,
                 sizeof(opt)) == -1)
    handle_error("setsockopt");

  server_addr->sin_family = AF_INET;
  server_addr->sin_addr.s_addr =
    htonl(0x7f000001); // 127.0.0.1
  server_addr->sin_port = htons(PORT);
}

void
register_client(int client_fd,
                int client_id,
                struct sockaddr_in* server_addr,
                socklen_t server_addrlen)
{
  char buffer[MAX_LEN];

  if (sendto(client_fd,
             &client_id,
             sizeof(int),
             MSG_CONFIRM,
             (struct sockaddr*)server_addr,
             server_addrlen) == -1)
    handle_error("sendto");

  int n = recvfrom(client_fd,
                   buffer,
                   MAX_LEN,
                   MSG_WAITALL,
                   (struct sockaddr*)server_addr,
                   &server_addrlen);
  if (n == -1)
    handle_error("recvfrom");

  int id;
  memcpy(&id, buffer, sizeof(int));

  if (id == 0) {
    puts("User with this id already exists");
    close(client_fd);
    exit(EXIT_FAILURE);
  } else {
    puts("You have successfully registered");
  }
}

void
send_message(int client_fd,
             int client_id,
             struct sockaddr_in* server_addr,
             socklen_t server_addrlen)
{
  char buffer[MAX_LEN];

  while (true) {
    char* message = client_menu();

    memset(buffer, '\0', MAX_LEN);
    memcpy(buffer, &client_id, sizeof(int));
    strncpy(buffer + sizeof(int),
            message,
            MAX_LEN - sizeof(int) - 1);

    if (sendto(client_fd,
               buffer,
               sizeof(int) + strlen(buffer + sizeof(int)),
               MSG_CONFIRM,
               (struct sockaddr*)server_addr,
               server_addrlen) == -1)
      handle_error("sendto");

    if (strcmp(message, "q") == 0) {
      free(message);
      puts("\nThe client has successfully shut down");
      break;
    }

    free(message);
    memset(buffer, '\0', MAX_LEN);

    output_wrapped_title("Output", 30, '-');

    int n = recvfrom(client_fd,
                     buffer,
                     MAX_LEN,
                     MSG_WAITALL,
                     (struct sockaddr*)server_addr,
                     &server_addrlen);
    if (n == -1)
      handle_error("recvfrom");

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

  int client_fd;
  struct sockaddr_in server_addr;
  socklen_t server_addrlen = sizeof(server_addr);

  initialize_client(&client_fd, &server_addr);
  register_client(
    client_fd, client_id, &server_addr, server_addrlen);
  send_message(
    client_fd, client_id, &server_addr, server_addrlen);

  close(client_fd);
  return 0;
}
