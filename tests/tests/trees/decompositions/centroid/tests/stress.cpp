#include <algo/trees/segment_tree/operations/add.hpp>
#include <algo/trees/segment_tree/statistics/sum.hpp>
#include <algo/trees/decompositions/centroid.hpp>
#include "algo/trees/segment_tree/trees.hpp"
#include "algo/utils/debug.hpp"
#include "tests/framework/asserts.hpp"
#include "tests/framework/test.hpp"

#include <algo/utils/random/random.hpp>
#include <algo/utils/generators/tree.hpp>

using namespace algo::trees::decompositions;
using namespace algo::trees::segment_tree;
using namespace algo::utils::generators;
using namespace algo::utils::random;

using Tree = std::vector<std::vector<int>>;

struct BruteForce {
  const Tree& tree;
  int n;

  explicit BruteForce(const Tree& tree)
      : tree(tree),
        n(tree.size()) {
  }

  int GetMin(int u, int dist) {
    return DFS(u, -1, dist);
  }

  int DFS(int v, int parent, int d) {
    if (d < 0) {
      return 1e9;
    }
    int result = v;
    for (int u : tree[v]) {
      if (u != parent) {
        result = std::min(result, DFS(u, v, d - 1));
      }
    }
    return result;
  };
};

struct Tester {
  const Tree& tree;
  Centroids<Operation<operations::AddOp>, Statistics<statistics::Sum>>
      centroids;
  BruteForce brute_force;
  int n;
  explicit Tester(const Tree& tree)
      : tree(tree),
        centroids(tree),
        brute_force(tree),
        n(tree.size()) {
  }

  void Test(int k_query) {
    dbg(tree);
    for (int q = 0; q < k_query; ++q) {
      Ask();
    }
  };

  void Ask() {
    int u = RandomInt(0, n - 1);
    int dist = RandomInt(0, n);
    auto result = centroids.GetMin(u, dist);
    auto correct_result = brute_force.GetMin(u, dist);
    dbg(u, dist);
    dbg(result);
    dbg(correct_result);
    ASSERT_EQ(result, correct_result);
  }
};

Tree ConvertToTree(const std::vector<TreeGenerator::Edge>& edges, int n) {
  Tree tree(n);
  for (auto [u, v] : edges) {
    tree[u].push_back(v);
    tree[v].push_back(u);
  }
  return tree;
};

void Stress(int k_rep, int min_tree_size, int max_tree_size, int k_query) {
  auto tree_generator = TreeGenerator();
  for (int rep = 0; rep < k_rep; ++rep) {
    int n = RandomInt(min_tree_size, max_tree_size);
    auto edges = tree_generator.GetEdges(n);
    auto tree = ConvertToTree(edges, n);
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
