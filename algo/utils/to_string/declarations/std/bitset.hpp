#pragma once

#include <bitset>
#include <string>

namespace algo::utils {
template <size_t N>
std::string ToString(const std::bitset<N>&);
}  // namespace algo::utils
