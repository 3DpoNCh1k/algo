#pragma once

#include <cassert>
#include <cstdlib>
#include <set>
#include <vector>
#include <algo/graphs/scc.hpp>

namespace algo::maths::algebra {
struct TwoSat {
  using Clause = std::pair<int, int>;
  using Graph = std::vector<std::vector<int>>;
  using Solution = std::set<int>;
  using Result = std::pair<bool, Solution>;
  explicit TwoSat(int n, const std::vector<Clause>& clauses)
      : k_variable_(n) {
    dependency_graph_.resize(2 * k_variable_);
    for (auto [a, b] : clauses) {
      int u = VariableToVertex(a);
      int v = VariableToVertex(b);
      dependency_graph_[VertexNegation(u)].push_back(v);
      dependency_graph_[VertexNegation(v)].push_back(u);
    }
  }

  Result Solve() {
    auto [condenstaion_graph, components] =
        graphs::StronglyConnectedComponents(dependency_graph_);
    value_.assign(dependency_graph_.size(), -1);
    for (const auto& component : components) {
      if (value_[component[0]] == -1) {
        for (int v : component) {
          if (value_[v] != -1) {
            return Result(false, {});
          }
          value_[v] = 0;
          value_[VertexNegation(v)] = 1;
        }
      }
    }
    Solution solution;
    for (int v = 0; v < k_variable_; ++v) {
      if (value_[v] == 1) {
        solution.insert(v + 1);
      }
    }
    return Result(true, solution);
  }

 private:
  int VariableToVertex(int var) {
    if (var > 0) {
      return var - 1;
    } else {
      auto vertex = std::abs(var) - 1;
      return VertexNegation(vertex);
    }
  }

  int VertexNegation(int vertex) {
    if (vertex < k_variable_) {
      return vertex + k_variable_;
    }
    return vertex - k_variable_;
  }

  int k_variable_;
  Graph dependency_graph_;
  std::vector<int> value_;
};

}  // namespace algo::maths::algebra
