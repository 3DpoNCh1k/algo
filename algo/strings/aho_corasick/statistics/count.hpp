#pragma once

#include <algo/strings/aho_corasick/statistics/base.hpp>
#include <algo/utils/types/fundamentals.hpp>

namespace algo::strings::aho_corasick::statistics {
struct Count : Base {
  i64 result = 0;

  Count() {
    Reset();
  }

  void Reset() {
    result = 0;
  }

  void FoundAsLongestPatternEndingAt(int index) {
    result++;
  }

  void FoundAsSuffixOfLongerPattern(const Count& pattern_stat) {
    result += pattern_stat.result;
  }

  bool operator==(const Count& that) const {
    return result == that.result;
  }

  bool operator!=(const Count& that) const {
    return !(*this == that);
  }
};
}  // namespace algo::strings::aho_corasick::statistics
