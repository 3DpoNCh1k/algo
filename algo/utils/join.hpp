#pragma once

#include <sstream>
#include <string>

#include <algo/utils/to_string/to_string.hpp>

namespace algo::utils {

template <typename Iterable, typename Transform>
std::string JoinToString(const Iterable& iterable, Transform&& transform,
                         const std::string& separator) {
  std::stringstream ss;
  bool first = true;
  for (auto& e : iterable) {
    if (!first) {
      ss << separator;
    }
    ss << transform(e);
    first = false;
  }
  return ss.str();
}

template <typename Iterable>
std::string JoinToString(const Iterable& iterable,
                         const std::string& separator = " ") {
  return JoinToString(
      iterable,
      [](auto& e) {
        return ToString(e);
      },
      separator);
}
}  // namespace algo::utils
