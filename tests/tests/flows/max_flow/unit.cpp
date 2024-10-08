#include <algo/flows/max_flow.hpp>
#include "algo/utils/debug.hpp"
#include "tests/framework/asserts.hpp"
#include "tests/framework/test.hpp"

using namespace algo::flows;

TEST(Simple) {
  auto network = ResidualNetwork(4, 0, 3);
  network.Add(0, 1, 1);
  network.Add(0, 2, 1);
  network.Add(1, 3, 2);
  network.Add(2, 1, 1);
  auto [F, _] = MaxFlow(network);
  ASSERT_EQ(F, 2);
};

RUN_ALL_TESTS()
