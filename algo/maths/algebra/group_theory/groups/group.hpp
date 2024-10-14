#pragma once

#include <algo/maths/algebra/group_theory/monoids/monoid.hpp>

namespace algo::maths::algebra::group_theory::group {

// Should be unique - full template specialization
template <typename E, typename O>
struct Group : monoid::Monoid<E, O> {
  using Element = E;
  using Operation = O;

  static Element Inverse(Element);
};
}  // namespace algo::maths::algebra::group_theory::group
