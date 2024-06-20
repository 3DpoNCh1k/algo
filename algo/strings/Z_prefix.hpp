#pragma once

#include <string>
#include <vector>

namespace algo::strings {
// Verification: https://codeforces.com/group/CYMPFXi8zA/contest/261526/problem/B
std::vector<int> PrefixFunction(const std::string& s) {
  int n = s.size();
  std::vector<int> pref(n);
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
std::vector<int> ZFunction(const std::string& s) {
  int n = s.size();
  std::vector<int> zf(n);
  zf[0] = n;
  int l = 0, r = 0;
  for (int i = 1; i < n; ++i) {
    int cv = 0;
    if (r >= i) {
      cv = std::min(zf[i - l], r - i + 1);
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

}
