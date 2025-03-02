#pragma once

#include <algo/utils/types/fundamentals.hpp>

#include <algo/ranges/range.hpp>

#include <algo/maths/algebra/group_theory/operations/multiply.hpp>
#include <algo/maths/algebra/group_theory/monoids/monoid.hpp>

// include all min monoids here
#include <algo/maths/algebra/group_theory/monoids/matrix_multiply.hpp>
#include "algo/maths/algebra/matrix/matrix.hpp"

namespace algo::ranges::statistics {

namespace gt = algo::maths::algebra::group_theory;

template <typename ValueType>
struct Multiplication {
  using Value = ValueType;
  using Monoid = gt::monoid::Monoid<Value, gt::operation::Multiply>;
};

using IntMatrixMultiplication =
    Multiplication<maths::algebra::matrix::IntMatrix>;

}  // namespace algo::ranges::statistics
