#pragma once

#include <type_traits>
#include <cassert>

#include <algo/utils/types/fundamentals.hpp>
#include <algo/maths/algebra/modular_inverse.hpp>

namespace algo::utils {
template <typename ValueType, ValueType Mod,
          typename = std::enable_if_t<std::is_integral_v<ValueType> &&
                                      std::is_signed_v<ValueType>>>
struct Modular {
  static constexpr ValueType MOD = Mod;
  ValueType value = 0;

  Modular(){};
  template <typename T,
            typename = std::enable_if_t<std::is_integral_v<T> &&
                                        std::is_signed_v<ValueType>>>
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

  // *
  Modular operator/(const Modular& that) const {
    auto inverse = maths::algebra::ModularInverse(that.value, MOD);
    assert(inverse != -1);
    return (value * inverse) % MOD;
  }

  Modular& operator/=(const Modular& that) {
    *this = *this / that;
    return *this;
  }
  // *

  bool operator==(const Modular& that) const {
    return value == that.value;
  }

  bool operator!=(const Modular& that) const {
    return !(value == that.value);
  }

  bool IsValid() const {
    return value >= 0 && value < MOD;
  }

  ValueType GetValue() const {
    return value;
  }

  std::string ToString() const {
    std::stringstream ss;
    ss << "(" << value << " % " << MOD << ")";
    return ss.str();
  };
};

template <typename T, typename ValueType, ValueType Mod>
Modular<ValueType, Mod> operator+(const T& that,
                                  const Modular<ValueType, Mod>& modular) {
  return modular + that;
}

template <typename T, typename ValueType, ValueType Mod>
Modular<ValueType, Mod> operator-(const T& that,
                                  const Modular<ValueType, Mod>& modular) {
  return Modular<ValueType, Mod>(that) - modular;
}

template <typename T, typename ValueType, ValueType Mod>
Modular<ValueType, Mod> operator*(const T& that,
                                  const Modular<ValueType, Mod>& modular) {
  return modular * that;
}

template <typename T, typename ValueType, ValueType Mod>
Modular<ValueType, Mod> operator/(const T& that,
                                  const Modular<ValueType, Mod>& modular) {
  return modular / that;
}

template <typename T, typename ValueType, ValueType Mod>
bool operator==(const T& that, const Modular<ValueType, Mod>& modular) {
  return modular == that;
}

template <typename T, typename ValueType, ValueType Mod>
bool operator!=(const T& that, const Modular<ValueType, Mod>& modular) {
  return modular != that;
}

// NOLINTBEGIN
using Modular_2 = Modular<i64, 2>;
using Modular_1_000_000_007 = Modular<i64, 1'000'000'007>;
using Modular_1_000_000_009 = Modular<i64, 1'000'000'009>;
using Modular_998_244_353 = Modular<i64, 998'244'353>;
// NOLINTEND
}  // namespace algo::utils
