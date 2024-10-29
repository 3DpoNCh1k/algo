#pragma once

#include <vector>
#include <algo/maths/algebra/factorization/least_prime_factors.hpp>

namespace algo::maths::algebra::factorization {

std::vector<int> FindPrimesUpTo(int n) {
  auto least_primes = LeastPrimeFactors(n);
  std::vector<int> primes;
  for (int v = 2; v <= n; ++v) {
    if (least_primes[v] == v) {
      primes.push_back(v);
    }
  }
  return primes;
};

std::vector<int> Factorize(int n) {
  // 46340 = std::sqrt(std::numeric_limits<int>::max())
  static auto primes = FindPrimesUpTo(46340);
  std::vector<int> factors;
  for (int p : primes) {
    while (n % p == 0) {
      factors.push_back(p);
      n /= p;
    }
  }
  if (n > 1) {
    factors.push_back(n);
  }
  return factors;
}
}  // namespace algo::maths::algebra::factorization
