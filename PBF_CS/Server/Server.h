#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <fstream>
#include <mutex>
#include <chrono>

class TCPServer {
private:
  int port;
  int serverSocket;
  std::mutex logMutex;

public:
  TCPServer(int port);
  void start();
  void handleClient(int clientSocket);
  std::string getTimestamp();
};

#endif // SERVER_H
