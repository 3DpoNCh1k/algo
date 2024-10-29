#pragma once

#include <sstream>
#include <string>
#include <algo/utils/types/fundamentals.hpp>

namespace algo::ranges {

template <typename IndexType>
struct Range {
  using Index = IndexType;

  Range(Index l, Index r)
      : l(l),
        r(r) {
  }

  template <typename Jndex>
  bool IsInside(const Range<Jndex>& other) const {
    return other.l <= l && r <= other.r;
  };

  template <typename Jndex>
  bool IsOutside(const Range<Jndex>& other) const {
    return other.l > r || other.r < l;
  };

  Index Length() const {
    return r - l + 1;
  }

  std::string ToString() const {
    std::stringstream ss;
    ss << "Range: l = " << l << " r = " << r << std::endl;
    return ss.str();
  };

  template <typename Jndex>
  bool operator==(const Range<Jndex>& other) const {
    return l == other.l && r == other.r;
  }

  template <typename Jndex>
  bool operator!=(const Range<Jndex>& other) const {
    return !(*this == other);
  }

  // segment tree uses implicit conversion
  operator Range<i64>() {  // NOLINT
    return Range<i64>(l, r);
  };

  Index l, r;
};

using IntRange = Range<i64>;

}  // namespace algo::ranges
