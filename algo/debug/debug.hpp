#pragma once

#include <iostream>

#include <algo/utils/to_string/to_string.hpp>

namespace algo::utils::debug {
void Debug() {
}
template <class Head, class... Tail>
void Debug(Head h, Tail... t) {
  std::cerr << ToString(h);
  if (sizeof...(t)) {
    std::cerr << ", ";
  }
  Debug(t...);
}
}  // namespace algo::utils::debug

#ifdef LOCAL_DEBUG
#define debug(...)                                                          \
  do {                                                                      \
    std::cerr << "LINE(" << __LINE__ << ") -> [" << #__VA_ARGS__ << "]: ["; \
    algo::utils::debug::Debug(__VA_ARGS__);                                 \
    std::cerr << "]\n";                                                     \
  } while (false)

#else
#define debug(...) \
  do {             \
  } while (false)
#endif
