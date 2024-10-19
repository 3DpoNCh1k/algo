#pragma once

#include <algorithm>
#include <cassert>
#include <deque>
#include <vector>
#include "algo/trees/entity/tree.hpp"
#include "algo/trees/decompositions/centroid.hpp"

using namespace algo::trees;

struct MinCentroid : decompositions::centroid::BaseCentroid {
  struct Node {
    std::vector<int> min;
  };

  std::vector<Node> nodes;

  explicit MinCentroid(const Tree& tree)
      : BaseCentroid(tree),
        nodes(tree.n) {
    Calculate();
  }

  void CalculateForComponent(int c) {
    auto& node = nodes[c];

    using Queue = std::deque<std::pair<int, int>>;
    Queue q;
    q.emplace_back(c, -1);
    for (int dist = 0; !q.empty(); dist++) {
      auto min_value = std::min_element(q.begin(), q.end())->first;
      if (dist > 0) {
        min_value = std::min(min_value, node.min.back());
      }
      node.min.push_back(min_value);

      Queue next_q;
      for (auto [v, parent] : q) {
        for (int u : tree.adjacency_list[v]) {
          if (u != parent && centroids[u].level > centroids[c].level) {
            next_q.emplace_back(u, v);
          }
        }
      }
      q = next_q;
    }
  }

  int GetMin(int u, int dist) {
    int result = 1e9;
    assert(centroids[u].parent.back() == u);
    for (int i = centroids[u].parent.size() - 1; i >= 0; --i) {
      int c = centroids[u].parent[i];
      int d = centroids[u].distance[i];

      int min_from_centroid = GetMinFromCentroid(c, dist - d);
      result = std::min(result, min_from_centroid);
    }
    return result;
  }

  int GetMinFromCentroid(int c, int dist) {
    if (dist < 0) {
      return 1e9;
    }
    const auto& node = nodes[c];
    int node_max_dist = node.min.size() - 1;
    int index = std::min(dist, node_max_dist);
    return node.min[index];
  }
};
