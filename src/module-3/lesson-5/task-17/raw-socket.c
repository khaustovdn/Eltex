#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080
#define BUF_SIZE 65536

void
handle_packet(const char* buffer, int size)
{
  struct iphdr* iph = (struct iphdr*)buffer;
  struct udphdr* udph =
    (struct udphdr*)(buffer + iph->ihl * 4);

  if (size < sizeof(struct iphdr) + sizeof(struct udphdr)) {
    printf("Packet too short\n");
    return;
  }

  if (iph->saddr != htonl(0x7f000001) ||
      udph->uh_sport != htons(PORT)) {
    return;
  }

  printf("\nReceived packet: \n");
  printf("Source IP: %s\n",
         inet_ntoa(*(struct in_addr*)&iph->saddr));
  printf("Destination IP: %s\n",
         inet_ntoa(*(struct in_addr*)&iph->daddr));
  printf("Source Port: %d\n", ntohs(udph->source));
  printf("Destination Port: %d\n", ntohs(udph->dest));
  printf("Data Size: %ld bytes\n",
         size - iph->ihl * 4 - sizeof(struct udphdr));

  if (strlen(buffer + iph->ihl * 4 + sizeof(struct udphdr) +
             sizeof(int)) > 0) {
    printf("Data: %s\n",
           buffer + iph->ihl * 4 + sizeof(struct udphdr) +
             sizeof(int));
  } else {
    printf("No data in packet\n");
  }
}

int
main()
{
  int sockfd;
  char* buffer = (char*)malloc(BUF_SIZE);
  struct sockaddr_in addr;
  socklen_t addr_len = sizeof(addr);

  if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) <
      0) {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  while (1) {
    int data_size = recvfrom(sockfd,
                             buffer,
                             BUF_SIZE,
                             0,
                             (struct sockaddr*)&addr,
                             &addr_len);
    if (data_size <= 0) {
      perror("recvfrom failed");
      break;
    }

    handle_packet(buffer, data_size);
    memset(buffer, 0, BUF_SIZE);
  }

  close(sockfd);
  free(buffer);
  return 0;
}
