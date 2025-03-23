#include <algo/ranges/dst.hpp>
#include <algo/ranges/statistics/minimum.hpp>
#include <algo/ranges/statistics/sum.hpp>
#include <tests/framework/asserts.hpp>
#include <tests/framework/test.hpp>

TEST(Minimum) {
  std::vector<i64> a = {1, 0, 3, 2, 1};
  auto dst = algo::ranges::DST<algo::ranges::statistics::IntMinimum>(a);

  ASSERT_EQ(dst.Get(0, 0), 1);
  ASSERT_EQ(dst.Get(1, 1), 0);
  ASSERT_EQ(dst.Get(0, 1), 0);
  ASSERT_EQ(dst.Get(0, 2), 0);
  ASSERT_EQ(dst.Get(2, 3), 2);
  ASSERT_EQ(dst.Get(3, 4), 1);
  ASSERT_EQ(dst.Get(2, 4), 1);
  ASSERT_EQ(dst.Get(1, 4), 0);
  ASSERT_EQ(dst.Get(0, 4), 0);
}

TEST(Sum) {
  std::vector<i64> a = {1, 0, 3, 2, 1};
  auto dst = algo::ranges::DST<algo::ranges::statistics::IntSum>(a);

  ASSERT_EQ(dst.Get(0, 0), 1);
  ASSERT_EQ(dst.Get(1, 1), 0);
  ASSERT_EQ(dst.Get(0, 1), 1);
  ASSERT_EQ(dst.Get(0, 2), 4);
  ASSERT_EQ(dst.Get(2, 3), 5);
  ASSERT_EQ(dst.Get(3, 4), 3);
  ASSERT_EQ(dst.Get(2, 4), 6);
  ASSERT_EQ(dst.Get(1, 4), 6);
  ASSERT_EQ(dst.Get(0, 4), 7);
}

RUN_ALL_TESTS()
