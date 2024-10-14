#pragma once

#include <cassert>

#include "algo/maths/algebra/group_theory/groups/group.hpp"
#include "algo/utils/types/fundamentals.hpp"

#include <algo/ranges/range.hpp>

#include <algo/maths/algebra/group_theory/operations/plus.hpp>
#include "algo/maths/algebra/group_theory/monoids/monoid.hpp"

// include all plus monoids here
#include "algo/maths/algebra/group_theory/monoids/int_plus.hpp"

// include all plus groups here
#include "algo/maths/algebra/group_theory/groups/int_plus.hpp"

namespace algo::trees::segment_tree::statistics {

using namespace algo::maths::algebra::group_theory;

template <typename ValueType>
struct Sum {
  using Value = ValueType;
  using Monoid = monoid::Monoid<Value, operation::Plus>;
  using Group = group::Group<Value, operation::Plus>;
};

using IntSum = Sum<i64>;

}  // namespace algo::trees::segment_tree::statistics
