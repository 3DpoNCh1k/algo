#include "../../header.hpp"
#include "../../algebra/algebra.hpp"

// https://codeforces.com/group/CYMPFXi8zA/contest/279284/problem/B
void Solve() {
  vector<int> least_prime_factors = LeastPrimeFactors(2e6 + 5);
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int a;
    cin >> a;
    while (a > 1) {
      cout << least_prime_factors[a] << " ";
      a /= least_prime_factors[a];
    }
    cout << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  Solve();
}
