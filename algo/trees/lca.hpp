#pragma once

#include <vector>
#include <algo/trees/entity/tree.hpp>
#include <algo/utils/bits.hpp>

namespace algo::trees {
struct LowestCommonAncestor {
  explicit LowestCommonAncestor(const std::vector<int>& parent)
      : tree_(parent.size()) {
    auto max_power = utils::bits::ExponentOfPowerOfTwoThatAtLeast(u64(tree_.n));

    k_ancestor_ = max_power + 1;

    ancestors_.assign(tree_.n, std::vector<int>(k_ancestor_, -1));

    for (int v = 0; v < tree_.n; ++v) {
      if (parent[v] == -1) {
        root_ = v;
        ancestors_[root_][0] = root_;
      } else {
        ancestors_[v][0] = parent[v];
        tree_.AddEdge(parent[v], v);
      }
    }
  }

  void DFS(int v, int parent = -1) {
    t_in_[v] = t_++;
    for (int i = 1; i < k_ancestor_; ++i) {
      ancestors_[v][i] = ancestors_[ancestors_[v][i - 1]][i - 1];
    }
    for (int u : tree_.adjacency_list[v]) {
      if (u == parent) {
        continue;
      }
      height_[u] = height_[v] + 1;
      DFS(u, v);
    }
    t_out_[v] = t_++;
  }

  void Solve() {
    t_ = 0;
    t_in_.resize(tree_.n);
    t_out_.resize(tree_.n);
    height_.resize(tree_.n);
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
  int k_ancestor_;
  int root_;
  Tree tree_;
  std::vector<std::vector<int>> ancestors_;
  std::vector<int> height_;
  std::vector<int> t_in_, t_out_;
  int t_;
};

using LCA = LowestCommonAncestor;
}  // namespace algo::trees
