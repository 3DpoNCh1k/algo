#pragma once

#include <sstream>
#include <string>
#include <vector>
#include <utility>

#include <algo/utils/to_string/to_string.hpp>

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

struct DirectedEdge {
  DirectedEdge(int from, int to)
      : from(from),
        to(to){};

  int from;
  int to;

  bool operator==(const DirectedEdge& that) {
    return from == that.from && to == that.to;
  }

  std::string ToString() const {
    std::stringstream ss;
    ss << "(" << from << " -> " << to << ")";
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

using DirectedEdges = std::vector<DirectedEdge>;

struct BipartiteGraph {
  BipartiteGraph()
      : n_left_side(0),
        n_right_side(0) {
  }

  BipartiteGraph(int n_left_side, int n_right_side)
      : n_left_side(n_left_side),
        n_right_side(n_right_side) {
    g.resize(n_left_side);
  }

  BipartiteGraph(int n_left_side, int n_right_side, AdjacencyList g)
      : n_left_side(n_left_side),
        n_right_side(n_right_side),
        g(std::move(g)) {
  }

  BipartiteGraph(const BipartiteGraph& g) = default;
  BipartiteGraph(BipartiteGraph&& g) = default;

  BipartiteGraph& operator=(const BipartiteGraph& g) = default;
  BipartiteGraph& operator=(BipartiteGraph&& g) = default;

  int n_left_side, n_right_side;
  AdjacencyList g;

  auto& operator[](int i) {
    return g[i];
  }

  auto& operator[](int i) const {
    return g[i];
  }

  DirectedEdges Edges() const {
    DirectedEdges edges;
    for (int v = 0; v < n_left_side; ++v) {
      for (int u : g[v]) {
        edges.emplace_back(v, u);
      }
    }
    return edges;
  }

  std::string ToString() const {
    std::stringstream ss;
    ss << "Bipartite graph" << " "
       << utils::ToString(std::make_pair(n_left_side, n_right_side)) << "\n";
    ss << utils::ToString(g);
    return ss.str();
  };
};

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
