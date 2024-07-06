#pragma once

#include <string>
#include <algo/utils/to_string/declarations/all.hpp>

namespace algo::utils {
template <class T1, class T2>
std::string ToString(const std::pair<T1, T2>& p) {
  return "(" + ToString(p.first) + ", " + ToString(p.second) + ")";
}
}  // namespace algo::utils
