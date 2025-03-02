#pragma once

#include <algo/utils/types/fundamentals.hpp>
#include <algo/maths/algebra/matrix/matrix.hpp>
#include <cassert>

namespace algo::maths::algebra {

namespace details {
  template <typename T>
  T Power(T init_value, T value, i64 power) {
    T result = std::move(init_value);
    while (power) {
      if (power & 1) {
        result *= value;
      }
      power /= 2;
      value *= value;
    }
    return result;
  }
}

template <typename T>
T Power(T value, i64 power) {
  return details::Power(T(1), std::move(value), power);
}

template<typename T>
matrix::Matrix<T> Power(matrix::Matrix<T> matrix, i64 power) {
  assert(matrix.IsSquare());
  return details::Power(matrix::Matrix<T>::One(matrix.k_row), std::move(matrix), power);
}
}  // namespace algo::maths::algebra
