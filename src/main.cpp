#include <atomic>
#include <chrono>
#include <csignal>
#include <fstream>
#include <ios>
#include <iostream>
#include <mutex>
#include <thread>

#include "cli.h"
#include "files.h"
#include "scanner.h"
#include "serializer.h"
#include "server.h"

std::atomic<bool> is_running = true;

void signal_handler(int signum) { is_running.store(false); }

int main(int argc, char **argv) {
  std::signal(SIGINT, signal_handler);
  std::signal(SIGTERM, signal_handler);

  Cli cli(argc, argv);
  Files files;
  Scanner scanner(cli.path);
  Serializer serializer(files);
  Server server(1234, serializer);

  std::mutex files_mutex;
  server.run();

  std::cout << "Scanning in: " << cli.path << "\tInterval: " << cli.interval << " s" << "\n";
  while (is_running.load()) {
    std::lock_guard<std::mutex> lock(files_mutex);

    files.clear();
    scanner.scan_once(files);

    std::ofstream out_file(cli.path / ".media_files", std::ios::out | std::ios::trunc);
    out_file << serializer.to_json();
    std::this_thread::sleep_for(std::chrono::seconds(cli.interval));
  }
  // while (is_running.load()) {
  //   scanner.scan_once(files);

  //   {
  //     std::ofstream out_file(cli.path.string() + "/" + ".media_files",
  //                            std::ios::out | std::ios::trunc);
  //     out_file << serializer.to_json();
  //   }
  //   std::cout << "Succesfully scaned: " << cli.path.string() << "\n";
  //   files.clear();
  //   std::this_thread::sleep_for(std::chrono::seconds(cli.interval));
  // }

  std::cout << "\nExiting..";
}
