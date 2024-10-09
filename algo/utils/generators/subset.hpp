#pragma once

#include <cassert>
#include <set>

#include <algo/utils/random/random.hpp>

namespace algo::utils::generators {
struct SubsetGenerator {
  SubsetGenerator() {
  }

  std::set<i64> FromRange(i64 from, i64 to, int count) {
    assert(count <= (to - from + 1));
    std::set<i64> taken;
    for (int i = 0; i < count; ++i) {
      bool found = false;
      for (int rep = 0; rep < REP; ++rep) {
        auto value = random::RandomInt(from, to);
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

 private:
  static constexpr int REP = 100;
};

}  // namespace algo::utils::generators
