#pragma once

#include <cassert>

#include <algo/trees/segment_tree/statistics/sum.hpp>
#include "algo/trees/segment_tree/statistics/minimum.hpp"
#include "algo/ranges/range.hpp"
#include "algo/utils/debug.hpp"

namespace algo::trees::segment_tree::updates {

template <typename Element, typename Range = ranges::IntRange>
struct Add {
  using ElementType = Element;
  Add(Range range, Element add)
      : range(range),
        add(add) {
  }

  Add Compose(Add update) const {
    dbg("Add.Compose", range, add, update.range, update.add);

    assert(range == update.range);

    auto result = Add(*this);
    result.add += update.add;
    return result;
  };

  Add OnSubrange(Range subrange) const {
    assert(subrange.IsInside(range));

    return Add(subrange, add);
  }

  auto Apply(statistics::IntSum stat) const {
    dbg("Add.Apply", range, add, stat.range, stat.value);
    assert(range == stat.range);

    stat.value += stat.range.Length() * add;
    return stat;
  }

  auto Apply(statistics::IntMinimum stat) const {
    assert(range == stat.range);

    stat.value += add;
    return stat;
  }

  Range range;
  Element add;
};

using IntAdd = Add<i64>;

}  // namespace algo::trees::segment_tree::updates
