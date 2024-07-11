#pragma once

#include <type_traits>
#include "algo/utils/types/fundamentals.hpp"

namespace algo::utils::bits {

template <typename T>
constexpr bool IsU64 = std::is_same_v<T, u64>;

template <typename T>
constexpr std::enable_if_t<IsU64<T>, int> CountOfOnes(T x) {
  return __builtin_popcountll(x);
};

template <typename T>
constexpr std::enable_if_t<IsU64<T>, bool> IsPowerOfTwo(T x) {
  return x && !(x & (x - 1));
};

template <typename T>
constexpr std::enable_if_t<IsU64<T>, int> IndexOfLeastSignificantBit(T x) {
  // 0 -> -1
  return __builtin_ffsll(x) - 1;
};

template <typename T>
constexpr std::enable_if_t<IsU64<T>, int> IndexOfMostSignificantBit(T x) {
  // 0 -> -1
  return x == 0 ? -1 : 63 - __builtin_clzll(x);
};

template <typename T>
constexpr std::enable_if_t<IsU64<T>, u64> PowerOfTwoThatAtLeast(T x) {
  if (IsPowerOfTwo(x)) {
    return x;
  }
  return 1LL << (IndexOfMostSignificantBit(x) + 1);
};

}  // namespace algo::utils::bits
