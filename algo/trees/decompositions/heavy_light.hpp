#pragma once

#include <algo/trees/entity/tree.hpp>
#include <algo/ranges/segment_tree/trees.hpp>

namespace algo::trees::decompositions {

template <typename Update, typename Statistics>
struct HeavyLightDecomposition {
  using SegmentTree =
      ranges::segment_tree::LazyPropagationStaticSegmentTree<Update,
                                                             Statistics>;

  using Monoid = typename Statistics::Monoid;
  using Value = typename Statistics::Value;

  explicit HeavyLightDecomposition(const Tree& tree)
      : root_(0),
        input_tree_(tree),
        segment_tree_(input_tree_.n, Monoid::Identity()) {
    AllocateMemory();
    BuildPaths();
  }

  template <typename... Args>
  void ApplyOnPath(int u, int v, Args&&... args) {
    Apply(u, v, std::forward<Args>(args)...);
  };

  template <typename... Args>
  void ApplyAtVertex(int v, Args&&... args) {
    Apply(v, v, std::forward<Args>(args)...);
  };

  Value GetFromPath(int u, int v) {
    return Get(u, v);
  }

  Value GetFromVertex(int v) {
    return Get(v, v);
  }

 private:
  void AllocateMemory() {
    parent_.resize(input_tree_.n);
    height_.resize(input_tree_.n);
    size_.resize(input_tree_.n);

    index_.resize(input_tree_.n);
    top_.resize(input_tree_.n);
  }

  void BuildPaths() {
    parent_[root_] = -1;
    height_[root_] = 0;
    CalculateVertexInfo(root_);

    top_[root_] = root_;
    index_[root_] = 0;
    next_index_ = 1;
    CalculatePaths(root_);
  }

  void CalculateVertexInfo(int v) {
    size_[v] = 1;
    for (int u : input_tree_.adjacency_list[v]) {
      if (u != parent_[v]) {
        parent_[u] = v;
        height_[u] = height_[v] + 1;
        CalculateVertexInfo(u);
        size_[v] += size_[u];
      }
    }
  }

  void CalculatePaths(int v) {
    int heavy_child = -1;
    for (int u : input_tree_.adjacency_list[v]) {
      if (u != parent_[v]) {
        if (heavy_child == -1 || size_[heavy_child] < size_[u]) {
          heavy_child = u;
        }
      }
    }
    if (heavy_child != -1) {
      top_[heavy_child] = top_[v];
      index_[heavy_child] = next_index_++;
      CalculatePaths(heavy_child);
    }
    for (int u : input_tree_.adjacency_list[v]) {
      if (u != parent_[v] && u != heavy_child) {
        top_[u] = u;
        index_[u] = next_index_++;
        CalculatePaths(u);
      }
    }
  }

  template <typename... Args>
  void Apply(int u, int v, Args... args) {
    while (top_[u] != top_[v]) {
      if (height_[top_[u]] < height_[top_[v]]) {
        std::swap(u, v);
      }
      int l = index_[top_[u]];
      int r = index_[u];
      segment_tree_.template ApplyOnRange(Update(l, r, args...));
      u = parent_[top_[u]];
    }
    if (height_[u] < height_[v]) {
      std::swap(u, v);
    }
    int l = index_[v];
    int r = index_[u];
    segment_tree_.template ApplyOnRange(Update(l, r, args...));
  };

  auto Get(int u, int v) {
    auto result = Monoid::Identity();
    while (top_[u] != top_[v]) {
      if (height_[top_[u]] < height_[top_[v]]) {
        std::swap(u, v);
      }
      int l = index_[top_[u]];
      int r = index_[u];
      result = Monoid::Combine(
          result, segment_tree_.template GetFromRange<Statistics>(l, r));
      u = parent_[top_[u]];
    }
    if (height_[u] < height_[v]) {
      std::swap(u, v);
    }
    int l = index_[v];
    int r = index_[u];

    result = Monoid::Combine(
        result, segment_tree_.template GetFromRange<Statistics>(l, r));
    return result;
  };

  int root_;
  const Tree& input_tree_;
  SegmentTree segment_tree_;

  std::vector<int> height_;
  std::vector<int> parent_;
  std::vector<int> size_;

  std::vector<int> index_;
  int next_index_;
  std::vector<int> top_;
};

template <typename Update, typename Statistics>
using HLD = HeavyLightDecomposition<Update, Statistics>;

}  // namespace algo::trees::decompositions
