#pragma once

#include <cassert>
#include <vector>
#include <algo/utils/types/fundamentals.hpp>
#include <algo/trees/entity/tree.hpp>
#include <algo/trees/decompositions/centroid.hpp>

using namespace algo::trees;

struct SumCentroid : decompositions::centroid::BaseCentroid {
  struct Node {
    int color = 0;
    std::array<i64, 2> sum;
    std::array<int, 2> count;
    std::vector<std::array<i64, 2>> child_sum;
    std::vector<std::array<int, 2>> child_count;
    int centroid_child_id = -1;
  };

  std::vector<Node> nodes;

  explicit SumCentroid(const Tree& tree)
      : BaseCentroid(tree),
        nodes(tree.n) {
    Calculate();
  }

  void CalculateForComponent(int c) {
    auto& node = nodes[c];
    int k = tree.adjacency_list[c].size();

    node.child_sum.resize(k);
    node.child_count.resize(k);
    node.sum[node.color] = 0;
    node.count[node.color] = 1;

    for (int i = 0; i < k; ++i) {
      int u = tree.adjacency_list[c][i];
      if (centroids[u].level > centroids[c].level) {
        Dfs(c, i, u, c, 1);

        for (int j = 0; j < 2; ++j) {
          node.sum[j] += node.child_sum[i][j];
          node.count[j] += node.child_count[i][j];
        }
      }
    }
  }

  void Dfs(int c, int child_i, int v, int p, int dist) {
    if (centroids[v].level == centroids[c].level + 1) {
      nodes[v].centroid_child_id = child_i;
    }
    nodes[c].child_count[child_i][nodes[v].color] += 1;
    nodes[c].child_sum[child_i][nodes[v].color] += dist;

    for (int u : tree.adjacency_list[v]) {
      if (u != p && centroids[u].level > centroids[c].level) {
        Dfs(c, child_i, u, v, dist + 1);
      }
    }
  }

  i64 GetSum(int v) {
    i64 result = 0;
    int color = nodes[v].color;
    int prev_child_c = -1;
    for (int i = centroids[v].parent.size() - 1; i >= 0; --i) {
      int c = centroids[v].parent[i];
      i64 d = centroids[v].distance[i];

      auto s = GetSumFromCentroidWithoutChild(c, prev_child_c, color);
      auto cnt = GetCountFromCentroidWithoutChild(c, prev_child_c, color);

      result += s + cnt * d;

      prev_child_c = nodes[c].centroid_child_id;
    }
    return result;
  }

  i64 GetSumFromCentroidWithoutChild(int c, int child, int color) {
    auto& node = nodes[c];
    return node.sum[color] - (child == -1 ? 0 : node.child_sum[child][color]);
  };

  int GetCountFromCentroidWithoutChild(int c, int child, int color) {
    auto& node = nodes[c];
    return node.count[color] -
           (child == -1 ? 0 : node.child_count[child][color]);
  };

  void ChangeColor(int v) {
    int color = nodes[v].color;
    int prev_child_c = -1;
    assert(centroids[v].parent.back() == v);
    for (int i = centroids[v].parent.size() - 1; i >= 0; --i) {
      int c = centroids[v].parent[i];
      i64 d = centroids[v].distance[i];

      auto& node = nodes[c];
      if (prev_child_c != -1) {
        // sum
        node.sum[color] -= node.child_sum[prev_child_c][color];
        node.sum[color ^ 1] -= node.child_sum[prev_child_c][color ^ 1];

        node.child_sum[prev_child_c][color] -= d;
        node.child_sum[prev_child_c][color ^ 1] += d;

        node.sum[color] += node.child_sum[prev_child_c][color];
        node.sum[color ^ 1] += node.child_sum[prev_child_c][color ^ 1];

        // count
        node.count[color] -= node.child_count[prev_child_c][color];
        node.count[color ^ 1] -= node.child_count[prev_child_c][color ^ 1];

        node.child_count[prev_child_c][color] -= 1;
        node.child_count[prev_child_c][color ^ 1] += 1;

        node.count[color] += node.child_count[prev_child_c][color];
        node.count[color ^ 1] += node.child_count[prev_child_c][color ^ 1];
      } else {
        // v's centroid
        node.count[color] -= 1;
        node.color ^= 1;
        node.count[color ^ 1] += 1;
      }
      prev_child_c = node.centroid_child_id;
    }
  };
};
