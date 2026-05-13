#include "serializer.h"
#include <string>

std::string Serializer::to_json() {
  std::string output;
  output.reserve(1024);
  output += "{\n";

  // Audio
  output += "\"audio\": [";
  bool first = true;
  for (const auto &audio : source_.audios) {
    if (!first) {
      output += ", ";
    }
    output += "\"" + audio + "\"";
    first = false;
  }
  output += "],\n";

  // Video
  output += "\"video\": [";
  first = true;
  for (const auto &video : source_.videos) {
    if (!first) {
      output += ", ";
    }
    output += "\"" + video + "\"";
    first = false;
  }
  output += "],\n";

  // Images
  output += "\"images\": [";
  first = true;
  for (const auto &image : source_.images) {
    if (!first) {
      output += ", ";
    }
    output += "\"" + image + "\"";
    first = false;
  }
  output += "]\n";

  output += "}\n";
  return output;
}
