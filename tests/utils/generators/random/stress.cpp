#include <set>

#include <algo/utils/generators/random.hpp>
#include "tests/testing/asserts.hpp"

using namespace algo::utils::generators;

void TestInt() {
  auto g = RandomGenerator();
  {
    const int from = -5;
    const int to = 5;
    const int rep_count = 1000;
    std::set<int> s;
    for (int rep = 0; rep < rep_count; ++rep) {
      auto value = g.GetInt(from, to);
      ASSERT_TRUE(value >= from);
      ASSERT_TRUE(value <= to);
      s.insert(value);
    }
    ASSERT_TRUE(s.size() == (to - from + 1));
  }
}

int main() {
  TestInt();
}
