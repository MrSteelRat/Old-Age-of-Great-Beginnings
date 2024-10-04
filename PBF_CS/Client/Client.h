#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <chrono>
#include <thread>

class TCPClient {
private:
  std::string clientName;
  int serverPort;
  int period;

public:
  TCPClient(std::string clientName, int serverPort, int period);
  void start();
  std::string getTimestamp();
};

#endif // CLIENT_H
