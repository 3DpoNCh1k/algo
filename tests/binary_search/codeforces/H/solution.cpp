#include <iostream>
#include "algo/binary_search/binary_search.hpp"

using namespace std;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  i64 w, h, n;
  cin >> w >> h >> n;

  auto a = algo::binary_search::FindFirstTrue(0, 2e18, [&](i64 a) {
    i64 k_row = (a / h);
    int k_col = (a / w);
    if (k_row == 0 || k_col == 0) {
      return false;
    }
    if (k_row >= n || k_col >= n) {
      return true;
    }
    return k_row * k_col >= n;
  });

  cout << a << "\n";
}
