#pragma once

#include "../header.hpp"

// Verification: https://judge.yosupo.jp/problem/two_sat

struct TwoSat {
  const int mxN = 2e5;
  const int INF = 1e9;

  vector<vector<int>> g, g_inv;
  vector<int> visited, order, val;

  int n;
  int flag = 1;

  // see solve()
  explicit TwoSat(vector<vector<int>>& g0) {
    g = g0;
    int n2 = g0.size();
    // assume, it's 2 * # vertices: x: (0...n-1); !x: (n...2n-1)
    assert((n2 % 2) == 0);
    n = n2 / 2;
    g_inv.assign(2 * n, {}), visited.assign(2 * n, 0);
    for (int u; u < 2 * n; ++u) {
      for (int v : g0[u]) {
        g_inv[v].push_back(u);
      }
    }
  }

  void dfs(int v) {
    visited[v] = 1;
    for (int u : g_inv[v]) {
      if (visited[u] == 0) {
        dfs(u);
      }
    }
    order.push_back(v);
  }

  void dfs2(int v, int c) {
    visited[v] = 1;
    int nv = v < n ? v + n : v - n;
    if (visited[nv] == 1) {
      flag = 0;  // no solution x -> !x
    }

    val[v] = c;
    val[nv] = 1 ^ c;

    for (int u : g[v]) {
      if (visited[u] == 0) {
        dfs2(u, c);
      }
    }
    visited[v] = 2;
  }

  // ans - set TRUE vertices
  bool Solve(set<int>& ret_ans) {
    for (int i = 2 * n - 1; i >= 0; --i) {
      if (visited[i] == 0) {
        dfs(i);
      }
    }
    visited.assign(2 * n, 0);
    val.resize(2 * n, -1);

    flag = 1;
    for (int i = 2 * n - 1; i >= 0; i--) {
      int u = order[i];
      if (visited[u] != 0) {
        continue;
      }
      int c = val[u];
      if (val[u] == -1) {
        // if not marked -> mark as positive
        c = 1;
      }
      dfs2(u, c);
    }

    ret_ans.clear();
    for (int i = 0; i < n; ++i) {
      if (val[i] != 0) {
        ret_ans.insert(i);
      }
    }
    return flag != 0;
  }
};
