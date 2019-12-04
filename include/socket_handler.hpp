#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>


#ifndef SOCKET_HANDLER_H
#define SOCKET_HANDLER_H

  int create_client_socket(char* url,int port);
  int create_server_socket(char* address,int port);

#endif