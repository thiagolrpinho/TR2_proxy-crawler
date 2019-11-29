#include "estrutura_helper.hpp"

#define GET_STRING_SIZE (4);
#define POST_STRING_SIZE (5);
#define HTTP_1_STRING_SIZE (6);


estrutura_request request_parser( string request )
{ 
  estrutura_request analisador_request;
  string url, host, full_path, file_path;
  size_t coordenada_indice_get, coordenada_indice_http, coordenada_indice_host, coordenada_indice_fim_linha_host;
 
  //Printa o request no terminal
  cout << "Request recebida: " << endl;
  cout << request << endl;

  coordenada_indice_get = request.find("GET", 0);

  if ( coordenada_indice_get == string::npos )
  {
    coordenada_indice_get = request.find("POST", 0);
    if(coordenada_indice_get != string::npos) coordenada_indice_get += POST_STRING_SIZE;
  } else {
    coordenada_indice_get += GET_STRING_SIZE;
  }

  coordenada_indice_http = request.find(" HTTP/1", 0 );
  if( coordenada_indice_http != string::npos && coordenada_indice_get != string::npos)
  {
    url = request.substr(coordenada_indice_get, coordenada_indice_http - coordenada_indice_get);
  }

  cout << "Url é:" << url << endl;

  coordenada_indice_host = request.find("Host:", 0 ) + HTTP_1_STRING_SIZE;
  coordenada_indice_fim_linha_host = request.find("\n", coordenada_indice_host);
  if( coordenada_indice_host != string::npos && coordenada_indice_fim_linha_host != string::npos)
  {
    host = request.substr(coordenada_indice_host, coordenada_indice_fim_linha_host - coordenada_indice_host);
  }
  cout << "Host é:" << host << endl;

// Limpando os \r 
url.erase( remove(url.begin(), url.end(), '\r'), url.end() );
host.erase( remove(host.begin(), host.end(), '\r'), host.end() );

file_path = "http://" + host + "/";

if( file_path.compare(url) == 0 )
{
  file_path = "/index.html";
} else {
  file_path = url.substr(file_path.size()-1, url.size() - file_path.size() -1  );
}

full_path = host + file_path;

strncpy(analisador_request.url, url.c_str(), url.size() );
strncpy(analisador_request.host, host.c_str(), host.size());
strncpy(analisador_request.file_path, file_path.c_str(), file_path.size());
strncpy(analisador_request.complete_path, full_path.c_str(), full_path.size());

cout << analisador_request.file_path << endl;
cout << analisador_request.complete_path << endl;

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