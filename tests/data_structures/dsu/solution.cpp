#include <iostream>
#include <algo/data_structures/dsu.hpp>

int main() {
  int n, q;
  std::cin >> n >> q;

  algo::data_structures::DSU dsu(n);

  for (int i = 0; i < q; ++i) {
    int t, u, v;
    std::cin >> t >> u >> v;
    if (t == 0) {
      dsu.Merge(u, v);
    } else {
      std::cout << (dsu.Find(v) == dsu.Find(u) ? 1 : 0) << std::endl;
    }
  }
}
