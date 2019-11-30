#include "estrutura_helper.hpp"


size_t find_request_coordinate( string request )
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

}
estrutura_request request_parser( string request )
{ 
  estrutura_request analisador_request;
  string url, host, full_path, file_path, porta;
  size_t coordenada_requisicao, coordenada_indice_http, coordenada_indice_host, coordenada_indice_fim_linha_host;
  size_t coordenada_porta;

  //Printa o request no terminal
  cout << "Request recebida: " << endl;
  cout << request << endl;

  coordenada_requisicao = find_request_coordinate(  request );
  coordenada_indice_http = request.find(" HTTP/1", 0 );
  if( coordenada_indice_http != string::npos && coordenada_requisicao != string::npos)
  {
    url = request.substr(coordenada_requisicao, coordenada_indice_http - coordenada_requisicao);
  }

  cout << "Url é:" << url << endl;

  coordenada_indice_host = request.find("Host:", 0 ) + HTTP_1_STRING_SIZE;
  coordenada_indice_fim_linha_host = request.find("\n", coordenada_indice_host);
  
  if( coordenada_indice_host != string::npos && coordenada_indice_fim_linha_host != string::npos)
  {
    host = request.substr(coordenada_indice_host, coordenada_indice_fim_linha_host - coordenada_indice_host);
    coordenada_porta = host.find(":");
    if( coordenada_porta != string::npos ) { 
      porta = host.substr( coordenada_porta , host.size() - coordenada_indice_fim_linha_host - 1 );
      host = host.substr( 0 , coordenada_indice_fim_linha_host );

    }
  }
  cout << "Host é:" << host <<  endl;

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

cout << "File path: " << analisador_request.file_path << endl;
cout << "complete path: " << analisador_request.complete_path << endl;

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
  url = "GET " + original_url + " HTTP/1.1 \r\n";


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

bool cache_file(string nome_pasta, string dados )
{
  string nome_pasta_com_cached = CACHED_FILES_FOLDER + nome_pasta;

  string nome_arquivo = nome_pasta_com_cached + "/cached_request.txt";

  cout << "Caching file inside " + nome_pasta << endl;
  
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
  string nome_pasta_com_cached = CACHED_FILES_FOLDER + caminho_arquivo_com_nome;
  string nome_arquivo = nome_pasta_com_cached + "/cached_request.txt";

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
  size_t first_ocurrence, second_ocurrence;
  first_ocurrence = 0;
  second_ocurrence = complete_path.find(delimiter);

  while(second_ocurrence != string::npos and first_ocurrence != string::npos )
  { 
    extracted_subdomain =  complete_path.substr(first_ocurrence, second_ocurrence - first_ocurrence + 1 );
    acummulated_sub_domain = acummulated_sub_domain + extracted_subdomain;
     // Primeiro verificamos se existe a pasta com esse caminho acumulado
    if( exist_folder(acummulated_sub_domain) == false)
    {
      // Se não existir, criamos a pasta
      if (create_folder(acummulated_sub_domain) == false)succesfull_stored = false;
    } 


    // Se o segundo indice já estiver no final então não há mais o que procurar
    if ( second_ocurrence == complete_path.size() - 1 )
    {
      cache_file( acummulated_sub_domain, dados );
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