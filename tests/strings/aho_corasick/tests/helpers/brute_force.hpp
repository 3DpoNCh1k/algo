#pragma once

#include <string>
#include <vector>

struct BruteForce {
  using Patterns = std::vector<std::string>;
  Patterns patterns;
  std::string s;
  explicit BruteForce(const Patterns& patterns)
      : patterns(patterns) {
  }

  void Scan(const std::string& s0) {
    s = s0;
  }
};
