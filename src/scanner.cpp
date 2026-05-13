#include "scanner.h"
#include "formats.h"

#include <filesystem>

void Scanner::scan_once(Files &files) {

  for (const auto &entry : std::filesystem::recursive_directory_iterator(path_)) {
    if (!entry.is_regular_file()) {
      continue;
    }

    const auto &path = entry.path();
    const auto ext = path.filename().extension();
    if (formats.audio.contains(ext)) {
      files.audios.push_back(path.filename());
    } else if (formats.video.contains(ext)) {
      files.videos.push_back(path.filename());
    } else if (formats.image.contains(ext)) {
      files.images.push_back(path.filename());
    }
  }

  // for (const auto &entry : std::filesystem::recursive_directory_iterator(path)) {
  //   if (std::filesystem::is_regular_file(entry) && entry.path().extension() == ".jpg") {
  //     files.images.push_back(entry.path().filename());
  //   } else if (std::filesystem::is_regular_file(entry) && entry.path().extension() == ".mp3") {
  //     files.audio.push_back(entry.path().filename());
  //   }
  // }
}
