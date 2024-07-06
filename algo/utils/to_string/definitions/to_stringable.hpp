#pragma once

#include <type_traits>
#include <string>

#include <algo/utils/traits/traits.hpp>

namespace algo::utils {
template <typename T>
std::enable_if_t<traits::is_to_stringable_v<T>, std::string> ToString(
    const T& value) {
  return std::to_string(value);
}
}  // namespace algo::utils
