#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netdb.h>

#include <netinet/in.h>
#include <arpa/inet.h>

int main() {

  char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";


  //Cria Socket
  int server_socket;
  server_socket = socket(AF_INET, SOCK_STREAM, 0);

  //Define o endereço do Socket
  int server_ip = INADDR_ANY;
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(8001);
  server_address.sin_addr.s_addr = server_ip;

  //Associa o IP e a porta ao socket
  bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

  listen(server_socket, 5);

  char host_addr[15];
  int i, j;
  char request[1024];
  int client_socket;
  //Deixa o servidor escutando
  while(1) {
    client_socket = accept(server_socket, NULL, NULL);
    //Recebe o request
    recv(client_socket, request, sizeof(request), 0);
    i = 0;
    while(1){
      if(request[i] == ":" && request[i-1] == "t" && request[i-2] == "s"){
        j = 0;
        while(request[i] != "\n"){
          host_addr[j] = request[i];
        }
        break;
      }
    }

    //Envia a mensagem
    send(client_socket, http_header, sizeof(http_header), 0);
    printf("%s \n ----------------------------------------\n",request);
    printf("%s \n ----------------------------------------\n",host_addr);
    //Encerra conexão
    close(client_socket);
  }


  return 0;
}