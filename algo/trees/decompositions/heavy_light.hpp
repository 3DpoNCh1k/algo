#pragma once

#include <algo/trees/segment_tree/trees.hpp>
#include "algo/utils/debug.hpp"

namespace algo::trees::decompositions {

template <typename Operation, typename StatisticsTuple>
struct HeavyLightDecomposition {
  using SegmentTree =
      segment_tree::LazyPropagationStaticSegmentTree<Operation,
                                                     StatisticsTuple>;

  using InputTree = std::vector<std::vector<int>>;

  int root;
  int n;
  const InputTree& input_tree;
  SegmentTree segment_tree;

  std::vector<int> height;
  std::vector<int> parent;
  std::vector<int> size;

  std::vector<int> index;
  int next_index;
  std::vector<int> top;

  explicit HeavyLightDecomposition(const InputTree& tree)
      : root(0),
        n(tree.size()),
        input_tree(tree),
        segment_tree(n) {
    AllocateMemory();
    BuildPaths();
  }

  void ApplyOnPath(int u, int v, const Operation& op) {
    Apply(u, v, op);
  };

  void ApplyAtVertex(int v, const Operation& op) {
    Apply(v, v, op);
  };

  template <typename Statistics>
  Statistics GetFromPath(int u, int v) {
    return Get<Statistics>(u, v);
  }

  template <typename Statistics>
  Statistics GetFromVertex(int v) {
    return Get<Statistics>(v, v);
  }

 private:
  void Apply(int u, int v, const Operation& op) {
    while (top[u] != top[v]) {
      if (height[top[u]] < height[top[v]]) {
        std::swap(u, v);
      }
      int l = index[top[u]];
      int r = index[u];
      dbg("Apply.Different paths", l, r);
      segment_tree.template ApplyOnRange(l, r, op);
      u = parent[top[u]];
    }
    if (height[u] < height[v]) {
      std::swap(u, v);
    }
    int l = index[v];
    int r = index[u];
    dbg("Apply.Same path", l, r);
    segment_tree.template ApplyOnRange(l, r, op);
  };

  template <typename Statistics>
  Statistics Get(int u, int v) {
    dbg("Get", u, v);
    auto result = Statistics{};
    while (top[u] != top[v]) {
      if (height[top[u]] < height[top[v]]) {
        std::swap(u, v);
      }
      int l = index[top[u]];
      int r = index[u];
      dbg("Get.Different paths", l, r);
      result =
          result.Merge(segment_tree.template GetFromRange<Statistics>(l, r));
      u = parent[top[u]];
    }
    if (height[u] < height[v]) {
      std::swap(u, v);
    }
    int l = index[v];
    int r = index[u];
    dbg("Get.Same path", l, r);
    result = result.Merge(segment_tree.template GetFromRange<Statistics>(l, r));
    return result;
  };

  void AllocateMemory() {
    parent.resize(n);
    height.resize(n);
    size.resize(n);

    index.resize(n);
    top.resize(n);
  }

  void BuildPaths() {
    parent[root] = -1;
    height[root] = 0;
    CalculateVertexInfo(root);
    dbg(parent);
    dbg(height);
    dbg(size);

    top[root] = root;
    index[root] = 0;
    next_index = 1;
    CalculatePaths(root);

    dbg(index);
    dbg(top);
  }

  void CalculateVertexInfo(int v) {
    size[v] = 1;
    for (int u : input_tree[v]) {
      if (u != parent[v]) {
        parent[u] = v;
        height[u] = height[v] + 1;
        CalculateVertexInfo(u);
        size[v] += size[u];
      }
    }
  }

  void CalculatePaths(int v) {
    int heavy_child = -1;
    for (int u : input_tree[v]) {
      if (u != parent[v]) {
        if (heavy_child == -1 || size[heavy_child] < size[u]) {
          heavy_child = u;
        }
      }
    }
    if (heavy_child != -1) {
      top[heavy_child] = top[v];
      index[heavy_child] = next_index++;
      CalculatePaths(heavy_child);
    }
    for (int u : input_tree[v]) {
      if (u != parent[v] && u != heavy_child) {
        top[u] = u;
        index[u] = next_index++;
        CalculatePaths(u);
      }
    }
  }
};

template <typename Operation, typename StatisticsTuple>
using HLD = HeavyLightDecomposition<Operation, StatisticsTuple>;

}  // namespace algo::trees::decompositions
