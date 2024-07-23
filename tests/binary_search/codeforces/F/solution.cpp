#include <iostream>
#include <vector>
#include "algo/binary_search/binary_search.hpp"

using namespace std;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  for (int q = 0; q < k; ++q) {
    int v;
    cin >> v;

    auto i_less_or_equal =
        algo::binary_search::FindLastTrue(0, n - 1, [&](int i) {
          return a[i] <= v;
        });

    int index = i_less_or_equal;
    if (i_less_or_equal == -1) {
      index = 0;
    } else {
      int i_greater = i_less_or_equal + 1;
      if (i_greater < n &&
          std::abs(a[i_greater] - v) < std::abs(a[i_less_or_equal] - v)) {
        index = i_greater;
      }
    }

    cout << a[index] << "\n";
  }
}
