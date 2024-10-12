#pragma once

#include <cassert>

#include "algo/utils/types/fundamentals.hpp"

#include <algo/ranges/range.hpp>

#include <algo/maths/algebra/group_theory/operations/plus.hpp>
#include "algo/maths/algebra/group_theory/monoids/monoid.hpp"

// include all plus monoids here
#include "algo/maths/algebra/group_theory/monoids/int_plus.hpp"

namespace algo::trees::segment_tree::statistics {

using namespace algo::maths::algebra::group_theory;

template <typename Element, typename RangeType = ranges::IntRange>
struct Sum {
  using Monoid = monoid::Monoid<Element, operation::Plus>;
  using Range = RangeType;
  Element value;
  Range range;

  explicit Sum(Range range, Element value = Monoid::Identity())
      : range(range),
        value(value) {
  }
};

using IntSum = Sum<i64>;

}  // namespace algo::trees::segment_tree::statistics
