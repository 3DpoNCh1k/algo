#include <algo/utils/types/modular.hpp>
#include <algo/utils/types/fundamentals.hpp>
#include <tests/framework/asserts.hpp>
#include <algo/utils/meta.hpp>
#include <tests/framework/test.hpp>

template <typename ValueType, ValueType Mod>
struct Tester {
  using ModularType = algo::utils::Modular<ValueType, Mod>;

  static constexpr i64 MOD = Mod;
  static const i64 MinValue = -10;
  static const i64 MaxValue = 10;

  void TestCreation() {
    {
      ModularType value;
      ASSERT_TRUE(value.IsValid());
      ASSERT_TRUE(value == 0);
      ASSERT_TRUE(value.GetValue() == 0);
    }
    for (i64 i = MinValue; i <= MaxValue; ++i) {
      auto remainder = ((i % MOD) + MOD) % MOD;
      auto value = ModularType(i);
      ASSERT_TRUE(value.IsValid());
      ASSERT_TRUE(value == remainder);
      ASSERT_TRUE(value.GetValue() == remainder);
    }
  }

  void TestAddition() {
    for (i64 first = MinValue; first <= MaxValue; ++first) {
      for (i64 second = MinValue; second <= MaxValue; ++second) {
        auto remainder = (((first + second) % MOD) + MOD) % MOD;
        {
          auto value = ModularType(first) + second;
          ASSERT_TRUE(value.IsValid());
          ASSERT_TRUE(value == remainder);
          ASSERT_TRUE(value.GetValue() == remainder);
        }
        {
          auto value = first + ModularType(second);
          ASSERT_TRUE(value.IsValid());
          ASSERT_TRUE(value == remainder);
          ASSERT_TRUE(value.GetValue() == remainder);
        }
        {
          auto value = ModularType(first) + ModularType(second);
          ASSERT_TRUE(value.IsValid());
          ASSERT_TRUE(value == remainder);
          ASSERT_TRUE(value.GetValue() == remainder);
        }
      }
    }
    ModularType value = 0;
    i64 remainder = 0;
    for (i64 add = MinValue; add <= MaxValue; ++add) {
      value += add;
      remainder = (((remainder + add) % MOD) + MOD) % MOD;
      ASSERT_TRUE(value.IsValid());
      ASSERT_TRUE(value == remainder);
      ASSERT_TRUE(value.GetValue() == remainder);
    }
  }

  void TestSubstraction() {
    for (i64 first = MinValue; first <= MaxValue; ++first) {
      for (i64 second = MinValue; second <= MaxValue; ++second) {
        auto remainder = (((first - second) % MOD) + MOD) % MOD;
        {
          auto value = ModularType(first) - second;
          ASSERT_TRUE(value.IsValid());
          ASSERT_TRUE(value == remainder);
          ASSERT_TRUE(value.GetValue() == remainder);
        }
        {
          auto value = first - ModularType(second);
          ASSERT_TRUE(value.IsValid());
          ASSERT_TRUE(value == remainder);
          ASSERT_TRUE(value.GetValue() == remainder);
        }
        {
          auto value = ModularType(first) - ModularType(second);
          ASSERT_TRUE(value.IsValid());
          ASSERT_TRUE(value == remainder);
          ASSERT_TRUE(value.GetValue() == remainder);
        }
      }
    }

    ModularType value = 0;
    i64 remainder = 0;
    for (i64 sub = MinValue; sub <= MaxValue; ++sub) {
      value -= sub;
      remainder = (((remainder - sub) % MOD) + MOD) % MOD;
      ASSERT_TRUE(value.IsValid());
      ASSERT_TRUE(value == remainder);
      ASSERT_TRUE(value.GetValue() == remainder);
    }
  }

  void TestMultiplication() {
    for (i64 first = MinValue; first <= MaxValue; ++first) {
      for (i64 second = MinValue; second <= MaxValue; ++second) {
        auto remainder = (((first * second) % MOD) + MOD) % MOD;
        {
          auto value = ModularType(first) * second;
          ASSERT_TRUE(value.IsValid());
          ASSERT_TRUE(value == remainder);
          ASSERT_TRUE(value.GetValue() == remainder);
        }
        {
          auto value = first * ModularType(second);
          ASSERT_TRUE(value.IsValid());
          ASSERT_TRUE(value == remainder);
          ASSERT_TRUE(value.GetValue() == remainder);
        }
        {
          auto value = ModularType(first) * ModularType(second);
          ASSERT_TRUE(value.IsValid());
          ASSERT_TRUE(value == remainder);
          ASSERT_TRUE(value.GetValue() == remainder);
        }
      }
    }

    ModularType value = 0;
    i64 remainder = 0;
    for (i64 mul = MinValue; mul <= MaxValue; ++mul) {
      value *= mul;
      remainder = (((remainder * mul) % MOD) + MOD) % MOD;
      ASSERT_TRUE(value.IsValid());
      ASSERT_TRUE(value == remainder);
      ASSERT_TRUE(value.GetValue() == remainder);
    }
  }

  void Test() {
    TestCreation();
    TestAddition();
    TestSubstraction();
    TestMultiplication();
  }
};

TEST(From1To10i64) {
  algo::utils::meta::ForLoop<1, 10>([](auto int_number) {
    Tester<i64, int_number.Value>().Test();
  });
}

TEST(13i32) {
  Tester<i32, 13>().Test();
}

TEST(17i16) {
  Tester<i16, 17>().Test();
}

TEST(37i8) {
  Tester<i8, 37>().Test();
}

RUN_ALL_TESTS()
