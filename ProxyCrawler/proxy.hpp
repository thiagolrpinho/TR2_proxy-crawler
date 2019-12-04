#ifndef PROXY_HPP
#define PROXY_HPP
#include <stdio.h>
#include <stdlib.h>


#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "socket_handler.hpp"
#include "estrutura_helper.hpp"

int start_full_proxy();
string get_request(int proxy_socket);
string send_request_and_receive_response(int browser_proxy_socket, string request, char host[350], int porta);
void send_back_request(int proxy_socket, string response);


#endif // PROXY_HPP
