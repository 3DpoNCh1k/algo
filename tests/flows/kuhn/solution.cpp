#include <iostream>
#include <algo/flows/kuhn.hpp>

int main() {
  int l, r, m;
  std::cin >> l >> r >> m;

  std::vector<std::vector<int>> left(l);
  for (int edge = 0; edge < m; ++edge) {
    int u, v;
    std::cin >> u >> v;
    left[u].push_back(v);
  }

  auto kuhn = algo::flows::Kuhn(left, r);
  std::vector<int> ret_mt;
  int k = kuhn.Solve(ret_mt);
  std::cout << k << std::endl;
  for (int v = 0; v < r; ++v) {
    if (ret_mt[v] != -1) {
      std::cout << ret_mt[v] << " " << v << std::endl;
    }
  }
}
