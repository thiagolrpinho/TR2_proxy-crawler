#include "estrutura_helper.hpp"




estrutura_request request_parser( string request )
{ 
  estrutura_request analisador_request;
  string url, host;
  size_t coordenada_indice_get, coordenada_indice_http, coordenada_indice_host, coordenada_indice_fim_linha_host;
  memset(analisador_request.host, 0, sizeof(analisador_request.host));
  memset(analisador_request.url, 0, sizeof(analisador_request.url));

  //Printa o request no terminal
  cout << "Request recebida: " << endl;
  cout << request << endl;

  coordenada_indice_get = request.find("GET", 0);
  cout << coordenada_indice_get << endl;
  if ( coordenada_indice_get == string::npos )
  {
    coordenada_indice_get = request.find("POST", 0);
    if(coordenada_indice_get != string::npos) coordenada_indice_get += 5;
  } else {
    coordenada_indice_get += 4;
  }
  cout << coordenada_indice_get << endl;

  coordenada_indice_http = request.find(" HTTP/1", 0 );
  cout << coordenada_indice_http << endl;
  if( coordenada_indice_http != string::npos && coordenada_indice_get != string::npos)
  {
    url = request.substr(coordenada_indice_get, coordenada_indice_http - coordenada_indice_get);
  }

  cout << "Url é:" << url << endl;

  coordenada_indice_host = request.find("Host:", 0 ) + 6;
  coordenada_indice_fim_linha_host = request.find("\n", coordenada_indice_host);
  cout << coordenada_indice_fim_linha_host << " e " << coordenada_indice_host << endl;
  if( coordenada_indice_host != string::npos && coordenada_indice_fim_linha_host != string::npos)
  {
    host = request.substr(coordenada_indice_host, coordenada_indice_fim_linha_host - coordenada_indice_host);
  }
  cout << "Host é:" << host << endl;
url.erase( remove(url.begin(), url.end(), '\r'), url.end() );
host.erase( remove(host.begin(), host.end(), '\r'), host.end() );

strncpy(analisador_request.url, url.c_str(), url.size() );
strncpy(analisador_request.host, host.c_str(), host.size());

return analisador_request;
}


bool is_valid_host(const string host )
{ 
  bool site_valid = true;
  if( host == "detectportal.firefox.com" ) site_valid = false;
  if( host == "g.symcd.com") site_valid = false;
  if( host == "sr.symcd.com") site_valid = false;
  if( host == "ocsp.digicert.com") site_valid = false;

  return site_valid;
}