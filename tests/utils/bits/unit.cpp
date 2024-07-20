#include <algo/utils/bits.hpp>
#include "algo/utils/meta.hpp"
#include "tests/testing/asserts.hpp"

using namespace algo::utils::bits;

void TestCountOfOnes() {
  STATIC_ASSERT_EQ(CountOfOnes(u64(0)), 0);
  STATIC_ASSERT_EQ(CountOfOnes(u64(1)), 1);
  STATIC_ASSERT_EQ(CountOfOnes(u64(-1)), 64);
  STATIC_ASSERT_EQ(CountOfOnes(u64(123)), 6);
}

void TestIsPowerOfTwo() {
  {
    algo::utils::meta::ForLoop<0, 63>([](auto int_number) {
      constexpr auto Value = 1LL << int_number.Value;
      STATIC_ASSERT_TRUE(IsPowerOfTwo(u64(Value)));
    });
  }
  {
    STATIC_ASSERT_FALSE(IsPowerOfTwo(u64(0)));
    STATIC_ASSERT_FALSE(IsPowerOfTwo(u64(3)));
    STATIC_ASSERT_FALSE(IsPowerOfTwo(u64(5)));
    STATIC_ASSERT_FALSE(IsPowerOfTwo(u64(6)));
  }
}

void TestIndexOfLeastSignificantBit() {
  {
    algo::utils::meta::ForLoop<0, 63>([](auto int_number) {
      constexpr auto Value = 1LL << int_number.Value;
      STATIC_ASSERT_EQ(IndexOfLeastSignificantBit(u64(Value)),
                       int_number.Value);
    });
  }
  {
    STATIC_ASSERT_EQ(IndexOfLeastSignificantBit(u64(0)), -1);
    STATIC_ASSERT_EQ(IndexOfLeastSignificantBit(u64(3)), 0);
    STATIC_ASSERT_EQ(IndexOfLeastSignificantBit(u64(5)), 0);
    STATIC_ASSERT_EQ(IndexOfLeastSignificantBit(u64(6)), 1);
  }
}

void TestLeastSignificantBitOnly() {
  {
    algo::utils::meta::ForLoop<0, 63>([](auto int_number) {
      constexpr auto Value = 1LL << int_number.Value;
      STATIC_ASSERT_EQ(LeastSignificantBitOnly(u64(Value)), Value);
    });
  }
  {
    STATIC_ASSERT_EQ(LeastSignificantBitOnly(u64(0)), 0);
    STATIC_ASSERT_EQ(LeastSignificantBitOnly(u64(3)), 1);
    STATIC_ASSERT_EQ(LeastSignificantBitOnly(u64(5)), 1);
    STATIC_ASSERT_EQ(LeastSignificantBitOnly(u64(6)), 2);
  }
}

void TestIndexOfMostSignificantBit() {
  {
    algo::utils::meta::ForLoop<0, 63>([](auto int_number) {
      constexpr auto Value = 1LL << int_number.Value;
      STATIC_ASSERT_EQ(IndexOfMostSignificantBit(u64(Value)), int_number.Value);
    });
  }
  {
    STATIC_ASSERT_EQ(IndexOfMostSignificantBit(u64(0)), -1);
    STATIC_ASSERT_EQ(IndexOfMostSignificantBit(u64(3)), 1);
    STATIC_ASSERT_EQ(IndexOfMostSignificantBit(u64(5)), 2);
    STATIC_ASSERT_EQ(IndexOfMostSignificantBit(u64(6)), 2);
  }
}

void TestMostSignificantBitOnly() {
  {
    algo::utils::meta::ForLoop<0, 63>([](auto int_number) {
      constexpr auto Value = 1LL << int_number.Value;
      STATIC_ASSERT_EQ(MostSignificantBitOnly(u64(Value)), Value);
    });
  }
  {
    STATIC_ASSERT_EQ(MostSignificantBitOnly(u64(0)), 0);
    STATIC_ASSERT_EQ(MostSignificantBitOnly(u64(3)), 2);
    STATIC_ASSERT_EQ(MostSignificantBitOnly(u64(5)), 4);
    STATIC_ASSERT_EQ(MostSignificantBitOnly(u64(6)), 4);
  }
}

void TestExponentOfPowerOfTwoThatAtLeast() {
  {
    algo::utils::meta::ForLoop<0, 63>([](auto int_number) {
      constexpr auto Value = 1LL << int_number.Value;
      STATIC_ASSERT_EQ(ExponentOfPowerOfTwoThatAtLeast(u64(Value)),
                       int_number.Value);
    });
  }
  {
    STATIC_ASSERT_EQ(ExponentOfPowerOfTwoThatAtLeast(u64(0)), 0);
    STATIC_ASSERT_EQ(ExponentOfPowerOfTwoThatAtLeast(u64(3)), 2);
    STATIC_ASSERT_EQ(ExponentOfPowerOfTwoThatAtLeast(u64(5)), 3);
    STATIC_ASSERT_EQ(ExponentOfPowerOfTwoThatAtLeast(u64(6)), 3);
  }
}

void TestPowerOfTwoThatAtLeast() {
  {
    algo::utils::meta::ForLoop<0, 63>([](auto int_number) {
      constexpr auto Value = 1LL << int_number.Value;
      STATIC_ASSERT_EQ(PowerOfTwoThatAtLeast(u64(Value)), Value);
    });
  }
  {
    STATIC_ASSERT_EQ(PowerOfTwoThatAtLeast(u64(0)), 1);
    STATIC_ASSERT_EQ(PowerOfTwoThatAtLeast(u64(3)), 4);
    STATIC_ASSERT_EQ(PowerOfTwoThatAtLeast(u64(5)), 8);
    STATIC_ASSERT_EQ(PowerOfTwoThatAtLeast(u64(6)), 8);
  }
}

int main() {
  TestCountOfOnes();
  TestIsPowerOfTwo();
  TestIndexOfLeastSignificantBit();
  TestLeastSignificantBitOnly();
  TestIndexOfMostSignificantBit();
  TestMostSignificantBitOnly();
  TestExponentOfPowerOfTwoThatAtLeast();
  TestPowerOfTwoThatAtLeast();
}
