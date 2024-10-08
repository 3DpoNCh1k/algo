#pragma once

#include <string>
#include <vector>

struct Tester {
  using Patterns = std::vector<std::string>;
  const Patterns& patterns;

  explicit Tester(const Patterns& patterns)
      : patterns(patterns) {
  }

  virtual void Test(const std::string& s) = 0;
};
