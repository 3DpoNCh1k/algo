#include <cstdlib>
#include <iostream>
#include "algo/trees/linkcut.hpp"


int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  auto linkcut = algo::trees::LinkCut(n);
  for(int q = 0; q < m; ++q) {
    std::string command;
    std::cin >> command;
    if (command == "link") {
      int u, v;
      std::cin >> u >> v;
      linkcut.Link(u, v);
    } else if (command == "cut") {
      int u, v;
      std::cin >> u >> v;
      linkcut.Cut(u, v);
    } else if (command == "connected") {
      int u, v;
      std::cin >> u >> v;
      std::cout << linkcut.Connected(u, v) << "\n";
    }
  }
}