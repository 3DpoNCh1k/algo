#include "algo/flows/entities.hpp"
#include "algo/flows/max_flow.hpp"
#include "algo/utils/generators/random.hpp"
#include "tests/framework/test.hpp"

#include "validate.hpp"

using namespace algo::flows;

ResidualNetwork GenerateNetwork(
    int n, int e, int c, algo::utils::generators::RandomGenerator& random) {
  int source = random.GetInt(0, n - 1);
  int sink;
  do {
    sink = random.GetInt(0, n - 1);
  } while (sink == source);
  ResidualNetwork network(n, source, sink);
  for (int i = 0; i < e; ++i) {
    int from;
    do {
      from = random.GetInt(0, n - 1);
    } while (from == sink);
    int to;
    do {
      to = random.GetInt(0, n - 1);
    } while (to == source);
    int capacity = random.GetInt(0, c);
    network.Add(from, to, capacity);
  }
  return network;
};

void Stress(int k_rep, int max_n, int max_e, int max_c) {
  auto random = algo::utils::generators::RandomGenerator(max_n ^ max_e ^ max_c);
  for (int rep = 0; rep < k_rep; ++rep) {
    int n = random.GetInt(2, max_n);
    int e = random.GetInt(0, max_e);
    int c = random.GetInt(0, max_c);
    auto network = GenerateNetwork(n, e, c, random);
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
