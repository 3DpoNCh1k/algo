#include <algorithm>
#include <utility>
#include <vector>

#include <algo/utils/generators/random.hpp>

namespace algo::utils::generators {

struct TreeGenerator {
  using Edge = std::pair<int, int>;
  RandomGenerator random_generator;

  std::vector<Edge> GetEdges(int n) {
    std::vector<Edge> edges;
    for (int i = 1; i < n; ++i) {
      edges.emplace_back(random_generator.GetInt(0, i - 1), i);
    }

    std::shuffle(edges.begin(), edges.end(), random_generator.GetEngine());

    std::vector<int> permutation(n);
    std::iota(permutation.begin(), permutation.end(), 0);
    std::shuffle(permutation.begin(), permutation.end(),
                 random_generator.GetEngine());

    for (Edge& edge : edges) {
      // Rename
      edge.first = permutation[edge.first];
      edge.second = permutation[edge.second];

      // Change the order of edge ends
      if (random_generator.GetBool()) {
        std::swap(edge.first, edge.second);
      }
    }

    return edges;
  }
};
}  // namespace algo::utils::generators
