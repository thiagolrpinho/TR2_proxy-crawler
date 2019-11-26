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
  printf("\nHost: %s \n", host_url->h_addr);
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
  struct sockaddr_in server_address;
  //Especifica o endereço e a porta para o Server Socket
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);
  server_address.sin_addr.s_addr = inet_addr(address);
  //Associa o IP e a porta ao Server Socket
  bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
  //Fica escutando o Server Socket
  listen(server_socket, 3);

  return server_socket;
}

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
  int server_socket = create_server_socket("127.0.0.1",8001);

  char method[7];
  char request[40960];
  int internal_socket;
  int external_socket;
  while(1) {
    //Limpa a variavel que guarda o método do request/response
    memset(method, 0, sizeof method);

    //Aceita conexão pelo Socket de Recepção
    internal_socket = accept(server_socket, NULL, NULL);
    //Recebe o request
    recv(internal_socket, request, sizeof(request), 0);


    //Cria o socket cliente como Socket de Envio, para fazer a requisição ao servidor de destino
    external_socket = create_client_socket("127.0.0.1", 8002);



    //Printa o request no terminal
    printf("Request: %s \n ----------------------------------------\n",request);



    //Teste//Envia a requisição ao destino,pelo Socket de Envio, e pega a resposta
    send(external_socket, request, sizeof(request), 0);
    recv(external_socket, &request, sizeof(request), 0);
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
    }*/


    //Envia a mensagem pelo Socket Receptor
    send(internal_socket, request, sizeof(request), 0);
    printf("Response: %s \n ----------------------------------------\n",request);

    //Encerra conexão
    close(internal_socket);

  }
  /* Free memory allocated to the pattern buffer by regcomp() */
  regfree(&connect_regex);
  return 0;
}