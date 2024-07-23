#pragma once

#include <set>
#include <utility>
#include <vector>

namespace algo::graphs {

using Graph = std::vector<std::vector<int>>;
using Components = std::vector<std::vector<int>>;
using Condensation = std::pair<Graph, Components>;

namespace scc::details {
struct SCCImpl {
  explicit SCCImpl(const Graph& g0)
      : g_(g0),
        n_(g_.size()) {
  }

  // Kosaraju's algorithm
  Condensation Condense() {
    CreateInversedGraph();
    OrderVertices();
    ExtractComponents();
    return Harvest();
  }

 private:
  void CreateInversedGraph() {
    g_inversed_.resize(n_);
    for (int v = 0; v < n_; ++v) {
      for (int u : g_[v]) {
        g_inversed_[u].push_back(v);
      }
    }
  }

  void OrderVertices() {
    order_.clear();
    visited_.assign(n_, false);
    for (int v = 0; v < n_; ++v) {
      if (!visited_[v]) {
        OrderDfs(v);
      }
    }
  }

  void ExtractComponents() {
    visited_.assign(n_, false);
    component_.assign(n_, -1);
    k_component_ = 0;
    for (int i = n_ - 1; i >= 0; --i) {
      int v = order_[i];
      if (!visited_[v]) {
        ComponentDfs(v, k_component_);
        k_component_++;
      }
    }
  }

  Condensation Harvest() {
    Components components;
    components.resize(k_component_);
    std::set<std::pair<int, int>> edges;
    for (int v = 0; v < n_; ++v) {
      components[component_[v]].push_back(v);
      for (int u : g_[v]) {
        if (component_[v] != component_[u]) {
          edges.emplace(component_[v], component_[u]);
        }
      }
    }

    Graph graph;
    graph.resize(k_component_);
    for (auto [v, u] : edges) {
      graph[v].push_back(u);
    }
    return Condensation(std::move(graph), std::move(components));
  };

  void OrderDfs(int v) {
    visited_[v] = true;
    for (int u : g_[v]) {
      if (!visited_[u]) {
        OrderDfs(u);
      }
    }
    order_.push_back(v);
  }

  void ComponentDfs(int v, int component_number) {
    component_[v] = component_number;
    visited_[v] = true;
    for (int u : g_inversed_[v]) {
      if (!visited_[u]) {
        ComponentDfs(u, component_number);
      }
    }
  }

  const Graph& g_;
  const int n_;
  Graph g_inversed_;

  std::vector<int> order_;
  std::vector<bool> visited_;

  std::vector<int> component_;
  int k_component_;
};
}  // namespace scc::details

Condensation StronglyConnectedComponents(const Graph& g) {
  return scc::details::SCCImpl(g).Condense();
}

}  // namespace algo::graphs
