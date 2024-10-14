#pragma once

#include <algorithm>
#include <cassert>
#include <deque>
#include <vector>
#include "algo/binary_search/binary_search.hpp"
#include "algo/utils/bits.hpp"
#include "algo/trees/entity/tree.hpp"
#include "algo/debug/debug.hpp"
namespace algo::trees::decompositions {

template <typename Operation, typename StatisticsTuple>
struct CentroidDecomposition {
  const Tree& input_tree;
  int root_centroid = -1;
  struct Node {
    // min
    std::vector<int> min;
    std::vector<int> min_d;
    // min

    // sum
    int color = 0;
    std::vector<i64> sum;
    std::vector<int> count;
    std::vector<std::vector<i64>> child_sum;
    std::vector<std::vector<int>> child_count;
    // sum

    std::vector<int> centroid_children;
    std::vector<int> tree_children;
    int next_centroid = -1;
    int centroid_child_id = -1;

    std::vector<int> centroid;
    std::vector<int> distance;
  };

  std::vector<bool> forbidden;
  std::vector<Node> nodes;
  std::vector<int> size;

  explicit CentroidDecomposition(const Tree& tree)
      : input_tree(tree) {
    AllocateMemory();
    BuildCentroids();
    PrintNodes();
    CalculateDp();
    PrintDps();
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
    debug("GetMin", u, dist);
    int result = 1e9;
    for (int i = nodes[u].centroid.size() - 1; i >= 0; --i) {
      int c = nodes[u].centroid[i];
      int d = nodes[u].distance[i];
      debug("GetMin", i, c, d);
      int min_from_centroid = GetMinFromCentroid(c, dist - d);
      result = std::min(result, min_from_centroid);
    }
    return result;
  }

  i64 GetSum(int v) {
    debug("GetSum", v);
    i64 result = 0;
    int color = nodes[v].color;
    int prev_child_c = -1;
    for (int i = nodes[v].centroid.size() - 1; i >= 0; --i) {
      int c = nodes[v].centroid[i];
      i64 d = nodes[v].distance[i];
      debug(c, d, prev_child_c, color);

      auto s = GetSumFromCentroidExceptCentroidChild(c, prev_child_c, color);
      auto cnt =
          GetCountFromCentroidExceptCentroidChild(c, prev_child_c, color);

      result += s + cnt * d;
      debug(s, cnt, result);

      prev_child_c = nodes[c].centroid_child_id;
    }
    return result;
  }

  i64 GetSumFromCentroidExceptCentroidChild(int c, int child, int color) {
    debug("GetSumFromCentroidExceptCentroidChild", c, child, color);
    auto& node = nodes[c];
    debug(node.sum);
    debug(node.child_sum);
    return node.sum[color] - (child == -1 ? 0 : node.child_sum[child][color]);
  };

  int GetCountFromCentroidExceptCentroidChild(int c, int child, int color) {
    debug("GetCountFromCentroidExceptCentroidChild", c, child, color);
    auto& node = nodes[c];
    debug(node.count);
    debug(node.child_count);
    return node.count[color] -
           (child == -1 ? 0 : node.child_count[child][color]);
  };

  void ChangeColor(int v) {
    debug("ChangeColor", v);
    int color = nodes[v].color;
    int prev_child_c = -1;
    for (int i = nodes[v].centroid.size() - 1; i >= 0; --i) {
      int c = nodes[v].centroid[i];
      i64 d = nodes[v].distance[i];

      debug(c, d, prev_child_c);

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

        debug("after");
        debug(node.child_sum[prev_child_c]);
        debug(node.child_count[prev_child_c]);
        debug(node.sum);
        debug(node.count)
      }

      prev_child_c = nodes[c].centroid_child_id;
    }

    nodes[v].count[color] -= 1;
    nodes[v].color ^= 1;
    nodes[v].count[color ^ 1] += 1;
  };

 private:
  void AllocateMemory() {
    nodes.resize(input_tree.n);
    int max_k =
        utils::bits::ExponentOfPowerOfTwoThatAtLeast(u64(input_tree.n)) + 1;
    for (auto& node : nodes) {
      node.centroid.reserve(max_k);
      node.distance.reserve(max_k);
      node.sum.resize(2);
      node.count.resize(2);
    }
    size.resize(input_tree.n);
    forbidden.resize(input_tree.n, false);
  }

  void BuildCentroids() {
    root_centroid = BuildRecursive(0, -1, -1);
  }

  void PrintNodes() {
    debug("PrintNodes");
    debug(root_centroid);
    for (int v = 0; v < input_tree.n; ++v) {
      const auto& node = nodes[v];
      debug(v);
      debug(node.centroid);
      debug(node.distance);
      debug(node.centroid_children);
    }
  }

