#pragma once

#include <set>
#include <utility>
#include <vector>

#include <algo/graphs/entity/graph.hpp>
#include <algo/graphs/entity/condensation.hpp>

namespace algo::graphs {

namespace scc::details {
template <typename... EdgeProperties>
struct SCCImpl {
  using Graph = DirectedGraphWith<EdgeProperties...>;
  using CondensationType = Condensation<EdgeProperties...>;
  explicit SCCImpl(const Graph& g0)
      : g_(g0),
        g_inversed_(g0.n) {
  }

  // Kosaraju's algorithm
  CondensationType Condense() {
    CreateInversedGraph();
    OrderVertices();
    ExtractComponents();
    return Harvest();
  }

 private:
  void CreateInversedGraph() {
    for (int v = 0; v < g_.n; ++v) {
      for (int e : g_.edge_list[v]) {
        auto edge = g_.edges[e];
        std::swap(edge.to, edge.from);
        g_inversed_.AddEdge(edge);
      }
    }
  }

  void OrderVertices() {
    order_.clear();
    visited_.assign(g_.n, false);
    for (int v = 0; v < g_.n; ++v) {
      if (!visited_[v]) {
        OrderDfs(v);
      }
    }
  }

  void ExtractComponents() {
    visited_.assign(g_.n, false);
    component_.assign(g_.n, -1);
    k_component_ = 0;
    for (int i = g_.n - 1; i >= 0; --i) {
      int v = order_[i];
      if (!visited_[v]) {
        ComponentDfs(v, k_component_);
        k_component_++;
      }
    }
  }

  auto Harvest() {
    std::vector<typename CondensationType::Component> components(k_component_);
    Graph graph(k_component_);

    std::set<std::pair<int, int>> added_edges;
    for (int v = 0; v < g_.n; ++v) {
      components[component_[v]].push_back(v);
      for (int e : g_.edge_list[v]) {
        auto edge = g_.edges[e];
        int u = edge.to;
        if (component_[v] != component_[u] &&
            added_edges.find({component_[v], component_[u]}) ==
                added_edges.end()) {
          added_edges.emplace(component_[v], component_[u]);

          auto new_edge = edge;
          new_edge.from = component_[v];
          new_edge.to = component_[u];

          graph.AddEdge(new_edge);
        }
      }
    }

    return CondensationType{std::move(graph), std::move(components)};
  };

  void OrderDfs(int v) {
    visited_[v] = true;
    for (int e : g_.edge_list[v]) {
      int u = g_.edges[e].to;
      if (!visited_[u]) {
        OrderDfs(u);
      }
    }
    order_.push_back(v);
  }

  void ComponentDfs(int v, int component_number) {
    component_[v] = component_number;
    visited_[v] = true;
    for (int e : g_inversed_.edge_list[v]) {
      int u = g_inversed_.edges[e].to;
      if (!visited_[u]) {
        ComponentDfs(u, component_number);
      }
    }
  }

  const Graph& g_;
  Graph g_inversed_;

  std::vector<int> order_;
  std::vector<bool> visited_;

  std::vector<int> component_;
  int k_component_;
};
}  // namespace scc::details

template <typename... EdgeProperties>
auto StronglyConnectedComponents(
    const DirectedGraphWith<EdgeProperties...>& g) {
  return scc::details::SCCImpl(g).Condense();
}

}  // namespace algo::graphs
