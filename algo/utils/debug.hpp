#pragma once

#include <iostream>

#include <algo/utils/to_string/to_string.hpp>

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
#define dbg(...)                                                     \
  cerr << "LINE(" << __LINE__ << ") -> [" << #__VA_ARGS__ << "]: ["; \
  DBG(__VA_ARGS__);                                                  \
  cerr << "]\n";
#else
#define dbg(...) 0
#endif
