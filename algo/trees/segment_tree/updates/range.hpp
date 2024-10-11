#pragma once

namespace algo::trees::segment_tree::range_updates {

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

  Index l, r;
};

using IntRange = Range<int>;

}  // namespace algo::trees::segment_tree::range_updates
