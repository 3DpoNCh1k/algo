#pragma once

#include <string>
#include <vector>

namespace algo::strings {
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

// alias
constexpr auto LongestCommonPrefixes = ZFunction;

}  // namespace algo::strings
