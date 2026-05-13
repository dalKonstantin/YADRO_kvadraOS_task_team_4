#include <atomic>
#include <chrono>
#include <csignal>
#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "files.h"
#include "scanner.h"
#include "serializer.h"

std::atomic<bool> is_running = true;

void signal_handler(int signum) { is_running.store(false); }

int main() {
  std::signal(SIGINT, signal_handler);
  std::signal(SIGTERM, signal_handler);

  std::string home_path = std::getenv("HOME");
  if (home_path.empty()) {
    std::cerr << "Cannot open $HOME\n";
    return 1;
  }

  Files files;
  Scanner scanner(home_path);
  Serializer serializer(files);

  while (is_running) {
    scanner.scan_once(files);

    {
      std::ofstream out_file(".media_files", std::ios::out | std::ios::trunc);
      out_file << serializer.to_json();
    }
    files.clear();
    std::this_thread::sleep_for(std::chrono::seconds(5));
  }

  std::cout << "\nExiting..";
}
