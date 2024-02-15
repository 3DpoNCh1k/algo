#pragma once

#include "../header.hpp"


// Verification: https://codeforces.com/group/CYMPFXi8zA/contest/261526/problem/B
vector<int> PrefixFunction(const string& s) {
  int n = s.size();
  vector<int> pref(n);
  for (int i = 1; i < n; ++i) {
    int p = pref[i - 1];
    while (true) {
      if (s[i] == s[p]) {
        pref[i] = p + 1;
        break;
      }
      if (p == 0) {
        break;
      }
      p = pref[p - 1];
    }
  }
  return pref;
}

// Verification: https://judge.yosupo.jp/problem/zalgorithm
vector<int> ZFunction(const string& s) {
  int n = s.size();
  vector<int> zf(n);
  zf[0] = n;
  int l = 0, r = 0;
  for (int i = 1; i < n; ++i) {
    int cv = 0;
    if (r >= i) {
      cv = min(zf[i - l], r - i + 1);
    }
    while (i + cv < n && s[i + cv] == s[cv]) {
      cv++;
    }
    zf[i] = cv;
    if (i + zf[i] - 1 > r) {
      l = i, r = i + zf[i] - 1;
    }
  }
  return zf;
}
