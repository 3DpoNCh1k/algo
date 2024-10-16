#pragma once

#include <limits>
#include "algo/data_structures/convex_hull_trick.hpp"
#include "algo/utils/bits.hpp"

namespace algo::ranges {

template <bool is_minimum, typename T = i64>
struct ConvexHullTree {
  static constexpr bool IsMinimum = is_minimum;
  using CHT = data_structures::cht::ConvexHullTrick<IsMinimum, T>;
  using Line = typename CHT::Line;

  std::vector<CHT> nodes;
  int B = -1;
  int root = -1;

  explicit ConvexHullTree(const std::vector<Line>& lines) {
    B = utils::bits::PowerOfTwoThatAtLeast(u64(lines.size()));
    root = 1;

    nodes.resize(2 * B);

    for (int idx = 0; idx < lines.size(); ++idx) {
      int i = idx + B;
      nodes[i] = CHT(lines[idx]);
    }

    for (int i = B - 1; i >= root; --i) {
      auto left = 2 * i;
      auto right = left + 1;
      nodes[i] = CHT(nodes[left], nodes[right]);
    }
  }

  T Get(int l, int r, T x) {
    constexpr auto Identity = []() {
      if constexpr (IsMinimum) {
        return std::numeric_limits<T>::max();
      } else {
        return std::numeric_limits<T>::min();
      }
    }();

    auto combine = [](T a, T b) {
      if constexpr (IsMinimum) {
        return std::min(a, b);
      } else {
        return std::max(a, b);
      }
    };

    auto answer = Identity;
    l += B;
    r += B;
    while (l <= r) {
      if ((l & 1) == 1) {
        T value = nodes[l].GetValue(x);
        answer = combine(answer, value);
      }
      if ((r & 1) == 0) {
        T value = nodes[r].GetValue(x);
        answer = combine(answer, value);
      }
      l = (l + 1) / 2;
      r = (r - 1) / 2;
    }
    return answer;
  }
};

template <typename T>
using MinimumConvexHullTree = ConvexHullTree<true, T>;

template <typename T>
using MaximumConvexHullTree = ConvexHullTree<false, T>;

}  // namespace algo::ranges
