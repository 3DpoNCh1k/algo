#pragma once

#include <algo/trees/segment_tree/statistics/value_of.hpp>
#include <algo/trees/segment_tree/statistics/sum.hpp>
#include "algo/trees/segment_tree/statistics/minimum.hpp"

namespace algo::trees::segment_tree::updates {

using namespace statistics;

template <typename Element, typename Range = ranges::IntRange>
struct Set {
  using Index = typename Range::Index;

  Set(Range range, Element value)
      : range(range),
        value(value) {
  }

  Set(Index index, Element value)
      : range(index, index),
        value(value) {
  }

  Set(Index l, Index r, Element value)
      : range(l, r),
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

  auto Apply(ValueOf<IntSum>) const {
    return range.Length() * value;
  }

  auto Apply(ValueOf<IntMinimum>) const {
    return value;
  }

  Range range;
  Element value;
};

using IntSet = Set<i64>;

}  // namespace algo::trees::segment_tree::updates
