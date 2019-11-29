/*
Módulo criado com o intuito de encapsular funções relacionadas à análise e 
separação de dados extraídos das requisições e respostas
*/
#include <iostream>
#include <string>
#include <string.h>
#include <strings.h>
#include <algorithm> 
using namespace std;

#ifndef ESTRUTURA_HELPER_HPP
#define ESTRUTURA_HELPER_HPP
struct estrutura_request {
  char host[350];
  char url[350];
};

// Função que analise a request a retorna uma estrutura com host, url 
// e subdominio.
estrutura_request request_parser( string request );

// Estrutura recebe um host e retorna se ele é válido
bool is_valid_host(const string host );


#endif