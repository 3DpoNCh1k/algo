#pragma once

#include <algorithm>
#include <utility>
#include <vector>

#include <algo/utils/generators/random.hpp>

namespace algo::utils::generators {

struct TreeGenerator {
  using Edge = std::pair<int, int>;

  explicit TreeGenerator(RandomGenerator& random)
      : random_(random) {
  }

  std::vector<Edge> GetEdges(int n) {
    std::vector<Edge> edges;
    for (int i = 1; i < n; ++i) {
      edges.emplace_back(random_.GetInt(0, i - 1), i);
    }

    std::shuffle(edges.begin(), edges.end(), random_.GetEngine());

    std::vector<int> permutation(n);
    std::iota(permutation.begin(), permutation.end(), 0);
    std::shuffle(permutation.begin(), permutation.end(), random_.GetEngine());

    for (Edge& edge : edges) {
      // Rename
      edge.first = permutation[edge.first];
      edge.second = permutation[edge.second];

      // Change the order of edge ends
      if (random_.GetBool()) {
        std::swap(edge.first, edge.second);
      }
    }

    return edges;
  }

 private:
  RandomGenerator random_;
};
}  // namespace algo::utils::generators
