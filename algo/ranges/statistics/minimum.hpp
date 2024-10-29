#pragma once

#include <algo/utils/types/fundamentals.hpp>

#include <algo/ranges/range.hpp>

#include <algo/maths/algebra/group_theory/operations/min.hpp>
#include <algo/maths/algebra/group_theory/monoids/monoid.hpp>

// include all min monoids here
#include <algo/maths/algebra/group_theory/monoids/int_min.hpp>

namespace algo::ranges::statistics {

using namespace algo::maths::algebra::group_theory;

template <typename ValueType>
struct Minimum {
  using Value = ValueType;
  using Monoid = monoid::Monoid<Value, operation::Min>;
};

using IntMinimum = Minimum<i64>;

}  // namespace algo::ranges::statistics
