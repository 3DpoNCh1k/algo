#include <iostream>
#include <vector>
#include "algo/utils/types/types.hpp"
#include "algo/trees/segment_tree/trees.hpp"
#include "algo/trees/segment_tree/operations/add.hpp"
#include "algo/trees/segment_tree/statistics/sum.hpp"


using namespace algo::trees::segment_tree;

int main() {
    int n, q;
    std::cin >> n >> q;
    std::vector<algo::utils::i64> a(n);
    for(int i = 0; i < n; ++i) {
      std::cin >> a[i];
    }

    auto lazy = LazyPropagationDynamicSegmentTree<Operation<operations::AddOp>, Statistics<statistics::Sum>>(0, n-1);

    for(int i = 0; i < n; ++i) {
      lazy.ApplyAtIndex(i, operations::AddOp{a[i]});
    }

    for(int i = 0; i < q; ++i) {
        int command;
        std::cin >> command;
        switch (command) {
          case 0:
            {
              int index, value;
              std::cin >> index >> value;
              lazy.ApplyAtIndex(index, operations::AddOp{value});
              break;
            }
          case 1:
          {
              int l, r;
              std::cin >> l >> r;
              auto result = lazy.GetFromRange<statistics::Sum>(l, r-1).result;
              std::cout << result << std::endl;
              break;
          }
        }
    }
}