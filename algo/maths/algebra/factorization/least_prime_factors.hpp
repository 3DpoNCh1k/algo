#pragma once

#include <vector>

namespace algo::maths::algebra::factorization {
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
}  // namespace algo::maths::algebra::factorization
