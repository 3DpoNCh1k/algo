#pragma once

#include <algo/utils/types/fundamentals.hpp>

namespace algo::maths::algebra {
template <typename T>
T Power(T value, i64 power) {
  T result = 1;
  while (power) {
    if (power & 1) {
      result *= value;
    }
    power /= 2;
    value *= value;
  }
  return result;
}
}  // namespace algo::maths::algebra
