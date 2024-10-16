#include "algo/data_structures/convex_hull_trick.hpp"
#include "tests/framework/asserts.hpp"
#include "tests/framework/test.hpp"

using namespace algo::data_structures::cht;

template <typename CHT>
void Test() {
  auto sign = CHT::IsMinimum ? 1 : -1;

  using Line = typename CHT::Line;

  auto line0 = Line(2, 3);
  auto line1 = Line(1, 4);
  auto line2 = Line(-3, 10);
  auto line3 = Line(2, 2);
  auto line4 = Line(0, 3);

  std::vector<Line> lines = {line0, line1, line2, line3, line4};

  if (sign == -1) {
    for (auto& line : lines) {
      line.k = -line.k;
      line.b = -line.b;
    }
  }

  auto cht = CHT(lines);

  ASSERT_EQ(cht.hull.size(), 3);

  ASSERT_EQ(cht.hull[0], lines[3]);
  ASSERT_EQ(cht.hull[1], lines[4]);
  ASSERT_EQ(cht.hull[2], lines[2]);

  ASSERT_EQ(cht.GetValue(-2), -2 * sign);
  ASSERT_EQ(cht.GetValue(-1), 0 * sign);
  ASSERT_EQ(cht.GetValue(0), 2 * sign);
  ASSERT_EQ(cht.GetValue(1), 3 * sign);
  ASSERT_EQ(cht.GetValue(2), 3 * sign);
  ASSERT_EQ(cht.GetValue(3), 1 * sign);
  ASSERT_EQ(cht.GetValue(4), -2 * sign);
}

TEST(Minimum) {
  STATIC_ASSERT_EQ(MinimumCHT<>::IsMinimum, true);
  Test<MinimumCHT<>>();
}

TEST(Maximum) {
  STATIC_ASSERT_EQ(MaximumCHT<>::IsMinimum, false);
  Test<MaximumCHT<>>();
}

RUN_ALL_TESTS()
