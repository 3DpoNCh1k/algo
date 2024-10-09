#pragma once

#include <string>

#include <algo/utils/random/random.hpp>

namespace algo::utils::generators {

struct StringGenerator {
  StringGenerator() {
  }

  std::string FromRange(char from, char to, int len) {
    std::string s;
    for (int i = 0; i < len; ++i) {
      char ch = random::RandomInt(from, to);
      s.push_back(ch);
    }
    return s;
  }

  std::string Printable(int len) {
    return FromRange(32, 127, len);
  }

  std::string Digits(int len) {
    return FromRange(48, 57, len);
  }

  std::string Letters(int len) {
    auto k_lower = random::RandomInt(0, len);
    auto s = Lowercase(k_lower) + Uppercase(len - k_lower);
    random::Shuffle(s);
    return s;
  }

  std::string Uppercase(int len) {
    return FromRange(65, 90, len);
  }

  std::string Lowercase(int len) {
    return FromRange(97, 122, len);
  }
};

}  // namespace algo::utils::generators
