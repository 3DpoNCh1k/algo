#include <algo/maths/algebra/power.hpp>
#include "algo/utils/generators/random.hpp"
#include "algo/utils/types/modular.hpp"
#include "tests/testing/asserts.hpp"

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
  auto random = algo::utils::generators::RandomGenerator(0);
  for (int rep = 0; rep < k_rep; ++rep) {
    Modular value = random.GetInt(0, Modular::MOD - 1);
    auto power = random.GetInt(0, 1e5);
    auto result = algo::maths::algebra::Power(value, power);
    auto expected = LinearPower(value, power);
    ASSERT_EQ(result, expected);
  }
};

int main() {
  TestSmall<i64>();
  TestSmall<algo::utils::Modular_2>();
  TestSmall<algo::utils::Modular_1_000_000_007>();

  TestBig<algo::utils::Modular_2>(100);
  TestBig<algo::utils::Modular_1_000_000_007>(100);
}
