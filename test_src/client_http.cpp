#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#include <string.h>
#include <strings.h>

#include <catch.hpp>


int main(){

  //Cria Socket
  int client_socket = socket(AF_INET,SOCK_STREAM,0);
  struct sockaddr_in client_address;
  //Especifica o endereço e a porta para o Client Socket
  client_address.sin_family = AF_INET;
  client_address.sin_port = htons(8228);
  client_address.sin_addr.s_addr = inet_addr("127.0.0.1");

  //Connecta/Verifica conexão
  int connection_status = connect(client_socket, (struct sockaddr *) &client_address, sizeof(client_address));
  if(connection_status == -1){
    printf("Ocorreu um erro ao tentar estabalecer conexão com o socket");
  }

  //Request
  string request = R"GET http://brasilia.deboa.com/ HTTP/1.1
                        Host: brasilia.deboa.com
                        User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:70.0) Gecko/20100101 Firefox/70.0
                        Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
                        Accept-Language: en-US,en;q=0.5
                        Accept-Encoding: gzip, deflate
                        Connection: keep-alive
                        Cookie: __cfduid=dec1a89f1a5f26d6f650e2e814a09e8d61574859270; _ga=GA1.2.1109585577.1574860689; nav44561=a34c214f46789837600ca870309_332; _fbp=fb.1.1574860691855.1385721276; __gads=ID=e65e2e1a5e78073f:T=1574860692:S=ALNI_MatQcTrCgTxp3pw6hKegpynFpliSw
                        Upgrade-Insecure-Requests: 1";

  char request_char[request.size()];
  strncpy(request_char, request.c_str(), request.size());

  //Envia Request
  send(client_socket, request_char, sizeof(request), 0);

  return 0;
}