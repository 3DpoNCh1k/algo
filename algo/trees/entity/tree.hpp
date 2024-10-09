#pragma once

#include <vector>

namespace algo::trees {

struct Tree {
  int n;
  std::vector<std::vector<int>> adjacency_list;

  explicit Tree(int n)
      : n(n) {
    adjacency_list.resize(n);
  }

  void AddEdge(int v, int u) {
    adjacency_list[v].push_back(u);
    adjacency_list[u].push_back(v);
  }
};

}  // namespace algo::trees
