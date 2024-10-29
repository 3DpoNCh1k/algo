#pragma once

#include <utility>
#include <algo/utils/types/fundamentals.hpp>

namespace algo::binary_search {

namespace details {
template <typename Predicate>
i64 FindFirstTrueImpl(i64 from, i64 to, Predicate&& predicate, bool inverse) {
  i64 l = from;
  i64 r = to + 1;
  while (l < r) {
    i64 m = l + (r - l) / 2;
    if (predicate(m) ^ inverse) {
      r = m;
    } else {
      l = m + 1;
    }
  }
  return l;
};
}  // namespace details
template <typename Predicate>
i64 FindFirstTrue(i64 from, i64 to, Predicate&& predicate) {
  return details::FindFirstTrueImpl(from, to,
                                    std::forward<Predicate>(predicate), false);
};

template <typename Predicate>
i64 FindLastTrue(i64 from, i64 to, Predicate&& predicate) {
  auto first_false = details::FindFirstTrueImpl(
      from, to, std::forward<Predicate>(predicate), true);
  return first_false - 1;
};

template <typename Predicate>
i64 FindFirstFalse(i64 from, i64 to, Predicate&& predicate) {
  auto first_false = details::FindFirstTrueImpl(
      from, to, std::forward<Predicate>(predicate), true);
  return first_false;
};

template <typename Predicate>
i64 FindLastFalse(i64 from, i64 to, Predicate&& predicate) {
  auto first_true = details::FindFirstTrueImpl(
      from, to, std::forward<Predicate>(predicate), false);
  return first_true - 1;
};
}  // namespace algo::binary_search
