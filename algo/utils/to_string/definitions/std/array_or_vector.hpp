#pragma once

#include <type_traits>
#include <sstream>
#include <string>

#include <algo/utils/to_string/declarations/all.hpp>
#include <algo/utils/traits/traits.hpp>
#include <algo/utils/traits/std/dimension.hpp>

namespace algo::utils {
template <class T>
std::enable_if_t<traits::is_std_array_v<T> || traits::is_std_vector_v<T>,
                 std::string>
ToString(const T& arr_or_vec) {
  std::stringstream result;
  result << "[";
  for (int i = 0; i < int(arr_or_vec.size()); ++i) {
    if constexpr (traits::dimension_v<decltype(arr_or_vec[i])> > 0) {
      result << "\n";
    }
    result << "i=" + ToString(i) + ": ";
    result << ToString(arr_or_vec[i]);
    result << (i == int(arr_or_vec.size()) - 1 ? "" : ", ");
  }
  result << "]";
  return result.str();
}
}  // namespace algo::utils
