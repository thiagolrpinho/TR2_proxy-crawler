#include "proxy_handler.hpp"


TEST_CASE(" Testa lógica do cliente ", "[HTTP_CLIENT] ")
{
    SECTION(" Envia Request ")
  {
    //Criando cenario de teste


    //REQUIRE(request_enviado == request_gabarito);
  }

    SECTION(" Recebe Response ")
  {

    //REQUIRE(response_recebido == response_gabarito);
  }

}//TEST_CASE(" Testa lógica do cliente ", "[HTTP_CLIENT]")

TEST_CASE(" Testa lógica do servidor ", "[HTTP_SERVER]")
{
    SECTION(" Recebe Request ")
  {
    ///////Criando cenario de teste///////
    int server_socket, internal_socket;
    server_socket = create_client_socket("127.0.0.1",int 8228);
    internal_socket = accept(server_socket, NULL, NULL);
    //////////////////////////////////////

    //Criando gabarito
    string request_gabarito = R"GET http://brasilia.deboa.com/ HTTP/1.1
                        Host: brasilia.deboa.com
                        User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:70.0) Gecko/20100101 Firefox/70.0
                        Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
                        Accept-Language: en-US,en;q=0.5
                        Accept-Encoding: gzip, deflate
                        Connection: keep-alive
                        Cookie: __cfduid=dec1a89f1a5f26d6f650e2e814a09e8d61574859270; _ga=GA1.2.1109585577.1574860689; nav44561=a34c214f46789837600ca870309_332; _fbp=fb.1.1574860691855.1385721276; __gads=ID=e65e2e1a5e78073f:T=1574860692:S=ALNI_MatQcTrCgTxp3pw6hKegpynFpliSw
                        Upgrade-Insecure-Requests: 1";

    //Testando a função
    request_recebida = recv_request(server_socket, internal_socket);
    REQUIRE(request_recebida == request_gabarito);

    ///////Desfazendo cenario de teste///////
    shutdown(server_socket, SHUT_RDWR);
    shutdown(internal_socket, SHUT_RDWR);
    //////////////////////////////////////

  }

    SECTION(" Envia Response ")
  {

    //REQUIRE(response_enviado == response_gabarito);
  }

}//TEST_CASE(" Testa lógica do servidor ", "[HTTP_SERVER]")
