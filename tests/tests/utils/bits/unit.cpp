#include <algo/utils/bits.hpp>
#include <algo/utils/meta.hpp>
#include <tests/framework/asserts.hpp>
#include <tests/framework/test.hpp>

namespace bits = algo::utils::bits;

TEST(CountOfOnes) {
  STATIC_ASSERT_EQ(bits::CountOfOnes(u64(0)), 0);
  STATIC_ASSERT_EQ(bits::CountOfOnes(u64(1)), 1);
  STATIC_ASSERT_EQ(bits::CountOfOnes(u64(-1)), 64);
  STATIC_ASSERT_EQ(bits::CountOfOnes(u64(123)), 6);
}

TEST(IsPowerOfTwo) {
  {
    algo::utils::meta::ForLoop<0, 63>([](auto int_number) {
      constexpr auto Value = 1LL << int_number.Value;
      STATIC_ASSERT_TRUE(bits::IsPowerOfTwo(u64(Value)));
    });
  }
  {
    STATIC_ASSERT_FALSE(bits::IsPowerOfTwo(u64(0)));
    STATIC_ASSERT_FALSE(bits::IsPowerOfTwo(u64(3)));
    STATIC_ASSERT_FALSE(bits::IsPowerOfTwo(u64(5)));
    STATIC_ASSERT_FALSE(bits::IsPowerOfTwo(u64(6)));
  }
}

TEST(IndexOfLeastSignificantBit) {
  {
    algo::utils::meta::ForLoop<0, 63>([](auto int_number) {
      constexpr auto Value = 1LL << int_number.Value;
      STATIC_ASSERT_EQ(bits::IndexOfLeastSignificantBit(u64(Value)),
                       int_number.Value);
    });
  }
  {
    STATIC_ASSERT_EQ(bits::IndexOfLeastSignificantBit(u64(0)), -1);
    STATIC_ASSERT_EQ(bits::IndexOfLeastSignificantBit(u64(3)), 0);
    STATIC_ASSERT_EQ(bits::IndexOfLeastSignificantBit(u64(5)), 0);
    STATIC_ASSERT_EQ(bits::IndexOfLeastSignificantBit(u64(6)), 1);
  }
}

TEST(LeastSignificantBitOnly) {
  {
    algo::utils::meta::ForLoop<0, 63>([](auto int_number) {
      constexpr auto Value = 1LL << int_number.Value;
      STATIC_ASSERT_EQ(bits::LeastSignificantBitOnly(u64(Value)), Value);
    });
  }
  {
    STATIC_ASSERT_EQ(bits::LeastSignificantBitOnly(u64(0)), 0);
    STATIC_ASSERT_EQ(bits::LeastSignificantBitOnly(u64(3)), 1);
    STATIC_ASSERT_EQ(bits::LeastSignificantBitOnly(u64(5)), 1);
    STATIC_ASSERT_EQ(bits::LeastSignificantBitOnly(u64(6)), 2);
  }
}

TEST(IndexOfMostSignificantBit) {
  {
    algo::utils::meta::ForLoop<0, 63>([](auto int_number) {
      constexpr auto Value = 1LL << int_number.Value;
      STATIC_ASSERT_EQ(bits::IndexOfMostSignificantBit(u64(Value)),
                       int_number.Value);
    });
  }
  {
    STATIC_ASSERT_EQ(bits::IndexOfMostSignificantBit(u64(0)), -1);
    STATIC_ASSERT_EQ(bits::IndexOfMostSignificantBit(u64(3)), 1);
    STATIC_ASSERT_EQ(bits::IndexOfMostSignificantBit(u64(5)), 2);
    STATIC_ASSERT_EQ(bits::IndexOfMostSignificantBit(u64(6)), 2);
  }
}

TEST(MostSignificantBitOnly) {
  {
    algo::utils::meta::ForLoop<0, 63>([](auto int_number) {
      constexpr auto Value = 1LL << int_number.Value;
      STATIC_ASSERT_EQ(bits::MostSignificantBitOnly(u64(Value)), Value);
    });
  }
  {
    STATIC_ASSERT_EQ(bits::MostSignificantBitOnly(u64(0)), 0);
    STATIC_ASSERT_EQ(bits::MostSignificantBitOnly(u64(3)), 2);
    STATIC_ASSERT_EQ(bits::MostSignificantBitOnly(u64(5)), 4);
    STATIC_ASSERT_EQ(bits::MostSignificantBitOnly(u64(6)), 4);
  }
}

TEST(ExponentOfPowerOfTwoThatAtLeast) {
  {
    algo::utils::meta::ForLoop<0, 63>([](auto int_number) {
      constexpr auto Value = 1LL << int_number.Value;
      STATIC_ASSERT_EQ(bits::ExponentOfPowerOfTwoThatAtLeast(u64(Value)),
                       int_number.Value);
    });
  }
  {
    STATIC_ASSERT_EQ(bits::ExponentOfPowerOfTwoThatAtLeast(u64(0)), 0);
    STATIC_ASSERT_EQ(bits::ExponentOfPowerOfTwoThatAtLeast(u64(3)), 2);
    STATIC_ASSERT_EQ(bits::ExponentOfPowerOfTwoThatAtLeast(u64(5)), 3);
    STATIC_ASSERT_EQ(bits::ExponentOfPowerOfTwoThatAtLeast(u64(6)), 3);
  }
}

TEST(PowerOfTwoThatAtLeast) {
  {
    algo::utils::meta::ForLoop<0, 63>([](auto int_number) {
      constexpr auto Value = 1LL << int_number.Value;
      STATIC_ASSERT_EQ(bits::PowerOfTwoThatAtLeast(u64(Value)), Value);
    });
  }
  {
    STATIC_ASSERT_EQ(bits::PowerOfTwoThatAtLeast(u64(0)), 1);
    STATIC_ASSERT_EQ(bits::PowerOfTwoThatAtLeast(u64(3)), 4);
    STATIC_ASSERT_EQ(bits::PowerOfTwoThatAtLeast(u64(5)), 8);
    STATIC_ASSERT_EQ(bits::PowerOfTwoThatAtLeast(u64(6)), 8);
  }
}

RUN_ALL_TESTS()
