#pragma once
#include <filesystem>

struct Cli {
  Cli(int argc, char *argv[]);

  std::filesystem::path path;
  int interval = 5;
  bool save_to_file = false;
};
