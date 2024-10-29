#include <algo/utils/meta.hpp>
#include <tests/framework/asserts.hpp>
#include <tests/framework/test.hpp>

using namespace algo::utils::meta;

TEST(IntNumber) {
  STATIC_ASSERT_EQ(IntNumber<-1>::Value, -1);
  STATIC_ASSERT_EQ(IntNumber<1>::Value, 1);
}

TEST(Concat) {
  {
    constexpr auto SeqA = IntSeq<1, 2>{};
    constexpr auto SeqB = IntSeq<3, 4>{};
    constexpr auto SeqAB = Concat(SeqA, SeqB);
    constexpr auto Expected = IntSeq<1, 2, 3, 4>();
    constexpr auto IsSame = std::is_same_v<decltype(SeqAB), decltype(Expected)>;
    STATIC_ASSERT_TRUE(IsSame);
  }
  {
    constexpr auto SeqA = IntSeq<>{};
    constexpr auto SeqB = IntSeq<1>{};
    constexpr auto SeqAB = Concat(SeqA, SeqB);
    constexpr auto Expected = IntSeq<1>();
    constexpr auto IsSame = std::is_same_v<decltype(SeqAB), decltype(Expected)>;
    STATIC_ASSERT_TRUE(IsSame);
  }
  {
    constexpr auto SeqA = IntSeq<1>{};
    constexpr auto SeqB = IntSeq<>{};
    constexpr auto SeqAB = Concat(SeqA, SeqB);
    constexpr auto Expected = IntSeq<1>();
    constexpr auto IsSame = std::is_same_v<decltype(SeqAB), decltype(Expected)>;
    STATIC_ASSERT_TRUE(IsSame);
  }
  {
    constexpr auto SeqA = IntSeq<>{};
    constexpr auto SeqB = IntSeq<>{};
    constexpr auto SeqAB = Concat(SeqA, SeqB);
    constexpr auto Expected = IntSeq<>();
    constexpr auto IsSame = std::is_same_v<decltype(SeqAB), decltype(Expected)>;
    STATIC_ASSERT_TRUE(IsSame);
  }
}

TEST(IntRange) {
  {
    constexpr auto RangeSeq = IntRange<0, 0>();
    constexpr auto Expected = IntSeq<0>();
    constexpr auto IsSame =
        std::is_same_v<decltype(RangeSeq), decltype(Expected)>;
    STATIC_ASSERT_TRUE(IsSame);
  }
  {
    constexpr auto RangeSeq = IntRange<1, 0>();
    constexpr auto Expected = IntSeq<>();
    constexpr auto IsSame =
        std::is_same_v<decltype(RangeSeq), decltype(Expected)>;
    STATIC_ASSERT_TRUE(IsSame);
  }
  {
    constexpr auto RangeSeq = IntRange<-2, 3>();
    constexpr auto Expected = IntSeq<-2, -1, 0, 1, 2, 3>();
    constexpr auto IsSame =
        std::is_same_v<decltype(RangeSeq), decltype(Expected)>;
    STATIC_ASSERT_TRUE(IsSame);
  }
}

template <int L, int R>
constexpr void CalculateSum() {
  constexpr int S = (L + R) * (R - L + 1) / 2;
  int s = 0;
  auto func = [&s](auto num) {
    STATIC_ASSERT_TRUE(num.Value >= L);
    STATIC_ASSERT_TRUE(num.Value <= R);
    s += num.Value;
  };
  ForLoop<L, R>(func);
  ASSERT_EQ(s, S);
}

TEST(ForLoop) {
  CalculateSum<1, 3>();
  CalculateSum<-15, 17>();
  CalculateSum<0, 0>();
  CalculateSum<1, 0>();
}

RUN_ALL_TESTS()
