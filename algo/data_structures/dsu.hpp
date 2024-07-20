#pragma once

#include <vector>

namespace algo::data_structures {
struct DisjointSetUnion {
  std::vector<int> parent, height;

  explicit DisjointSetUnion(int n) {
    parent.resize(n), height.resize(n, 1);
    for (int i = 0; i < n; ++i) {
      parent[i] = i;
    }
  }

  int Find(int v) {
    if (parent[v] == v) {
      return v;
    }
    return parent[v] = Find(parent[v]);
  }

  void Merge(int u, int v) {
    int parent_u = Find(u);
    int parent_v = Find(v);
    if (parent_u == parent_v) {
      return;
    }
    if (height[parent_u] < height[parent_v]) {
      std::swap(parent_u, parent_v);
    }
    parent[parent_v] = parent_u;
    if (height[parent_u] == height[parent_v]) {
      height[parent_u]++;
    }
  }
};

using DSU = DisjointSetUnion;

}  // namespace algo::data_structures
