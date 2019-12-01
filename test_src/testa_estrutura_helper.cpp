#include "estrutura_helper.hpp"



TEST_CASE( "Encontra termos", "[Parser]" ) 
{ 
  SECTION( "Accept-Enconde")
  {
    string request_testada = "";
    string request = R"(GET http://brasilia.deboa.com/ HTTP/1.1
    Host: brasilia.deboa.com
    User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:70.0) Gecko/20100101 Firefox/70.0
    Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
    Accept-Language: en-US,en;q=0.5
    Accept-Encoding: gzip, deflate
    Connection: keep-alive
    Cookie: __cfduid=dce0eed27599c61fb30beeb3b49899ad11575055723; nav44561=a39e141f6d01d5335869c7adf09_335; _ga=GA1.2.1523189692.1575123738; _fbp=fb.1.1575123737810.1223483772
    Upgrade-Insecure-Requests: 1
    Cache-Control: max-age=0)";

    string request_tratada_gabarito = R"(GET http://brasilia.deboa.com/ HTTP/1.1
    Host: brasilia.deboa.com
    User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:70.0) Gecko/20100101 Firefox/70.0
    Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
    Accept-Language: en-US,en;q=0.5
    Accept-Encoding: identity
    Connection: keep-alive
    Cookie: __cfduid=dce0eed27599c61fb30beeb3b49899ad11575055723; nav44561=a39e141f6d01d5335869c7adf09_335; _ga=GA1.2.1523189692.1575123738; _fbp=fb.1.1575123737810.1223483772
    Upgrade-Insecure-Requests: 1
    Cache-Control: max-age=0)";

    request_testada = set_accept_enconde_identity(request);
    
    REQUIRE( request_testada == request_tratada_gabarito ); 
  } // SECTION( "Accept-Enconde")

  SECTION( "Extrai informações header")
  {
    estrutura_request estrutura_testada;
    estrutura_request estrutura_gabarito = {"brasilia.deboa.com"
    , "http://brasilia.deboa.com/"
    , "/index.html"
    , "brasilia.deboa.com/index.html"
    , "000"
    , true 
    };

    string request = R"(GET http://brasilia.deboa.com/ HTTP/1.1
    Host: brasilia.deboa.com
    User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:70.0) Gecko/20100101 Firefox/70.0
    Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
    Accept-Language: en-US,en;q=0.5
    Accept-Encoding: gzip, deflate
    Connection: keep-alive
    Cookie: __cfduid=dce0eed27599c61fb30beeb3b49899ad11575055723; nav44561=a39e141f6d01d5335869c7adf09_335; _ga=GA1.2.1523189692.1575123738; _fbp=fb.1.1575123737810.1223483772
    Upgrade-Insecure-Requests: 1
    Cache-Control: max-age=0)";

    estrutura_testada = extract_header(request);
    
    REQUIRE( strcmp(estrutura_testada.host, estrutura_gabarito.host) == 0 ); 
    REQUIRE( strcmp(estrutura_testada.url, estrutura_gabarito.url) == 0 );
    REQUIRE( strcmp(estrutura_testada.file_path, estrutura_gabarito.file_path) == 0 ); 
    REQUIRE( strcmp(estrutura_testada.complete_path, estrutura_gabarito.complete_path) == 0 ); 
  } // SECTION( "Extrai informações header")

  SECTION("Extrai informação do header com porta na url")
  {
    estrutura_request estrutura_testada;
    estrutura_request estrutura_gabarito = {"push.services.mozilla.com:443"
    , "push.services.mozilla.com:443"
    , ""
    , ""
    , "443"
    , true 
    };

    string request = R"( CONNECT push.services.mozilla.com:443 HTTP/1.1
                        User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:70.0) Gecko/20100101 Firefox/70.0
                        Proxy-Connection: keep-alive
                        Connection: keep-alive
                        Host: push.services.mozilla.com:443
                        )";

    estrutura_testada = extract_header(request);
    
    REQUIRE( strcmp(estrutura_testada.url, estrutura_gabarito.url) == 0 );
    REQUIRE( strcmp(estrutura_testada.file_path, estrutura_gabarito.file_path) == 0 ); 
    REQUIRE( strcmp(estrutura_testada.complete_path, estrutura_gabarito.complete_path) == 0 ); 
    REQUIRE( strcmp(estrutura_testada.host, estrutura_gabarito.host) == 0 ); 
  } // SECTION( "Extrai informações header ")

} // TEST_CASE( "Encontra termos", "[Parser]" ) 