#pragma once

#include <cassert>
#include <deque>
#include <vector>
#include <algo/trees/entity/tree.hpp>

namespace algo::trees::decompositions::centroid {

struct BaseCentroid {
  /*
    centroids[root].level == 0
    centroids[v].parent.back() == v
    centroids[v].parent[0] == root
  */

  struct Centroid {
    int size;
    int level = -1;
    std::vector<int> parent;
    std::vector<int> distance;
  };

  const Tree& tree;
  std::vector<Centroid> centroids;

  explicit BaseCentroid(const Tree& tree)
      : tree(tree),
        centroids(tree.n) {
    Decompose();
  }

  virtual void CalculateForComponent(int centroid) = 0;

  void Calculate() {
    for (int v = 0; v < tree.n; ++v) {
      CalculateForComponent(v);
    }
  }

  void Decompose() {
    BuildRecursive(0, -1, 0);
  }

  void BuildRecursive(int v, int p, int lvl) {
    CalculateSubtreeSize(v, -1);
    int c = FindCentroid(v, -1);
    auto& centroid = centroids[c];
    centroid.level = lvl;
    CalculateParentsAndDistances(c);
    for (int u : tree.adjacency_list[c]) {
      if (centroids[u].level == -1) {
        BuildRecursive(u, c, lvl + 1);
      }
    }
  }

  void CalculateSubtreeSize(int v, int p) {
    auto& centroid = centroids[v];
    centroid.size = 1;
    for (int u : tree.adjacency_list[v]) {
      if (u != p && centroids[u].level == -1) {
        CalculateSubtreeSize(u, v);
        centroid.size += centroids[u].size;
      }
    }
  }

  int FindCentroid(int v, int p) {
    int index = -1;
    for (int u : tree.adjacency_list[v]) {
      if (u != p && centroids[u].level == -1) {
        if (centroids[u].size > centroids[v].size / 2) {
          index = u;
          break;
        }
      }
    }
    if (index == -1) {
      return v;
    }
    centroids[v].size -= centroids[index].size;
    centroids[index].size += centroids[v].size;
    return FindCentroid(index, v);
  }

  void CalculateParentsAndDistances(int c) {
    auto& centroid_node = centroids[c];

    using Queue = std::deque<std::pair<int, int>>;
    Queue q;
    q.emplace_back(c, -1);
    for (int dist = 0; !q.empty(); dist++) {
      Queue next_q;
      for (auto& [v, parent] : q) {
        centroids[v].parent.push_back(c);
        centroids[v].distance.push_back(dist);
        for (int u : tree.adjacency_list[v]) {
          if (u != parent && centroids[u].level == -1) {
            next_q.emplace_back(u, v);
          }
        }
      }
      q = next_q;
    }
  }
};

}  // namespace algo::trees::decompositions::centroid
