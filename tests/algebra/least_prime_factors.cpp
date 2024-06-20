#include <iostream>
#include <vector>

#include <algo/algebra/algebra.hpp>

// https://codeforces.com/group/CYMPFXi8zA/contest/279284/problem/B
void Solve() {
  std::vector<int> least_prime_factors = LeastPrimeFactors(2e6 + 5);
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    int a;
    std::cin >> a;
    while (a > 1) {
      std::cout << least_prime_factors[a] << " ";
      a /= least_prime_factors[a];
    }
    std::cout << "\n";
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  Solve();
}
