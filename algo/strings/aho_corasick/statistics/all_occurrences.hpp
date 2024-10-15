#pragma once

#include <algo/strings/aho_corasick/statistics/base.hpp>
#include <algo/utils/types/fundamentals.hpp>
#include <vector>

namespace algo::strings::aho_corasick::statistics {
template <typename String>
struct AllOccurrences : Base<String> {
  AllOccurrences() {
    Reset();
  }

  void Reset() {
    positions.clear();
  }

  void FoundAsLongestPatternEndingAt(int index) {
    FoundEndingAt(index);
  }

  void FoundAsSuffixOfLongerPattern(const AllOccurrences& pattern_stat) {
    for (int pos : pattern_stat.positions) {
      int end_index = pos + pattern_stat.pattern.size() - 1;
      FoundEndingAt(end_index);
    }
  }

  bool operator==(const AllOccurrences& that) const {
    return positions == that.positions;
  }

  bool operator!=(const AllOccurrences& that) const {
    return !(*this == that);
  }

  void FoundEndingAt(int index) {
    int start_index = index - this->pattern.size() + 1;
    positions.push_back(start_index);
  }

  std::vector<int> positions;
};
}  // namespace algo::strings::aho_corasick::statistics
