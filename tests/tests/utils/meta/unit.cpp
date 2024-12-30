#include <algo/utils/meta.hpp>
#include <tests/framework/asserts.hpp>
#include <tests/framework/test.hpp>

namespace meta = algo::utils::meta;

TEST(IntNumber) {
  STATIC_ASSERT_EQ(meta::IntNumber<-1>::Value, -1);
  STATIC_ASSERT_EQ(meta::IntNumber<1>::Value, 1);
}

TEST(Concat) {
  {
    constexpr auto SeqA = meta::IntSeq<1, 2>{};
    constexpr auto SeqB = meta::IntSeq<3, 4>{};
    constexpr auto SeqAB = meta::Concat(SeqA, SeqB);
    constexpr auto Expected = meta::IntSeq<1, 2, 3, 4>();
    constexpr auto IsSame = std::is_same_v<decltype(SeqAB), decltype(Expected)>;
    STATIC_ASSERT_TRUE(IsSame);
  }
  {
    constexpr auto SeqA = meta::IntSeq<>{};
    constexpr auto SeqB = meta::IntSeq<1>{};
    constexpr auto SeqAB = meta::Concat(SeqA, SeqB);
    constexpr auto Expected = meta::IntSeq<1>();
    constexpr auto IsSame = std::is_same_v<decltype(SeqAB), decltype(Expected)>;
    STATIC_ASSERT_TRUE(IsSame);
  }
  {
    constexpr auto SeqA = meta::IntSeq<1>{};
    constexpr auto SeqB = meta::IntSeq<>{};
    constexpr auto SeqAB = meta::Concat(SeqA, SeqB);
    constexpr auto Expected = meta::IntSeq<1>();
    constexpr auto IsSame = std::is_same_v<decltype(SeqAB), decltype(Expected)>;
    STATIC_ASSERT_TRUE(IsSame);
  }
  {
    constexpr auto SeqA = meta::IntSeq<>{};
    constexpr auto SeqB = meta::IntSeq<>{};
    constexpr auto SeqAB = meta::Concat(SeqA, SeqB);
    constexpr auto Expected = meta::IntSeq<>();
    constexpr auto IsSame = std::is_same_v<decltype(SeqAB), decltype(Expected)>;
    STATIC_ASSERT_TRUE(IsSame);
  }
}

TEST(IntRange) {
  {
    constexpr auto RangeSeq = meta::IntRange<0, 0>();
    constexpr auto Expected = meta::IntSeq<0>();
    constexpr auto IsSame =
        std::is_same_v<decltype(RangeSeq), decltype(Expected)>;
    STATIC_ASSERT_TRUE(IsSame);
  }
  {
    constexpr auto RangeSeq = meta::IntRange<1, 0>();
    constexpr auto Expected = meta::IntSeq<>();
    constexpr auto IsSame =
        std::is_same_v<decltype(RangeSeq), decltype(Expected)>;
    STATIC_ASSERT_TRUE(IsSame);
  }
  {
    constexpr auto RangeSeq = meta::IntRange<-2, 3>();
    constexpr auto Expected = meta::IntSeq<-2, -1, 0, 1, 2, 3>();
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
  meta::ForLoop<L, R>(func);
  ASSERT_EQ(s, S);
}

TEST(ForLoop) {
  CalculateSum<1, 3>();
  CalculateSum<-15, 17>();
  CalculateSum<0, 0>();
  CalculateSum<1, 0>();
}

RUN_ALL_TESTS()
