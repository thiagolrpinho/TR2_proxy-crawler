#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <arpa/inet.h>

int main() {

  //Cria Socket
  int client_socket;
  client_socket = socket(AF_INET,SOCK_STREAM,0);

  //Especifica um endereço para o Socket
  int server_ip = inet_addr("127.0.0.1");
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(8001);
  server_address.sin_addr.s_addr = server_ip;

  //Verifica conexão
  int connection_status = connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address));
  if(connection_status == -1){
    printf("Ocorreu um erro ao tentar estabalecer conexão com o socket");
  }

  //Recebe o dado do servidor
  char server_response[4096];
  char request[] = "GET / HTTP/1.1\r\n\r\n";
  send(client_socket, request, sizeof(request), 0);
  recv(client_socket, &server_response, sizeof(server_response),0);

  //Imprime a resposta do servidor
  printf("\nA resposta do servidor foi: \n %s",server_response);
  //printf("\n---%d---", server_ip);

  //Encerra conexão
  close(client_socket);

  return 0;
}