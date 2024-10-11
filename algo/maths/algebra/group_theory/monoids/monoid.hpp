#pragma once

namespace algo::maths::algebra::group_theory::monoid {

// Should be unique - full template specialization
template <typename E, typename Op>
struct Monoid {
  using Element = E;
  using Operation = Op;

  static Element Combine(Element, Element);
  static Element Identity();
};

// Share
template <typename E, typename Op>
struct AddTypeAliases {
  using Element = E;
  using Operation = Op;
};
}  // namespace algo::maths::algebra::group_theory::monoid
