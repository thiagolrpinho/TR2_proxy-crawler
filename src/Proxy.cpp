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
  int server_socket, external_socket, internal_socket;
  char host_domain_url[30];
  char request_char[40960];
  char response_char[4];
  string proceed_flag, request, response, url, host;


  //Cria socket de Recepção e deixa listening
  do {
    server_socket = create_server_socket("127.0.0.1",8228);
  } while(server_socket == -1 );

  while( proceed_flag != "n") {
    //Limpa a variaveis de request/response
    memset(request_char, 0, sizeof(request_char));
    memset(response_char, 0, sizeof(response_char));

    //Limpa a variavel que guarda o método do request/response
    memset(host_domain_url, 0, sizeof host_domain_url);

    cout << "Recebendo request" << endl;
    //Aceita conexão pelo Socket de Recepção
    internal_socket = accept(server_socket, NULL, NULL);

    //Recebe o request
    recv(internal_socket, request_char, sizeof(request_char), 0);
    request = request_char;

    request_data = request_parser(request);

    //Pulando sites de redirecionamento
    if( !is_valid_host(request_data.host) ) continue;
    cout << "Host antes do destine: " << request_data.host << "!" << endl;

    destine_server = gethostbyname(  request_data.host );
    if( destine_server != NULL ) {
      cout << "Endereço ip do Host é:" << inet_ntoa( (struct in_addr) *((struct in_addr *) destine_server->h_addr_list[0])) << endl;
    } else {
      cout << "Falha ao capturar o ip de: " << request_data.host << endl;
      shutdown(internal_socket, SHUT_RDWR);
      shutdown(server_socket, SHUT_RDWR);
      break;
    }
    if( request_data.is_get ) 
    {
      cout << "Request é Get" << endl;
      if( exist_folder( request_data.complete_path ) == false )
      // Se não existir uma pasta para esse subdomínio, ele cria o subdomínio e armazena a resposta externa
      {
        cout << "Pasta não existe" << endl;
        //Cria o socket cliente como Socket de Envio, para fazer a requisição ao servidor de destino
        external_socket = create_client_socket(inet_ntoa( (struct in_addr) *((struct in_addr *) destine_server->h_addr_list[0])), 80);
        //Envia a requisição ao destino,pelo Socket de Envio, e pega a resposta
        send(external_socket, request_char, sizeof(request_char), 0);
        
        response = "";
        while( read(external_socket, &response_char, sizeof(response_char) - 1) != 0)
        {
          response += response_char;
          bzero(response_char, sizeof(response_char));
        }

        shutdown(external_socket, SHUT_RDWR);
        close(external_socket);

        if( !store_domain( request_data.complete_path, response ) ) return false;
      } else {
          cout << "Pasta existe" << endl;
          // Se já existir uma pasta criada para esse subdominio, carrega o que está salvo
          response = load_cached( request_data.complete_path );
          strncpy(response_char, response.c_str(), response.size() );
        }
      } else {
          cout << "Não é get" << endl;
        //Cria o socket cliente como Socket de Envio, para fazer a requisição ao servidor de destino
        external_socket = create_client_socket(inet_ntoa( (struct in_addr) *((struct in_addr *) destine_server->h_addr_list[0])), 80);
        //Envia a requisição ao destino,pelo Socket de Envio, e pega a resposta
        send(external_socket, request_char, sizeof(request_char), 0);
        recv(external_socket, &response_char, sizeof(response_char), 0);
        shutdown(external_socket, SHUT_RDWR);
        close(external_socket);
      }

    //Envia a mensagem pelo Socket Interno
    send(internal_socket, response_char, sizeof(response_char), 0);
    cout << "Response enviada: " << endl;
    cout << response_char << endl;

    //Encerra conexão
    shutdown(internal_socket, SHUT_RDWR);
    close(internal_socket);



    cin >> proceed_flag;
  }

  shutdown(server_socket, SHUT_RDWR);
  return 0;
}