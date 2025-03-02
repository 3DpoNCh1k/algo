#include <algo/maths/algebra/power.hpp>
#include <algo/utils/random/random.hpp>
#include <algo/utils/types/modular.hpp>
#include <tests/framework/asserts.hpp>
#include <tests/framework/test.hpp>
#include "algo/maths/algebra/matrix/matrix.hpp"

using algo::utils::random::RandomInt;

template <typename T>
T LinearPower(T value, int power) {
  T result = 1;
  for (int i = 0; i < power; ++i) {
    result *= value;
  }
  return result;
};

template <typename T>
auto LinearPower(algo::maths::algebra::matrix::Matrix<T> value, int power) {
  ASSERT_TRUE(value.IsSquare());
  auto result = algo::maths::algebra::matrix::Matrix<T>::Identity(value.k_row);
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

template <typename T>
void TestSmallMatrix() {
  for(int size = 1; size <= 5; ++size) {
    for(int rep = 0; rep < 100; ++rep) {
      algo::maths::algebra::matrix::Matrix<T> a(size);
      for(int row = 0; row < size; ++row) {
        for(int col = 0; col < size; ++col) {
          a[row][col] = RandomInt(-5, 5);
        }
      }
      for (int power = 0; power <= 7; ++power) {
        auto result = algo::maths::algebra::Power(a, power);
        auto expected = LinearPower(a, power);
        ASSERT_EQ(result, expected);
      }
    }
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

TEST(StressIntSmallMatrix) {
  TestSmallMatrix<i64>();
}

TEST(StressModular2SmallMatrix) {
  TestSmallMatrix<i64>();
}

TEST(StressModularBigPrimeSmallMatirx) {
  TestSmallMatrix<algo::utils::Modular_1_000_000_007>();
}


RUN_ALL_TESTS()
