#include <iostream>
#include <vector>

#include <algo/trees/hld.hpp>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  int n;
  std::cin >> n;
  std::vector<std::vector<int>> g(n);
  for (int e = 0; e < n - 1; ++e) {
    int u, v;
    std::cin >> u >> v;
    --u;
    --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  auto hld = algo::trees::HLD(g);

  int m;
  std::cin >> m;
  for (int q = 0; q < m; ++q) {
    std::string command;
    std::cin >> command;
    if (command == "+") {
      int v, u, d;
      std::cin >> v >> u >> d;
      --v;
      --u;
      hld.AddOnPath(u, v, d);
    } else if (command == "?") {
      int v;
      std::cin >> v;
      --v;
      std::cout << hld.QueryOnPath(v, v) << "\n";
    } else {
      std::abort();
    }
  }
}
