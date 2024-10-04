#include "Server.h"

TCPServer::TCPServer(int port) : port(port) {}

void TCPServer::start() {
    struct sockaddr_in serverAddr {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
      std::cerr << "Error opening socket\n";
      exit(EXIT_FAILURE);
    }

    int bindStatus = bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (bindStatus < 0) {
      std::cerr << "Error binding socket\n";
      exit(EXIT_FAILURE);
    }

    listen(serverSocket, 5);

    while (true) {
      struct sockaddr_in clientAddr {};
      socklen_t clientLen = sizeof(clientAddr);
      int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
      if (clientSocket < 0) {
        std::cerr << "Error accepting client connection\n";
        continue;
      }

      std::thread clientThread(&TCPServer::handleClient, this, clientSocket);
      clientThread.detach();
    }
}

void TCPServer::handleClient(int clientSocket) {
    char buffer[1024];
    int valread = read(clientSocket, buffer, sizeof(buffer));
    if (valread <= 0) {
      close(clientSocket);
      return;
    }

    std::string clientMessage(buffer, valread);
    std::string logEntry = "[" + getTimestamp() + "] " + clientMessage;

    logMutex.lock();
    std::ofstream logFile("log.txt", std::ios_base::app);
    logFile << logEntry << std::endl;
    logFile.close();
    logMutex.unlock();

    close(clientSocket);
}

std::string TCPServer::getTimestamp() {
    const auto now = std::chrono::system_clock::now();
    const auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    const auto time = std::chrono::system_clock::to_time_t(now);
    char time_str[20]{};
    std::strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", std::localtime(&time));

    char ms_str[4]; // Buffer for milliseconds
    std::sprintf(ms_str, "%.3d", static_cast<int>(now_ms.time_since_epoch().count() % 1000));

    return std::string(time_str) + "." + ms_str;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <port>\n";
    return EXIT_FAILURE;
  }

  int port = std::stoi(argv[1]);
  TCPServer server(port);
  server.start();

  return EXIT_SUCCESS;
}
