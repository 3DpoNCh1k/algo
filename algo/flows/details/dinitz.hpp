#pragma once

#include <algo/flows/entities.hpp>
#include <algo/utils/types/fundamentals.hpp>
#include <deque>
#include "algo/utils/debug.hpp"

namespace algo::flows::details {
struct Dinitz {
  const ResidualNetwork& network;
  std::vector<int> flows;
  std::vector<int> next;
  std::vector<int> distance;
  i64 flow;
  static constexpr int Infinity = 1e9;

  explicit Dinitz(ResidualNetwork& network)
      : network(network) {
  }

  std::pair<i64, std::pair<Flow, Cut>> MaxFlow() {
    flows.resize(network.edges.size());
    flow = 0;
    for (int i = 30; i >= 0; --i) {
      int limit = 1 << i;
      FindAugmentingPaths(limit);
    }

    return {flow, {Flow{flows}, FindCut()}};
  }

  Cut FindCut() {
    Cut cut;
    for (int v = 0; v < network.n; ++v) {
      if (distance[v] == Infinity) {
        continue;
      }
      for (int e : network[v]) {
        int u = network.edges[e].to;
        if (distance[u] == Infinity && !network.IsResidualEdge(e)) {
          cut.edges.push_back(e);
        }
      }
    }
    return cut;
  }

  void FindAugmentingPaths(int limit) {
    // dbg("FindAugmentingPaths", limit);
    while (true) {
      bool found = BuildLayers(limit);
      // dbg(found);
      // dbg(distance);
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
    // dbg("FindAugmentingPath", v, limit);
    while (next[v] < network[v].size()) {
      int e = network[v][next[v]];
      // dbg(next[v], e);
      // dbg(network.edges[e].from, network.edges[e].to);
      assert(network.edges[e].from == v);
      if (network.edges[e].capacity - flows[e] < limit) {
        // dbg("less than limit");
        next[v]++;
        continue;
      }
      int u = network.edges[e].to;
      // dbg(v, u, e);
      if (distance[u] != distance[v] + 1) {
        // dbg("not bfs");
        next[v]++;
        continue;
      }
      if (u == network.sink) {
        // dbg("found sink");
        flows[e] += limit;
        flows[network.PairedEdgeIndex(e)] -= limit;
        return true;
      }
      if (FindAugmentingPath(u, limit)) {
        // dbg("found path");
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
      for (int e : network[v]) {
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
