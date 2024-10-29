#include <algo/maths/algebra/power.hpp>
#include <algo/utils/random/random.hpp>
#include <algo/utils/types/modular.hpp>
#include <tests/framework/asserts.hpp>
#include <tests/framework/test.hpp>

using namespace algo::utils::random;

template <typename T>
T LinearPower(T value, int power) {
  T result = 1;
  for (int i = 0; i < power; ++i) {
    result *= value;
  }
  return result;
};

template <typename T>
void TestSmall() {
  for (int value = -10; value <= 10; ++value) {
    for (int power = 0; power <= 15; ++power) {
      auto result = algo::maths::algebra::Power(T(value), power);
      auto expected = LinearPower(T(value), power);
      ASSERT_EQ(result, expected);
    }
  }
};

template <typename Modular>
void TestBig(int k_rep) {
  for (int rep = 0; rep < k_rep; ++rep) {
    Modular value = RandomInt(0, Modular::MOD - 1);
    auto power = RandomInt(0, 1e5);
    auto result = algo::maths::algebra::Power(value, power);
    auto expected = LinearPower(value, power);
    ASSERT_EQ(result, expected);
  }
};

TEST(StressIntSmall) {
  TestSmall<i64>();
}

TEST(StressModular2Small) {
  TestSmall<algo::utils::Modular_2>();
}

TEST(StressModularBigPrimeSmall) {
  TestSmall<algo::utils::Modular_1_000_000_007>();
}

TEST(StressModular2Big) {
  TestBig<algo::utils::Modular_2>(100);
}

TEST(StressModularBigPrimeBig) {
  TestBig<algo::utils::Modular_1_000_000_007>(100);
}

RUN_ALL_TESTS()
