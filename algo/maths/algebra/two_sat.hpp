#pragma once

#include <cassert>
#include <cstdlib>
#include <set>
#include <vector>
#include "algo/graphs/scc.hpp"

namespace algo::maths::algebra {
struct TwoSat {
  using Clause = std::pair<int, int>;
  using Graph = std::vector<std::vector<int>>;
  using Solution = std::set<int>;
  using Result = std::pair<bool, Solution>;
  Graph dependency_graph;
  std::vector<int> value;

  int k_variable;

  explicit TwoSat(int n, const std::vector<Clause>& clauses)
      : k_variable(n) {
    dependency_graph.resize(2 * k_variable);
    for (auto [a, b] : clauses) {
      int u = VariableToVertex(a);
      int v = VariableToVertex(b);
      dependency_graph[VertexNegation(u)].push_back(v);
      dependency_graph[VertexNegation(v)].push_back(u);
    }
  }

  int VariableToVertex(int var) {
    if (var > 0) {
      return var - 1;
    } else {
      auto vertex = std::abs(var) - 1;
      return VertexNegation(vertex);
    }
  }

  int VertexNegation(int vertex) {
    if (vertex < k_variable) {
      return vertex + k_variable;
    }
    return vertex - k_variable;
  }

  Result Solve() {
    auto scc = graphs::SCC(dependency_graph);
    auto [condenstaion_graph, components] = scc.Condense();
    value.assign(dependency_graph.size(), -1);
    for (const auto& component : components) {
      if (value[component[0]] == -1) {
        for (int v : component) {
          if (value[v] != -1) {
            return Result(false, {});
          }
          value[v] = 0;
          value[VertexNegation(v)] = 1;
        }
      }
    }
    Solution solution;
    for (int v = 0; v < k_variable; ++v) {
      if (value[v] == 1) {
        solution.insert(v + 1);
      }
    }
    return Result(true, solution);
  }
};

}  // namespace algo::maths::algebra
