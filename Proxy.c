#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <regex.h>

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

  //Cria Socket de Envio
  int sender_socket;
  sender_socket = socket(AF_INET,SOCK_STREAM,0);
  struct sockaddr_in server_sender_address;

  //Especifica um endereço para o Socket de Envio
  int server_ip = inet_addr("127.0.0.1");
  server_sender_address.sin_family = AF_INET;
  server_sender_address.sin_port = htons(8002);
  server_sender_address.sin_addr.s_addr = server_ip;

  //Cria Socket Receptor
  int server_socket;
  server_socket = socket(AF_INET, SOCK_STREAM, 0);

  //Define o endereço do Socket Receptor
  server_ip = INADDR_ANY;
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(8001);
  server_address.sin_addr.s_addr = server_ip;

  //Associa o IP e a porta ao Socket Receptor
  bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

  //Deixa o programa escutando o Socket Receptor
  listen(server_socket, 3);

  char method[7];
  char request[1024];
  int client_socket;

  //Cria e Compila a Regex que vai ser utilizada para minerar os dados do request/response
  regex_t connect_regex;
  int connect_reti;
  char msgbuf[100];
  connect_reti = regcomp(&connect_regex, "CONNECT", 0);
  if (connect_reti) {
      printf("Could not compile regex\n");
      exit(1);
  }




  //Deixa o servidor escutando
  while(1) {
    //Limpa a variavel que guarda o método do request/response
    memset(method, 0, sizeof method);
    //Aceita conexão pelo Socket de Recepção
    client_socket = accept(server_socket, NULL, NULL);
    //Recebe o request
    recv(client_socket, request, sizeof(request), 0);
    //Printa o request no terminal
    printf("Request: %s \n ----------------------------------------\n",request);

    /* Executa expressão regular de método*/
    connect_reti = regexec(&connect_regex, request, 0, NULL, 0);
    if (!connect_reti) {
      printf("Método: Connect\n");

      //Especifica um endereço para o Socket de Envio, Comentado por motivo de teste
      /*server_ip = inet_addr("127.0.0.1");
      server_sender_address.sin_addr.s_addr = server_ip;*/

      //Connecta/Verifica conexão
      int connection_status = connect(sender_socket, (struct sockaddr *) &server_sender_address, sizeof(server_sender_address));
      if(connection_status == -1){
        printf("Ocorreu um erro ao tentar estabalecer conexão com o socket");
      }
      //Teste//Envia a requisição ao destino,pelo Socket de Envio, e pega a resposta
      send(sender_socket, request, sizeof(request), 0);
      recv(sender_socket, &request, sizeof(request), 0);
      close(sender_socket);


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


    //Envia a mensagem pelo Socket Receptor
    send(client_socket, request, sizeof(request), 0);
    printf("Response: %s \n ----------------------------------------\n",request);

    /* Free memory allocated to the pattern buffer by regcomp() */
    //Encerra conexão
    close(client_socket);

  }

  regfree(&connect_regex);
  return 0;
}