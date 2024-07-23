#pragma once

#include <vector>

namespace algo::data_structures {
struct DisjointSetUnion {
  explicit DisjointSetUnion(int n) {
    parent_.resize(n), height_.resize(n, 1);
    for (int i = 0; i < n; ++i) {
      parent_[i] = i;
    }
  }

  int Find(int v) {
    if (parent_[v] == v) {
      return v;
    }
    return parent_[v] = Find(parent_[v]);
  }

  void Merge(int u, int v) {
    int parent_u = Find(u);
    int parent_v = Find(v);
    if (parent_u == parent_v) {
      return;
    }
    if (height_[parent_u] < height_[parent_v]) {
      std::swap(parent_u, parent_v);
    }
    parent_[parent_v] = parent_u;
    if (height_[parent_u] == height_[parent_v]) {
      height_[parent_u]++;
    }
  }

 private:
  std::vector<int> parent_, height_;
};

using DSU = DisjointSetUnion;

}  // namespace algo::data_structures
