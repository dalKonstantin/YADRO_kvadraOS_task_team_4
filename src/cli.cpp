#include "cli.h"
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>

Cli::Cli(int argc, char **argv) {
  const char *home = std::getenv("HOME");
  if (home != nullptr) {
    path = home;
  } else {
    path = std::filesystem::current_path();
  }
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-i" && i + 1 < argc) {
      interval = std::stoi(argv[++i]);
    } else if (arg == "-p" && i + 1 < argc) {
      path = std::filesystem::absolute(argv[++i]);
      std::cout << path << "\n";
    }
  }
}
