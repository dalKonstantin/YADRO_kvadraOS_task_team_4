#pragma once
#include <string>
#include <vector>

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
