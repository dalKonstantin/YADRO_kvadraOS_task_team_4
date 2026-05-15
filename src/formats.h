#pragma once

#include <string>
#include <unordered_set>

/*
 * Struct for storing file formats
 */
struct Formats {
  std::unordered_set<std::string> audio = {".mp3", ".wav", ".flac"};
  std::unordered_set<std::string> video = {".mp4", ".mpg", ".avi", ".mkv"};
  std::unordered_set<std::string> image = {".jpeg", ".jpg", ".png"};
};

inline const Formats formats;
