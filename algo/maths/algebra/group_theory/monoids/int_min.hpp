#pragma once

#include <limits>
#include <algo/maths/algebra/group_theory/monoids/monoid.hpp>
#include <algo/maths/algebra/group_theory/operations/min.hpp>
#include <algo/utils/types/fundamentals.hpp>

namespace algo::maths::algebra::group_theory::monoid {

template <>
struct Monoid<i64, operation::Min> : AddTypeAliases<i64, operation::Min> {
  static i64 Combine(i64 a, i64 b) {
    return std::min(a, b);
  }
  static i64 Identity() {
    return std::numeric_limits<i64>::max();
  };
};

using IntMin = Monoid<i64, operation::Min>;

}  // namespace algo::maths::algebra::group_theory::monoid
