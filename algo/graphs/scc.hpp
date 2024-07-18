#pragma once

#include <iostream>
#include <set>
#include <utility>
#include <vector>

namespace algo::graphs {
struct StronglyConnectedComponents {
  const int mxN = 2e5;
  const int INF = 1e9;

  std::set<std::pair<int, int>>
      ans;  // edges in StronglyConnectedComponents graph (w/o duplicate edges)
  std::vector<std::vector<int>> g, g_inv;
  std::vector<int> visited, order, scc;
  int n;
  // see solve()
  explicit StronglyConnectedComponents(
      const std::vector<std::vector<int>>& g0) {
    // 0 indexed
    g = g0;
    n = g.size();
    g_inv.assign(n, {}), visited.assign(n, 0), scc.assign(n, 0);
    for (int u = 0; u < n; ++u) {
      for (int v : g[u]) {
        g_inv[v].push_back(u);
      }
    }
  }

  void Solve(std::vector<int>& ret_scc,
             std::set<std::pair<int, int>>& ret_ans) {
    for (int i = 0; i < n; ++i) {
      if (visited[i] == 0) {
        OrderDfs(i);
      }
    }
    visited.assign(n, 0);
    int cmp = 1;
    for (int i = n - 1; i >= 0; --i) {
      int u = order[i];
      if (visited[u] == 0) {
        SccDfs(u, cmp);
        cmp++;
      }
    }
    ret_scc = scc;
    ret_ans = ans;
  }

  // EXAMPLE (cnt # edges in StronglyConnectedComponents graph)
  // 1 indexed vertices
  void Solve() {
    int n, m;
    std::cin >> n >> m;
    g.assign(n + 1, {}), g_inv.assign(n + 1, {}), visited.assign(n + 1, 0),
        scc.assign(n + 1, 0);

    for (int i = 0; i < m; ++i) {
      int u, v;
      std::cin >> u >> v;
      g[u].push_back(v);
      g_inv[v].push_back(u);
    }

    for (int i = 1; i <= n; ++i) {
      if (visited[i] == 0) {
        OrderDfs(i);
      }
    }

    visited.assign(n + 1, 0);
    int cmp = 1;
    for (int i = n - 1; i >= 0; --i) {
      int u = order[i];
      if (visited[u] == 0) {
        SccDfs(u, cmp);
        cmp++;
      }
    }
    std::cout << ans.size();
  }

 private:
  void OrderDfs(int v) {
    visited[v] = 1;
    for (int u : g[v]) {
      if (visited[u] == 0) {
        OrderDfs(u);
      }
    }
    order.push_back(v);
  }

  void SccDfs(int v, int cmp) {
    scc[v] = cmp;
    visited[v] = 1;
    for (int u : g_inv[v]) {
      if (visited[u] == 0) {
        SccDfs(u, cmp);
      } else {
        if (scc[u] != scc[v]) {
          ans.insert({scc[u], scc[v]});
        }
      }
    }
  }
};

using SCC = StronglyConnectedComponents;

}  // namespace algo::graphs
