#pragma once

#include <algo/utils/types.hpp>

namespace algo::maths::algebra {
using utils::i64;
// a*x + b*y = g
i64 ExtendedGCD(i64 a, i64 b, i64& x, i64& y) {
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }
  i64 x1, y1;
  //  (b%a)*x1 + a*y1 = g
  //  a*y1 + (b - (b/a) * a)*x1 = g
  //  a*(y1 - (b/a)*x1) + b*(x1) = g
  i64 g = ExtendedGCD(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
  return g;
}

i64 GCD(i64 a, i64 b) {
  i64 x, y;
  return ExtendedGCD(a, b, x, y);
}
}  // namespace algo::maths::algebra
