#pragma once

#include "algo/utils/types/fundamentals.hpp"

#include <algo/ranges/range.hpp>

#include <algo/maths/algebra/group_theory/operations/min.hpp>
#include "algo/maths/algebra/group_theory/monoids/monoid.hpp"

// include all min monoids here
#include "algo/maths/algebra/group_theory/monoids/int_min.hpp"

namespace algo::trees::segment_tree::statistics {

using namespace algo::maths::algebra::group_theory;

template <typename Element, typename RangeType = ranges::IntRange>
struct Minimum {
  using Monoid = monoid::Monoid<Element, operation::Min>;
  using Range = RangeType;
  Element value;
  Range range;

  explicit Minimum(Range range, Element value = Monoid::Identity())
      : range(range),
        value(value) {
  }
};

using IntMinimum = Minimum<i64>;

}  // namespace algo::trees::segment_tree::statistics
