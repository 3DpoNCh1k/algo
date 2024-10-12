#pragma once

#include <sstream>
#include <string>

namespace algo::ranges {

template <typename Index = int>
struct Range {
  Range(Index l, Index r)
      : l(l),
        r(r) {
  }

  bool IsInside(const Range& other) const {
    return other.l <= l && r <= other.r;
  };

  bool IsOutside(const Range& other) const {
    return other.l > r || other.r < l;
  };

  Index Length() const {
    return r - l + 1;
  }

  bool IsEmpty() const {
    return l > r;
  }

  static Range MakeEmpty() {
    return Range(0, -1);
  }

  std::string ToString() const {
    std::stringstream ss;
    ss << "Range: l = " << l << " r = " << r << std::endl;
    return ss.str();
  };

  bool operator==(const Range& other) const {
    return l == other.l && r == other.r;
  }

  bool operator!=(const Range& other) const {
    return !(*this == other);
  }

  Index l, r;
};

using IntRange = Range<int>;

}  // namespace algo::ranges
