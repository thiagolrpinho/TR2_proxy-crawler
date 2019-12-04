/*
Módulo criado com o intuito de encapsular funções relacionadas à análise e 
separação de dados extraídos das requisições e respostas
*/
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <strings.h>
#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>
#include <catch.hpp>

using namespace std;

#ifndef ESTRUTURA_HELPER_HPP
#define ESTRUTURA_HELPER_HPP

#define GET_STRING_SIZE (4)
#define PUT_STRING_SIZE (4)
#define POST_STRING_SIZE (5)
#define HEAD_STRING_SIZE (5)
#define PATCH_STRING_SIZE (6)
#define DELETE_STRING_SIZE (7)
#define CONNECT_STRING_SIZE (8)
#define HTTP_1_STRING_SIZE (6)
#define CACHED_FILES_FOLDER "./cached_files/"

struct estrutura_request {
  char host[350];
  char url[350];
  char file_path[200];
  char complete_path[200];
  int porta;
  bool is_get;
};

// Função que retorna o indice correto onde começa a url da requisição
// Também verifica se é do tipo GET e altera a flag dentro do request header
size_t find_request_coordinate( string request, estrutura_request request_header );

// Função que analise a request a retorna uma estrutura com host, url 
// e subdominio.
estrutura_request extract_header( string request );

// Estrutura recebe um host e retorna se ele é válido
bool is_valid_host(const string host );

// Cria um GET usando a URL passada e retorna na forma de array de char
string create_get_request( const string original_url );


// Cria uma pasta dentro da pasta cached_files usando a string passada como nome,
bool create_folder(const string relative_folder_path );

// Salva nessa pasta os dados desejados em .txt
bool cache_file(string relative_folder_path, string data );

// Carrega os dados armazenados em .txt dentro da pasta desejada:
string load_cached( string relative_folder_path );

// Valida se há uma pasta dentro da pasta cached_files para um dado nome
bool exist_folder(const string relative_folder_path );

// Armazena um caminho completo e cria as pastas necessárias para cada subdominio
bool store_domain(string complete_path, string dados );

// Receives a request, searches for Accept-Encode and overwrites the params
// to identity. if no Accept-Encode was found, return the same string
string set_accept_enconde_identity(string original_request);

// Lê linhas e trata \r
std::istream& safeGetline(std::istream& is, std::string& t);
#endif