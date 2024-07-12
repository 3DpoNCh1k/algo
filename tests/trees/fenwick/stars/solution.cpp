#include <iostream>
#include <sstream>
#include <string>

#include <algo/trees/fenwick/trees.hpp>
#include "algo/trees/fenwick/operations/add.hpp"
#include "algo/trees/fenwick/statistics/sum.hpp"

using namespace std;
using namespace algo::trees::fenwick;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;

  auto fenwick =
      Fenwick3D<Operation<operations::AddOp>, Statistics<statistics::Sum>>(n, n,
                                                                           n);

  string line;
  while (getline(cin, line)) {
    if (line.empty()) {
      continue;
    }
    auto ss = istringstream(line);
    int command;
    ss >> command;
    if (command == 1) {
      int x, y, z, k;
      ss >> x >> y >> z >> k;
      fenwick.ApplyAtIndex(operations::AddOp{k}, x, y, z);
    } else if (command == 2) {
      int x0, x1, y0, y1, z0, z1;
      ss >> x0 >> y0 >> z0;
      ss >> x1 >> y1 >> z1;
      auto result =
          fenwick.GetFromRange<statistics::Sum>(x0, x1, y0, y1, z0, z1);
      cout << result.result << "\n";
    } else if (command == 3) {
      break;
    } else {
      abort();
    }
  }
}
