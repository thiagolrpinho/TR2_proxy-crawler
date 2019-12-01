#include "estrutura_helper.hpp"


size_t find_request_coordinate( string request, estrutura_request request_header )
{
  size_t coordenada_requisicao;
  coordenada_requisicao = request.find("GET", 0);
  if ( coordenada_requisicao != string::npos ) return coordenada_requisicao + GET_STRING_SIZE;

  coordenada_requisicao = request.find("POST", 0);
  if(coordenada_requisicao != string::npos) return coordenada_requisicao + POST_STRING_SIZE;

  coordenada_requisicao = request.find("CONNECT", 0);
  if(coordenada_requisicao != string::npos) return coordenada_requisicao + CONNECT_STRING_SIZE;

  coordenada_requisicao = request.find("HEAD", 0);
  if(coordenada_requisicao != string::npos) return coordenada_requisicao + HEAD_STRING_SIZE;

  coordenada_requisicao = request.find("PUT", 0);
  if(coordenada_requisicao != string::npos) return coordenada_requisicao + PUT_STRING_SIZE;

  coordenada_requisicao = request.find("DELETE", 0);
  if(coordenada_requisicao != string::npos) return coordenada_requisicao + DELETE_STRING_SIZE;

  coordenada_requisicao = request.find("PATCH", 0);
  if(coordenada_requisicao != string::npos) return coordenada_requisicao + PATCH_STRING_SIZE;

  return string::npos;
}
estrutura_request request_parser( string request )
{ 
  estrutura_request request_header;
  string url, host, full_path, file_path, porta;
  string dominio;
  size_t coordenada_requisicao, coordenada_indice_http, coordenada_indice_host, coordenada_indice_fim_linha_host;
  size_t coordenada_porta;

  request_header.is_get = false;
  memset(request_header.host, 0, sizeof(request_header.host));
  memset(request_header.url, 0, sizeof(request_header.url));
  memset(request_header.file_path, 0, sizeof(request_header.file_path));
  memset(request_header.porta, 0, sizeof(request_header.porta));
  memset(request_header.complete_path, 0, sizeof(request_header.complete_path));

  coordenada_requisicao = request.find("GET", 0);
  if ( coordenada_requisicao != string::npos )   request_header.is_get = true;

  //Printa o request no terminal
  cout << "Request recebida: " << endl;
  cout << request << endl;

  coordenada_requisicao = find_request_coordinate(  request, request_header  );
  coordenada_indice_http = request.find(" HTTP/1", 0 );
  if( coordenada_indice_http != string::npos && coordenada_requisicao != string::npos)
  {
    url = request.substr(coordenada_requisicao, coordenada_indice_http - coordenada_requisicao);
  }

  

  coordenada_indice_host = request.find("Host:", 0 ) + HTTP_1_STRING_SIZE;
  coordenada_indice_fim_linha_host = request.find("\n", coordenada_indice_host);
  
  if( coordenada_indice_host != string::npos && coordenada_indice_fim_linha_host != string::npos)
  {
    host = request.substr(coordenada_indice_host, coordenada_indice_fim_linha_host - coordenada_indice_host);
    coordenada_porta = host.find(":");
    if( coordenada_porta != string::npos ) 
    { 
      porta = host.substr( coordenada_porta , host.size() - coordenada_porta - 1 );
      host = host.substr( 0 , coordenada_porta );
      cout << "Há porta: " << porta << endl;
    }
  }

// Limpando os \r 
url.erase( remove(url.begin(), url.end(), '\r'), url.end() );
host.erase( remove(host.begin(), host.end(), '\r'), host.end() );


dominio = "http://" + host + "/";

if( dominio.compare(url) == 0 )
{
  file_path = "/index.html";
} else {
  file_path = url.substr(dominio.size()-1, url.size() - dominio.size() + 1);
}

full_path = host + file_path;

strncpy(request_header.url, url.c_str(), url.size() );
strncpy(request_header.host, host.c_str(), host.size());
strncpy(request_header.file_path, file_path.c_str(), file_path.size());
strncpy(request_header.complete_path, full_path.c_str(), full_path.size());

cout << "Url é:" << request_header.url << endl;
cout << "Host é:" << request_header.host <<  endl;
cout << "File path: " << request_header.file_path << endl;
cout << "complete path: " << request_header.complete_path << endl;

return request_header;
}


bool is_valid_host(const string host )
{ 
  bool site_valid = true;
  if( host == "detectportal.firefox.com" ) site_valid = false;
  if( host == "g.symcd.com") site_valid = false;
  if( host == "sr.symcd.com") site_valid = false;
  if( host == "ocsp.digicert.com") site_valid = false;
  if( host == "ocsp.pki.goog") site_valid = false;
 
  return site_valid;
}



string create_get_request( const string original_url )
{
  string url;
  url = "GET " + original_url + " \r\n";

  return url;
}

bool create_folder(string caminho_relativo_pasta )
{
  int creation_result; 
  size_t coordenada_ponto;
  cout << "Creating folder: " << caminho_relativo_pasta << "!" << endl;
  
  

  string caminho_relativo_pasta_com_cached = CACHED_FILES_FOLDER + caminho_relativo_pasta;

  if ((creation_result = mkdir( caminho_relativo_pasta_com_cached.c_str(), S_IRUSR | S_IWUSR | S_IXUSR)) != 0)
  {
    if (creation_result != 0 && errno != EEXIST)
    {
      cout << "mkdir error: " << strerror(errno) << endl;
      return false;
    }
  }
  return true;
}

