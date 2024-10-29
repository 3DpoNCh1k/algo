#pragma once

#include <algorithm>

#include <algo/graphs/entity/bipartite.hpp>
#include <algo/graphs/entity/edge.hpp>
#include <algo/utils/bits.hpp>

#include <tests/framework/asserts.hpp>

using namespace algo::graphs;

int GetMatchingSize(const BipartiteGraph& g) {
  int max_size = 0;
  for (int mask = 0; mask < (1 << g.edges.size()); ++mask) {
    std::vector<bool> left_side_taken(g.n);
    std::vector<bool> right_side_taken(g.n_right);
    bool ok = true;
    for (int i = 0; ok && i < g.edges.size(); ++i) {
      if (((1 << i) & mask) > 0) {
        auto edge = g.edges[i];
        ok &= !left_side_taken[edge.from];
        ok &= !right_side_taken[edge.to];
        left_side_taken[edge.from] = true;
        right_side_taken[edge.to] = true;
      }
    }
    if (ok) {
      int cur_size = algo::utils::bits::CountOfOnes(u64(mask));
      max_size = std::max(max_size, cur_size);
    }
  }
  return max_size;
};

void Validate(const std::vector<DirectedEdge>& matching,
              const BipartiteGraph& g) {
  std::vector<bool> left_side_taken(g.n);
  std::vector<bool> right_side_taken(g.n_right);
  for (auto edge : matching) {
    ASSERT_TRUE(edge.from >= 0 && edge.from < g.n);
    ASSERT_TRUE(edge.to >= 0 && edge.to < g.n_right);

    ASSERT_CONTAINS(g.edges, edge);

    ASSERT_FALSE(left_side_taken[edge.from]);
    ASSERT_FALSE(right_side_taken[edge.to]);

    left_side_taken[edge.from] = true;
    right_side_taken[edge.to] = true;
  }
};
