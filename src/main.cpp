#include <atomic>
#include <chrono>
#include <condition_variable>
#include <csignal>
#include <fstream>
#include <ios>
#include <iostream>
#include <mutex>
#include <sys/socket.h>

#include "cli.h"
#include "files.h"
#include "scanner.h"
#include "serializer.h"
#include "server.h"

std::atomic<bool> is_running = true;
std::mutex shutdown_mutex;

std::condition_variable shutdown_cv;
void signal_handler(int signum) {
  is_running.store(false);
  shutdown_cv.notify_all();
}

int main(int argc, char **argv) {
  std::signal(SIGINT, signal_handler);
  std::signal(SIGTERM, signal_handler);

  Cli cli(argc, argv);
  Files files;
  Scanner scanner(cli.path);
  Serializer serializer(files);
  Server server(1234, serializer);

  server.run();

  // Simple lock
  std::mutex files_mutex;

  std::cout << "Scanning in: " << cli.path << "\tInterval: " << cli.interval << " s" << "\n";
  while (is_running.load()) {
    {
      std::lock_guard<std::mutex> lock(files_mutex);

      files.clear();
      scanner.scan_once(files);

      if (cli.save_to_file) {
        std::ofstream out_file(cli.path / ".media_files", std::ios::out | std::ios::trunc);
        out_file << serializer.to_json();
      }
    }

    std::unique_lock<std::mutex> lock(shutdown_mutex);

    shutdown_cv.wait_for(lock, std::chrono::seconds(cli.interval),
                         []() { return !is_running.load(); });
  }

  server.request_stop();
  std::cout << "\nExiting..";
}
