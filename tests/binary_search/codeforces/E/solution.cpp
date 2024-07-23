#include <algorithm>
#include <iostream>
#include <vector>
#include "algo/binary_search/binary_search.hpp"

using namespace std;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  sort(a.begin(), a.end());
  int k;
  cin >> k;
  for (int q = 0; q < k; ++q) {
    int l, r;
    cin >> l >> r;

    auto k_less_or_equal_r =
        algo::binary_search::FindLastTrue(0, n - 1, [&](int i) {
          return a[i] <= r;
        });

    auto k_less_l = algo::binary_search::FindLastTrue(0, n - 1, [&](int i) {
      return a[i] < l;
    });

    cout << (k_less_or_equal_r - k_less_l) << " ";
  }
}
