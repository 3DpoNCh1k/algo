#include <algo/utils/types/modular.hpp>
#include <algo/utils/types/fundamentals.hpp>
#include <tests/framework/asserts.hpp>

using namespace algo::utils;

template <typename ValueType, ValueType Mod>
struct Tester {
  using ModularType = Modular<ValueType, Mod>;

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

void Test64() {
  Tester<i64, 1>().Test();
  Tester<i64, 2>().Test();
  Tester<i64, 3>().Test();
  Tester<i64, 4>().Test();
  Tester<i64, 5>().Test();
  Tester<i64, 6>().Test();
  Tester<i64, 7>().Test();
  Tester<i64, 8>().Test();
  Tester<i64, 9>().Test();
  Tester<i64, 10>().Test();
}

void Test32() {
  Tester<i32, 13>().Test();
}

void Test16() {
  Tester<i16, 17>().Test();
}

void Test8() {
  Tester<i8, 37>().Test();
}

int main() {
  Test8();
  Test16();
  Test32();
  Test64();
}
