#pragma once
#include <string>
#include <vector>

/*
 * Struct for storing the found files
 */
struct Files {
  std::vector<std::string> audios;
  std::vector<std::string> videos;
  std::vector<std::string> images;

  void clear() {
    audios.clear();
    videos.clear();
    images.clear();
  }
};
