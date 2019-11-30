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
using namespace std;

#ifndef ESTRUTURA_HELPER_HPP
#define ESTRUTURA_HELPER_HPP

#define GET_STRING_SIZE (4)
#define POST_STRING_SIZE (5)
#define HTTP_1_STRING_SIZE (6)
#define CACHED_FILES_FOLDER "./cached_files/"

struct estrutura_request {
  char host[350];
  char url[350];
  char file_path[200];
  char complete_path[200];
};

// Função que analise a request a retorna uma estrutura com host, url 
// e subdominio.
estrutura_request request_parser( string request );

// Estrutura recebe um host e retorna se ele é válido
bool is_valid_host(const string host );

// Cria um GET usando a URL passada e retorna na forma de array de char
string create_get_request( const string original_url );


// Cria uma pasta dentro da pasta cached_files usando a string passada como nome,
bool create_folder(const string nome_pasta, string data );

// Salva nessa pasta os dados desejada na forma de um txt
bool cache_file(string nome_pasta, string data);

// Valida se há uma pasta dentro da pasta cached_files para um dado nome
bool exist_folder(const string nome_pasta );

// Armazena um caminho completo e cria as pastas necessárias para cada subdominio
bool store_domain(string complete_path, string dados );


#endif