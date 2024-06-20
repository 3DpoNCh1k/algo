#pragma once

#include <string>
#include <vector>

namespace algo::utils {
std::string ToString(const std::vector<bool>& v) {
  std::string result;
  for (const auto& x : v) {
    result += char('0' + static_cast<int>(x));
  }
  return result;
}
}  // namespace algo::utils
