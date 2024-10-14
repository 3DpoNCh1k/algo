#pragma once

#include <algo/maths/algebra/group_theory/monoids/monoid.hpp>

namespace algo::maths::algebra::group_theory::group {

// Should be unique - full template specialization
template <typename E, typename Op>
struct Group : monoid::Monoid<E, Op> {
  using Element = E;
  using Operation = Op;

  static Element Inverse(Element);
};
}  // namespace algo::maths::algebra::group_theory::group
