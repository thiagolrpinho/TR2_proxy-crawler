#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

int main() {

  char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";
  //Caso de teste no terminal, apenas TCP, sem utilizar o protocolo HTTP
  //char server_message[256] = "Hello, you reached the Server!";
  //strcat(http_header, server_message);

  //Abre arquivo
  FILE *html_data;
  html_data = fopen("index.html", "r");

  //Lê o conteúdo do arquivo
  char response_data[1024];
  fgets(response_data, 1024, html_data);

  //Concatena a resposta no http_header
  strcat(http_header, response_data);

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

  listen(server_socket, 3);


  char request[1024];
  int client_socket;
  //Deixa o servidor escutando
  while(1) {
    client_socket = accept(server_socket, NULL, NULL);
    //Recebe o request
    recv(client_socket, request, sizeof(request), 0);
    //Envia a mensagem
    send(client_socket, http_header, sizeof(http_header), 0);

    printf("%s \n ----------------------------------------\n",request);
    //Encerra conexão
    close(client_socket);

  }


  return 0;
}