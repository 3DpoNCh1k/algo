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
    int pu = Find(u);
    int pv = Find(v);
    if (pu == pv) {
      return;
    }
    if (height[pu] < height[pv]) {
      parent[pu] = pv;
    } else {
      parent[pv] = pu;
      if (height[pu] == height[pv]) {
        height[pu]++;
      }
    }
  }
};

using DSU = DisjointSetUnion;

}  // namespace algo::data_structures
