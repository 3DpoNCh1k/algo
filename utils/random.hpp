#include <random>
#include "../header.hpp"

struct RandomGenerator {
  RandomGenerator() {
    Reset(chrono::steady_clock::now().time_since_epoch().count());
  }
  explicit RandomGenerator(u32 seed) {
    Reset(seed);
  }
  void Reset(u32 seed) {
    rng_.seed(seed);
  }
  i64 RandomInt(i64 a, i64 b) {
    return uniform_int_distribution<i64>(a, b)(rng_);
  }
  bool RandomBool() {
    return RandomInt(0, 1) == 0;
  }

  mt19937& GetRng() {
    return rng_;
  }

  mt19937 rng_;
};
