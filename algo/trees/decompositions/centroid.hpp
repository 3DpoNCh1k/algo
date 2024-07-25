#pragma once

#include <algorithm>
#include <cassert>
#include <deque>
#include <vector>
#include "algo/binary_search/binary_search.hpp"
#include "algo/utils/bits.hpp"
#include "algo/utils/debug.hpp"
namespace algo::trees::decompositions {

template <typename Operation, typename StatisticsTuple>
struct CentroidDecomposition {
  using InputTree = std::vector<std::vector<int>>;

  int n;
  const InputTree& input_tree;

  struct Node {
    std::vector<int> min;
    std::vector<int> min_d;

    std::vector<int> centroid;
    std::vector<int> distance;
  };

  std::vector<bool> forbidden;
  std::vector<Node> nodes;
  std::vector<int> size;

  explicit CentroidDecomposition(const InputTree& tree)
      : n(tree.size()),
        input_tree(tree) {
    AllocateMemory();
    BuildCentroids();
  }

  void ApplyAtVertex(int v, const Operation& op) {

  };

  template <typename Statistics>
  Statistics GetFromVertex(int v) {
    return Get<Statistics>(v, 0);
  }

  template <typename Statistics>
  Statistics GetFromNeighborhood(int v, int d) {
    return Get<Statistics>(v, d);
  }

  int GetMin(int u, int dist) {
    dbg("GetMin", u, dist);
    int result = 1e9;
    for (int i = nodes[u].centroid.size() - 1; i >= 0; --i) {
      int c = nodes[u].centroid[i];
      int d = nodes[u].distance[i];
      dbg("GetMin", i, c, d);
      int min_from_centroid = GetMinFromCentroid(c, dist - d);
      result = std::min(result, min_from_centroid);
    }
    return result;
  }

  i64 GetSum(int v) {
    return 0;
  }

  void ChangeColor(int v) {

  };

 private:
  void AllocateMemory() {
    nodes.resize(n);
    int max_k = utils::bits::ExponentOfPowerOfTwoThatAtLeast(u64(n)) + 1;
    for (auto& node : nodes) {
      node.centroid.reserve(max_k);
      node.distance.reserve(max_k);
    }
    size.resize(n);
    forbidden.resize(n, false);
  }

  void BuildCentroids() {
    BuildRecursive(0);
    PrintNodes();
  }

  void PrintNodes() {
    dbg("PrintNodes");
    for (int v = 0; v < n; ++v) {
      const auto& node = nodes[v];
      dbg(v);
      dbg(node.centroid);
      dbg(node.distance);
    }
  }

  int BuildRecursive(int v) {
    CalculateSubtreeSize(v, -1);
    int c = FindCentroid(v, -1);
    AddCentroid(c);
    for (int u : input_tree[c]) {
      if (!forbidden[u]) {
        int child = BuildRecursive(u);
      }
    }
    return c;
  }

  void CalculateSubtreeSize(int v, int parent) {
    size[v] = 1;
    for (int u : input_tree[v]) {
      if (u != parent && !forbidden[u]) {
        CalculateSubtreeSize(u, v);
        size[v] += size[u];
      }
    }
  }

  int FindCentroid(int v, int parent) {
    int index = -1;
    for (int u : input_tree[v]) {
      if (u != parent && !forbidden[u]) {
        if (size[u] > size[v] / 2) {
          index = u;
          break;
        }
      }
    }
    if (index == -1) {
      return v;
    }
    size[v] -= size[index];
    size[index] += size[v];
    return FindCentroid(index, v);
  }

  void AddCentroid(int c) {
    dbg("AddCentroid", c);
    forbidden[c] = true;
    // DFS(c, -1, prev_centroid, c, 0);
    std::deque<std::pair<int, int>> q;
    auto& centroid_node = nodes[c];
    q.emplace_back(c, -1);
    for (int dist = 0; !q.empty(); dist++) {
      auto min_value = std::min_element(q.begin(), q.end())->first;
      if (dist > 0) {
        min_value = std::min(min_value, centroid_node.min.back());
      }
      centroid_node.min.push_back(min_value);
      centroid_node.min_d.push_back(dist);
      std::deque<std::pair<int, int>> next_q;
      for (auto [v, parent] : q) {
        nodes[v].centroid.push_back(c);
        nodes[v].distance.push_back(dist);
        for (int u : input_tree[v]) {
          if (u != parent && !forbidden[u]) {
            next_q.emplace_back(u, v);
          }
        }
      }
      q = next_q;
    }
  }

  // void DFS(int v, int parent, int forbidden, int c, int d) {
  //   auto& node = nodes[v];
  //   node.centroid.push_back(c);
  //   node.distance.push_back(d);
  //   for (int u : input_tree[v]) {
  //     if (u != parent && u != forbidden) {
  //       DFS(u, v, forbidden, c, d + 1);
  //     }
  //   }
  // }

  int GetMinFromCentroid(int c, int dist) {
    if (dist < 0) {
      return 1e9;
    }
    const auto& node = nodes[c];
    int node_max_dist = node.min.size() - 1;
    int index = std::min(dist, node_max_dist);
    return node.min[index];
    // int index =
    //     binary_search::FindLastTrue(0, node.min_d.size() - 1, [&](int i) {
    //       node.min_d[i] <= dist;
    //     });

    // return index == -1? 1e9: node.min[index];
  }

  template <typename Statistics>
  Statistics Get(int u, int dist) {
    return Statistics{};
  }
};

template <typename Operation, typename StatisticsTuple>
using Centroids = CentroidDecomposition<Operation, StatisticsTuple>;
}  // namespace algo::trees::decompositions
