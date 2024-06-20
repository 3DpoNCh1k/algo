#pragma once

#include <vector>
#include "../utils/types.hpp"


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

std::vector<int> LeastPrimeFactors(int n) {
  std::vector<int> least_primes(n + 1);
  std::vector<int> primes;
  for (int i = 2; i <= n; ++i) {
    if (least_primes[i] == 0) {
      least_primes[i] = i;
      primes.push_back(i);
    }
    for (int j = 0; j < (int)primes.size() && primes[j] <= least_primes[i] &&
                    i * primes[j] <= n;
         ++j) {
      least_primes[i * primes[j]] = primes[j];
    }
  }
  return least_primes;
}

const i32 MOD = 1e9 + 7;

i64 AddMOD(i64 a, i64 b) {
  i64 res = a + b;
  return res < MOD ? res : res - MOD;
}

int MultiplyMOD(int a, int b) {
  i64 res = a * b;
  return res % MOD;
}

i64 MultiplyMOD(i64 a, i64 b) {
  // choose appropriate compiler for __int128
  __int128 res = a * b;
  return res % MOD;
}
