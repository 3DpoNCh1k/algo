#pragma once

#include <string>

template <class T1, class T2>
std::string ToString(const std::pair<T1, T2>& p) {
  return "(" + ToString(p.first) + ", " + ToString(p.second) + ")";
}