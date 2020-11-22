#include "Server_Core.hpp"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
//#include <pthread>

Server_Core::Server_Core(){}
Server_Core::Server_Core(int port, std::string address){
      this->port_number = port;
      this->address = address;
}

void Server_Core::run(){
  int listening = socket(AF_INET, SOCK_STREAM, 0);

  if (listening == -1){
      std::cerr << "Can't create a socket! Quitting" << std::endl;
      return;
  }

  // Bind the ip address and port to a socket
  sockaddr_in hint;
  hint.sin_family = AF_INET;
  hint.sin_port = htons(port_number);
  inet_pton(AF_INET, address.c_str(), &hint.sin_addr);

  bind(listening, (sockaddr*)&hint, sizeof(hint));

  // Tell Winsock the socket is for listening
  listen(listening, SOMAXCONN);

  // Wait for a connection
  sockaddr_in client;
  socklen_t clientSize = sizeof(client);

  int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

  char host[NI_MAXHOST];       // Client's remote name
  char service[NI_MAXSERV];   // Service (i.e. port) the client is connect on

  memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
  memset(service, 0, NI_MAXSERV);

  if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0){
      std::cout << host << " connected on port " << service << std::endl;
  }
  else{
      inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
      std::cout << host << " connected on port " << ntohs(client.sin_port) << std::endl;
  }

  // Close listening socket
  close(listening);

  // While loop: accept and echo message back to client
  char buf[4096];

  while (true){
      memset(buf, 0, 4096);

      // Wait for client to send data
      int bytesReceived = recv(clientSocket, buf, 4096, 0);
      if (bytesReceived == -1){
          std::cerr << "Error in recv(). Quitting" << std::endl;
          break;
      }

      if (bytesReceived == 0){
          std::cout << "Client disconnected " << std::endl;
          break;
      }

      std::cout << std::string(buf, 0, bytesReceived) << std::endl;

      // Echo message back to client
      send(clientSocket, buf, bytesReceived + 1, 0);
  }

  close(clientSocket);
}

int Server_Core::threadDispatch() {return 0;}

std::ostream& operator<< (std::ostream& os, Server_Core& s)
{
  os << "Adres: "<<s.address<<"  port: "<<s.port_number;
  return os;
}

void Server_Core::idiotic_respond(){

}
