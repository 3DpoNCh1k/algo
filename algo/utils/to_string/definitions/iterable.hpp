#pragma once

#include <type_traits>
#include <sstream>
#include <string>

#include <algo/utils/to_string/declarations/all.hpp>
#include <algo/utils/traits/traits.hpp>

namespace algo::utils {
template <typename T>
std::enable_if_t<!traits::is_std_array_v<T> && !traits::is_std_vector_v<T> &&
                     traits::is_iterable_v<T>,
                 std::string>
ToString(const T& iterable) {
  std::stringstream result;
  result << "{";
  int i = 0;
  for (const auto& entry : iterable) {
    if constexpr (traits::dimension_v<decltype(entry)> > 0) {
      result << "\n";
    }
    result << ToString(entry);
    result << (i == int(iterable.size()) - 1 ? "" : ", ");
    ++i;
  }
  result << "}";
  return result.str();
}
}  // namespace algo::utils
