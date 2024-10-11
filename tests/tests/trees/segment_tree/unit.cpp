
#include <algo/trees/segment_tree/updates/range_update.hpp>
#include <algo/trees/segment_tree/updates/add.hpp>
#include <algo/trees/segment_tree/updates/set.hpp>

#include <algo/trees/segment_tree/new_statistics/sum.hpp>

#include "algo/utils/debug.hpp"
#include "tests/framework/asserts.hpp"
#include "tests/framework/test.hpp"

using namespace algo::trees::segment_tree::range_updates;
using namespace algo::trees::segment_tree::new_statistics;

TEST(Simple) {
  // auto range_update = RangeUpdate(0, 1);
  // auto update = Update(i64(1), 0, 1);
  auto range = Range(0, 1);
  auto update = Update(range, 1);
}

RUN_ALL_TESTS()
