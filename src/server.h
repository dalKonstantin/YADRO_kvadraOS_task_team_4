#pragma once
#include "serializer.h"
#include <atomic>
#include <sys/socket.h>
#include <thread>

/*
 * Simple HTTP server
 */
class Server {
public:
  Server(int port, Serializer &serializer);

  void run();
  void request_stop();
  ~Server();

private:
  Serializer &serializer_;
  int server_fd_;
  std::atomic<bool> is_running_;
  std::thread server_thread_;

  void send_json(int client_fd, const std::string json);
  void send_not_found(int client_fd);
};
