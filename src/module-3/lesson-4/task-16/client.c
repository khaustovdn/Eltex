#include <fcntl.h>
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
  fputs("Enter message to send\n\tc. Calculator\n\tsf. "
        "Send File\n\tq. Quit\nInput: ",
        stdout);
  return input_string();
}

InputResult
file_editor_menu()
{
  output_wrapped_title("File Editor Menu", 50, '-');
  fputs("Appending a new value to a file\nInput: ", stdout);
  return input_double();
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

int
handle_message(int sock_fd,
               int client_id,
               const char* message)
{
  char buffer[MAX_LEN];
  bzero(buffer, MAX_LEN);
  memcpy(buffer, &client_id, sizeof(int));
  strncpy(buffer + sizeof(int),
          message,
          MAX_LEN - sizeof(int) - 1);

  size_t message_length = strlen(buffer + sizeof(int));
  if (send(
        sock_fd, buffer, sizeof(int) + message_length, 0) ==
      -1)
    handle_error("send");

  bzero(buffer, MAX_LEN);
  output_wrapped_title("Output", 30, '-');

  int n = recv(sock_fd, buffer, sizeof(buffer), 0);
  if (n <= 0) {
    if (n == 0) {
      puts("Server closed connection");
    } else {
      handle_error("recv");
    }
    close(sock_fd);
    return -1;
  }

  if (strcmp(message, "q") == 0 && n == sizeof(int)) {
    puts("Logging out...");
    close(sock_fd);
    return -1;
  }

  int id;
  memcpy(&id, buffer, sizeof(int));
  printf("Server: %s\n", buffer + sizeof(int));

  if (strcmp(buffer + sizeof(int), "Invalid action") == 0) {
    return 0;
  }
  return 1;
}

void
handle_client(int sock_fd, int client_id)
{
  int is_action = -1;

  while (true) {
    char* message;

    if (is_action >= 0 && is_action <= 3) {
      fputs("Input: ", stdout);
      message = input_string();
    } else
      message = client_menu();

    if (strncmp(message, "sf", MAX_LEN) == 0) {
      strncpy(message, "calculator", MAX_LEN - 1);
      message[MAX_LEN - 1] = '\0';
      int fd = open("file.bin", O_RDWR | O_CREAT, 0666);
      if (fd == -1) {
        handle_error("open");
        free(message);
        return;
      }

      for (int i = 0; i < 2; i++) {
        InputResult result = file_editor_menu();
        if (!result.success) {
          close(fd);
          free(message);
          return;
        }
        if (write(fd, result.value, sizeof(double)) == -1) {
          handle_error("write");
          close(fd);
          free(message);
          return;
        }
      }
      lseek(fd, 0, SEEK_SET);
      if (handle_message(sock_fd, client_id, message) ==
          -1) {
        close(fd);
        free(message);
        return;
      }

      free(message);
      fputs("Input: ", stdout);
      char* message = input_string();
      if (handle_message(sock_fd, client_id, message) ==
          -1) {
        close(fd);
        free(message);
        free(message);
        return;
      }

      double result;
      while (read(fd, &result, sizeof(result)) > 0) {
        snprintf(message, MAX_LEN, "%lf", result);
        printf("From the file entered: %lf\n", result);
        if (handle_message(sock_fd, client_id, message) ==
            -1) {
          close(fd);
          free(message);
          return;
        }
      }
      close(fd);
      continue;
    } else if (strncmp(message, "c", MAX_LEN) == 0) {
      strncpy(message, "calculator", MAX_LEN - 1);
      message[MAX_LEN - 1] = '\0';
      is_action = 0;
    }

    if (is_action >= 0)
      is_action++;

    int ms = handle_message(sock_fd, client_id, message);
    if (ms == -1) {
      free(message);
      return;
    } else if (ms == 0) {
      is_action = -1;
    }

    free(message);
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
  handle_client(sock_fd, client_id);

  close(sock_fd);
  return 0;
}
