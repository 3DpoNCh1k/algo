#pragma once

#include <algo/utils/types.hpp>
#include <algo/maths/algebra/gcd.hpp>
#include <vector>

namespace algo::maths::algebra {
using utils::i64;

// a*x = 1 (mod m) ~> a*x = 1 + m*y ~> a*x - m*y = 1
i64 ModularInverse(i64 a, i64 m) {
  i64 x, y;
  i64 g = ExtendedGCD(a, m, x, y);
  if (g != 1) {
    // no solution
    return -1;
  }
  return ((x % m) + m) % m;
}

std::vector<int> PrimeModularInverses(int m) {
  std::vector<int> inv(m);
  inv[1] = 1;
  // m (mod i) = m - (m/i)*i
  // apply mod m
  // m (mod i) = -(m/i)*i
  // multiply by inv[m (mod i)] and by inv[i]
  // inv[i] = -(m/i) * inv[m (mod i)]
  for (int i = 2; i < m; ++i) {
    inv[i] = m - (((m / i) * inv[m % i]) % m);
  }
  return inv;
}
}  // namespace algo::maths::algebra
