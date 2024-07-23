#pragma once

#include <algorithm>
#include <string>
#include <vector>

namespace algo::strings {
// Kasai's algorithm
std::vector<int> LcpArray(const std::vector<int>& suffix_array,
                          const std::string& s) {
  int n = s.size();
  if (n <= 1) {
    return {};
  }
  std::vector<int> lcp(n - 1);
  std::vector<int> inversed_suffix_array(n, 0);
  for (int pos = 0; pos < n; ++pos) {
    inversed_suffix_array[suffix_array[pos]] = pos;
  }
  int current_lcp = 0;
  for (int suffix_index = 0; suffix_index < n; ++suffix_index) {
    int pos = inversed_suffix_array[suffix_index];
    if (pos == 0) {
      continue;
    }
    int previous_suffix_index = suffix_array[pos - 1];

    while (suffix_index + current_lcp < n &&
           previous_suffix_index + current_lcp < n &&
           s[suffix_index + current_lcp] ==
               s[previous_suffix_index + current_lcp]) {
      current_lcp++;
    }

    lcp[pos - 1] = current_lcp;
    current_lcp--;
    current_lcp = std::max(current_lcp, 0);
  }

  return std::move(lcp);
}
}  // namespace algo::strings
