#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <regex.h>
#include "socket_handler.h"

int main() {

  //Cria e Compila a Regex que vai ser utilizada para minerar os dados do request/response
  regex_t connect_regex;
  int connect_reti;
  char msgbuf[100];
  connect_reti = regcomp(&connect_regex, "CONNECT", 0);
  if (connect_reti) {
      printf("Could not compile regex\n");
      exit(1);
  }

  //Cria socket de Recepção e deixa listening
  int server_socket = create_server_socket("127.0.0.1",8080);

  char host_domain_url[30];
  char request[40960];
  char response[40960];
  int internal_socket;
  int external_socket;
  while(1) {
    //Limpa a variavel que guarda o método do request/response
    memset(host_domain_url, 0, sizeof host_domain_url);

    //Aceita conexão pelo Socket de Recepção
    internal_socket = accept(server_socket, NULL, NULL);
    //Recebe o request
    recv(internal_socket, request, sizeof(request), 0);

    //Printa o request no terminal
    printf("Request: %s \n ----------------------------------------\n",request);


    //Cria o socket cliente como Socket de Envio, para fazer a requisição ao servidor de destino
    external_socket = create_client_socket("104.28.13.216", 80);


    //Teste//Envia a requisição ao destino,pelo Socket de Envio, e pega a resposta
    send(external_socket, request, sizeof(request), 0);
    recv(external_socket, &response, sizeof(response), 0);
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
    printf("Response: %s \n ----------------------------------------\n",response);

    //Encerra conexão
    close(internal_socket);

    //Limpa a variaveis de request/response
    memset(request, 0, sizeof(request));
    memset(response, 0, sizeof(response));

  }
  /* Free memory allocated to the pattern buffer by regcomp() */
  regfree(&connect_regex);
  return 0;
}