#pragma once

#include <cassert>

#include <algo/trees/segment_tree/new_statistics/sum.hpp>
#include "algo/trees/segment_tree/new_statistics/minimum.hpp"
#include "algo/trees/segment_tree/updates/range.hpp"

namespace algo::trees::segment_tree::range_updates {

template <typename Element, typename Range = IntRange>
struct Add {
  Add(Range range, Element add)
      : range(range),
        add(add) {
  }

  Add Compose(Add update) {
    assert(range.IsInside(update.range));

    auto result = Add(*this);
    result.add += update.add;
    return result;
  };

  auto Apply(new_statistics::IntSum stat) {
    assert(stat.range.IsInside(range));
    stat.value += stat.range.Length() * add;
    return stat;
  }

  auto Apply(new_statistics::IntMinimum stat) {
    assert(stat.range.IsInside(range));
    stat.value += add;
    return stat;
  }

  Range range;
  Element add;
};

using IntAdd = Add<i64>;

}  // namespace algo::trees::segment_tree::range_updates
