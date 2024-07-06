#pragma once

#include <type_traits>
#include <string>

#include <algo/utils/traits/traits.hpp>

namespace algo::utils {
template <typename T>
std::enable_if_t<traits::has_ToString_v<T>, std::string> ToString(const T&);
}
