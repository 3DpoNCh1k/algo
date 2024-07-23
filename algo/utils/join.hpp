#pragma once

#include <sstream>
#include <string>

#include <algo/utils/to_string/to_string.hpp>

namespace algo::utils {
struct Parameters {
  std::string prefix = "";
  std::string suffix = "";
  std::string separator = ", ";
};

template <typename Iterable, typename Transform>
std::string JoinToString(const Iterable& iterable, Transform&& transform,
                         const Parameters& parameters = Parameters{}) {
  std::stringstream ss;
  ss << parameters.prefix;
  bool first = true;
  for (auto& e : iterable) {
    if (!first) {
      ss << parameters.separator;
    }
    ss << transform(e);
    first = false;
  }
  ss << parameters.suffix;
  return ss.str();
}

template <typename Iterable>
std::string JoinToString(const Iterable& iterable,
                         const Parameters& parameters = Parameters{}) {
  return JoinToString(
      iterable,
      [](auto& e) {
        return ToString(e);
      },
      parameters);
}
}  // namespace algo::utils
