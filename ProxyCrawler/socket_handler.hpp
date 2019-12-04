#ifndef SOCKET_HANDLER_H
#define SOCKET_HANDLER_H

  int create_client_socket(char* url,int port);
  int create_server_socket(char* address,int port);

#endif