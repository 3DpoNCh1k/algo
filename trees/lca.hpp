#pragma once

#include "../header.hpp"

// Verification: https://judge.yosupo.jp/problem/lca

struct LCA {
  vector<vector<int>> g, parent;
  vector<int> h, t_in, t_out;
  int n, LOG, root, t;

  LCA(){};
  explicit LCA(const vector<int>& P, int root = 0)
      : root(root) {
    n = P.size();  // with parent of root
    g.assign(n, {}), h.assign(n, 0), t_in.assign(n, 0), t_out.assign(n, 0);
    LOG = 0;
    while ((1 << LOG) < n) {
      ++LOG;
    }

    parent.assign(n, vector<int>(LOG + 1));
    // assume root = 0
    for (int i = 1; i <= n - 1; ++i) {
      int p = P[i];
      //--p; // 0 indexed
      parent[i][0] = p;
      g[p].push_back(i);
      g[i].push_back(p);
    }
    parent[root][0] = root;
    t = 0;
  }

  void dfs(int v) {
    t_in[v] = t++;
    for (int i = 1; i <= LOG; ++i) {
      parent[v][i] = parent[parent[v][i - 1]][i - 1];
    }
    int par = parent[v][0];
    for (int u : g[v]) {
      if (u != par) {
        h[u] = h[v] + 1;
        dfs(u);
      }
    }
    t_out[v] = t++;
  }

  void Solve() {
    dfs(root);
  }

  int GetLCA(int u, int v) {
    //--u, --v; // 0 indexed
    if (t_in[u] > t_in[v]) {
      swap(u, v);
    }
    if (t_out[u] > t_out[v]) {
      return u;  // + 1;
    }
    for (int i = LOG; i >= 0; --i) {
      int p = parent[u][i];
      if (t_out[p] < t_out[v]) {
        u = p;
      }
    }
    return parent[u][0];  // + 1;
  }
};
