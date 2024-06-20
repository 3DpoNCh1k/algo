#include <array>
#include <cstddef>
#include <vector>

// NOLINTBEGIN
template <class T>
struct std::rank<std::vector<T>>
    : std::integral_constant<std::size_t, std::rank<T>::value + 1> {};

template <class T, size_t N>
struct std::rank<std::array<T, N>>
    : std::integral_constant<std::size_t, rank<T>::value + 1> {};

template <typename T>
struct std::rank<T const> : rank<T> {};

template <typename T>
struct std::rank<T&> : rank<T> {};

template <typename T>
struct std::rank<T&&> : rank<T> {};
// NOLINTEND