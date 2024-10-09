#include <set>

#include <algo/utils/random/random.hpp>
#include <tests/framework/asserts.hpp>
#include "tests/framework/test.hpp"

using namespace algo::utils::random;

TEST(StressInt) {
  const int from = -5;
  const int to = 5;
  const int rep_count = 1000;
  std::set<int> s;
  for (int rep = 0; rep < rep_count; ++rep) {
    auto value = RandomInt(from, to);
    ASSERT_TRUE(value >= from);
    ASSERT_TRUE(value <= to);
    s.insert(value);
  }
  ASSERT_TRUE(s.size() == (to - from + 1));
}

RUN_ALL_TESTS()
