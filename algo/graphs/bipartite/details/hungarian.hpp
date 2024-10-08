#pragma once

#include <algorithm>

#include <algo/graphs/entities.hpp>
#include <cassert>
#include <vector>
#include "algo/utils/debug.hpp"

namespace algo::graphs::bipartite::details {
struct Hungarian {
  const BipartiteGraphWithCost& g;
  explicit Hungarian(const BipartiteGraphWithCost& g0)
      : g(g0) {
  }

  std::vector<bool> visited_right;
  std::vector<int> visited_right_by_edge;
  std::vector<bool> visited_left;

  std::vector<int> right_matching;
  std::vector<int> left_matching;

  std::vector<i64> right_potential;
  std::vector<i64> left_potential;
  std::vector<int> minimum_edge;

  std::vector<DirectedEdgeWithCost> Assign() {
    right_matching.assign(g.n_right_side, -1);
    left_matching.assign(g.n_left_side, -1);
    right_potential.assign(g.n_right_side, 0);
    left_potential.assign(g.n_left_side, 0);
    while (FindAugmentingPath()) {
    }

    std::vector<DirectedEdgeWithCost> assignment;
    for (int v = 0; v < g.n_left_side; ++v) {
      if (left_matching[v] != -1) {
        assignment.push_back(g.edges[left_matching[v]]);
      }
    }
    return assignment;
  };

  bool FindAugmentingPath() {
    dbg("FindAugmentingPath");
    visited_right.assign(g.n_right_side, false);
    visited_right_by_edge.assign(g.n_right_side, -1);
    visited_left.assign(g.n_left_side, false);
    minimum_edge.assign(g.n_right_side, -1);
    for (int v = 0; v < g.n_left_side; ++v) {
      if (left_matching[v] == -1) {
        VisitLeft(v);
      }
    }
    while (true) {
      auto e = FindMinimumEdge();
      if (e == -1) {
        return false;
      }
      auto delta = GetEdgeCost(e);
      for (int v = 0; v < g.n_left_side; ++v) {
        if (visited_left[v]) {
          left_potential[v] -= delta;
        }
      }
      for (int u = 0; u < g.n_right_side; ++u) {
        if (visited_right[u]) {
          right_potential[u] += delta;
        }
      }
      auto edge = g.edges[e];
      assert(!visited_right[edge.to]);
      visited_right[edge.to] = true;
      visited_right_by_edge[edge.to] = e;
      if (right_matching[edge.to] == -1) {
        ApplyAugmentingPath(e);
        return true;
      }
      int v = g.edges[right_matching[edge.to]].from;
      VisitLeft(v);
    }
  }

  void ApplyAugmentingPath(int e) {
    while (true) {
      auto edge = g.edges[e];
      int prev_e = left_matching[edge.from];
      right_matching[edge.to] = e;
      left_matching[edge.from] = e;
      if (prev_e == -1) {
        break;
      }
      int u = g.edges[prev_e].to;
      e = visited_right_by_edge[u];
    }
  };

  void VisitLeft(int v) {
    visited_left[v] = true;
    for (int e : g[v]) {
      auto edge = g.edges[e];
      if (left_matching[v] == e) {
        continue;
      }
      if (minimum_edge[edge.to] == -1 ||
          GetEdgeCost(minimum_edge[edge.to]) > GetEdgeCost(e)) {
        minimum_edge[edge.to] = e;
      }
    }
  }

  i64 GetEdgeCost(int e) {
    auto edge = g.edges[e];
    return left_potential[edge.from] + right_potential[edge.to] + edge.cost;
  };

  int FindMinimumEdge() {
    dbg("FindMinimumEdge");
    int e = -1;
    for (int u = 0; u < g.n_right_side; ++u) {
      if (visited_right[u]) {
        continue;
      }
      if (minimum_edge[u] == -1) {
        continue;
      }
      if (e == -1 || GetEdgeCost(e) > GetEdgeCost(minimum_edge[u])) {
        e = minimum_edge[u];
      }
    }
    return e;
  }
};
}  // namespace algo::graphs::bipartite::details
