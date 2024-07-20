#pragma once

#include <string>
#include <vector>

namespace algo::strings {
/*
For every suffix of `s` calculates the length of the common prefix with `s`
*/
std::vector<int> ZFunction(const std::string& s) {
  int n = s.size();
  std::vector<int> length(n);
  length[0] = n;
  int l = 0, r = 0;
  for (int i = 1; i < n; ++i) {
    int current_length = 0;
    if (r >= i) {
      current_length = std::min(length[i - l], r - i + 1);
    }
    while (i + current_length < n &&
           s[i + current_length] == s[current_length]) {
      current_length++;
    }
    length[i] = current_length;
    if (i + length[i] - 1 > r) {
      l = i;
      r = i + length[i] - 1;
    }
  }
  return length;
}
}  // namespace algo::strings
