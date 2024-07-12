#include <cassert>
#include <iostream>

#include <algo/trees/fenwick/operations/add.hpp>
#include <algo/trees/fenwick/operations/operation.hpp>
#include <algo/trees/fenwick/statistics/sum.hpp>
#include <algo/trees/fenwick/statistics/statistics.hpp>
#include "algo/trees/fenwick/trees.hpp"

using namespace algo::trees::fenwick;
using namespace operations;
using namespace statistics;

int main() {
  int n, q;
  std::cin >> n >> q;
  std::string t;
  std::cin >> t;
  auto fenwick = FenwickTree<Operation<AddOp>, Statistics<Sum>>(n);

  auto set_at_index = [&fenwick](int index, auto value) {
    auto res = fenwick.GetAtIndex<Sum>(index);
    auto add = AddOp{value - res.result};
    fenwick.ApplyAtIndex(add, index);
  };

  for (int k = 0; k < n; ++k) {
    auto value = t[k] == '1' ? 1 : 0;
    set_at_index(k, value);
  }

  for (int query = 0; query < q; ++query) {
    int c, k;
    std::cin >> c >> k;
    switch (c) {
      case 0:
        set_at_index(k, 1);
        break;
      case 1:
        set_at_index(k, 0);
        break;
      case 2: {
        auto res = fenwick.GetAtIndex<Sum>(k);
        std::cout << res.result << std::endl;
      } break;
      case 3: {
        int smallest = -1;
        int l = k, r = n - 1;
        int count = fenwick.GetFromRange<Sum>(k, n - 1).result;
        while (l < r) {
          int m = (l + r + 1) / 2;
          if (fenwick.GetFromRange<Sum>(m, n - 1).result < count) {
            r = m - 1;
            smallest = r;
          } else {
            l = m;
          }
        }
        if (smallest == -1 && fenwick.GetAtIndex<Sum>(n - 1).result == 1) {
          smallest = n - 1;
        }
        std::cout << smallest << std::endl;
        break;
      }
      case 4: {
        int largest = -1;
        int l = 0, r = k;
        int count = fenwick.GetFromRange<Sum>(0, k).result;
        while (l < r) {
          int m = (l + r) / 2;
          if (fenwick.GetFromRange<Sum>(0, m).result < count) {
            l = m + 1;
            largest = l;
          } else {
            r = m;
          }
        }
        if (largest == -1 && fenwick.GetAtIndex<Sum>(0).result == 1) {
          largest = 0;
        }
        std::cout << largest << std::endl;
        break;
      }
    }
  }
}
