#pragma once

namespace algo::strings::aho_corasick::statistics {
template <typename String>
struct Base {
  String pattern;
  void SetPattern(const String& p) {
    pattern = p;
  }
};
}  // namespace algo::strings::aho_corasick::statistics
