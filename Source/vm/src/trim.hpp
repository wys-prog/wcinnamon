#pragma once

#include <string>

#include <cctype> // For std::isspace
#include <string>

std::string trim(const std::string &str) {
  size_t start = 0;
  while (start < str.size() && std::isspace(str[start])) {
    ++start;
  }

  size_t end = str.size();
  while (end > start && std::isspace(str[end - 1])) {
    --end;
  }

  return str.substr(start, end - start);
}
