#include <set>

#include <algo/utils/generators/random_generator.hpp>
#include "algo/utils/generators/subset_generator.hpp"

#include "tests/testing/asserts.hpp"

using namespace algo::utils::generators;

void TestGetFromRange() {
  auto subset_generator = SubsetGenerator();
  auto random_generator = RandomGenerator();
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

int main() {
  TestGetFromRange();
}
