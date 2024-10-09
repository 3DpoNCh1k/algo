#include <set>

#include <algo/utils/random/random.hpp>
#include <algo/utils/generators/subset.hpp>

#include <tests/framework/asserts.hpp>
#include "tests/framework/test.hpp"

using namespace algo::utils::random;
using namespace algo::utils::generators;

TEST(StressGetFromRange) {
  auto subset_generator = SubsetGenerator();
  {
    const int from = -10;
    const int to = 10;
    const int rep_count = 50;
    for (int rep = 0; rep < rep_count; ++rep) {
      int l = RandomInt(from, to);
      int r = RandomInt(l, to);
      int k = RandomInt(1, r - l + 1);
      auto subset = subset_generator.FromRange(l, r, k);
      ASSERT_EQ(subset.size(), k);
      for (auto e : subset) {
        ASSERT_TRUE(e >= l);
        ASSERT_TRUE(e <= r);
      }
    }
  }
}

RUN_ALL_TESTS()
