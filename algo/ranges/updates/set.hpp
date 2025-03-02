#pragma once

#include <algo/maths/algebra/matrix/matrix.hpp>

#include <algo/ranges/statistics/value_of.hpp>
#include <algo/ranges/statistics/sum.hpp>
#include <algo/ranges/statistics/minimum.hpp>
#include <cassert>
#include "algo/maths/algebra/power.hpp"
#include "algo/ranges/statistics/multiplication.hpp"

namespace algo::ranges::updates {

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

  auto Apply(statistics::ValueOf<statistics::IntSum>) const {
    return range.Length() * value;
  }

  auto Apply(statistics::ValueOf<statistics::IntMinimum>) const {
    return value;
  }

  auto Apply(statistics::ValueOf<statistics::IntMatrixMultiplication>) const {
    if (range.Length() == 1) {
      return value;
    }
    assert(value.IsSquare());
    return maths::algebra::Power(value, range.Length());
  }

  Range range;
  Element value;
};

using IntSet = Set<i64>;
using IntMatrixSet = Set<maths::algebra::matrix::IntMatrix>;

}  // namespace algo::ranges::updates
