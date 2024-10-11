#pragma once

#include <algo/trees/segment_tree/new_statistics/sum.hpp>
#include "algo/trees/segment_tree/new_statistics/minimum.hpp"

namespace algo::trees::segment_tree::range_updates {

template <typename Range, typename Element>
struct Set {
  Set(Range range, Element value)
      : range(range),
        value(value) {
  }

  Set Compose(Set update) {
    assert(range.IsInside(update.range));

    auto result = Set(*this);
    result.value = update.value;
    return result;
  };

  auto Apply(new_statistics::IntSum stat) {
    stat.value = stat.range.Length() * value;
    return stat;
  }

  auto Apply(new_statistics::IntMinimum stat) {
    stat.value = value;
    return stat;
  }

  Range range;
  Element value;
};

}  // namespace algo::trees::segment_tree::range_updates
