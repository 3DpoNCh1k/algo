#pragma once

#include <algorithm>
#include <set>

#include <algo/graphs/entity/bipartite.hpp>
#include "tests/framework/asserts.hpp"

using namespace algo::graphs;

template <typename Cost>
auto GetAssignmentCost(const BipartiteGraphWith<Cost>& g) {
  using C = typename Cost::CostType;
  int n = std::max(g.n, g.n_right);
  std::pair<int, C> min_cost = {n, 0};
  std::vector<int> permutation(n);
  for (int i = 0; i < n; ++i) {
    permutation[i] = i;
  }
  do {
    std::pair<int, C> cur_cost = {0, 0};
    for (int v = 0; v < g.n; ++v) {
      int u = permutation[v];
      if (u >= g.n_right) {
        cur_cost.first++;
      } else {
        std::pair<int, C> edge_cost = {1, 0};
        for (int e : g.edge_list[v]) {
          if (g.edges[e].to == u) {
            edge_cost = min(edge_cost, {0, g.edges[e].cost});
          }
        }
        cur_cost.first += edge_cost.first;
        cur_cost.second += edge_cost.second;
      }
    }
    min_cost = min(min_cost, cur_cost);
  } while (std::next_permutation(permutation.begin(), permutation.end()));
  return min_cost.second;
};

template <typename Cost>
void Validate(const std::vector<DirectedEdgeWith<Cost>>& assignment,
              const BipartiteGraphWith<Cost>& g) {
  auto min_cost = GetAssignmentCost(g);
  typename Cost::CostType cost = 0;
  std::set<int> left;
  std::set<int> right;
  for (auto e : assignment) {
    ASSERT_TRUE(left.find(e.from) == left.end());
    ASSERT_TRUE(right.find(e.to) == right.end());
    ASSERT_CONTAINS(g.edges, e);
    left.insert(e.from);
    right.insert(e.to);
    cost += e.cost;
  }
  ASSERT_EQ(cost, min_cost);
};
