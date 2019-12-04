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

string get_request(int server_socket);


#endif // PROXY_HPP
