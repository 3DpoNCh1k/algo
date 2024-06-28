#pragma once

#include <string>
#include <vector>

namespace algo::strings {
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
}  // namespace algo::strings
