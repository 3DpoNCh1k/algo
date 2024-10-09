#pragma once

#include <algorithm>
#include <utility>
#include <vector>

#include <algo/utils/random/random.hpp>

namespace algo::utils::generators {

struct TreeGenerator {
  using Edge = std::pair<int, int>;

  explicit TreeGenerator() {
  }

  std::vector<Edge> GetEdges(int n) {
    std::vector<Edge> edges;
    for (int i = 1; i < n; ++i) {
      edges.emplace_back(random::RandomInt(0, i - 1), i);
    }

    random::Shuffle(edges);

    std::vector<int> permutation(n);
    std::iota(permutation.begin(), permutation.end(), 0);
    random::Shuffle(permutation);

    for (Edge& edge : edges) {
      // Rename
      edge.first = permutation[edge.first];
      edge.second = permutation[edge.second];

      // Change the order of edge ends
      if (random::Maybe()) {
        std::swap(edge.first, edge.second);
      }
    }

    return edges;
  }
};
}  // namespace algo::utils::generators
