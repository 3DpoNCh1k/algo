#pragma once

#include <algo/maths/algebra/group_theory/groups/group.hpp>
#include <algo/maths/algebra/group_theory/monoids/int_plus.hpp>
#include <algo/maths/algebra/group_theory/operations/plus.hpp>
#include <algo/utils/types/fundamentals.hpp>

namespace algo::maths::algebra::group_theory::group {

template <>
struct Group<i64, operation::Plus> : monoid::IntPlus {
  static constexpr bool IsAbelian = true;
  static i64 Inverse(i64 value) {
    return -value;
  }
};

using IntPlus = Group<i64, operation::Plus>;

}  // namespace algo::maths::algebra::group_theory::group
