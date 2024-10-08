#include <map>
#include <set>
#include <vector>

#include <algo/utils/generators/random.hpp>
#include <algo/utils/generators/tree.hpp>

#include <tests/framework/asserts.hpp>
#include "tests/framework/test.hpp"

using namespace algo::utils::generators;

struct Graph {
  bool has_cycles;
  int k_components;

  enum class Color { gray, black };

  std::map<int, std::set<int>> g;
  std::map<int, Color> colors;
  explicit Graph(std::vector<std::pair<int, int>> edges) {
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
    auto edges = std::vector<std::pair<int, int>>({});
    auto graph = Graph(edges);
    ASSERT_TRUE(graph.IsConnected());
    ASSERT_FALSE(graph.HasCycles());
  }
  {
    auto edges = std::vector<std::pair<int, int>>({{1, 2}});
    auto graph = Graph(edges);
    ASSERT_TRUE(graph.IsConnected());
    ASSERT_FALSE(graph.HasCycles());
  }
  {
    auto edges = std::vector<std::pair<int, int>>({{1, 2}, {3, 4}});
    auto graph = Graph(edges);
    ASSERT_FALSE(graph.IsConnected());
    ASSERT_FALSE(graph.HasCycles());
  }
  {
    auto edges = std::vector<std::pair<int, int>>({{0, 0}});
    auto graph = Graph(edges);
    ASSERT_TRUE(graph.IsConnected());
    ASSERT_TRUE(graph.HasCycles());
  }
  {
    auto edges = std::vector<std::pair<int, int>>({{0, 1}, {1, 0}});
    auto graph = Graph(edges);
    ASSERT_TRUE(graph.IsConnected());
    ASSERT_TRUE(graph.HasCycles());
  }
  {
    auto edges = std::vector<std::pair<int, int>>({{0, 1}, {1, 2}});
    auto graph = Graph(edges);
    ASSERT_TRUE(graph.IsConnected());
    ASSERT_FALSE(graph.HasCycles());
  }
  {
    auto edges = std::vector<std::pair<int, int>>({{0, 1}, {1, 2}, {2, 0}});
    auto graph = Graph(edges);
    ASSERT_TRUE(graph.IsConnected());
    ASSERT_TRUE(graph.HasCycles());
  }
  {
    auto edges =
        std::vector<std::pair<int, int>>({{0, 1}, {2, 3}, {3, 4}, {4, 2}});
    auto graph = Graph(edges);
    ASSERT_FALSE(graph.IsConnected());
    ASSERT_TRUE(graph.HasCycles());
  }
}

TEST(GetEdges) {
  auto random = RandomGenerator(0);
  auto tree_generator = TreeGenerator(random);
  {
    const int from = 1;
    const int to = 10;
    const int rep_count = 50;
    for (int rep = 0; rep < rep_count; ++rep) {
      int n = random.GetInt(from, to);
      auto edges = tree_generator.GetEdges(n);
      ASSERT_EQ(int(edges.size()), n - 1);
      for (auto edge : edges) {
        ASSERT_TRUE(edge.first >= 0);
        ASSERT_TRUE(edge.first < n);
        ASSERT_TRUE(edge.second >= 0);
        ASSERT_TRUE(edge.second < n);
      }

      auto graph = Graph(edges);
      ASSERT_TRUE(graph.IsConnected());
      ASSERT_FALSE(graph.HasCycles());
    }
  }
}

RUN_ALL_TESTS()
