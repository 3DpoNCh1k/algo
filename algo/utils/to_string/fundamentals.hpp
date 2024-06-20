#pragma once

#include <string>

std::string ToString(char c) {
  return std::string(1, c);
}
std::string ToString(bool b) {
  return b ? "true" : "false";
}
std::string ToString(const char* s) {
  return std::string(s);
}