bool cache_file(string caminho_relativo_pasta, string dados)
{
  string nome_arquivo, caminho_relativo_pasta_com_cached = CACHED_FILES_FOLDER + caminho_relativo_pasta;
  size_t coordenada_ponto;

  //coordenada_ponto = caminho_relativo_pasta.find(".");
  //if( coordenada_ponto == string::npos )
  //{
    nome_arquivo = caminho_relativo_pasta_com_cached + "/index.html";
  //} else { 
  //  nome_arquivo = caminho_relativo_pasta_com_cached;
  //}

  cout << "Caching file inside " + caminho_relativo_pasta << endl;
  
  if( dados != "")
  {
    cout << "Caching file with name " + nome_arquivo << endl;
    ofstream file_cached;
    file_cached.open(nome_arquivo);
    file_cached << dados;
    file_cached.close();
  }
  return true;
}

string load_cached( string caminho_arquivo_com_nome )
{
  string caminho_relativo_pasta_com_cached = CACHED_FILES_FOLDER + caminho_arquivo_com_nome;
  string nome_arquivo = caminho_relativo_pasta_com_cached + "/index.html";

  ifstream infile (nome_arquivo, ios::binary );
  string dados, linha;

  if (infile.is_open()) {
    /* dados =  "HTTP/1.0 200 OK\r\n\r\n";
    if( caminho_arquivo_com_nome.find(".jpg") != string::npos ) {
      dados += "Content-Type: image/jpg\r\n\r\n";
    } else if ( caminho_arquivo_com_nome.find(".png") != string::npos ) {
      dados += "Content-Type: image/png\r\n\r\n";
    } */
    while( safeGetline (infile, linha) )
    {
      dados = dados + linha + " \r\n";  
    }

  } else {
    cout << "Problemas ao ler arquivo";
    return "";
  }
    return dados;
}


bool exist_folder(const string caminho_arquivo_com_nome )
{
  bool pasta_existe = false;
  struct stat st = {0};
  string caminho_arquivo_com_nome_e_cached = CACHED_FILES_FOLDER + caminho_arquivo_com_nome;

  if (stat(caminho_arquivo_com_nome_e_cached.c_str(), &st) != -1) pasta_existe = true;

  return pasta_existe ;
}

bool store_domain(string complete_path, string dados )
{ 
  bool succesfull_stored = true;
  string extracted_subdomain, acummulated_sub_domain = "", delimiter = "/";
  size_t first_slice_coordinate, second_slice_coordinate;
  first_slice_coordinate = 0;
  second_slice_coordinate = complete_path.find(delimiter);

  cout << "Storing domain" << endl;

  while(second_slice_coordinate != string::npos and first_slice_coordinate != string::npos )
  { 
    extracted_subdomain =  complete_path.substr(first_slice_coordinate, second_slice_coordinate - first_slice_coordinate + 1 );
    acummulated_sub_domain = acummulated_sub_domain + extracted_subdomain;
    cout << "Slicing domain:" << acummulated_sub_domain << "!" << endl;
     
    // Primeiro verificamos se existe a pasta com esse caminho acumulado
    if( exist_folder(acummulated_sub_domain) == false)
    {
      // Se não existir, criamos a pasta
      if (create_folder(acummulated_sub_domain) == false) succesfull_stored = false;
    } 

    // Se o segundo indice já estiver no final então não há mais o que procurar
    if ( second_slice_coordinate == complete_path.size() - 1 )
    {
      cache_file( acummulated_sub_domain, dados );
      first_slice_coordinate = string::npos;
    } else {
      // Caso não esteja, continua buscando
      
      first_slice_coordinate = second_slice_coordinate + 1;
    }
    second_slice_coordinate = complete_path.find(delimiter, first_slice_coordinate + 1);
    // Caso não haja mais delimitadores, devemos extrair somente até o final
    if (second_slice_coordinate == string::npos)
    {
      second_slice_coordinate = complete_path.size() - 1;
    }
  } 

  return succesfull_stored;
}

std::istream& safeGetline(std::istream& is, std::string& t)
{
    t.clear();

    // The characters in the stream are read one-by-one using a std::streambuf.
    // That is faster than reading them one-by-one using the std::istream.
    // Code that uses streambuf this way must be guarded by a sentry object.
    // The sentry object performs various tasks,
    // such as thread synchronization and updating the stream state.

    std::istream::sentry se(is, true);
    std::streambuf* sb = is.rdbuf();

    for(;;) {
        int c = sb->sbumpc();
        switch (c) {
        case '\n':
            return is;
        case '\r':
            if(sb->sgetc() == '\n')
                sb->sbumpc();
            return is;
        case std::streambuf::traits_type::eof():
            // Also handle the case when the last line has no line ending
            if(t.empty())
                is.setstate(std::ios::eofbit);
            return is;
        default:
            t += (char)c;
        }
    }
}


string set_accept_enconde_identity(string original_request)
{
  size_t slicer_first_coordinate, slicer_second_coordinate;
  string request_temp, word_to_find = "Accept-Encoding: ", identity_enconding = "identity";
  slicer_first_coordinate = original_request.find(word_to_find);    
  slicer_second_coordinate = original_request.find("\n", slicer_first_coordinate);
  
  if( slicer_first_coordinate != string::npos and slicer_second_coordinate != string::npos ){
    request_temp = original_request.replace(slicer_first_coordinate + word_to_find.size(),  slicer_second_coordinate - slicer_first_coordinate - word_to_find.size(), identity_enconding );
  } else {
    request_temp = original_request;
  }
  
  return request_temp;
}
