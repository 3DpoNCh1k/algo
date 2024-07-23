#pragma once

#include <algo/strings/aho_corasick/statistics/base.hpp>

namespace algo::strings::aho_corasick::statistics {
struct Rightmost : Base {
  int result = -1;

  Rightmost() {
    Reset();
  }

  void Reset() {
    result = -1;
  }

  void FoundAsLongestPatternEndingAt(int index) {
    FoundEndingAt(index);
  }

  void FoundAsSuffixOfLongerPattern(const Rightmost& pattern_stat) {
    if (pattern_stat.result != -1) {
      int end_index = pattern_stat.result + pattern_stat.pattern.size() - 1;
      FoundEndingAt(end_index);
    }
  }

  bool operator==(const Rightmost& that) const {
    return result == that.result;
  }

  bool operator!=(const Rightmost& that) const {
    return !(*this == that);
  }

 private:
  void FoundEndingAt(int index) {
    int start_index = index - pattern.size() + 1;
    if (result == -1 || start_index > result) {
      result = start_index;
    }
  }
};
}  // namespace algo::strings::aho_corasick::statistics
