#include <deque>

#include "algo/flows/entities.hpp"
#include "algo/flows/max_flow.hpp"
#include "algo/utils/generators/random.hpp"
#include "tests/framework/asserts.hpp"

using namespace algo::flows;

struct Tester {
  int max_n, max_e, max_c;
  algo::utils::generators::RandomGenerator random;
  Tester(int n, int e, int c)
      : max_n(n),
        max_e(e),
        max_c(c),
        random(n ^ e) {
    assert(max_n >= 2);
  };

  void Test(int k_rep) {
    for (int rep = 0; rep < k_rep; ++rep) {
      auto network = GenerateNetwork();
      dbg(network.n, network.edges.size(), network.source, network.sink);
      auto [F, flow_cut] = MaxFlow(network);
      auto [flow, cut] = flow_cut;
      Validate(network, F, flow, cut);
    }
  }

  ResidualNetwork GenerateNetwork() {
    int n = random.GetInt(2, max_n);
    int e = random.GetInt(0, max_e);
    int c = random.GetInt(0, max_c);
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

  void Validate(const ResidualNetwork& network, i64 f, const Flow& flow,
                const Cut& cut) {
    ASSERT_EQ(flow.flows.size(), network.edges.size());
    for (int e = 0; e < network.edges.size(); ++e) {
      if (!network.IsResidualEdge(e)) {
        auto edge = network.edges[e];
        auto edge_flow = flow.flows[e];
        ASSERT_TRUE(edge_flow >= 0);
        ASSERT_TRUE(edge_flow <= edge.capacity);
      }
    }
    std::vector<i64> flow_in(network.n);
    std::vector<i64> flow_out(network.n);
    for (int e = 0; e < network.edges.size(); ++e) {
      if (!network.IsResidualEdge(e)) {
        auto edge = network.edges[e];
        auto edge_flow = flow.flows[e];
        flow_in[edge.to] += edge_flow;
        flow_out[edge.from] += edge_flow;
      }
    }
    ASSERT_EQ(flow_in[network.sink], f);
    ASSERT_EQ(flow_out[network.sink], 0);

    ASSERT_EQ(flow_in[network.source], 0);
    ASSERT_EQ(flow_out[network.source], f);
    for (int v = 0; v < network.n; ++v) {
      if (v != network.source && v != network.sink) {
        ASSERT_EQ(flow_in[v], flow_out[v]);
      }
    }

    std::vector<bool> forbidden(network.edges.size());
    for (int e : cut.edges) {
      forbidden[e] = true;
    }
    std::vector<bool> visited(network.n);
    visited[network.source] = true;
    std::deque<int> q{network.source};
    while (!q.empty()) {
      int v = q.front();
      q.pop_front();
      for (int e : network[v]) {
        if (!network.IsResidualEdge(e) && !forbidden[e]) {
          auto edge = network.edges[e];
          int u = edge.to;
          if (!visited[u]) {
            visited[u] = true;
            q.push_back(u);
          }
        }
      }
    }
    ASSERT_FALSE(visited[network.sink]);
    i64 cut_flow = 0;
    for (int e : cut.edges) {
      ASSERT_FALSE(network.IsResidualEdge(e));
      auto edge = network.edges[e];
      auto edge_flow = flow.flows[e];
      ASSERT_TRUE(visited[edge.from]);
      ASSERT_FALSE(visited[edge.to]);
      ASSERT_EQ(edge_flow, edge.capacity);
      cut_flow += edge_flow;
    }
    ASSERT_EQ(cut_flow, f);
  };
};

void Test() {
  Tester(5, 10, 10).Test(50);
  Tester(20, 100, 10).Test(1000);
  Tester(100, 1000, 1e9).Test(100);
}

int main() {
  Test();
}
