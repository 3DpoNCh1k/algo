#pragma once

#include <bitset>
#include <string>

template <size_t N>
std::string ToString(const std::bitset<N>& b) {
  return b.ToString();
}
