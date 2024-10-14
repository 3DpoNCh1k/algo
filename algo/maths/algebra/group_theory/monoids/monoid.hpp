#pragma once

namespace algo::maths::algebra::group_theory::monoid {

// Should be unique - full template specialization
template <typename E, typename O>
struct Monoid {
  using Element = E;
  using Operation = O;

  static Element Combine(Element, Element);
  static Element Identity();
};

// Share
template <typename E, typename O>
struct AddTypeAliases {
  using Element = E;
  using Operation = O;
};
}  // namespace algo::maths::algebra::group_theory::monoid
