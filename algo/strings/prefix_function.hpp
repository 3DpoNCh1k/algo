#pragma once

#include <string>
#include <vector>

namespace algo::strings {
/*
For every prefix `p` of `s` calculates the length of the longest string `t` that
1) `t` != `p`
2) `t` is a prefix of `p`
3) `t` is a suffix of `p`
*/
std::vector<int> PrefixFunction(const std::string& s) {
  int n = s.size();
  std::vector<int> length(n);
  for (int i = 1; i < n; ++i) {
    int previous_length = length[i - 1];
    while (true) {
      if (s[i] == s[previous_length]) {
        length[i] = previous_length + 1;
        break;
      }
      if (previous_length == 0) {
        break;
      }
      previous_length = length[previous_length - 1];
    }
  }
  return length;
}
}  // namespace algo::strings
