#pragma once
#include "files.h"

class Scanner {
public:
  Scanner(std::string path) : path_(path) {};
  void scan_once(Files &files);

private:
  std::string path_;
};
