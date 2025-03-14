#include <algo/utils/bits.hpp>
#include <tests/framework/asserts.hpp>

#include "helpers.hpp"
#include <tests/framework/test.hpp>

void Test(std::vector<int> coefficients, std::vector<Complex> values) {
  assert(coefficients.size() == values.size());
  assert(algo::utils::bits::IsPowerOfTwo(u64(coefficients.size())));

  auto fft = FFT(coefficients.size());
  auto fft_values = fft.Transform(AsComplexes(coefficients));
  {
    auto equal = AreEqual(values, fft_values);
    ASSERT_TRUE(equal);
  }
  auto fft_coefficients = AsInts(fft.Inverse(values));
  {
    auto equal = coefficients == fft_coefficients;
    ASSERT_TRUE(equal);
  }
}

void TestMultiply(std::vector<int> a, std::vector<int> b,
                  std::vector<int> expected) {
  int n = algo::utils::bits::PowerOfTwoThatAtLeast(u64(a.size() + b.size()));
  a.resize(n);
  b.resize(n);
  expected.resize(n);
  auto result = AsInts(FFT(n).Multiply(AsComplexes(a), AsComplexes(b)));
  ASSERT_EQ(result, expected);
};

TEST(Transform1) {
  Test({1}, {1});
}
TEST(Transform2) {
  Test({1, 2}, {3, -1});
}
TEST(Transform3) {
  Test({1, 2, 3, 4}, {10, {-2, -2}, -2, {-2, 2}});
}

TEST(Multiply1) {
  TestMultiply({1}, {1}, {1});
}
TEST(Multiply2) {
  TestMultiply({1, 2, 3, 4, 5}, {-1, -2, -3},
               {-1, -4, -10, -16, -22, -22, -15});
}
TEST(Multiply3) {
  TestMultiply({0, 1, 0, -2}, {-3, 0, 4}, {0, -3, 0, 10, 0, -8});
}

RUN_ALL_TESTS()
