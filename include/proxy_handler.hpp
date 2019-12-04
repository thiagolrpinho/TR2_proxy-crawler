#include <catch.hpp>
#include "socket_handler.hpp"
#include "estrutura_helper.hpp"

#ifndef PROXY_HANDLER_HPP
#define PROXY_HANDLER_HPP

  string recv_request(int server_socket, int internal_socket)
  string send_response(string response, int internal_socket)
  bool send_request()
  bool recv_response()
  hostent dns_resolution(estrutura_request header_attributes)


#endif