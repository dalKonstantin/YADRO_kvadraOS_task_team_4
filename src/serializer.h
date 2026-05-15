#pragma once

#include "files.h"
#include <string>

/*
 * Class that serializes data to json
 */
class Serializer {
public:
  Serializer(Files &files) : source_(files) {};

  std::string to_json();

private:
  Files &source_;
};
