#pragma once

#include <utility>
#include <vector>

#include <algo/utils/random/random.hpp>
#include <algo/trees/entity/tree.hpp>

namespace algo::utils::generators {

struct TreeGenerator {
  explicit TreeGenerator() {
  }

  trees::Tree Tree(int n) {
    std::vector<std::pair<int, int>> edges;
    for (int i = 1; i < n; ++i) {
      edges.emplace_back(random::RandomInt(0, i - 1), i);
    }

    random::Shuffle(edges);

    std::vector<int> permutation(n);
    std::iota(permutation.begin(), permutation.end(), 0);
    random::Shuffle(permutation);

    for (auto& edge : edges) {
      // Rename
      edge.first = permutation[edge.first];
      edge.second = permutation[edge.second];
    }

    trees::Tree tree(n);
    for (auto& edge : edges) {
      tree.AddEdge(edge.first, edge.second);
    }

    return tree;
  }
};
}  // namespace algo::utils::generators
