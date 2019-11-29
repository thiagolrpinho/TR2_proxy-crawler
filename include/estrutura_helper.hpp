/*
Módulo criado com o intuito de encapsular funções relacionadas à análise e 
separação de dados extraídos das requisições e respostas
*/
#include <iostream>
#include <string>
#include <string.h>
#include <strings.h>
#include <algorithm> 


#ifndef ESTRUTURA_HELPER_HPP
#define ESTRUTURA_HELPER_HPP
struct estrutura_request {
  char host[350];
  char url[350];
};

estrutura_request request_parser( std::string request );

#endif