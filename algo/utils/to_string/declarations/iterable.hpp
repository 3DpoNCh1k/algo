#pragma once

#include <type_traits>
#include <string>

#include <algo/utils/traits/traits.hpp>

namespace algo::utils {
template <typename T>
std::enable_if_t<!traits::is_std_array_v<T> && !traits::is_std_vector_v<T> &&
                     traits::is_iterable_v<T>,
                 std::string>
ToString(const T&);
}
