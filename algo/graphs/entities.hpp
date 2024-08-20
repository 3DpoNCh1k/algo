#pragma once

#include <sstream>
#include <string>
#include <vector>
#include <utility>

namespace algo::graphs {

struct UndirectedEdge {
  UndirectedEdge(int u, int v)
      : u(u),
        v(v){};

  int u;
  int v;

  bool operator==(const UndirectedEdge& that) {
    return (u == that.u && v == that.v) || (v == that.u && u == that.v);
  }

  int Neighbor(int w) {
    return w == u ? v : (w == v ? u : -1);
  }

  std::string ToString() const {
    std::stringstream ss;
    ss << "(" << u << " <-> " << v << ")";
    return ss.str();
  };
};

using Graph = std::vector<std::vector<int>>;
using Components = std::vector<std::vector<int>>;
using Condensation = std::pair<Graph, Components>;

using VertexAdjacencyList = Graph;
using EdgeAdjacencyList = Graph;
using AdjacencyList = VertexAdjacencyList;

using Edge = UndirectedEdge;
using Edges = std::vector<Edge>;

std::pair<int, Edges> ToEdges(const AdjacencyList& g) {
  int n = g.size();
  Edges edges;
  for (int v = 0; v < n; ++v) {
    for (int u : g[v]) {
      if (v <= u) {
        edges.emplace_back(v, u);
      }
    }
  }
  return {n, edges};
};

std::pair<Edges, AdjacencyList> ToEdgeAdjacencyList(const AdjacencyList& g0) {
  auto [n, edges] = ToEdges(g0);
  EdgeAdjacencyList g(n);
  for (int e = 0; e < edges.size(); ++e) {
    g[edges[e].u].push_back(e);
    g[edges[e].v].push_back(e);
  }
  return {edges, g};
};

}  // namespace algo::graphs
