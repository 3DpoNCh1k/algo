#pragma once

#include <algorithm>

#include <algo/graphs/entities.hpp>
#include <algo/graphs/bipartite/matching.hpp>
#include "algo/utils/generators/random.hpp"
#include "algo/utils/bits.hpp"
#include "tests/framework/asserts.hpp"

using namespace algo::graphs;
using namespace algo::graphs::bipartite;

int GetMatchingSize(const BipartiteGraph& g) {
  auto edges = g.Edges();
  int e = edges.size();
  int max_size = 0;
  for (int mask = 0; mask < (1 << e); ++mask) {
    std::vector<bool> left_side_taken(g.n_left_side);
    std::vector<bool> right_side_taken(g.n_right_side);
    bool ok = true;
    for (int i = 0; ok && i < e; ++i) {
      if (((1 << i) & mask) > 0) {
        auto [v, u] = edges[i];
        ok &= !left_side_taken[v];
        ok &= !right_side_taken[u];
        left_side_taken[v] = true;
        right_side_taken[u] = true;
      }
    }
    if (ok) {
      int cur_size = algo::utils::bits::CountOfOnes(u64(mask));
      max_size = std::max(max_size, cur_size);
    }
  }
  return max_size;
};

void Validate(const DirectedEdges& matching, const BipartiteGraph& g) {
  std::vector<bool> left_side_taken(g.n_left_side);
  std::vector<bool> right_side_taken(g.n_right_side);
  for (auto [v, u] : matching) {
    ASSERT_TRUE(v >= 0 && v < g.n_left_side);
    ASSERT_TRUE(u >= 0 && u < g.n_right_side);
    ASSERT_CONTAINS(g[v], u);

    ASSERT_FALSE(left_side_taken[v]);
    ASSERT_FALSE(right_side_taken[u]);

    left_side_taken[v] = true;
    right_side_taken[u] = true;
  }
};
