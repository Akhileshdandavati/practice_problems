#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8888
#define BUFFER_SIZE 1024

void send_message(int client_socket, const char *message)
{
  ssize_t bytes_sent;

  bytes_sent = send(client_socket, message, strlen(message), 0);
  if (bytes_sent < 0)
  {
    perror("Error sending data to server");
    exit(1);
  }
}

void receive_message(int client_socket, char *buffer, size_t buffer_size)
{
  ssize_t bytes_received;

  bytes_received = recv(client_socket, buffer, buffer_size - 1, 0);
  if (bytes_received < 0)
  {
    perror("Error receiving data from server");
    exit(1);
  }
  buffer[bytes_received] = '\0';
}

int main()
{
  int client_socket;
  struct sockaddr_in server_address;
  char buffer[BUFFER_SIZE];

  client_socket = socket(AF_LOCAL, SOCK_STREAM, 0);  //(Domain,type,protocol)
  if (client_socket < 0)
  {
    perror("Error creating socket");
    exit(1);
  }

  server_address.sin_family = AF_LOCAL;
  server_address.sin_port = htons(SERVER_PORT);
  if (inet_pton(AF_INET, SERVER_IP, &(server_address.sin_addr)) <= 0)
  {
    perror("Invalid address/Address not supported");
    exit(1);
  }

  if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
  {
    perror("Error connecting to server");
    exit(1);
  }

  send_message(client_socket, "Registration:akhilesh password123");
  receive_message(client_socket, buffer, sizeof(buffer));
  printf("Server response: %s\n", buffer);

  send_message(client_socket, "Authentication:akhilesh password123");
  receive_message(client_socket, buffer, sizeof(buffer));
  printf("Server response: %s\n", buffer);

  send_message(client_socket, "CreateTopic:MyTopic");
  receive_message(client_socket, buffer, sizeof(buffer));
  printf("Server response: %s\n", buffer);

  close(client_socket);

  return 0;
}