#include <algo/ranges/updates/add.hpp>
#include <algo/ranges/statistics/sum.hpp>
#include <algo/trees/decompositions/heavy_light.hpp>
#include "algo/trees/entity/tree.hpp"

#include "tests/framework/asserts.hpp"
#include "tests/framework/test.hpp"

#include <algo/utils/random/random.hpp>
#include <algo/utils/generators/tree.hpp>

using namespace algo::trees::decompositions;
using namespace algo::ranges::segment_tree;
using namespace algo::ranges::updates;
using namespace algo::ranges::statistics;
using namespace algo::trees;
using namespace algo::utils::generators;
using namespace algo::utils::random;

struct BruteForce {
  const Tree& tree;
  std::vector<i64> values;

  explicit BruteForce(const Tree& tree)
      : tree(tree) {
    values.resize(tree.n);
  }

  void Apply(int u, int v, i64 add) {
    auto path = GetPath(u, v);
    for (int w : path) {
      values[w] += add;
    }
  }

  auto Get(int u, int v) {
    i64 stat = 0;
    auto path = GetPath(u, v);
    for (int w : path) {
      stat += values[w];
    }
    return stat;
  }

  std::vector<int> GetPath(int u, int v) {
    std::vector<int> path;
    DFS(u, -1, v, path);
    return path;
  };

  bool DFS(int v, int parent, int target, std::vector<int>& path) {
    path.push_back(v);
    if (v == target) {
      return true;
    }
    for (int u : tree.adjacency_list[v]) {
      if (u != parent) {
        if (DFS(u, v, target, path)) {
          return true;
        }
      }
    }
    path.pop_back();
    return false;
  }
};

struct Tester {
  const Tree& tree;
  HLD<IntAdd, IntSum> hld;
  BruteForce brute_force;

  explicit Tester(const Tree& tree)
      : tree(tree),
        hld(tree),
        brute_force(tree) {
  }

  void Test(int k_query) {
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
    int v = RandomInt(0, tree.n - 1);
    int add = RandomInt(-1e9, 1e9);

    if (u == v && Maybe()) {
      hld.ApplyAtVertex(v, add);
    } else {
      hld.ApplyOnPath(u, v, add);
    }
    brute_force.Apply(u, v, add);
  }

  void Ask() {
    int u = RandomInt(0, tree.n - 1);
    int v = RandomInt(0, tree.n - 1);
    auto stat =
        (u == v && Maybe()) ? hld.GetFromVertex(v) : hld.GetFromPath(u, v);
    auto correct_stat = brute_force.Get(u, v);

    ASSERT_EQ(stat, correct_stat);
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
