#include <algo/trees/entity/tree.hpp>

#include <algo/debug/debug.hpp>

#include <tests/framework/asserts.hpp>
#include <tests/framework/test.hpp>

#include <algo/utils/random/random.hpp>
#include <algo/utils/generators/tree.hpp>

#include "centroid.hpp"

using namespace algo::trees;
using namespace algo::utils::generators;
using namespace algo::utils::random;

struct BruteForce {
  const Tree& tree;

  explicit BruteForce(const Tree& tree)
      : tree(tree) {
  }

  int GetMin(int u, int dist) {
    return DFS(u, -1, dist);
  }

  int DFS(int v, int parent, int d) {
    if (d < 0) {
      return 1e9;
    }
    int result = v;
    for (int u : tree.adjacency_list[v]) {
      if (u != parent) {
        result = std::min(result, DFS(u, v, d - 1));
      }
    }
    return result;
  };
};

struct Tester {
  const Tree& tree;

  MinCentroid centroids;
  BruteForce brute_force;
  explicit Tester(const Tree& tree)
      : tree(tree),
        centroids(tree),
        brute_force(tree) {
  }

  void Test(int k_query) {
    debug(tree);
    for (int q = 0; q < k_query; ++q) {
      Ask();
    }
  };

  void Ask() {
    int u = RandomInt(0, tree.n - 1);
    int dist = RandomInt(0, tree.n);
    auto result = centroids.GetMin(u, dist);
    auto correct_result = brute_force.GetMin(u, dist);
    debug(u, dist);
    debug(result);
    debug(correct_result);
    ASSERT_EQ(result, correct_result);
  }
};

void Stress(int k_rep, int min_tree_size, int max_tree_size, int k_query) {
  auto tree_generator = TreeGenerator();
  for (int rep = 0; rep < k_rep; ++rep) {
    int n = RandomInt(min_tree_size, max_tree_size);
    auto tree = tree_generator.Tree(n);
    auto tester = Tester(tree);
    tester.Test(k_query);
  }
}

TEST(StressSmall) {
  Stress(1000, 1, 10, 100);
}

TEST(StressBig) {
  Stress(50, 100, 500, 1000);
}

RUN_ALL_TESTS()
