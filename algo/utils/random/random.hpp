#pragma once

#include <algorithm>
#include <random>
#include <chrono>

#include <algo/utils/types/fundamentals.hpp>

namespace algo::utils::random {
namespace details {
struct Random {
  Random() {
    Reset();
  }

  explicit Random(u32 seed) {
    Reset(seed);
  }

  void Reset(u32 seed) {
    engine_.seed(seed);
  }

  void Reset() {
    Reset(std::chrono::steady_clock::now().time_since_epoch().count());
  }

  i64 Int(i64 a, i64 b) {
    return std::uniform_int_distribution<i64>(a, b)(engine_);
  }

  bool Maybe(u32 k_outcome) {
    return Int(1, k_outcome) == 1;
  }

  bool Maybe() {
    return Maybe(2);
  }

  ::Real Real(::Real a, ::Real b) {
    return std::uniform_real_distribution<::Real>(a, b)(engine_);
  }

  template <typename T>
  void Shuffle(T& items) {
    std::shuffle(items.begin(), items.end(), engine_);
  }

 private:
  std::mt19937 engine_;
};
static Random random(123);
}  // namespace details

void RandomReset(u32 seed) {
  details::random.Reset(seed);
}

void RandomReset() {
  details::random.Reset();
}

i64 RandomInt(i64 a, i64 b) {
  return details::random.Int(a, b);
}

bool Maybe(u32 k_outcome) {
  return details::random.Maybe(k_outcome);
}

bool Maybe() {
  return details::random.Maybe();
}

Real RandomReal(Real a, Real b) {
  return details::random.Real(a, b);
}

template <typename T>
void Shuffle(T& items) {
  return details::random.Shuffle(items);
}
}  // namespace algo::utils::random
