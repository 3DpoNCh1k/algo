#include "algo/flows/entities.hpp"
#include "algo/flows/max_flow.hpp"
#include "tests/framework/test.hpp"
#include <algo/utils/random/random.hpp>

#include "validate.hpp"

using namespace algo::flows;
using namespace algo::utils::random;

ResidualNetwork GenerateNetwork(int n, int e, int c) {
  int source = RandomInt(0, n - 1);
  int sink;
  do {
    sink = RandomInt(0, n - 1);
  } while (sink == source);
  ResidualNetwork network(n, source, sink);
  for (int i = 0; i < e; ++i) {
    int from;
    do {
      from = RandomInt(0, n - 1);
    } while (from == sink);
    int to;
    do {
      to = RandomInt(0, n - 1);
    } while (to == source);
    int capacity = RandomInt(0, c);
    network.Add(from, to, capacity);
  }
  return network;
};

void Stress(int k_rep, int max_n, int max_e, int max_c) {
  for (int rep = 0; rep < k_rep; ++rep) {
    int n = RandomInt(2, max_n);
    int e = RandomInt(0, max_e);
    int c = RandomInt(0, max_c);
    auto network = GenerateNetwork(n, e, c);
    dbg(network.n, network.edges.size(), network.source, network.sink);
    auto [F, flow_cut] = MaxFlow(network);
    auto [flow, cut] = flow_cut;
    Validate(network, F, flow, cut);
  }
}

TEST(StressSmall) {
  Stress(50, 5, 10, 10);
}

TEST(StressMedium) {
  Stress(1000, 20, 100, 10);
}

TEST(StressBig) {
  Stress(100, 100, 1000, 1e9);
}

RUN_ALL_TESTS()
