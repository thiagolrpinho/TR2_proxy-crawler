#include "estrutura_helper.hpp"




estrutura_request request_parser( std::string request )
{ 
  estrutura_request analisador_request;
  std::string url, host;
  size_t coordenada_indice_get, coordenada_indice_http, coordenada_indice_host, coordenada_indice_fim_linha_host;
  memset(analisador_request.host, 0, sizeof(analisador_request.host));
  memset(analisador_request.url, 0, sizeof(analisador_request.url));

  //Printa o request no terminal
  std::cout << "Request recebida: " << std::endl;
  std::cout << request << std::endl;

  coordenada_indice_get = request.find("GET", 0);
  std::cout << coordenada_indice_get << std::endl;
  if ( coordenada_indice_get == std::string::npos )
  {
    coordenada_indice_get = request.find("POST", 0);
    if(coordenada_indice_get != std::string::npos) coordenada_indice_get += 5;
  } else {
    coordenada_indice_get += 4;
  }
  std::cout << coordenada_indice_get << std::endl;

  coordenada_indice_http = request.find(" HTTP/1", 0 );
  std::cout << coordenada_indice_http << std::endl;
  if( coordenada_indice_http != std::string::npos && coordenada_indice_get != std::string::npos)
  {
    url = request.substr(coordenada_indice_get, coordenada_indice_http - coordenada_indice_get);
  }

  std::cout << "Url é:" << url << std::endl;

  coordenada_indice_host = request.find("Host:", 0 ) + 6;
  coordenada_indice_fim_linha_host = request.find("\n", coordenada_indice_host);
  std::cout << coordenada_indice_fim_linha_host << " e " << coordenada_indice_host << std::endl;
  if( coordenada_indice_host != std::string::npos && coordenada_indice_fim_linha_host != std::string::npos)
  {
    host = request.substr(coordenada_indice_host, coordenada_indice_fim_linha_host - coordenada_indice_host);
  }
  std::cout << "Host é:" << host << std::endl;
url.erase( std::remove(url.begin(), url.end(), '\r'), url.end() );
host.erase( std::remove(host.begin(), host.end(), '\r'), host.end() );

strncpy(analisador_request.url, url.c_str(), url.size() );
strncpy(analisador_request.host, host.c_str(), host.size());

return analisador_request;
}