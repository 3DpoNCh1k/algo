#pragma once

#include <vector>
#include "algo/utils/bits.hpp"

namespace algo::trees {
struct LowestCommonAncestor {
  using Graph = std::vector<std::vector<int>>;

  explicit LowestCommonAncestor(const std::vector<int>& parent)
      : n_(parent.size()) {
    auto max_power = utils::bits::IndexOfMostSignificantBit(
        utils::bits::PowerOfTwoThatAtLeast(u64(n_)));

    k_ancestor_ = max_power + 1;

    ancestors_.assign(n_, std::vector<int>(k_ancestor_, -1));
    graph_.resize(n_);

    for (int v = 0; v < n_; ++v) {
      if (parent[v] == -1) {
        root_ = v;
        ancestors_[root_][0] = root_;
      } else {
        ancestors_[v][0] = parent[v];
        graph_[parent[v]].push_back(v);
      }
    }
  }

  void DFS(int v) {
    t_in_[v] = t_++;
    for (int i = 1; i < k_ancestor_; ++i) {
      ancestors_[v][i] = ancestors_[ancestors_[v][i - 1]][i - 1];
    }
    for (int u : graph_[v]) {
      height_[u] = height_[v] + 1;
      DFS(u);
    }
    t_out_[v] = t_++;
  }

  void Solve() {
    t_ = 0;
    t_in_.resize(n_);
    t_out_.resize(n_);
    height_.resize(n_);
    height_[root_] = 0;
    DFS(root_);
  }

  int GetLCA(int u, int v) {
    if (t_in_[u] > t_in_[v]) {
      std::swap(u, v);
    }
    if (t_out_[u] > t_out_[v]) {
      return u;
    }
    for (int i = k_ancestor_ - 1; i >= 0; --i) {
      int p = ancestors_[u][i];
      if (t_out_[p] < t_out_[v]) {
        u = p;
      }
    }
    return ancestors_[u][0];
  }

 private:
  int n_;
  int k_ancestor_;
  int root_;
  Graph graph_;
  std::vector<std::vector<int>> ancestors_;
  std::vector<int> height_;
  std::vector<int> t_in_, t_out_;
  int t_;
};

using LCA = LowestCommonAncestor;
}  // namespace algo::trees
