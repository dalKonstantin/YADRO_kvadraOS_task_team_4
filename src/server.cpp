#include "server.h"
#include "serializer.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

Server::Server(int port, Serializer &serializer)
    : serializer_(serializer), server_fd_(-1), is_running_(false) {

  // Create socket
  server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
  int opt = 1;

  setsockopt(server_fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  // Bind
  struct sockaddr_in address{};
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);
  bind(server_fd_, reinterpret_cast<sockaddr *>(&address), sizeof(address));

  // Listen
  listen(server_fd_, 3);
}

void Server::run() {
  is_running_.store(true);

  server_thread_ = std::thread([this]() {
    while (is_running_.load()) {
      int client_fd = accept(server_fd_, nullptr, nullptr);

      if (client_fd == -1) {
        continue;
      }
      char buffer[4096];
      recv(client_fd, buffer, sizeof(buffer), 0);

      std::string json = serializer_.to_json();
      send_json(client_fd, json);
    }
  });
}

void Server::request_stop() {
  is_running_.store(false);
  if (server_fd_ != -1) {
    close(server_fd_);
    server_fd_ = -1;
  }
}
Server::~Server() {
  request_stop();
  if (server_thread_.joinable()) {
    server_thread_.join();
  }
}

void Server::send_json(int client_fd, const std::string json) {
  std::string response = "HTTP/1.1 200 OK\r\n"
                         "Content-Type: application/json\r\n"
                         "Content-Length: " +
                         std::to_string(json.size()) +
                         "\r\n"
                         "Connection: close\r\n"
                         "\r\n" +
                         json;

  send(client_fd, response.c_str(), response.size(), 0);
  close(client_fd);
}
