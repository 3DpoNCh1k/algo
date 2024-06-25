#pragma once

#include <vector>
#include <set>
#include <utility>

// TODO: fix TLE on random_03 test
namespace algo::flows {
struct Kuhn {
  std::vector<std::vector<int>> L;
  std::vector<int> visited;
  std::vector<int> mt;
  // left sz, right sz
  int n1, n2;
  // # matchings
  int k_mt;
  Kuhn(const std::vector<std::vector<int>>& left, int n2)
      : n2(n2) {
    L = left;
    n1 = L.size();
    visited.resize(n1, 0);
    mt.resize(n2, -1);
  }

  int Solve(std::vector<int>& ret_mt) {
    std::vector<char> used1(n1);
    k_mt = 0;
    std::set<std::pair<int, int>> q;
    std::vector<std::vector<int>> right(n2);
    std::vector<int> degs(n1);
    for (int i = 0; i < n1; ++i) {
      degs[i] = L[i].size();
      q.insert({L[i].size(), i});
      for (int v : L[i]) {
        right[v].push_back(i);
      }
    }

    int k = 0;
    while (!q.empty()) {
      ++k;
      auto it = q.begin();
      int d = it->first, idx = it->second;
      q.erase(it);
      for (int v : L[idx]) {
        if (mt[v] == -1) {
          used1[idx] = 1;
          k_mt++;
          mt[v] = idx;
          for (int u : right[v]) {
            auto it2 = q.find({degs[u], u});
            if (it2 != q.end()) {
              degs[u]--;
              q.erase(it2);
              if (degs[u] > 0) {
                q.insert({degs[u], u});
              }
            }
          }
          break;
        }
      }
    }

    for (int i = 0; i < n1; ++i) {
      if (used1[i] != 0) {
        continue;
      }
      visited.assign(n1, 0);
      if (TryKuhn(i)) {
        k_mt++;
      }
    }
    ret_mt = mt;
    return k_mt;
  }

  bool TryKuhn(int v) {
    if (visited[v] != 0) {
      return false;
    }
    visited[v] = 1;
    for (int u : L[v]) {
      if (mt[u] == -1 || TryKuhn(mt[u])) {
        mt[u] = v;
        return true;
      }
    }
    return false;
  }
};
}  // namespace algo::flows
