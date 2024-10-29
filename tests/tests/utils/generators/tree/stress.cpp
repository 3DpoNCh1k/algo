#include <map>
#include <set>
#include <vector>

#include <algo/utils/random/random.hpp>
#include <algo/trees/utils.hpp>
#include <algo/utils/generators/tree.hpp>

#include <tests/framework/asserts.hpp>
#include <tests/framework/test.hpp>

#include <algo/graphs/entity/edge.hpp>

using namespace algo::utils::generators;
using namespace algo::graphs;

struct Graph {
  bool has_cycles;
  int k_components;

  enum class Color { gray, black };

  std::map<int, std::set<int>> g;
  std::map<int, Color> colors;
  explicit Graph(std::vector<UndirectedEdge> edges) {
    has_cycles = false;
    for (auto [u, v] : edges) {
      g[u].insert(v);
      if (g[v].find(u) != g[v].end()) {
        has_cycles = true;
      }
      g[v].insert(u);
    }

    k_components = 0;
    for (auto [u, v] : edges) {
      if (colors.find(u) == colors.end()) {
        k_components++;
        DFS(u, u);
      }
    }
  }

  void DFS(int v, int previous) {
    if (colors.find(v) != colors.end()) {
      if (colors[v] == Color::gray) {
        has_cycles = true;
      }
      return;
    }
    colors[v] = Color::gray;
    for (int u : g[v]) {
      if (u != previous) {
        DFS(u, v);
      }
    }
    colors[v] = Color::black;
  }

  bool IsConnected() {
    return k_components <= 1;
  }
  bool HasCycles() {
    return has_cycles;
  }
};

TEST(Graph) {
  {
    auto edges = std::vector<UndirectedEdge>({});
    auto graph = Graph(edges);
    ASSERT_TRUE(graph.IsConnected());
    ASSERT_FALSE(graph.HasCycles());
  }
  {
    auto edges = std::vector<UndirectedEdge>({{1, 2}});
    auto graph = Graph(edges);
    ASSERT_TRUE(graph.IsConnected());
    ASSERT_FALSE(graph.HasCycles());
  }
  {
    auto edges = std::vector<UndirectedEdge>({{1, 2}, {3, 4}});
    auto graph = Graph(edges);
    ASSERT_FALSE(graph.IsConnected());
    ASSERT_FALSE(graph.HasCycles());
  }
  {
    auto edges = std::vector<UndirectedEdge>({{0, 0}});
    auto graph = Graph(edges);
    ASSERT_TRUE(graph.IsConnected());
    ASSERT_TRUE(graph.HasCycles());
  }
  {
    auto edges = std::vector<UndirectedEdge>({{0, 1}, {1, 0}});
    auto graph = Graph(edges);
    ASSERT_TRUE(graph.IsConnected());
    ASSERT_TRUE(graph.HasCycles());
  }
  {
    auto edges = std::vector<UndirectedEdge>({{0, 1}, {1, 2}});
    auto graph = Graph(edges);
    ASSERT_TRUE(graph.IsConnected());
    ASSERT_FALSE(graph.HasCycles());
  }
  {
    auto edges = std::vector<UndirectedEdge>({{0, 1}, {1, 2}, {2, 0}});
    auto graph = Graph(edges);
    ASSERT_TRUE(graph.IsConnected());
    ASSERT_TRUE(graph.HasCycles());
  }
  {
    auto edges = std::vector<UndirectedEdge>({{0, 1}, {2, 3}, {3, 4}, {4, 2}});
    auto graph = Graph(edges);
    ASSERT_FALSE(graph.IsConnected());
    ASSERT_TRUE(graph.HasCycles());
  }
}

TEST(TreeGenerator) {
  auto tree_generator = TreeGenerator();
  {
    const int from = 1;
    const int to = 10;
    const int rep_count = 50;
    for (int rep = 0; rep < rep_count; ++rep) {
      int n = algo::utils::random::RandomInt(from, to);
      auto tree = tree_generator.Tree(n);
      auto edges = algo::trees::ToEdges(tree);
      ASSERT_EQ(int(edges.size()), n - 1);
      for (auto edge : edges) {
        ASSERT_TRUE(edge.u >= 0);
        ASSERT_TRUE(edge.u < n);
        ASSERT_TRUE(edge.v >= 0);
        ASSERT_TRUE(edge.v < n);
      }

      auto graph = Graph(edges);
      ASSERT_TRUE(graph.IsConnected());
      ASSERT_FALSE(graph.HasCycles());
    }
  }
}

RUN_ALL_TESTS()
