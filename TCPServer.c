#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

int main() {

  char server_message[256] = "Hello you reached the Server!";

  //Cria Socket
  int server_socket;
  server_socket = socket(AF_INET,SOCK_STREAM,0);

  //Define o endereço do Socket
  int server_ip = INADDR_ANY;
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(8228);
  server_address.sin_addr.s_addr = server_ip;

  //Associa o IP e a porta ao socket
  bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

  listen(server_socket, 0);

  int client_socket;
  client_socket = accept(server_socket, NULL, NULL);

  //Envia a mensagem
  send(client_socket, server_message, sizeof(server_message), 0);

  //Encerra conexão
  close(server_socket);

  return 0;
}