  int BuildRecursive(int v, int prev_centroid, int id) {
    CalculateSubtreeSize(v, -1);
    int c = FindCentroid(v, -1);
    nodes[c].next_centroid = prev_centroid;
    nodes[c].centroid_child_id = id;
    AddCentroid(c);
    for (int u : input_tree.adjacency_list[c]) {
      if (!forbidden[u]) {
        int child = BuildRecursive(u, c, nodes[c].centroid_children.size());
        nodes[c].centroid_children.push_back(child);
        nodes[c].tree_children.push_back(u);
      }
    }
    return c;
  }

  void CalculateSubtreeSize(int v, int parent) {
    size[v] = 1;
    for (int u : input_tree.adjacency_list[v]) {
      if (u != parent && !forbidden[u]) {
        CalculateSubtreeSize(u, v);
        size[v] += size[u];
      }
    }
  }

  int FindCentroid(int v, int parent) {
    int index = -1;
    for (int u : input_tree.adjacency_list[v]) {
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
    debug("AddCentroid", c);
    forbidden[c] = true;
    // DFS(c, -1, prev_centroid, c, 0);
    std::deque<std::pair<int, int>> q;
    auto& centroid_node = nodes[c];
    q.emplace_back(c, -1);
    for (int dist = 0; !q.empty(); dist++) {
      // min
      auto min_value = std::min_element(q.begin(), q.end())->first;
      if (dist > 0) {
        min_value = std::min(min_value, centroid_node.min.back());
      }
      centroid_node.min.push_back(min_value);
      centroid_node.min_d.push_back(dist);
      // min

      std::deque<std::pair<int, int>> next_q;
      for (auto [v, parent] : q) {
        nodes[v].centroid.push_back(c);
        nodes[v].distance.push_back(dist);
        for (int u : input_tree.adjacency_list[v]) {
          if (u != parent && !forbidden[u]) {
            next_q.emplace_back(u, v);
          }
        }
      }
      q = next_q;
    }
  }

  void PrintDps() {
    debug("PrintDps");
    for (int v = 0; v < input_tree.n; ++v) {
      const auto& node = nodes[v];
      debug(v);
      debug(node.color);
      debug(node.sum);
      debug(node.count);
      debug(node.next_centroid);
      debug(node.centroid_child_id);
      for (int i = 0; i < node.centroid_children.size(); ++i) {
        debug(i, node.centroid_children[i]);
        debug(i, node.child_sum[i]);
        debug(i, node.child_count[i]);
      }
    }
    debug("PrintDps END");
  }

  void CalculateDp() {
    forbidden.assign(input_tree.n, false);
    CalculateCentroid(root_centroid);
  }

  void CalculateCentroid(int c) {
    debug("CalculateCentroid", c);
    forbidden[c] = true;
    auto& node = nodes[c];
    int k = node.centroid_children.size();
    node.child_sum.resize(k);
    node.child_count.resize(k);

    node.sum[0] = 0;
    node.count[0] = 1;

    for (int i = 0; i < k; ++i) {
      int c_child = node.centroid_children[i];
      int t_child = node.tree_children[i];
      debug(c, c_child, t_child);

      node.child_sum[i].resize(2);
      node.child_count[i].resize(2);

      node.child_sum[i][0] = DfsSum(t_child, -1, 1, 0);
      node.child_sum[i][1] = DfsSum(t_child, -1, 1, 1);

      node.sum[0] += node.child_sum[i][0];
      node.sum[1] += node.child_sum[i][1];

      node.child_count[i][0] = DfsCount(t_child, -1, 0);
      node.child_count[i][1] = DfsCount(t_child, -1, 1);
      debug(node.count[0], node.child_count[i][0]);
      node.count[0] += node.child_count[i][0];
      node.count[1] += node.child_count[i][1];

      CalculateCentroid(c_child);
    }
  }

  i64 DfsSum(int v, int p, int dist, int col) {
    if (forbidden[v]) {
      return 0;
    }
    i64 result = nodes[v].color == col ? dist : 0;
    for (int u : input_tree.adjacency_list[v]) {
      if (u != p) {
        result += DfsSum(u, v, dist + 1, col);
      }
    }
    return result;
  }

  int DfsCount(int v, int p, int col) {
    if (forbidden[v]) {
      return 0;
    }
    int result = nodes[v].color == col ? 1 : 0;
    for (int u : input_tree.adjacency_list[v]) {
      if (u != p) {
        result += DfsCount(u, v, col);
      }
    }
    return result;
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
