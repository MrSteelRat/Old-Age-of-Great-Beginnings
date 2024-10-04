#include "Client.h"

TCPClient::TCPClient(std::string clientName, int serverPort, int period) : clientName(std::move(clientName)), serverPort(serverPort), period(period) {}

void TCPClient::start() {
    struct sockaddr_in serverAddr {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    while (true) {
      int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
      if (clientSocket < 0) {
        std::cerr << "Error opening socket\n";
        exit(EXIT_FAILURE);
      }

      if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Connection failed\n";
        close(clientSocket);
        exit(EXIT_FAILURE);
      }

      std::string message = "[" + getTimestamp() + "] \"" + clientName + "\"";
      send(clientSocket, message.c_str(), message.length(), 0);
      close(clientSocket);

      std::this_thread::sleep_for(std::chrono::seconds(period));
    }
}

std::string TCPClient::getTimestamp() {
    time_t now = time(nullptr);
    struct tm timeinfo {};
    char buffer[80];
    localtime_r(&now, &timeinfo);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
    return std::string(buffer);
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " <client_name> <server_port> <period>\n";
    return EXIT_FAILURE;
  }

  std::string clientName = argv[1];
  int serverPort = std::stoi(argv[2]);
  int period = std::stoi(argv[3]);

  TCPClient client(clientName, serverPort, period);
  client.start();

  return EXIT_SUCCESS;
}
