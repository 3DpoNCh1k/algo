#pragma once

#include <deque>

#include "algo/flows/entity/residual_network.hpp"
#include "algo/utils/types/fundamentals.hpp"
#include "tests/framework/asserts.hpp"

using namespace algo::flows;

void Validate(const ResidualNetwork& network, const Flow& flow,
              const Cut& cut) {
  ASSERT_EQ(2 * flow.edge_flow.size(), network.edges.size());

  for (int index = 0; index < flow.edge_flow.size(); ++index) {
    int e = 2 * index;
    ASSERT_FALSE(network.IsResidualEdge(e));
    ASSERT_TRUE(network.IsResidualEdge(e + 1));
    auto edge_flow = flow.edge_flow[index];
    auto edge = network.edges[e];
    ASSERT_TRUE(edge_flow >= 0);
    ASSERT_TRUE(edge_flow <= edge.capacity);
  }

  std::vector<i64> flow_in(network.n);
  std::vector<i64> flow_out(network.n);

  for (int index = 0; index < flow.edge_flow.size(); ++index) {
    int e = 2 * index;
    auto edge_flow = flow.edge_flow[index];
    auto edge = network.edges[e];
    flow_in[edge.to] += edge_flow;
    flow_out[edge.from] += edge_flow;
  }

  ASSERT_EQ(flow_in[network.sink], flow.flow);
  ASSERT_EQ(flow_out[network.sink], 0);

  ASSERT_EQ(flow_in[network.source], 0);
  ASSERT_EQ(flow_out[network.source], flow.flow);

  for (int v = 0; v < network.n; ++v) {
    if (v != network.source && v != network.sink) {
      ASSERT_EQ(flow_in[v], flow_out[v]);
    }
  }

  std::vector<bool> forbidden(network.edges.size());
  for (int index : cut.edges) {
    int e = 2 * index;
    forbidden[e] = true;
  }

  std::vector<bool> visited(network.n);
  visited[network.source] = true;
  std::deque<int> q{network.source};
  while (!q.empty()) {
    int v = q.front();
    q.pop_front();
    for (int e : network.edge_list[v]) {
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
  for (int index : cut.edges) {
    int e = 2 * index;
    ASSERT_FALSE(network.IsResidualEdge(e));
    auto edge_flow = flow.edge_flow[index];
    auto edge = network.edges[e];
    ASSERT_TRUE(visited[edge.from]);
    ASSERT_FALSE(visited[edge.to]);
    ASSERT_EQ(edge_flow, edge.capacity);
    cut_flow += edge_flow;
  }

  ASSERT_EQ(cut_flow, flow.flow);
};
