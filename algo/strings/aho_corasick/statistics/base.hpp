#pragma once

#include <string>
namespace algo::strings::aho_corasick::statistics {
struct Base {
  std::string pattern;
  void SetPattern(const std::string& p) {
    pattern = p;
  }
};
}  // namespace algo::strings::aho_corasick::statistics
