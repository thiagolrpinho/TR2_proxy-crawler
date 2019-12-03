#include <stdio.h>
#include "proxy_handler.hpp"
#include "socket_handler.hpp"

string recv_request(int server_socket){
  int server_socket, internal_socket;
  char request_buffer[1024];
  string request;

    //Cria socket de Recepção e deixa listening
  do {
    server_socket = create_server_socket("127.0.0.1",8228);
  } while(server_socket == -1 );

  //Aceita conexão pelo Socket de Recepção
  internal_socket = accept(server_socket, NULL, NULL);

  //Recebe o request
  while( recv(internal_socket, &request_buffer, sizeof(request_buffer) - 1) != 0)
  {
    request += request_buffer;
    bzero(request_buffer, sizeof(request_buffer));
  }

  return request;
}

bool send_response(string response, ){
  char response_buffer[1024];
  string partial_response;
  int number_of_fragments, segmentation_sent, segment_size;
  size_t partial_index_coordinate, total_length;



  //Envia a mensagem pelo Socket Interno
  total_length = response.size();
  number_of_fragments = total_length/sizeof(response_buffer);

  for( int segments_sent = 0; segments_sent <= number_of_fragments; segments_sent++ )
  {
    partial_index_coordinate = (segments_sent)*sizeof(response_buffer);

    if( partial_index_coordinate + sizeof(response_buffer) >= total_length )
    {
      segment_size = total_length - partial_index_coordinate - 1;
    } else {
      segment_size = sizeof(response_buffer);
    }
    partial_response = response.substr( partial_index_coordinate , segment_size );
    strncpy(response_buffer, partial_response.c_str(), partial_response.size() );
    send(internal_socket, response_buffer, sizeof(response_buffer), 0);
  };

  response.erase( remove(response.begin(), response.end(), '\r'), response.end() );
  if(response.size() > 500)
  {
    cout << response.substr(0, 500) << endl;
  } else {
    cout << response << endl;
  }

  //Encerra conexão
  shutdown(internal_socket, SHUT_RDWR);
  close(internal_socket);

  return false;
}