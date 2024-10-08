#include <set>

#include <algo/utils/generators/random.hpp>
#include <algo/utils/generators/subset.hpp>

#include <tests/framework/asserts.hpp>
#include "tests/framework/test.hpp"

using namespace algo::utils::generators;

TEST(StressGetFromRange) {
  auto random_generator = RandomGenerator(0);
  auto subset_generator = SubsetGenerator(random_generator);
  {
    const int from = -10;
    const int to = 10;
    const int rep_count = 50;
    for (int rep = 0; rep < rep_count; ++rep) {
      int l = random_generator.GetInt(from, to);
      int r = random_generator.GetInt(l, to);
      int k = random_generator.GetInt(1, r - l + 1);
      auto subset = subset_generator.GetFromRange(l, r, k);
      ASSERT_EQ(subset.size(), k);
      for (auto e : subset) {
        ASSERT_TRUE(e >= l);
        ASSERT_TRUE(e <= r);
      }
    }
  }
}

RUN_ALL_TESTS()
