#pragma once

#include <algo/maths/algebra/group_theory/monoids/monoid.hpp>
#include <algo/maths/algebra/group_theory/operations/plus.hpp>
#include <algo/utils/types/fundamentals.hpp>

namespace algo::maths::algebra::group_theory::monoid {

template <>
struct Monoid<i64, operation::Plus> : AddTypeAliases<i64, operation::Plus> {
  static i64 Combine(i64 a, i64 b) {
    return a + b;
  }
  static i64 Identity() {
    return 0;
  };
};

using IntPlus = Monoid<i64, operation::Plus>;

}  // namespace algo::maths::algebra::group_theory::monoid
