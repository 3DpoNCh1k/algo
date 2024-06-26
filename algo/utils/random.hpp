#pragma once

#include <random>
#include <chrono>

#include <algo/utils/types/types.hpp>

namespace algo::utils::random {
struct RandomGenerator {
  RandomGenerator() {
    Reset(std::chrono::steady_clock::now().time_since_epoch().count());
  }
  explicit RandomGenerator(u32 seed) {
    Reset(seed);
  }
  void Reset(u32 seed) {
    rng_.seed(seed);
  }
  i64 RandomInt(i64 a, i64 b) {
    return std::uniform_int_distribution<i64>(a, b)(rng_);
  }
  bool RandomBool() {
    return RandomInt(0, 1) == 0;
  }

  std::mt19937& GetRng() {
    return rng_;
  }

  std::mt19937 rng_;
};
}  // namespace algo::utils::random
