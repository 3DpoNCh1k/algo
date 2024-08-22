#include <iostream>

#include <algo/flows/entities.hpp>
#include <algo/flows/max_flow.hpp>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  algo::flows::ResidualNetwork network(n + 1, 1, n);
  for (int i = 0; i < m; ++i) {
    int v, u, c;
    cin >> v >> u >> c;
    network.AddBidirectional(v, u, c);
  }

  auto [F, flow_cut] = algo::flows::MaxFlow(network);
  auto [flow, _] = std::move(flow_cut);
  cout << F << "\n";
  for (int i = 0; i < m; ++i) {
    cout << flow.flows[network.GetInternalEdgeIndex(i)] << "\n";
  }
}
