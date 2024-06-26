#include <iostream>
#include <algo/trees/lazy_segment_tree.hpp>
#include <vector>

const int MODULO = 998244353;

int main() {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for(int i = 0; i < n; ++i) {
      std::cin >> a[i];
    }

    // TODO: use not lazy (eager/regular) segment tree
    auto lazy = algo::trees::LazySegmentTree(a);

    for(int i = 0; i < q; ++i) {
        int command;
        std::cin >> command;
        switch (command) {
          case 0:
            {
              int index, value;
              std::cin >> index >> value;
              lazy.AddValue(index, index, value);
              break;
            }
          case 1:
          {
              int l, r;
              std::cin >> l >> r;
              auto result = lazy.GetSum(l, r-1);
              std::cout << result << std::endl;
              break;
          }
        }
    }
}