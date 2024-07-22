#pragma once

#include <cassert>
#include <set>

#include <algo/utils/generators/random.hpp>

namespace algo::utils::generators {
struct SubsetGenerator {
  RandomGenerator& random;
  explicit SubsetGenerator(RandomGenerator& random)
      : random(random) {
  }
  static constexpr int REP = 100;

  std::set<i64> GetFromRange(i64 from, i64 to, int count) {
    assert(count <= (to - from + 1));
    std::set<i64> taken;
    for (int i = 0; i < count; ++i) {
      bool found = false;
      for (int rep = 0; rep < REP; ++rep) {
        auto value = random.GetInt(from, to);
        if (taken.find(value) == taken.end()) {
          taken.insert(value);
          found = true;
          break;
        }
      }
      if (!found) {
        for (auto value = from; taken.size() != count && value <= to; ++value) {
          taken.insert(value);
        }
        break;
      }
    }
    assert(taken.size() == count);
    return taken;
  }
};

}  // namespace algo::utils::generators
