#pragma once

#include <cassert>
#include <vector>

namespace algo::flows {

struct Edge {
  int from;
  int to;
  int capacity;
  Edge(int from, int to, int capacity)
      : from(from),
        to(to),
        capacity(capacity) {
  }
};

struct Cut {
  std::vector<int> edges;
};

struct Flow {
  std::vector<int> flows;
};

struct ResidualNetwork {
  int n;
  int source, sink;
  std::vector<Edge> edges;
  std::vector<std::vector<int>> g;

  ResidualNetwork(int n, int source, int sink)
      : n(n),
        source(source),
        sink(sink) {
    assert(sink != source);
    g.resize(n);
  }

  void Add(int from, int to, int capacity) {
    g[from].push_back(edges.size());
    edges.emplace_back(from, to, capacity);
    g[to].push_back(edges.size());
    edges.emplace_back(to, from, 0);
  }

  void AddBidirectional(int v, int u, int capacity) {
    g[v].push_back(edges.size());
    edges.emplace_back(v, u, capacity);
    g[u].push_back(edges.size());
    edges.emplace_back(u, v, capacity);
  }

  int GetInternalEdgeIndex(int index) const {
    return 2 * index;
  }

  int GetExternalEdgeIndex(int index) const {
    assert(!IsResidualEdge(index));
    return index / 2;
  }

  auto& operator[](int i) {
    return g[i];
  }

  auto& operator[](int i) const {
    return g[i];
  }

  int PairedEdgeIndex(int e) const {
    return e ^ 1;
  }

  bool IsResidualEdge(int e) const {
    return (e & 1) != 0;
  }
};

}  // namespace algo::flows
