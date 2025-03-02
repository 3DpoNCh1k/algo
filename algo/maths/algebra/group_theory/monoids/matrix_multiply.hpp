#pragma once


#include <algo/maths/algebra/group_theory/monoids/monoid.hpp>
#include <algo/maths/algebra/group_theory/operations/multiply.hpp>
#include <algo/maths/algebra/matrix/matrix.hpp>

namespace algo::maths::algebra::group_theory::monoid {

template <typename T>
struct Monoid<matrix::Matrix<T>, operation::Multiply> : AddTypeAliases<i64, operation::Multiply> {
  static matrix::Matrix<T> Combine(matrix::Matrix<T> a, matrix::Matrix<T> b) {
    return a * b;
  }
  static matrix::Matrix<T> Identity() {
    return matrix::Matrix<T>::Identity();
  };
};

using IntMatrixMultiply = Monoid<matrix::IntMatrix, operation::Multiply>;

}  // namespace algo::maths::algebra::group_theory::monoid
