#include <netinet/in.h>
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
start_client(int client_id)
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
  server_addr.sin_addr.s_addr =
    htonl(0x7f000001); // 127.0.0.1
  server_addr.sin_port = htons(PORT);

  socklen_t server_addrlen = sizeof(server_addr);
  sendto(client_fd,
         &client_id,
         sizeof(int),
         MSG_CONFIRM,
         (struct sockaddr*)&server_addr,
         server_addrlen);

  int n = recvfrom(client_fd,
                   buffer,
                   MAX_LEN,
                   MSG_WAITALL,
                   (struct sockaddr*)&server_addr,
                   &server_addrlen);
  int id = 0;
  memcpy(&id, buffer, sizeof(int));

  if (id == 0) {
    puts("User with this id already exists");
    close(client_fd);
    exit(EXIT_FAILURE);
  } else {
    puts("You have successfully registered");
  }

  while (true) {
    char* action_choice = client_menu();
    if (strcmp(action_choice, "q") == 0) {
      free(action_choice);
      puts("\nThe client has successfully shut down");
      break;
    }

    memset(buffer, 0, MAX_LEN);
    memcpy(buffer, &client_id, sizeof(int));
    strncpy(buffer + sizeof(int),
            action_choice,
            MAX_LEN - sizeof(int) - 1);
    sendto(client_fd,
           buffer,
           sizeof(int) + sizeof(action_choice),
           MSG_CONFIRM,
           (struct sockaddr*)&server_addr,
           server_addrlen);

    free(action_choice);
  }
  close(client_fd);
}

int
main(int argc, char* argv[])
{
  if (argc != 2 || !is_unsigned(argv[1]) ||
      atoi(argv[1]) == 0) {
    puts("Input the client ID");
    exit(EXIT_FAILURE);
  }
  int client_id = atoi(argv[1]);
  start_client(client_id);
  return 0;
}
