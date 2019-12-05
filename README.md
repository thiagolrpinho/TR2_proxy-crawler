# Um Inspetor HTTP baseado em Proxy Server

Thiago Guimarães Barros
14/0066225
Universidade de Brasília
thigb7@gmail.com

Thiago Luis Rodrigues Pinho
150065205
Universidade de Brasília
thiagoluispinho@gmail.com

## Objetivo
O objetivo do projeto foi implementar um Inspetor HTTP, utilizando um proxy http para analisar o trafego da web, contendo interface gráfica, e as funcionalidade spider e dump, que são respectivamente, uma função que cria a árvore hipertextual de uma dada URL com suas dadas URLs subjacentes, uma função que baixa o conteúdo de uma dada URL para ser acessada como sendo local.

## Introdução
Um servidor proxy consiste em um intermediador do trafego entre o cliente, que pode ser um ou mais usuários utilizando um navegador web, e um servidor, que hospeda do site. Podendo ser utilizado com algumas finalidades como:

+ **Melhorar desempenho do acesso á rede pelo cliente** - O proxy pode salvar as páginas acessadas ou as páginas de um domínio acessado, para não ser necessário o envio da requisição ao servidor de destino.
+ **Bloquear o acesso á domínios escolhidos como improópios** - O proxy pode bloquear requisições á domínios pre cadastrados como imprórpios, retornando para o cliente uma página informando o bloqueio.
+ **Mascarar o endereço do cliente** - O proxy pode ser usado com a finalidade de navegar na web estando anônimo, sendo visto na rede com o endereço do proxy.

## Arquitetura do Software
Modularizamos o código utilizando arquivos cpp, e suas respectivas bibliotecas hpp, sendo compilados através de um makefile. Implementamos também testes automatizados para melhorar a robustês do programa e ganhar produtividade. Pra a interface gráfica utilizamos as bibiotecas do QT Creator. Separados em uma arquitetura de pastas que facilite o entendimento, mantendo as boas práticas.

## Implementação
Para a implementação do Proxy utilizamos a biblioteca <sockets.h>, com a finalidade de abrir sockets para os IPs e portas desejados, modularizamos essa funcionalidade de abertura de socket criando a biblioteca socket_handler, para a mineração dos dados do cabeçalho request criamos uma biblioteca chamada estrutura_helper, que extrai os dados necessários do header e retorna uma Struct com as informações necessárias como host e etc. Utilizamos a função gethostbyname() para fazer uma requisição ao servidor DNS e termos o IP do domínio solicitado. Para a interface gráfica utilizamos as bibliotecas do QT Creator, e para a criação dos testes automatizados utilizamos a biblioteca <catch.hpp>.

## Conclusão

Com a conclusão do projeto conseguimos ter um melhor entendimento de como funciona a camada de aplicação tanto como o funcionamento do protocolo HTTP, aprendendo também o funcionamento de um servidor proxy na prática tanto como suas utilidades no âmbito de melhorar desempenho do acesso a rede, mascarar seu real IP e bloquear domínios considerados impróprios para o administrador da rede.

## Execução do Programa
