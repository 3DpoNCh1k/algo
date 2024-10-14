#pragma once

#include <algo/utils/types/fundamentals.hpp>
#include <deque>
#include "algo/flows/entity/residual_network.hpp"
#include "algo/debug/debug.hpp"

namespace algo::flows::details {
template <typename Capacity>
struct Dinitz {
  using ResidualNetwork = ResidualNetworkWith<Capacity>;

  const ResidualNetwork& network;
  std::vector<int> flows;
  std::vector<int> next;
  std::vector<int> distance;
  i64 flow;
  static constexpr int Infinity = 1e9;

  explicit Dinitz(ResidualNetwork& network)
      : network(network) {
  }

  std::pair<Flow, Cut> MaxFlow() {
    flows.resize(network.edges.size());
    flow = 0;
    for (int i = 30; i >= 0; --i) {
      int limit = 1 << i;
      FindAugmentingPaths(limit);
    }

    return {GetFlow(), GetCut()};
  }

  Cut GetCut() {
    Cut cut;
    // iterate over existing (not residual) edges
    for (int e = 0; e < network.edges.size(); e += 2) {
      auto edge = network.edges[e];
      if (distance[edge.from] != Infinity && distance[edge.to] == Infinity) {
        cut.edges.push_back(e / 2);
      }
    }

    return cut;
  }

  Flow GetFlow() {
    Flow flow;

    flow.flow = this->flow;
    // iterate over existing (not residual) edges
    for (int e = 0; e < network.edges.size(); e += 2) {
      flow.edge_flow.push_back(flows[e]);
    }

    return flow;
  }

  void FindAugmentingPaths(int limit) {
    // debug("FindAugmentingPaths", limit);
    while (true) {
      bool found = BuildLayers(limit);
      // debug(found);
      // debug(distance);
      if (!found) {
        break;
      }
      next.assign(network.n, 0);
      while (FindAugmentingPath(network.source, limit)) {
        flow += limit;
      }
    }
  }

  bool FindAugmentingPath(int v, int limit) {
    // debug("FindAugmentingPath", v, limit);
    while (next[v] < network.edge_list[v].size()) {
      int e = network.edge_list[v][next[v]];
      // debug(next[v], e);
      // debug(network.edges[e].from, network.edges[e].to);
      assert(network.edges[e].from == v);
      if (network.edges[e].capacity - flows[e] < limit) {
        // debug("less than limit");
        next[v]++;
        continue;
      }
      int u = network.edges[e].to;
      // debug(v, u, e);
      if (distance[u] != distance[v] + 1) {
        // debug("not bfs");
        next[v]++;
        continue;
      }
      if (u == network.sink) {
        // debug("found sink");
        flows[e] += limit;
        flows[network.PairedEdgeIndex(e)] -= limit;
        return true;
      }
      if (FindAugmentingPath(u, limit)) {
        // debug("found path");
        flows[e] += limit;
        flows[network.PairedEdgeIndex(e)] -= limit;
        return true;
      }
      next[v]++;
    }
    return false;
  }

  bool BuildLayers(int limit) {
    distance.assign(network.n, Infinity);
    distance[network.source] = 0;
    std::deque<int> q{network.source};
    bool found = false;
    while (!q.empty()) {
      int v = q.front();
      q.pop_front();
      if (v == network.sink) {
        found = true;
      }
      for (int e : network.edge_list[v]) {
        if (network.edges[e].capacity - flows[e] < limit) {
          continue;
        }
        int u = network.edges[e].to;
        if (distance[u] == Infinity) {
          distance[u] = distance[v] + 1;
          q.push_back(u);
        }
      }
    }
    return found;
  }
};
}  // namespace algo::flows::details
