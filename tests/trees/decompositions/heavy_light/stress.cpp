#include <algo/trees/segment_tree/operations/add.hpp>
#include <algo/trees/segment_tree/statistics/sum.hpp>
#include <algo/trees/decompositions/heavy_light.hpp>
#include "algo/trees/segment_tree/trees.hpp"
#include "tests/testing/asserts.hpp"

#include <algo/utils/generators/random.hpp>
#include <algo/utils/generators/tree.hpp>

using namespace algo::trees::decompositions;
using namespace algo::trees::segment_tree;
using namespace algo::utils::generators;

using Tree = std::vector<std::vector<int>>;

struct BruteForce {
  const Tree& tree;
  int n;
  std::vector<i64> values;

  explicit BruteForce(const Tree& tree)
      : tree(tree),
        n(tree.size()) {
    values.resize(n);
  }

  void Apply(int u, int v, const operations::AddOp& op) {
    auto path = GetPath(u, v);
    for (int w : path) {
      values[w] += op.add;
    }
  }

  statistics::Sum Get(int u, int v) {
    auto stat = statistics::Sum{};
    auto path = GetPath(u, v);
    for (int w : path) {
      stat.result += values[w];
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
    for (int u : tree[v]) {
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
  RandomGenerator& random;
  const Tree& tree;
  HLD<Operation<operations::AddOp>, Statistics<statistics::Sum>> hld;
  BruteForce brute_force;
  int n;
  explicit Tester(RandomGenerator& random, const Tree& tree)
      : random(random),
        tree(tree),
        hld(tree),
        brute_force(tree),
        n(tree.size()) {
  }

  void Test(int k_query) {
    dbg("Test");
    dbg(tree);
    for (int q = 0; q < k_query; ++q) {
      if (random.GetBool()) {
        Update();
      } else {
        Ask();
      }
    }
  };

  void Update() {
    int u = random.GetInt(0, n - 1);
    int v = random.GetInt(0, n - 1);
    int value = random.GetInt(-1e9, 1e9);
    // int value = random.GetInt(-1, 1);
    dbg("Update", u, v, value);
    auto op = operations::AddOp{value};
    if (u == v && random.GetBool()) {
      hld.ApplyAtVertex(v, op);
    } else {
      hld.ApplyOnPath(u, v, op);
    }
    brute_force.Apply(u, v, op);
  }

  void Ask() {
    int u = random.GetInt(0, n - 1);
    int v = random.GetInt(0, n - 1);
    dbg("Ask", u, v);
    auto stat = (u == v && random.GetBool())
                    ? hld.GetFromVertex<statistics::Sum>(v)
                    : hld.GetFromPath<statistics::Sum>(u, v);
    auto correct_stat = brute_force.Get(u, v);
    dbg(stat.result);
    dbg(correct_stat.result);
    ASSERT_EQ(stat.result, correct_stat.result);
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

void Test(int k_rep, int min_tree_size, int max_tree_size, int k_query) {
  RandomGenerator random(0);
  TreeGenerator tree_generator(random);
  for (int rep = 0; rep < k_rep; ++rep) {
    int n = random.GetInt(min_tree_size, max_tree_size);
    auto edges = tree_generator.GetEdges(n);
    auto tree = ConvertToTree(edges, n);
    auto tester = Tester(random, tree);
    tester.Test(k_query);
  }
}

int main() {
  Test(1000, 1, 10, 100);
  Test(50, 100, 500, 1000);
}
