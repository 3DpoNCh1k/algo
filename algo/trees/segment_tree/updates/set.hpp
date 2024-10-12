#pragma once

#include <algo/trees/segment_tree/statistics/sum.hpp>
#include "algo/trees/segment_tree/statistics/minimum.hpp"

namespace algo::trees::segment_tree::updates {

template <typename Element, typename Range = ranges::IntRange>
struct Set {
  Set(Range range, Element value)
      : range(range),
        value(value) {
  }

  Set Compose(Set update) {
    assert(range == update.range);

    auto result = Set(*this);
    result.value = update.value;
    return result;
  };

  Set OnSubrange(Range subrange) const {
    assert(subrange.IsInside(range));
    return Set(subrange, value);
  }

  auto Apply(statistics::IntSum stat) const {
    assert(range == stat.range);

    stat.value = stat.range.Length() * value;
    return stat;
  }

  auto Apply(statistics::IntMinimum stat) const {
    assert(range == stat.range);

    stat.value = value;
    return stat;
  }

  Range range;
  Element value;
};

using IntSet = Set<i64>;

}  // namespace algo::trees::segment_tree::updates
