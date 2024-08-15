#pragma once

#include <algo/strings/aho_corasick/statistics/base.hpp>

namespace algo::strings::aho_corasick::statistics {
template <typename String>
struct Leftmost : Base<String> {
  int result = -1;

  Leftmost() {
    Reset();
  }

  void Reset() {
    result = -1;
  }

  void FoundAsLongestPatternEndingAt(int index) {
    FoundEndingAt(index);
  }

  void FoundAsSuffixOfLongerPattern(const Leftmost& pattern_stat) {
    if (pattern_stat.result != -1) {
      int end_index = pattern_stat.result + pattern_stat.pattern.size() - 1;
      FoundEndingAt(end_index);
    }
  }

  bool operator==(const Leftmost& that) const {
    return result == that.result;
  }

  bool operator!=(const Leftmost& that) const {
    return !(*this == that);
  }

 private:
  void FoundEndingAt(int index) {
    int start_index = index - this->pattern.size() + 1;
    if (result == -1 || start_index < result) {
      result = start_index;
    }
  }
};
}  // namespace algo::strings::aho_corasick::statistics
