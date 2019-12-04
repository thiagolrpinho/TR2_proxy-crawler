#include "socket_handler.hpp"


int create_client_socket(char* address,int port){
  //Cria Socket
  int client_socket = socket(AF_INET,SOCK_STREAM,0);
  struct sockaddr_in client_address;
  //Especifica o endereço e a porta para o Client Socket
  client_address.sin_family = AF_INET;
  client_address.sin_port = htons(port);
  client_address.sin_addr.s_addr = inet_addr(address);


  //Tentativa de pegar o ip do servidor de destino pela url. Obs mudar o parametro para (char* url, int port)
  /*
  struct hostent *host_url;
  host_url = gethostbyname(url);
  //printf("\nHost: %s \n", inet_ntoa(*((struct in_addr *)host_url->h_addr)));
  bcopy(host_url->h_addr, &client_address.sin_addr.s_addr, host_url->h_length);
  */

  //Connecta/Verifica conexão
  int connection_status = connect(client_socket, (struct sockaddr *) &client_address, sizeof(client_address));
  if(connection_status == -1){
    printf("Ocorreu um erro ao tentar estabalecer conexão com o socket");
  }
  return client_socket;
}

int create_server_socket(char* address,int port){
  //Cria Socket
  int server_socket = socket(AF_INET,SOCK_STREAM,0);
  //int on = 1;

  struct sockaddr_in server_address;
  //Especifica o endereço e a porta para o Server Socket
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);
  server_address.sin_addr.s_addr = inet_addr(address);
  //setsockopt(server_socket, IPPROTO_TCP, TCP_NODELAY, (const char *)&on, sizeof(int));

  //Associa o IP e a porta ao Server Socket
  bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
  //Fica escutando o Server Socket
  listen(server_socket, 3);

  return server_socket;
}