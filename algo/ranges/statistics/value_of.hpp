
#pragma once

namespace algo::ranges::statistics {
template <typename Statistics>
struct ValueOf {
  using Value = typename Statistics::Value;

  explicit ValueOf(const Value& value)
      : value(value) {
  }

  const Value& value;
};
}  // namespace algo::ranges::statistics
