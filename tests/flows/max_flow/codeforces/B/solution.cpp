#include <iostream>

#include <algo/utils/types/fundamentals.hpp>
#include "algo/flows/entities.hpp"
#include "algo/flows/max_flow.hpp"
#include "algo/utils/join.hpp"

using namespace std;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  algo::flows::ResidualNetwork network(n + 1, 1, n);
  for (int i = 0; i < m; ++i) {
    int v, u, c;
    cin >> v >> u >> c;
    // network.AddBidirectional(v, u, c);
    network.Add(v, u, c);
    network.Add(u, v, c);
  }

  auto [F, flow_cut] = algo::flows::MaxFlow(network);
  auto [_, cut] = std::move(flow_cut);

  cout << cut.edges.size() << " " << F << "\n";
  cout << algo::utils::JoinToString(
              cut.edges,
              [&](int e) {
                return network.GetExternalEdgeIndex(e) / 2 + 1;
              },
              algo::utils::Parameters{"", "", " "})
       << "\n";
}
