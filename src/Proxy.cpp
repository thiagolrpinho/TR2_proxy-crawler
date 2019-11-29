#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <string>
#include <iostream>

#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "socket_handler.hpp"


int main() {

  hostent *destine_server;
  char host_char[30];
  int server_socket, external_socket, internal_socket;
  char host_domain_url[30];
  char request_char[40960];
  char response_char[40960];
  std::string proceed_flag, request, response, url, host;
  size_t coordenada_indice_get, coordenada_indice_http, coordenada_indice_host, coordenada_indice_fim_linha_host;

  //Cria socket de Recepção e deixa listening
  do {
    server_socket = create_server_socket("127.0.0.1",8228);
  } while(server_socket == -1 );

  while( proceed_flag != "n") {
    //Limpa a variavel que guarda o método do request/response
    memset(host_domain_url, 0, sizeof host_domain_url);

    std::cout << "Recebendo request" << std::endl;
    //Aceita conexão pelo Socket de Recepção
    internal_socket = accept(server_socket, NULL, NULL);
    //Recebe o request
    recv(internal_socket, request_char, sizeof(request_char), 0);
    request = request_char;

    //Printa o request no terminal
    std::cout << "Request recebida: " << std::endl;
    std::cout << request << std::endl;

    coordenada_indice_get = request.find("GET", 0);
    std::cout << coordenada_indice_get << std::endl;
    if ( coordenada_indice_get == std::string::npos )
    {
      coordenada_indice_get = request.find("POST", 0);
      if(coordenada_indice_get != std::string::npos) coordenada_indice_get += 5;
    } else {
      coordenada_indice_get += 4;
    }
    std::cout << coordenada_indice_get << std::endl;

    coordenada_indice_http = request.find(" HTTP/1", 0 );
    std::cout << coordenada_indice_http << std::endl;
    if( coordenada_indice_http != std::string::npos && coordenada_indice_get != std::string::npos)
    {
      url = request.substr(coordenada_indice_get, coordenada_indice_http - coordenada_indice_get);
    }

    std::cout << "Url é:" << url << std::endl;

    coordenada_indice_host = request.find("Host:", 0 ) + 6;
    coordenada_indice_fim_linha_host = request.find("\n", coordenada_indice_host);
    std::cout << coordenada_indice_fim_linha_host << " e " << coordenada_indice_host << std::endl;
    if( coordenada_indice_host != std::string::npos && coordenada_indice_fim_linha_host != std::string::npos)
    {
      host = request.substr(coordenada_indice_host, coordenada_indice_fim_linha_host - coordenada_indice_host);
    }
    std::cout << "Host é:" << host << std::endl;

    //Atribuindo url à variavel char *host_char
    strcpy(host_char, "brasilia.deboa.com");


    destine_server = gethostbyname(host_char);
    std::cout << "Endereço ip do Host é:" << inet_ntoa( (struct in_addr) *((struct in_addr *) destine_server->h_addr_list[0])) << std::endl;


    //Cria o socket cliente como Socket de Envio, para fazer a requisição ao servidor de destino
    external_socket = create_client_socket(inet_ntoa( (struct in_addr) *((struct in_addr *) destine_server->h_addr_list[0])), 80);



    //Teste//Envia a requisição ao destino,pelo Socket de Envio, e pega a resposta
    send(external_socket, request_char, sizeof(request_char), 0);
    recv(external_socket, &response_char, sizeof(response_char), 0);
    std::cout << "Recebendo Response" << std::endl;
    shutdown(external_socket, SHUT_RDWR);
    close(external_socket);

    //Envia a mensagem pelo Socket Receptor
    send(internal_socket, response_char, sizeof(response_char), 0);
    std::cout << "Response enviada: " << std::endl;
    std::cout << response_char << std::endl;

    //Encerra conexão
    shutdown(internal_socket, SHUT_RDWR);
    close(internal_socket);

    //Limpa a variaveis de request/response
    memset(request_char, 0, sizeof(request_char));
    memset(response_char, 0, sizeof(response_char));

    std::cin >> proceed_flag;
  }

  shutdown(server_socket, SHUT_RDWR);
  return 0;
}