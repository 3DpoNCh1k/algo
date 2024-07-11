#pragma once

#include <random>
#include <chrono>

#include <algo/utils/types/fundamentals.hpp>

namespace algo::utils::generators {
struct RandomGenerator {
  using Real = double;

  RandomGenerator() {
    Reset(std::chrono::steady_clock::now().time_since_epoch().count());
  }
  explicit RandomGenerator(u32 seed) {
    Reset(seed);
  }
  void Reset(u32 seed) {
    engine_.seed(seed);
  }
  i64 GetInt(i64 a, i64 b) {
    return std::uniform_int_distribution<i64>(a, b)(engine_);
  }
  bool GetBool() {
    return GetInt(0, 1) == 0;
  }

  Real GetReal(Real a, Real b) {
    return std::uniform_real_distribution<Real>(a, b)(engine_);
  }

  std::mt19937& GetEngine() {
    return engine_;
  }

 private:
  std::mt19937 engine_;
};
}  // namespace algo::utils::generators
