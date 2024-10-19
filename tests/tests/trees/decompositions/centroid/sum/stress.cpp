
#include "algo/trees/entity/tree.hpp"

#include "algo/debug/debug.hpp"
#include "tests/framework/asserts.hpp"
#include "tests/framework/test.hpp"

#include <algo/utils/random/random.hpp>
#include <algo/utils/generators/tree.hpp>

#include "centroid.hpp"

using namespace algo::trees;
using namespace algo::utils::generators;
using namespace algo::utils::random;

struct BruteForce {
  const Tree& tree;
  std::vector<int> color;
  explicit BruteForce(const Tree& tree)
      : tree(tree),
        color(tree.n, 0) {
  }

  int GetSum(int u) {
    return DFS(u, -1, 0, color[u]);
  }

  void ChangeColor(int u) {
    color[u] ^= 1;
  }

  i64 DFS(int v, int parent, int d, int col) {
    i64 result = 0;
    if (color[v] == col) {
      result += d;
    }
    for (int u : tree.adjacency_list[v]) {
      if (u != parent) {
        result += DFS(u, v, d + 1, col);
      }
    }
    return result;
  };
};

struct Tester {
  const Tree& tree;
  SumCentroid centroids;
  BruteForce brute_force;

  explicit Tester(const Tree& tree)
      : tree(tree),
        centroids(tree),
        brute_force(tree) {
  }

  void Test(int k_query) {
    debug(tree);
    for (int q = 0; q < k_query; ++q) {
      if (Maybe()) {
        Update();
      } else {
        Ask();
      }
    }
  };

  void Update() {
    int u = RandomInt(0, tree.n - 1);
    debug("Update", u);
    centroids.ChangeColor(u);
    brute_force.ChangeColor(u);
  }

  void Ask() {
    int u = RandomInt(0, tree.n - 1);
    debug("Ask", u);
    auto result = centroids.GetSum(u);
    auto correct_result = brute_force.GetSum(u);
    debug(u);
    debug(result);
    debug(correct_result);
    ASSERT_EQ(result, correct_result);
  }
};

void Test(int k_rep, int min_tree_size, int max_tree_size, int k_query) {
  auto tree_generator = TreeGenerator();
  for (int rep = 0; rep < k_rep; ++rep) {
    int n = RandomInt(min_tree_size, max_tree_size);
    auto tree = tree_generator.Tree(n);
    debug("Test", tree);
    auto tester = Tester(tree);
    tester.Test(k_query);
  }
}

TEST(StressSmall) {
  Test(1000, 1, 10, 100);
}

TEST(StressBig) {
  Test(50, 100, 500, 1000);
}

RUN_ALL_TESTS()
