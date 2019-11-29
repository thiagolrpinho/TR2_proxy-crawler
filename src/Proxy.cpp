#include <stdio.h>
#include <stdlib.h>


#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "socket_handler.hpp"
#include "estrutura_helper.hpp"


int main() {

  hostent *destine_server;
  estrutura_request request_data;
  char host_char[30];
  int server_socket, external_socket, internal_socket;
  char host_domain_url[30];
  char request_char[40960];
  char response_char[40960];
  const char *host_name_temporary;
  std::string proceed_flag, request, response, url, host;

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

    request_data = request_parser(request);

    //Pulando sites de redirecionamento
    if( request_data.host == "detectportal.firefox.com" ) continue;

    destine_server = gethostbyname(  request_data.host );
    if( destine_server != NULL ) {
      std::cout << "Endereço ip do Host é:" << inet_ntoa( (struct in_addr) *((struct in_addr *) destine_server->h_addr_list[0])) << std::endl;
    } else {
      std::cout << "Falha ao capturar o ip de: " << request_data.host << std::endl;
      shutdown(internal_socket, SHUT_RDWR);
      shutdown(server_socket, SHUT_RDWR);
      break;
    }

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