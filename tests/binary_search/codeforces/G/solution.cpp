#include <iostream>
#include <vector>
#include "algo/binary_search/binary_search.hpp"

using namespace std;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, x, y;
  cin >> n >> x >> y;

  auto t = algo::binary_search::FindFirstTrue(0, 1e18, [&](i64 t) {
    t -= std::min(x, y);
    i64 k = 1;
    k += t / x;
    k += t / y;
    return k >= n;
  });

  cout << t << "\n";
}
