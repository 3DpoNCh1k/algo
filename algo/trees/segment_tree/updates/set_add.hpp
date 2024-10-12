#pragma once

#include <algo/trees/segment_tree/statistics/sum.hpp>
#include <cassert>
#include "algo/trees/segment_tree/statistics/minimum.hpp"

#include "algo/trees/segment_tree/updates/add.hpp"
#include "algo/ranges/range.hpp"
#include "algo/trees/segment_tree/updates/set.hpp"

namespace algo::trees::segment_tree::updates {

template <typename Element, typename Range = ranges::IntRange>
struct SetAdd {
  SetAdd(Range range, Element value, Element add, bool should_set)
      : range(range),
        value(value),
        add(add),
        should_set(should_set) {
  }

  // Should be implicit
  // NOLINTNEXTLINE
  SetAdd(Add<Element, Range> add)
      : SetAdd(add.range, 0, add.add, false) {
  }

  // NOLINTNEXTLINE
  SetAdd(Set<Element, Range> set)
      : SetAdd(set.range, set.value, 0, true) {
  }

  SetAdd Compose(SetAdd update) const {
    assert(range == update.range);

    auto result = SetAdd(*this);

    if (update.should_set) {
      result = update;
    } else {
      result.add += update.add;
    }

    return result;
  };

  SetAdd OnSubrange(Range subrange) const {
    assert(subrange.IsInside(range));

    return SetAdd(subrange, value, add, should_set);
  }

  auto Apply(statistics::IntSum stat) const {
    assert(range == stat.range);

    if (should_set) {
      stat.value = stat.range.Length() * value;
    }
    stat.value += stat.range.Length() * add;

    return stat;
  }

  auto Apply(statistics::IntMinimum stat) const {
    assert(range == stat.range);

    if (should_set) {
      stat.value = value;
    }
    stat.value += add;

    return stat;
  }

  Range range;
  Element value;
  Element add;
  bool should_set;
};

using IntSetAdd = SetAdd<i64>;

}  // namespace algo::trees::segment_tree::updates
