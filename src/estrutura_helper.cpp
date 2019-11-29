#include "estrutura_helper.hpp"




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



string create_get_request( const string original_url )
{
  string url;
  url = "GET " + original_url + " \r\n";


  return url;
}

bool create_folder(string nome_pasta)
{
  int creation_result;
  string nome_pasta_com_cached = CACHED_FILES_FOLDER + nome_pasta;
  if ((creation_result = mkdir( nome_pasta_com_cached.c_str(), S_IRUSR | S_IWUSR | S_IXUSR)) != 0)
  {
    if (creation_result != 0 && errno != EEXIST)
    {
      cout << "mkdir error: " << strerror(errno) << endl;
      return false;
    }
  }
  return true;
}

bool exist_folder(const string nome_pasta )
{
  bool pasta_existe = false;
  struct stat st = {0};
  string nome_pasta_com_cached = CACHED_FILES_FOLDER + nome_pasta;

  if (stat(nome_pasta_com_cached.c_str(), &st) != -1) pasta_existe = true;

  return pasta_existe ;
}

bool store_domain(string complete_path)
{ 
  bool succesfull_stored = true;
  string extracted_subdomain, acummulated_sub_domain = "", delimiter = "/";
  size_t first_ocurrence, second_ocurrence;
  first_ocurrence = 0;
  second_ocurrence = complete_path.find(delimiter);

  while(second_ocurrence != string::npos and first_ocurrence != string::npos )
  { 
    extracted_subdomain =  complete_path.substr(first_ocurrence, second_ocurrence - first_ocurrence + 1 );
    acummulated_sub_domain = acummulated_sub_domain + extracted_subdomain;
    cout << acummulated_sub_domain <<  "!Abaco!" << endl;
     // Primeiro verificamos se existe a pasta com esse caminho acumulado
    if( exist_folder(acummulated_sub_domain) == false)
    {
      // Se não existir, criamos a pasta
      if (create_folder(acummulated_sub_domain) == false)succesfull_stored = false;
    } 
    // Se o segundo indice já estiver no final então não há mais o que procurar
    if ( second_ocurrence == complete_path.size() - 1 )
    {
      first_ocurrence = string::npos;
    } else {
      // Caso não esteja, continua buscando
      first_ocurrence = second_ocurrence + 1;
    }
    second_ocurrence = complete_path.find(delimiter, first_ocurrence + 1);
    // Caso não haja mais delimitadores, devemos extrair somente até o final
    if (second_ocurrence == string::npos)
    {
      second_ocurrence = complete_path.size() - 1;
    }
  } 

  return succesfull_stored;
}
/*
if ((dir_result = mkdir(get.host, S_IRUSR | S_IWUSR | S_IXUSR)) != 0)
    {
      if (dir_result != 0 && errno != EEXIST)
      {
        printf("mkdir error: %s", strerror(errno));
      }
    }
    find_subdir(get);
    strcat(path, get.host);
    strcat(path, get.file_path);
    index = fopen(path, "w");

    while (read(sock, buffer, BUFFER_SIZE - 1) != 0){
      fputs(buffer,index);
      bzero(buffer, BUFFER_SIZE);
    }

    fclose(index);
    sendCachedFile(get.complete_path, new_socket);
    shutdown(sock, SHUT_RDWR);
    close(sock);
    printf("[Proxy] No cahced file! Downloaded and sent!");
  }
  */