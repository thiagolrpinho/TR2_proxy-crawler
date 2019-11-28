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

#include <regex.h>
#include "socket_handler.hpp"


int main() {

  //Cria e Compila a Regex que vai ser utilizada para minerar os dados do request/response
  regex_t connect_regex;
  int connect_reti;
  int server_socket, external_socket, internal_socket;
  char msgbuf[100];
  char host_domain_url[30];
  char request[40960];
  char response[40960];
  std::string proceed_flag;
  std::string pao = "Pão é bom";

  connect_reti = regcomp(&connect_regex, "CONNECT", 0);
  if (connect_reti) { 
      printf("Could not compile regex\n");
      exit(1);
  }

  //Cria socket de Recepção e deixa listening
  do { 
    server_socket = create_server_socket("127.0.0.1",8080);
  } while(server_socket == -1 );

  while( proceed_flag != "n") {
    //Limpa a variavel que guarda o método do request/response
    memset(host_domain_url, 0, sizeof host_domain_url);

    std::cout << "Recebendo request" << std::endl;
    //Aceita conexão pelo Socket de Recepção
    internal_socket = accept(server_socket, NULL, NULL);
    //Recebe o request
    recv(internal_socket, request, sizeof(request), 0);

    //Printa o request no terminal
    std::cout << "Request recebida: " << std::endl;
    std::cout << request << std::endl;


    //Cria o socket cliente como Socket de Envio, para fazer a requisição ao servidor de destino
    external_socket = create_client_socket("104.28.13.216", 80);


    
    //Teste//Envia a requisição ao destino,pelo Socket de Envio, e pega a resposta
    send(external_socket, request, sizeof(request), 0);
    recv(external_socket, &response, sizeof(response), 0);
    std::cout << "Recebendo Response" << std::endl;
    shutdown(external_socket, SHUT_RDWR);
    close(external_socket);

    /* Executa expressão regular de método*/
    /*
    connect_reti = regexec(&connect_regex, request, 0, NULL, 0);
    if (!connect_reti) {
      printf("Método: Connect\n");

    }
    else if (connect_reti == REG_NOMATCH) {
        printf("No match");
    }
    else if (connect_reti == REG_NOMATCH) {
        printf("No match");
    }
    else if (connect_reti == REG_NOMATCH) {
        printf("No match");
    }
    else {
        regerror(connect_reti, &connect_regex, msgbuf, sizeof(msgbuf));
        printf("Regex match failed: %s\n", msgbuf);
        exit(1);
    }
    */


    //Envia a mensagem pelo Socket Receptor
    send(internal_socket, response, sizeof(response), 0);
    std::cout << "Response enviada: " << std::endl;
    std::cout << response << std::endl;

    //Encerra conexão
    shutdown(internal_socket, SHUT_RDWR);
    close(internal_socket);

    //Limpa a variaveis de request/response
    memset(request, 0, sizeof(request));
    memset(response, 0, sizeof(response));

    std::cin >> proceed_flag;
  }
  /* Free memory allocated to the pattern buffer by regcomp() */
  regfree(&connect_regex);
  shutdown(server_socket, SHUT_RDWR);
  return 0;
}