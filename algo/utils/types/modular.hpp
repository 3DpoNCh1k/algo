#pragma once

#include <type_traits>

#include <algo/utils/types/types.hpp>

namespace algo::utils {
template <typename InternalType, InternalType Mod,
          typename = std::enable_if_t<std::is_integral_v<InternalType> &&
                                      std::is_signed_v<InternalType>>>
struct Modular {
  static constexpr InternalType MOD = Mod;
  InternalType value = 0;

  Modular(){};
  template <typename T,
            typename = std::enable_if_t<std::is_integral_v<T> &&
                                        std::is_signed_v<InternalType>>>
  // NOLINTNEXTLINE
  Modular(T v) {
    v %= MOD;
    if (v < 0) {
      v += MOD;
    }
    value = v;
  }
  Modular(const Modular&) = default;
  Modular(Modular&&) = default;
  Modular& operator=(const Modular&) = default;
  Modular& operator=(Modular&&) = default;

  // +
  Modular operator+(const Modular& that) const {
    return (value + that.value) % MOD;
  }
  Modular& operator+=(const Modular& that) {
    *this = *this + that;
    return *this;
  }
  // +

  // Unary -
  Modular operator-() const {
    return value == 0 ? 0 : MOD - value;
  }
  // Unary -

  // -
  Modular operator-(const Modular& that) const {
    return *this + (-that);
  }
  Modular& operator-=(const Modular& that) {
    *this = *this - that;
    return *this;
  }
  // -

  // *
  Modular operator*(const Modular& that) const {
    return (value * that.value) % MOD;
  }

  Modular& operator*=(const Modular& that) {
    *this = *this * that;
    return *this;
  }
  // *

  // TODO: operator/

  bool operator==(const Modular& that) const {
    return value == that.value;
  }

  bool operator!=(const Modular& that) const {
    return !(value == that.value);
  }

  bool IsValid() const {
    return value >= 0 && value < MOD;
  }

  InternalType GetValue() {
    return value;
  }
};

template <typename T, typename ModularInternalType, ModularInternalType Mod>
Modular<ModularInternalType, Mod> operator+(
    const T& that, const Modular<ModularInternalType, Mod>& modular) {
  return modular + that;
}

template <typename T, typename ModularInternalType, ModularInternalType Mod>
Modular<ModularInternalType, Mod> operator-(
    const T& that, const Modular<ModularInternalType, Mod>& modular) {
  return Modular<ModularInternalType, Mod>(that) - modular;
}

template <typename T, typename ModularInternalType, ModularInternalType Mod>
Modular<ModularInternalType, Mod> operator*(
    const T& that, const Modular<ModularInternalType, Mod>& modular) {
  return modular * that;
}

template <typename T, typename ModularInternalType, ModularInternalType Mod>
bool operator==(const T& that,
                const Modular<ModularInternalType, Mod>& modular) {
  return modular == that;
}

template <typename T, typename ModularInternalType, ModularInternalType Mod>
bool operator!=(const T& that,
                const Modular<ModularInternalType, Mod>& modular) {
  return modular != that;
}

// NOLINTBEGIN
using Modular_2 = Modular<i64, 2>;
using Modular_1_000_000_007 = Modular<i64, 1'000'000'007>;
using Modular_1_000_000_009 = Modular<i64, 1'000'000'009>;
// NOLINTEND
}  // namespace algo::utils
