#pragma once

#include <cassert>
#include <set>
#include <vector>

namespace algo::maths::algebra {
struct TwoSat {
  using Graph = std::vector<std::vector<int>>;
  Graph dependency_graph;
  Graph dependency_graph_inversed;
  std::vector<int> visited;
  std::vector<int> order;
  std::vector<int> value;

  int variable_count;
  bool has_contradiction = false;

  explicit TwoSat(Graph dependency_graph_0) {
    dependency_graph = std::move(dependency_graph_0);
    int vertex_count = dependency_graph.size();
    // Assume that #vertices == 2 * #variables
    // #variables == n
    // Variables have indices in range: [0...n-1] and corresponding negations have [n...2*n-1]
    assert((vertex_count % 2) == 0);
    variable_count = vertex_count / 2;
    dependency_graph_inversed.assign(vertex_count, {});
    visited.assign(vertex_count, 0);
    for (int u = 0; u < vertex_count; ++u) {
      for (int v : dependency_graph[u]) {
        dependency_graph_inversed[v].push_back(u);
      }
    }
  }

  void dfs(int v) {
    visited[v] = 1;
    for (int u : dependency_graph_inversed[v]) {
      if (visited[u] == 0) {
        dfs(u);
      }
    }
    order.push_back(v);
  }

  void dfs2(int v, int c) {
    visited[v] = 1;
    int nv = v < variable_count ? v + variable_count : v - variable_count;
    if (visited[nv] == 1) {
      has_contradiction = true;
    }

    value[v] = c;
    value[nv] = 1 ^ c;

    for (int u : dependency_graph[v]) {
      if (visited[u] == 0) {
        dfs2(u, c);
      }
    }
    visited[v] = 2;
  }

  // ans - set TRUE vertices
  bool Solve(std::set<int>& ret_ans) {
    for (int i = 2 * variable_count - 1; i >= 0; --i) {
      if (visited[i] == 0) {
        dfs(i);
      }
    }
    visited.assign(2 * variable_count, 0);
    value.resize(2 * variable_count, -1);

    for (int i = 2 * variable_count - 1; i >= 0; i--) {
      int u = order[i];
      if (visited[u] != 0) {
        continue;
      }
      int c = value[u];
      if (value[u] == -1) {
        // if not marked -> mark as positive
        c = 1;
      }
      dfs2(u, c);
    }

    ret_ans.clear();
    for (int i = 0; i < variable_count; ++i) {
      if (value[i] != 0) {
        ret_ans.insert(i);
      }
    }
    return !has_contradiction;
  }
};

}  // namespace algo::maths::algebra
