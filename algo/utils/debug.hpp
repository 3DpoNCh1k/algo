#pragma once

#include <iostream>

#include <algo/utils/to_string/to_string.hpp>

namespace algo::utils::debug {
void DBG() {
}
template <class Head, class... Tail>
void DBG(Head h, Tail... t) {
  std::cerr << ToString(h);
  if (sizeof...(t)) {
    std::cerr << ", ";
  }
  DBG(t...);
}
#ifdef LOCAL_DEBUG
#define dbg(...)                                                          \
  std::cerr << "LINE(" << __LINE__ << ") -> [" << #__VA_ARGS__ << "]: ["; \
  DBG(__VA_ARGS__);                                                       \
  std::cerr << "]\n";
#else
#define dbg(...)
#endif

}  // namespace algo::utils::debug

using algo::utils::debug::DBG;
