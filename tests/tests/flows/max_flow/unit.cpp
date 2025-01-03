#include <algo/flows/max_flow.hpp>
#include <algo/flows/entity/residual_network.hpp>
#include <algo/flows/entity/capacity.hpp>
#include <algo/graphs/entity/edge.hpp>
#include <algo/debug/debug.hpp>
#include <tests/framework/asserts.hpp>
#include <tests/framework/test.hpp>

TEST(Simple) {
  auto network = algo::flows::ResidualNetwork(4, 0, 3);
  network.AddEdge(0, 1, 1);
  network.AddEdge(0, 2, 1);
  network.AddEdge(1, 3, 2);
  network.AddEdge(2, 1, 1);
  auto [flow, cut] = algo::flows::MaxFlow(network);
  ASSERT_EQ(flow.flow, 2);
};

RUN_ALL_TESTS()
