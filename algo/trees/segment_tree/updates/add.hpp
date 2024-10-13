#pragma once

#include <cassert>

#include <algo/trees/segment_tree/statistics/value_of.hpp>
#include <algo/trees/segment_tree/statistics/sum.hpp>
#include "algo/trees/segment_tree/statistics/minimum.hpp"
#include "algo/ranges/range.hpp"
#include "algo/utils/debug.hpp"

namespace algo::trees::segment_tree::updates {

using namespace statistics;

template <typename Element, typename Range = ranges::IntRange>
struct Add {
  using Index = typename Range::Index;
  Add(Range range, Element add)
      : range(range),
        add(add) {
  }

  Add(Index index, Element add)
      : range(index, index),
        add(add) {
  }

  Add(Index l, Index r, Element add)
      : range(l, r),
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

  auto Apply(ValueOf<IntSum> value) const {
    return value.value + range.Length() * add;
  }

  auto Apply(ValueOf<IntMinimum> value) const {
    return value.value + add;
  }

  Range range;
  Element add;
};

using IntAdd = Add<i64>;

}  // namespace algo::trees::segment_tree::updates
