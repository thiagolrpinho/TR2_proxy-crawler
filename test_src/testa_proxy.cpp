#include "proxy_handler.hpp"


TEST_CASE(" Testa lógica do cliente ", "[HTTP_CLIENT] ")
{
    SECTION(" Envia Request ")
  {

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

    //REQUIRE(request_recebido == request_gabarito);
  }

    SECTION(" Envia Response ")
  {

    //REQUIRE(response_enviado == response_gabarito);
  }

}//TEST_CASE(" Testa lógica do servidor ", "[HTTP_SERVER]")
