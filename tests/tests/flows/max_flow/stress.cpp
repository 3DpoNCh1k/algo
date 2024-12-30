#include <algo/flows/entity/residual_network.hpp>
#include <algo/flows/max_flow.hpp>
#include <algo/utils/generators/graph.hpp>
#include <tests/framework/test.hpp>
#include <algo/utils/random/random.hpp>

#include "validate.hpp"

using algo::utils::random::RandomInt;

void Stress(int k_rep, int max_n, int max_e, int max_c) {
  auto graph_generator = algo::utils::generators::GraphGenerator();
  for (int rep = 0; rep < k_rep; ++rep) {
    int n = RandomInt(2, max_n);
    int source = RandomInt(0, n - 1);
    int sink;
    do {
      sink = RandomInt(0, n - 1);
    } while (sink == source);
    int e = RandomInt(0, max_e);
    int c = RandomInt(0, max_c);
    auto network = graph_generator.ResidualNetwork(n, source, sink, e, c);
    auto [flow, cut] = algo::flows::MaxFlow(network);
    Validate(network, flow, cut);
  }
}

TEST(StressSmall) {
  Stress(1000, 5, 10, 10);
}

TEST(StressMedium) {
  Stress(5000, 20, 100, 10);
}

TEST(StressBig) {
  Stress(100, 100, 1000, 1e9);
}

RUN_ALL_TESTS()
