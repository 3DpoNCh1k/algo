#pragma once

#include <cassert>
#include <algo/flows/entity/flow.hpp>
#include <algo/flows/entity/cut.hpp>
#include <algo/flows/entity/capacity.hpp>

#include <algo/graphs/entity/graph.hpp>
#include "algo/utils/types/fundamentals.hpp"

namespace algo::flows {

template <typename Capacity>
struct ResidualNetworkWith : graphs::DirectedGraphWith<Capacity> {
  using GraphType = graphs::DirectedGraphWith<Capacity>;
  using EdgeType = typename GraphType::EdgeType;
  using C = typename Capacity::CapacityType;
  int source, sink;

  ResidualNetworkWith(int n, int source, int sink)
      : GraphType(n),
        source(source),
        sink(sink) {
    assert(sink != source);
  }

  void AddEdge(int from, int to, C capacity) {
    GraphType::AddEdge(EdgeType(from, to, Capacity(capacity)));
    GraphType::AddEdge(EdgeType(to, from, Capacity(0)));
  }

  int PairedEdgeIndex(int e) const {
    return e ^ 1;
  }

  bool IsResidualEdge(int e) const {
    return (e & 1) != 0;
  }

  std::string ToString() const {
    std::stringstream ss;
    ss << "Residual network: source = " << source << " sink = " << sink << "\n";
    ss << GraphType::ToString();
    return ss.str();
  };
};

using ResidualNetwork = ResidualNetworkWith<Capacity<i64>>;

}  // namespace algo::flows
